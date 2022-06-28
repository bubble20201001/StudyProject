// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInAttackRange.h"
#include "MyAnimal.h"
#include "MyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"

UBTService_IsPlayerInAttackRange::UBTService_IsPlayerInAttackRange()
{
	AttackRange = 50.0f;
	bNotifyBecomeRelevant = true;

	NodeName = TEXT("Is Player in Attack Range");
}

void UBTService_IsPlayerInAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AMyAIController* const cont = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (cont == nullptr) return;

	AMyAnimal* const npcBot = Cast<AMyAnimal>(cont->GetPawn());
	if (npcBot == nullptr) return;

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// 플레이어가 공격 범위에 들어왔는가?
	if(player)
		cont->GetBlackboard()->SetValueAsBool(bb_keys::player_is_in_attack_range, npcBot->GetDistanceTo(player) <= AttackRange);
}