// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOM_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FDoorRequest OpenRequest;

	UPROPERTY(BlueprintAssignable)
		FDoorRequest CloseRequest;

private:

	float GetMassOfActorsStanding(); // Gets total mass and names of all actors standing on the pressure plate and logs it

	UPROPERTY(VisibleAnywhere)
		float OpenAngle = -90.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;
	
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
		float TriggerMass = 50.f;

	float LastOpenTime;
	float CurrentTime;
	AActor* Owner = nullptr;
};
