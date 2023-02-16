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

private:
	//Keeps the object and the camera connected, separeted by a distance
	UPROPERTY(VisibleAnywhere, Category = "Camera Control")
	class USpringArmComponent* SpringArm;
	//The camera that renders the player view
	UPROPERTY(VisibleAnywhere, Category = "Camera Control")
	class UCameraComponent* FollowCamera;
};
