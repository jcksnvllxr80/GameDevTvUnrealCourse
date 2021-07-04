// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

 void AShooterAIController::BeginPlay()
{
	 Super::BeginPlay();
	 PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	 if(PlayerPawn)
	 {
		 SetFocus(PlayerPawn);
		 
	 }
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// always move to actor with an acceptance radius of 200cm (2 meters)
	MoveToActor(PlayerPawn, 200);

}