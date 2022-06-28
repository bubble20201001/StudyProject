// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_PlayerRocation.h"
#include "MyAIController.h"
#include "blackboard_keys.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UMyBTTask_PlayerRocation::UMyBTTask_PlayerRocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Rqandom Location");
}

EBTNodeResult::Type UMyBTTask_PlayerRocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (player == nullptr) return EBTNodeResult::Failed;

	auto const cont = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if(cont == nullptr) return EBTNodeResult::Failed;

	FVector const player_location = player->GetActorLocation();

	if (IsSerchRandom) // ã������
	{
		FNavLocation loc;

		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(player_location, SearchRadius, loc, nullptr))	// ������ SearchRadius���� ������ �÷��̾ ã�´�
		{
			cont->GetBlackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);
		}
	}
	else
	{
		cont->GetBlackboard()->SetValueAsVector(bb_keys::target_location, player_location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
