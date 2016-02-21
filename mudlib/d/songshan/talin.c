 // TIE@FY3 ALL RIGHTS RESERVED
inherit ROOM;
void create()
{
        set("short", "塔林");
        set("long", @LONG
东接少林寺，是嵩山最灵秀之地，占地万余平方米，自唐至清
历时千年的少林方丈，高僧大都埋骨于此，大大小小二百二十多座
砖石墓塔，按照死者生前的佛学地位，修养等等大小不一，高下不
一的排列着。墓塔造型各异，是研究古代砖石建筑，雕刻艺术的宝
库，最为出名的便是天竺和尚就公塔和日僧的菊庵塔。
LONG
        );
        set("exits", ([ 
  "east" : AREA_SHAOLIN"houmen",
  "northeast" : __DIR__"huishan",
  "northwest" : __DIR__"damo",
  "south" : __DIR__"erzu",
]));
        set("outdoors", "songshan");
        set("objects", ([
                __DIR__"obj/ta1" : 1,
                __DIR__"npc/lama3" : 1,
       ]) );
        
        set("coor/x",-220);
        set("coor/y",410);
        set("coor/z",70);
        setup();
        replace_program(ROOM);
}     
