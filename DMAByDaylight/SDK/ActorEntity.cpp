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


	if (ActorId == 3058432 || ActorId == 3064661)//gen esp
	{
		Name = LIT(L"gen");
		ActorRole = EActorRole::EActorRole_Generator;
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 3230099)//totem esp
	{
		Name = LIT(L"☠️");
		ActorRole = EActorRole::EActorRole_Tokem;
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 2780721)//chest esp
	{
		Name = LIT(L"📦");
		ActorRole = EActorRole::EActorRole_MeatHook;
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 724253)//hatch esp
	{
		Name = LIT(L"hatch");
		ActorRole = EActorRole::EActorRole_Hatch;
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 997216)//gate esp
	{
		Name = LIT(L"exit gate");
		ActorRole = EActorRole::EActorRole_Gate;
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 2378860 || ActorId == 1378121)//basement esp
	{
		ActorRole = EActorRole::EActorRole_Pallet;
		Name = LIT(L"🔽base");
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 2481165 || ActorId == 2485880) //red glyph esp
	{
		ActorRole = EActorRole::EActorRole_Window;
		Name = LIT(L"red glyph");
		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
		return;
	}

	if (ActorId == 3309776 || ActorId == 3309799 || ActorId == 2762714 || ActorId == 2762684 || ActorId == 3309780 || ActorId == 2762710 || ActorId == 2768163 || ActorId == 3316565)//bear trap esp
	{
		ActorRole = EActorRole::EActorRole_Window;
		Name = LIT(L"🐻");
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
		// by this point ÎÒÃÇ¹ýÂËµÄÖ»Ê£ÏÂÍæ¼ÒÁË
			//if (PlayerRole != EPlayerRole::EPlayerRole__VE_Camper && PlayerRole != EPlayerRole::EPlayerRole__VE_Slasher)
			//	return;
			// 
		// ´´½¨Ò»¸ö×Ö·û´®Á÷£¬ÓÃÓÚ¸ñÊ½»¯Êä³ö
		std::stringstream ss;
		ss << std::hex << Class;

		// »ñÈ¡×Ö·û´®Á÷ÖÐµÄÄÚÈÝ£¬²¢×ª»»Îª¿í×Ö·û´®
		std::string hexStr = ss.str();
		std::wstring wHexStr(hexStr.begin(), hexStr.end());

		Name = wHexStr;
		//Name = std::to_wstring(ActorId);
		; if (PlayerRole == EPlayerRole::EPlayerRole__VE_Camper)
		{
			ActorRole = EActorRole::EActorRole_Players;
			Name = LIT(L"");
			switch (ActorId)
			{
			case 3276364:
			case 3276332:
			case 3276335:
				Name = LIT(L"dwight");
				break;
			case 1781659:
				Name = LIT(L"meg");
				break;
			case 3583742:
			case 3583705:
				Name = LIT(L"rebecca");
				break;
			case 1593072:
				Name = LIT(L"gabriel");
				break;
			case 1863893:
				Name = LIT(L"feng");
				break;
			case 2794252:
			case 2794226:
			case 2794256:
				Name = LIT(L"jake");
				break;
			case 2434774:
				Name = LIT(L"bill");
				break;
			case 1392680:
				Name = LIT(L"claudette");
				break;
			case 1485396:
				Name = LIT(L"nea");
				break;
			case 3128192:
			case 3128195:
			case 3128241:
				Name = LIT(L"david");
				break;
			case 2637089:
				Name = LIT(L"tap");
				break;
			case 1827499:
				Name = LIT(L"adam");
				break;
			case 331423:
				Name = LIT(L"steve");
				break;
			case 1521237:
				Name = LIT(L"cutie");
				break;
			case 3336770:
			case 3336793:
			case 3336774:
				Name = LIT(L"yui");
				break;
			case 774308:
				Name = LIT(L"sarina");
				break;
			case 2269776:
				Name = LIT(L"ada");
				break;
			case 920735:
				Name = LIT(L"alanwake");
				break;
			case 2250222:
				Name = LIT(L"ace");
				break;
			case 839667:
				Name = LIT(L"claire");
				break;
			case 1433067:
				Name = LIT(L"kate");
				break;
			case 862857:
				Name = LIT(L"maria");
				break;
			case 1797634:
				Name = LIT(L"lara");
				break;
			case 3239630:
			case 3239662:
				Name = LIT(L"mikaela");
				break;
			case 2358687:
				Name = LIT(L"leon");
				break;
			case 16556098:
			case 1656098:
				Name = LIT(L"yun jin");
				break;
			case 2151738:
				Name = LIT(L"carlos");
				break;
			case 489684:
				Name = LIT(L"nancy");
				break;
			case 2422471:
				Name = LIT(L"felix");
				break;
			case 1768433:
				Name = LIT(L"vittoro");
				break;
			case 2438296:
				Name = LIT(L"quentin");
				break;
			case 2315587:
				Name = LIT(L"renato");
				break;
			case 1009381:
				Name = LIT(L"jane");
				break;
			case 1154353:
			case 665068:
				Name = LIT(L"cheryl");
				break;
			case 2852284:
			case 2852248:
				Name = LIT(L"ash");
				break;
			case 3226865:
			case 3226833:
				Name = LIT(L"thalita");
				break;
			case 1255978:
				Name = LIT(L"nick cage");
				break;
			case 2236563:
				Name = LIT(L"jonah");
				break;
			case 3386776:
				Name = LIT(L"troupe");
				break;
			case 1772048:
				Name = LIT(L"elodie");
				break;
			case 1279896:
				Name = LIT(L"jeff");
				break;
			case 1433076:
				Name = LIT(L"james");
				break;
			case 940574:
				Name = LIT(L"jill");
				break;
			case 2604096:
				Name = LIT(L"haddie");
				break;
			case 3587364:
			case 3587327:
				Name = LIT(L"ellen");
				break;
			case 816798:
				Name = LIT(L"chris");
				break;
			case 1679373:
				Name = LIT(L"sheva");
				break;
			case 1168016:
				Name = LIT(L"laurie");
				break;
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
				Name = LIT(L"lich");
				break;
			case 1537170:
				Name = LIT(L"nurse");
				break;
			case 1792371:
				Name = LIT(L"billy");
				break;
			case 3574830:
				Name = LIT(L"wraith");
				break;
			case 1781659:
				Name = LIT(L"ghost");
				break;
			case 804980:
				Name = LIT(L"Linmei");
				break;
			  case 1280494:
				Name = LIT(L"huntress");
				break;
			  case 2908597:
				  Name = LIT(L"huntress");
				  break;
			  case 3122283:
				  Name = LIT(L"onryo");
				  break;
			  case 2707640:
				  Name = LIT(L"pyramid");
				  break;
			//	Name = LIT(L"8");
			//	break;
			//case 804980:
			//	Name = LIT(L"9");
			//	break;
			case 487045:
				Name = LIT(L"trapper");
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
