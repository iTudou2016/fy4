 // TIE@FY3
inherit SKILL;
#include <ansi.h> 
void setup() {
        set("name", "打狗棒法");
        set("usage/staff", 1);
        set("usage/parry", 1);
        set("learn_bonus", -200);
        set("practice_bonus", -5);
        set("practice_limit",150);
        set("skill_class", "beggar");   
        set("effective_level", 210);
        set("parry_msg", ({
        "结果$n用手中的$v格开了$N的$w。\n",
        "$n不避不闪，一招「双龙夺珠」，手中$v直取$N的双目。\n",
        "$n挥出$v，蓦地点向$N的面门。\n",
                })
        );
        set("unarmed_parry_msg", ({
        "$n将手中的$v舞得密不透风，封住了$N的攻势。\n",
        "$n不避不闪，一招「双龙夺珠」，手中$v直取$N的双目。\n",
        "$n挥出$v，蓦地点向$N的面门。\n",
                })      
        );      
        action = ({
([      "action": "$N使出一招「棒打双犬」，手中$w化作两道青光砸向$n的$l",
        "dodge": 10,
        "damage": 90,
        "damage_type": "挫伤"
]),
([      "action": "$N手中$w左右晃动，一招「拨草寻蛇」向$n的$l攻去",
        "dodge": 20,
        "damage": 120,
        "damage_type": "挫伤"
]),
([      "action": "$N举起$w，居高临下使一招「打草惊蛇」敲向$n的$l",
        "dodge": 30,
        "damage": 200,
        "damage_type": "挫伤"
]),
([      "action": "$N施出「拨狗朝天」，$w由下往上向$n撩去",
        "dodge": 20,
        "damage": 80,
        "damage_type": "挫伤"
]),
([      "action": "$N施展出打狗棒法中的「守棒揣狗」，$w往$n要害递去",
        "dodge": 20,
        "damage": 150,
        "damage_type": "挫伤"
]),
        });
} 
int valid_learn(object me)
{
    if(!::valid_learn(me)) {
        return 0;
    }
    if( (int)me->query("str") + (int)me->query("max_force") / 10 < 15 ) {
        return notify_fail("你的膂力还不够，也许该练一练内力来增强力量。\n");
        }
        return 1;
} 
int practice_skill(object me)
{
        if( (int)me->query("kee") < 10 ) 
                return notify_fail("你的体力不够练这门棍法，还是先休息休息吧。\n");
        
        if(!::practice_skill(me)) return 0;
        me->add("force",-5);
        return 1;
}  
mixed hit_ob(object me, object victim, int damage_bonus)
{
    object ob;
    if( random(damage_bonus) < 250 ) return 0;
    if(ob=victim->query_temp("weapon"))
    if(ob->query("skill_type") == "whip")
    if(victim->query_skill_mapped("whip") == "thunderwhip")
        if(me->query_skill("staff") > victim->query_skill("whip")) {
        switch(random(3)) {
            case 0:
                    message_vision(HIR "\n因武功路数相克，$N占尽了上风！" NOR,me,victim);
                    break;
            case 1:
                    message_vision(HIR "\n$N轻而易举地抢入$n的空隙之间！" NOR,me,victim);
                    break;
            case 2:
                    message_vision(HIR "\n因棍鞭法相克，$n逐渐施展不开了！" NOR,me,victim);
                    break;
                    }
    return random(me->query_skill("staff")) * 3;
    }
    return 0;
}
