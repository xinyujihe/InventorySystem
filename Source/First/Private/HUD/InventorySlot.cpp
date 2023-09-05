// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InventorySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ActorComponent/Item.h"
#include "ActorComponent/InventoryComponent.h"
#include "HUD/DropMenu.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventorySlot::UpdateSlot(TSubclassOf<AItem>ItemtoUpdate)
{
	HeldItem = ItemtoUpdate;
	AItem* DefaultActor = Cast<AItem>(ItemtoUpdate->GetDefaultObject(true));
	ItemImage->SetBrushFromTexture(DefaultActor->GetItemDetails().ItemIcon);
	SetText_Quantity(CurrentStack);
	if (!(Text_Quantity->IsVisible()) && CurrentStack > 1)//文本为隐藏且CurrentStack大于1时调用
	{
		Text_Quantity->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInventorySlot::EquipItem(const TSubclassOf<AItem>& EquipmentItem, UInventoryComponent* OwnerComponent)
{
	AItem* ToEquipItem = EquipmentItem.GetDefaultObject();
	if (ToEquipItem->GetItemDetails().ItemType == SlotType)
	{
		OwnerComponent->RemoveItemFromInventory(EquipmentItem);
		OwnerComponent->HiddenInventoryHUD();
		OwnerComponent->ShowInventoryHUD();
		SwitchSlotType(OwnerComponent, EquipmentItem);
	}
}

void UInventorySlot::SwitchSlotType(UInventoryComponent* OwnerComponent, const TSubclassOf<AItem>& EquipmentItem)
{
	switch (SlotType)
	{
	case EItemType::EIT_Archer: OwnerComponent->SetEquippedArcher(EquipmentItem);
		break;
	case EItemType::EIT_Armor:
		break;
	case EItemType::EIT_Weapon:OwnerComponent->SetEquippedWeapon(EquipmentItem);
		break;
	case EItemType::EIT_Shield:
		break;
	default:
		break;
	}
}

void UInventorySlot::SetText_Quantity(int32 Number)
{
	FString String = FString::FromInt(Number);
	FText Text = FText::FromString(String);
	Text_Quantity->SetText(Text);
}

