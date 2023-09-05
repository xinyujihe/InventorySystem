// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTypes.h"
#include "InventorySlot.generated.h"

class UButton;
class UImage;
class AItem;
class UTextBlock;
class UDropMenu;
class UInventoryUI;

UCLASS()
class FIRST_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

private:

	

protected:
	UPROPERTY(meta = (BindWidget), BluePrintReadOnly)
	UButton* Button;

	UPROPERTY(meta = (BindWidget), BluePrintReadOnly)
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget), BluePrintReadOnly)
	UTextBlock* Text_Quantity;

	//背包UI
	UPROPERTY(BluePrintReadOnly, EditAnywhere)
	UInventoryUI* InventoryUI;

	UPROPERTY(BluePrintReadOnly)
	TSubclassOf<AItem>HeldItem;

	/**/
	UPROPERTY(BluePrintReadWrite, VisibleAnywhere)
	int32 CurrentStack = 1;

	UPROPERTY(BluePrintReadWrite, EditAnywhere)
	bool BIsEquipmentslot = false;

	UPROPERTY(BluePrintReadWrite, EditAnywhere)
	EItemType SlotType;
	
public:


	UFUNCTION(BlueprintCallable)
	void UpdateSlot(TSubclassOf<AItem>ItemtoUpdate);

	UFUNCTION(BlueprintCallable)
	void EquipItem(const TSubclassOf<AItem>& EquipmentItem, UInventoryComponent* OwnerComponent);

	void SwitchSlotType(UInventoryComponent* OwnerComponent, const TSubclassOf<AItem>& EquipmentItem);

	void SetText_Quantity(int32 Number);
	FORCEINLINE TSubclassOf<AItem> GetHeldItem() { return HeldItem; }
	FORCEINLINE int32 GetCurrentStack() { return CurrentStack; }
	FORCEINLINE void SetCurrentStack(int32 Num) { CurrentStack += Num; }
	FORCEINLINE void SetInventoryUI(UInventoryUI* UI) { InventoryUI = UI; }
};
