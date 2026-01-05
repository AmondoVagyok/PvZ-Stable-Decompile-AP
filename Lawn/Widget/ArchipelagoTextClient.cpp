#include "ArchipelagoTextClient.h"

#include "../../LawnApp.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../Resources.h"
#include "../../SexyAppFramework/APWrapper.h"
#include "../../SexyAppFramework/Font.h"

const int CHAT_LINE_HEIGHT = 10;
const int CHAT_WIDTH = 600;

ArchipelagoTextClient::ArchipelagoTextClient(LawnApp* theApp)
{
    mApp = theApp;
    mFirstCharTyped = false;
    
    mMessageEditWidget = CreateEditWidget(0, this, nullptr);
    mMessageEditWidget->DisableAutocap();
    mMessageEditWidget->SetFont(FONT_PICO129);
    mMessageEditWidget->Resize(0, BOARD_HEIGHT - FONT_PICO129->GetHeight() - 10, CHAT_WIDTH, FONT_PICO129->GetHeight());
    
    Widget::Resize(0, 0, BOARD_HEIGHT, BOARD_WIDTH);
}

void ArchipelagoTextClient::Draw(Sexy::Graphics* g)
{
    Widget::Draw(g);
    
    g->PushState();
    
    auto font_height = FONT_PICO129->GetHeight();
    
    g->SetColor({0, 0, 0, 100});
    g->FillRect(0, BOARD_HEIGHT - 40 - 10 - font_height * CHAT_LINE_HEIGHT, CHAT_WIDTH, font_height * CHAT_LINE_HEIGHT + 10);
    g->FillRect(0, BOARD_HEIGHT - 15 - font_height, CHAT_WIDTH, font_height + 10);
    
    // Get the last 10 lines of text
    Sexy::Color aTextColor(255, 255, 255);
    auto chat_messages = mApp->mAP->ChatMessages();
    auto i = 0;
    for (auto message = chat_messages.rbegin(); message != chat_messages.rend(); ++message)
    {
        TodDrawString(g, *message, 0, BOARD_HEIGHT - 45 - font_height * i, FONT_PICO129, aTextColor, DS_ALIGN_LEFT);
        i++;
        if (i == CHAT_LINE_HEIGHT) break;
    }
    
    g->PopState();
}

void ArchipelagoTextClient::AddedToManager(Sexy::WidgetManager* theWidgetManager)
{
    Widget::AddedToManager(theWidgetManager);
    AddWidget(mMessageEditWidget);
    theWidgetManager->SetFocus(mMessageEditWidget);
}

void ArchipelagoTextClient::RemovedFromManager(Sexy::WidgetManager* theWidgetManager)
{
    Widget::RemovedFromManager(theWidgetManager);
    RemoveWidget(mMessageEditWidget);
}

void ArchipelagoTextClient::EditWidgetText(int theId, const SexyString& theString)
{
    EditListener::EditWidgetText(theId, theString);
    mApp->mAP->SendAPMessage(theString);
    mMessageEditWidget->SetText("");
}

bool ArchipelagoTextClient::AllowChar(int theId, SexyChar theChar)
{
    // Avoid t appearing in the chat when first opening it
    if (!mFirstCharTyped)
    {
        mFirstCharTyped = true;
        return false;
    }
    return EditListener::AllowChar(theId, theChar);
}
