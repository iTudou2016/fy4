#include <ansi.h>
inherit F_CLEAN_UP; 
int exert(object me,object target,int amount)
{
        object *ob;
        int i, extra,level; 
        
        extra = me->query_skill("libieforce");
        level = me->query_skill("libieforce");
        if(me->query("class")!="swordsuper"&& userp(me))
                return notify_fail("只有剑宗亲传弟子才可以使用"+MAG"【离别】"NOR+"。\n"); 
        if(extra<100)
        	return notify_fail("你的离别心法还不够熟练！\n");
        if(me->query_temp("libieforce_libie"))
                return notify_fail("你已经在施展"+MAG"【离别】"NOR+"了。\n");
        if( (int)me->query("force") < 600 )
                return notify_fail("你的内力不够。\n");
      
        me->add("force", -600);
        
        message_vision(WHT"$N深吸了一口气，暗运离别内功心法，团团紫气围绕在$N的周围......\n"NOR,me);
        if (level>200) level = 200;
        me->set_temp("libieforce_busy",level/50);
        extra= extra+random(extra);
        me->add_temp("libieforce_libie",extra);
        call_out("remove_effect",extra/5,me,extra);
        return 1;
} 
int remove_effect(object me,int extra)
{
        if(!me) return 0;
        me->delete_temp("libieforce_libie");
        me->delete_temp("libieforce_busy");
        tell_object(me,"你"+MAG"离别心法"NOR+"的效果已经消失了。\n");
        return 1;
}
