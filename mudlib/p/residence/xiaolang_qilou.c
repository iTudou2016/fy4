#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
  set("short",HIG"棋楼"NOR);
  set("long",@LONG
这里是庄主萧十一郎邀人对局之处，主人10岁开始学象棋，从师自父亲，15岁
开始自学围棋，颇有小成，昔年与挚友在此间大战三天三夜，最后以半子负于对手
，憾甚！房间布置简单优雅，墙壁上绘满古时候的名家残局，想来主人闲暇之时便
来此与人对弈。
LONG
  );
  set("exits",([
                 "northdown" : __DIR__"xiaolang2", 
                 "northeast" : __DIR__"xiaolang_qinlou",
                 "northwest" : __DIR__"xiaolang_shulou",       
               ]));
    set("indoors", "residence");
        set("coor/x",15);
        set("coor/y",2034);
        set("coor/z",40);
        set("no_death_penalty",1);
        setup();
    replace_program(ROOM); 
}       
