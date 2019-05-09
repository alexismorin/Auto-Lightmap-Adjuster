// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AutoLightmapAdjuster.h"
#include "AutoLightmapAdjusterStyle.h"
#include "AutoLightmapAdjusterCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EngineUtils.h"
#include "Object.h"

#include "LevelEditor.h"

static const FName AutoLightmapAdjusterTabName("AutoLightmapAdjuster");

#define LOCTEXT_NAMESPACE "FAutoLightmapAdjusterModule"

void FAutoLightmapAdjusterModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAutoLightmapAdjusterStyle::Initialize();
	FAutoLightmapAdjusterStyle::ReloadTextures();

	FAutoLightmapAdjusterCommands::Register();
	


	PluginCommandsLow = MakeShareable(new FUICommandList);

	PluginCommandsLow->MapAction(
		FAutoLightmapAdjusterCommands::Get().PluginActionLow,
		FExecuteAction::CreateRaw(this, &FAutoLightmapAdjusterModule::generateLow),
		FCanExecuteAction());

	PluginCommandsMedium = MakeShareable(new FUICommandList);

	PluginCommandsMedium->MapAction(
		FAutoLightmapAdjusterCommands::Get().PluginActionMedium,
		FExecuteAction::CreateRaw(this, &FAutoLightmapAdjusterModule::generateMedium),
		FCanExecuteAction());

	PluginCommandsHigh = MakeShareable(new FUICommandList);

	PluginCommandsHigh->MapAction(
		FAutoLightmapAdjusterCommands::Get().PluginActionHigh,
		FExecuteAction::CreateRaw(this, &FAutoLightmapAdjusterModule::generateHigh),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommandsLow, FMenuExtensionDelegate::CreateRaw(this, &FAutoLightmapAdjusterModule::AddMenuLowExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommandsMedium, FMenuExtensionDelegate::CreateRaw(this, &FAutoLightmapAdjusterModule::AddMenuMediumExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommandsHigh, FMenuExtensionDelegate::CreateRaw(this, &FAutoLightmapAdjusterModule::AddMenuHighExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	
}

void FAutoLightmapAdjusterModule::ShutdownModule()
{
	FAutoLightmapAdjusterStyle::Shutdown();
	FAutoLightmapAdjusterCommands::Unregister();
}


void FAutoLightmapAdjusterModule::generateLow()
{
	for (TObjectIterator<UStaticMeshComponent> Itr; Itr; ++Itr)
	{
		UStaticMeshComponent *component = *Itr;
		int adjustedComponentSize = component->CalcBounds(component->GetComponentTransform()).SphereRadius;
		component->bOverrideLightMapRes = true;
		component->OverriddenLightMapRes = adjustedComponentSize*0.25;
		FAutoLightmapAdjusterCommands::Register();
	}

}

void FAutoLightmapAdjusterModule::generateMedium()
{
	for (TObjectIterator<UStaticMeshComponent> Itr; Itr; ++Itr)
	{
		UStaticMeshComponent *component = *Itr;
		int adjustedComponentSize = component->CalcBounds(component->GetComponentTransform()).SphereRadius;
		component->bOverrideLightMapRes = true;
		component->OverriddenLightMapRes = adjustedComponentSize*0.5;
		FAutoLightmapAdjusterCommands::Register();
	}

}

void FAutoLightmapAdjusterModule::generateHigh()
{
	for (TObjectIterator<UStaticMeshComponent> Itr; Itr; ++Itr)
	{
		UStaticMeshComponent *component = *Itr;
		int adjustedComponentSize = component->CalcBounds(component->GetComponentTransform()).SphereRadius;
		component->bOverrideLightMapRes = true;
		component->OverriddenLightMapRes = adjustedComponentSize*1;
		FAutoLightmapAdjusterCommands::Register();
	}

}

void FAutoLightmapAdjusterModule::AddMenuLowExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAutoLightmapAdjusterCommands::Get().PluginActionLow);
}

void FAutoLightmapAdjusterModule::AddMenuMediumExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAutoLightmapAdjusterCommands::Get().PluginActionMedium);
}

void FAutoLightmapAdjusterModule::AddMenuHighExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAutoLightmapAdjusterCommands::Get().PluginActionHigh);
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAutoLightmapAdjusterModule, AutoLightmapAdjuster)