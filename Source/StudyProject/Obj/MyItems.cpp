// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItems.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "MyBasicCharacter.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "MyGameInstance.h"

// Sets default values
AMyItems::AMyItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 메시
	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obj"));
	RootComponent = mStaticMesh;

	// 충돌스피어
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(100.0f);
	CollisionSphere->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyItems::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 오브젝트와 내 캐릭터가 충돌
	if (OtherActor->IsA(AMyCharacter::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Collision Touch"));

		// 현재 내 인스턴스 가져오기
		UMyGameInstance* GameInst = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		// 인벤토리에 넣어주기
		if (IsValid(GameInst))
		{
			FItemTableInfo* getitem = GameInst->GetItemInfo(ItemUnique);

			Destroy();
		}
	}
}