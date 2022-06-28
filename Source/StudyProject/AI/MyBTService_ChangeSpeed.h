// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UMyBTService_ChangeSpeed : public UBTService
{
	GENERATED_BODY()

public:
	UMyBTService_ChangeSpeed();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	FString GetStaticServiceDescription() const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"));
	float Speed;
};
