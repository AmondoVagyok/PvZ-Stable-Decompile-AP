#ifndef ARCHIPELAGOTEXTCLIENT_H
#define ARCHIPELAGOTEXTCLIENT_H
#include "../../SexyAppFramework/EditListener.h"
#include "../../SexyAppFramework/Widget.h"

class LawnEditWidget;
class LawnApp;

class ArchipelagoTextClient : public Sexy::Widget, public Sexy::EditListener
{
public:
    ArchipelagoTextClient(LawnApp* theApp);
    
    LawnApp*                    mApp;
    LawnEditWidget*			    mMessageEditWidget;
    bool                        mFirstCharTyped;
    
public:
    void Draw(Sexy::Graphics* g) override;
    void AddedToManager(Sexy::WidgetManager* theWidgetManager) override;
    void RemovedFromManager(Sexy::WidgetManager* theWidgetManager) override;
    void EditWidgetText(int theId, const SexyString& theString) override;
    bool AllowChar(int theId, SexyChar theChar) override;
};

#endif
