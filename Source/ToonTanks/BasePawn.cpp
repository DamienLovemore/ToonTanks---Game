// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	//Create a component of that type and with that name.
	//(Also assings it as a child of this object)
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
