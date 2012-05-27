#pragma once

#include "skse/ScaleformCallbacks.h"
#include "skse/GameTypes.h"
#include "skse/Utilities.h"

class TESObjectREFR;

//// menu implementations

// 1C+
class IMenu : public FxDelegateHandler
{
public:
	IMenu();
	virtual ~IMenu();
	
	virtual void	InstallCallbacks(AddCallbackVisitor * visitor);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual UInt32	Unk_04(void * arg);
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);	// CurrentTime
	virtual void	Unk_06(void);

	GFxMovieView	* view;	// 08 - init'd to 0, a class, virtual fn 0x114 called in dtor
	UInt8			unk0C;		// 0C - init'd to 3
	UInt8			pad0D[3];	// 0D
	UInt32			unk10;		// 10 - init'd to 0
	UInt32			unk14;		// 14 - init'd to 0x12
	GRefCountBase	* unk18;	// 18 - holds a reference
};

// 34
class Console : public IMenu
{
public:
	// C+
	struct Unk20
	{
		struct Unk0
		{
			UInt32	unk0;
			UInt32	unk4;
		};

		struct Unk8
		{
			UInt32	unk0;
		};

		Unk0	unk0;	// 0
		Unk8	unk8;	// 8
	};

	void	* opcodeInfo;	// 1C - constructor checks that opcodes match
	Unk20	unk20;			// 20 - init'd to 0, probably history linked list?
	UInt32	unk2C;			// 2C - init'd to 0
	UInt8	unk30;			// 30 - init'd to 0
};

// 68
class BarterMenu : public IMenu
{
	GFxValue	* root;		// 1C
	// ...
	UInt8		unk34;		// 34
};

//// menu management

// 08
class IUIMessageData
{
public:
	virtual ~IUIMessageData();

//	void	** _vtbl;	// 00
	UInt8	unk04;		// 04
	UInt8	unk05;		// 05
	UInt8	pad06[2];	// 06
};

// 14
class BSUIMessageData : public IUIMessageData
{
public:
	BSString			* unk08;	// 08
	StringCache::Ref	unk0C;		// 0C
	UInt32				unk10;		// 10
};

// 10
// ### pool added in 1.3 (or maybe 1.2)
class UIMessage
{
public:
	enum
	{
		kMessage_Refresh = 0,	// used after ShowAllMapMarkers
		kMessage_Open,
		kMessage_Close,
	};

	StringCache::Ref	strData;	// 00
	UInt32				message;	// 04
	IUIMessageData		* objData;	// 08 - something with a virtual destructor
	UInt8				isPooled;	// 0C
	UInt8				pad0D[3];	// 0D
};

// 04
template <typename T>
class BSTMessageQueue
{
public:
	BSTMessageQueue();
	virtual ~BSTMessageQueue();

	virtual bool	Push(T * obj);		// pure, add (loop until lock taken, call Fn05)
	virtual bool	TryPush(T * obj);	// pure, try add (try to take lock, return false if already taken, else call Fn05)
	virtual bool	Pop(T * obj);		// pure, remove (loop until lock taken, call Fn06)
	virtual bool	TryPop(T * obj);	// pure, try remove (try to take lock, return false if already taken, else call Fn06)

//	void	** _vtbl;	// 00
};

// 08
template <typename T>
class BSTCommonMessageQueue : public BSTMessageQueue <T>
{
protected:
	virtual bool	PushInternal(T * obj);	// pure
	virtual bool	PopInternal(T * obj);	// pure

public:
	volatile UInt32	lock;	// 04
};

// 08 + sizeof(T) * T_len + 0C
template <typename T, UInt32 T_len>
class BSTCommonStaticMessageQueue : public BSTCommonMessageQueue <T>
{
public:
	T		data[T_len];	// 008
	UInt32	numEntries;		// 198 - offsets are for <UIMessage *, 100>
	UInt32	writePtr;		// 19C
	UInt32	readPtr;		// 1A0
};

// 1C8
// 5CC - pool added in 1.2 or 1.3
class UIManager
{
public:
	enum
	{
		kPoolSize = 0x40,
	};

	typedef BSTCommonStaticMessageQueue <UIMessage *, 100>	MessageQueue;

	UInt32			unk000;		// 000
	MessageQueue	messages;	// 004
	UInt32			pad1A8[(0x1C8 - 0x1A8) / 4];	// 1A8
	UInt32			poolUsed;	// 1C8
	UIMessage		messagePool[kPoolSize];	// 1CC

