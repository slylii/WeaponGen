// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class NIR_API AWeapon : public AActor
{
	GENERATED_BODY()

	AWeapon();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Damage = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MagazineSize = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ReloadSpeed = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FireRate = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Range = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Recoil = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Accuracy = 0;

};
