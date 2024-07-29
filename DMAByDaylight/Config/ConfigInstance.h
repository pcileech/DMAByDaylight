#pragma once
#include "Pch.h"
#include "PlayerConfig.h"
#include "MiscConfig.h"
#include "TokenConfig.h"
#include "WindowConfig.h"
#include "Overlay.h"
#include "DebugAndDevConfig.h"
class ConfigInstances
{
public:
	PlayerConfig Survivor = PlayerConfig(LIT("Survivor"));
	PlayerConfig Killer = PlayerConfig(LIT("Killer"));
	OverlayConfig Overlay = OverlayConfig(LIT("Overlay"));
	MiscConfig GenESP = MiscConfig(LIT("Generator"));
	DebugAndDevConfig DebugESP = DebugAndDevConfig(LIT("Debug"));
	TokenConfig TokenESP = TokenConfig(LIT("Token"));
	WindowConfig WindowESP = WindowConfig(LIT("Window"));

	json ToJson()
	{
		json jsoned;
		jsoned.merge_patch(Survivor.ToJson());
		jsoned.merge_patch(GenESP.ToJson());
		jsoned.merge_patch(DebugESP.ToJson());
		jsoned.merge_patch(TokenESP.ToJson());
		jsoned.merge_patch(Overlay.ToJson());
		jsoned.merge_patch(Killer.ToJson());
		jsoned.merge_patch(WindowESP.ToJson());
		return jsoned;
	}

	void FromJson(json jsoned)
	{
		Survivor.FromJson(jsoned);
		GenESP.FromJson(jsoned);
		DebugESP.FromJson(jsoned);
		TokenESP.FromJson(jsoned);
		Overlay.FromJson(jsoned);
		Killer.FromJson(jsoned);
		WindowESP.FromJson(jsoned);
	}
};