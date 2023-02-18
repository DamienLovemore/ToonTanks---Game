// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 700;

	//The timer that triggers fire
	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRate = 2;

	//The reference to the player pawn
	class ATank* Tank;

	bool IsTankInRange(ATank* Player) const;
	//The function that verifies if fire should
	//be called, everytime the timer triggers
	void CheckFireCondition();
};
