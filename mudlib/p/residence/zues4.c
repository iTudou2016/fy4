#include <ansi.h>
#define X_COOR 0
#define Y_COOR 2040
#define Z_COOR 50
inherit ROOM;
void create()
{
set("short", WHT"卧房"NOR);
set("long", @LONG
这是主人的卧室，中间是一张床（bed)，东面是一个窗户，透过窗户，你可以
看到楚楚和唠叨的房子，靠窗处摆着一束鲜花，淡淡的芬芳散发在空气中。
LONG
);
        set("exits", ([
		"west" : __DIR__"zues3",
]));

set("objects", ([
       ]) );

        set("item_desc", ([
                "bed": "一张柔软的大床，睡上去一定很舒服。\n",
                "床": "一张柔软的大床，睡上去一定很舒服。\n",
        ]) );

        set("coor/x",X_COOR);
        set("coor/y",Y_COOR);
        set("coor/z",Z_COOR);
        set("indoors","residence");
        setup();
}
void init()
{
        add_action("do_sleep", "sleep");
}
    
int do_sleep(string arg)
{
   object me, obj, girl;
   int gin, kee, sen; 
   me = this_player();
   obj = this_object(); 
   if (me->is_fighting()) return 1;
   if (this_object()->query_temp("marks/taken")) {
      tell_object(me, "床上有人耶。。。。\n");
      return 1;
   }
      else{
      message_vision("$N揉揉眼、打个哈欠，躺到了床上，", me);
      tell_object(me, "很快你就觉的睡意朦胧。\n");
      message("vision", me->name()+"翻了几个身，找到个舒适的姿势，很快就进入了梦乡。\n", environment(me), me);
      obj->set_temp("marks/taken", 1);
      gin = (int) me->query("eff_gin");
      kee = (int) me->query("eff_kee");
      sen = (int) me->query("eff_sen");
      me->set("gin", gin);
      me->set("kee", kee);
      me->set("sen", sen);
      me->set_temp("disable_inputs",1);
      me->set_temp("block_msg/all",1);
      me->set_temp("is_unconcious",1);
      me->set("disable_type",HIG "<睡梦中>"NOR); 
      call_out("wake", 10, me);
      return 1;
   }
   return 1;
} 
void wake(object me)
{
   object obj; 
   obj = this_object();
   me->delete_temp("disable_inputs");
   me->delete("disable_type");
   me->delete_temp("block_msg/all");
   me->delete_temp("is_unconcious");
   if(!me->is_ghost())
   message_vision("$N睁开了眼睛，一个鲤鱼打挺从床上跳了下来。\n", me); 
   tell_object(me, "你觉得精神好了很多。\n");
   obj->set_temp("marks/taken", 0);  
}  