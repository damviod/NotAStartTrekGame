// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MillenniumFalcon.generated.h"

UCLASS()
class NOTASTARTTREKGAME_API AMillenniumFalcon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMillenniumFalcon();

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	UStaticMeshComponent *falconMesh;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	UStaticMeshComponent *falconCanion;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	USceneComponent *laserSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	USpringArmComponent *arm;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UCameraComponent *cam;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="Falcon movement")
	float powerMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Transient, Category = "Falcon movement")
	float currentPower;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Falcon movement")
	float speedMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Transient, Category = "Falcon movement")
	float currentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Falcon movement")
	float linearDragRate;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Falcon movement")
	float pitchMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Transient, Category = "Falcon movement")
	float currentPitch;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Falcon movement")
	float yawMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Transient, Category = "Falcon movement")
	float currentYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Transient, Category = "Falcon movement")
	float currentRoll;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Transient, Category = "Aim")
	bool IsCamLocked;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Aim")
	float aroundRate = 180;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Aim")
	float lookupRate = 180;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Aim")
	float laserRange;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Effects")
	TSubclassOf<UCameraShake> falconCameraShakeTemplate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitProperties() override;
	
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	//UFUNCTION()
	//void OnBeginOverlap(UPrimitiveComponent* thisComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:

	void Power(float);
	void Yaw(float);
	void Pitch(float);
	void LookUp(float);
	void LookAround(float);
	void LockCam();
	void UnlockCam();
	void Aim();
	void Shoot();

	FRotator initArmRotation;
	FRotator initCamRotation;
};
