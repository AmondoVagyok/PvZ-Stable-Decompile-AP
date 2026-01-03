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
    
    uint64_t next_listener_id = 0;
    
    APClient* mAP = nullptr;
    std::string server_name;
    std::string slot_name;
    std::string password;
    
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
    
    d->mAP = new APClient(ap_get_uuid("uuid.txt"), "Plants vs. Zombies: Replanted", server_name);
    d->mAP->set_print_handler([](const std::string& print_line)
    {
        std::cout << "Archipelago: " << print_line << std::endl;
    });
    d->mAP->set_print_json_handler([this](const APClient::PrintJSONArgs& print_line)
    {
        if (print_line.type == "ServerChat")
        {
            std::string concatenated_message;
            for (const auto& node : print_line.data)
            {
                concatenated_message.append(node.text);
            }
            for (const auto& server_chat_listener : this->d->server_chat_listeners)
            {
                server_chat_listener.second(concatenated_message);
            }
        }
        std::cout << "Archipelago: " << print_line.message << std::endl;
    });
    d->mAP->set_socket_connected_handler([this, slot_name, password]
    {
        d->mAP->ConnectSlot(slot_name, password, 0b111 /* Everything! */);
    });
    d->mAP->set_slot_connected_handler([this](const nlohmann::json& slot_data)
    {
        // TODO: Save slot data
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
        for (auto item : items)
        {
            ap_items.push_back(APItem {
                item.item,
                item.location,
                item.player,
                item.flags
            });
        }

        for (const auto& item_received_listener : this->d->item_received_listeners)
        {
            item_received_listener.second(ap_items);
        }
    });
    d->mAP->set_data_package_changed_handler([this](const nlohmann::json& data_package)
    {
        
    });
    d->mAP->set_socket_disconnected_handler([this]
    {
        for (const auto& disconnection_listener : this->d->disconnection_listener)
        {
            disconnection_listener.second();
        }
        this->Disconnect();
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

std::string APWrapper::PlayerDisplayName(int slot) const
{
    if (!d->mAP) return "";
    
    auto players = d->mAP->get_players();
    for (const auto& player : d->mAP->get_players())
    {
        if (player.slot != slot) continue;
        if (player.alias.empty())
        {
            return player.name;
        }
        else
        {
            return player.name + " (" + player.alias + ")";
        }
    }
    return "";
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

