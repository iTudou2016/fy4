 inherit ROOM;
void create()
{
        set("short", "ɽ�����"); 
        set("long", @LONG
���������ģ������ȥ�����������Լ�����ָ�����¿Ŀİ�����Ҳ��֪��
��ȵ�ʲô�������������Ǿ���������·�ĺá�Զ����ͣ�Ĵ�������ɽϪ������
�����ƺ��ڸ����㲻Զ�ĵط������������е�������Դ��
LONG);
        set("outdoors", "fugui");
        set("type","road");
        set("exits",([
                "east":__DIR__"shanlin1",
                "south":__DIR__"shanlu3",
        ]) );
        set("coor/x",-610);
        set("coor/y",160);
        set("coor/z",20);
        setup();
        replace_program(ROOM);
}       