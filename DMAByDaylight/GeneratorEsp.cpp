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
        if (entity->GetActorRole() != EActorRole::EActorRole_Generator)
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

        // Get generator completion percentage
        int percent = std::floor(100 * entity->GetGeneratorPercentFinish());

        // Skip drawing ESP if the generator is 100% completed
        if (percent >= 100) {
            continue;
        }

        // Format the percentage string
        std::wstring wpercent = std::to_wstring(percent) + L"%";

        // Set color based on percentage
        if (percent <= 39)
            config.TextColour = Colour(161, 229, 144); // green
        else if (percent <= 69)
        {
            config.TextColour = Colour(255, 255, 153); // yellow
            wpercent = L"❗️" + std::to_wstring(percent) + L"%❗️";
        }
        else
        {
            config.TextColour = Colour(255, 0, 0); // Bright Red
            wpercent = L"⚠️" + std::to_wstring(percent) + L"%⚠️";
        }

        // Increase font size for percentage
        float percentageFontSize = config.GenESPFontSize * 3.0f; // Increase font size by 50%

        DrawText(screenpos.x, screenpos.y, wpercent, "Verdana", percentageFontSize, config.TextColour, CentreCentre);
    }
}
