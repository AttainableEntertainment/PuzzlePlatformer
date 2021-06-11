// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/MainMenu.h"




UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/UserInterface/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class!= nullptr)) return;

	MenuClass = MenuBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	//UE_LOG(LogTemp, Warning, TEXT("Widget Class found=%s"),*MenuClass->GetName());
}
void UPuzzlePlatformGameInstance::LoadMenu()
{
	UMainMenu* Widget=CreateWidget<UMainMenu>(this,MenuClass);
	if (!ensure(Widget!= nullptr)) return;

	Widget->AddToViewport();
	Widget->bIsFocusable = true;

	APlayerController* PlayerController;
	PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(Widget->TakeWidget());
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor=true;

	Widget->SetMenuInterface(this);

}
void UPuzzlePlatformGameInstance::Host() 
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!= nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World!= nullptr)) return;
	World->ServerTravel("/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap?listen");


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
