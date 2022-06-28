#pragma once

#include "UObject/NameTypes.h"
#include "Containers/UnrealString.h"

// TargetLoaction : 타겟 위치
// CanSeePlayer : 플레이어를 감지했는가
// PlayerIsInAttackRange : 공격 범위 안에 들어왔는가

namespace bb_keys
{
	TCHAR const* const target_location = TEXT("TargetLoaction");
	TCHAR const* const can_see_player = TEXT("CanSeePlayer");
	TCHAR const* const player_is_in_attack_range = TEXT("PlayerIsInAttackRange");
}