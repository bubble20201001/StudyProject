// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimal.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMyAnimal::AMyAnimal()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMyAnimal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AMyCharacter::StaticClass()) && m_IsDuringAttack)	// ºÎµúÇû´Ù¸é °ø°Ý
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ApplyDamage"));
	}
}

int AMyAnimal::melee_attack_Implementation()
{
	if (Montage)
	{
		PlayAnimMontage(Montage);
	}

	return 0;
}

UAnimMontage* AMyAnimal::GetMontage() const
{
	return Montage;
}
