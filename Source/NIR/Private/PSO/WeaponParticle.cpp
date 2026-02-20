#include "WeaponParticle.h"

WeaponCharacteristic WeaponCharacteristic::MultiplyOnCoeff(WeaponCharacteristic CharacteristicToMultiply, float Coeff)
{
	CharacteristicToMultiply.Damage *= Coeff;
	CharacteristicToMultiply.MagazineSize *= Coeff;
	CharacteristicToMultiply.ReloadSpeed *= Coeff;
	CharacteristicToMultiply.FireRate *= Coeff;
	CharacteristicToMultiply.Range *= Coeff;
	CharacteristicToMultiply.Recoil *= Coeff;
	CharacteristicToMultiply.Accuracy *= Coeff;
	return CharacteristicToMultiply;
}

WeaponCharacteristic WeaponCharacteristic::Subtraction(WeaponCharacteristic FirstCharacteristic, WeaponCharacteristic SecondCharacteristic)
{
	WeaponCharacteristic NewCharacteristic = FirstCharacteristic;
	
	NewCharacteristic.Damage -= SecondCharacteristic.Damage;
	//NewCharacteristic.Damage = FMath::Clamp(NewCharacteristic.Damage, 0.0f, 1.0f);
	
	NewCharacteristic.MagazineSize -= SecondCharacteristic.MagazineSize;
	//NewCharacteristic.MagazineSize = FMath::Clamp(NewCharacteristic.MagazineSize, 0.0f, 1.0f);
	
	NewCharacteristic.ReloadSpeed -= SecondCharacteristic.ReloadSpeed;
	//NewCharacteristic.ReloadSpeed = FMath::Clamp(NewCharacteristic.ReloadSpeed, 0.0f, 1.0f);
	
	NewCharacteristic.FireRate -= SecondCharacteristic.FireRate;
	//NewCharacteristic.FireRate = FMath::Clamp(NewCharacteristic.FireRate, 0.0f, 1.0f);
	
	NewCharacteristic.Range -= SecondCharacteristic.Range;
	//NewCharacteristic.Range = FMath::Clamp(NewCharacteristic.Range, 0.0f, 1.0f);
	
	NewCharacteristic.Recoil -= SecondCharacteristic.Recoil;
	//NewCharacteristic.Recoil = FMath::Clamp(NewCharacteristic.Recoil, 0.0f, 1.0f);

	NewCharacteristic.Accuracy -= SecondCharacteristic.Accuracy;
	//NewCharacteristic.Accuracy = FMath::Clamp(NewCharacteristic.Accuracy, 0.0f, 1.0f);
	
	return NewCharacteristic;
}

WeaponCharacteristic WeaponCharacteristic::Add(WeaponCharacteristic FirstCharacteristic,
	WeaponCharacteristic SecondCharacteristic)
{
	WeaponCharacteristic NewCharacteristic = FirstCharacteristic;
	
	NewCharacteristic.Damage += SecondCharacteristic.Damage;
	//NewCharacteristic.Damage = FMath::Clamp(NewCharacteristic.Damage, 0.0f, 1.0f);
	
	NewCharacteristic.MagazineSize += SecondCharacteristic.MagazineSize;
	//NewCharacteristic.MagazineSize = FMath::Clamp(NewCharacteristic.MagazineSize, 0.0f, 1.0f);
	
	NewCharacteristic.ReloadSpeed += SecondCharacteristic.ReloadSpeed;
	//NewCharacteristic.ReloadSpeed = FMath::Clamp(NewCharacteristic.ReloadSpeed, 0.0f, 1.0f);
	
	NewCharacteristic.FireRate += SecondCharacteristic.FireRate;
	//NewCharacteristic.FireRate = FMath::Clamp(NewCharacteristic.FireRate, 0.0f, 1.0f);
	
	NewCharacteristic.Range += SecondCharacteristic.Range;
	//NewCharacteristic.Range = FMath::Clamp(NewCharacteristic.Range, 0.0f, 1.0f);
	
	NewCharacteristic.Recoil += SecondCharacteristic.Recoil;
	//NewCharacteristic.Recoil = FMath::Clamp(NewCharacteristic.Recoil, 0.0f, 1.0f);

	NewCharacteristic.Accuracy += SecondCharacteristic.Accuracy;
	//NewCharacteristic.Accuracy = FMath::Clamp(NewCharacteristic.Accuracy, 0.0f, 1.0f);

	
	return NewCharacteristic;
}

