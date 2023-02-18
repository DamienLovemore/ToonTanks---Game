// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
    //Must have because it is a override
    Super::BeginPlay();

    //Allows tick function to work
    this->PrimaryActorTick.bCanEverTick = true;

    //Gets a reference to the player
    //(Since we only have one, it will always be zero)
    this->Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    //Sets a timer to run in this world timer manager.
    //(The last argument is for the timer to loop, and not just call once)
    this->GetWorldTimerManager().SetTimer(this->FireRateTimerHandle, this, &ATower::CheckFireCondition, this->FireRate, true);
}

//Verifies if the player pawn is within range
bool ATower::IsTankInRange(ATank* PlayerTank) const
{
    bool InRange = false;

    //Verifies if there is a reference to the player
    //(Not null)
    if (this->Tank)
    {
        //Calculates the distance between the player and this object
        float Distance = FVector::Dist(this->GetActorLocation(), this->Tank->GetActorLocation());

        //If the player is within range, rotate to face it
        if (Distance <= this->FireRange)
        {
            InRange = true;
        }
    }

    return InRange;
}

//Rotates the turrets to face the player if it is
//in range
void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (this->IsTankInRange(this->Tank))  
        this->RotateTurret(this->Tank->GetActorLocation());
}

//Fire at the player if in range, once every 2 seconds
void ATower::CheckFireCondition()
{
    if (this->IsTankInRange(this->Tank))
        this->Fire();
}
