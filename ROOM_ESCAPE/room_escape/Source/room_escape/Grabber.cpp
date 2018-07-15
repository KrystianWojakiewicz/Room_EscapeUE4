// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"

#define OUT

//FUNCTIONS
void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	GetFirstPhysicsBodyInReach();
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
}

void UGrabber::FindPhysicsHandleComponent() {
	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) { ; }
	else {
		UE_LOG(LogTemp, Error, TEXT("Physics Handle not found in object %s"), *Owner->GetName())
	}
}


void UGrabber::FindInputComponent() {
	
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Input Component not found in object %s"), *Owner->GetName())
	}
}


void UGrabber::DebugLine(FVector &PlayerViewLoc, FVector &LineTraceEnd) {
	
	DrawDebugLine(
		GetWorld(),
		PlayerViewLoc,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		25.f
	);
}

 
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {
	
	FVector PlayerViewLoc;
	FRotator PlayerViewRot;

	//Get player location and rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLoc,
		OUT PlayerViewRot
	);

	// Gets coordinates of maximimum reach
	FVector LineTraceEnd = PlayerViewLoc + PlayerViewRot.Vector() * Reach;
	FHitResult Hit;
	FCollisionQueryParams TraceParamenters(FName(TEXT("")), false, GetOwner());
	
	// Check collison	
	bool bTrace = GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewLoc,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParamenters
	);

	// confirm the collison with a Log
	if (bTrace) {
		FString ActorHit = Hit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("COLLISON WITH OBJECT %s"), *ActorHit);
	}
	return FHitResult();
}
////////////////////////////////////////END OF FUNCTIONS////////////////////////////////////////////


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

	Owner = GetOwner();

	FindPhysicsHandleComponent();
	FindInputComponent();
	
}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//TODO If collision detected and grab is pressed
		//Move grabbed object every frame
}



