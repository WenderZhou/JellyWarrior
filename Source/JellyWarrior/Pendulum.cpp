// Fill out your copyright notice in the Description page of Project Settings.


#include "Pendulum.h"

// Sets default values
APendulum::APendulum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}
	
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Pendulum/SM_Pendulum.SM_Pendulum'"));
		if (Mesh.Succeeded())
		{
			StaticMeshComponent->SetStaticMesh(Mesh.Object);
		}
		StaticMeshComponent->SetRelativeScale3D(FVector(80.f, 80.f, 80.f));
		StaticMeshComponent->SetupAttachment(RootComponent);
	}

	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("'/Game/Pendulum/C_Pendulum.C_Pendulum'"));
		check(Curve.Succeeded());
		CurveFloat = Curve.Object;
		
		TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
		
		FOnTimelineFloat InterpFunc;
		InterpFunc.BindUFunction(this, FName("SetRoll"));
		TimelineComponent->AddInterpFloat(CurveFloat, InterpFunc);

		TimelineComponent->SetLooping(true);
	}
}

// Called when the game starts or when spawned
void APendulum::BeginPlay()
{
	Super::BeginPlay();

	PlayTimeline();
}

// Called every frame
void APendulum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APendulum::SetRoll(float Roll)
{
	FRotator Rotator = StaticMeshComponent->GetRelativeRotation();
	Rotator.Roll = Roll;
	StaticMeshComponent->SetRelativeRotation(Rotator);
}

void APendulum::PlayTimeline()
{
	TimelineComponent->Play();
}

void APendulum::StopTimeline()
{
	TimelineComponent->Stop();
}
