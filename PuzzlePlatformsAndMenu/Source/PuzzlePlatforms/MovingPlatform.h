// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:

	AMovingPlatform();

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float Speed = 20;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true), Category = "Gameplay")
	FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	int ActiveTriggers = 1;
};