// Fill out your copyright notice in the Description page of Project Settings.


#include "PSO/WeaponGenerator.h"

#include "WeaponParticle.h"
#include "PSO/Weapon.h"

// Sets default values
AWeaponGenerator::AWeaponGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float AWeaponGenerator::NewInertiaCalculation(int Iteration)
{
	float MaxInertiaCoeff = 0.9f;
	float MinInertiaCoeff = 0.4f;
	return MaxInertiaCoeff - (MaxInertiaCoeff - MinInertiaCoeff) * Iteration / IterationNumber;
}

void AWeaponGenerator::InitSwarm()
{
	IdealDamage = FMath::RandRange(IdealDamageRange.X, IdealDamageRange.Y);
	float BestStartFitness = 0.0f;
	int BestStartID = 0;
	for (int i = 0; i < ParticleCount; i++)
	{
		WeaponParticle* particle = new WeaponParticle(DamageRange, MagazineSizeRange, ReloadSpeedRange, FireRateRange, RangeRange, RecoilRange, AccuracyRange);
		particle->SetPersonalBestDecision();
		particle->Fitness = FitnessFunction(*particle);
		particle->BastFitness = particle->Fitness;
		if (particle->Fitness > BestStartFitness)
		{
			BestStartFitness = particle->Fitness;
			BestStartID = i;
		}
		WeaponParticles.Add(particle);
	}
	GlobalBestWeapon = *WeaponParticles[BestStartID];
}

float AWeaponGenerator::RandomCoeff()
{
	return FMath::RandRange(0.0f, 1.0f);
}

float AWeaponGenerator::FitnessFunction(WeaponParticle& Weapon)
{

	float DenormDamage = Weapon.Unnormalization(Weapon.WeaponParticleCharacteristic.Damage, DamageRange.X, DamageRange.Y);
	float DenormMagazineSize = Weapon.Unnormalization(Weapon.WeaponParticleCharacteristic.MagazineSize, MagazineSizeRange.X, MagazineSizeRange.Y);
	float DenormReloadSpeed = Weapon.Unnormalization(Weapon.WeaponParticleCharacteristic.ReloadSpeed, ReloadSpeedRange.X, ReloadSpeedRange.Y);
	float DenormFireRate = Weapon.Unnormalization(Weapon.WeaponParticleCharacteristic.FireRate, FireRateRange.X, FireRateRange.Y);
	float DenormRange = Weapon.Unnormalization(Weapon.WeaponParticleCharacteristic.Range, RangeRange.X, RangeRange.Y);
	float DenormRecoil = Weapon.Unnormalization(Weapon.WeaponParticleCharacteristic.Recoil, RecoilRange.X, RecoilRange.Y);
	float DenormAccuracy = Weapon.Unnormalization(Weapon.WeaponParticleCharacteristic.Accuracy, AccuracyRange.X, AccuracyRange.Y);
	
	float Fitness = 0;
	
	FVector2D DPSRange = {(DamageRange.X*MagazineSizeRange.X)/(MagazineSizeRange.X*FireRateRange.X), (DamageRange.Y*MagazineSizeRange.Y)/(MagazineSizeRange.Y*FireRateRange.Y)};
	float DPSCurrent = (DenormDamage*DenormMagazineSize)/(DenormMagazineSize*DenormFireRate);
	float DPSNorm = Normalization(DPSCurrent, DPSRange.X, DPSRange.Y);
	
	float Error = FMath::Abs(DPSNorm - TargetDPS);
	//Fitness = 100.0f * (1.0f - Error);


	float NormDamage = Weapon.WeaponParticleCharacteristic.Damage;
	float NormRange = Weapon.WeaponParticleCharacteristic.Range;
	float NormFR = Weapon.WeaponParticleCharacteristic.FireRate;
	float NormRec = Weapon.WeaponParticleCharacteristic.Recoil;
	float NormRS = Weapon.WeaponParticleCharacteristic.ReloadSpeed;
	float NormMS = Weapon.WeaponParticleCharacteristic.MagazineSize;
	float NormAc = Weapon.WeaponParticleCharacteristic.Accuracy;

	Error = FMath::Abs(NormDamage - IdealDamage);
	Fitness += 100.0f * (1.0f - Error);
	
	float IdealRange = FMath::Pow(NormDamage, TargetDamageOnRange);
	IdealRange = FMath::Clamp(IdealRange, 0.0f, 1.0f);
	Error = FMath::Abs(NormRange - IdealRange);
	Fitness += 100.0f * (1.0f - Error);

	float IdealFR = FMath::Pow(NormDamage, TargetDamageOnFR);
	IdealFR = FMath::Clamp(IdealFR, 0.0f, 1.0f);
	Error = FMath::Abs(NormFR - IdealFR);
	Fitness += 100.0f * (1.0f - Error);

	float IdealRec = FMath::Pow(NormDamage, TargetDamageOnRecoil);
	IdealRec = FMath::Clamp(IdealRec, 0.0f, 1.0f);
	Error = FMath::Abs(NormRec - IdealRec);
	Fitness += 100.0f * (1.0f - Error);

	float IdealRS = FMath::Pow(NormDamage, TargetDamageOnRS);
	IdealRS = FMath::Clamp(IdealRS, 0.0f, 1.0f);
	Error = FMath::Abs(NormRS - IdealRS);
	Fitness += 100.0f * (1.0f - Error);

	float IdealMS = FMath::Pow(NormDamage, TargetDamageOnMS);
	IdealMS = FMath::Clamp(IdealMS, 0.0f, 1.0f);
	Error = FMath::Abs(1 - NormMS - IdealMS);
	Fitness += 100.0f * (1.0f - Error);

	float IdealAc = FMath::Pow(NormDamage, TargetDamageOnAccuracy);
	IdealAc = FMath::Clamp(IdealAc, 0.0f, 1.0f);
	Error = FMath::Abs(1 - NormAc - IdealAc);
	Fitness += 100.0f * (1.0f - Error);
	
	return Fitness;
}

