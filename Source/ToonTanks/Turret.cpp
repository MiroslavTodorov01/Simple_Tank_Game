// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATurret::ATurret()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATurret::BeginPlay() 
{
    Super::BeginPlay();
    
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!tank) 
    {
        UE_LOG(LogTemp, Warning, TEXT("tank null!"));
        return;
    }

    FVector tankLocation = tank->GetActorLocation();

    float distance = FVector::Dist(GetActorLocation(), tankLocation);

    rotateTurretMesh(tankLocation);
}

// void ATurret::tickTest(float DeltaTime)
// {
//     if (!tank) 
//     {
//         UE_LOG(LogTemp, Warning, TEXT("tank null!"));
//         return;
//     }

//     UE_LOG(LogTemp, Display, TEXT("tick"));

//     FVector tankLocation = tank->GetActorLocation();

//     float distance = FVector::Dist(GetActorLocation(), tankLocation);

//     rotateTurretMesh(tankLocation);
// }