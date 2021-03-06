#pragma once

#include "skse/GameFormComponents.h"
#include "skse/GameForms.h"
#include "skse/GameEvents.h"
#include "skse/NiObjects.h"
#include "GameBSExtraData.h"

class BSAnimationGraphEvent;

// TESObjectREFR and child classes

// 08
class BSHandleRefObject : public NiRefObject
{
public:
};

// 4
class IAnimationGraphManagerHolder
{
public:
	virtual ~IAnimationGraphManagerHolder();

	virtual UInt32			Unk_01(void);
	virtual UInt32			Unk_02(void);
	virtual UInt32			Unk_03(void);
	virtual UInt32			Unk_04(void);
	virtual UInt32			Unk_05(void);
	virtual UInt32			Unk_06(void);
	virtual UInt32			Unk_07(void);
	virtual UInt32			Unk_08(void);
	virtual UInt32			Unk_09(void);
	virtual UInt32			Unk_0A(void);
	virtual UInt32			Unk_0B(void);
	virtual UInt32			Unk_0C(void);
	virtual UInt32			Unk_0D(void);
	virtual UInt32			Unk_0E(void);
	virtual UInt32			Unk_0F(void);
	virtual UInt32			Unk_10(void);
	virtual UInt32			Unk_11(void);
	virtual UInt32			Unk_12(void);

//	void	** _vtbl;
};

// 128
class IPostAnimationChannelUpdateFunctor
{
public:
	virtual ~IPostAnimationChannelUpdateFunctor();
//	void	** _vtbl;
};

// 54
class TESObjectREFR : public TESForm
{
public:
	enum { kTypeID = kFormType_Reference };

	// currently none of these have been analyzed
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	Unk_3B(void);
	virtual void	Unk_3C(void);
	virtual void	Unk_3D(void);
	virtual void	Unk_3E(void);
	virtual void	Unk_3F(void);
	virtual void	Unk_40(void);
	virtual void	Unk_41(void);
	virtual void	Unk_42(void);
	virtual void	Unk_43(void);
	virtual void	Unk_44(void);
	virtual void	Unk_45(void);
	virtual void	Unk_46(void);
	virtual void	Unk_47(void);
	virtual void	Unk_48(void);
	virtual void	Unk_49(void);
	virtual void	Unk_4A(void);
	virtual void	Unk_4B(void);
	virtual void	Unk_4C(void);
	virtual void	Unk_4D(void);
	virtual void	Unk_4E(void);
	virtual void	Unk_4F(void);
	virtual void	Unk_50(void);
	virtual void	GetStartingPos(float * pos);
	virtual void	Unk_52(void);
	virtual void	Unk_53(void);
	virtual void	Unk_54(void);
	virtual void	Unk_55(void);
	virtual void	Unk_56(void);
	virtual void	Unk_57(void);
	virtual void	Unk_58(void);
	virtual void	Unk_59(void);
	virtual void	Unk_5A(void);
	virtual void	Unk_5B(void);
	virtual void	Unk_5C(void);
	virtual void	Unk_5D(void);
	virtual void	Unk_5E(void);
	virtual void	Unk_5F(void);
	virtual void	Unk_60(void);
	virtual void	Unk_61(void);
	virtual void	Unk_62(void);
	virtual void	Unk_63(void);
	virtual void	Unk_64(void);
	virtual void	Unk_65(void);
	virtual void	Unk_66(void);
	virtual void	Unk_67(void);
	virtual void	Unk_68(void);
	virtual void	Unk_69(void);
	virtual void	Unk_6A(void);
	virtual void *	Unk_6B(void);	// tested in HasLoaded3D, possibly NiNode * Get3D()
	virtual void	Unk_6C(void);
	virtual void	Unk_6D(void);
	virtual void	Unk_6E(void);
	virtual void	Unk_6F(void);
	virtual void	Unk_70(void);
	virtual void	Unk_71(void);
	virtual void	Unk_72(void);
	virtual void	Unk_73(void);
	virtual void	Unk_74(void);
	virtual void	Unk_75(void);
	virtual void	Unk_76(void);
	virtual void	Unk_77(void);
	virtual void	Unk_78(void);
	virtual void	Unk_79(void);
	virtual void	Unk_7A(void);
	virtual void	Unk_7B(void);
	virtual void	Unk_7C(void);
	virtual void	Unk_7D(void);
	virtual void	Unk_7E(void);
	virtual void	Unk_7F(void);
	virtual void	Unk_80(void);
	virtual void	Unk_81(void);
	virtual void	Unk_82(void);
	virtual void	Unk_83(void);
	virtual void	Unk_84(void);
	virtual void	Unk_85(void);
	virtual void	Unk_86(void);
	virtual void	Unk_87(void);
	virtual void	Unk_88(void);
	virtual void	Unk_89(void);
	virtual void	Unk_8A(void);
	virtual void	Unk_8B(void);
	virtual void	Unk_8C(void);
	virtual void	Unk_8D(void);
	virtual void	Unk_8E(void);
	virtual void	Unk_8F(void);
	virtual void	Unk_90(void);
	virtual void	Unk_91(void);
	virtual void	Unk_92(void);
	virtual void	Unk_93(void);
	virtual void	Unk_94(void);
	virtual void	Unk_95(void);
	virtual void	Unk_96(void);
	virtual void	Unk_97(void);
	virtual void	Unk_98(void);
	virtual void	Unk_99(void);
	virtual void	Unk_9A(void);
	virtual void	Unk_9B(void);

