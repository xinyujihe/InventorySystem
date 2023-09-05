// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTypes.h"
#include "InventoryUI.generated.h"

/**
 * 
 */
class UUniformGridSlot;
class UUniformGridPanel;
class UInventorySlot;
class AItem;

UCLASS()
class FIRST_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UInventoryUI(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), VisibleAnywhere)
	UUniformGridPanel* GridPanel;

	/*装备槽*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), EditAnywhere)
	UInventorySlot* WBP_WeaponSlot;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), EditAnywhere)
	UInventorySlot* WBP_ArcherSlot;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), EditAnywhere)
	UInventorySlot* WBP_ShieldSlot;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<UInventorySlot*>AllInventoryArray;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UInventorySlot* ItemSlot;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EItemType DisplayType = EItemType::EIT_Weapon;
public:
	

	UFUNCTION(BlueprintCallable)
	void UiUpdate(TArray<TSubclassOf<class AItem>> InventoryArray, int32 InvnetorySize);

	UFUNCTION(BlueprintCallable)
	void WeaponUiUpdate(int32 Size, TArray<TSubclassOf<class AItem>> InventoryArray);

	//void UiUpdateItem(TSubclassOf<class AItem> AddToItem);
	void SetWBP_WeaponSlot(TSubclassOf<class AItem> SlotItem);
	void SetWBP_ArcherSlot(TSubclassOf<class AItem> SlotItem);
	void SetWBP_ShieldSlot(TSubclassOf<class AItem> SlotItem);
	
	UFUNCTION(BlueprintImplementableEvent)
	bool ChickItemSlot(TSubclassOf<AItem> Item);

	UFUNCTION(BlueprintCallable)
	void SetDisplayType(EItemType Itemtype, TArray<TSubclassOf<class AItem>> InventoryArray);//用枚举类型的变量作为参数控制盒子碰撞

	FORCEINLINE TArray<UInventorySlot*> GetAllInventoryArray() { return AllInventoryArray; };
	FORCEINLINE void  EmptyAllInventoryArray() { AllInventoryArray.Empty(); };
private:
	UPROPERTY(EditAnywhere, Category = Categoryname)
	TSubclassOf<UInventorySlot> InventorySlot;

	

	//背包每行存储的数量
	UPROPERTY(EditAnywhere, Category = Categoryname)
	int32 Length = 5;
	

};
