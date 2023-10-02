// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    playerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (playerController) 
    {
        FHitResult hit;

        playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit);

        rotateTurretMesh(hit.ImpactPoint);
    }

}

APlayerController* ATank::getPlayerController() const
{
    return playerController;
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true);

    SetActorTickEnabled(false);
    
    bAlive = false;
}

void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);

    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::fire);
    
    PlayerInputComponent->BindAction(TEXT("MouceX"), EInputEvent::IE_Pressed, this, &ATank::fire);
}

void ATank::MoveForward(float Value)
{
   float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
   
    FVector move = FVector(Value * DeltaTime * Speed, 0, 0);

    AActor::AddActorLocalOffset(move, true);
}

void ATank::Turn(float Value)
{
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    FRotator DeltaRotation = FRotator(0, Value * DeltaTime * TurnRate, 0);

    AddActorLocalRotation(DeltaRotation, true);
}