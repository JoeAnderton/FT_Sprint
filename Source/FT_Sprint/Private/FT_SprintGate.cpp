// Fill out your copyright notice in the Description page of Project Settings.


#include "FT_SprintGate.h"
#include "FT_SprintGateManager.h" 

// Sets default values
AFT_SprintGate::AFT_SprintGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create our mesh component
	gateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gate Mesh"));
	// set the gate as our Root Component in other word the base of our object
	SetRootComponent(gateMesh);

	// Set up overlap events, Trigger
	gateMesh->SetGenerateOverlapEvents(true);
	gateMesh->OnComponentBeginOverlap.AddDynamic(this, &AFT_SprintGate::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AFT_SprintGate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFT_SprintGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// add a collision function for the gates
void AFT_SprintGate::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if we hit the player character
	if(OtherActor
		&& (OtherActor != this) && OtherComp)
	{
		// only trigger once
		if(!isTriggered && !completedTrack)
		{
			isTriggered = true;
			// inform the gate manager
			if (AFT_SprintGateManager::instance)
			{
				AFT_SprintGateManager::instance->GatePassed();
				UE_LOG(LogTemp, Log, TEXT("Sprint Gate Triggered"));
			}
		}
	}
}
