// Copyright Epic Games, Inc. All Rights Reserved.

#include "NIRGameMode.h"
#include "NIRCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANIRGameMode::ANIRGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
