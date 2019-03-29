// Fill out your copyright notice in the Description page of Project Settings.

#include "FalconLaser.h"


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


}

// Called when the game starts or when spawned
void AFalconLaser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFalconLaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

