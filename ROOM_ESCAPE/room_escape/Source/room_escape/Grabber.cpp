// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber is working"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewLoc;
	FRotator PlayerViewRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLoc,
		OUT PlayerViewRot
	);
	
	UE_LOG(LogTemp, Warning, TEXT("Player Location is %s"), *PlayerViewLoc.ToString());
	UE_LOG(LogTemp, Error, TEXT("  Player View is %s"), *PlayerViewRot.ToString());

	/* Another Way of getting player ViewPoint
	FString PlayerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetPawnViewLocation().ToString();
	FString PlayerView = GetWorld()->GetFirstPlayerController()->GetPawn()->GetViewRotation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Player Location is %s"), *PlayerLoc);
	UE_LOG(LogTemp, Error, TEXT("  Player View is %s"), *PlayerView);
	*/
}

