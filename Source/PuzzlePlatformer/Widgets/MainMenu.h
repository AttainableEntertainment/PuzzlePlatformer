// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()
public:

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddress;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinIPButton;



	UFUNCTION()
	void HostClicked();
	UFUNCTION()
	void JoinButtonClicked();
	UFUNCTION()
	void BackButtonClicked();
	UFUNCTION()
	void JoinIPButtonClicked();
	UFUNCTION()
	void QuitButtonClicked();



};
