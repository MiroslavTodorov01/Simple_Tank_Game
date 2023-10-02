// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

public:

	void ActorDied(AActor* actor);

	int32 getTowersCount();

private:

	class AToonTankPlayerController *playerController;

	void GameHandleStart();

	UPROPERTY(EditAnywhere)
	float timeToStart;

	int32 towersCount;
};
