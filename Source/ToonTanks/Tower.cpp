// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
    //Must have because it is a override
    Super::BeginPlay();

    //Allows tick function to work
    this->PrimaryActorTick.bCanEverTick = true;

    //Gets a reference to the player
    //(Since we only have one, it will always be zero)
    this->Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Verifies if there is a reference to the player
    //(Not null)
    if (this->Tank)
    {
        //Calculates the distance between the player and this object
        float Distance = FVector::Dist(this->GetActorLocation(), this->Tank->GetActorLocation());

        //If the player is within range, rotate to face it
        if (Distance <= this->FireRange)
        {
            this->RotateTurret(this->Tank->GetActorLocation());
        }
    }
}
