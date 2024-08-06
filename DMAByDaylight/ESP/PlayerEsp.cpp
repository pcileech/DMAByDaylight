#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "PlayerEsp.h"
#include "ConfigUtilities.h"

std::shared_ptr<CheatFunction> UpdatePlayers = std::make_shared<CheatFunction>(10, [] {
    if (!EngineInstance)
        return;
    EngineInstance->UpdatePlayers();
    });

void DrawPlayerEsp()
{
    if (!EngineInstance)
        return;

    for (auto entity : EngineInstance->GetActors())
    {
        if (entity->GetActorRole() != EActorRole::EActorRole_Players &&
            entity->GetActorRole() != EActorRole::EActorRole_Hatch &&
            entity->GetActorRole() != EActorRole::EActorRole_Gate &&
            entity->GetActorRole() != EActorRole::EActorRole_Tokem &&
            entity->GetActorRole() != EActorRole::EActorRole_Pallet &&
            entity->GetActorRole() != EActorRole::EActorRole_MeatHook &&
            entity->GetActorRole() != EActorRole::EActorRole_Window) // Include EActorRole_Window
        {
            continue;
        }
        if (entity->GetPosition() == Vector3(0, 0, 0))
            continue;

        PlayerConfig config = Configs.Survivor;
        if (entity->GetPlayerRole() == EPlayerRole::EPlayerRole__VE_Slasher)
            config = Configs.Killer;

        // Set specific colors for different roles
        if (entity->GetActorRole() == EActorRole::EActorRole_Tokem) {
            config.TextColour = Colour(193, 193, 193); // Example: setting color to cyan totem
        }
        if (entity->GetActorRole() == EActorRole::EActorRole_Hatch) {
            config.TextColour = Colour(0, 255, 255); // Example: setting color to cyan hatch
        }
        if (entity->GetActorRole() == EActorRole::EActorRole_Gate) {
            config.TextColour = Colour(11, 98, 97); // Example: setting color to orange gate
        }
        if (entity->GetActorRole() == EActorRole::EActorRole_Window) {
            config.TextColour = Colour(255, 255, 0); // Example: setting color to yellow traps
        }
        if (entity->GetActorRole() == EActorRole::EActorRole_Pallet) {
            config.TextColour = Colour(255, 181, 208); // Example: setting color to pink gen
        }
        if (entity->GetActorRole() == EActorRole::EActorRole_MeatHook) {
            config.TextColour = Colour(255, 165, 80); // Example: setting color to chest color
        }

        Vector2 screenpos = Camera::WorldToScreen(EngineInstance->GetCameraCache().POV, entity->GetPosition());
        if (screenpos == Vector2::Zero())
            continue;
        Vector3 campos = Vector3(EngineInstance->GetCameraCache().POV.Location.X, EngineInstance->GetCameraCache().POV.Location.Y, EngineInstance->GetCameraCache().POV.Location.Z);
        float distance = (Vector3::Distance(campos, entity->GetPosition()) / 39.62f) - 6;
        if (distance < 0)
            continue;

        std::wstring name = config.Name ? entity->GetName() : L"";
        std::wstring wdistance = (config.Distance && entity->GetActorRole() != EActorRole::EActorRole_MeatHook && entity->GetActorRole() != EActorRole::EActorRole_Tokem) ? L"[" + std::to_wstring((int)distance / 2) + L"m]" : L"";
        if (distance > config.MaxDistance)
            continue;

        DrawText(screenpos.x, screenpos.y, name, "Verdana", config.FontSize, config.TextColour, CentreCentre);

        // Draw distance below the player name for all roles except MeatHook and Tokem
        if (config.Distance && entity->GetActorRole() != EActorRole::EActorRole_MeatHook && entity->GetActorRole() != EActorRole::EActorRole_Tokem) {
            DrawText(screenpos.x, screenpos.y + config.FontSize, wdistance, "Verdana", config.FontSize, config.TextColour, CentreCentre);
        }
    }
}
