// Fill out your copyright notice in the Description page of Project Settings.


#include "Displacer.h"
#include "Beacon.h"

// Sets default values
ADisplacer::ADisplacer()
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

	//Suscripción a los eventos de trigger enter
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ADisplacer::TriggerEnter);

	//Suscripción a los eventos de trigger enter
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &ADisplacer::TriggerExit);

	lastTrigger = nullptr;

}

// Called when the game starts or when spawned
void ADisplacer::BeginPlay()
{
	Super::BeginPlay();

	//Indica que el objeto se está desplazando
	isDisplacing = true;
	
}

// Called every frame
void ADisplacer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Desplaza al actor por la escena
	if(isDisplacing)
		SetActorLocation(GetActorLocation() - GetActorRightVector() * direction * DeltaTime * displacementSpeed);

}

//Método que gira el objeto
void ADisplacer::Rotate()
{
	if (direction == 1)
		direction = -1;
	else
		direction = 1;
}

//Método que establece si el objeto se moverá
void ADisplacer::Displace(bool displace)
{
	isDisplacing = displace;

}

//Funcion que permite moverse si tiene permiso
void ADisplacer::Permit() {
	Displace(true);
}

//Trigger enter
void ADisplacer::TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Se compueba que sea un puntero válido
	if (OtherActor != nullptr)
	{
		//Se convierte de actor a displacer o semaforo, para distinguir las acciones a tomar
		ASwitch* trigger = Cast<ASwitch>(OtherActor);
		ABeacon* semaforo = Cast<ABeacon>(OtherActor);
		//se comprueba que sea alguno de los dos casos anteriores
		if (trigger != nullptr) {
			
			//Si no ha chocado con un muro lo guarda, para no chocar de nuevo con el y gira su direccion
			if (lastTrigger == nullptr) {
				lastTrigger = trigger;
				Rotate();
			}//Si sí a chocado con algun muro, comprueba que no sea el mismo, y si es distinto, gira
			else if (trigger->GetName() != lastTrigger->GetName()) {
				lastTrigger = trigger;
				Rotate();
			}
			
		}//Si ha chocado con un semaforo, se para y pide permiso al semaforo
		else if (semaforo != nullptr) {
			Displace(false);
			semaforo->StoppedVehicle(this);
		}
	}
}

//Trigger exit
void ADisplacer::TriggerExit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Se compueba que sea un puntero válido
	if (OtherActor != nullptr)
	{
		//Si sale de la zona de influencia de un semaforo, le da la señal para que este este abierto a dar permisos a otros desplazadores
		ABeacon* semaforo = Cast<ABeacon>(OtherActor);
		if (semaforo != nullptr) {
			semaforo->AllowPermits();
		}
	}
}
