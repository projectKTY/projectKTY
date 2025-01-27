// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSCharacter.generated.h"

/**
*  TPSCharacter - ���ӿ� ���� �÷��̾�� �� AI ��ο��� �������� ���� ĳ������ ���̽� Ŭ����
*  �⺻������ �̵� �� ȸ�� ������ �����Ͽ� ��� ĳ���Ϳ��� ������ �� �ְ� ����
*/

struct FInputActionValue;

UCLASS()
class PROJECTKTY_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UCharacterStatComponent* StatComponent;

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 1;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

public:
	// Sets default values for this character's properties
	ATPSCharacter();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	virtual void SetDead();
	void PlayDeadAnimation();
	TObjectPtr<class UAnimMontage> DeadMontage;

protected:
	virtual void BeginPlay();

	virtual void SetDefaultStatus();
	virtual void SetDefaultCharacterSettings();

	// UFUNCTION(NetMulticast, Reliable)
	// void MulticastSetDie();

public:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
};
