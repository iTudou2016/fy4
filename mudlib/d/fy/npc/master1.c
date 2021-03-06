 // taolord.c
inherit NPC;
#include <ansi.h>
inherit F_MASTER;
int leave(); 
void create()
{
    set_name("雷一鸣", ({ "master lei", "master", "lei" }) );
    set("nickname", HIY"独鹤"NOR);
    set("gender", "男性");
    set("age", 44);
    set("long",
        "当年开山立柜大盗严独鹤身边有雷、电两大当家，之后跟严独鹤一起遁入空门。\n"
        "今日峨嵋精英尽出为掌门报仇，连【刀】、【剑】两名长老亦破戒出山。\n");
    set("combat_exp", 5000000);
    set("score", random (20000)); 
    set("class", "emei");
    set("reward_npc", 1);
    set("difficulty", 30); 
    set("int", 30);
    set("cor", 20);
    set("cps", 30);
    set("spi", 30);
    set("fly_target",1);        
    set("force", 3000);
    set("max_force", 3000);
    set("force_factor", 100);
    set("atman", 1400);
    set("max_atman", 1400);
    set("mana", 2000);
    set("max_mana", 2000); 
    set("resistance/gin",70);
    set("resistance/kee",70);
    set("resistance/sen",99);
        
    set("inquiry",  ([
                "leave": (: leave :),
                ]) );
    set("apprentice_available", 10);

    create_family("峨嵋派", 5, "刀宗长老");
    set("rank_nogen",1);
    set("ranks",({"弟子","少侠","居士","真人","护法",YEL"长老"NOR,YEL"副掌门"NOR,
                      HIY"掌门"NOR})); 
    set_skill("literate", 120);
    set_skill("force", 120);
    set_skill("move", 120);
    set_skill("unarmed", 120);
    set_skill("blade", 120);
    set_skill("parry", 120);
    set_skill("dodge", 120);
    set_skill("changelaw", 120);
    set_skill("shenji-blade", 160);
    set_skill("skyforce", 100);
    set_skill("yue-strike", 100);
    set_skill("shenji-steps", 120);
    set_skill("perception", 180);
    set_skill("throwing", 200);
    set_skill("tanzhi-shentong", 180);

    map_skill("parry", "shenji-blade");
    map_skill("blade", "shenji-blade");
    map_skill("move", "shenji-steps");
    map_skill("dodge", "shenji-steps");
    map_skill("literate", "changelaw");
    map_skill("force", "skyforce");
    map_skill("unarmed", "yue-strike"); 
    map_skill("throwing", "tanzhi-shentong"); 
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
                (: perform_action, "dodge.shenjimiaosuan" :),
                (: perform_action, "blade.jichulianhuan" :),
    }) ); 
    setup(); 
    add_money("gold", 10);
    carry_object("/obj/weapon/blade")->wield();
    carry_object("/obj/armor/cloth")->wear();
} 
void attempt_apprentice(object ob)
{
    if(ob->query("marry")){
                message_vision("$N哼了一声：峨嵋虽然不限入世还是出家，但也没有拖儿带女的。”\n", 
                                this_object(), ob);
                return;
    }
    if (ob->query("once_menpai/emei")&& ob->query("class")!="emei") {
                command("say 你不是叛出去了么,还有脸回来见我们？");
                return;
                } 
    if( query("apprentice_available") ) {
        if( find_call_out("do_recruit") != -1 )
            command("say 慢著，一个一个来。");
        else
            call_out("do_recruit", 2, ob);
    } else {
        command("say 老夫今天已经收了三个弟子，不想再收徒了。");
    }
} 
void do_recruit(object ob)
{
//    if( (string)ob->query("marks/峨嵋叛徒") )    //wrong
    if( ob->query("once_menpai/emei") )
        command("say " + ob->query("name") + "！你还有脸回来见我们？");
    else {
        command("recruit " + ob->query("id") );
        ob->set("once_menpai/emei",1);
    }
} 
int recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "emei");
    add("apprentice_availavble", -1);
} 
void die()
{
    object ob;
    if( !ob = query_temp("last_damage_from") )
        ob = this_player(1);
    if(ob) 
        ob->set_temp("killed_master_shi",1);
    ::die();
} 
void init()
{
        object ob; 
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
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
        if(id_class == "emei"&& userp(victim)&&player!=victim)
        {
message_vision(HIW"$N对著$n喝道：" + RANK_D->query_rude(player) 
                                                + "竟敢杀" + RANK_D->query_self_rude(this_object()) 
                                                + "的徒弟，去死吧。\n"NOR, this_object(), player);
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            if (!player->is_busy()) player->start_busy(2);
            return 0;
        } 
    }
    return 0;
}  
int leave() {
        if (this_player()->query("class")!="emei") return 0;
        message_vision(CYN"$N无奈长叹：门下一个一个离弃，我派复仇难望！\n"NOR, this_object(),this_player());
        message_vision(CYN"$N苦笑说：走吧，峨嵋百年修为，靠你自己好好琢磨了。\n"NOR,this_object(),this_player());
        message_vision(CYN"$N说：一场缘分，若看见我派弟子就传个口信吧！\n"NOR,this_object(),this_player());
        return 1;
}
