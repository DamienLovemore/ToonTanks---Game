// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	this->PrimaryActorTick.bCanEverTick = true;

	//Create a component (not a actor) of that type and with that name.
	//Can only be used in the Constructor
	this->CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	//Changes the RootComponent to be the new created component
	this->RootComponent = this->CapsuleComp;

	this->BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	//Attach the component to the wanted object
	this->BaseMesh->SetupAttachment(this->CapsuleComp);

	this->TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	this->TurretMesh->SetupAttachment(this->BaseMesh);

	this->ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectiles Spawn"));
	this->ProjectileSpawnPoint->SetupAttachment(this->TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	//LookAtTarget is the destination, GetComponentLocation is
	//where we are now
	FVector ToTarget = LookAtTarget - this->TurretMesh->GetComponentLocation();

	//Calculates the right rotation based on the distance
	//between the points
	FRotator LookAtRotation = ToTarget.Rotation();
	//Because we only want to rotate around (z axis = yaw)
	//we do not rotate in the others axis
	LookAtRotation.Pitch = 0;
	LookAtRotation.Roll = 0;

	//Used to make framerate independent movements and
	//rotations
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	//Calculate a intermediate rotation between current and target
	//rotation, so it does not rotate immediately to the target
	FRotator SmoothRotation = FMath::RInterpTo(this->TurretMesh->GetComponentRotation(), LookAtRotation, DeltaTime, 25);

	//Use SetWorldRotation instead of adding local rotation
	//because the calculation we do in ToTarget is in the
	//world scope, not local scope.
	this->TurretMesh->SetWorldRotation(SmoothRotation);
}

void ABasePawn::Fire()
{
	//The start point of the bullet
	FVector ProjectileSpawnPointLocation = this->ProjectileSpawnPoint->GetComponentLocation();
	//The rotation that the bullet should have
	//(Rotate with the turret)
	FRotator ProjectileSpawnPointRotation = this->ProjectileSpawnPoint->GetComponentRotation();

	//Visual indicator of where the bullet is
	//being shoot from
	//DrawDebugSphere(this->GetWorld(), ProjectileSpawnPointLocation, 25, 12, FColor::Red, false, 3);

	//auto lets the editor to figure out the correct type
	auto Projectile = this->GetWorld()->SpawnActor<AProjectile>(this->ProjectileClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	//Makes to sure to assign this bullet to this object,
	//so we can know later from which it came
	Projectile->SetOwner(this);
}
