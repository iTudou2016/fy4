 //Created by justdoit at May 2001
//All Rights Reserved ^_^ 
 
inherit ROOM; 
void create() 
{ 
        set("short", "����");
        set("long", @LONG 
����ϰϰ��΢΢��Щ��ζ֮�м����˱ǻ��㣬ԶԶ��ȥ���������۵�С��������
�дУ�һ���̡�һ�ź졢һ�Żơ�һ���ϣ��˵��Ƿ����ƽ�����Ӣ�ͷס����Ƶ�����
��֮�ˣ�����ůʪ����ľ���̣����ݷ�ï�������Ͽɰ�����Ů���ǽ������ɰ�������
��������������˱Ȼ��㡣
LONG 
           ); 
        set("exits",  
           ([  
       "northeast" : __DIR__"flowerroad2",
       "southup" : __DIR__"yuhuage",
            ])); 
        set("objects",  
           ([  
       __DIR__"npc/flowergirl" : random(3),
       __DIR__"npc/xiaofan" : 1,
            ])); 
        set("outdoors", "baiyun"); 
        set("coor/x",10); 
        set("coor/y",-1600); 
        set("coor/z",0); 
        setup(); 
        replace_program(ROOM); 
}     
