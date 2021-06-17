// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "ExitMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UExitMenu : public UMenuBase
{
	GENERATED_BODY()
public:
protected:
	virtual bool Initialize() override;
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitGameButton;

	UFUNCTION()
	void CancelButtonClicked();

	UFUNCTION()
	void ExitGameButtonClicked();
};
