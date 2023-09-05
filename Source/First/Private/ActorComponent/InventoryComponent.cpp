// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/InventoryUI.h"
#include "Kismet/KismetArrayLibrary.h"
#include "HUD/DropMenu.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	ArcherMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArcherMesh"));
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//ShpereTrace();
	if (OverlappingItem)
	{
		ShowPickUpUI();
	}
}

void UInventoryComponent::AddItemToInventory_Implementation(AItem* Item)
{
	InventoryArray.Add(Item->GetClass());
	if (InventoryHUD && InventoryHudIsOpen)
	{
		HiddenInventoryHUD();
		ShowInventoryHUD();
	}
}

void UInventoryComponent::SpawnItemFromActor_Implementation(TSubclassOf<class AItem> Item, FTransform SpawnTransform, bool BIsEquipSlot)
{
	GetWorld()->SpawnActor<AItem>(Item, SpawnTransform);
	if (BIsEquipSlot)
	{
		CheckDropItem(Item);
	}
	else
	{
		RemoveItemFromInventory(Item);
	}
	HiddenInventoryHUD();
	ShowInventoryHUD();
}

void UInventoryComponent::RemoveItemFromInventory(const TSubclassOf<AItem>& Item)
{
	int32 Idenx = InventoryArray.Find(Item);
	if (Idenx >= 0)
	{
		InventoryArray.RemoveAt(Idenx);
		FString TStr = FString::FromInt(Idenx);
		GEngine->AddOnScreenDebugMessage(7, 2.0f, FColor::Green, FString::Printf(TEXT("The Item Idenx is: %d"), Idenx));
	}
}

void UInventoryComponent::CheckDropItem(TSubclassOf<class AItem> DropItem)
{
	if (DropItem == EquippedWeapon || DropItem == EquippedArcher)
	{
		AItem* ToDropItem = DropItem.GetDefaultObject();
		EItemType DropType = ToDropItem->GetItemDetails().ItemType;
		switch (DropType)
		{
		case EItemType::EIT_Archer: SetEquippedArcher(EmptyItem);
			break;
		case EItemType::EIT_Weapon: SetEquippedWeapon(EmptyItem);
			break;
		case EItemType::EIT_Shield:
			break;
		case EItemType::EIT_Armor:
			break;
		case EItemType::ETI_Cooking:
			break;
		case EItemType::EIT_Material:
			break;
		case EItemType::EIT_ImportantItems:
			break;
		default:
			break;
		}
	}
}

void UInventoryComponent::SetOverlappingItem_Implementation(AItem* Item)
{
	CanPickItem.AddUnique(Item);
	OverlappingItem = Item;
}

void UInventoryComponent::RemoveOverlappingItem_Implementation(AItem* Item)
{
	CanPickItem.Remove(Item);
	OverlappingItem = nullptr;
}

void UInventoryComponent::ShowPickUpUI()
{
	if (Controller && PickUpUIClass)
	{
		bool IsLocalPlayer = Controller->IsLocalPlayerController();
		if (IsLocalPlayer)
		{
			if (!PickUpUI)
			{
				PickUpUI = CreateWidget<UUserWidget>(Controller, PickUpUIClass);
			}
			PickUpUI->AddToViewport();
		}
	}
}

void UInventoryComponent::HiddenPickUpUI()
{
	if (PickUpUI)
	{
		PickUpUI->RemoveFromParent();
	}
}

void UInventoryComponent::PickUpActorByKey()
{
	if (OverlappingItem)
	{
		for (int i = 1; i <= OverlappingItem->GetItemDetails().CurrentStack; i++)
		{
			AddItemToInventory_Implementation(OverlappingItem);
		}
		UGameplayStatics::SpawnSoundAtLocation(this, OverlappingItem->GetSound(), OverlappingItem->GetActorLocation());
		CanPickItem.Remove(OverlappingItem);
		OverlappingItem->Destroy();
		if (CanPickItem.Num()&& OverlappingItem ==nullptr)
		{
			const int32 num = FMath::RandRange(0, CanPickItem.Num() - 1);
			OverlappingItem = CanPickItem[num];
		}
	}
	
}

void UInventoryComponent::ShowInventoryHUD()
{
	if (!Controller || !InventoryUIClass) return;
	bool IsLocalPlayer = Controller->IsLocalPlayerController();
	if (IsLocalPlayer)
	{
		CreateInventoryHud();
		InventoryHUD->AddToViewport();
		InventoryHUD->WeaponUiUpdate(WeaponBackpackSize, InventoryArray);
		if (BController)
		{
			Controller->SetInputMode(FInputModeGameAndUI());
			Controller->bShowMouseCursor = true;
		}
	}
}

