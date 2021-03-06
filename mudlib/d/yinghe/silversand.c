 // Room: silversand.c --- by MapMaker
inherit ROOM;
string trail();
void create()
{
        set("short", "银色沙丘");
        set("long", @LONG
一大片晶莹洁白的沙丘，似雪如银。脚踩在沙地上，竟然有玲珑悦耳的乐声。
沙丘连绵向南延伸，不知道有多远。北面有一座形式古怪的巨大殿堂。东边一条巨
大的石柱耸天而立。沙地上有一些蜿蜒的痕迹，似乎有什么东西在这里爬过。
LONG);  
        //{{ --- by MapMaker
        set("type","street");
        set("exits",([
                "east":__DIR__"cylinder",
                "southup":__DIR__"silversand2",
                "north":__DIR__"weaponroom",
        ]) );
        //}}
        set("item_desc", ([
                "trail" : (: trail :),
                "痕迹" : (: trail :),
                "sand" : "沙地上有一些蜿蜒的痕迹（ｔｒａｉｌ）。\n",
                "沙" : "沙地上有一些蜿蜒的痕迹（ｔｒａｉｌ）。\n",
        ]));
        setup();
} 
void init(){
        add_action("do_search", "search");
}
string trail(){
        object me;
        me = this_player();
        if(me->query_skill("animal-training") > 50) {
                tell_object(me, "你分辨出那似乎是蛇行过的痕迹，还发现了几片一白色的鳞片。\n");
                tell_object(me, "你意识到着里可能有异蛇。\n");
                me->set_temp("marks/寒水蛇", 1);
        } else {
                tell_object(me, "你不懂驯兽常识那里分辨得出这些痕迹？\n");
        } 
   return "";
} 
int do_search(){
        object me, snake;
        
        me = this_player();
        if(me->is_busy() || me->is_fighting()){
                return notify_fail("你正在忙。\n");
        }
        message_vision("$N在沙丘上仔细寻找。\n", me);
        me->start_busy(1);
        snake = present("hanshui snake", this_object());
        if(objectp(snake)){
                return notify_fail("有条蛇在你眼前不远的沙地上。\n");
        }
        if(!objectp(snake) && query("snake_gone")) {
                return notify_fail("这里已被人翻找过了，看来也找不出什么东西了。\n");
        }
        if(!me->query_temp("marks/寒水蛇")){
                return notify_fail("你胡乱找寻了一通，什么都没有发现。\n");
        }
        if(!random(3) && !objectp(snake)){
                tell_object(me, "你在沙丘的一角看到一条小蛇。银白色的小蛇跟银白色的沙子宛如一体，
不仔细绝难看到。\n");
                snake = new(__DIR__"npc/water_snake");
                if(objectp(snake)){
                        snake->move(this_object());
                }
                set("snake_gone", 1);
        } else {
                tell_object(me, "你什么都没有发现。\n");
        }
        return 1;
} 
void reset(){
        ::reset();
        if(query("snake_gone")){
                delete("snake_gone");
        }
}  
