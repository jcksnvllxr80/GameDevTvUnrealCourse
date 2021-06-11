// Copyright Aaron Watkins 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaT);
	void CloseDoor(float DeltaT);
	float TotalActorMass() const;

private:
	UPROPERTY(EditAnywhere)
	float OpenYaw = 90.f;
	float CloseYaw;
	FRotator ObjRotation;
	AActor *OwningObj = nullptr;
	float DoorLastOpened = 0.f;
	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;

	UPROPERTY(EditAnywhere) 
	float DoorClosedDelay = 0.3f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 1.33f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.33f;
};
