// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	//Visible in unity editor, but not editable
	UPROPERTY(VisibleAnywhere)
	int32 VisibleAnywhereInt = 12;

	//It is visible and editable in the Unreal Editor
	UPROPERTY(EditAnywhere)
	int32 EditAnywhereInt = 22;

	//Can only be visible if it is a instance
	//(placed in the world)
	UPROPERTY(VisibleInstanceOnly)
	int32 VisibleInstanceOnlyInt = 11;

	UPROPERTY(EditAnywhere)
	float Speed = 400;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Forward declare a variable to make header file smaller
	UPROPERTY()	
	class UCapsuleComponent* CapsuleComp;
	//StaticMesh are used to visually render something
	UPROPERTY()
	UStaticMeshComponent* BaseMesh;
	UPROPERTY()
	UStaticMeshComponent* TurretMesh;
	UPROPERTY()
	USceneComponent* ProjectileSpawnPoint;
};
