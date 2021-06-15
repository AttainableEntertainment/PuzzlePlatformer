// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuBase.h"
#include "MenuInterface.h"


void UMenuBase::Setup()
{
	this->AddToViewport();
	this->bIsFocusable = true;

	APlayerController* PlayerController;
	PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(this->TakeWidget());
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}
void UMenuBase::SetMenuInterface(IMenuInterface* Interface)
{
	this->MenuInterface = Interface;
}
void UMenuBase::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	APlayerController* PlayerController;
	PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;

}