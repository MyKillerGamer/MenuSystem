// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "InGameOverlayComponent.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UGameMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	/*UInGameOverlayComponent* AddOverlayComponent(UInGameOverlayComponent* OverlayComponent);*/

protected:

	virtual bool Initialize() override;

	APlayerController* PlayerController;

private:

	/*UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;*/

	UPROPERTY(meta = (BindWidget))
	class UButton* PushToMainMenuButton;

	UFUNCTION()
	void ReturnToGame();

	UFUNCTION()
	void ReturnToMainMenu();


	UPROPERTY()
	TArray<UInGameOverlayComponent*> OverlayComponents;
};