	// parents
	BSHandleRefObject	handleRefObject;	// 14
	BSTEventSink <BSAnimationGraphEvent>	animGraphEventSink;	// 1C
	IAnimationGraphManagerHolder			animGraphHolder;	// 20

	// members
	TESForm* baseForm;	// 24
	float	rotX;		// 28
	float	rotY;		// 2C
	float	rotZ;		// 30
	float	posX;		// 34
	float	posY;		// 38
	float	posZ;		// 3C
	
	TESObjectCELL	* parentCell;	// 40
	BGSMovementType	* movementType;	// 44
	BaseExtraList	extraData;		// 48
	UInt32			unk50;			// flags?
};
STATIC_ASSERT(sizeof(TESObjectREFR) == 0x54);
STATIC_ASSERT(offsetof(TESObjectREFR, handleRefObject) == 0x14);

// 04
class IMovementInterface
{
public:
	virtual ~IMovementInterface();
//	void	** _vtbl;	// 00
};

// 04
class IMovementState : public IMovementInterface
{
public:
	virtual ~IMovementState();
};

// 10 - 8 byte alignment
class ActorState : public IMovementState
{
public:
	virtual ~ActorState();

	//UInt32 align04;	// 04
	//UInt64 flags;	// 08
	UInt32 flags04;
	UInt32 flags08;
};

//STATIC_ASSERT(sizeof(ActorState) == 0x10);

// 1B0
class Actor : public TESObjectREFR
{
public:
	virtual ~Actor();

	struct SpellArray
	{
		UInt32 allocatedCount;
		SpellItem** spells;
		UInt32 spellCount;
	};

