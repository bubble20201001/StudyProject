// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_IsPlayerInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UBTService_IsPlayerInAttackRange : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_IsPlayerInAttackRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"));
	float AttackRange;
};
