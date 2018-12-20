// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

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

//
//void UGameMenu::SetMenuInterface(IMenuInterface * MenuInterface)
//{
//	this->MenuInterface = MenuInterface;
//}

void UGameMenu::ReturnToGame()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) { return; }

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController != nullptr)) { return; }

	FInputModeGameOnly InputModeData;

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UGameMenu::ReturnToMainMenu()
{
	//Open Main menu level

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) { return; }
	UGameplayStatics::OpenLevel(World, (FName("/Game/MenuSystem/MainMenu")));
}
