// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystem.h"
#include "FalconLaser.generated.h"

UCLASS()
class NOTASTARTTREKGAME_API AFalconLaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFalconLaser();

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	USceneComponent *root;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UStaticMeshComponent *beam1;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UStaticMeshComponent *beam2;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UCapsuleComponent *collider;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Laser")
	float laserSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Effects")
	UParticleSystem *explossionTemplate;

	FVector falconSpeed;
	FVector totalSpeed;

	FVector initSpeed;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* thisComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
};