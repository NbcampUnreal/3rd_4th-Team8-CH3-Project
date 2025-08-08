#include "GameModes/ShooterGameStateBase.h"
#include "GameModes/ShooterBaseGameMode.h"

AShooterGameStateBase::AShooterGameStateBase()
{
	TotalEnemy = 0;
	AliveEnemyCount = 0;
}

void AShooterGameStateBase::SetAliveEnemyCount(int32 Count)
{
	if (TotalEnemy == 0)
	{
		TotalEnemy = Count;
		AliveEnemyCount = TotalEnemy;
	}
	else
	{
		AliveEnemyCount = AliveEnemyCount - (TotalEnemy-Count);
		TotalEnemy = Count;
	}
	
}

void AShooterGameStateBase::OnEnemyDied()
{
	if (AliveEnemyCount > 0)
	{
		AliveEnemyCount = FMath::Max(AliveEnemyCount - 1, 0);
	}

	UE_LOG(LogTemp, Warning, TEXT("The enemy is dead  (%d / %d)"), AliveEnemyCount, TotalEnemy);

	if (AliveEnemyCount <= 0 && TotalEnemy > 0)
	{
		AShooterBaseGameMode* GameMode = GetWorld()->GetAuthGameMode<AShooterBaseGameMode>();
		if (GameMode)
		{
			TotalEnemy = 0;
			GameMode->OnAllEnemiesDefeated();
		}
	}
}

