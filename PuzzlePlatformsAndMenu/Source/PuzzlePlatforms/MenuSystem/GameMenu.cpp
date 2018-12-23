// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "InGameOverlayComponent.h"
#include "GameFramework/Character.h"

bool UGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	if(!ensure(CancelButton != nullptr)) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UGameMenu::ReturnToGame);

	if(!ensure(PushToMainMenuButton != nullptr)) { return false; }
	PushToMainMenuButton->OnClicked.AddDynamic(this, &UGameMenu::ReturnToMainMenu);

	return true;
}

UInGameOverlayComponent* UGameMenu::AddOverlayComponent(UInGameOverlayComponent* OverlayComponent)
{
	OverlayComponents.Add(OverlayComponent);
	UInGameOverlayComponent* ThisComponent = OverlayComponents.FindLast;
	UE_LOG(LogTemp, Warning, TEXT("Added overlay component: %s"), *ThisComponent->GetName());
	return ThisComponent;
}

void UGameMenu::ReturnToGame()
{
	// Implement ReturnToGameFromCorrectInstance to work with dynamic delegate.
}

void UGameMenu::ReturnToMainMenu()
{
	//Open Main menu level

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) { return; }
	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UGameMenu::ReturnToGameFromCorrectInstance(UInGameOverlayComponent* OverlayComponent)
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) { return; }

	PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController != nullptr)) { return; }
/*
	FInputModeGameOnly GameSetup;

	PlayerController->SetInputMode(GameSetup);
	PlayerController->GetPawn()->EnableInput(PlayerController);
	PlayerController->bShowMouseCursor = false;*/

	// Get the name of the parent of the Overlay component.
	// Get the actor that called this function
	// Confirm tags
	// Run from that overlay component

	OverlayComponent->bMenuActive = false;
}
