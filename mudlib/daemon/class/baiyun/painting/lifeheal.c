 // lifeheal.c
#include <ansi.h> 
int exert(object me, object target, int amount)
{
        if( !target )
                return notify_fail("你要用真气为谁疗伤？\n"); 
        if( me->is_fighting() || target->is_fighting())
                return notify_fail("战斗中无法运功疗伤！\n"); 
        if( (int)me->query("force") < 150 )
                return notify_fail("你的真气不够。\n"); 
        if (target!=me){
        message_vision(HIC "$N运起画道内功，手掌轻贴在$n背心，缓缓地将真气输入$n体内....\n\n"NOR,me,target);
        message_vision(HIC"过了不久，$N额头上冒出豆大的汗珠，$n吐出一口瘀血，脸色看起来红润多了。\n"NOR,me,target);
        }       else
        {message_vision(HIY "$N运起画道内功，缓缓地将真气在体内流转....\n\n"NOR,me);
        message_vision(HIY"过了不久，$N吐出一口瘀血，脸色看起来红润多了。\n"NOR,me);
        }
        target->receive_curing("kee", 10 + (int)me->query_skill("painting",1));
        me->add("force", -50);
        me->set("force_factor", 0); 
        return 1;
}
