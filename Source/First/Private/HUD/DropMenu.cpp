// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DropMenu.h"
#include "ActorComponent/InventoryComponent.h"


void UDropMenu::NativeConstruct()
{
	Super::NativeConstruct();
	SetInventoryComponent();
}

void UDropMenu::DropFunction(FTransform BuildLocation)
{
	if (!HeldItem && !OwnerInventoryComponent) return;
	if (BHasStack)
	{
		OwnerInventoryComponent->CreateItemAmountWidget(HeldItem, SlotStack);
	}
	else
	{
		OwnerInventoryComponent->SpawnItemFromActor_Implementation(HeldItem, BuildLocation, BIsEquipSlot);
		OwnerInventoryComponent->ClearDropMenu();
		
	}
}

void UDropMenu::SetInventoryComponent()
{
	if (!OwnerInventoryComponent)
	{
		OwnerInventoryComponent =Cast<UInventoryComponent>(GetOwningPlayerPawn()->GetComponentByClass(UInventoryComponent::StaticClass()));
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Cyan, TEXT("SetInventoryComponent Function has  run"));
	}
}

void UDropMenu::ClearDropMenu()
{
	if (this)
	{
		this->RemoveFromParent();
	}
}
