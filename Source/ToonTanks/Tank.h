// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:	
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Keeps the object and the camera connected, separeted by a distance
	UPROPERTY(VisibleAnywhere, Category = "Camera Control")
	class USpringArmComponent* SpringArm;
	//The camera that renders the player view
	UPROPERTY(VisibleAnywhere, Category = "Camera Control")
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float Speed = 489;
	UPROPERTY(EditAnywhere, Category= "Player Movement")
	float TurnRate = 90;

	//The controller is what posses the pawn (player)
	APlayerController* PlayerControllerRef;

	void Move(float Value);
	void Turn(float Value);
};
