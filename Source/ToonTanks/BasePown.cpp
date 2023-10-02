// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePown.h"
#include "Components/CapsuleComponent.h"
// #include "Components/SceneComponent.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePown::ABasePown()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(capsuleComp);

	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower Mesh"));
	TowerMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TowerMesh);
}

// Called every frame
void ABasePown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePown::HandleDestruction()
{
	// sound, dead animation

	if (!dethAnimation) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Deth Animation null!"));
		return;
	}
	else if (!dethSound) 
	{
		UE_LOG(LogTemp, Warning, TEXT("deth sound null"));
		return;
	}

	UGameplayStatics::SpawnSoundAtLocation(this, dethSound, GetActorLocation());

	UGameplayStatics::SpawnEmitterAtLocation(this, dethAnimation, GetActorLocation(), GetActorRotation());

	if (destroyShake) 
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(destroyShake);
	}
	
}

void ABasePown::rotateTurretMesh(FVector &locationOfTarget)
{	
	//DrawDebugSphere(GetWorld(), locationOfTarget, 20, 10, FColor::Blue);

	FVector toTarget = locationOfTarget - GetActorLocation();

	FRotator rotation = FRotator(0.f, toTarget.Rotation().Yaw, 0.f);

	TowerMesh->SetWorldRotation(
		FMath::RInterpTo(TowerMesh->GetComponentRotation(), rotation, GetWorld()->GetDeltaSeconds(), 5), true);
}

void ABasePown::fire() 
{
   // DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 25.f, 10, FColor::Red, false, 2);

	if (bullet == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("projectile null!"));
		return;
	}

	FVector location = ProjectileSpawnPoint->GetComponentLocation();

	FRotator rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto projectile = GetWorld()->SpawnActor<ABullet>(bullet ,location, rotation);

	projectile->SetOwner(this);
}