WeaponParticle::WeaponParticle(FVector2D DamageRange,
                               FVector2D MagazineSizeRange,
                               FVector2D ReloadSpeedRange,
                               FVector2D FireRateRange,
                               FVector2D RangeRange,
                               FVector2D RecoilRange,
                               FVector2D AccuracyRange)
{
	WeaponParticleCharacteristic.Damage = Normalization(FMath::RandRange(DamageRange.X, DamageRange.Y),
		DamageRange.X, DamageRange.Y);
	WeaponParticleCharacteristic.MagazineSize = Normalization(FMath::RandRange(MagazineSizeRange.X, MagazineSizeRange.Y),
		MagazineSizeRange.X, MagazineSizeRange.Y);
	WeaponParticleCharacteristic.ReloadSpeed = Normalization(FMath::RandRange(ReloadSpeedRange.X, ReloadSpeedRange.Y),
		ReloadSpeedRange.X, ReloadSpeedRange.Y);
	WeaponParticleCharacteristic.FireRate = Normalization(FMath::RandRange(FireRateRange.X, FireRateRange.Y),
		FireRateRange.X, FireRateRange.Y);
	WeaponParticleCharacteristic.Range = Normalization(FMath::RandRange(RangeRange.X, RangeRange.Y),
		RangeRange.X, RangeRange.Y);
	WeaponParticleCharacteristic.Recoil = Normalization(FMath::RandRange(RecoilRange.X, RecoilRange.Y),
		RecoilRange.X, RecoilRange.Y);
	WeaponParticleCharacteristic.Accuracy = Normalization(FMath::RandRange(AccuracyRange.X, AccuracyRange.Y),
		AccuracyRange.X, AccuracyRange.Y);

	WeaponPreviousParticleCharacteristic = WeaponParticleCharacteristic;
}

WeaponParticle::WeaponParticle()
{
}

void WeaponParticle::SetPersonalBestDecision()
{
	WeaponBestParticleCharacteristic.Damage = WeaponParticleCharacteristic.Damage;
	WeaponBestParticleCharacteristic.MagazineSize = WeaponParticleCharacteristic.MagazineSize;
	WeaponBestParticleCharacteristic.ReloadSpeed = WeaponParticleCharacteristic.ReloadSpeed;
	WeaponBestParticleCharacteristic.FireRate = WeaponParticleCharacteristic.FireRate;
	WeaponBestParticleCharacteristic.Range = WeaponParticleCharacteristic.Range;
	WeaponBestParticleCharacteristic.Recoil = WeaponParticleCharacteristic.Recoil;
	WeaponBestParticleCharacteristic.Accuracy = WeaponParticleCharacteristic.Accuracy;
}

float WeaponParticle::DPSCount()
{
	float DPS = (WeaponParticleCharacteristic.Damage * WeaponParticleCharacteristic.MagazineSize) /
		(WeaponParticleCharacteristic.MagazineSize * WeaponParticleCharacteristic.FireRate + WeaponParticleCharacteristic.ReloadSpeed);
	return DPS;
}

float WeaponParticle::Normalization(float ParamToNormalization, float MinParamValue, float MaxParamValue)
{
	if (MaxParamValue - MinParamValue != 0)
	{
		float NormalizedParam = (ParamToNormalization - MinParamValue) / (MaxParamValue - MinParamValue);
		return NormalizedParam;
	}
	return 0;
}

float WeaponParticle::Unnormalization(float ParamToUnnormalization, float MinParamValue, float MaxParamValue)
{
	float UnnormalizedParam  = ParamToUnnormalization * (MaxParamValue - MinParamValue) + MinParamValue;
	return UnnormalizedParam;
}
