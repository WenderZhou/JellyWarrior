// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

UCLASS()
class JELLYWARRIOR_API ACheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Flag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pole;

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerVolume;

	UFUNCTION(BlueprintCallable)
	bool Save(AActor* Actor);
};
