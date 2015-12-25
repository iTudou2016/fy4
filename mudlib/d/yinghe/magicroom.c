 // Room: magicroom.c --- by MapMaker
inherit ROOM; 
void create()
{
        set("short", "静心石"); 
        set("long", @LONG
这是一块空地，目前什么都还没有修。
LONG);
        set("long_night", @LONG
这是一块空地，到了晚上就更不要指望看见什么。
LONG); 
        //{{ --- by MapMaker
        set("type","street");
        set("exits",([
        "east":__DIR__"monsterroom",
        "west":__DIR__"foodroom",
        "north":__DIR__"wineroom",
        ]) );
        //}} 
        setup();
        replace_program(ROOM);
}  
