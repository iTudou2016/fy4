 // a skeleton for user rooms
#include <ansi.h>
#define X_COOR 15
#define Y_COOR 2050
#define Z_COOR 50
#define R_FLAG 17
#define OWNER "txdizi"
#define CLASS "铁雪山庄"
inherit ROOM;
void create()
{
set("short", "四知书屋");
set("long", @long
面阔五间、外形简朴的四知书屋，以小巧的竹帘与小庐相通。
所谓“四知”源于《周易·系词》：“群子知微、知彰、知柔、知刚。”
房中搁了几个木凳，一张木桌。上面有些小碟小盏，里面是些糕点茶水，
但凡来拜访的客人渴了饿了，都可随意食用。

long
);
        set("exits", ([
        

"east" : __DIR__"txdizi1",

]));
set("objects", ([
//"/p/residence/npc/featherwa" : 1,
       ]) );
        set("coor/x",X_COOR);
        set("coor/y",Y_COOR);
        set("coor/z",Z_COOR);
        set("room_flag",R_FLAG);
        set("owner", OWNER);
        set("class", CLASS);
        set("gao_amount", 100);
        set("tea_amount", 100);
        set("indoors","residence");
        
        setup();
}
void init()
{
        int flag;
        flag = (int) query("room_flag");
        if(flag & 1) set("valid_startroom",1);
   if(flag & 2) set("NONPC",1);
        if(flag & 4) set("no_fight",1);
        if(flag & 8) set("no_magic",1);
        if(flag & 16) set("indoors","residence");
        add_action("do_invite","invite");
        add_action("do_setowner","setowner");
        add_action("do_list","list");
                add_action("do_look", "look");
        add_action("do_eat", "eat");
        add_action("do_drink", "drink");
}
int valid_enter(object me)
{
        int flag;
// means no enter at the beginning.
        int enter = 0;
    flag = (int) query("room_flag");
// always let owner go in:
        if((string)me->query("id") == (string)query("owner"))
        enter = 1;
        if(flag & 16)
        enter = 1;
        if(flag & 512)
        if((string)me->query("id") == (string)query("owner"))
        enter = 1;
        if(flag & 1024)
        if((string)me->query("class") == (string)query("class"))
        enter = 1;
        if(flag & 2048) 
        {
                if(strlen(query("invite")) && strsrch((string)query("invite"),"["+(string)me->query("id")+"]") != -1)
                enter = 1;
        }
//      write(sprintf("%d", enter));    
        return enter;
}
int do_list()
{
        object me;
        string *list,invitelist;
        me = this_player();
        if((string)me->query("id") != (string)query("owner"))
        return 0;
   invitelist = query("invite");
        if (strlen(invitelist))
        {
                list = explode("]"+invitelist+"[", "][");
                write("你邀请了下列玩家到你的房间:\n");
                for(int i=0;i<sizeof(list);i++)
                        write(list[i]+"\n");
        }else
                write("你没有邀请任何人到你的房间。\n");
        return 1;
} 
int do_invite(string arg)
{
        object me;
        string invitelist;
        me= this_player();
        if((string)me->query("id") != (string)query("owner"))
        return 0;
        if( !arg )
        {
                write("你要邀请谁? \n");
                return 1;
        }
        invitelist = (string)query("invite");
        if(strlen(invitelist) && strsrch(invitelist,"["+arg+"]") != -1)
        {
                //if the person has already been invited, remove it from invite list.
                invitelist = replace_string(invitelist,"["+arg+"]","");
                set("invite",invitelist);
                write("你将"+arg+"从你的邀请名单中除去。\n");
        }else
        {
                //invite the person.
                if( find_player(arg))
                {
                        if(!strlen(invitelist))
                                set("invite","["+arg+"]");
                        else
                                set("invite",invitelist+"["+arg+"]");
                        write("你邀请"+arg+"来你的房间。\n");
           }else
                {
                        write("咦... 有这个人吗?\n");
                }
        }
        return 1;
} 
int do_setowner(string arg)
{
        string oldowner;
        oldowner = (string)query("owner");
        set("owner",arg);
        write("你将房间的主人暂时设为"+arg+"。\n");
        call_out("set_back",60, oldowner);
        return 1;
} 
int set_back(string oldowner)
{
        set("owner", oldowner);
        return 1;
}
  

int do_look(string arg) {
        object me;
        int i, j;
        
        me = this_player();

    i = query("gao_amount");
    j = query("tea_amount");
    if( !arg || arg != "table" && arg != "木桌" && arg !="小盏" && arg!= "teacup" 
) return 0;
    if(arg == "table" || arg == "石桌") {
                if (i > 0) {
            write("木桌上有几盘精致的小碟，里面有些梅花糕，可以吃（ｅａｔ）的。\n");
                } else {
            write("木桌上面有几个小碟，里面只剩下了一些糕点残渣。\n");
                }       
        me->set_temp("know_gao", 1);
    } else if (arg == "小盏" || arg == "teacup" ) {
                if (j > 0) {
            write("茶盏里盛满了铁观音，还冒着清香的热气。你可以喝（ｄｒｉｎｋ）。\n");
                } else {
            write("茶盏已空了，不过茶香犹在空气中荡漾。\n");
                }
        me->set_temp("know_tea", 1);
        }
        return 1;
}        
int do_eat(string arg) {
        object me;
        int i;
        
        me = this_player();
    i = query("gao_amount");
        
    if( !arg || arg != "taosu gao" && arg != "梅花糕" && arg != "gao" ) return 0;
        if( me->is_fighting()) return notify_fail("你现在不能吃。\n");
    if( i > 0 && me->query_temp("know_gao")) {
                if (me->query("food") >= me->max_food_capacity() ) {
                        write("你已经吃饱了，实在吃不下了。\n");
            message("vision", me->name() + "面有难色的看着面前剩下的糕点。\n",
                                        environment(me), me);
                        return 1;
                } else {
                        if(me->is_busy()) return notify_fail("你现在忙，不能吃。\n");
            message_vision("$N拿起一个梅花糕，慢慢的品尝着。\n", me);
                        me->start_busy(2);
           }
        //add("gao_amount", -1);
        me->add("food", 100);
    } else if( i =0 && me->query_temp("know_gao")) {
        write("已经没有糕点了！\n");
        } else { 
                return 0;
        }
        return 1;
} 
int do_drink(string arg)
{
        object me;
        int i;
        
        me=this_player();
    i = query("tea_amount");
        
    if(!arg || arg != "tea" && arg != "铁观音") return 0;
        if(me->query("water") >= me->max_water_capacity())
                        return notify_fail("你似乎并不渴。\n");
        if(me->is_fighting()) return notify_fail("你现在不能喝。\n");
        if(me->is_busy()) return notify_fail("你现在忙，不能喝。\n");
    if (i > 0 && me->query_temp("know_tea")) {
        message_vision("$N轻轻捧起茶盏，耐心地品茗起来。\n",me);
                me->start_busy(2);
       // add("tea_amount", -1);
        me->add("water",100);
    } else if( i = 0 && me->query_temp("know_tea")) {
        write("茶盏已经空了。\n");
        message("vision", me->name() + "端起茶盏看了看。\n", environment(me), me);
        } else {
                return 0;
        }
        return 1;
}
