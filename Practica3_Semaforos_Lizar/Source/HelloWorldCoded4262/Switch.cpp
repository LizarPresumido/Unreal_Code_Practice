// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"
#include "Displacer.h"

// Sets default values
ASwitch::ASwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Crea el componente Collider
	boxCollider = CreateDefaultSubobject<UBoxComponent>("Collider");

	//Establece la medida del collider
	boxCollider->SetBoxExtent(FVector(50, 50, 50));

	//Establece la raíz en la jerarquía de componentes
	SetRootComponent(boxCollider);

	//Crea el componente Malla
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	//Modifica la jerarquía de componentes
	mesh->AttachToComponent(boxCollider, FAttachmentTransformRules::SnapToTargetIncludingScale);


}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();

	mesh->SetVisibility(false);

}



