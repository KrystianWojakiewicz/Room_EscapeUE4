// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

////////////Functions
void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();
	FRotator ObjectRot = Owner->GetActorRotation();
	FRotator NewRot(0.f, -60.f, 0.f);
	if (!Owner->SetActorRotation(NewRot, ETeleportType::None)) {
		UE_LOG(LogTemp, Warning, TEXT("Could not open door"));
	}
}
////////////////////////////////


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
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}
	
}

