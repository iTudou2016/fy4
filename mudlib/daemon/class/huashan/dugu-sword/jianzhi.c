 // ice@fy4
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra, bonus, i, n, num;
        
        object *enemy;

        if ( me->query("class")!= "huashan")
			return notify_fail("只有华山弟子才能领悟独孤精要。\n");
        if((int)me->query_skill("dugu-sword",1) < 200)
            return notify_fail("你的独孤九剑还不够精纯！\n");      

        enemy = me->query_enemy();

        if(!sizeof(enemy))
            return notify_fail("［剑指中原］只能对战斗中的对手使用。\n");
        if(target)
            return notify_fail("剑指中原不需要指定使用对象！！\n");
                
        msg = HBCYN "\n$N"+HBCYN"的剑尖忽然倒地，全身力量将剑身压成了弓状，继然借力一跃而起！！！\n\n"NOR;
        message_vision(msg,me);
		num = sizeof(enemy);
		n = num;
		if(n==1) n=2;
		if(n > 3) n = 3;

        extra = me->query_skill("sword") + me->query_skill("move") + n*100;
		bonus = me->query("combat_exp")/1000*extra/8000;
        if((int)me->query_skill("dugu-sword",1) > 250) extra = extra + bonus;
        for(i=0;i<num;i++)
        {
			target = enemy[i];
            if(target->query("combat_exp") < random((int)me->query("combat_exp"))*10+(int)me->query("combat_exp")/3) {
                message_vision(HIW"\n剑光从天而降，笼罩着$N"+HIW"！"NOR+RED"剑"+HIY"　指"NOR+BLU"　中"+HIG"　原"+NOR"，"+HIR"独"NOR+YEL"　步"+HIB"　八"NOR+GRN"　方"+NOR"！！\n\n"NOR,target);
                target->receive_wound("kee",random(extra/2)+extra/2);
                target->receive_damage("kee",extra+extra/2);
                target->set_temp("last_damage_from",me);
                COMBAT_D->report_status(target);
				COMBAT_D->win_lose_check(me,target,1);
			}
			else message_vision(NOR"\n但$n"+NOR"看准来势，闪身避过了$N"+NOR"这一剑！\n\n"NOR,me,target);

		}

        if (me->query_busy()<n) 
                me->start_busy(n);
        return 1;
}  
