// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UGameMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	// void SetMenuInterface(IMenuInterface * MenuInterface);

	void Setup();

protected:

	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* PushToMainMenuButton;


	UFUNCTION()
	void ReturnToGame();

	UFUNCTION()
	void ReturnToMainMenu();

	// IMenuInterface* MenuInterface;
};
