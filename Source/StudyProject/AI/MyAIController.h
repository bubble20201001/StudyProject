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

// BehaviorTree : 행동을 분석하고 우선순위가 높은 행동부터 실행하도록 하는 트리 구조의 설계 기법
//	이를 이용하면 행동 패턴을 체계적으로 설계 가능
// Blackboard : BehaviorTree에 필요한 데이터 셋을 저장한다.
// UAISenseConfig_Sight : 표적의 거리나 시거 시야반경 등을 조정할 수 있는 클래스

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class STUDYPROJECT_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController(FObjectInitializer const& object_initializer);

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* _Pawn) override;	// 해당 컨트롤러가 폰을 소유하도록 요청할 때 재정의 가능한 네이티브 함수, 매개 변수로 소유할 폰을 받는다.
	virtual void Tick(float DeltaSeccond) override;
	virtual FRotator GetControlRotation() const override;

public:
	// BlueprintCallable : 작성한 함수를 블루프린트에서 사용할 수 있음
	// FAIStimulus :  npc에 자극을 주어 캐릭터를 쫒아 오게 할 수 있다.

	// 타겟 감지
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void OnTergetDetected(AActor* actor, FAIStimulus const stimulus);

	class UBlackboardComponent* GetBlackboard() const;

private:
	// 	EditInstanceOnly : 월드상에 배치된 오브젝트의 디테일 패널에서 값을 수정 가능

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Search", meta = (AllowPrivateAccess = "true"));
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Search", meta = (AllowPrivateAccess = "true"));
	class UBehaviorTree* BTree;

	class UBlackboardComponent* m_pBlackboard;
	class UAISenseConfig_Sight* m_pSightConfig;

private:
	void SetupPerceptionSystem();
};
