// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;




class FAutoLightmapAdjusterModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	void generateLow();
	void generateMedium();
	void generateHigh();
	
private:

	void AddMenuLowExtension(FMenuBuilder& Builder);
	void AddMenuMediumExtension(FMenuBuilder& Builder);
	void AddMenuHighExtension(FMenuBuilder& Builder);

private:
	TSharedPtr<class FUICommandList> PluginCommandsLow;
	TSharedPtr<class FUICommandList> PluginCommandsMedium;
	TSharedPtr<class FUICommandList> PluginCommandsHigh;
};
