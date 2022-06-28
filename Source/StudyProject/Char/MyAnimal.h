// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasicCharacter.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
#include "MyAnimal.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API AMyAnimal : public AMyBasicCharacter, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	AMyAnimal();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	int melee_attack_Implementation() override;
	UAnimMontage* GetMontage() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage;
};
