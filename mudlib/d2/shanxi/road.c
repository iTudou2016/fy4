inherit ROOM;
void create()
{
        set("short", "瀑布边");
        set("long", @long
绕过小道，走上山来，能远远望见那壶口瀑布。山道延着瀑布边，路过黄河，
指向林中的村庄。此地两岸夹山，河底石岩上冲刷成一巨沟，滚滚黄水奔流至此，
倒悬倾注，若奔马直入河沟，波浪翻滚，惊涛怒吼，震声数里可闻。其形如巨壶沸
腾，故名「壶口瀑布」。
long
        );
        
        set("exits", ([ 
  "north" :__DIR__"shulin",
  "east" : __DIR__"road1",
  "southwest" : "/d/chenxiang/road",
]));
        set("outdoors", "shanxi");
                set("no_magic",1);
        set("NONPC",1);

        set("coor/x",-500);
        set("coor/y",-400);
        set("coor/z",100);
        setup();
}

void init()
{
        add_action("do_go","go"); 
} 
int do_go()
{
if(random(10)){
this_player()->move(this_object());
return 1;
}
} 