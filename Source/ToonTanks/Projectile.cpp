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
	
	//Bind the object event to the function that
	//should respond to it
	this->ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Test if hit event is being trigger
	UE_LOG(LogTemp, Warning, TEXT("OnHit event triggered"));

	//Parameters names debugging
	UE_LOG(LogTemp, Display, TEXT("HittedComponent: %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Display, TEXT("OtherActor: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Display, TEXT("OtherComp: %s"), *OtherComp->GetName());
}