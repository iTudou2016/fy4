 // TIE@FY3 ALL RIGHTS RESERVED
inherit ROOM;
void create()
{
        set("short", "�ص�");
        set("long", @LONG
���澹�������ص��������ǵ�̾��µ�ʯ�ڣ�����Ƕ
�ŷ�����ͭ�ơ� 
LONG
        );
        set("exits", ([ 
                "north" : __DIR__"palace3",
                "south" : __DIR__"palace1",
                        ]));
        set("objects", ([
//              __DIR__"npc/nun" : 2,
        ]) );
        set("indoors", "eren");
        set("coor/x",0);
        set("coor/y",0);
        set("coor/z",0);
        setup();
        replace_program(ROOM);
}       