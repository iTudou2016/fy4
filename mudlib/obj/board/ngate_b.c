 //
inherit BULLETIN_BOARD;
#include <ansi.h>
void create()
{
        set_name( CYN "新手问题墙" NOR, ({ "wall" }) );
        set("location", AREA_FY"ngate");
        set("board_id", "ngate_b");
        set("long",     "一堵便於张贴和涂鸦的城墙。\n" );
        setup();
        set("capacity", 300);
        replace_program(BULLETIN_BOARD);
} 
