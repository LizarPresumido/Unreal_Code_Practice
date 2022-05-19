// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HelloWorldActorCoded.generated.h"

UCLASS()
class HELLOWORLDCODED4262_API AHelloWorldActorCoded : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, Category = "Data Param")
		FString message;

	// Sets default values for this actor's properties
	AHelloWorldActorCoded();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
