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
 Blueprintable : �� Ŭ������ �������Ʈ ������ ������ ���̽� Ŭ������ ����
 FObjectInitializer : ���� C++ �����ڰ� ȣ��� �� UObject ����(�Ӽ� �ʱ�ȭ) �� �Ϸ��ϱ� ���� ���� Ŭ����
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
