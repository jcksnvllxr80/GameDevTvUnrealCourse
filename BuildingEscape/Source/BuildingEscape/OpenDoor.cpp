// Copyright Aaron Watkins 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/WorldSettings.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#define OUT 

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
	OwningObj = GetOwner();
	ObjRotation = OwningObj->GetActorRotation();
	CloseYaw = ObjRotation.Yaw;
	OpenYaw += ObjRotation.Yaw;

	ValidatePressurePlate();
	FindAudioComponent();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TotalActorMass() > MassToOpenDoor)
	{
		PlayAudioComponent(DoorOpenedAudioPlayed);
		DoorOpenedAudioPlayed = true;
		DoorClosedAudioPlayed = false;
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorClosedDelay)
	{
		PlayAudioComponent(DoorClosedAudioPlayed);
		DoorClosedAudioPlayed = true;
		DoorOpenedAudioPlayed = false;
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaT)
{
	// UE_LOG(LogTemp, Display, TEXT("%s's rotation is %s"), *OwningObj->GetName(), *ObjRotation.ToString());
	// UE_LOG(LogTemp, Display, TEXT("%s's yaw is %f"), *OwningObj->GetName(), OpenYaw);
	ObjRotation = OwningObj->GetActorRotation();
	OwningObj->SetActorRotation({
		ObjRotation.Pitch, 
		FMath::Lerp(ObjRotation.Yaw, OpenYaw, DeltaT * DoorOpenSpeed), 
		ObjRotation.Roll
	});
}

void UOpenDoor::CloseDoor(float DeltaT)
{
	// UE_LOG(LogTemp, Display, TEXT("%s's rotation is %s"), *OwningObj->GetName(), *ObjRotation.ToString());
	// UE_LOG(LogTemp, Display, TEXT("%s's yaw is %f"), *OwningObj->GetName(), OpenYaw);
	ObjRotation = OwningObj->GetActorRotation();
	OwningObj->SetActorRotation({
		ObjRotation.Pitch, 
		FMath::Lerp(ObjRotation.Yaw, CloseYaw, DeltaT * DoorCloseSpeed), 
		ObjRotation.Roll
	});
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("%s has no audio component to be found."),
			*GetOwner()->GetName()
		);
	}
}

void UOperDoor::ValidatePressurePlate() const
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s's Pressure Plate is not set!"), *OwningObj->GetName());
	}
}

void UOpenDoor::PlayAudioComponent(bool AudioHasAlreadyBeenPlayed) const
{
	if (AudioComponent && !AudioHasAlreadyBeenPlayed)
	{
		UE_LOG(LogTemp, Display, TEXT("Playing door audio."));
		AudioComponent->Play();
	}
}

float UOpenDoor::TotalActorMass() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (PressurePlate)
	{
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);
		for (AActor *OverlappingActor : OverlappingActors)
		{
			TotalMass += OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	return TotalMass;
}
