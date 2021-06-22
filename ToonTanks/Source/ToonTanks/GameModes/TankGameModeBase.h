// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APawnTurret;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	APawnTank* PlayerTank;
	int32 TargetTurrets = 0;

	int32 GetTargetTurretCount();
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintIMplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintIMplementableEvent)
	void GameOver(bool PlayerWon);
};
