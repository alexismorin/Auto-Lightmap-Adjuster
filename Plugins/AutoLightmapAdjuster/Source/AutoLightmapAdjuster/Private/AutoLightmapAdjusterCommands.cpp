// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AutoLightmapAdjusterCommands.h"

#define LOCTEXT_NAMESPACE "FAutoLightmapAdjusterModule"

void FAutoLightmapAdjusterCommands::RegisterCommands()
{
	UI_COMMAND(PluginActionLow, "Lightmap Scale - Performance", "Conform scale in lightmap for all static meshes in the scene", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(PluginActionMedium, "Lightmap Scale - Balanced", "Conform scale in lightmap for all static meshes in the scene", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(PluginActionHigh, "Lightmap Scale - Quality", "Conform scale in lightmap for all static meshes in the scene", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
