// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "MenuInterface.h"

bool UMainMenu::Initialize()
{
	Super::Initialize();

	if (!ensure(HostButton!= nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostClicked);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinButtonClicked);

	if (!ensure(BackButton != nullptr)) return false;
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::BackButtonClicked);

	if (!ensure(JoinIPButton != nullptr)) return false;
	JoinIPButton->OnClicked.AddDynamic(this, &UMainMenu::JoinIPButtonClicked);

	return true;

}

void UMainMenu::HostClicked() 
{
	if (!ensure(MenuInterface!= nullptr)) return;

	MenuInterface->Host();
}
void UMainMenu::JoinButtonClicked()
{
	if (!ensure(MenuSwitcher!= nullptr)) return;
	if (!ensure(JoinMenu!= nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}
void UMainMenu::BackButtonClicked()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}
void UMainMenu::JoinIPButtonClicked()
{
	 if (!ensure(MenuInterface!= nullptr)) return;
	 if (!ensure(IPAddress != nullptr)) return;

	MenuInterface->Join(IPAddress->GetText().ToString());
}


