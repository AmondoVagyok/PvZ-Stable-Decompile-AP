#include "APWrapper.h"

#define APCLIENT_DEBUG

#define _WIN32_WINNT 0x0600
#include <apclient.hpp>
#include <apuuid.hpp>

class APWrapper_Private {
public:
    std::map<uint64_t, std::function<void(const std::string&)>> server_chat_listeners;
    std::map<uint64_t, std::function<void(const std::list<APItem>&)>> item_received_listeners;
    std::map<uint64_t, std::function<void()>> connection_complete_listener;
    std::map<uint64_t, std::function<void()>> disconnection_listener;
    std::map<uint64_t, std::function<void(const std::string&)>> slot_refused_listeners;
    std::map<uint64_t, std::function<void(const std::string&, const std::string&)>> deathlink_listeners;
    std::map<uint64_t, std::function<void(const std::string&)>> any_chat_listeners;
    
    uint64_t next_listener_id = 0;
    
    APClient* mAP = nullptr;
    std::string server_name;
    std::string slot_name;
    std::string password;
    nlohmann::json slot_data;
    
    std::list<APItem> received_items;
    std::map<int64_t, APItem> location_scouts;
    
    std::list<std::string> tags;
    float last_sent_deathlink;
    std::string last_deathlink_source;
    std::string last_deathlink_cause;
    
    std::list<std::string> chat_messages;
    
    bool delete_on_next_poll = false;
};

ListenerHandle::~ListenerHandle()
{
    on_delete();
}

ListenerHandle::ListenerHandle(std::function<void()> on_delete)
    : on_delete(on_delete)
{
}

APWrapper::APWrapper() : d(new APWrapper_Private)
{
}

APWrapper::~APWrapper()
{
    delete d->mAP;
    delete d;
}

void APWrapper::Connect(const std::string& server_name, const std::string& slot_name, const std::string& password) const
{
    // Already connected
    if (d->mAP)
    {
        return;
    }
    
    d->server_name = server_name;
    d->slot_name = slot_name;
    d->password = password;
    d->tags.clear();
    d->chat_messages.clear();
    
    d->mAP = new APClient(ap_get_uuid("uuid.txt"), "Plants vs. Zombies: Replanted", server_name);
    d->mAP->set_print_handler([](const std::string& print_line)
    {
        std::cout << "Archipelago: " << print_line << std::endl;
    });
    d->mAP->set_print_json_handler([this](const APClient::PrintJSONArgs& print_line)
    {
        std::string concatenated_message;
        for (const auto& node : print_line.data)
        {
            concatenated_message.append(node.text);
        }
        
        d->chat_messages.push_back(concatenated_message);
        
        if (print_line.type == "ServerChat")
        {
            for (const auto& server_chat_listener : this->d->server_chat_listeners)
            {
                server_chat_listener.second(concatenated_message);
            }
        }
        
        for (const auto& any_chat_listener : this->d->any_chat_listeners)
        {
            any_chat_listener.second(concatenated_message);
        }
    });
    d->mAP->set_socket_connected_handler([this, slot_name, password]
    {
        d->mAP->ConnectSlot(slot_name, password, 0b111 /* Everything! */, d->tags);
    });
    d->mAP->set_slot_connected_handler([this](const nlohmann::json& slot_data)
    {
        this->d->slot_data = slot_data;
        
        // Scout all locations and cache them
        auto scouted_locations = this->d->mAP->get_missing_locations();
        scouted_locations.merge(this->d->mAP->get_checked_locations());
        
        d->mAP->LocationScouts(std::list(scouted_locations.begin(), scouted_locations.end()), 0);
        
        for (const auto& connection_complete_listener : this->d->connection_complete_listener)
        {
            connection_complete_listener.second();
        }
    });
    d->mAP->set_slot_refused_handler([this](const std::list<std::string>& errors) {
        auto error = errors.back();
        for (const auto& slot_refused_listener : this->d->slot_refused_listeners)
        {
            slot_refused_listener.second(error);
        }
        this->Disconnect();
    });
    d->mAP->set_socket_error_handler([this](const std::string& error_message)
    {
        this->Disconnect();
    });
    d->mAP->set_items_received_handler([this](const std::list<APClient::NetworkItem>& items) {
        std::list<APItem> ap_items;
        for (const auto item : items)
        {
            ap_items.push_back(APItem {
                item.item,
                item.location,
                item.player,
                item.flags,
                item.index
            });
        }
        
        d->received_items.splice(d->received_items.end(), ap_items);

        for (const auto& item_received_listener : this->d->item_received_listeners)
        {
            item_received_listener.second(ap_items);
        }
    });
    d->mAP->set_socket_disconnected_handler([this]
    {
        for (const auto& disconnection_listener : this->d->disconnection_listener)
        {
            disconnection_listener.second();
        }
        this->Disconnect();
    });
    d->mAP->set_bounced_handler([this](const nlohmann::json& bounce_data)
    {
        auto tags = bounce_data["tags"];
        if (tags.size() > 0 && tags[0] == "DeathLink")
        {
            // Handle DeathLink packet
            auto data = bounce_data["data"];
            std::string source = data["source"];
            auto cause = data["cause"]; // string
            double time = data["time"]; // number_float
            
            if (time != d->last_sent_deathlink)
            {
                d->last_deathlink_source = source;
                if (cause.is_string())
                {
                    d->last_deathlink_cause = cause;
                } else
                {
                    d->last_deathlink_cause = "";
                }
                    
                for (const auto& deathlink_listener : this->d->deathlink_listeners)
                {
                    deathlink_listener.second(source, d->last_deathlink_cause);
                }
            }
        }
    });
    d->mAP->set_location_info_handler([this](const std::list<APClient::NetworkItem>& location_info)
    {
        for (const auto& location : location_info)
        {
            d->location_scouts[location.location] = APItem {
                location.item,
                location.location,
                location.player,
                location.flags,
                location.index
            };
        }
    });
}

