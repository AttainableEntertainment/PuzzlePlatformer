// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(class IMenuInterface* Interface);
	void Setup();


protected:
	virtual bool Initialize() override;
	class IMenuInterface* MenuInterface;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	UPROPERTY()
	TSubclassOf<class UUserWidget> MenuClass;


};
