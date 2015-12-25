 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
inherit ROOM;
void create()
{
  set("short","经石峪");
  set("long",@LONG
这是与大观峰遥相呼应，是一处规模更大的摩崖石刻，年代远溯到北
齐，距今已然有１４００年历史了，在这天然石坪之上，密密麻麻的刻着
《金刚般若波罗蜜经》。经文字大如斗，篆隶兼备，书法遒劲，历代尊为
“大字鼻祖”，“榜书之宗”，千年风雨，现在经文只有一千多字了，但
却依然无可比拟。
LONG
  );
  set("exits",([
        "westdown" : __DIR__"doumu",
        "southup" : __DIR__"luohan",
               ]));
        set("objects", ([
        __DIR__"obj/jingwen" : 1,
                        ]) );
        set("outdoors", "fengyun");
        set("coor/x",320);
        set("coor/y",2380);
        set("coor/z",40);
        setup();
        replace_program(ROOM);
}     
