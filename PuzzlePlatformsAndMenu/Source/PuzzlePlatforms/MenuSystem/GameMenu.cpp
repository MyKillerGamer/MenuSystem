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

	if(!ensure(PushToMainMenuButton != nullptr)) { return false; }
	PushToMainMenuButton->OnClicked.AddDynamic(this, &UGameMenu::ReturnToMainMenu);

	/*
	if(!ensure(CancelButton != nullptr)) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UGameMenu::ReturnToGame);
	*/

	return true;
}

/*
UInGameOverlayComponent* UGameMenu::AddOverlayComponent(UInGameOverlayComponent* OverlayComponent)
{
	/*
	OverlayComponents.Add(OverlayComponent);
	UInGameOverlayComponent* ThisComponent = OverlayComponents.FindLast;
	UE_LOG(LogTemp, Warning, TEXT("Added overlay component: %s"), *ThisComponent->GetName());
	return ThisComponent;
	return OverlayComponent;
}*/

void UGameMenu::ReturnToGame()
{
	// Effectively Unused
	// Implement ReturnToGameFromCorrectInstance to work with dynamic delegate.

	/*
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) { return; }

	PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController != nullptr)) { return; }
	*/

}

void UGameMenu::ReturnToMainMenu()
{
	//Open Main menu level

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) { return; }
	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}
