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


}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* OwningObj = GetOwner();
	FRotator ObjRotation = OwningObj->GetActorRotation();
	UE_LOG(LogTemp, Display, TEXT("%s's rotation is %s"), *OwningObj->GetName(), *ObjRotation.ToString());
	UE_LOG(LogTemp, Display, TEXT("%s's yaw is %f"), *OwningObj->GetName(), TargetYaw);

	float CurrentYaw = ObjRotation.Yaw;
	ObjRotation.Yaw = FMath::Lerp(CurrentYaw, TargetYaw, 0.025f);
	OwningObj->SetActorRotation(ObjRotation);

	// float OpenDoorYaw = -90.f;
	// FRotator CurrentRoatation = GetOwner()->GetActorRotation();
	// FRotator OpenDoor = {0.f, OpenDoorYaw, 0.f};
	// FRotator OpenDoor(0.f, OpenDoorYaw, 0.f);
	// GetOwner()->SetActorRotation(OpenDoor);
	// GetOwner()->SetActorRotation(CurrentRoatation.Add(0.f, OpenDoorYaw, 0.f));
}

