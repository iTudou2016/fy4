 // a skeleton for user rooms
#define X_COOR 15
#define Y_COOR 2055
#define Z_COOR 45
#define R_FLAG 17
#define OWNER "ximen"
#define CLASS "黄山派"
inherit ROOM;
void create()
{
	//object con, item, item2;
set("short", "长廊");
set("long", @long
踏上级级如痕浓绿的石阶，走上长廊。庭园是非常陈旧的，应该到处
都可以看得见蛛网积尘虫鼠，可是这间屋子，却被洗得像是条刚被一个勤
快的妇人从胰子水里提出来的床单那麽乾净。甚至连铺地的槐木板，都已
经被洗得发白。
long

);
        set("exits", ([
"southdown" : __DIR__"yxiao3",
"north" : __DIR__"yxiao5",

]));
/*set("objects", ([
"/p/residence/obj/wall" : 1,
//"/p/residence/obj/sword1" : 1,
//"/p/residence/obj/sword2" : 1,
       ]) );

               set("item_desc", ([
                "paper": "一张黄黄的纸条上以狂草写着：\n水月爱妻：吾往杀敌，不日即返。　愚夫　标枪　留字\n",
                "纸条": "一张黄黄的纸条上以狂草写着：\n水月爱妻：吾往杀敌，不日即返。　愚夫　标枪　留字\n",
        ]) );*/
        set("coor/x",X_COOR);
   set("coor/y",Y_COOR);
        set("coor/z",Z_COOR);
        set("room_flag",R_FLAG);
        set("owner", OWNER);
        set("class", CLASS);
        set("outdoors","residence");
        setup();
      /*  con = present("wall", this_object());
        inv = all_inventory(con);
        if( sizeof(inv) != 1) {
                for(i=sizeof(inv)-1; i>=0; i--) destruct(inv[i]);
                item = new(__DIR__"obj/sword1");
                item2 = new(__DIR__"obj/sword2");
                item->move(con);
                item2->move(con);*/
}
void init()
{
        int flag;
        flag = (int) query("room_flag");
        if(flag & 1) set("valid_startroom",1);
        if(flag & 2) set("NONPC",1);
        if(flag & 4) set("no_fight",1);
        if(flag & 8) set("no_magic",1);
        if(flag & 16) set("outdoors","residence");
        add_action("do_invite","invite");
        add_action("do_setowner","setowner");
        add_action("do_list","list");
                //add_action("do_sleep", "sleep");
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
    