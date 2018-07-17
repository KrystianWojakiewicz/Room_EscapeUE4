// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

#define OUT

//FUNCTIONS
void UGrabber::Grab() {
	
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit) {

		if (!PhysicsHandle) return;
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(), // what point of component to grab
			true // To enable rotation 
		);
	}
}

void UGrabber::Release() {
	if (!PhysicsHandle) return;
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent() {
	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
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

FVector UGrabber::FindStartOfLineTrace() const {
	FVector PlayerViewLoc;
	FRotator PlayerViewRot;

	//Get player location and rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLoc,
		OUT PlayerViewRot
	);

	// return coordinates of maximimum reach
	return PlayerViewLoc;

}

FVector UGrabber::FindEndOfLineTrace() const {
FVector PlayerViewLoc;
FRotator PlayerViewRot;

//Get player location and rotation
GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
	OUT PlayerViewLoc,
	OUT PlayerViewRot
);

// return coordinates of maximimum reach
return PlayerViewLoc + PlayerViewRot.Vector() * Reach;

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {
	
	FHitResult Hit;
	FCollisionQueryParams TraceParamenters(FName(TEXT("")), false, GetOwner());
	// Check collison	
	bool bTrace = GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		FindStartOfLineTrace(),
		FindEndOfLineTrace(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParamenters
	);

	// confirm the collison with a Log
	if (bTrace) {
		FString ActorHit = Hit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("COLLISON WITH OBJECT %s"), *ActorHit);
	}
	return Hit;
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
	
	if (!PhysicsHandle) return;
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(FindEndOfLineTrace()); //Move grabbed object every frame
		
	}
	
		
}



