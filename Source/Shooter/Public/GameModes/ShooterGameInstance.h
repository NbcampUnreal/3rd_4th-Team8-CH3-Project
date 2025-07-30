#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"

UCLASS()
class SHOOTER_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UShooterGameInstance();
	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<FName> WaveLevelNames;

	UFUNCTION(BlueprintCallable)
	void NextWaveLevel();

};
