 inherit ROOM;
#include <ansi.h> 
void create() 
{
        set("short", "���");
        set("long", @LONG
���죬��ɳ����ɳ�����죬�����Ż�ɳ��ԶԶ����ȥ��һ���ɫ�Ĵ������ڷ�
ɳ�зɾ�����������Զ����ߡ���������ҲԶ����ߣ��ޱ��޼ʵĻ�ԭ��·������
̤�����ģ���������ֱ����ֱͨ��������졣���¾��������á�
LONG
        );
        set("exits", ([ 
                "south" : __DIR__"nstreet3",
                "north" : __DIR__"grassland1a",
        ]));
        set("objects", ([
        ]) );
        set("outdoors", "biancheng");
        set("coor/x",-1110);
        set("coor/y",230);
        set("coor/z",0);
        setup();
        replace_program(ROOM);
}