// Copyright Aaron Watkins 2021

#include "Grabber1.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/WorldSettings.h"
#include "CollisionQueryParams.h"
#define OUT 

// Sets default values for this component's properties
UGrabber1::UGrabber1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber1::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("%s has no physics handle component to be found."),
			*GetOwner()->GetName()
		);
	}
}


void UGrabber1::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(
			LogTemp,
			Display,
			TEXT("%s has an input component."),
			*GetOwner()->GetName()
		);
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber1::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber1::Release);
	}
}


// Called when the game starts
void UGrabber1::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	FindInputComponent();
}


void UGrabber1::Grab()
{
	UE_LOG(LogTemp, Display, TEXT("Grabber pressed"));
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	// see what we are hitting
	AActor *ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Display, TEXT("Line trace has hit %s."), *ActorHit->GetName());
		PhysicsHandle->GrabComponentAtLocation(
			HitResult.GetComponent(),
			NAME_None,
			ActorHit->GetActorLocation()
		);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Line trace has hit nothing."));
	}
}


FVector UGrabber1::GetPlayerReachPosition() const
{
	FVector PlayerVPLoc;
	FRotator PlayerVPRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPLoc,
		OUT PlayerVPRot
	);
	// draw a line from player showing the reach
	return PlayerVPLoc + PlayerVPRot.Vector() * PlayerReach;
}


FVector UGrabber1::GetPlayerWorldPosition() const
{
	FVector PlayerVPLoc;
	FRotator PlayerVPRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerVPLoc, OUT PlayerVPRot);
	return PlayerVPLoc;
}


void UGrabber1::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Grabber released"));
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
}


FHitResult UGrabber1::GetFirstPhysicsBodyInReach() const
{
	// DrawDebugLine(
	// 	GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 0, 255), false, 0.f, 0, 5.f
	// );

	// ray-cast out to a certain distance
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerWorldPosition(),
		GetPlayerReachPosition(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return Hit;
}


// Called every frame
void UGrabber1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayerReachPosition());
	}
}

