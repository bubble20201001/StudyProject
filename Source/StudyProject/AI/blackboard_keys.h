#pragma once

#include "UObject/NameTypes.h"
#include "Containers/UnrealString.h"

// TargetLoaction : Ÿ�� ��ġ
// CanSeePlayer : �÷��̾ �����ߴ°�
// PlayerIsInAttackRange : ���� ���� �ȿ� ���Դ°�

namespace bb_keys
{
	TCHAR const* const target_location = TEXT("TargetLoaction");
	TCHAR const* const can_see_player = TEXT("CanSeePlayer");
	TCHAR const* const player_is_in_attack_range = TEXT("PlayerIsInAttackRange");
}