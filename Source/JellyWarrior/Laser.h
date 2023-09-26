// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class JELLYWARRIOR_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> Beams;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComponent;

	UFUNCTION()
	void Emit(UStaticMeshComponent* StaticMeshComponent, const FVector Origin, const FVector Direction, FHitResult& HitResult);
};
