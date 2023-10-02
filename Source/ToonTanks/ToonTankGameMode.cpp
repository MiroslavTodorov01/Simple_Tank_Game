// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankPlayerController.h"

void AToonTankGameMode::ActorDied(AActor* actor)
{
    ATank *tank = Cast<ATank>(actor);

    ATower *tower = Cast<ATower>(actor);

    if (tank) 
    {
        tank->HandleDestruction();
        if (playerController) 
        {
            playerController->SetActorState(false);

        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Player controller null"));
        }

        GameOver(false);
    }
    else if (tower) 
    {
        tower->HandleDestruction();

        towersCount--;

        if (towersCount == 0) 
        {
            GameOver(true);
        }
    }
}

void AToonTankGameMode::BeginPlay() 
{
    Super::BeginPlay();

    GameHandleStart();
}

void AToonTankGameMode::GameHandleStart()
{
    towersCount = getTowersCount();

    playerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (playerController) 
    {
        playerController->SetActorState(false);

    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("Player controller null!!"));
    }

    FTimerHandle timeHandle;

    FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(playerController, &AToonTankPlayerController::SetActorState, true);

    GetWorldTimerManager().SetTimer(timeHandle, timerDelegate, timeToStart, false);
}

int32 AToonTankGameMode::getTowersCount()
{   
    TArray<AActor*> towers;

    auto towerClass = ATower::StaticClass();

    UGameplayStatics::GetAllActorsOfClass(this, towerClass, towers);

    return towers.Num();
}