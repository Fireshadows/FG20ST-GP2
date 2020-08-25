// Copyright Epic Games, Inc. All Rights Reserved.

#include "FGGP2GameMode.h"
#include "FGGP2PlayerController.h"
#include "FGGP2Pawn.h"

AFGGP2GameMode::AFGGP2GameMode()
{
	// no pawn by default
	DefaultPawnClass = AFGGP2Pawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AFGGP2PlayerController::StaticClass();
}
