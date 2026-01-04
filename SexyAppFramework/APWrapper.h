#ifndef AP_WRAPPER_H
#define AP_WRAPPER_H

#include <functional>
#include <string>

class APWrapper;
class APWrapper_Private;

class ListenerHandle
{
public:
    ~ListenerHandle();
    
protected:
    friend APWrapper;
    explicit ListenerHandle(std::function<void()> on_delete);
    
private:
    std::function<void()> on_delete;
};

// Keep up to date with APClient::NetworkItem
struct APItem
{
    int64_t item;
    int64_t location;
    int player;
    unsigned flags;
    int index = -1; // to sync items, not actually part of NetworkItem
};

class APWrapper
{
public:
    APWrapper();
    ~APWrapper();
    
    enum class ConnectionStatus
    {
        Disconnected,
        Connecting,
        Connected
    };
    
    void Connect(const std::string& server_name, const std::string& slot_name, const std::string& password = "") const;
    void Disconnect() const;
    void DisconnectNow() const;
    std::string ServerName() const;
    std::string SlotName() const;
    std::string Password() const;
    ConnectionStatus ConnectionStatus() const;
    
    int64_t MySlot() const;
    
    std::string PlayerDisplayName(int slot) const;
    
    std::string ItemName(const APItem& item) const;
    std::string ItemName(int64_t item, int64_t slot) const;

    void Poll() const;
    
    void CheckLocations(const std::list<int64_t>& location_ids) const;
    
    ListenerHandle* AddServerChatMessageListener(std::function<void(const std::string&)>) const;
    ListenerHandle* AddItemsReceivedListener(std::function<void(const std::list<APItem>&)>) const;
    ListenerHandle* AddConnectionCompleteListener(std::function<void()>) const;
    ListenerHandle* AddSlotRefusedListener(std::function<void(const std::string&)>) const;
    ListenerHandle* AddDisconnectionListener(std::function<void()>) const;

private:
    APWrapper_Private* d;
};

#endif
