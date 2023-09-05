// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "FirstCharacter.generated.h"



class UInputAction;
class UAnimMontage;
class UInputMappingContext;
struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class FIRST_API AFirstCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	
	AFirstCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*变量*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = MoveValues)
	ECharacterState CharacterState = ECharacterState::ECS_StandMove;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = MoveValues)
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = MoveValues)
	FVector MoveInputValue;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = MoveValues)
	bool bSpeedUp;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = MoveValues)
	bool bCanJump;

	/*函数*/
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

private:

	/*输入*/
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* CharacterMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SpeedUpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LeftKeyAttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* BackToIdleAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* PickUpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* OpenInventoryAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	void Move(const FInputActionValue& Value);
	void ClearMove(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SpeedUp(const FInputActionValue& Value);
	void LightAttack(const FInputActionValue& Value);
	bool FistsAndUnoccupied();
	void BackToIdle(const FInputActionValue& Value);
	void PickUpActor(const FInputActionValue& Value);
	void OpenInventory();
	void Jump();

	/*组件*/
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* Arm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	/*Montage*/
	UPROPERTY(EditAnyWhere, Category = "montages")
	UAnimMontage* JumpMontage;

public:
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
