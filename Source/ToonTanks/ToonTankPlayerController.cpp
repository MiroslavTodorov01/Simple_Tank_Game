// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankPlayerController.h"

void AToonTankPlayerController::SetActorState(bool bPlayerStatus)
{
    if (bPlayerStatus) 
    {
        GetPawn()->EnableInput(this);
    }
    else 
    {
        GetPawn()->DisableInput(this);
    }
    
    bShowMouseCursor = bPlayerStatus;
}