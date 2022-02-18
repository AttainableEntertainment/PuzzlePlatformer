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

	UFUNCTION(Exec)
	void RequestRefresh() override;

private:
	UPROPERTY()
	TSubclassOf<class UUserWidget> MenuClass;

	UPROPERTY()
	TSubclassOf<class UUserWidget> ExitMenuClass;

	class UMainMenu* MainMenu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void CreateSession();

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);
};
