// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropMenu.generated.h"

class AItem;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class FIRST_API UDropMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position", meta = (ExposeOnSpawn = "true", OverrideNativeName = "HeldItem"))
	TSubclassOf<AItem>HeldItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position", meta = (ExposeOnSpawn = "true", OverrideNativeName = "BHasStack?"))
	bool BHasStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position", meta = (ExposeOnSpawn = "true", OverrideNativeName = "BIsEquipSlot?"))
	bool BIsEquipSlot;

	//物品的数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position", meta = (ExposeOnSpawn = "true", OverrideNativeName = "SlotStack"))
	int32 SlotStack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Position")
	UInventoryComponent* OwnerInventoryComponent;
public:
	UFUNCTION(BlueprintCallable)
	void DropFunction(FTransform BuildLocation);

	UFUNCTION(BlueprintCallable)
	void SetInventoryComponent();

	UFUNCTION(BlueprintCallable)
	void ClearDropMenu();


	FORCEINLINE void SetSlotStack(int32 Variable) { SlotStack = Variable; }
	
};
