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
	if (MenuInterface != nullptr)
	{
		MenuInterface->RequestRefresh();
	}


}
void UMainMenu::BackButtonClicked()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}
void UMainMenu::JoinIPButtonClicked()
{
	//if (!ensure(MenuInterface!= nullptr)) return;
	//if (!ensure(IPAddress != nullptr)) return;
	MenuInterface->Join("");

}
void UMainMenu::QuitButtonClicked()
{
	GetOwningPlayer()->ConsoleCommand("Quit");
}
/**
 * @brief Sets the server list inside the menu
 * @param ServerNames list of server names
*/
void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
	//Get world pointer and check if null
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	//clears list before setting it to avoid repeats 
	ServerList->ClearChildren();

	for (const FString& ServerName : ServerNames)
	{
		//Creates widget server row 
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerClass);
		if (!ensure(Row != nullptr)) return;

		//set server row text box name
		Row->ServerName->SetText(FText::FromString(ServerName));

		//adds server row widget to panelwidget scrollbox serverlist
		ServerList->AddChild(Row);
	}

}


