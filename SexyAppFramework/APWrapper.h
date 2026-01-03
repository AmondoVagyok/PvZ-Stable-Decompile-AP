#ifndef AP_WRAPPER_H
#define AP_WRAPPER_H

#include <functional>
#include <string>

class APWrapper_Private;

class APWrapper
{
public:
    APWrapper();
    ~APWrapper();
    
    void Poll() const;
    
    void AddServerChatMessageListener(std::function<void(const std::string&)>);

private:
    APWrapper_Private* d;
};

#endif
