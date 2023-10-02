// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePown.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePown
{
	GENERATED_BODY()
	
public:

	ATurret();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
// public:
// 	UFUNCTION(BlueprintCallable)
// 	void tickTest(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank* tank;	
};
