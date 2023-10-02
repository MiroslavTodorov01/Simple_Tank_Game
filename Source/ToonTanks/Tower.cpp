// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (ifTankIsInRange()) 
    {
         FVector tankLocation = tank->GetActorLocation();

        rotateTurretMesh(tankLocation);
    }

}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::checkFireCondition, FireRate, true);
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::checkFireCondition()
{

    if (tank == nullptr) 
    {
        return;
    }

    if (ifTankIsInRange() && tank->bAlive) 
    {
        Super::fire();
    }
}

bool ATower::ifTankIsInRange()
{
    if (!tank) 
    {
        UE_LOG(LogTemp, Warning, TEXT("tank null!"));
        return false;
    }

    FVector tankLocation = tank->GetActorLocation();

    float distance = FVector::Dist(GetActorLocation(), tankLocation);

    if (distance <= fireRange) 
    {
        return true;
    }

    return false;
}