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
		// 현재 속도를 얻어온다.
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}

	auto MyTestChar = Cast<AMyCharacter>(Pawn);
	if (MyTestChar)
	{
		// 공중에 있는가
		IsInAir = MyTestChar->GetMovementComponent()->IsFalling();
		// 내 캐릭터의 최대 스피드를 구함
		CurrentWalkSpeed = MyTestChar->GetMovementComponent()->GetMaxSpeed();
	}
}