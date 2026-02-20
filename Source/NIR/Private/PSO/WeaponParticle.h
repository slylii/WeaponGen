#pragma once

struct WeaponCharacteristic
{
	float Damage = 0.0f;
	float MagazineSize = 0.0f;
	float ReloadSpeed = 0.0f;
	float FireRate = 0.0f;
	float Range = 0.0f;
	float Recoil = 0.0f;
	float Accuracy = 0.0f;

	static WeaponCharacteristic MultiplyOnCoeff(WeaponCharacteristic CharacteristicToMultiply, float Coeff);
	static WeaponCharacteristic Subtraction(WeaponCharacteristic FirstCharacteristic, WeaponCharacteristic SecondCharacteristic);
	static WeaponCharacteristic Add(WeaponCharacteristic FirstCharacteristic, WeaponCharacteristic SecondCharacteristic);
};


class WeaponParticle
{
public:
	WeaponParticle(FVector2D DamageRange,
		FVector2D MagazineSizeRange,
		FVector2D ReloadSpeedRange,
		FVector2D FireRateRange,
		FVector2D RangeRange,
		FVector2D RecoilRange,
		FVector2D AccuracyRange);
	WeaponParticle();
	
	float Normalization(float ParamToNormalization, float MinParamValue, float MaxParamValue);
	float Unnormalization(float ParamToUnnormalization, float MinParamValue, float MaxParamValue);
	void SetPersonalBestDecision();
	float DPSCount();

	

	WeaponCharacteristic WeaponParticleCharacteristic = {0.0f, 0, 0.0f, 0.0f, 0, 0.0f, 0};
	WeaponCharacteristic WeaponPreviousParticleCharacteristic = {0.0f, 0, 0.0f, 0.0f, 0, 0.0f, 0};
	WeaponCharacteristic WeaponBestParticleCharacteristic = {0.0f, 0, 0.0f, 0.0f, 0, 0.0f, 0};
	WeaponCharacteristic CurrentVelocity = {0.0f, 0, 0.0f, 0.0f, 0, 0.0f, 0};
	WeaponCharacteristic PreviousVelocity = {0.0f, 0, 0.0f, 0.0f, 0, 0.0f, 0};
	
	float Fitness = 0.0f;
	float BastFitness = 0.0f;
};
