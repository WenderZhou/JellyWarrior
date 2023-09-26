// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlButton.h"

// Sets default values
AControlButton::AControlButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}
	
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Engine/BasicShapes/Cube.Cube'"));
		if (Mesh.Succeeded())
		{
			StaticMeshComponent->SetStaticMesh(Mesh.Object);
		}
		StaticMeshComponent->SetRelativeScale3D(FVector(1.f, 1.f, 0.1f));
		StaticMeshComponent->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AControlButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AControlButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}