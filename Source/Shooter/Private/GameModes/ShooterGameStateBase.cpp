#include "GameModes/ShooterGameStateBase.h"
#include "GameModes/ShooterBaseGameMode.h"

AShooterGameStateBase::AShooterGameStateBase()
{
	TotalEnemy = 0;
	AliveEnemyCount = 0;
}

void AShooterGameStateBase::SetAliveEnemyCount(int32 Count)
{
	TotalEnemy = Count;
	AliveEnemyCount = TotalEnemy;
}

void AShooterGameStateBase::OnEnemyDied()
{
	if (AliveEnemyCount > 0)
	{
		AliveEnemyCount--;
	}

	UE_LOG(LogTemp, Warning, TEXT("The enemy is dead  (%d / %d)"), AliveEnemyCount, TotalEnemy);

	if (AliveEnemyCount <= 0 && TotalEnemy > 0)
	{
		AShooterBaseGameMode* GameMode = GetWorld()->GetAuthGameMode<AShooterBaseGameMode>();
		if (GameMode)
		{
			GameMode->OnAllEnemiesDefeated();
		}
	}
}

