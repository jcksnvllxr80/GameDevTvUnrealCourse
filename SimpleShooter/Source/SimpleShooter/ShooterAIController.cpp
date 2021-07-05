// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

 void AShooterAIController::BeginPlay()
{
	 Super::BeginPlay();
	 PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	 if (AIBehavior)
	 {
		 RunBehaviorTree(AIBehavior);
		 GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	 }
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// always move to actor with an acceptance radius of 200cm (2 meters)
	
	if (PlayerPawn)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
			GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation")));
		}
		else
		{
			GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		}
	}

}