 // bat_poison.c
inherit __DIR__"generic_condition";
#include <ansi.h>
#include <condition.h>  
int update_condition(object me, int duration)
{
        me->receive_wound("kee", 50);
        me->receive_damage("sen", 50);
        me->apply_condition("bat_poison", duration - 1);
        if( duration < 1 )
                tell_object(me, HIG "你中的蝙蝠毒终于发作光了！\n" NOR );
        else
                tell_object(me, RED "你中的蝙蝠毒发作了！\n" NOR );
        if( duration < 1 ) 
                return 0;
        return 1;
}      
