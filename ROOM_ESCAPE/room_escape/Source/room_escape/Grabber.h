// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOM_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	UPROPERTY(EditAnywhere)
		float Reach = 150.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	AActor* Owner;
	
	void Grab(); // Action input "Grab"
	void Release(); // Action input "Grab"
	void FindPhysicsHandleComponent(); // Checks if Physics Handle component is attached
	void FindInputComponent(); // Checks if Input component is attached and if so deal with potential input
	void DebugLine(FVector&, FVector&); // Draws a red 3D line horizontally from Pawn
	FHitResult GetFirstPhysicsBodyInReach() const; // Checks for collision and returns the first PhysicsBody Hit
	FVector FindStartOfLineTrace() const; // uses OUT parameters to find player location/rotation
	FVector FindEndOfLineTrace() const; // uses OUT parameters to find max reach location/rotation
};
