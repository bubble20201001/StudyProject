// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RandomMove.h"
#include "StudyProject.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "MyAIController.h"
#include "Engine/World.h"
#include "blackboard_keys.h"

UMyBTTask_RandomMove::UMyBTTask_RandomMove(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Rqandom Location");
}

EBTNodeResult::Type UMyBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const cont = Cast<AMyAIController>(OwnerComp.GetAIOwner());		// AI소유주 가져오기
	if (cont == nullptr) return EBTNodeResult::Failed;

	auto const npc = cont->GetPawn();
	if (npc == nullptr) return EBTNodeResult::Failed;

	FVector const origin = npc->GetActorLocation();	// AI의 소유주의 위치 가져오기
	FNavLocation loc;


	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld()); // Navi 메시 가져오기
	if (nav_sys == nullptr) return EBTNodeResult::Failed;

	if (nav_sys->GetRandomPointInNavigableRadius(origin, SearchRadius, loc, nullptr))	// Origin 주변의 반경으로 제한된 탐색 가능한 공간에서 임의의 지점을 찾는다.
	{
		cont->GetBlackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);	// 임의의 지점을 찾았다면 이동
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
