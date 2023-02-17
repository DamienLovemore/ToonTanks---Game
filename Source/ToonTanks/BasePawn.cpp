// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

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
