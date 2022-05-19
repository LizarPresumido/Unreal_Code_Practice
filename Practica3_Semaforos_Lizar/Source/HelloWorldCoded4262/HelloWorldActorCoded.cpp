// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloWorldActorCoded.h"

// Sets default values
AHelloWorldActorCoded::AHelloWorldActorCoded()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHelloWorldActorCoded::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(0, 15, FColor::White, message);
	
}

// Called every frame
void AHelloWorldActorCoded::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

