// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
  Super::BeginPlay();

  GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

  PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (!(PlayerPawn && PlayerInFireRange()))
  {
	  return;
  }
  RotateTurrent(PlayerPawn->GetActorLocation());
}

bool APawnTurret::PlayerInFireRange() const
{
	return ReturnDistanceToPlayer() <= FireRange;
}

void APawnTurret::CheckFireCondition() const
{
	if (!PlayerPawn)
	{
		return;
	}

	if (PlayerInFireRange())
	{
		Fire();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Fire condition checked."));
}

float APawnTurret::ReturnDistanceToPlayer() const
{
	if (!PlayerPawn)
	{
		return 0.f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}