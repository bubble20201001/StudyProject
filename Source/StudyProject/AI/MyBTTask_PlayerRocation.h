// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MyBTTask_PlayerRocation.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UMyBTTask_PlayerRocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_PlayerRocation(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"));
	bool IsSerchRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"));
	float SearchRadius = 150.0f;
};