void UInventoryComponent::CreateInventoryHud()
{
	if (!InventoryHUD)
	{
		InventoryHUD = CreateWidget<UInventoryUI>(Controller, InventoryUIClass);
	}
	InventoryHUD->WeaponUiUpdate(WeaponBackpackSize, InventoryArray);
}

void UInventoryComponent::InitializeController(APlayerController* PlayerController, USkeletalMeshComponent* VariableSceneComponent)
{
	if (!Controller)
	{
		Controller = PlayerController;
		AttachToMesh = VariableSceneComponent;
	}
}

void UInventoryComponent::HiddenInventoryHUD()
{
	if (InventoryHUD)
	{
		InventoryHUD->RemoveFromParent();
		InventoryHUD->EmptyAllInventoryArray();
		Controller->SetInputMode(FInputModeGameOnly());
		Controller->bShowMouseCursor = false;
	}
}

void UInventoryComponent::ShpereTrace()
{
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = Start + GetOwner()->GetActorForwardVector() * TraceLength;
	ActorsToIgnore.Add(GetOwner());

	for (AActor* Actor : ActorsToIgnore)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	UKismetSystemLibrary::SphereTraceSingle(
		this,
		Start,
		End,
		TraceRadius,
		//ETraceTypeQuery::ECC_GameTraceChannel1,//跟踪类型查询，一般为可见性追踪。这个参数并不重要。可以自己自定义查询类型
		UEngineTypes::ConvertToTraceType(TRACE_Inventory),
		false,//如果为 true，则针对复杂碰撞进行测试，如果为 false，则针对简化碰撞进行测试。
		ActorsToIgnore,
		bShowBoxDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,//绘制Debug检测
		BoxHit,
		true,//是否忽略自己
		FLinearColor::Green,
		FLinearColor::Red
	);
	if (BoxHit.GetActor())
	{

	}
}

void UInventoryComponent::CreateItemAmountWidget(TSubclassOf<AItem>Variable, int32 SlotStack)
{
	if (!ItemAmountWidgetClass) return;
	ItemToDrop = Variable;
	if (ItemAmount)
	{
		ItemAmount->RemoveFromParent();
	}
	ItemAmount = CreateWidget<UDropMenu>(Controller, ItemAmountWidgetClass);
	if (ItemAmount)
	{
		ItemAmount->SetSlotStack(SlotStack);
	}
	ItemAmount->AddToViewport();
	DropMenu->RemoveFromParent();
}

const FName& UInventoryComponent::AttachToName(const TSubclassOf<AItem> &Variable, bool CharacterState)
{
	ItemToAttachName= CharacterState ? Variable.GetDefaultObject()->GetItemDetails().AttachToName2 : Variable.GetDefaultObject()->GetItemDetails().AttachToName;
	return ItemToAttachName;
}

void UInventoryComponent::ClearDropMenu()
{
	if (DropMenu)
	{
		DropMenu->RemoveFromParent();
		DropMenu = nullptr;
	}
}

void UInventoryComponent::SetEquippedWeapon(TSubclassOf<AItem> Variable)
{
	EquippedWeapon = Variable;
	if (EquippedWeapon && AttachToMesh)
	{
		InventoryHUD->SetWBP_WeaponSlot(EquippedWeapon);
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);//为Location，Rotation， Scale单独创建规则。 
		WeaponMeshComponent->AttachToComponent(AttachToMesh, TransformRules, AttachToName(EquippedWeapon, BIsCombatState));
		WeaponMeshComponent->SetStaticMesh(EquippedWeapon.GetDefaultObject()->GetItemDetails().Mesh);

	}
}

void UInventoryComponent::SetEquippedArcher(TSubclassOf<AItem> Variable)
{
	EquippedArcher = Variable;
	if (EquippedArcher && AttachToMesh)
	{
		InventoryHUD->SetWBP_ArcherSlot(EquippedArcher);
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
		ArcherMeshComponent->AttachToComponent(AttachToMesh, TransformRules, AttachToName(EquippedArcher, BIsCombatState));
		ArcherMeshComponent->SetStaticMesh(EquippedArcher.GetDefaultObject()->GetItemDetails().Mesh);

	}
}