	MagicTarget		magicTarget;					// 054
	ActorValueOwner	actorValueOwner;				// 060
	//UInt32			align64;						// 064
	ActorState		actorState;						// 068
	BSTEventSink<void*> transformDeltaEvent;		// 078 .?AV?$BSTEventSink@VBSTransformDeltaEvent@@@@
	BSTEventSink<void*>	characterMoveFinishEvent;	// 07C .?AV?$BSTEventSink@VbhkCharacterMoveFinishEvent@@@@
	IPostAnimationChannelUpdateFunctor	unk_080;	// 080 IPostAnimationChannelUpdateFunctor
	UInt32	unk_84[32];								// 084
	SpellArray	addedSpells;						// 104
	UInt32	unk_110[38];							// 110
	// these last two may be on character instead
	BSTEventSink<void*>	 menuOpenCloseEvent;		// 1A8	.?AV?$BSTEventSink@VMenuOpenCloseEvent@@@@
	BSTEventSink<void*>	 menuModeChangeEvent;		// 1AC .?AV?$BSTEventSink@VMenuModeChangeEvent@@@@
};
STATIC_ASSERT(offsetof(Actor, magicTarget) == 0x54);
STATIC_ASSERT(offsetof(Actor, actorValueOwner) == 0x60);
STATIC_ASSERT(sizeof(ActorValueOwner) == 0x4);
STATIC_ASSERT(offsetof(Actor, actorState) == 0x64);
STATIC_ASSERT(offsetof(Actor, transformDeltaEvent) == 0x70);
STATIC_ASSERT(offsetof(Actor, addedSpells) == 0xFC);
STATIC_ASSERT(offsetof(Actor, menuOpenCloseEvent) == 0x1A0);
STATIC_ASSERT(sizeof(Actor) == 0x1A8);

// 1B0
// Character + 98 = process?
class Character : public Actor
{
	enum { kTypeID = kFormType_Character };
public:
	MEMBER_FN_PREFIX(Character);
	DEFINE_MEMBER_FN(QueueNiNodeUpdate, void, 0x0072E660, bool);
};

// 718
class PlayerCharacter : public Character
{
public:
	virtual ~PlayerCharacter();

	// parents
	BSTEventSink <void *>	userEventEnabledEvent;		// 1A8 .?AV?$BSTEventSink@VUserEventEnabledEvent@@@@
	BSTEventSource <void *>	actorCellEventSource;		// 1AC .?AV?$BSTEventSource@UBGSActorCellEvent@@@@
	BSTEventSource <void *>	actorDeathEventSource;		// 1DC .?AV?$BSTEventSource@UBGSActorDeathEvent@@@@
	BSTEventSource <void *>	positionPlayerEventSource;	// 20C .?AV?$BSTEventSource@UPositionPlayerEvent@@@@

	UInt32	pad23C[(0x6D4 - 0x23C) >> 2];	// 23C
	UInt8   pad6D4;							// 6D4
	UInt8	numPerkPoints;					// 6D5

	// ### todo: confirm
	struct ObjDesc
	{
		TESForm	* form;
		void	* extraData;
	};

	MEMBER_FN_PREFIX(PlayerCharacter);
	DEFINE_MEMBER_FN(GetDamage, double, 0x0072DF90, ObjDesc * pForm);
	DEFINE_MEMBER_FN(GetArmorValue, double, 0x0072DF60, ObjDesc * pForm);
};

STATIC_ASSERT(offsetof(PlayerCharacter, userEventEnabledEvent) == 0x1A8);
STATIC_ASSERT(offsetof(PlayerCharacter, pad23C) == 0x23C);
STATIC_ASSERT(offsetof(PlayerCharacter, numPerkPoints) == 0x6D5);

// D8
class Explosion : public TESObjectREFR
{
	//
};

// 118
class ChainExplosion : public Explosion
{
	//
};

// 88
class Hazard : public TESObjectREFR
{
	enum { kTypeID = kFormType_Hazard };
};

// 140+
class Projectile : public TESObjectREFR
{
	//
};

// 150
class BarrierProjectile : public Projectile
{
	enum { kTypeID = kFormType_BarrierProj };
};

// 174
class BeamProjectile : public Projectile
{
	enum { kTypeID = kFormType_BeamProj };
};

// 16C
class ConeProjectile : public Projectile
{
	enum { kTypeID = kFormType_ConeProj };
};

// 148
class FlameProjectile : public Projectile
{
	enum { kTypeID = kFormType_FlameProj };
};

// 148
class GrenadeProjectile : public Projectile
{
	enum { kTypeID = kFormType_Grenade };
};

// 148
class MissileProjectile : public Projectile
{
	enum { kTypeID = kFormType_Missile };
};

// 150
class ArrowProjectile : public MissileProjectile
{
	enum { kTypeID = kFormType_Arrow };
};
