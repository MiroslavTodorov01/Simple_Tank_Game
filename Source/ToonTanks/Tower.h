// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePown.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePown
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class ATank* tank;

	UPROPERTY(EditAnywhere)
	float fireRange;

	FTimerHandle fireRateTimerHandle;

	UPROPERTY(EditAnywhere)
	float FireRate;

	void checkFireCondition();

	bool ifTankIsInRange();
};
