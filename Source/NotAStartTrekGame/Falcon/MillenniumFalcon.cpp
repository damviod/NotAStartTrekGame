// Fill out your copyright notice in the Description page of Project Settings.

#include "MillenniumFalcon.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "HUD/BaseFalconHUD.h"
#include "Kismet/GameplayStatics.h"

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
	GetWorld()->DebugDrawTraceTag = "LINE_TRACE_AIM";

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
	PlayerInputComponent->BindAxis("LookUp", this, &AMillenniumFalcon::LookUp);
	PlayerInputComponent->BindAxis("LookAround", this, &AMillenniumFalcon::LookAround);
	PlayerInputComponent->BindAction("LockCam", EInputEvent::IE_Pressed, this, &AMillenniumFalcon::LockCam);
	PlayerInputComponent->BindAction("LockCam", EInputEvent::IE_Released, this, &AMillenniumFalcon::UnlockCam);

}

void AMillenniumFalcon::PostInitProperties()
{
	Super::PostInitProperties();

	initArmRotation = arm->GetRelativeTransform().Rotator();
	initCamRotation = cam->GetRelativeTransform().Rotator();
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

void AMillenniumFalcon::LookUp(float axisValue)
{
	if (IsCamLocked)
	{
		cam->AddRelativeRotation(FRotator(axisValue*lookupRate*GetWorld()->DeltaTimeSeconds, 0.f, 0.f));
		Aim();
	}
	else
	{

		FRotator newR = FMath::RInterpTo(cam->GetRelativeTransform().Rotator(), initCamRotation, GetWorld()->DeltaTimeSeconds, 10.f);
		cam->SetRelativeRotation(newR);
	}
}
void AMillenniumFalcon::LookAround(float axisValue)
{
	if (IsCamLocked)
	{
		arm->AddRelativeRotation(FRotator(0.f, axisValue*aroundRate*GetWorld()->DeltaTimeSeconds, 0.f));
		Aim();
	}
	else
	{
		
		FRotator newR = FMath::RInterpTo(arm->GetRelativeTransform().Rotator(), initArmRotation, GetWorld()->DeltaTimeSeconds, 10.f);
		arm->SetRelativeRotation(newR);
	}
}
void AMillenniumFalcon::LockCam()
{
	IsCamLocked = true;


	APlayerController *pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ABaseFalconHUD * hud = (ABaseFalconHUD *) pc->GetHUD();
	hud->SetFalconHUDVisibility(true);

	/*
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString("Bloqueo"));
		*/

}

void AMillenniumFalcon::UnlockCam()
{
	IsCamLocked = false;

	APlayerController *pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ABaseFalconHUD * hud = (ABaseFalconHUD *)pc->GetHUD();
	hud->SetFalconHUDVisibility(false);
}

void AMillenniumFalcon::Aim()
{
	FHitResult hit;
	FVector start = cam->GetComponentLocation();
	FVector end = start + cam->GetForwardVector()*laserRange;
	FCollisionQueryParams qp = FCollisionQueryParams::DefaultQueryParam;
	qp.AddIgnoredActor(this);

#ifdef UE_BUILD_DEBUG

	qp.TraceTag = "LINE_TRACE_AIM";

#endif // UE_BUILD_DEBUG

	bool isHit = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Camera, qp);

	if (isHit)
	{
		APlayerController *pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ABaseFalconHUD * hud = (ABaseFalconHUD *)pc->GetHUD();
		hud->SetTargetDistanceText(hit.Distance);
	}
}

