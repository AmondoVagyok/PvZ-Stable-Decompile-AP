#ifndef AP_WRAPPER_H
#define AP_WRAPPER_H

#include <functional>
#include <string>

class APWrapper_Private;

// Keep up to date with APClient::NetworkItem
struct APItem
{
    int64_t item;
    int64_t location;
    int player;
    unsigned flags;
};

class APWrapper
{
public:
    APWrapper();
    ~APWrapper();
    
    void Poll() const;
    
    void CheckLocations(const std::list<int64_t>& location_ids) const;
    
    void AddServerChatMessageListener(std::function<void(const std::string&)>) const;
    void AddItemsReceivedListener(std::function<void(const std::list<APItem>&)>) const;

private:
    APWrapper_Private* d;
};

#endif
