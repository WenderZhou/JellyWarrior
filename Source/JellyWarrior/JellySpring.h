// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "JellySpring.generated.h"

UCLASS()
class JELLYWARRIOR_API AJellySpring : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJellySpring();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> Spheres;

	UPROPERTY(EditAnywhere)
	TArray<UPhysicsConstraintComponent*> PhysicsConstraintComponents;

	int GridSize;
	
	UFUNCTION()
	void AddConstraint(int i1, int j1, int k1, int i2, int j2, int k2);
};
