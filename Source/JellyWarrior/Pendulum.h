// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Pendulum.generated.h"

UCLASS()
class JELLYWARRIOR_API APendulum : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APendulum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UTimelineComponent* TimelineComponent;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

	UFUNCTION()
	void SetRoll(float Roll);
	
	UFUNCTION()
	void PlayTimeline();

	UFUNCTION()
	void StopTimeline();
};
