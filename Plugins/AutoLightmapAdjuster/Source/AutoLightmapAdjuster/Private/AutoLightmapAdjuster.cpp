// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AutoLightmapAdjuster.h"
#include "AutoLightmapAdjusterStyle.h"
#include "AutoLightmapAdjusterCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EngineUtils.h"

#include "LevelEditor.h"

static const FName AutoLightmapAdjusterTabName("AutoLightmapAdjuster");

#define LOCTEXT_NAMESPACE "FAutoLightmapAdjusterModule"

void FAutoLightmapAdjusterModule::StartupModule()
{	
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
		float adjustedComponentSize = component->CalcBounds(component->GetComponentTransform()).BoxExtent.Size();
		component->bOverrideLightMapRes = true;
		float scaleCalculation = 1024.0 / (adjustedComponentSize*0.05);
		int32 IntNumb = (int32)scaleCalculation;
		component->OverriddenLightMapRes = FMath::Clamp(IntNumb, 4, 64);
		FAutoLightmapAdjusterCommands::Register();
	}
}

void FAutoLightmapAdjusterModule::generateMedium()
{
	for (TObjectIterator<UStaticMeshComponent> Itr; Itr; ++Itr)
	{
		UStaticMeshComponent *component = *Itr;
		float adjustedComponentSize = component->CalcBounds(component->GetComponentTransform()).BoxExtent.Size();
		component->bOverrideLightMapRes = true;
		float scaleCalculation = 2048.0 / (adjustedComponentSize*0.05);
		int32 IntNumb = (int32)scaleCalculation;
		component->OverriddenLightMapRes = FMath::Clamp(IntNumb,4, 128) ;
		FAutoLightmapAdjusterCommands::Register();
	}
}

void FAutoLightmapAdjusterModule::generateHigh()
{
	for (TObjectIterator<UStaticMeshComponent> Itr; Itr; ++Itr)
	{
		UStaticMeshComponent *component = *Itr;
		float adjustedComponentSize = component->CalcBounds(component->GetComponentTransform()).BoxExtent.Size();
		component->bOverrideLightMapRes = true;
		float scaleCalculation = 4096.0 / (adjustedComponentSize*0.05);
		int32 IntNumb = (int32)scaleCalculation;
		component->OverriddenLightMapRes = FMath::Clamp(IntNumb, 4, 256);
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