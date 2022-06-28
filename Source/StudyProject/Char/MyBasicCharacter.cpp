// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasicCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMyBasicCharacter::AMyBasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_IsDuringAttack = false;
	m_ComboAttackNum = 0;
}

// Called when the game starts or when spawned
void AMyBasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyBasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyBasicCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	//PlayAnimMontage(BeHit_AniMontage);

	if (DamageTaken > 0.0f) // 받은 데미지가 1이상이면
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);		// 데미지 적용
	}
}

float AMyBasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float GetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);	// 무언가로 부터 받은 데미지의 양

	if (HP <= 0.0f) return 0.0f;

	// HP깎기
	if (GetDamage > 0.0f)
		HP -= GetDamage;

	// 해당 데미지를 받고 사망했을 경우 죽음 모션을 작동시키고 죽음 처리한다.
	if (HP <= 0)
	{
		PlayAnimMontage(DeathAniMontage, 1.0f);
		Die(GetDamage, DamageEvent, EventInstigator, DamageCauser);
	}
	// 아닐 경우 남은 HP표시
	else
	{
		OnHit(GetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("HP : %f"), HP));
	}

	return GetDamage;
}

void AMyBasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	HP = FMath::Min(0.0f, HP);

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();
	if (DamageType == nullptr) return;

	Killer = GetDamageInstigator(Killer, *DamageType);

	GetWorldTimerManager().ClearAllTimersForObject(this);		// 특정 오브젝트에 연관된 타이머 해제

	// SetCollisionEnabled : 충돌 허가 유무
	// SetResponseToChannel : 이 몸체의 충돌 응답을 특정 채널로 설정
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	// 움직임을 멈춘다
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	if (Controller != NULL) 
		Controller->UnPossess();

	float DeathAnimDuration = PlayAnimMontage(DeathAniMontage);

	FTimerHandle TimerHamdle;
	GetWorldTimerManager().SetTimer(TimerHamdle, this, &AMyBasicCharacter::DeathAnimationEnd, DeathAnimDuration, false);
}

void AMyBasicCharacter::DeathAnimationEnd()
{
	// 액터를 게임에서 숨긴다.
	this->SetActorHiddenInGame(true);
	// 이 액터의 수명을 설정하며 만료되면 개체가 파괴된다. 요청된 수명이 0이면 타이머가 지워지고 액터가 소멸되지 않는다.
	SetLifeSpan(0.1f);
}

void AMyBasicCharacter::Attack()
{
	m_ComboAttackNum = rand() % 2 + 1;
	FString PlaySection = "Attack_" + FString::FromInt(m_ComboAttackNum);
	PlayAnimMontage(AttackAniMontage, 1.0f, FName(*PlaySection));
	m_IsDuringAttack = true;

	FTimerHandle TH_Attack_End;
	GetWorldTimerManager().SetTimer(TH_Attack_End, this, &AMyBasicCharacter::AttackEnd, 1.7f, false);
}

void AMyBasicCharacter::AttackEnd()
{
	m_IsDuringAttack = false;
}

