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

	// ConstructorHelpers::FObjectFinde : Asset의 내용물을 가져올 때 사용
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
		m_pBlackboard->InitializeBlackboard(*BTree->BlackboardAsset);	// BTree가 올바르게 초기화 되면 true 반환
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
	if (auto const ch = Cast< AMyCharacter>(actor))	// 플레이어(MyCharacter)를 감지했는가
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "FindPlayer");
		GetBlackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());	// 블랙보드에 내가 설정한 can_see_player값에 true를 반환해준다.
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

	m_pSightConfig->SightRadius = 500.0f;	// 감지거리
	m_pSightConfig->LoseSightRadius = m_pSightConfig->SightRadius + 50.0f;	// 감지불가 거리
	m_pSightConfig->PeripheralVisionAngleDegrees = 90.0f;	// AI시야 각
	m_pSightConfig->SetMaxAge(5.0f);
	m_pSightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;	// 기본값이 아니면 마지막으로 본 위치의 이 범위 내에 있는 경우 이미 본 대상을 항상 볼 수 있음

	// DetectionByAffiliation ~에 연계(제휴)되어 인식
	m_pSightConfig->DetectionByAffiliation.bDetectEnemies = true;		// Enemies 감지
	m_pSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	m_pSightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// 지각(인지)를 하는 Component
	GetPerceptionComponent()->SetDominantSense(*m_pSightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTergetDetected);	// 타겟 감지를 업데이트 한다
	GetPerceptionComponent()->ConfigureSense(*m_pSightConfig);
}
