// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckPoint.h"
#include "GameFramework/Character.h"
#include "Containers/Queue.h"
#include "Jelly.generated.h"

UCLASS()
class JELLYWARRIOR_API AJelly : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJelly();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACheckPoint* LastCheckPoint;
	
	TQueue<FString> PromptQueue;

	UFUNCTION(BlueprintCallable)
	void PromptEnqueue(FString Message);

	UFUNCTION(BlueprintCallable)
	FString PromptDequeue();

	UFUNCTION(BlueprintCallable)
	bool PromptEmpty();
};
