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
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAutoLightmapAdjusterStyle::Initialize();
	FAutoLightmapAdjusterStyle::ReloadTextures();

	FAutoLightmapAdjusterCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAutoLightmapAdjusterCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FAutoLightmapAdjusterModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FAutoLightmapAdjusterModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FAutoLightmapAdjusterModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FAutoLightmapAdjusterModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FAutoLightmapAdjusterStyle::Shutdown();

	FAutoLightmapAdjusterCommands::Unregister();
}


void FAutoLightmapAdjusterModule::PluginButtonClicked()
{
	for (TObjectIterator<UStaticMeshComponent> Itr; Itr; ++Itr)
	{
		// Access the subclass instance with the * or -> operators.
		UStaticMeshComponent *Component = *Itr;
		Component->bOverrideLightMapRes = true;
		Component->OverriddenLightMapRes = 1024;
		PostEditChangeProperty();
	//	FPropertyChangedEvent evt(nullptr);
	//	Component->PostEditChangeProperty(evt);

	//	UE_LOG(LogTemp, Warning, TEXT(to Component->GetLocalBounds));
	}

	// Put your "OnButtonClicked" stuff here
	//FText DialogText = FText::Format(
	//						LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
	//						FText::FromString(TEXT("FAutoLightmapAdjusterModule::PluginButtonClicked()")),
	//						FText::FromString(TEXT("AutoLightmapAdjuster.cpp"))
	//				   );
	//FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FAutoLightmapAdjusterModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAutoLightmapAdjusterCommands::Get().PluginAction);
}

void FAutoLightmapAdjusterModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FAutoLightmapAdjusterCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAutoLightmapAdjusterModule, AutoLightmapAdjuster)