// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Public/GenericPlatform/GenericPlatformMisc.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	if(!ensure(HostButton != nullptr)) { return false; }
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if(!ensure(JoinRedirectButton != nullptr)) { return false; }
	JoinRedirectButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if(!ensure(CancelJoinButton != nullptr)) { return false; }
	CancelJoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if(!ensure(ConfirmJoinButton != nullptr)) { return false; }
	ConfirmJoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if(!ensure(QuitButton != nullptr)) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) { return; }

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController != nullptr)) { return; }

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) { return; }

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController != nullptr)) { return; }

	FInputModeGameOnly InputModeData;

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;

	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

void UMainMenu::HostServer()
{
	if(MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if(!ensure(IPAddressField != nullptr)) { return; }
	const FString& Address = IPAddressField->GetText().ToString();
	if(MenuInterface != nullptr)
	{
		MenuInterface->Join(Address);
	}
}

void UMainMenu::OpenJoinMenu()
{
	if(!ensure(MenuSwitcher != nullptr)) { return; }
	if(!ensure(JoinMenu != nullptr)) { return; }
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if(!ensure(MenuSwitcher != nullptr)) { return; }
	if(!ensure(MainMenu != nullptr)) { return; }
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGame()
{
	// TODO Remove log and uncomment code, but only for the build version, not for development, and only one implementation
	// FGenericPlatformMisc::RequestExit(false);
	UE_LOG(LogTemp, Warning, TEXT("Attempted to quit."));
	
	/*if(MenuInterface != nullptr)
	{
		// Causes a crash
		MenuInterface->Quit();
	}*/
}