void APWrapper::Disconnect() const
{
    d->delete_on_next_poll = true;
}

void APWrapper::DisconnectNow() const
{
    delete d->mAP;
    d->mAP = nullptr;
}

std::string APWrapper::ServerName() const
{
    return d->server_name;
}

std::string APWrapper::SlotName() const
{
    return d->slot_name;
}

std::string APWrapper::Password() const
{
    return d->password;
}

enum APWrapper::ConnectionStatus APWrapper::ConnectionStatus() const
{
    if (!d->mAP) return ConnectionStatus::Disconnected;

    switch (d->mAP->get_state())
    {
    case APClient::State::SLOT_CONNECTED:
        return ConnectionStatus::Connected;
    case APClient::State::DISCONNECTED:
    case APClient::State::SOCKET_CONNECTING:
    case APClient::State::SOCKET_CONNECTED:
    case APClient::State::ROOM_INFO:
        return ConnectionStatus::Connecting;
    }
    
    return ConnectionStatus::Disconnected;
}

void APWrapper::SendAPMessage(const std::string& message) const
{
    if (!d->mAP) return;
    d->mAP->Say(message);
}

int64_t APWrapper::MySlot() const
{
    if (!d->mAP) return -1;
    return d->mAP->get_player_number();
}

std::string APWrapper::PlayerDisplayName(int slot) const
{
    if (!d->mAP) return "";
    
    if (slot == 0) return "Archipelago";
    
    auto players = d->mAP->get_players();
    for (const auto& player : d->mAP->get_players())
    {
        if (player.slot != slot) continue;
        if (player.alias.empty())
        {
            return player.name;
        }
        return player.name + " (" + player.alias + ")";
    }
    return "";
}

std::string APWrapper::ItemName(const APItem& item) const
{
    const auto player_game = d->mAP->get_player_game(item.player);
    return d->mAP->get_item_name(item.item, player_game);
}

std::string APWrapper::ItemName(const int64_t item, const int64_t slot) const
{
    const auto player_game = d->mAP->get_player_game(slot);
    return d->mAP->get_item_name(item, player_game);
}

int64_t APWrapper::ReceivedItemCount(int item) const
{
    auto count = 0;
    for (const auto& received_item : d->received_items)
    {
        if (received_item.item == item) count++;
    }
    return count;
}

void APWrapper::Poll() const
{
    if (d->delete_on_next_poll)
    {
        delete d->mAP;
        d->mAP = nullptr;
        d->delete_on_next_poll = false;
    }
    
    if (!d->mAP) return;
    this->d->mAP->poll();
}

