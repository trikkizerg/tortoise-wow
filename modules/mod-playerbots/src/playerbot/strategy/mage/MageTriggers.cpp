
#include "playerbot/playerbot.h"
#include "MageTriggers.h"
#include "MageActions.h"

using namespace ai;

bool AnyMageArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("ice armor", target) &&
           !ai->HasAura("frost armor", target) &&
           !ai->HasAura("molten armor", target) &&
           !ai->HasAura("mage armor", target);
}

bool MageArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("mage armor", target);
}

bool IceArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("ice armor", target) &&
           !ai->HasAura("frost armor", target);
}

bool MoltenArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("molten armor", target);
}

bool ManaShieldTrigger::IsActive()
{
    return !ai->HasAura("mana shield", bot) && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.mediumMana;
}

#ifdef MANGOSBOT_ZERO
bool IciclesTrigger::IsActive()
{
    if (!SpellCanBeCastedTrigger::IsActive())
        return false;

    Unit* target = GetTarget();
    if (!target || !target->IsAlive())
        return false;

    if (AI_VALUE2(uint8, "health", "current target") <= 30)
        return false;

    if (AI_VALUE2(uint8, "health", "self target") < 60)
        return false;

    return AI_VALUE(uint8, "my attacker count") == 0;
}

bool IciclesChannelCheckTrigger::IsActive()
{
    if (Spell* spell = bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
    {
        if (spell->m_spellInfo)
        {
            uint32 id = spell->m_spellInfo->Id;
            if (id == 52516 || id == 51991 || id == 51995 || id == 51997)
            {
                Unit* target = AI_VALUE(Unit*, "current target");
                return !target || !target->IsAlive();
            }
        }
    }
    return false;
}

bool EvocationChannelCheckTrigger::IsActive()
{
    if (Spell* spell = bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
    {
        if (spell->m_spellInfo && spell->m_spellInfo->Id == 12051)
        {
            if (!AI_VALUE2(bool, "has mana", "self target"))
                return false;
            return AI_VALUE2(uint8, "mana", "self target") >= 95;
        }
    }
    return false;
}
#endif

bool IceLanceTrigger::IsActive()
{
    Unit* target = GetTarget();
    return target && ai->HasAnyAuraOf(target, "frost nova", "frostbite", NULL);
}

bool HotStreakTrigger::IsActive()
{
    //Usage by id. By name hot streak aura doesn't work.
    return ai->HasAura(48108, bot);
}

bool FireballOrFrostfireBoltFreeTrigger::IsActive()
{
    return ai->HasAura("fireball!", bot);
}

bool NoImprovedScorchDebuffTrigger::IsActive()
{
    if (bot->HasSpell(11095) || bot->HasSpell(12872) || bot->HasSpell(12873))
    {
        return DebuffTrigger::IsActive();
    }

    return false;
}

#ifdef MANGOSBOT_ZERO
bool ArcanePowerTrigger::IsActive()
{
    if (!BuffTrigger::IsActive())
        return false;

    if (!ai->IsStateActive(BotState::BOT_STATE_COMBAT))
        return false;

    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target || !target->IsAlive())
        return false;

    if (!AI_VALUE2(bool, "has mana", "self target"))
        return false;

    return AI_VALUE2(uint8, "mana", "self target") >= 70;
}
#endif