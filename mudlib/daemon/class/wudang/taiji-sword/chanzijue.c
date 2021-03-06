 // tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra, myexp, hisexp;
        
        if ((string)me->query("class") != "wudang")
                return notify_fail(WHT"太极缠字诀是武当不传之秘。\n"NOR);
        
        extra = me->query_skill("taiji-sword",1);
        if ( extra < 150) return notify_fail("你的太极剑法还不够纯熟！\n");
        
        if (userp(me) && me->query_skill_mapped("force") != "taijiforce")
                return notify_fail("［太极剑法］需要［太极心法］的配合！\n");
        
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("［缠字诀］只能对战斗中的对手使用。\n");
        
        if(target->is_busy())
                return notify_fail("对方已经手忙脚乱了。\n");
        
        if (target->query("step_less")==2) 
                return notify_fail(HIW"此人身势灵活，功力深湛，不会被此剑法迷惑的。\n"NOR);
        
        myexp = (int) me->query("combat_exp");
        hisexp= (int)target->query("combat_exp");
        
        if (!userp(target))
        if (hisexp>3500000) 
                hisexp = hisexp*1.5;
        
        message_vision(HIY"$N"HIY"展开太极剑法，剑势圆转如意，划出了一个又一个圈子。\n"NOR,me);
        if(random(hisexp) < myexp*1.2)  {
            message_vision(HIC "$N"HIC"被$n"HIC"的剑法所缠，动作慢了下来！\n"NOR,target,me);
            target->start_busy(2+random(3));
        } else  {
                message_vision(HIW"但是被$N躲开了！\n"NOR,target);        
                me->start_busy(2);
        }
        return 1;
}   