	MEMBER_FN_PREFIX(UIManager);
	// this takes ownership of the message ptr
//	DEFINE_MEMBER_FN(AddMessage, void, 0x004500C0, UIMessage * msg);	// old 1.1 implementation
	// 1.3 uses a little non-thread-safe pool of UIMessages to wrap around the nicely thread-safe BSTMessageQueue it gets added to
	DEFINE_MEMBER_FN(AddMessage, void, 0x00431DF0, StringCache::Ref * strData, UInt32 msgID, void * objData);

	static UIManager *	GetSingleton(void)
	{
		return *((UIManager **)0x012D8E74);
	}
};


// 11C
class UIStringHolder
{
public:
	void				* unk00;					// 000
	StringCache::Ref	faderData;					// 004 "FaderData"
	StringCache::Ref	hudData;					// 008 "HUDData"
	StringCache::Ref	hudCamData;					// 00C "HUDCamData"
	StringCache::Ref	floatingQuestMarkers;		// 010 "FloatingQuestMarkers"
	StringCache::Ref	consoleData;				// 014 "ConsoleData"
	StringCache::Ref	quantityData;				// 018 "QuantityData"
	StringCache::Ref	messageBoxData;				// 01C "MessageBoxData"
	StringCache::Ref	bsUIScaleformData;			// 020 "BSUIScaleformData"
	StringCache::Ref	bsUIMessageData;			// 024 "BSUIMessageData"
	StringCache::Ref	bsUIAnalogData;				// 028 "BSUIAnalogData"
	StringCache::Ref	inventoryUpdateData;		// 02C "InventoryUpdateData"
	StringCache::Ref	refHandleUIData;			// 030 "RefHandleUIData"
	StringCache::Ref	tesFormUIData;				// 034 "TESFormUIData"
	StringCache::Ref	loadingMenuData;			// 038 "LoadingMenuData"
	StringCache::Ref	kinectStateData;			// 03C "KinectStateChangeData"
	StringCache::Ref	kinectUserEventData;		// 040 "KinectUserEventData"
	StringCache::Ref	inventoryMenu;				// 044 "InventoryMenu"
	StringCache::Ref	console;					// 048 "Console"
	StringCache::Ref	dialogueMenu;				// 04C "Dialogue Menu"
	StringCache::Ref	hudMenu;					// 050 "HUD Menu"
	StringCache::Ref	mainMenu;					// 054 "Main Menu"
	StringCache::Ref	messageBoxMenu;				// 058 "MessageBoxMenu"
	StringCache::Ref	cursorMenu;					// 05C "Cursor Menu"
	StringCache::Ref	faderMenu;					// 060 "Fader Menu"
	StringCache::Ref	magicMenu;					// 064 "MagicMenu"
	StringCache::Ref	topMenu;					// 068 "Top Menu"
	StringCache::Ref	overlayMenu;				// 06C "Overlay Menu"
	StringCache::Ref	overlayInteractionMenu;		// 070 "Overlay Interaction Menu"
	StringCache::Ref	loadingMenu;				// 074 "Loading Menu"
	StringCache::Ref	tweenMenu;					// 078 "TweenMenu"
	StringCache::Ref	barterMenu;					// 07C "BarterMenu"
	StringCache::Ref	giftMenu;					// 080 "GiftMenu"
	StringCache::Ref	debugTextMenu;				// 084 "Debug Text Menu"
	StringCache::Ref	mapMenu;					// 088 "MapMenu"
	StringCache::Ref	lockpickingMenu;			// 08C "Lockpicking Menu"
	StringCache::Ref	quantityMenu;				// 090 "Quantity Menu"
	StringCache::Ref	statsMenu;					// 094 "StatsMenu"
	StringCache::Ref	containerMenu;				// 098 "ContainerMenu"
	StringCache::Ref	sleepWaitMenu;				// 09C "Sleep/Wait Menu"
	StringCache::Ref	levelUpMenu;				// 0A0 "LevelUp Menu"
	StringCache::Ref	journalMenu;				// 0A4 "Journal Menu"
	StringCache::Ref	bookMenu;					// 0A8 "Book Menu"
	StringCache::Ref	favoritesMenu;				// 0AC "FavoritesMenu"
	StringCache::Ref	raceSexMenu;				// 0B0 "RaceSex Menu"
	StringCache::Ref	craftingMenu;				// 0B4 "Crafting Menu"
	StringCache::Ref	trainingMenu;				// 0B8 "Training Menu"
	StringCache::Ref	mistMenu;					// 0BC "Mist Menu"
	StringCache::Ref	tutorialMenu;				// 0C0 "Tutorial Menu"
	StringCache::Ref	creditsMenu;				// 0C4 "Credits Menu"
	StringCache::Ref	titleSequenceMenu;			// 0C8 "TitleSequence Menu"
	StringCache::Ref	consoleNativeUIMenu;		// 0CC "Console Native UI Menu"
	StringCache::Ref	kinectMenu;					// 0D0 "Kinect Menu"
	StringCache::Ref	textWidget;					// 0D4 "TextWidget"
	StringCache::Ref	buttonBarWidget;			// 0D8 "ButtonBarWidget"
	StringCache::Ref	graphWidget;				// 0DC "GraphWidget"
	StringCache::Ref	textureWidget;				// 0E0 "TextureWidget"
	StringCache::Ref	uiMenuOK;					// 0E4 "UIMenuOK"
	StringCache::Ref	uiMenuCancel;				// 0E8 "UIMenuCancel"
	StringCache::Ref	showText;					// 0EC "Show Text"
	StringCache::Ref	hideText;					// 0F0 "Hide Text"
	StringCache::Ref	showList;					// 0F4 "Show List"
	StringCache::Ref	voiceReady;					// 0F8 "Voice Ready"
	StringCache::Ref	dmfoStr;					// 0FC "DMFOStr"
	StringCache::Ref	showJournal;				// 100 "Show Journal"
	StringCache::Ref	journalSettingsSaved;		// 104 "Journal Settings Saved"
	StringCache::Ref	closeMenu;					// 108 "CloseMenu"
	StringCache::Ref	closingAllMenus;			// 10C "Closing All Menus"
	StringCache::Ref	refreshMenu;				// 110 "RefreshMenu"
	StringCache::Ref	menuTextureDegradeEvent;	// 114 "Menu Texture Degrade Event"
	StringCache::Ref	diamondMarker;				// 118 "<img src='DiamondMarker' width='10' height='15' align='baseline' vspace='5'>"