float AWeaponGenerator::Normalization(float ParamToNormalization, float MinParamValue, float MaxParamValue)
{
	if (MaxParamValue - MinParamValue != 0)
	{
		float NormalizedParam = (ParamToNormalization - MinParamValue) / (MaxParamValue - MinParamValue);
		return NormalizedParam;
	}
	return 0;
}

float AWeaponGenerator::Unnormalization(float ParamToUnnormalization, float MinParamValue, float MaxParamValue)
{
	float UnnormalizedParam  = ParamToUnnormalization * (MaxParamValue - MinParamValue) + MinParamValue;
	return UnnormalizedParam;
}

void AWeaponGenerator::PSOAlgorithm()
{
	if (bIsFirstGeneration)
	{
		WeaponParticles.Empty();
		InitSwarm();
		bIsFirstGeneration = false;
	}
	
	for (int i = 0; i < IterationNumber; i++)
	{
		InertiaCoeff = NewInertiaCalculation(i);
		if (i == 0 && bIsFirstGeneration)
		{
			int BestWeaponParticleID = 0;
			for (int j = 0; j < ParticleCount-1; j++)
			{
				if (WeaponParticles[BestWeaponParticleID]->Fitness < WeaponParticles[j+1]->Fitness)
				{
					BestWeaponParticleID = j+1;
				}
			}
			GlobalBestWeapon = *WeaponParticles[BestWeaponParticleID];
			GlobalBestWeapon.WeaponBestParticleCharacteristic = WeaponParticles[BestWeaponParticleID]->WeaponBestParticleCharacteristic;
			GlobalBestWeapon.BastFitness = WeaponParticles[BestWeaponParticleID]->BastFitness;
			GlobalBestWeapon.Fitness = WeaponParticles[BestWeaponParticleID]->Fitness;
			bIsFirstGeneration = false;
		}

		int IDBestFitness = 0;
		for (int k = 0; k < ParticleCount; k++)
		{
			RandomCoeffFirst = RandomCoeff();
			RandomCoeffSecond = RandomCoeff();

			WeaponParticles[k]->CurrentVelocity = VelocityCount(*WeaponParticles[k]);
			WeaponParticles[k]->WeaponPreviousParticleCharacteristic = WeaponParticles[k]->WeaponParticleCharacteristic;
			WeaponParticles[k]->WeaponParticleCharacteristic = WeaponCharacteristic::Add(WeaponParticles[k]->WeaponParticleCharacteristic, WeaponParticles[k]->CurrentVelocity);

			WeaponParticles[k]->WeaponParticleCharacteristic.Damage = FMath::Clamp(WeaponParticles[k]->WeaponParticleCharacteristic.Damage, 0.0f, 1.0f);
			WeaponParticles[k]->WeaponParticleCharacteristic.MagazineSize = FMath::Clamp(WeaponParticles[k]->WeaponParticleCharacteristic.MagazineSize, 0.0f, 1.0f);
			WeaponParticles[k]->WeaponParticleCharacteristic.ReloadSpeed = FMath::Clamp(WeaponParticles[k]->WeaponParticleCharacteristic.ReloadSpeed, 0.0f, 1.0f);
			WeaponParticles[k]->WeaponParticleCharacteristic.FireRate = FMath::Clamp(WeaponParticles[k]->WeaponParticleCharacteristic.FireRate, 0.0f, 1.0f);
			WeaponParticles[k]->WeaponParticleCharacteristic.Range = FMath::Clamp(WeaponParticles[k]->WeaponParticleCharacteristic.Range, 0.0f, 1.0f);
			WeaponParticles[k]->WeaponParticleCharacteristic.Recoil = FMath::Clamp(WeaponParticles[k]->WeaponParticleCharacteristic.Recoil, 0.0f, 1.0f);
			WeaponParticles[k]->WeaponParticleCharacteristic.Accuracy = FMath::Clamp(WeaponParticles[k]->WeaponParticleCharacteristic.Accuracy, 0.0f, 1.0f);

			WeaponParticles[k]->Fitness = FitnessFunction(*WeaponParticles[k]);
			WeaponParticles[k]->PreviousVelocity = WeaponParticles[k]->CurrentVelocity;
			
			if (WeaponParticles[k]->Fitness > WeaponParticles[k]->BastFitness)
			{
				WeaponParticles[k]->BastFitness = WeaponParticles[k]->Fitness;
				WeaponParticles[k]->WeaponBestParticleCharacteristic = WeaponParticles[k]->WeaponParticleCharacteristic;
			}
			
			if (WeaponParticles[IDBestFitness]->BastFitness < WeaponParticles[k]->BastFitness)
			{
				IDBestFitness = k;
			}
			
		}
		
		//if (WeaponParticles[IDBestFitness]->BastFitness > GlobalBestWeapon.BastFitness)
		//{
		//	GlobalBestWeapon = *WeaponParticles[IDBestFitness];
		//	BestFitness = WeaponParticles[IDBestFitness]->Fitness;
		//}
		if (WeaponParticles[IDBestFitness]->BastFitness > GlobalBestWeapon.BastFitness)
		{
			GlobalBestWeapon.WeaponBestParticleCharacteristic = WeaponParticles[IDBestFitness]->WeaponBestParticleCharacteristic;
			GlobalBestWeapon.WeaponParticleCharacteristic = WeaponParticles[IDBestFitness]->WeaponBestParticleCharacteristic;
			GlobalBestWeapon.BastFitness = WeaponParticles[IDBestFitness]->BastFitness;
			GlobalBestWeapon.Fitness = WeaponParticles[IDBestFitness]->Fitness;
		}
	}

	GeneratedWeapon->Damage = GlobalBestWeapon.Unnormalization(GlobalBestWeapon.WeaponBestParticleCharacteristic.Damage, DamageRange.X, DamageRange.Y);
	GeneratedWeapon->MagazineSize = GlobalBestWeapon.Unnormalization(GlobalBestWeapon.WeaponBestParticleCharacteristic.MagazineSize, MagazineSizeRange.X, MagazineSizeRange.Y);
	GeneratedWeapon->ReloadSpeed = GlobalBestWeapon.Unnormalization(GlobalBestWeapon.WeaponBestParticleCharacteristic.ReloadSpeed, ReloadSpeedRange.X, ReloadSpeedRange.Y);
	GeneratedWeapon->FireRate = GlobalBestWeapon.Unnormalization(GlobalBestWeapon.WeaponBestParticleCharacteristic.FireRate, FireRateRange.X, FireRateRange.Y);
	GeneratedWeapon->Range = GlobalBestWeapon.Unnormalization(GlobalBestWeapon.WeaponBestParticleCharacteristic.Range, RangeRange.X, RangeRange.Y);
	GeneratedWeapon->Recoil = GlobalBestWeapon.Unnormalization(GlobalBestWeapon.WeaponBestParticleCharacteristic.Recoil, RecoilRange.X, RecoilRange.Y);
	GeneratedWeapon->Accuracy = GlobalBestWeapon.Unnormalization(GlobalBestWeapon.WeaponBestParticleCharacteristic.Accuracy, AccuracyRange.X, AccuracyRange.Y);

}

