// Fill out your copyright notice in the Description page of Project Settings.

#include "FalconLaser.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Falcon/MillenniumFalcon.h"

// Sets default values
AFalconLaser::AFalconLaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>("root");
	SetRootComponent(root);

	beam1 = CreateDefaultSubobject<UStaticMeshComponent>("beamLeft");
	beam1->SetupAttachment(root);

	beam2 = CreateDefaultSubobject<UStaticMeshComponent>("beamRight");
	beam2->SetupAttachment(root);

	collider = CreateDefaultSubobject<UCapsuleComponent>("collider");
	collider->SetupAttachment(root);
}

// Called when the game starts or when spawned
void AFalconLaser::BeginPlay()
{
	Super::BeginPlay();
	
	totalSpeed = falconSpeed + GetActorForwardVector()*laserSpeed;

	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue,totalSpeed.ToString());

	collider->OnComponentBeginOverlap.AddDynamic(this, &AFalconLaser::OnBeginOverlap);

}

// Called every frame
void AFalconLaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(totalSpeed*DeltaTime, true);

}
void AFalconLaser::OnBeginOverlap(UPrimitiveComponent* thisComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AMillenniumFalcon>(OtherActor))
		return;

	if (explossionTemplate != nullptr)
	{
		FVector scale = FVector(12.f, 12.f, 12.f);
		FTransform t;
		t.SetScale3D(scale);
		t.SetLocation(GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explossionTemplate, t);
	}
	Destroy();
}

