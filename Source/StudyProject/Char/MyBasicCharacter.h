// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBasicCharacter.generated.h"

UCLASS()
class STUDYPROJECT_API AMyBasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyBasicCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ���������� �¾Ҵٸ� �׿� ���� ó��(ü�� ���� / ��� ��)�� ���� ó���� �Ѵ�.
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	// ���Ϳ��� ���ظ� �ش�.
	// �Ű� ���� ���� : ���� ��������, ���� �������� �����ϴ� ��Ű��, �������� ���� å���� �ִ� ��Ʈ�ѷ�, ���� ���ظ� ���� ����(������)
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	
	void DeathAnimationEnd();

public:
	void Attack();
	void AttackEnd();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Pawn")
	UAnimMontage* AttackAniMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Pawn")
	UAnimMontage* DeathAniMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
	float MaxHP;

	int m_ComboAttackNum;
	bool m_IsDuringAttack;
};
