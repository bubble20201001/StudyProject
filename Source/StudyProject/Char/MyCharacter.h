// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasicCharacter.h"
// generated : ���÷����� �ִ� �������� ��ŷ�ϱ� ���� ���, �� ����� �����ؾ� UHT(Unreal Header Tool)�� ��ũ�θ� �����ϰ� ���÷��� ������ �߰�
// �� �������� �����ؾ߸� ���ϴ� ��� ���� ���÷����� �ھƳ��� �� ����
#include "MyCharacter.generated.h"

/**
1. UPROPERTY, UFUNCTION, UCLASS : �𸮾� ���÷��� ��ũ�� / �𸮾� ���÷��� �ý��ۿ� �ش� ��ũ�ΰ� ������ �˸� / ������ �ݷ��ǿ� ���� ���� �ֱ� ���� / ���÷����� ���� �� ��� ������ �̸� & ���� ���� ��Ÿ�� �� Ȯ�� ����
	1-1. UPROPERTY : C++�� ������ BP�� ����
	2-2. UFUNCTION : C++�� �Լ��� BP�� ����
	2-3. UCLASS : C++�� Ŭ������ BP�� ����
* ���� �� �� ���� : https://darkcatgame.tistory.com/62
2. ���÷��� : ���α׷��� ����ð��� �ڱ� �ڽ��� �����ϴ� ���
 */
UCLASS()
class STUDYPROJECT_API AMyCharacter : public AMyBasicCharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

public:
	//VisibleAnywhere : ��� ������Ƽ â�� �������� ������ �� ���� /  � "Edit" �����ڿ͵� ȣȯ �Ұ�
	//BlueprintReadOnly :  �������Ʈ���� ���� ���� ������ ���� �Ұ� / BlueprintReadWrite �����ڿ� ȣȯ �Ұ�
	//Category : �������Ʈ ���� ���� �� ������Ƽ�� ǥ���� ���� ī�װ��� ���� / ��ø ī�װ��� | �����ڷ� ���� / �������Ʈ�� �� �������Ʈ �г�, ��Ŭ�� �׼� ���, ������ â �� ǥ�õ� �� �ִ� ���� ī�װ��� �Ű���

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
	void SetupStimulus();	// �ڱ��� �༭ ���� ������� ����� ���� �Լ�

	class UAIPerceptionStimuliSourceComponent* m_pStimulus;
};
