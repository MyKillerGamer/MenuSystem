// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InGameOverlayComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEPLATFORMS_API UInGameOverlayComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInGameOverlayComponent(const FObjectInitializer &ObjectInitializer);

	bool bMenuActive;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	

	class APlayerController* OwnerController;

	UFUNCTION()
	void OpenMenu();


	TSubclassOf<class UUserWidget> GameMenuClass;

	class UGameMenu* GameMenu;
};
