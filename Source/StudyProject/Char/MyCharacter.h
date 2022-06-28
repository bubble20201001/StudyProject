// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasicCharacter.h"
// generated : 리플렉션이 있는 유형으로 마킹하기 위한 헤더, 이 헤더를 기입해야 UHT(Unreal Header Tool)이 매크로를 감지하고 리플렉션 유형에 추가
// 맨 마지막에 존재해야만 원하는 모든 값에 리플렉션을 박아넣을 수 있음
#include "MyCharacter.generated.h"

/**
1. UPROPERTY, UFUNCTION, UCLASS : 언리얼 리플렉션 매크로 / 언리얼 리플렉션 시스템에 해당 매크로가 있음을 알림 / 가비지 콜렉션에 의해 생명 주기 관리 / 리플렉션을 통해 이 멤버 변수의 이름 & 유형 등을 런타임 중 확인 가능
	1-1. UPROPERTY : C++의 변수를 BP와 연동
	2-2. UFUNCTION : C++의 함수를 BP와 연동
	2-3. UCLASS : C++의 클래스를 BP와 연동
* 인자 값 상세 참고 : https://darkcatgame.tistory.com/62
2. 리플렉션 : 프로그램이 실행시간에 자기 자신을 조사하는 기능
 */
UCLASS()
class STUDYPROJECT_API AMyCharacter : public AMyBasicCharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

public:
	//VisibleAnywhere : 모든 프로퍼티 창에 보이지만 편집할 수 없음 /  어떤 "Edit" 지정자와도 호환 불가
	//BlueprintReadOnly :  블루프린트에서 읽을 수는 있지만 변경 불가 / BlueprintReadWrite 지정자와 호환 불가
	//Category : 블루프린트 편집 툴에 이 프로퍼티를 표시할 때의 카테고리를 지정 / 중첩 카테고리는 | 연산자로 정의 / 블루프린트의 내 블루프린트 패널, 우클릭 액션 목록, 디테일 창 등 표시될 수 있는 곳에 카테고리가 매겨짐

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera);
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera);
	class UCameraComponent* FollowCamera;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartJump();
	void EndJump();
	void StartWalk();
	void EndWalk();

private:
	void SetupStimulus();	// 자극을 줘서 몹을 따라오게 만들기 위한 함수

	class UAIPerceptionStimuliSourceComponent* m_pStimulus;
};
