 // thunderwhip.c
#include <ansi.h> 
inherit SKILL;
void setup(){
        set("name", "天雷破");
        set("usage/whip", 1);
        set("usage/parry", 1);
        set("effective_level", 180);
        set("learn_bonus", 20);
        set("practice_bonus", -200);
        set("black_white_ness", 20);
        set("skill_class", "yinshi");
        set("parry_msg", ({
        "$n一鞭转空，身形籍式升空三尺，反手连戳三鞭“太古神龙三掉尾”，卷起一道鞭焰，护住全身。\n",
                "$n一招“横扣天机”，贯运真力，直截$N手中的$w\n",
                "$n右臂向后一摆，手中的$v向前卷出，鞭影象雪花般罩住了$N。\n",
                "$n急踏步移形换位，让开这一招。\n",
        }) ); 
        set("unarmed_parry_msg", ({
        "$n一鞭转空，身形籍式升空三尺，反手连戳三鞭“太古神龙三掉尾”，卷起一道鞭焰，护住全身。\n",
        "$n右臂向后一摆，手中的$v向前卷出，鞭影象雪花般罩住了$N。\n",
        "$n急踏步移形换位，让开这一招。\n",
        }) );
        
        action = ({
                ([
                        "action":               
                        "$N惊叱一声，双手并举，寒光陡飞，霎时人鞭合一，凌空直向$n飞去",
                        "dodge":                100,
                        "damage":               60,
                        "damage_type":  "刺伤"
                ]),
                ([
                        "action":               
                        "$N手中鞭影乍迸，卷起万重电光，“太古开天”轰然横扫。",
                        "dodge":                500,
                        "damage":               40,
                        "damage_type":  "瘀伤"
                ]),
                ([
                   "action":               
                        "$N鞭式一变，杀机四布，展开了天雷破有去无回的杀招“太古伏羲说八卦”",
                        "dodge":                400,
                        "damage":               150,
                        "damage_type":  "刺伤"
                ]),
                ([
                        "action":               
                        "$N跃起三丈，身在半空，招式陡变，“太古神龙”如惊涛骇浪，卷转电擎而落",
                        "dodge":                400,
                        "damage":               60,
                        "damage_type":  "瘀伤"
                ]),
        });
}
int valid_learn(object me)
{
        object ob; 
        if( (int)me->query("max_force") < 50 ){
                return notify_fail("你的内力不够，没有办法练天雷破, 多练些内力再来吧。\n");
        }
        if(!::valid_learn(me)){
                return 0;
        }
        return 1;
} 
int practice_skill(object me)
{
        if((int)me->query("force") < 10 ){
                return notify_fail("你的内力不够，没有办法练习天雷破。\n");
        }
        if(!::practice_skill(me)){
                return 0;
        }
        me->add("force", -10);
        write("你按著所学练了一遍天雷破。\n");
        return 1;
} 
mixed hit_ob(object me, object victim, int damage_bonus)
{
    object ob,weapon;
    int cele;
    
    if( random(damage_bonus) < 250 ) return 0;
    if(ob=victim->query_temp("weapon"))
    if(ob->query("skill_type") == "hammer")
    if(victim->query_skill_mapped("hammer") == "pangu-hammer"
     ||victim->query_skill_mapped("hammer") == "assasin-hammer"
     ||victim->query_skill_mapped("hammer") == "liuxing-hammer")
    if(me->query_skill("whip")+50 > victim->query_skill("hammer")) {
    switch(random(3)) {
            case 0:
                    message_vision(HIR "\n因武功路数相克，$N占尽了上风！" NOR,me,victim);
                    break;
            case 1:
                    message_vision(HIR "\n$N轻而易举地抢入$n的空隙之间！" NOR,me,victim);
                    break;
            case 2:
                    message_vision(HIR "\n因鞭锤法相克，$n逐渐施展不开了！" NOR,me,victim);
                    break;
                    }
    return random(me->query_skill("whip")) * 4;
    }
    return 0;
}        
