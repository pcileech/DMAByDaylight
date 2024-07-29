#include "Pch.h"
#include "Engine.h"
#include "ActorEntity.h"
#include "Globals.h"
#include "PlayerEsp.h"
#include "GeneratorEsp.h"

Engine::Engine()
{
	//GNameTable = TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress(ProcessName) + GNames);
	//printf("GNameTable: %p\n", GNameTable);
	GWorld = TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress(ProcessName) + GWorld);
	//printf("GWorld: %p\n", GWorld);
	PersistentLevel = TargetProcess.Read<uint64_t>(GWorld + PersistentLevel);
	//printf("PersistentLevel: %p\n", PersistentLevel);
	OwningGameInstance = TargetProcess.Read<uint64_t>(GWorld + OwningGameInstance);
	//printf("OwningGameInstance: %p\n", OwningGameInstance);
	LocalPlayers = TargetProcess.Read<uint64_t>(OwningGameInstance + LocalPlayers);
	//printf("LocalPlayers: %p\n", LocalPlayers);
	LocalPlayers = TargetProcess.Read<uint64_t>(LocalPlayers);
	//printf("LocalPlayers: %p\n", LocalPlayers);
	PlayerController = TargetProcess.Read<uint64_t>(LocalPlayers + PlayerController);
	//printf("PlayerController: %p\n", PlayerController);
	AcknowledgedPawn = TargetProcess.Read<uint64_t>(PlayerController + AcknowledgedPawn);
	//printf("AcknowledgedPawn: %p\n", AcknowledgedPawn);
	CameraManager = TargetProcess.Read<uint64_t>(PlayerController + CameraManager);
	//printf("CameraManager: %p\n", CameraManager);
	CameraEntry = TargetProcess.Read<CameraCacheEntry>(CameraManager + CameraCachePrivateOffset);
	//printf("CameraCacheEntry: %p\n", CameraEntry);

	//auto interaction_handler = TargetProcess.Read<uintptr_t>(AcknowledgedPawn + 0xb58);
	//auto skillcheck = TargetProcess.Read<uintptr_t>(interaction_handler + 0x310);

	//auto is_displayed = TargetProcess.Read<bool>(skillcheck + 0x151);
	//auto current_progress = TargetProcess.Read<float>(skillcheck + 0x154);
	//auto success_zone = TargetProcess.Read<float>(skillcheck + 0x198);

	//std::cout << "is_displayed: " << is_displayed << std::endl;
	//std::cout << "current_progress: " << current_progress << std::endl;
	//std::cout << "success_zone: " << success_zone << std::endl;

	//printf("\n\n");

	//if (is_displayed && current_progress > success_zone)
	//{
	//	// press space
	//	std::cout << "hit space!!!!!!!!!!!!!!!!!! " << std::endl;

	//}

}


void Engine::Cache()
{

	OwningActor = TargetProcess.Read<uint64_t>(PersistentLevel + OwningActorOffset);
	MaxPacket = TargetProcess.Read<uint32_t>(PersistentLevel + MaxPacketOffset);
	
	//printf("Actor Array: %p\n", OwningActor);
	//printf("Actor Array Size: %d\n", MaxPacket);

	std::vector<uint64_t> entitylist;
	entitylist.resize(MaxPacket);
	std::unique_ptr<uint64_t[]> object_raw_ptr = std::make_unique<uint64_t[]>(MaxPacket);
	TargetProcess.Read(OwningActor, object_raw_ptr.get(), MaxPacket * sizeof(uint64_t));
	for (size_t i = 0; i < MaxPacket; i++)
	{
		entitylist[i] = object_raw_ptr[i];

		//------------------------------------------------

	}

	std::list<std::shared_ptr<ActorEntity>> actors;
	auto handle = TargetProcess.CreateScatterHandle();
	for (uint64_t address : entitylist)
	{
		uintptr_t actor = address;
		if (!actor)
			continue;
		
			std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor, handle);
			actors.push_back(entity);
		
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);


	handle = TargetProcess.CreateScatterHandle();
	for (std::shared_ptr<ActorEntity> entity : actors)
	{
		entity->SetUp1(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);

	std::vector<std::shared_ptr<ActorEntity>> playerlist;
	for (std::shared_ptr<ActorEntity> entity : actors)
	{
		entity->SetUp2(handle);
		if (entity->GetName() == LIT(L"Entity"))
			continue;
		if(entity->GetPosition() == Vector3::Zero())
						continue;
		playerlist.push_back(entity);
	}
	Actors = playerlist;
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
}
void Engine::UpdatePlayers()
{
	auto handle = TargetProcess.CreateScatterHandle();
	for (std::shared_ptr<ActorEntity> entity : Actors)
	{
		entity->UpdatePosition(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
}

void Engine::UpdateGenerators()
{
	//auto handle = TargetProcess.CreateScatterHandle();
	//for (std::shared_ptr<ActorEntity> entity : Actors)
	//{
	//	entity->UpdateGenPosition(handle);
	//}
	//TargetProcess.ExecuteReadScatter(handle);
	//TargetProcess.CloseScatterHandle(handle);
}

void Engine::UpdateDebugs()
{
	//auto handle = TargetProcess.CreateScatterHandle();
	//for (std::shared_ptr<ActorEntity> entity : Actors)
	//{
	//	entity->UpdateGenPosition(handle);
	//}
	//TargetProcess.ExecuteReadScatter(handle);
	//TargetProcess.CloseScatterHandle(handle);
}

void Engine::RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, CameraManager + CameraCachePrivateOffset,reinterpret_cast<void*>(&CameraEntry),sizeof(CameraCacheEntry));
}

CameraCacheEntry Engine::GetCameraCache()
{
	return CameraEntry;
}

std::vector<std::shared_ptr<ActorEntity>> Engine::GetActors()
{
	return Actors;
}

uint32_t Engine::GetActorSize()
{
	return MaxPacket;
}
