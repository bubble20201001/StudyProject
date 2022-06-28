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
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	// 애니메이션 업데이트
	
private:
	// EditAnywhere : 아키타입이나 인스턴스 양쪽의 프로퍼티 창에서 편집 가능 / 디테일 창 및 블루프린트 에디터의 디테일 창에서 해당 변수 노출
	// AllowPrivateAccess : C++ 코드상에서 private 접근 한정자로 수식된 변수에 대해 접근을 허용하여, 블루프린트 상에 노출시킬 수 있도록 도움

	// 폰(플레이어)의 현재 스피드
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float CurrentPawnSpeed;

	// 폰(플레이어)의 걸음 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float CurrentWalkSpeed;

	// 폰(플레이어)가 공중에 있는가
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool IsInAir;
};
