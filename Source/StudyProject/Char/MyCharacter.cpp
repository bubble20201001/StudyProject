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
1. USpringArmComponent : 폰 보다 느린 가속 / 감속을 따라다니는 카메라에 적용시킬 수 있어, 카메라의 부드러운 부착점이 됨
	카메라가 입체 오브젝트를 뚫고 지나가지 못하도록 하는 기능도 내장되어 있어, 삼인칭 게임에서 플레이어가 구석에서 벽을 등지는 상황에 유용함
	게임에 보다 부드러운 느낌의 카메라 작업을 아주 빠르고 쉽게 얻어낼 수 있음
2. RootComponent : 언리얼엔진 액터에는 위치, 방향, 크기 정보가 없어 이러한 정보를 같기 위해 필요한 부분을 컴포넌트가 대체하는 과정에서 나온 것
	RootComponent 는 하위 다른 컴포넌트를 가질 수 있다(트리로 관리)
3. Pawn : 월드 내 플레이어나 AI 개체에 대한 물리적 표현
*/

AMyCharacter::AMyCharacter()
{
	CameraBoom = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));	// 객체 생성
	CameraBoom->SetupAttachment(RootComponent);	// 중심에 붙여 준다
	CameraBoom->TargetArmLength = 800.0f; // 길이 조정
	CameraBoom->bUsePawnControlRotation = true; // 폰의 카메라 로테이션 제어를 허용

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 카메라를 지지대에 소켓 네임으로 붙여줌
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터 회전

	SetupStimulus();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent); // PlayerInputComponent가 있는가

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
		const FRotator Rotation = Controller->GetControlRotation(); // Controller의 Rotation을 알아낸다
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);	// 회전 값을 행렬로 변환하여 전방을 알아낸다
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
	// 걷기 상태면 속도를 절반으로 줄여줌
	GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
}

void AMyCharacter::EndWalk()
{
	// 해제시 원래대로 돌려줌
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
	m_pStimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());	// 소유 액터를 지정된 감지 클래스의 소스로 등록
	m_pStimulus->RegisterWithPerceptionSystem();	// 인식 시스템에 등록
}