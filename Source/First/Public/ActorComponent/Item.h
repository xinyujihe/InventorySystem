// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemTypes.h"
#include "Item.generated.h"

class UWidgetComponent;
class UBoxComponent;
class UUserWidget;
class USoundBase;
class UInventoryComponent;

struct FItemDetails
{
	FName ItemName = "None";
	FText ItemDiscription = FText::FromString("None");;
	UTexture2D* ItemIcon = nullptr;
	UStaticMesh* Mesh = nullptr;
	int32 CurrentStack = 1;
	EItemType ItemType = EItemType::EIT_Archer;
	ECookingType CookingType;
	//未拿出武器附加到的Socket名称
	FName AttachToName;
	//拿出武器附加到的Socket名称
	FName AttachToName2;
};

UCLASS()

class FIRST_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AItem();
	virtual void Tick(float DeltaTime) override;
protected:
	
	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetOverLappingComponent(AActor* OtherActor);


	UFUNCTION()
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool ComponentHasInterface(AActor* OtherActor);
	
	virtual void BeginPlay() override;
	/*Item的属性*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variable)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variable)
	FText ItemDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variable)
	UTexture2D* ItemIcon;
	//Spawn的Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Variable)
	UStaticMesh* ItemMesh;

	//记录物品当前的堆叠
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Variable)
	int32 CurrentStack = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Variable)
	int32 MaxStack = 99;
	
	//物品的种类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Variable)
	EItemType ItemType = EItemType::EIT_Archer;

	//当物品种类为Cooking时显示该Cooking种类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Variable, meta = (EditCondition = "ItemType == EItemType::ETI_Cooking", EditConditionHides))
	ECookingType CookingType;

	//装备槽名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variable)
	FName InSocketName;
	//持有槽名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variable)
	FName HoldingSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variable)
	UWidgetComponent* WidgetComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Variable)
	UBoxComponent* Box;
	

private:
	UPROPERTY(EditAnywhere, Category = Variable)
	USoundBase* PickUpSpound;

	UPROPERTY(VisibleAnywhere, Category = Variable)
	UInventoryComponent* OverLappingComponent;
public:

	//将物品装备到人物身上
	UFUNCTION(BlueprintImplementableEvent)
	void Equip(USceneComponent* Inparent);

	FItemDetails GetItemDetails();
	FORCEINLINE USoundBase* GetSound() { return PickUpSpound; };
	FORCEINLINE int32 GetMaxStack() { return MaxStack; };
};
