// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Widgets/MenuInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	UFUNCTION(Exec,BlueprintCallable)
	void LoadMenu(TSubclassOf<class UUserWidget> WidgetClass);

	UFUNCTION(Exec)
	void Host() override;



	UFUNCTION(Exec)
	void Join(const FString& Address) override;

	UFUNCTION(Exec)
	void LoadMainMenu() override;

private:
	UPROPERTY()
	TSubclassOf<class UUserWidget> MenuClass;

	UPROPERTY()
	TSubclassOf<class UUserWidget> ExitMenuClass;

	class UMenuBase* Widget;

	IOnlineSessionPtr SessionInterface;

	void CreateSession();

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
};
