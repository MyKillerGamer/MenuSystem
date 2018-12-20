// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(!ensure(MenuBPClass.Class != nullptr)) { return; }
	MenuClass = MenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if(!ensure(MenuClass != nullptr)) { return; }
	
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if(!ensure(Menu != nullptr)) { return; }

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if(!ensure(Engine != nullptr)) { return; }

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) { return; }

	World->ServerTravel("/Game/Dynamic/Levels/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if(!ensure(Engine != nullptr)) { return; }

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController != nullptr)) { return; }

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::Quit()
{
	// Not in use: Causes crashes
	UEngine* Engine = GetEngine();
	if(!ensure(Engine != nullptr)) { return; }

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Quitting"));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController != nullptr)) { return; }

	Quit();
}
