// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "Beacon.generated.h"

UCLASS()
class HELLOWORLDCODED4262_API ABeacon : public AActor
{
	GENERATED_BODY()
	
public:	

	//Colisionador del objeto
	UPROPERTY(EditAnywhere, Category = "Collider")
		class USphereComponent* collider;

	//Colores de la luz
	FLinearColor stopColor, continueColor;

	//Estado de la baliza
	enum BeaconState { Verde, Rojo };
	BeaconState beaconState;

	//https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Engine/FTimerHandle/
	//Manejador que identifica a un timer de manera única
	FTimerHandle timerId;

	FTimerDelegate timerDel;

	//Punto de Luz
	UPointLightComponent* light;	

	//Lista de objetos desplazador detenidos
	TArray<class ADisplacer*> list;


	//Booleana que controla si hay algun desplazador moviendose en su interior
	bool displacerMoving;


	// Sets default values for this actor's properties
	ABeacon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		//Funcion para detectar un desplazador parado
		void StoppedVehicle(class ADisplacer* displacer);

	UFUNCTION()
		//Funcion para dar permiso cuando el desplazador actual en movimiento sale de rango
		void AllowPermits();

private:

	UFUNCTION()
		//Funcion para ejecutar los cambios cuando la baliza cambia de estado
		void Switching(bool state);

	UFUNCTION()
		//Enciende o apaga la luz de la baliza
		void SetLight();


	UFUNCTION()
		//Callback del timer para dar permiso a un desplazador
		void GivePermission();

};
