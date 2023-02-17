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
	//Allos to get and set variable in Blueprints visual code
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 VisibleAnywhereInt = 12;

	//It is visible and editable in the Unreal Editor
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 EditAnywhereInt = 22;

	//Can only be visible if it is a instance
	//(placed in the world)
	UPROPERTY(VisibleInstanceOnly)
	int32 VisibleInstanceOnlyInt = 11;

	//Can only be visible in the defaults editor
	//(Double-click BP on Content Drawer)
	UPROPERTY(VisibleDefaultsOnly)
	int32 VisibleDefaultsOnlyInt = 5;

	UPROPERTY(EditDefaultsOnly)
	int32 EditDefaultsOnlyInt = 9;

	UPROPERTY(EditInstanceOnly)
	int32 EditInstanceOnlyInt = 14;
	
private:
	//Forward declare a variable to make header file smaller
	UPROPERTY(VisibleAnywhere, Category = "Pawn Structure", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))	
	class UCapsuleComponent* CapsuleComp;
	//StaticMesh are used to visually render something
	UPROPERTY(VisibleAnywhere, Category = "Pawn Structure", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, Category = "Pawn Structure", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Projectiles", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	//Allows Blueprint access from private variables.
	//(Still encapsulated in the C++ side)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "20\% Cooler", meta = (AllowPrivateAccess = "true"))
	int32 PrivateVisibleAnywhereInt = 21;

	//Category is used to put variables into their own separate categories
	//(The \ is used to escape characters)
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "20\% Cooler", meta = (AllowPrivateAccess = "true"))
	int32 PrivateEditAnywhereInt = 21;
};
