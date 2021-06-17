// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MenuInterface.h"

bool UExitMenu::Initialize()
{
	Super::Initialize();

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UExitMenu::CancelButtonClicked);

	if (!ensure(ExitGameButton != nullptr)) return false;
	ExitGameButton->OnClicked.AddDynamic(this, &UExitMenu::ExitGameButtonClicked);

	return true;
}
void UExitMenu::CancelButtonClicked()
{
	RemoveFromViewport();
	OnLevelRemovedFromWorld(GetWorld()->GetCurrentLevel(), GetWorld());
}
void UExitMenu::ExitGameButtonClicked()
{
	if (!ensure(MenuInterface != nullptr)) return;

	MenuInterface->LoadMainMenu();
}