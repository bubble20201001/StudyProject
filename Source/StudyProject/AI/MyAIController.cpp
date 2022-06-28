// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyCharacter.h"
#include "blackboard_keys.h"

AMyAIController::AMyAIController(FObjectInitializer const& object_initializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// ConstructorHelpers::FObjectFinde : Asset�� ���빰�� ������ �� ���
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/_My/AI/DeerStag_BT.DeerStag_BT'"));
	
	if (obj.Succeeded())
		BTree = obj.Object;

	BehaviorTreeComp = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	m_pBlackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	SetupPerceptionSystem();
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BTree)
	{
		RunBehaviorTree(BTree);
		BehaviorTreeComp->StartTree(*BTree);
	}
}

void AMyAIController::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);
	if (m_pBlackboard)
	{
		m_pBlackboard->InitializeBlackboard(*BTree->BlackboardAsset);	// BTree�� �ùٸ��� �ʱ�ȭ �Ǹ� true ��ȯ
	}
}

void AMyAIController::Tick(float DeltaSeccond)
{
	Super::Tick(DeltaSeccond);
}

FRotator AMyAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AMyAIController::OnTergetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto const ch = Cast< AMyCharacter>(actor))	// �÷��̾�(MyCharacter)�� �����ߴ°�
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "FindPlayer");
		GetBlackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());	// �����忡 ���� ������ can_see_player���� true�� ��ȯ���ش�.
	}
}

UBlackboardComponent* AMyAIController::GetBlackboard() const
{
	return m_pBlackboard;
}

void AMyAIController::SetupPerceptionSystem()
{
	m_pSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	m_pSightConfig->SightRadius = 500.0f;	// �����Ÿ�
	m_pSightConfig->LoseSightRadius = m_pSightConfig->SightRadius + 50.0f;	// �����Ұ� �Ÿ�
	m_pSightConfig->PeripheralVisionAngleDegrees = 90.0f;	// AI�þ� ��
	m_pSightConfig->SetMaxAge(5.0f);
	m_pSightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;	// �⺻���� �ƴϸ� ���������� �� ��ġ�� �� ���� ���� �ִ� ��� �̹� �� ����� �׻� �� �� ����

	// DetectionByAffiliation ~�� ����(����)�Ǿ� �ν�
	m_pSightConfig->DetectionByAffiliation.bDetectEnemies = true;		// Enemies ����
	m_pSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	m_pSightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// ����(����)�� �ϴ� Component
	GetPerceptionComponent()->SetDominantSense(*m_pSightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTergetDetected);	// Ÿ�� ������ ������Ʈ �Ѵ�
	GetPerceptionComponent()->ConfigureSense(*m_pSightConfig);
}
