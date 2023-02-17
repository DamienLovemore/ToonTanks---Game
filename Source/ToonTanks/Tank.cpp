// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Connector"));
    this->SpringArm->SetupAttachment(this->RootComponent);

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
    //Verify if the user input is being listened
    //UE_LOG(LogTemp, Display, TEXT("MoveFoward Axis Value: %f"), Value);

    //Creates a vector (x,y,z) and assign zero
    //to all its values.(FVector::ZeroVector also
    //works)
    FVector DeltaLocation = FVector(0.0f);
    //Returns the DeltaTime passed in the world of that object
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    //X is the movement in the front and back
    //(Multiply by speed and DeltaTime to adjust its movement
    //speed and make it framerate independet)
    DeltaLocation.X = Value * this->Speed * DeltaTime;

    //Move this character location by the FVector
    //offset, considering its local rotation
    this->AddActorLocalOffset(DeltaLocation);    
}