// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

#define OUT

////////////Functions//////////////////////////////////////////////////////

void UOpenDoor::OpenDoor()
{
	FRotator NewRot(0.f, OpenAngle, 0.f);
	if (!Owner->SetActorRotation(NewRot, ETeleportType::None)) {
		UE_LOG(LogTemp, Warning, TEXT("Could not open door"));
	}
}

void UOpenDoor::CloseDoor()
{
	FRotator NewRot(0.f, 0.f, 0.f);
	if (!Owner->SetActorRotation(NewRot, ETeleportType::None)) {
		UE_LOG(LogTemp, Warning, TEXT("Could not close door"));
	}
}

float UOpenDoor::GetMassOfActorsStanding() {

	float TotalMass = 0.f;

	// using OUT getter to find actors overlapping pressure plate
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) return TotalMass;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	// iterate through actors overlapping and log their names
	FString ListOfActorsOverlapping;

	for (const auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		ListOfActorsOverlapping += Actor->GetName();
		ListOfActorsOverlapping += TEXT(" , ");
	}
	if (OverlappingActors.Num() != 0) {
		UE_LOG(LogTemp, Warning, TEXT(" Actors Standing: %s \n Total Mass: %f"), *ListOfActorsOverlapping, TotalMass)
	}
	
		// return the total mass of actors inside the pressure plate
		return TotalMass;
}

////////////////////////////////END OF FUNCTIONS////////////////////////////////////////////////////


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

	Owner = GetOwner();
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate not attached to %s"), *Owner->GetName())
	}
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GetMassOfActorsStanding() > TriggerMass) {
		OpenDoor();
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LastOpenTime >= DoorCloseDelay) {
		CloseDoor();

	}
}

