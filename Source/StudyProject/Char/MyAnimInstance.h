// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	// �ִϸ��̼� ������Ʈ
	
private:
	// EditAnywhere : ��ŰŸ���̳� �ν��Ͻ� ������ ������Ƽ â���� ���� ���� / ������ â �� �������Ʈ �������� ������ â���� �ش� ���� ����
	// AllowPrivateAccess : C++ �ڵ�󿡼� private ���� �����ڷ� ���ĵ� ������ ���� ������ ����Ͽ�, �������Ʈ �� �����ų �� �ֵ��� ����

	// ��(�÷��̾�)�� ���� ���ǵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float CurrentPawnSpeed;

	// ��(�÷��̾�)�� ���� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float CurrentWalkSpeed;

	// ��(�÷��̾�)�� ���߿� �ִ°�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool IsInAir;
};
