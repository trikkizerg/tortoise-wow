
#include "playerbot/playerbot.h"
#include "RogueTriggers.h"
#include "RogueActions.h"

using namespace ai;

bool RiposteCastTrigger::IsActive()
{
	Unit* target = GetTarget();
	if (!target)
		return false;

	bool isMelee = true;
	if (target->IsPlayer())
	{
		isMelee = !ai->IsRanged((Player*)target);
	}

	return SpellCanBeCastedTrigger::IsActive() && isMelee;
}

#ifdef MANGOSBOT_ZERO
bool SurpriseAttackTrigger::IsActive()
{
    Unit* target = GetTarget();
    if (!target)
        return false;

    bool isMelee = !target->IsPlayer() || !ai->IsRanged((Player*)target);
    return SpellCanBeCastedTrigger::IsActive() && isMelee;
}

bool ShadowOfDeathTrigger::IsActive()
{
    if (!SpellCanBeCastedTrigger::IsActive())
        return false;

    if (AI_VALUE2(uint8, "combo", "current target") < 5)
        return false;

    return AI_VALUE2(uint8, "health", "current target") > 30;
}

bool MarkForDeathTrigger::IsActive()
{
    if (!SpellCanBeCastedTrigger::IsActive())
        return false;

    return AI_VALUE2(uint8, "health", "current target") > 50;
}
#endif