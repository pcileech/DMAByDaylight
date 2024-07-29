#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "MiscConfig.h"
#include "ConfigUtilities.h"

std::shared_ptr<CheatFunction> UpdateGenerators = std::make_shared<CheatFunction>(10, [] {
	if (!EngineInstance)
		return;
	EngineInstance->UpdateGenerators();
	});

void DrawGeneratorEsp()
{
	if (!EngineInstance)
		return;

	for (auto entity : EngineInstance->GetActors())
	{
		if (entity->GetActorRole() != EActorRole::EActorRole_Generator && entity->GetActorRole() != EActorRole::EActorRole_KillerItem)
		{
			continue;
		}
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;
		MiscConfig config = Configs.GenESP;

		Vector2 screenpos = Camera::WorldToScreen(EngineInstance->GetCameraCache().POV, entity->GetPosition());
		if (screenpos == Vector2::Zero())
			continue;
		Vector3 campos = Vector3(EngineInstance->GetCameraCache().POV.Location.X, EngineInstance->GetCameraCache().POV.Location.Y, EngineInstance->GetCameraCache().POV.Location.Z);
		float distance = (Vector3::Distance(campos, entity->GetPosition()) / 39.62f) - 6;
		if (distance < 0 || distance > config.GenESPMaxDistance)
			continue;
		// 获取发电机信息
		int percent = std::floor(100 * entity->GetGeneratorPercentFinish());
		std::wstring wdistance = config.GenESPDistance ? L"[" + std::to_wstring((int)distance/2) + L"m]" + L"[" + std::to_wstring(percent) + L"%]" : L"";
		std::wstring name = config.GenESPEnabled ? entity->GetName() : L"";

		config.TextColour = Colour(218, 112, 214);
		if (entity->GetActorRole() == EActorRole::EActorRole_KillerItem)
		{
			config.TextColour = Colour(250, 20, 20);
		}
		DrawText(screenpos.x, screenpos.y, name + wdistance, "Verdana", config.GenESPFontSize, config.TextColour, CentreCentre);
	}
	
}