 // powerup.c
#include <ansi.h> 
inherit F_CLEAN_UP; 
void remove_effect(object me, int amount); 
int exert(object me, object target, int amount)
{
    int skill;
    
    if( target != me )
        return notify_fail("你只能用九阴心经提升自己的战斗力。\n");
    if( (int)me->query("force") < 100 )
        return notify_fail("你的内力不够。\n");
    if( (int)me->query_temp("powerup") )
        return notify_fail("你已经在运功中了。\n"); 
    skill = me->query_skill("nine-moon-force",1);
    me->add("bellicosity", skill);
    me->add("force", -100); 
    message_vision(
        HIR 
"$N眼观鼻，鼻观口，口观心，施展九阴心经，聚虚为实，全身透出阴寒无比的真气！\n" NOR, me); 
    me->add_temp("apply/attack", skill);
    me->add_temp("apply/dodge", skill);
    me->set_temp("powerup", 1); 
    me->start_call_out( (: call_other, __FILE__, "remove_effect", me, 
                         skill :), skill); 
    if( me->is_fighting()) me->start_busy(1); 
    return 1;
} 
void remove_effect(object me, int amount)
{
    me->add_temp("apply/attack", - amount);
    me->add_temp("apply/dodge", - amount);
    me->delete_temp("powerup");
    tell_object(me, "你的九阴心经运行完毕，将内力收回丹田。\n");
}
    
