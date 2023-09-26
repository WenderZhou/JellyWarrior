// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Cannon.generated.h"

UCLASS()
class JELLYWARRIOR_API ACannon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* MountPivotComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MountMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BarrelMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPointComponent;

	UPROPERTY(VisibleAnywhere)
	class UTimelineComponent* TimelineComponent;

	UPROPERTY(VisibleAnywhere)
	class UCurveVector* CurveVector;

	UFUNCTION(BlueprintCallable)
	void UpdateDirection(FVector2f ActionValue);

	UFUNCTION(BlueprintCallable)
	bool Fire();

	UFUNCTION()
	void Recoil(FVector value);

	UPROPERTY(VisibleAnywhere)
	float CoolDownTimeRemain;

	UPROPERTY(VisibleAnywhere)
	float CoolDownTimeTotal;
};
