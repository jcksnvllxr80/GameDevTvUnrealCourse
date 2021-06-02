// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// FString Log = TEXT("Hello, World!");
	// FString* PtrLog = &Log;

	// Log.Len();

	// PtrLog->Len();

	// UE_LOG(LogTemp, Display, TEXT("%s"), **PtrLog);
	// UE_LOG(LogTemp, Display, TEXT("This is a normal log."));
	// UE_LOG(LogTemp, Warning, TEXT("This is a warning log."));
	// UE_LOG(LogTemp, Error, TEXT("This is an error log."));

	UE_LOG(LogTemp, Display, TEXT("WorldPosition componenet attached to object: %s"), *GetOwner()->GetName());
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

