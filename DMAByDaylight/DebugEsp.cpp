#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "DebugAndDevConfig.h"
#include "ConfigUtilities.h"

std::shared_ptr<CheatFunction> UpdateDebugs = std::make_shared<CheatFunction>(10, [] {
	if (!EngineInstance)
		return;
	EngineInstance->UpdateDebugs();
	});

void DrawDebugEsp()
{
	if (!EngineInstance)
		return;

	for (auto entity : EngineInstance->GetActors())
	{
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;
		DebugAndDevConfig config = Configs.DebugESP;

		Vector2 screenpos = Camera::WorldToScreen(EngineInstance->GetCameraCache().POV, entity->GetPosition());
		if (screenpos == Vector2::Zero())
			continue;
		//Vector3 campos = Vector3(EngineInstance->GetCameraCache().POV.Location.X, EngineInstance->GetCameraCache().POV.Location.Y, EngineInstance->GetCameraCache().POV.Location.Z);

		// 获取全局ID信息
		std::wstring wdistance = config.DebugESPDistance ? L"[ID: " + entity->GetActorId() + L"]"  : L"";
		std::wstring name = config.DebugESPEnabled ? entity->GetName() : L"";

		DrawText(screenpos.x, screenpos.y, name + wdistance, "Verdana", config.DebugESPFontSize, config.TextColour, CentreCentre);
	}

}