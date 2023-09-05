#pragma once

UENUM(BlueprintType)
enum class EItemType : uint8
{
	//弓箭
	EIT_Archer UMETA(DisplayName = "Archer"),
	//武器
	EIT_Weapon UMETA(DisplayName = "Weapon"),
	//盾牌
	EIT_Shield UMETA(DisplayName = "Shield"),
	//盔甲
	EIT_Armor UMETA(DisplayName = "Armor"),
	//料理
	ETI_Cooking UMETA(DisplayName = "Cooking"),
	//材料
	EIT_Material UMETA(DisplayName = "Material"),
	//材料
	EIT_ImportantItems UMETA(DisplayName = "重要物品"),
};


UENUM(BlueprintType)
enum class ECookingType : uint8
{
	//料理-食物类
	ECT_Food UMETA(DisplayName = "Food"),
	//料理-药剂类
	ECT_Potion UMETA(DisplayName = "Potion")
};