// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "MyAnimal.h"
#include "GameFramework/CharacterMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	CurrentWalkSpeed = 0.0f;
	IsInAir = false;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		// ���� �ӵ��� ���´�.
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}

	auto MyTestChar = Cast<AMyCharacter>(Pawn);
	if (MyTestChar)
	{
		// ���߿� �ִ°�
		IsInAir = MyTestChar->GetMovementComponent()->IsFalling();
		// �� ĳ������ �ִ� ���ǵ带 ����
		CurrentWalkSpeed = MyTestChar->GetMovementComponent()->GetMaxSpeed();
	}
}