// Fill out your copyright notice in the Description page of Project Settings.


#include "Balloon.h"

// Sets default values
ABalloon::ABalloon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Engine/BasicShapes/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			StaticMeshComponent->SetStaticMesh(Mesh.Object);
		}
		
		StaticMeshComponent->SetRelativeLocation(FVector(0.f,0.f,50.f));
		
		StaticMeshComponent->SetSimulatePhysics(true);
		StaticMeshComponent->SetEnableGravity(false);

		StaticMeshComponent->BodyInstance.bOverrideMass = true;
		StaticMeshComponent->BodyInstance.SetMassOverride(1.f);
		
		RootComponent = StaticMeshComponent;
	}

	{
		BalloonAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BalloonAttachPoint"));

		BalloonAttachPoint->SetRelativeLocation(FVector(0.f, 0.f, -200.f));

		BalloonAttachPoint->SetupAttachment(StaticMeshComponent);
	}
	
	{
		CableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));

		CableComponent->SetRelativeLocation(FVector(0.f,0.f,-50.0f));
		CableComponent->EndLocation = FVector(0.f,0.f,0.f);
		
		CableComponent->SetupAttachment(StaticMeshComponent);
	}

	{
		PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));

		PhysicsConstraintComponent->SetConstrainedComponents(nullptr, NAME_None, StaticMeshComponent, NAME_None);
		
		PhysicsConstraintComponent->SetLinearXLimit(LCM_Limited, 200.0f);
		PhysicsConstraintComponent->SetLinearYLimit(LCM_Limited, 200.0f);
		PhysicsConstraintComponent->SetLinearZLimit(LCM_Limited, 200.0f);
		
		PhysicsConstraintComponent->SetupAttachment(RootComponent);
	}

	LyftMin = 0.0f;
	LyftMax = 0.0f;

	HeightMax = 1.0f;
	HeightMin = 0.0f;
}

// Called when the game starts or when spawned
void ABalloon::BeginPlay()
{
	Super::BeginPlay();

	// Assign a random color for the balloon
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/Balloon/M_Balloon.M_Balloon'"));
	if(Material)
	{
		MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(Material, nullptr);
		StaticMeshComponent->SetMaterial(0, MaterialInstanceDynamic);
		const FVector Color(FMath::RandRange(0.f,1.f), FMath::RandRange(0.f,1.f), FMath::RandRange(0.f,1.f));
		MaterialInstanceDynamic->SetVectorParameterValue(TEXT("Color"), Color);
	}
}

// Called every frame
void ABalloon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float Height = FMath::Clamp(StaticMeshComponent->GetComponentLocation().Z, HeightMin, HeightMax);
	const float Alpha = (Height - HeightMin) / (HeightMax - HeightMin);
	
	const float Lyft = FMath::Lerp(LyftMax, LyftMin, Alpha);
	
	const FVector Force(0.f, 0.f, Lyft);
	StaticMeshComponent->AddForce(Force);
}

void ABalloon::Attach(UPrimitiveComponent* PhysicsConstraintAttachComponent, USceneComponent* AttachComponent, FName SocketName)
{
	PhysicsConstraintComponent->SetConstrainedComponents(PhysicsConstraintAttachComponent, NAME_None, StaticMeshComponent, NAME_None);

	CableComponent->SetAttachEndToComponent(AttachComponent, SocketName);
}

void ABalloon::Detach()
{
	PhysicsConstraintComponent->BreakConstraint();

	CableComponent->SetAttachEndToComponent(BalloonAttachPoint);

	SetLifeSpan(3.0f);
}

