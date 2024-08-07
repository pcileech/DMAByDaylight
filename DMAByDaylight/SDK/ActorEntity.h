#pragma once
#include "EngineStructs.h"
enum class EPlayerRole: uint8_t
{
	EPlayerRole__VE_None = 0,
	EPlayerRole__VE_Slasher = 1,
	EPlayerRole__VE_Camper = 2,
	EPlayerRole__VE_Observer = 3,
	EPlayerRole__Max = 4,
	EPlayerRole__EPlayerRole_MAX = 5
};

enum class EActorRole : uint8_t
{
	EActorRole_Generator = 0,
	EActorRole_Players = 1,
	EActorRole_Tokem = 2,
	EActorRole_MeatHook = 3,
	EActorRole_Hatch = 4,
	EActorRole_Pallet = 5,
	EActorRole_Window = 6,
	EActorRole_Gate = 7,
	EActorRole_KillerItem = 8
};
class ActorEntity
{
private:

	uint64_t Class = 0;
	int ActorId = -1;
	float GeneratorPercentFinish = 0.0;
	EActorRole ActorRole;
	EPlayerRole PlayerRole;
	uint64_t PlayerState = 0x2C0; // Pawn -> PlayerState
	uint64_t AcknowledgedPawn = 0x2f8;
	uint64_t RootComponent = 0x1A8; // Actor -> RootComponent
	uint64_t RelativeLocation = 0x140; // SceneComponent -> RelativeLocation
	uint64_t GameRole = 0x3fa; // DBDPlayerState -> GameRole
	uint64_t ClassOffset = 0x10; // AActor -> Class
	uint64_t NameOffset = 0x18; // UObject -> Name
	int objectId = 0;
	std::string ClassName;
	std::wstring Name = LIT(L"Entity");
	UEVector UEPosition;
	Vector3 Position;
public:
	uint64_t GNameTable;
	uint64_t GNames = 0xF5DBF00; // GNames全局名称表的偏移
	ActorEntity(uint64_t address, VMMDLL_SCATTER_HANDLE handle);
	void SetUp1(VMMDLL_SCATTER_HANDLE handle);
	void SetUp2(VMMDLL_SCATTER_HANDLE handle);
	uint64_t GetClass();
	EPlayerRole GetPlayerRole();
	std::wstring GetName();
	EActorRole GetActorRole();
	std::wstring GetActorId();
	Vector3 GetPosition();
	void UpdatePosition(VMMDLL_SCATTER_HANDLE handle);
	float GetGeneratorPercentFinish();
	void UpdateGenPosition(VMMDLL_SCATTER_HANDLE handle);

};