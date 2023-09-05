// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InventoryUI.h"
#include "HUD/InventorySlot.h"
#include "Components/UniformGridPanel.h"
#include "ActorComponent/Item.h"



UInventoryUI::UInventoryUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInventoryUI::UiUpdate(TArray<TSubclassOf<class AItem>> InventoryArray, int32 InvnetorySize)
{
	if (!InventorySlot) return;
	GridPanel->ClearChildren();
	AllInventoryArray.Empty();
	for (auto& ItemActor : InventoryArray)
	{
		if (ItemActor.GetDefaultObject()->GetItemDetails().ItemType != DisplayType) continue;
		if (!ChickItemSlot(ItemActor) || GridPanel->GetChildrenCount() == 0)
		{
			ItemSlot = CreateWidget<UInventorySlot>(this, InventorySlot);
			AllInventoryArray.Add(ItemSlot);
			ItemSlot->UpdateSlot(ItemActor);//UI图标的更新
			ItemSlot->SetInventoryUI(this);
			GEngine->AddOnScreenDebugMessage(2, 2.0f, FColor::Green, TEXT("AllInventoryArray.AddUnique(ItemSlot) success"));
			if (Length)
			{
				GridPanel->AddChildToUniformGrid(ItemSlot, GridPanel->GetChildrenCount() / Length, GridPanel->GetChildrenCount() % Length);
			}

		}
	}

}

void UInventoryUI::WeaponUiUpdate(int32 Size, TArray<TSubclassOf<class AItem>> InventoryArray)
{
	if (!InventorySlot) return;
	GridPanel->ClearChildren();
	AllInventoryArray.Empty();
	for (int i = 0; i < Size; i++)
	{
		ItemSlot = CreateWidget<UInventorySlot>(this, InventorySlot);
		if (Length)
		{
			GridPanel->AddChildToUniformGrid(ItemSlot, GridPanel->GetChildrenCount() / Length, GridPanel->GetChildrenCount() % Length);
		}
		
	}

}

void UInventoryUI::SetWBP_WeaponSlot(TSubclassOf<class AItem> SlotItem)
{
	WBP_WeaponSlot->UpdateSlot(SlotItem);
}

void UInventoryUI::SetWBP_ArcherSlot(TSubclassOf<class AItem> SlotItem)
{
	WBP_ArcherSlot->UpdateSlot(SlotItem);
}

void UInventoryUI::SetWBP_ShieldSlot(TSubclassOf<class AItem> SlotItem)
{
	WBP_ShieldSlot->UpdateSlot(SlotItem);
}

void UInventoryUI::SetDisplayType(EItemType Itemtype, TArray<TSubclassOf<class AItem>> InventoryArray)
{
	DisplayType = Itemtype;
	UiUpdate(InventoryArray, 5);
}
//备份
//bool UInventoryUI::ChickItemSlot_Implementation(TSubclassOf<AItem> Item)
//{
//	if (AllInventoryArray.Num() < 1) return false;
//	for (auto SlotUI : AllInventoryArray)
//	{
//		auto SlotItem = SlotUI->GetHeldItem();
//		int32 MaxStack = SlotItem.GetDefaultObject()->GetMaxStack();//拿到Item的最大堆叠值
//		if (SlotItem.GetDefaultObject()->GetItemDetails().ItemName == Item.GetDefaultObject()->GetItemDetails().ItemName && SlotUI->GetCurrentStack() <= MaxStack)
//		{
//			GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Has SameSlot"));
//			SlotUI->SetCurrentStack(1);
//			HasSameItem = true;
//			return true;
//		}
//		else
//		{
//			HasSameItem = false;
//			return false;
//		}
//	}
//	return HasSameItem;
//}
// 背包更新逻辑备份
//void UInventoryUI::UiUpdate(TArray<TSubclassOf<class AItem>> InventoryArray)
//{
//	if (!InventorySlot) return;
//	GridPanel->ClearChildren();
//	AllInventoryArray.Empty();
//	for (auto& ItemActor : InventoryArray)
//	{
//		if (ItemActor.GetDefaultObject()->GetItemDetails().ItemType != DisplayType) continue;
//		if (!ChickItemSlot(ItemActor) || GridPanel->GetChildrenCount() == 0)
//		{
//			ItemSlot = CreateWidget<UInventorySlot>(this, InventorySlot);
//			AllInventoryArray.Add(ItemSlot);
//			ItemSlot->UpdateSlot(ItemActor);
//			ItemSlot->SetInventoryUI(this);
//			GEngine->AddOnScreenDebugMessage(2, 2.0f, FColor::Green, TEXT("AllInventoryArray.AddUnique(ItemSlot) success"));
//			if (Length)
//			{
//				GridPanel->AddChildToUniformGrid(ItemSlot, GridPanel->GetChildrenCount() / Length, GridPanel->GetChildrenCount() % Length);
//			}
//		}
//	}
//}

