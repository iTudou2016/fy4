#include <ansi.h>
inherit SKILL;
void setup() {
        set("name", "媚术");
//      set("usage/spells", 1);
        set("effective_level", 100);
        set("skill_class", "shenshui");
} 
int practice_skill(object me)
{
    return notify_fail("媚术只能用学的 \n");
}   
void skill_improved(object me) {
        int s;
        s = me->query_skill("charm", 1);
        if( s%10==9 && (int)me->query("per") < s/5) {
                tell_object(me, HIM "由於你勤练媚术，你的魅力提高了。\n" NOR);
                me->set("per",(s+1)/5);
//              me->add("per", 2);
        }
}  
