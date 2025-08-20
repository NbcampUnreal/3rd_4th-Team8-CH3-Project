// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ShooterController.h"

AShooterController::AShooterController()
{
	ShooterTeamID = FGenericTeamId(0);
}

FGenericTeamId AShooterController::GetGenericTeamId() const
{
	return ShooterTeamID;
}
