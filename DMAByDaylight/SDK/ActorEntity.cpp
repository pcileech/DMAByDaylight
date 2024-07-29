#include "Pch.h"
#include "ActorEntity.h"
#include "Camera.h"
#include "Globals.h"
#include "DebugAndDevConfig.h"
#include <ConfigUtilities.h>

ActorEntity::ActorEntity(uint64_t address,VMMDLL_SCATTER_HANDLE handle)
{
	Class = address;
	if(!address)
		return;
	 TargetProcess.AddScatterReadRequest(handle,Class + PlayerState,reinterpret_cast<void*>(&PlayerState), sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle,Class + AcknowledgedPawn, reinterpret_cast<void*>(&AcknowledgedPawn),sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle, Class + RootComponent, reinterpret_cast<void*>(&RootComponent),sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle, Class + 0x18, &ActorId,sizeof(int));
	 TargetProcess.AddScatterReadRequest(handle, Class + 0x3C0, &GeneratorPercentFinish, sizeof(float));
}

void ActorEntity::SetUp1(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;
	if (!AcknowledgedPawn && PlayerState) // players aren't pawns
	{
		TargetProcess.AddScatterReadRequest(handle, PlayerState + GameRole, reinterpret_cast<void*>(&PlayerRole), sizeof(EPlayerRole));
	}
}

