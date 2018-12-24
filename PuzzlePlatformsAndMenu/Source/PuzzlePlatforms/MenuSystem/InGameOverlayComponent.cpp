// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameOverlayComponent.h"
#include "GameFramework/Actor.h"
#include "GameMenu.h"
#include "GameFramework/Character.h"

#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UInGameOverlayComponent::UInGameOverlayComponent(const FObjectInitializer &ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	ConstructorHelpers::FClassFinder<UUserWidget> GameMenuBPClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));
	if(!ensure(GameMenuBPClass.Class != nullptr)) { return; }
	GameMenuClass = GameMenuBPClass.Class;


	// Gives Unique ID Tag to this component
	// if(!ensure(GetOwner() != nullptr)) { return; }
	// this->ComponentTags.Add(FName(*FString::Printf(TEXT("Parent: %s"), *GetOwner()->GetName())));

	// Tag:	(FName(*FString::Printf(TEXT("Parent: %s"), *GetOwner()->GetName())))

	// TODO Find correct component in array using Tag
	// TODO Find correct tag to use based on parent Character
}


// Called when the game starts
void UInGameOverlayComponent::BeginPlay()
{
	Super::BeginPlay();


	auto Owner = GetOwner();
	if(!ensure(Owner != nullptr)) { return; }
	ACharacter* OwnerAsCharacter = Cast<ACharacter>(Owner);
	if(!ensure(OwnerAsCharacter != nullptr)) { return; }
	OwnerController = Cast<APlayerController>(OwnerAsCharacter->GetController());
	if(!ensure(OwnerController != nullptr)) { return; }

	OwnerController->InputComponent->BindAction("Menu", EInputEvent::IE_Pressed, this, &UInGameOverlayComponent::OpenMenu);
	GameMenu = CreateWidget<UGameMenu>(OwnerController, GameMenuClass);
	bMenuActive = false;

	// UInGameOverlayComponent* InGameOverlayComponent = GameMenu->AddOverlayComponent(this); // TODO Change this into a TArray addition, otherwise the host crashes when trying to access the gamemenu after someone has joined.
}

void UInGameOverlayComponent::OpenMenu()
{

	if(!ensure(OwnerController != nullptr)) { return; }
	if(bMenuActive)
	{
		GameMenu->RemoveFromViewport();
		FInputModeGameOnly GameSetup;
		OwnerController->SetInputMode(GameSetup);
		OwnerController->GetPawn()->EnableInput(OwnerController);
		bMenuActive = false;
	}
	else
	{
		GameMenu->AddToViewport();
		FInputModeGameAndUI UISetup;
		OwnerController->SetInputMode(UISetup);
		UISetup.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		UISetup.SetWidgetToFocus(GameMenu->TakeWidget());
		OwnerController->GetPawn()->DisableInput(OwnerController);
		bMenuActive = true;
	}
	OwnerController->bShowMouseCursor = bMenuActive;
}

