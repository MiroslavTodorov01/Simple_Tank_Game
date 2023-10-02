// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));

	RootComponent = projectile;

	moveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));

	particleComponent->SetupAttachment(RootComponent);

	moveComponent->MaxSpeed = 2000;
	
	moveComponent->InitialSpeed = 20000;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	projectile->OnComponentHit.AddDynamic(this, &ABullet::onHit);

	if (launchSound) 
	{
		UGameplayStatics::SpawnSoundAtLocation(this, launchSound, GetActorLocation());
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::onHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// UE_LOG(LogTemp, Display, TEXT("%s"), *(HitComp->GetName()));
	// UE_LOG(LogTemp, Display, TEXT("%s"), *(OtherActor->GetActorNameOrLabel()));
	// UE_LOG(LogTemp, Display, TEXT("%s"), *(OtherComp->GetName()));
	// UE_LOG(LogTemp, Display, TEXT("%s"), *(NormalImpulse.ToCompactString()));
	// UE_LOG(LogTemp, Display, TEXT("%s"), *(Hit.GetActor()->GetActorNameOrLabel()));

	//UGameplayStatics::SpawnEmitterAtLocation(this, partical, HitComp->GetComponentLocation(), OtherActor->GetActorRotation());

	UGameplayStatics::SpawnEmitterAtLocation(this, partical, GetActorLocation(), GetActorRotation());

	AController* actorThatShoot = GetOwner()->GetInstigatorController();

	if (actorThatShoot == nullptr) 
	{
		UE_LOG(LogTemp, Display, TEXT("controller null"));
		Destroy();
		return;
	}

	if (!hitSound) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit sound null!"));
		return;
	}

	auto damageType = UDamageType::StaticClass();

	UGameplayStatics::SpawnSoundAtLocation(this, hitSound, GetActorLocation());

	if (hitShake != nullptr) 
	{	
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitShake);
	}

	if (OtherActor && OtherActor != GetOwner()) 
	{
		UGameplayStatics::ApplyDamage(OtherActor, damage, actorThatShoot, this, damageType);
	}

	Destroy();
}

float ABullet::getDamage()
{
	return damage;
}