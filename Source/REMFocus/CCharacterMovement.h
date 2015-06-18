// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CCharacterMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REMFOCUS_API UCCharacterMovement : public UActorComponent
{
	GENERATED_BODY()

private:

	FVector RotationInput, CurrentRot;
	FVector2D MovementInput;
	FVector2D CameraInput;
	UPROPERTY(EditAnywhere, Category = "Movement") float speed;
	UPROPERTY(EditAnywhere, Category = "Movement") float rotSpeed;
	ACharacter *actor;

public:
	UCCharacterMovement();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HandleVerticalAxis(float v);
	void HandleHorizontalAxis(float v);
	void HandleMouseX(float v);
	void HandleMouseY(float v);
};