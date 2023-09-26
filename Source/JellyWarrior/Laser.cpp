// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"

#include <Windows.Data.Text.h>

#include "Jelly.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}
	
	// Create static mesh for light beams
	for(int i = 0; i < 3; i++)
	{
		FString SubObjectName = FString::Printf(TEXT("Mesh%d"), i);;
		UStaticMeshComponent* StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*SubObjectName);
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Engine/BasicShapes/Cylinder.Cylinder'"));
		if (Mesh.Succeeded())
		{
			StaticMeshComponent->SetStaticMesh(Mesh.Object);
		}
		StaticMeshComponent->BodyInstance.SetCollisionProfileName(TEXT("OverlapAll"));
		StaticMeshComponent->SetupAttachment(RootComponent);
		StaticMeshComponent->SetVisibility(false);
		
		Beams.Add(StaticMeshComponent);
	}

	{
		ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
		ArrowComponent->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Origin = GetActorLocation();
	FVector Direction = ArrowComponent->GetForwardVector();

	for(auto Beam : Beams)
	{
		Beam->SetVisibility(false);
	}
	
	for(auto Beam : Beams)
	{
		FHitResult HitResult;
		Emit(Beam, Origin, Direction, HitResult);

		if(HitResult.GetActor() && HitResult.GetActor()->ActorHasTag(TEXT("Reflector")))
		{
			Origin = HitResult.Location;
			Direction = HitResult.Normal;
		}
		else
		{
			break;
		}
	}
}

// Emit a beam
void ALaser::Emit(UStaticMeshComponent* StaticMeshComponent, const FVector Origin, const FVector Direction, FHitResult& HitResult)
{
	const FVector Start = Origin;
	const FVector End = Start + 5000.f * Direction;

	StaticMeshComponent->SetVisibility(true);
	
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	if(HitResult.GetActor())
	{
		StaticMeshComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, HitResult.Distance / 100.f));
		StaticMeshComponent->SetWorldRotation(FRotationMatrix::MakeFromZ(Direction).Rotator());
		StaticMeshComponent->SetWorldLocation((HitResult.Location + Start) / 2);
	}
	else
	{
		StaticMeshComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 5000.f / 100.f));
		StaticMeshComponent->SetWorldRotation(FRotationMatrix::MakeFromZ(Direction).Rotator());
		StaticMeshComponent->SetWorldLocation((End + Start) / 2);
	}
}

