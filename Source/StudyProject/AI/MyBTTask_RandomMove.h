// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UObject/UObjectGlobals.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MyBTTask_RandomMove.generated.h"

/*
 Blueprintable : 이 클래스를 블루프린트 생성이 가능한 베이스 클래스로 노출
 FObjectInitializer : 실제 C++ 생성자가 호출된 후 UObject 생성(속성 초기화) 을 완료하기 위한 내부 클래스
 */
UCLASS(Blueprintable)
class STUDYPROJECT_API UMyBTTask_RandomMove : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTTask_RandomMove(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"));
	float SearchRadius = 1500.0f;
};
