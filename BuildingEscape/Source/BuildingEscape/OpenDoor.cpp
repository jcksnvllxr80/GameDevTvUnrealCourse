// Copyright Aaron Watkins 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	float OpenDoorYaw = -90.f;
	FRotator CurrentRoatation = GetOwner()->GetActorRotation();
	FRotator OpenDoor = {0.f, OpenDoorYaw, 0.f};
	// FRotator OpenDoor(0.f, OpenDoorYaw, 0.f);
	GetOwner()->SetActorRotation(OpenDoor);
	// GetOwner()->SetActorRotation(CurrentRoatation.Add(0.f, OpenDoorYaw, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