void APWrapper::CheckLocations(const std::list<int64_t>& location_ids) const
{
    if (!d->mAP) return;
    this->d->mAP->LocationChecks(location_ids);
}

APItem APWrapper::ItemAtLocation(int64_t location) const
{
    return d->location_scouts[location];
}

void APWrapper::SetGoal() const
{
    if (!d->mAP) return;
    this->d->mAP->StatusUpdate(APClient::ClientStatus::GOAL);
}

void APWrapper::EnableDeathLink(bool enable) const
{
    if (!enable)
    {
        d->tags.remove_if([](std::string tag)
        {
            return tag == "DeathLink";
        });
    }
    else
    {
        d->tags.emplace_back("DeathLink");
    }
    
    this->UpdateConnectionInformation();
}

void APWrapper::SendDeathLink(const std::string& reason) const
{
    // Ensure DeathLink is on
    for (const auto& tag : d->tags)
    {
        if (tag == "DeathLink")
        {
            auto time = d->mAP->get_server_time();
            d->last_sent_deathlink = time;
            d->mAP->Bounce({
                {"time", time},
                {"source", this->PlayerDisplayName(this->MySlot())},
                {"cause", reason}
            }, {}, {}, {"DeathLink"});
            return;
        }
    }
}

void APWrapper::ClearLastDeathLink() const
{
    d->last_deathlink_cause = "";
    d->last_deathlink_source = "";
}

std::string APWrapper::LastDeathLinkSource() const
{
    return d->last_deathlink_source;
}

std::string APWrapper::LastDeathLinkCause() const
{
    return d->last_deathlink_cause;
}

std::list<std::string> APWrapper::ChatMessages() const
{
    return d->chat_messages;
}

ListenerHandle* APWrapper::AddServerChatMessageListener(std::function<void(const std::string&)> listener) const
{
    auto id = d->next_listener_id++;
    this->d->server_chat_listeners.insert_or_assign(id, listener);
    
    return new ListenerHandle([this, id] { this->d->server_chat_listeners.erase(id); });
}

ListenerHandle* APWrapper::AddItemsReceivedListener(std::function<void(const std::list<APItem>&)> listener) const
{
    auto id = d->next_listener_id++;
    this->d->item_received_listeners.insert_or_assign(id, listener);
    
    return new ListenerHandle([this, id] { this->d->item_received_listeners.erase(id); });
}

ListenerHandle* APWrapper::AddConnectionCompleteListener(std::function<void()> listener) const
{
    auto id = d->next_listener_id++;
    this->d->connection_complete_listener.insert_or_assign(id, listener);
    
    return new ListenerHandle([this, id] { this->d->connection_complete_listener.erase(id); });
}

ListenerHandle* APWrapper::AddSlotRefusedListener(std::function<void(const std::string&)> listener) const
{
    auto id = d->next_listener_id++;
    this->d->slot_refused_listeners.insert_or_assign(id, listener);
    
    return new ListenerHandle([this, id] { this->d->slot_refused_listeners.erase(id); });
}

ListenerHandle* APWrapper::AddDisconnectionListener(std::function<void()> listener) const
{
    auto id = d->next_listener_id++;
    this->d->disconnection_listener.insert_or_assign(id, listener);
    
    return new ListenerHandle([this, id] { this->d->disconnection_listener.erase(id); });
}

ListenerHandle* APWrapper::AddDeathLinkListener(std::function<void(const std::string&, const std::string&)> listener) const
{
    auto id = d->next_listener_id++;
    this->d->deathlink_listeners.insert_or_assign(id, listener);
    
    return new ListenerHandle([this, id] { this->d->deathlink_listeners.erase(id); });
}

ListenerHandle* APWrapper::AddAnyChatMessageListener(std::function<void(const std::string&)> listener) const
{
    auto id = d->next_listener_id++;
    this->d->any_chat_listeners.insert_or_assign(id, listener);
    
    return new ListenerHandle([this, id] { this->d->any_chat_listeners.erase(id); });
}

void APWrapper::UpdateConnectionInformation() const
{
    if (!d->mAP) return;
    
    d->mAP->ConnectUpdate(0b111, d->tags);
}

