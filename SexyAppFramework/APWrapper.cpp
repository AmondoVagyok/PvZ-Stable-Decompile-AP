#include "APWrapper.h"

#define WSWRAP_NO_SSL
#define WSWRAP_NO_COMPRESSION
#define APCLIENT_DEBUG

#define _WIN32_WINNT 0x0600
#include <apclient.hpp>
#include <apuuid.hpp>

class APWrapper_Private {
public:
    std::vector<std::function<void(const std::string&)>> server_chat_listeners;
    std::vector<std::function<void(const std::list<APItem>&)>> item_received_listeners;
    
    APClient* mAP;
};

APWrapper::APWrapper() : d(new APWrapper_Private)
{
    d->mAP = new APClient(ap_get_uuid("uuid.txt"), "Plants vs. Zombies: Replanted");
    d->mAP->set_print_handler([](const std::string& print_line)
    {
        std::cout << "Archipelago: " << print_line << std::endl;
    });
    d->mAP->set_print_json_handler([this](const APClient::PrintJSONArgs& print_line)
    {
        if (print_line.type == "ServerChat")
        {
            std::string concatenated_message;
            for (auto node : print_line.data)
            {
                concatenated_message.append(node.text);
            }
            for (auto server_chat_listener : this->d->server_chat_listeners)
            {
                server_chat_listener(concatenated_message);
            }
        }
        std::cout << "Archipelago: " << print_line.message << std::endl;
    });
    d->mAP->set_socket_connected_handler([this]
    {
        d->mAP->ConnectSlot("Player1", "", 0b111 /* Everything! */);
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

        for (auto item_received_listener : this->d->item_received_listeners)
        {
            item_received_listener(ap_items);
        }
    });
    d->mAP->set_data_package_changed_handler([this](const nlohmann::json& data_package)
    {
        
    });
}

APWrapper::~APWrapper()
{
    delete d->mAP;
    delete d;
}

void APWrapper::Poll() const
{
    this->d->mAP->poll();
}

void APWrapper::CheckLocations(const std::list<int64_t>& location_ids) const
{
    this->d->mAP->LocationChecks(location_ids);
}

void APWrapper::AddServerChatMessageListener(std::function<void(const std::string&)> listener) const
{
    this->d->server_chat_listeners.push_back(listener);
}

void APWrapper::AddItemsReceivedListener(std::function<void(const std::list<APItem>&)> listener) const
{
    this->d->item_received_listeners.push_back(listener);
}

