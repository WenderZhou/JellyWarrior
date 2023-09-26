// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "Bullet.h"
#include "Curves/CurveVector.h"
#include "Components/TimelineComponent.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	// Camera
	{
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		check(CameraComponent != nullptr);

		CameraComponent->SetRelativeLocation(FVector(-150.0f, 0.0f, 250.0f));

		CameraComponent->bUsePawnControlRotation = false;

		CameraComponent->SetupAttachment(RootComponent);
	}
	
	// Mount
	{
		MountPivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MountPivot"));
		MountPivotComponent->SetupAttachment(RootComponent);

		MountMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MountMesh"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Cannon/CannonMount.CannonMount'"));
		if (Mesh.Succeeded())
		{
			MountMeshComponent->SetStaticMesh(Mesh.Object);
		}

		MountMeshComponent->SetupAttachment(MountPivotComponent);
	}

	// Barrel
	{
		BarrelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Cannon/CannonBarrel.CannonBarrel'"));
		if (Mesh.Succeeded())
		{
			BarrelMeshComponent->SetStaticMesh(Mesh.Object);
		}
		BarrelMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 96.5f));
		BarrelMeshComponent->SetupAttachment(MountMeshComponent);
	}

	// Bullet Spawn Point
	{
		ProjectileSpawnPointComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));

		ProjectileSpawnPointComponent->SetupAttachment(BarrelMeshComponent);
	}

	// Recoil animation
	{
		static ConstructorHelpers::FObjectFinder<UCurveVector> Curve(TEXT("'/Game/Cannon/C_Cannon.C_Cannon'"));
		check(Curve.Succeeded());
		CurveVector = Curve.Object;

		TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

		FOnTimelineVector InterpFunc;
		InterpFunc.BindUFunction(this, FName("Recoil"));
		TimelineComponent->AddInterpVector(CurveVector, InterpFunc);
	}

	CoolDownTimeRemain = 0.0f;
	CoolDownTimeTotal = 3.0f;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CoolDownTimeRemain > 0.0f)
	{
		CoolDownTimeRemain -= DeltaTime;

		CoolDownTimeRemain = FMath::Max(CoolDownTimeRemain, 0.f);
	}
}

// Called to bind functionality to input
void ACannon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACannon::UpdateDirection(FVector2f ActionValue)
{
	{
		FRotator Rotator = MountPivotComponent->GetRelativeRotation();
		Rotator.Yaw = FMath::Min(45.f, FMath::Max(-45.f, Rotator.Yaw + ActionValue.X * 0.5f));
		MountPivotComponent->SetRelativeRotation(Rotator);
	}

	{
		FRotator Rotator = BarrelMeshComponent->GetRelativeRotation();
		Rotator.Pitch = FMath::Min(30.f, FMath::Max(0.f, Rotator.Pitch + ActionValue.Y * 0.5f));
		BarrelMeshComponent->SetRelativeRotation(Rotator);
	}
}

bool ACannon::Fire()
{
	if (CoolDownTimeRemain > 0.0f)
		return false;

	UClass* ProjectileClass = LoadObject<UClass>(nullptr, TEXT("'/Game/Cannon/BP_Bullet.BP_Bullet_C'"));

	TimelineComponent->PlayFromStart();
	
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPointComponent->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPointComponent->GetComponentRotation();
	
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
	
			ABullet* Bullet = World->SpawnActor<ABullet>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
			if (Bullet)
			{
				FVector LaunchDirection = SpawnRotation.Vector();
				Bullet->FireInDirection(LaunchDirection);
	
				CoolDownTimeRemain = CoolDownTimeTotal;
	
				TimelineComponent->PlayFromStart();

				return true;
			}
		}
	}

	return false;
}

void ACannon::Recoil(FVector value)
{
	MountMeshComponent->SetRelativeLocation(value);
}

