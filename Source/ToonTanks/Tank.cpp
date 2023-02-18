// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Connector"));
    this->SpringArm->SetupAttachment(this->RootComponent);

    //The object that will follow the root must be a child of the camera connector.
    //(Keeps following the other separated by a distance)
    this->FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
    this->FollowCamera->SetupAttachment(this->SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    //Because it is a override must have
    Super::BeginPlay();

    //Allows this object to register tick events
    this->PrimaryActorTick.bCanEverTick = true;

    //Gets the controller system used by the player
    //to move the pawn (player char) around
    //Used casting to convert AController to APlayerController
    this->PlayerControllerRef = Cast<APlayerController>(this->GetController());

    //Example of usage of draw debug sphere (Used to show
    //where line trace is hitting for debug purposes)
    //DrawDebugSphere(this->GetWorld(), this->GetActorLocation() + FVector(0,0,200), 100, 20, FColor::Red, true, 30);
}

//Used to bind functions to access mappings
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    //Whenever you override a virtual function it is good for
    //you to use super inside its cpp declaration to avoid bugs
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Bind a axis mapping of that name to our function to handle
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    
    //Bind this action mapping to call Fire when the Fire button is pressed
    //(For released use IE_Released)
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Verifies if the pointer is not null
    //(If we have a controller possesing this pawn)
    if(this->PlayerControllerRef)
    {
        //Stores information about where it hit
        FHitResult HitResult;
        //Do a line trace check with the mouse cursor
        this->PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

        //Visual representation for debugging to see where
        //mouse is pointing
        //-1.f draw every single frame, segments how many lines
        //is used to draw the sphere
        //DrawDebugSphere(this->GetWorld(), HitResult.ImpactPoint, 25, 12, FColor::FromHex("#f7afba"), false, -1.f);

        //Rotate the tank turret in the direction the mouse is facing
        this->RotateTurret(HitResult.ImpactPoint);
    }
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
    //If Sweeping is on it stops moving if it would pass through an object.
    //Generate overlap must be enabled, and collisions to block what it
    //should not pass through.
    this->AddActorLocalOffset(DeltaLocation, true);    
}

void ATank::Turn(float Value)
{
    //FRotation is similar to FVector. But instead
    //of representing location, it represents rotation
    //Pitch - Rotation in the Y axis
    //Yaw - Rotation in the Z axis
    //Roll - Rotation in the X axis
    FRotator DeltaRotation = FRotator::ZeroRotator;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    //Yaw is the movement in the Z axis, it is used to
    //turn the tank around.
    DeltaRotation.Yaw = Value * this->TurnRate * DeltaTime;

    this->AddActorLocalRotation(DeltaRotation, true);   
}