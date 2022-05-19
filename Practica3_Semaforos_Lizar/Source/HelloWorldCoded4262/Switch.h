// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Switch.generated.h"

UCLASS()
class HELLOWORLDCODED4262_API ASwitch : public AActor
{
	GENERATED_BODY()
	
public:	

	//Colisionador del objeto
	UPROPERTY(EditAnywhere, Category = "Collider")
		class UBoxComponent* boxCollider;

	//Malla del objeto
	UPROPERTY(EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* mesh;

	// Sets default values for this actor's properties
	ASwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
