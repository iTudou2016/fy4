 // 燕南天的南天步法
inherit SKILL;
void setup(){
        set("name", "碧空步法");
        set("usage/dodge", 1);
        set("usage/move", 1);
        set("practice_damage", 100);    
        set("effective_level", 400);
        set("learn_bonus", -700);
        set("black_white_ness", 10);
        set("skill_class", "emei");
        set("dodge_msg", ({
        "$n身形轻灵，一招「浮云终日行」，有若天上的白云一般，令$N的攻势遥不可及。\n",
        "$n身形微动，一式「游子久不至」，倏地挪开，竟令$N找不到了$n的身影。\n",
        "$n抚首微喟，却在刻不容缓之际纵身拔起，化解了$N的攻势，正是一招「出门搔白首」。\n",
        "却见$n面现忧色，使出「若负平生志」，似是有气无力的身形一转，却恰好让$N的攻势落空。\n"
        }) );
} 
int practice_skill(object me)
{
	if( me->query("family/master_id") != "master yichen" && me->query("class") != "emei")
        return notify_fail("碧空步法只能学的。\n");
}
