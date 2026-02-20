// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSO/WeaponParticle.h"
#include "WeaponGenerator.generated.h"

class AWeapon;

UCLASS()
class NIR_API AWeaponGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponGenerator();
	
	TArray<WeaponParticle*> WeaponParticles;

	UFUNCTION(BlueprintCallable)
	void PSOAlgorithm();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AWeapon* GeneratedWeapon = nullptr;
	
	WeaponParticle GlobalBestWeapon;

	UPROPERTY(EditAnywhere)
	int IterationNumber = 0;
	UPROPERTY(EditAnywhere)
	float InertiaCoeff = 0.9f;
	UPROPERTY(EditAnywhere)
	int ParticleCount = 30;
	UPROPERTY(EditAnywhere)
	float VelocityPersonalBest = 1.5f;
	UPROPERTY(EditAnywhere)
	float VelocityGlobalBest = 1.5f;
	UPROPERTY(EditAnywhere)
	float RandomCoeffFirst = 1.0f;
	UPROPERTY(EditAnywhere)
	float RandomCoeffSecond = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFirstGeneration = true;

	UPROPERTY(EditAnywhere)
	float BestFitness = 0.0f;

	
	UPROPERTY(EditAnywhere)
	float TargetDamageOnMS = 0.5f;
	UPROPERTY(EditAnywhere)
	float TargetDamageOnFR = 0.5f;
	

	UPROPERTY(EditAnywhere)
	float TargetDPS = 0.5f;
	UPROPERTY(EditAnywhere)
	float TargetDamageOnAccuracy = 0.5f;
	UPROPERTY(EditAnywhere)
	float TargetDamageOnRecoil = 0.5f;
	UPROPERTY(EditAnywhere)
	float TargetDamageOnRS = 0.5f;
	UPROPERTY(EditAnywhere)
	FVector2D IdealDamageRange = {0.5f, 0.6f};
	UPROPERTY(EditAnywhere)
	float IdealDamage = 0.5f;
	UPROPERTY(EditAnywhere)
	float TargetDamageOnRange = 0.5f;

	
	UPROPERTY(EditAnywhere)
	FVector2D DamageRange = FVector2D(5, 50);
	UPROPERTY(EditAnywhere)
	FVector2D MagazineSizeRange = FVector2D(6, 30);
	UPROPERTY(EditAnywhere)
	FVector2D ReloadSpeedRange = FVector2D(0.5, 3);
	UPROPERTY(EditAnywhere)
	FVector2D FireRateRange = FVector2D(0.05, 2);
	UPROPERTY(EditAnywhere)
	FVector2D RangeRange = FVector2D(3, 30);
	UPROPERTY(EditAnywhere)
	FVector2D RecoilRange = FVector2D(0.05, 1.5);
	UPROPERTY(EditAnywhere)
	FVector2D AccuracyRange = FVector2D(5, 100);

	float Normalization(float ParamToNormalization, float MinParamValue, float MaxParamValue);
	float Unnormalization(float ParamToUnnormalization, float MinParamValue, float MaxParamValue);
	float NewInertiaCalculation(int Iteration);
	void InitSwarm();
	float RandomCoeff();
	float FitnessFunction(WeaponParticle& Weapon);
	WeaponCharacteristic VelocityCount(WeaponParticle& Weapon);
};
