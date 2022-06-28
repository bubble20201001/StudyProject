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

	// 누군가에게 맞았다면 그에 따른 처리(체력 감소 / 사망 등)에 관한 처리를 한다.
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	// 액터에게 피해를 준다.
	// 매개 변수 순서 : 받은 데미지양, 받은 데미지를 설명하는 패키지, 데미지에 대한 책임이 있는 컨트롤러, 직접 피해를 입힌 액터(공격자)
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
