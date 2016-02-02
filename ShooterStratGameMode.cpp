// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterStrat.h"
#include "ShooterStratGameMode.h"




AShooterStratGameMode::AShooterStratGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/PlayerCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}