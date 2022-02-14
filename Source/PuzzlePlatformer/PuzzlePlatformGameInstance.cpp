// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"


#include "Blueprint/UserWidget.h"
#include "Widgets/MainMenu.h"
#include "Widgets/ExitMenu.h"


const static FName SESSION_NAME = TEXT("My session name");

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/UserInterface/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class!= nullptr)) return;
	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> ExitMenuBPClass(TEXT("/Game/UserInterface/WBP_ExitMenu"));
	if (!ensure(ExitMenuBPClass.Class != nullptr)) return;
	ExitMenuClass = ExitMenuBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	//UE_LOG(LogTemp, Warning, TEXT("Widget Class found=%s"),*MenuClass->GetName());

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem Found %s"), *Subsystem->GetSubsystemName().ToString());

		SessionInterface = Subsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem not found"));
	}
	

}
void UPuzzlePlatformGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}
void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not create session"));
		return;
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::LoadMenu(TSubclassOf<UUserWidget> WidgetClass)
{
	Widget=CreateWidget<UMenuBase>(this,WidgetClass);
	if (!ensure(Widget!= nullptr)) return;

	Widget->Setup();

	Widget->SetMenuInterface(this);
	
}
void UPuzzlePlatformGameInstance::Host() 
{
	if (SessionInterface.IsValid())
	{
		//if session already exist, delete it 
		auto ExistingSession=SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}

}
void UPuzzlePlatformGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}
void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green,FString::Printf(TEXT("Joining:%s"),*Address));

	APlayerController* PlayerController;
	PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController!= nullptr)) return;
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
void UPuzzlePlatformGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController;
	PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel("/Game/ThirdPersonBP/Maps/L_MainMenu", ETravelType::TRAVEL_Absolute);
}