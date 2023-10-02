// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePown.generated.h"

UCLASS()
class TOONTANKS_API ABasePown : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePown();

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	class UParticleSystem* dethAnimation;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* capsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TowerMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class ABullet> bullet;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* dethSound;

	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<class UCameraShakeBase> destroyShake;

protected:

	void rotateTurretMesh(FVector &locationOfTarget);

	void fire();

	void HandleDestruction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 damage = 25;
};
