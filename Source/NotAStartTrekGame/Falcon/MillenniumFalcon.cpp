// Fill out your copyright notice in the Description page of Project Settings.

#include "MillenniumFalcon.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"

//#include "ConstructorHelpers.h"

// Sets default values
AMillenniumFalcon::AMillenniumFalcon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Para cargar un asset desde cpp, podemos hacerlo desde el código
	//indicando el path, pero si nos cambian el asset de directorio
	//dejaría de funcionar. Muchas veces es mas practico dejarlo
	//para la clase derivada en blueprints. Como en este caso,
	//que comentamos el codigo para desactivarlo.
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> Pepe(TEXT("/Game/StarterContent/Props/SM_Bush"));

	falconMesh = CreateDefaultSubobject<UStaticMeshComponent>("falconMesh");
	//falconMesh->SetStaticMesh(Pepe.Object);

	SetRootComponent(falconMesh);
	arm = CreateDefaultSubobject<USpringArmComponent>("arm");
	arm->SetupAttachment(falconMesh);
	cam = CreateDefaultSubobject<UCameraComponent>("cam");
	cam->SetupAttachment(arm);

	powerMax = 100;
}

// Called when the game starts or when spawned
void AMillenniumFalcon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMillenniumFalcon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Movimiento de rotacion
	FRotator rot(currentPitch, currentYaw, currentRoll);
	rot *= DeltaTime;
	falconMesh->AddLocalRotation(rot); // FRotator(currentPitch*DeltaTime, currentYaw*DeltaTime, currentRoll*DeltaTime));

	//Movimiento lineal
	currentSpeed += currentPower * DeltaTime;
	currentSpeed = FMath::Min(currentSpeed, speedMax);

	falconMesh->AddLocalOffset(FVector(currentSpeed*DeltaTime, 0.f, 0.f));
}

// Called to bind functionality to input
void AMillenniumFalcon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Power", this, &AMillenniumFalcon::Power);
	PlayerInputComponent->BindAxis("Yaw", this, &AMillenniumFalcon::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &AMillenniumFalcon::Pitch);
}

void AMillenniumFalcon::PostInitProperties()
{
	Super::PostInitProperties();

}

void AMillenniumFalcon::Power(float axisValue)
{
	if (FMath::Abs(axisValue) < 0.1f)
	{
		currentSpeed -= linearDragRate * currentSpeed*GetWorld()->DeltaTimeSeconds;
	}
	currentPower = axisValue * powerMax;

}

void AMillenniumFalcon::Yaw(float axisValue)
{
	if (FMath::Abs(axisValue) < 0.1f)
		currentRoll = -falconMesh->GetComponentRotation().Roll;
	else
		currentRoll = currentYaw*0.7f;

	currentYaw = FMath::FInterpTo(currentYaw, axisValue*yawMax, GetWorld()->DeltaTimeSeconds, 10.f);
}

void AMillenniumFalcon::Pitch(float axisValue)
{
	currentPitch = FMath::FInterpTo(currentPitch, axisValue*pitchMax, GetWorld()->DeltaTimeSeconds, 10.f);
}

