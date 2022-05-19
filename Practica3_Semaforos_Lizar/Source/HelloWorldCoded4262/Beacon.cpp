// Fill out your copyright notice in the Description page of Project Settings.


#include "Beacon.h"
#include "Displacer.h"

// Sets default values
ABeacon::ABeacon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Declaracion del valor rgb para los colores del beacon
	continueColor.InitFromString("R=0,G=255,B=0,A=1");
	stopColor.InitFromString("R=255,G=0,B=0,A=1");

	//Crea el colisionador
	collider = CreateDefaultSubobject<USphereComponent>("Collider");
	collider->SetSphereRadius(128, true);
	RootComponent = collider;

	//Se añade la luz al beacon
	light = CreateDefaultSubobject<UPointLightComponent>("Light");
	light->AttachToComponent(collider, FAttachmentTransformRules::SnapToTargetIncludingScale);
	light->SetLightColor(continueColor);

	//Se linkea la funcion para dar permiso al timers, para dar delay
	timerDel.BindUFunction(this, FName("GivePermission"));

	//booleana de control para 
	displacerMoving = false;
}

// Called when the game starts or when spawned
void ABeacon::BeginPlay()
{
	Super::BeginPlay();
	//Se establece el color del beacon a verde(Transitable)
	beaconState = BeaconState::Verde;

}

// Called every frame
void ABeacon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Funcion para realizar los cambios cuando el semaforo cambie de estado
void ABeacon::Switching(bool state) {
	if (state) {
		beaconState = BeaconState::Verde;
		SetLight();
		//switchCount++;
	}
	else {
		beaconState = BeaconState::Rojo;
		SetLight();
	}
}

//Funcion para cambiar el color del beacon
void ABeacon::SetLight()
{
	FLinearColor color;
	if (beaconState == BeaconState::Verde)
		color = continueColor;
	else
		color = stopColor;

	light->SetLightColor(color);
}

//Funcion para añadir el vehiculo detenido a la lista de vehiculos, y en caso de ser el primero, se le da paso
void ABeacon::StoppedVehicle(ADisplacer* displacer) {
	list.Add(displacer);
	if(!displacerMoving){
		GivePermission();
	}
	
}

//funcion para ejecutar el cambio de estado del semaforo y luego el timer para dar paso al siguiente desplazador
void ABeacon::AllowPermits() {
	Switching(true);
	GetWorldTimerManager().SetTimer(timerId, timerDel, 0.2f, false);
}

//Funcion para dar paso a un desplazador (First In First Out)
void ABeacon::GivePermission() {
	displacerMoving = false;
	if (list.Num() > 0) {
		//Da permiso y lo elimina de la lista
		list[0]->Permit();
		list.RemoveAt(0);
		displacerMoving = true;
		Switching(false);
	}
	
}



