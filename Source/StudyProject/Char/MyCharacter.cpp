// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

/*	
1. USpringArmComponent : �� ���� ���� ���� / ������ ����ٴϴ� ī�޶� �����ų �� �־�, ī�޶��� �ε巯�� �������� ��
	ī�޶� ��ü ������Ʈ�� �հ� �������� ���ϵ��� �ϴ� ��ɵ� ����Ǿ� �־�, ����Ī ���ӿ��� �÷��̾ �������� ���� ������ ��Ȳ�� ������
	���ӿ� ���� �ε巯�� ������ ī�޶� �۾��� ���� ������ ���� �� �� ����
2. RootComponent : �𸮾��� ���Ϳ��� ��ġ, ����, ũ�� ������ ���� �̷��� ������ ���� ���� �ʿ��� �κ��� ������Ʈ�� ��ü�ϴ� �������� ���� ��
	RootComponent �� ���� �ٸ� ������Ʈ�� ���� �� �ִ�(Ʈ���� ����)
3. Pawn : ���� �� �÷��̾ AI ��ü�� ���� ������ ǥ��
*/

AMyCharacter::AMyCharacter()
{
	CameraBoom = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));	// ��ü ����
	CameraBoom->SetupAttachment(RootComponent);	// �߽ɿ� �ٿ� �ش�
	CameraBoom->TargetArmLength = 800.0f; // ���� ����
	CameraBoom->bUsePawnControlRotation = true; // ���� ī�޶� �����̼� ��� ���

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // ī�޶� �����뿡 ���� �������� �ٿ���
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // ĳ���� ȸ��

	SetupStimulus();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent); // PlayerInputComponent�� �ִ°�

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AMyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look up / Down Mouse", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::EndJump);

	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AMyCharacter::StartWalk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &AMyCharacter::EndWalk);
}

void AMyCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation(); // Controller�� Rotation�� �˾Ƴ���
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);	// ȸ�� ���� ��ķ� ��ȯ�Ͽ� ������ �˾Ƴ���
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::StartWalk()
{
	// �ȱ� ���¸� �ӵ��� �������� �ٿ���
	GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
}

void AMyCharacter::EndWalk()
{
	// ������ ������� ������
	GetCharacterMovement()->MaxWalkSpeed *= 2.0f;
}

void AMyCharacter::StartJump()
{
	bPressedJump = true;
}

void AMyCharacter::EndJump()
{
	bPressedJump = false;
}

void AMyCharacter::SetupStimulus()
{
	m_pStimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("simulus"));
	m_pStimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());	// ���� ���͸� ������ ���� Ŭ������ �ҽ��� ���
	m_pStimulus->RegisterWithPerceptionSystem();	// �ν� �ý��ۿ� ���
}