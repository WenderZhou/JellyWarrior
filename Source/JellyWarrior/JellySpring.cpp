// Fill out your copyright notice in the Description page of Project Settings.


#include "JellySpring.h"

// Sets default values
AJellySpring::AJellySpring()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	GridSize = 6;
	
	for(int i = 0; i < GridSize; i++)
		for(int j = 0; j < GridSize; j++)
			for(int k = 0; k < GridSize; k++)
	{
		FString SubObjectName = FString::Printf(TEXT("Sphere_%d_%d_%d"), i, j, k);;
		UStaticMeshComponent* StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*SubObjectName);
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Engine/BasicShapes/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			StaticMeshComponent->SetStaticMesh(Mesh.Object);
		}
		StaticMeshComponent->SetupAttachment(RootComponent);
		StaticMeshComponent->SetRelativeScale3D(FVector(0.03f, 0.03f, 0.03f));
		StaticMeshComponent->SetRelativeLocation(10.0f * FVector(i, j, k));

		StaticMeshComponent->SetSimulatePhysics(true);
				
		Spheres.Push(StaticMeshComponent);
	}

	for(int i = 0; i < GridSize; i++)
		for(int j = 0; j < GridSize; j++)
			for(int k = 0; k < GridSize; k++)
			{
				if(i + 1 < GridSize)
				{
					AddConstraint(i, j, k, i + 1, j, k);
				}

				if(j + 1 < GridSize)
				{
					AddConstraint(i, j, k, i, j + 1, k);
				}

				if(k + 1 < GridSize)
				{
					AddConstraint(i, j, k, i, j, k + 1);
				}

				if(i + 1 < GridSize && j + 1 < GridSize)
				{
					AddConstraint(i, j, k, i + 1, j + 1, k);
					AddConstraint(i + 1, j, k, i, j + 1, k);
				}
				
				if(i + 1 < GridSize && k + 1 < GridSize)
				{
					AddConstraint(i, j, k, i + 1, j, k + 1);
					AddConstraint(i + 1, j, k, i, j, k + 1);
				}
				
				if(j + 1 < GridSize && k + 1 < GridSize)
				{
					AddConstraint(i, j, k, i, j + 1, k + 1);
					AddConstraint(i, j + 1, k, i, j, k + 1);
				}
			}
}

// Called when the game starts or when spawned
void AJellySpring::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJellySpring::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJellySpring::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJellySpring::AddConstraint(int i1, int j1, int k1, int i2, int j2, int k2)
{
	FString SubObjectName = FString::Printf(TEXT("Constrian_%d_%d_%d_%d_%d_%d"), i1, j1, k1, i2, j2, k2);;
	UPhysicsConstraintComponent* PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(*SubObjectName);

	auto Sphere1 = Spheres[i1 * GridSize * GridSize + j1 * GridSize + k1];
	auto Sphere2 = Spheres[i2 * GridSize * GridSize + j2 * GridSize + k2];

	PhysicsConstraintComponent->SetRelativeLocation((Sphere1->GetRelativeLocation() + Sphere2->GetRelativeLocation()) / 2);

	PhysicsConstraintComponent->SetConstrainedComponents(Sphere1, NAME_None, Sphere2, NAME_None);

	PhysicsConstraintComponent->SetLinearXLimit(LCM_Free, 0.0f);
	PhysicsConstraintComponent->SetLinearYLimit(LCM_Free, 0.0f);
	PhysicsConstraintComponent->SetLinearZLimit(LCM_Free, 0.0f);

	PhysicsConstraintComponent->SetLinearPositionDrive(true, true, true);
	PhysicsConstraintComponent->SetLinearPositionTarget(FVector(0.0f, 0.0f, 0.0f));
	PhysicsConstraintComponent->SetLinearDriveParams(5000.f, 1.f, 10000.f);

	PhysicsConstraintComponent->SetVisibility(false);
					
	PhysicsConstraintComponent->SetupAttachment(RootComponent);
}

