#ifndef ARCHIPELAGO_STATUS_DIALOG_H
#define ARCHIPELAGO_STATUS_DIALOG_H

#include "LawnDialog.h"
#include "../../SexyAppFramework/EditListener.h"

class LawnApp;

class ArchipelagoStatusDialog : public LawnDialog, public EditListener
{
public:
	LawnApp*			mApp;
	LawnEditWidget*			mHostEditWidget;
	LawnEditWidget*			mSlotEditWidget;
	LawnEditWidget*			mPasswordEditWidget;
	LawnStoneButton*		mConnectButton;

public:
    ArchipelagoStatusDialog(LawnApp* theApp);
	virtual ~ArchipelagoStatusDialog();
	
	virtual int			GetPreferredHeight(int theWidth);
	virtual void		Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void		AddedToManager(WidgetManager* theWidgetManager);
	virtual void		RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void		Draw(Graphics* g);
	virtual void		EditWidgetText(int theId, const SexyString& theString);
	virtual bool		AllowChar(int, SexyChar theChar);
	
	void ButtonDepress(int theId) override;
};

#endif