	static UIStringHolder *	GetSingleton(void)
	{
		return *((UIStringHolder **)0x012D8E70);
	}
};

// E4
class Inventory3DManager
{
public:
	~Inventory3DManager();

//	void			** _vtbl;	// 00
	UInt32			pad04[(0x34 - 0x04) / 4];	// 04
	TESObjectREFR	* object;	// 34
	// ...
};


// 00C
class MenuTableItem
{
public:

	BSFixedString	name;				// 000
	IMenu			* menuInstance;		// 004	0 if the menu is not currently open
	void			* menuConstructor;	// 008

	bool operator==(const MenuTableItem & rhs) const	{ return name == rhs.name; }
	bool operator==(const BSFixedString a_name) const	{ return name == a_name; }
	operator UInt32() const								{ return (UInt32)name.data; }
};

typedef tHashSet<UInt32,MenuTableItem> MenuTable;


// 11C
class MenuManager
{
	enum
	{
		kMenu_Inventory = 0,
		kMenu_Console,
		kMenu_Dialogue,
		kMenu_HUD,
		kMenu_Main,
		kMenu_MessageBox,
		kMenu_Cursor,
		kMenu_Fader,
		kMenu_Magic,
		kMenu_Top,
		kMenu_Overlay,
		kMenu_OverlayInteraction,
		kMenu_Loading,
		kMenu_Tween,
		kMenu_Barter,
		kMenu_Gift,
		kMenu_DebugText,
		kMenu_Map,
		kMenu_Lockpicking,
		kMenu_Quantity,
		kMenu_Stats,
		kMenu_Container,
		kMenu_SleepWait,
		kMenu_LevelUp,
		kMenu_Journal,
		kMenu_Book,
		kMenu_Favorites,
		kMenu_RaceSex,
		kMenu_Crafting,
		kMenu_Training,
		kMenu_Mist,
		kMenu_Tutorial,
		kMenu_Credits,
		kMenu_TitleSequence,
		kMenu_ConsoleNativeUI,
		kMenu_Kinect
	};

	// 030
	struct Unknown1
	{
		UInt32		unk_000;	// 000 (= 0)
		UInt32		unk_004;	// 004 (= 0)

		UnkArray	unk_008;	// 008
		UnkArray	unk_014;	// 014
		UnkArray	unk_020;	// 020

		UInt32		unk_02C;	// 02C (= 0)
	};
	STATIC_ASSERT(sizeof(Unknown1) == 0x30);

	// 030
	struct Unknown3
	{
		UInt32		freqLow;	// 000 (= Frequency.LowPart)
		UInt32		freqHigh;	// 004 (= Frequency.HighPart)

		UInt32		unk_008;	// 008 (= 0)
		UInt32		unk_00C;	// 00C (= 0)
		UInt32		unk_010;	// 010 (= 0)
		UInt32		unk_014;	// 014 (= 0)
		UInt32		unk_018;	// 018 (= 0)
		UInt32		unk_01C;	// 018 (= frequency related)
		
