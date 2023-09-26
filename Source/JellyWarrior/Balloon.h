// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CableComponent.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Balloon.generated.h"

UCLASS()
class JELLYWARRIOR_API ABalloon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABalloon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Attach(UPrimitiveComponent* PhysicsConstraintAttachComponent, USceneComponent* AttachComponent, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void Detach();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* BalloonAttachPoint;
	
	UPROPERTY(EditAnywhere)
	UCableComponent* CableComponent;

	UPROPERTY(EditAnywhere)
	UPhysicsConstraintComponent* PhysicsConstraintComponent;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* MaterialInstanceDynamic;

	UPROPERTY(EditAnywhere)
	float LyftMin;

	UPROPERTY(EditAnywhere)
	float LyftMax;

	UPROPERTY(EditAnywhere)
	float HeightMin;

	UPROPERTY(EditAnywhere)
	float HeightMax;
};
