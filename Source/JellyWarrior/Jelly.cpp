// Fill out your copyright notice in the Description page of Project Settings.


#include "Jelly.h"

// Sets default values
AJelly::AJelly()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJelly::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJelly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJelly::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJelly::PromptEnqueue(FString Message)
{
	PromptQueue.Enqueue(Message);
}

FString AJelly::PromptDequeue()
{
	FString Message;
	PromptQueue.Peek(Message);
	PromptQueue.Pop();
	return Message;
}

bool AJelly::PromptEmpty()
{
	return PromptQueue.IsEmpty();
}

