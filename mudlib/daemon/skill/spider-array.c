 // spider-array.c
#include <ansi.h> 
inherit SKILL;
void setup(){
        set("name", "灵蛛剑阵");
        set("usage/array", 1);
        set("effective_level", 200);
        set("learn_bonus", 40);
        set("practice_bonus", 20);
        set("black_white_ness", 40);
} 
int form_array(object leader)
{
        object *member; 
        member = leader->query_team();
        if( sizeof(member) != 8 )
                return notify_fail("灵蛛剑阵共需八人，少一个多一个都不行。\n");
        message_vision( HIG "$N率领众人四下站定八个方位，组成了「灵蛛剑阵」！\n" NOR, leader);
        return 1;
}   
