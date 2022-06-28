// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_ChangeSpeed.h"
#include "MyAnimal.h"
#include "MyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMyBTService_ChangeSpeed::UMyBTService_ChangeSpeed()
{
	Speed = 600.0f;
	bNotifyBecomeRelevant = true;

	NodeName = TEXT("Change Speed");
}

void UMyBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	auto const cont = OwnerComp.GetAIOwner();
	if (cont == nullptr) return;

	AMyAnimal* const npcBot = Cast<AMyAnimal>(cont->GetPawn());
	
	if(npcBot)
		npcBot->GetCharacterMovement()->MaxWalkSpeed = Speed;
}

FString UMyBTService_ChangeSpeed::GetStaticServiceDescription() const
{
	return FString("Change the NpcBot Speed");
}
