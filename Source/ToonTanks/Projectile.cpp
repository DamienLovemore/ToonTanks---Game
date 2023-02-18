// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	this->RootComponent = this->ProjectileMesh;

	//Creates the component that handles the movement of it
	//in the tick function
	this->MovementHandler = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Handler"));
	//Sets the speed that this object should move
	this->MovementHandler->InitialSpeed = 1300;
	this->MovementHandler->MaxSpeed = 1300;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

