 // fengyu-piaoxiang.c  风雨飘香步
inherit SKILL;
#include <ansi.h> 
void setup() {
        set("name", "风雨飘香步");
        set("usage/dodge", 1);
        set("usage/move", 1);
        set("effective_level", 120);
        set("practice_damage", 60);
        set("learn_bonus", -500);
        set("practice_bonus", -50);
        set("black_white_ness", 0);
        set("skill_class", "bat");
        set("dodge_msg", ({
            "$n一个「漠漠帆来重」，随着$N的攻势飘起，从容躲过这一招。\n",
            "$n使出一招「冥冥鸟去迟」，猛然纵起丈余，结果$N扑了个空。\n",
            "$n身形一摇，幻出几个人影，一招「山风吹空林」躲过了$N的攻势。\n",
            "$n一招「千峰同一色」纵身跃起，倏忽已落至$N身后。\n",
            "$n左一摇，右一晃，一招「落月去清波」已轻松闪过。\n",
            "$n双足一点，斜斜飞起，使出「皎皎孤月轮」已闪到$N身侧。\n",
        }) ); 
} 
int practice_skill(object me)
{
        if (me->query_skill("fengyu-piaoxiang",1) > 180)
                return notify_fail("练习已经不能加深你的领悟，只能通过学习来提高了。\n");       
        if ((int)me->query("force") < 20) {
                return notify_fail("你的内力不够练习。\n");
        }
        if(!::practice_skill(me)) {
                return 0;
        }
        me->add("force", -10);
        return 1;
}      

void skill_improved(object me)
{
        int s, n;
        s = me->query_skill("fengyu-piaoxiang", 1);
		if (s>320 && s%10==1 && me->query_skill("move",1)>320) {
			n = (s-311)/5;
			if( n > 10 ) n = 10;
			if( me->query("no_busy") < n ) {
			me->set("no_busy",n);
            tell_object(me, HIY "你长长地呼了口气。。。就在这刹那间，你对轻功的领悟达到了更高的境界！！！\n" NOR);
			}
		}
}