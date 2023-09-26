// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"

#include "Jelly.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
    	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    }
	
	{
		Pole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pole"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/CheckPoint/SM_Flagpole.SM_Flagpole'"));
		if (Mesh.Succeeded())
		{
			Pole->SetStaticMesh(Mesh.Object);
		}
		
		Pole->SetupAttachment(RootComponent);
	}

	{
		Flag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/CheckPoint/SM_Flag.SM_Flag'"));
		if (Mesh.Succeeded())
		{
			Flag->SetStaticMesh(Mesh.Object);
		}
		
		Flag->SetupAttachment(Pole);
	}

	{
		TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));

		TriggerVolume->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACheckPoint::Save(AActor* Actor)
{
	if(Actor->IsA(AJelly::StaticClass()))
	{
		AJelly* Jelly = Cast<AJelly>(Actor);
		Jelly->LastCheckPoint = this;

		return true;
	}
	return false;
}