WeaponCharacteristic AWeaponGenerator::VelocityCount(WeaponParticle& Weapon)
{
	float MaxVel = 0.03f;
	WeaponCharacteristic FirstPart = WeaponCharacteristic::MultiplyOnCoeff(Weapon.PreviousVelocity, InertiaCoeff);
	WeaponCharacteristic SecondPart = WeaponCharacteristic::MultiplyOnCoeff(WeaponCharacteristic::Subtraction(Weapon.WeaponBestParticleCharacteristic, Weapon.WeaponPreviousParticleCharacteristic), VelocityPersonalBest*RandomCoeffFirst);
	WeaponCharacteristic ThirdPart = WeaponCharacteristic::MultiplyOnCoeff(WeaponCharacteristic::Subtraction(GlobalBestWeapon.WeaponParticleCharacteristic, Weapon.WeaponPreviousParticleCharacteristic), VelocityGlobalBest*RandomCoeffSecond);
	WeaponCharacteristic Velocity = WeaponCharacteristic::Add(FirstPart, SecondPart);
	Velocity = WeaponCharacteristic::Add(Velocity, ThirdPart);
	Velocity.Damage = FMath::Clamp(Velocity.Damage, -MaxVel, MaxVel);
	Velocity.MagazineSize = FMath::Clamp(Velocity.MagazineSize, -MaxVel, MaxVel);
	Velocity.ReloadSpeed = FMath::Clamp(Velocity.ReloadSpeed, -MaxVel, MaxVel);
	Velocity.Range = FMath::Clamp(Velocity.Range, -MaxVel, MaxVel);
	Velocity.Recoil = FMath::Clamp(Velocity.Recoil, -MaxVel, MaxVel);
	Velocity.Accuracy = FMath::Clamp(Velocity.Accuracy, -MaxVel, MaxVel);
	return Velocity;
}