void ActorEntity::SetUp2(VMMDLL_SCATTER_HANDLE handle)
{

	if (!Class)
		return;
	if (!RootComponent)
		return;

	if (ActorId == 757209)//护士落点
	{
		ActorRole = EActorRole::EActorRole_KillerItem;
		Name = LIT(L"落点");
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 3309776)//夹子
	{
		ActorRole = EActorRole::EActorRole_KillerItem;
		Name = LIT(L"夹子");
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 723409)//地窖不是Pawn或者玩家，单独拎出来绘制
	{
		ActorRole = EActorRole::EActorRole_Hatch;
		Name = LIT(L"窑");
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 995809)//大门
	{
		ActorRole = EActorRole::EActorRole_Gate;
		Name = LIT(L"出口");
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 1727265)//木板
	{
		ActorRole = EActorRole::EActorRole_Pallet;
		Name = LIT(L"木板");
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	//if (ActorId == 3223480)//图腾
	//{
	//	ActorRole = EActorRole::EActorRole_Window;
	//	//Name = LIT(L"图腾");

	//	UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
	//	Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
	//	return;
	//}

	if (ActorId == 3058432 || ActorId == 1174806)//电机
	{
		Name = LIT(L"发电机");
		ActorRole = EActorRole::EActorRole_Generator;
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}
	

	DebugAndDevConfig config = Configs.DebugESP;
	if (config.DebugESPEnabled == false)
	{
		if (!AcknowledgedPawn && PlayerState) {
			if (PlayerRole != EPlayerRole::EPlayerRole__VE_Camper && PlayerRole != EPlayerRole::EPlayerRole__VE_Slasher)
				return;
		}
	}
	//if (!AcknowledgedPawn && PlayerState) // players aren't pawns
	//{
	// 
	// 
		// by this point 我们过滤的只剩下玩家了
			//if (PlayerRole != EPlayerRole::EPlayerRole__VE_Camper && PlayerRole != EPlayerRole::EPlayerRole__VE_Slasher)
			//	return;
			// 
		// 创建一个字符串流，用于格式化输出
		std::stringstream ss;
		ss << std::hex << Class;

		// 获取字符串流中的内容，并转换为宽字符串
		std::string hexStr = ss.str();
		std::wstring wHexStr(hexStr.begin(), hexStr.end());

		Name = wHexStr;
		//Name = std::to_wstring(ActorId);
		if (PlayerRole == EPlayerRole::EPlayerRole__VE_Camper)
		{
			ActorRole = EActorRole::EActorRole_Players;
			Name = LIT(L"");
			switch (ActorId)
			{
			case 3276364:
				Name = LIT(L"德怀特");
				break;
			case 3276332:
				Name = LIT(L"德怀特");
				break;
			case 1781659:
				Name = LIT(L"梅格");
				break;
			case 3583742:
				Name = LIT(L"蕾贝卡");
				break;
			case 1593072:
				Name = LIT(L"索玛");
				break;
			case 1863893:
				Name = LIT(L"冯敏");
				break;
			case 2794252:
				Name = LIT(L"杰克");
				break;
			case 2794226:
				Name = LIT(L"杰克");
				break;
			case 2434774:
				Name = LIT(L"比尔");
				break;
			case 1392680:
				Name = LIT(L"黑妹");
				break;
			case 1485396:
				Name = LIT(L"尼亚");
				break;
			case 3128192:
				Name = LIT(L"大卫");
				break;
			case 2637089:
				Name = LIT(L"泰普");
				break;
			case 1827499:
				Name = LIT(L"亚当");
				break;
			case 331423:
				Name = LIT(L"史蒂夫");
				break;
			case 1521237:
				Name = LIT(L"塞布尔");
				break;
			case 3336770:
				Name = LIT(L"木村唯");
				break;
			case 774308:
				Name = LIT(L"萨丽娜");
				break;
			case 2269776:
				Name = LIT(L"艾达·王");
				break;
			case 920735:
				Name = LIT(L"艾伦");
				break;
				//case 1781659:
				//	Name = LIT(L"");
				//	break;

			default:
				Name = std::to_wstring(ActorId);
				break;
			}
			
		}
		else if(PlayerRole == EPlayerRole::EPlayerRole__VE_Slasher)
		{
			ActorRole = EActorRole::EActorRole_Players;
			Name = LIT(L"");
			switch (ActorId)
			{
			case 1340221:
				Name = LIT(L"DND巫妖");
				break;
			case 1537170:
				Name = LIT(L"护士");
				break;
			case 1792371:
				Name = LIT(L"农场主");
				break;
			case 3574830:
				Name = LIT(L"叮当");
				break;
			case 1781659:
				Name = LIT(L"");
				break;
			case 804980:
				Name = LIT(L"琳妹");
				break;
			  case 1290494:
				Name = LIT(L"兔妈");
				break;
			//	Name = LIT(L"");
			//	break;
			//case 804980:
			//	Name = LIT(L"");
			//	break;
			case 487045:
				Name = LIT(L"夹哥");
				break;
			default:
				Name = std::to_wstring(ActorId);
				break;
			}
		}
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
	//}
}

EPlayerRole ActorEntity::GetPlayerRole()
{
	return PlayerRole;
}

uint64_t ActorEntity::GetClass()
{
	return Class;
}

std::wstring ActorEntity::GetName()
{
	return Name;
}

EActorRole ActorEntity::GetActorRole()
{
	return ActorRole;
}

std::wstring ActorEntity::GetActorId()
{
	return std::to_wstring(ActorId);
}

Vector3 ActorEntity::GetPosition()
{
	Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
	return Position;
}

void ActorEntity::UpdatePosition(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;
	if (!PlayerState)
		return;
	if (AcknowledgedPawn) // players aren't pawns
		return;
	if (PlayerRole != EPlayerRole::EPlayerRole__VE_Camper && PlayerRole != EPlayerRole::EPlayerRole__VE_Slasher)
		return;
	TargetProcess.AddScatterReadRequest(handle, RootComponent + RelativeLocation, reinterpret_cast<void*>(&UEPosition), sizeof(UEVector));
}

float ActorEntity::GetGeneratorPercentFinish()
{
	return GeneratorPercentFinish;
}

void ActorEntity::UpdateGenPosition(VMMDLL_SCATTER_HANDLE handle)
{
	//if (!Class)
	//	return;
	//if (!RootComponent)
	//	return;
	//if (!PlayerState)
	//	return;
	//if (!AcknowledgedPawn) // generators are pawns
	//	return;
	//TargetProcess.AddScatterReadRequest(handle, RootComponent + RelativeLocation, reinterpret_cast<void*>(&UEPosition), sizeof(UEVector));
}
