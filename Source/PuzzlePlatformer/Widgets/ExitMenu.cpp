// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitMenu.h"
#include "Components/Button.h"

bool UExitMenu::Initialize()
{
	Super::Initialize();

	if (!ensure(MainMenuButton != nullptr)) return false;
	MainMenuButton->OnClicked.AddDynamic(this, &UExitMenu::MainMenuButtonClicked);

	if (!ensure(ExitGameButton != nullptr)) return false;
	ExitGameButton->OnClicked.AddDynamic(this, &UExitMenu::ExitGameButtonClicked);

	return true;
}
void UExitMenu::MainMenuButtonClicked()
{

}
void UExitMenu::ExitGameButtonClicked()
{

}