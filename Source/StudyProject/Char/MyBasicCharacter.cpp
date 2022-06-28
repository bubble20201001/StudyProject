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

	if (DamageTaken > 0.0f) // ���� �������� 1�̻��̸�
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);		// ������ ����
	}
}

float AMyBasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float GetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);	// ���𰡷� ���� ���� �������� ��

	if (HP <= 0.0f) return 0.0f;

	// HP���
	if (GetDamage > 0.0f)
		HP -= GetDamage;

	// �ش� �������� �ް� ������� ��� ���� ����� �۵���Ű�� ���� ó���Ѵ�.
	if (HP <= 0)
	{
		PlayAnimMontage(DeathAniMontage, 1.0f);
		Die(GetDamage, DamageEvent, EventInstigator, DamageCauser);
	}
	// �ƴ� ��� ���� HPǥ��
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

	GetWorldTimerManager().ClearAllTimersForObject(this);		// Ư�� ������Ʈ�� ������ Ÿ�̸� ����

	// SetCollisionEnabled : �浹 �㰡 ����
	// SetResponseToChannel : �� ��ü�� �浹 ������ Ư�� ä�η� ����
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	// �������� �����
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
	// ���͸� ���ӿ��� �����.
	this->SetActorHiddenInGame(true);
	// �� ������ ������ �����ϸ� ����Ǹ� ��ü�� �ı��ȴ�. ��û�� ������ 0�̸� Ÿ�̸Ӱ� �������� ���Ͱ� �Ҹ���� �ʴ´�.
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

