// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Attack.h"
#include "MyAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "MyBasicCharacter.h"
#include "MyAnimal.h"
#include "CombatInterface.h"

UMyBTTask_Attack::UMyBTTask_Attack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Attack Player");
}

EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const cont = OwnerComp.GetAIOwner();
	AMyAnimal* const npcBot = Cast<AMyAnimal>(cont->GetPawn());

	if (ICombatInterface* const icombat = Cast<ICombatInterface>(npcBot))
	{
		if (MontageHasFinished(npcBot))
		{
			icombat->Execute_melee_attack(npcBot);
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UMyBTTask_Attack::MontageHasFinished(AMyAnimal* const npcBot)
{
	return npcBot->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npcBot->GetMontage());
}
