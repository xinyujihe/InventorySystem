// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorComponent/Item.h"
#include "PickUpInterface.h"
#include "InventoryComponent.generated.h"

#define TRACE_Inventory ECC_GameTraceChannel1

class UInventoryUI;
class AItem;
class UDropMenu;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRST_API UInventoryComponent : public UActorComponent, public IPickUpInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItemToInventory_Implementation(class AItem* Item) override;
	void SpawnItemFromActor_Implementation(TSubclassOf<class AItem> Item, FTransform SpawnTransform, bool BIsEquipSlot) override;
	void RemoveItemFromInventory(const TSubclassOf<AItem>& Item);
	void SetOverlappingItem_Implementation(class AItem* Item) override;
	void RemoveOverlappingItem_Implementation(class AItem* Item) override;

	
private:

	UPROPERTY(EditDefaultsOnly, Category = UIClass)
	TSubclassOf<UInventoryUI> InventoryUIClass;//InventoryClass类

	UPROPERTY(EditDefaultsOnly, Category = UIClass)
	TSubclassOf<UUserWidget> PickUpUIClass;

	UPROPERTY(EditDefaultsOnly, Category = UIClass)
	TSubclassOf<UUserWidget> ItemAmountWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Sets)
	float TraceLength = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = Sets)
	float TraceRadius;
	UPROPERTY(EditDefaultsOnly, Category = Sets)
	bool bShowBoxDebug;
	UPROPERTY(VisibleAnywhere, Category = Sets)
	TArray<AActor*> ActorsToIgnore;//模板类数组，数组内添加的Actor(AActor*)会被检测函数忽略

	UPROPERTY(VisibleAnywhere, Category = Sets)
	bool BController = true;//是否使用背包UI的控制器

	UPROPERTY(EditDefaultsOnly, Category = Sets)
	APlayerController* Controller;

	FHitResult BoxHit;

	UPROPERTY(EditAnywhere, Category = Categoryname)
	int32 InventorySize = 50;

	FName ItemToAttachName;
protected:
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sets)
	USkeletalMeshComponent* AttachToMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AItem>>InventoryArray;//存放所有Item

	/*HUD*/
	//背包UI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryUI* InventoryHUD;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 WeaponBackpackSize = 20;

	//物品的详细菜单
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* DropMenu;

	//丢弃物品的窗口
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDropMenu* ItemAmount;

	//靠近物品显示的拾取按键
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* PickUpUI;
	/**/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AItem* OverlappingItem;

	//可以捡起物品的数组
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AItem*>CanPickItem;

	//要丢弃的物品
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem>ItemToDrop;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool InventoryHudIsOpen ;

	//已装备的物品
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> EquippedArcher;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ArcherMeshComponent;
	//空的物品-用于清空人物装备中的物品
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> EmptyItem;

	/*人物的状态*/
	//人物是否处于战斗状态
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool BIsCombatState;
	

public:	
	void ShowPickUpUI();
	void HiddenPickUpUI();
	void PickUpActorByKey();
	UFUNCTION(BlueprintCallable)
	void ShowInventoryHUD();
	void CreateInventoryHud();
	//初始化控制器
	void InitializeController(APlayerController* PlayerController, USkeletalMeshComponent* VariableSceneComponent);
	UFUNCTION(BlueprintCallable)
	void HiddenInventoryHUD();
	void ShpereTrace();
	//创建丢弃物品窗口
	UFUNCTION(BlueprintCallable)
	void CreateItemAmountWidget(TSubclassOf<AItem>Variable, int32 SlotStack);

	//检查要丢弃的物品是否是正在装备中的物品及种类
	UFUNCTION(BlueprintCallable)
	void CheckDropItem(TSubclassOf<class AItem> DropItem);
	//为对应的装备赋值并Attach到人物身上
	UFUNCTION(BlueprintCallable)
	void SetEquippedWeapon(TSubclassOf<AItem> Variable);
	UFUNCTION(BlueprintCallable)
	void SetEquippedArcher(TSubclassOf<AItem> Variable);
	const FName& AttachToName(const TSubclassOf<AItem>& Variable, bool CharacterState);

	UFUNCTION(BlueprintCallable)
	void ClearDropMenu();

	FORCEINLINE void SetInventoryArray (AItem* AddtoItem) { InventoryArray.Add(AddtoItem->GetClass());}
	FORCEINLINE TArray<TSubclassOf<AItem>> GetInventoryArray() { return InventoryArray; }
	FORCEINLINE int32 GetInventorySize() { return InventorySize; }
	FORCEINLINE bool GetInventoryHudIsOpen() { return InventoryHudIsOpen; }
	FORCEINLINE void SetInventoryHudIsOpen(bool Variable) { InventoryHudIsOpen = Variable; }
	FORCEINLINE void SetBIsCombatState(bool Variable) { BIsCombatState = Variable; }
};
