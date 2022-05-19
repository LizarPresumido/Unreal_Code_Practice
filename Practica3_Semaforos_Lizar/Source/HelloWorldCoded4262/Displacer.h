// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Switch.h"
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Displacer.generated.h"


UCLASS()
class HELLOWORLDCODED4262_API ADisplacer : public AActor
{
	GENERATED_BODY()
	
public:	

	//Colisionador del objeto
	UPROPERTY(EditAnywhere, Category = "Collider")
		class UBoxComponent* boxCollider;

	//Malla del objeto
	UPROPERTY(EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* mesh;

	//Velocidad de desplazamiento del objeto
	UPROPERTY(EditAnywhere, Category = "Actor Data")
		float displacementSpeed = 10;

	//Indioca si el objeto se está desplazando
	UPROPERTY(EditAnywhere, Category = "Actor Data")
		bool isDisplacing;

	//Variable de control para no chocar 2 veces con el mismo objeto
	ASwitch* lastTrigger;

	// Sets default values for this actor's properties
	ADisplacer();

	//Valor de la direccion del desplazador (1 - ir hacia delante / -1 - ir hacia detras)
	int direction = 1;

	//Método que establece si el objeto se moverá
	UFUNCTION()
		void Displace(bool displace);

	//Método que establece si el objeto se moverá
	UFUNCTION()
		void Permit();

	//Método que gira la direccion del objeto
	UFUNCTION()
		void Rotate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Trigger Enter
	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	//Trigger exit
	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

};
