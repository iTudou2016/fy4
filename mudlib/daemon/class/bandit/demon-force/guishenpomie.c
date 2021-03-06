// guishenpomie.c by ice@fy4
#include <ansi.h>
inherit F_CLEAN_UP; 
int exert(object me, object target, int amount)
{
		object weapon;
        int extra;

        if( target != me ) 
                return notify_fail("［鬼神破灭］只能对自己使用。\n");  
        extra = me->query_skill("demon-force", 1);
        if(extra < 100) 
                return notify_fail("你的天地人魔心法不够纯熟，无法使用［鬼神破灭］。\n");
		if(me->query_skill("blade", 1) < 100)
                return notify_fail("你对刀法的领悟不够。\n");
        if(me->is_fighting())
                return notify_fail("战斗中不能使用［鬼神破灭］！\n");    
        if( (int)me->query_temp("bladeup") ) 
                return notify_fail("你已经在运功中了。\n"); 
        if( (int)me->query("force") < 100 )
                return notify_fail("你的内力不够。\n");
  
        if (userp(me)) me->add("force", -100);
        
        message_vision(HIB "\n$N"+HIB"运起天地人魔心法，全身泛出淡淡的蓝光。。。\n" NOR, me);   
        write(HIY"你觉得自己对刀法使用更加得心应手！\n"NOR); 

        me->add_temp("apply/blade", extra/4);
        me->set_temp("bladeup", 1); 
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, extra/4 :), extra);

        return 1; 
} 

 
void remove_effect(object me, int amount)
{
        me->add_temp("apply/blade", -amount);
        me->delete_temp("bladeup");
        tell_object(me, WHT"你感觉双臂一阵酸软，［鬼神破灭］的效果似乎消失了。\n"NOR);
}
