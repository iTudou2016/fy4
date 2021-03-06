 inherit NPC;
void smart_fight();
void smart_attack();  
void create()
{
       set_name("云松", ({ "yun song", "song" }) );
       set("nickname", "红衣喇嘛");
        set("gender", "男性" );
        set("age", 32);
        set("int", 30);
        set("class","lama");
        create_family("大昭寺", 21, "弟子");
        set("long",
        "云松乃是葛伦高僧的关门小弟子，修行甚勤。葛伦以之为门下\n"
        "众弟子榜样。\n"
                );
        set("chat_chance", 1);
        set("reward_npc", 1);
        set("difficulty", 2);
        set("chat_msg", ({
                "云松叹了口气道：赤松大师兄，不知道现在怎么样了。。\n",
        }) ); 
        set("inquiry", ([
                "舍利子": "嗯....舍利子一定是我师妹胭松盗走的。\n",
                "胭松": "胭松在布达拉宫城的大招寺里。",
        ]) );
        set("attitude", "peaceful");
        set("mana",4000);
        set("max_mana",4000);
        
        set_skill("iron-cloth", 100);
        set_skill("staff", 100);
        set_skill("lamastaff", 100);
        set_skill("unarmed", 100);
        set_skill("lamaism", 10);
        set_skill("bloodystrike", 50);
        set_skill("force", 100);
        set_skill("bolomiduo", 100);
        set_skill("spells",100);
        set_skill("parry",100);
        set_skill("kwan-yin-spells",100);
   set_skill("perception", 100);
        
        map_skill("spells","kwan-yin-spells");
        map_skill("parry","lamastaff");
        map_skill("unarmed", "bloodystrike");
        map_skill("force", "bolomiduo");
        map_skill("staff", "lamastaff");
        
        set("combat_exp", 1500000);
        
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
               (: smart_fight() :),
        }) );
        setup();
        carry_object(__DIR__"obj/redclothh")->wear();
        carry_object(__DIR__"obj/7staff")->wield();
}   
smart_fight()
{
        int i;
        object *enemy, who;
        who = this_object();
        if (who->is_busy()) return;
        enemy = this_object()->query_enemy();
        i = sizeof(enemy);
        if (i>2) {
                who->cast_spell("ni");
                return;
        }
        while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        if (enemy[i]->query_skill("iron-cloth")>300 
                                || enemy[i]->query("combat_exp")>who->query("combat_exp")) {
                                who->cast_spell("an");
                                switch( random(3) ) {
                                        case 0: command("grin");
                                                break;
                                        case 1: command("smile");
                                                break;
                                   case 2: command("smug");
                                                break;
                                        }
                                return;
                        }               
                        this_object()->smart_attack();
                        }
        }
return;
}  
smart_attack() {
        this_object()->perform_action("staff.fofazhizun");    
        return;
        }
