// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;

	FVector PlayerViewpointLoc;
	FRotator PlayerViewpointRot;
	OwnerController->GetPlayerViewPoint(PlayerViewpointLoc, PlayerViewpointRot);

	FVector End = PlayerViewpointLoc + PlayerViewpointRot.Vector() * MaxRange;

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, PlayerViewpointLoc, End, ECollisionChannel::ECC_GameTraceChannel1);
	if (bSuccess)
	{
		//DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor::Red, true);
		//UE_LOG(LogTemp, Display, TEXT("Success, there was a hit!"));
		FVector ShotDirection = -PlayerViewpointRot.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		AActor* ActorHit = Hit.GetActor();
		if(ActorHit)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			ActorHit->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
	//DrawDebugCamera(GetWorld(), PlayerViewpointLoc, PlayerViewpointRot, 90, 2, FColor::Red, true);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

