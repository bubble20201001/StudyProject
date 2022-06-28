// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "MyAIController.generated.h"

/**
 * 
 */

// BehaviorTree : �ൿ�� �м��ϰ� �켱������ ���� �ൿ���� �����ϵ��� �ϴ� Ʈ�� ������ ���� ���
//	�̸� �̿��ϸ� �ൿ ������ ü�������� ���� ����
// Blackboard : BehaviorTree�� �ʿ��� ������ ���� �����Ѵ�.
// UAISenseConfig_Sight : ǥ���� �Ÿ��� �ð� �þ߹ݰ� ���� ������ �� �ִ� Ŭ����

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class STUDYPROJECT_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController(FObjectInitializer const& object_initializer);

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* _Pawn) override;	// �ش� ��Ʈ�ѷ��� ���� �����ϵ��� ��û�� �� ������ ������ ����Ƽ�� �Լ�, �Ű� ������ ������ ���� �޴´�.
	virtual void Tick(float DeltaSeccond) override;
	virtual FRotator GetControlRotation() const override;

public:
	// BlueprintCallable : �ۼ��� �Լ��� �������Ʈ���� ����� �� ����
	// FAIStimulus :  npc�� �ڱ��� �־� ĳ���͸� �i�� ���� �� �� �ִ�.

	// Ÿ�� ����
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void OnTergetDetected(AActor* actor, FAIStimulus const stimulus);

	class UBlackboardComponent* GetBlackboard() const;

private:
	// 	EditInstanceOnly : ����� ��ġ�� ������Ʈ�� ������ �гο��� ���� ���� ����

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Search", meta = (AllowPrivateAccess = "true"));
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Search", meta = (AllowPrivateAccess = "true"));
	class UBehaviorTree* BTree;

	class UBlackboardComponent* m_pBlackboard;
	class UAISenseConfig_Sight* m_pSightConfig;

private:
	void SetupPerceptionSystem();
};
