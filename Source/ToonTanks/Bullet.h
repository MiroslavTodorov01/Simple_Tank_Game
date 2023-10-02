// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TOONTANKS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void onHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	float getDamage();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* projectile;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	class UProjectileMovementComponent* moveComponent;
	
	UPROPERTY(EditDefaultsOnly)
	float damage;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* partical;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* particleComponent;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* hitSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* launchSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> hitShake;
};