		UInt32		unk_020;	// 020
		UInt32		unk_024;	// 024

		UInt32		unk_028;	// 028 (= 0)
		UInt32		unk_02C;	// 02C (= 0)
	};
	STATIC_ASSERT(sizeof(Unknown3) == 0x30);

private:

	UInt32		unk_000;	// 000
	Unknown1	unk_004;	// 004
	Unknown1	unk_034;	// 034
	Unknown1	unk_064;	// 064
	UnkArray	unk_094;	// 094
	UInt32		unk_0A0;	// 0A0
	MenuTable	menuTable;	// 0A4
	UInt32		unk_0C0;	// 0C0 (= 0)
	UInt32		unk_0C4;	// 0C4 (= 0)
	UInt32		unk_0C8;	// 0C8 (= 0)
	UInt32		unk_0CC;	// 0CC (= 0)
	UInt32		unk_0D0;	// 0D0 (= 0)
	UInt32		unk_0D4;	// 0D4 (= 0)
	UInt32		unk_0D8;	// 0D8 (= 0)
	UInt32		unk_0DC;	// 0DC (= 0)
	UInt32		unk_0E0;	// 0E0 (= 0)
	UInt32		unk_0E4;	// 0E4
	Unknown3	unk_0E8;
	bool		unk_118;	// 118 (= 0)	dbg: 1
	bool		unk_119;	// 119 (= 0)
	char		pad[2];

public:

	static MenuManager * GetSingleton(void)
	{
		return *((MenuManager **)0x012D8DD8);
	}

	static BSFixedString * LookupMenuName(UInt32 menuID)
	{
		UIStringHolder * sh = UIStringHolder::GetSingleton();
		if (!sh)
			return NULL;

		switch(menuID) {
			case kMenu_Inventory: return &sh->inventoryMenu;
			case kMenu_Console: return &sh->console;
			case kMenu_Dialogue: return &sh->dialogueMenu;
			case kMenu_HUD: return &sh->hudMenu;
			case kMenu_Main: return &sh->mainMenu;
			case kMenu_MessageBox: return &sh->messageBoxMenu;
			case kMenu_Cursor: return &sh->cursorMenu;
			case kMenu_Fader: return &sh->faderMenu;
			case kMenu_Magic: return &sh->magicMenu;
			case kMenu_Top: return &sh->topMenu;
			case kMenu_Overlay: return &sh->overlayMenu;
			case kMenu_OverlayInteraction: return &sh->overlayInteractionMenu;
			case kMenu_Loading: return &sh->loadingMenu;
			case kMenu_Tween: return &sh->tweenMenu;
			case kMenu_Barter: return &sh->barterMenu;
			case kMenu_Gift: return &sh->giftMenu;
			case kMenu_DebugText: return &sh->debugTextMenu;
			case kMenu_Map: return &sh->mapMenu;
			case kMenu_Lockpicking: return &sh->lockpickingMenu;
			case kMenu_Quantity: return &sh->quantityMenu;
			case kMenu_Stats: return &sh->statsMenu;
			case kMenu_Container: return &sh->containerMenu;
			case kMenu_SleepWait: return &sh->sleepWaitMenu;
			case kMenu_LevelUp: return &sh->levelUpMenu;
			case kMenu_Journal: return &sh->journalMenu;
			case kMenu_Book: return &sh->bookMenu;
			case kMenu_Favorites: return &sh->favoritesMenu;
			case kMenu_RaceSex: return &sh->raceSexMenu;
			case kMenu_Crafting: return &sh->craftingMenu;
			case kMenu_Training: return &sh->trainingMenu;
			case kMenu_Mist: return &sh->mistMenu;
			case kMenu_Tutorial: return &sh->tutorialMenu;
			case kMenu_Credits: return &sh->creditsMenu;
			case kMenu_TitleSequence: return &sh->titleSequenceMenu;
			case kMenu_ConsoleNativeUI: return &sh->consoleNativeUIMenu;
			case kMenu_Kinect: return &sh->kinectMenu;
			default: return NULL;
		};
	}

	MEMBER_FN_PREFIX(MenuManager);
	DEFINE_MEMBER_FN(IsMenuOpen, bool, 0x00A55250, BSFixedString * menuName);
	//DEFINE_MEMBER_FN(Register, void, 0x00A55660, const char * name, void * ctorFunc);

	GFxMovieView *		GetMovieView(UInt32 menuID);
	
};
STATIC_ASSERT(sizeof(MenuManager) == 0x11C);
