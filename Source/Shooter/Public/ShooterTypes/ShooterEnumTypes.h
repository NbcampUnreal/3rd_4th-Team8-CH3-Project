#pragma once

UENUM()
enum class EShooterConfirmType : uint8
{
	ESC_Yes,
	ESC_No,
};

UENUM()
enum class EShooterSuccessType : uint8
{
	ESC_Successful,
	ESC_Failed,
};

UENUM()
enum class EShooterValidType : uint8
{
	EWT_Valid,
	EWT_Invalid,
};
