 // master.c
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name("叶孤城", ({ "master ye", "master" }) );
        set("nickname", HIC"一剑东来"NOR+HIR" 天外飞仙"NOR);
        set("gender", "男性" );
        set("age", 44);
        set("str", 50);
        set("cor", 30);
        set("cps", 30);
        set("int", 30);
       set("per", 40);
        set("agi",25);
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: perform_action, "sword.tianwaifeixian" :),
                (: perform_action, "dodge.tianwaifeixian" :),
        }) );
        set("attitude","friendly");
        set("max_force", 8000);
        set("force", 8000);
        set("force_factor", 30);
    set("max_kee",8000);
        set("max_gin",8000);
        set("max_sen",8000);
        set("chat_chance", 1);
        set("chat_msg", ({
                "叶孤城凝望海天之处，轻捋长髯微微一笑道：紫禁之颠，一剑东来。\n",
        }) ); 
        set("long",
"他自己的脸枯瘦丑陋，一双眼睛深深的下陷，虽然也目光似电，但着实有几分
阴狠辛辣之意。\n"
        );
        create_family("白云城",1, "城主");
        set("rank_nogen",1);
        set("ranks",({"剑童","小剑士","剑士","小剑客","剑客",
                      "小剑侠","剑侠","剑师",CYN"大剑师"NOR,
                      CYN"剑仙"NOR,CYN"剑神"NOR,HIC"剑圣"NOR}));
        set("rank_levels",({ 32000,64000,128000,256000,512000,
                             1024000,1536000,2304000,3456000,
                             5187000,26244000 }));
        set("combat_exp", 2000000);
        set("score", 200000);
        set("reward_npc", 1);
        set("difficulty", 10);
        set_skill("move", 150);
        set_skill("daode",150);
        set_skill("parry", 120);
        set_skill("dodge", 150);
        set_skill("force", 160);
        set_skill("literate", 130);
        set_skill("sword", 140);
        set_skill("unarmed",120);
        set_skill("changquan",120);
        set_skill("feixian-steps",140);
        set_skill("feixian-sword",140);
        set_skill("jingyiforce",60);
        map_skill("dodge", "feixian-steps");
        map_skill("sword", "feixian-sword");
        map_skill("force", "jingyiforce");
        map_skill("parry", "feixian-sword");
        map_skill("unarmed", "changquan");  
        setup();
        carry_object(__DIR__"obj/whitecloth")->wear();
        carry_object(__DIR__"obj/bsword")->wield();
        carry_object(__DIR__"obj/bcloth")->wear(); 
} 
void attempt_apprentice(object me)
{
      command("say 嗯，白云城正是用人之时，你可要努力啊！");
      command("recruit " + me->query("id") ); 
} 
void recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "baiyun");
} 
void init()
{       
        ::init();
        add_action("do_killing", "kill");
    
} 
int do_killing(string arg)
{
    object player, victim;
    string id,id_class;
    player = this_player();
    if(!arg || arg == "") return 0;
    victim = present(arg, environment(player));
    if(!objectp(victim))
                return notify_fail("这里没有这个人。\n");
    if(living(victim))
    {
        id_class=victim->query("class");
        id=victim->query("id");
        if(id_class == "baiyun"&& userp(victim)&& player!=victim)
        {
            message_vision(HIW
"$N冷冷道：接天楼岂能容你放肆！\n"NOR, this_object());
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            if (!player->is_busy()) player->start_busy(2);
            return 0;
        } 
    }
    return 0;
}  
int leave() {
        if (this_player()->query("class")!="assassin") return 0;
        message_vision(WHT"$N袍袖一拂冷冷道：白云弟子向来忠心不二，若你有了异心，还是趁早走吧！\n"NOR, this_object());
        message_vision(CYN"$N嘿然道：白云岛的琴棋书画岂是逆徒之辈所能领悟？\n"NOR,this_object());
        return 1;
}  
