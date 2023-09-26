// Fill out your copyright notice in the Description page of Project Settings.


#include "RopeBridge.h"

#include "Kismet/KismetMathLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ARopeBridge::ARopeBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}
	
	for(int i = 0; i < 12; i++)
	{
		FString SubObjectName = FString::Printf(TEXT("Plank%d"), i);;
		UStaticMeshComponent* StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*SubObjectName);

		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Building/SM_Board.SM_Board'"));
			
		StaticMeshComponent->SetStaticMesh(Mesh.Object);
		
		StaticMeshComponent->SetRelativeLocation(i * 150.f * FVector(1.0f, 0.0f, 0.0f));
		StaticMeshComponent->SetRelativeRotation(FRotator());
		StaticMeshComponent->SetRelativeScale3D(FVector(2.0f, 6.0f, 2.0f));
	
		StaticMeshComponent->SetSimulatePhysics(true);
		
		StaticMeshComponent->SetupAttachment(RootComponent);
		
		Planks.Add(StaticMeshComponent);
	}
	
	for(int i = 1; i < 12; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			FString SubObjectName = FString::Printf(TEXT("Constrian%d"), 2 * i + j);;
			UPhysicsConstraintComponent* PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(*SubObjectName);
		
			PhysicsConstraintComponent->SetRelativeLocation(Planks[i - 1]->GetRelativeLocation() + FVector(0.0f, 1.0f, 0.0f) * 140.f * (2 * j - 1));
		
			PhysicsConstraintComponent->SetConstrainedComponents(Planks[i], NAME_None, Planks[i - 1], NAME_None);
		
			PhysicsConstraintComponent->SetLinearXLimit(LCM_Limited, 0.0f);
			PhysicsConstraintComponent->SetLinearYLimit(LCM_Limited, 0.0f);
			PhysicsConstraintComponent->SetLinearZLimit(LCM_Limited, 0.0f);
		
			PhysicsConstraintComponent->SetupAttachment(RootComponent);
		}
	}
	
	Planks[0]->SetSimulatePhysics(false);
	Planks[11]->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void ARopeBridge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARopeBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

