// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "MenuInterface.h"
#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/UserInterface/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;
	ServerClass = ServerRowBPClass.Class;
}
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

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonClicked);

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
	// if (!ensure(MenuInterface!= nullptr)) return;
	// if (!ensure(IPAddress != nullptr)) return;
	//MenuInterface->Join(IPAddress->GetText().ToString());
	UWorld* World=this->GetWorld();
	if (!ensure(World != nullptr)) return;

	UServerRow* Row= CreateWidget<UServerRow>(World, ServerClass);
	if (!ensure(Row != nullptr)) return;

	//set server row textbox name

	Row->ServerName->SetText(FText::FromString(TEXT("Test Text")));

	ServerList->AddChild(Row);
}
void UMainMenu::QuitButtonClicked()
{
	GetOwningPlayer()->ConsoleCommand("Quit");
}


