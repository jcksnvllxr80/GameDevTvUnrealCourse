// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		UE_LOG(LogTemp, Display, TEXT("The Pawn, %s, was killed."), *PawnKilled->GetName())
		PlayerController->GameHasEnded(nullptr, false);
	}
}
