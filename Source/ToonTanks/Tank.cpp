// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
    this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Connector"));

    //The object that will follow the root must be a child of the camera connector.
    //(Keeps following the other separated by a distance)
    this->FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
    this->FollowCamera->SetupAttachment(this->SpringArm);
}

//Used to bind functions to access mappings
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    //Whenever you override a virtual function it is good for
    //you to use super inside its cpp declaration to avoid bugs
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Bind a axis mapping of that name to our function to handle
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}

void ATank::Move(float Value)
{
    UE_LOG(LogTemp, Display, TEXT("MoveFoward Axis Value: %f"), Value);
}