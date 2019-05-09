// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AutoLightmapAdjusterStyle.h"

class FAutoLightmapAdjusterCommands : public TCommands<FAutoLightmapAdjusterCommands>
{
public:

	FAutoLightmapAdjusterCommands()
		: TCommands<FAutoLightmapAdjusterCommands>(TEXT("AutoLightmapAdjuster"), NSLOCTEXT("Contexts", "AutoLightmapAdjuster", "AutoLightmapAdjuster Plugin"), NAME_None, FAutoLightmapAdjusterStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginActionLow;
	TSharedPtr< FUICommandInfo > PluginActionMedium;
	TSharedPtr< FUICommandInfo > PluginActionHigh;
};
