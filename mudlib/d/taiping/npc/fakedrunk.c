#include <ansi.h>
#include <command.h> 
inherit "/d/taiping/npc/smart_npc";
void do_drink(); 
void create()
{ 
        set_name("醉汉",({"drunk"}));
        set("age",37);
        set("combat_exp", 5000000);
                
        set("max_atman", 1000);
        set("atman", 1000);
        set("max_mana", 1000);
        set("mana", 1000);
        set("max_force",1500);
        set("force",1500);
        set("force_factor",100);
        
        set("pursuer", 1);
        set("parrot_killer",1);
        set("cor", 40);
        set("cps", 40);
        set("agi",40);
        set("fle",40);
        
        set("resistance/gin",30);
        set("resistance/kee",30);
        set("resistance/sen",30);
        
//      setting up special NPC function: healer, defense, zombie-killer
//      defense_type: 1. xiaohun-sword; 2.xiaohun-whip;3 yue-strike;4 lingxi-zhi;
        
//      set("defense_type",random(2)+1);        
//      set("zombie-killer",1);
//      set("officer-killer",1);
//      set("dungeon_npc","check");
        
        set("death_msg",CYN"\n$N说：完了，攒的银子再多有什么用。。 \n"NOR);
        set("chat_chance",1);
        set("chat_msg", ({
           (: do_drink :), }) 
        );
        set("nb_chat_chance", 100);
        set("nb_chat_msg_combat", ([
                10:     "\n杀手说：我们什么事都不管，只管杀人！！！\n",
        ]) ); 
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: auto_smart_fight(50) :),    
        }) );
        
        CHAR_D->setup_char(this_object());
        auto_npc_setup("wang",200,160,0,"/obj/weapon/","fighter_w","sharen-sword",1);
        set_skill("move",1000);
        setup();
        carry_object("/obj/armor/cloth")->wear();
        carry_object(AREA_FY"npc/obj/killersword")->wield();
}  
void init(){
        ::init();
        add_action("do_look", "look");
}  
int do_look(string arg) {
        if(arg == "drunk"){
                write("一个摇头晃脑的汉子，显然是喝多了。\n");
                write("他看起来约三十多岁。\n");
                write("他英俊潇洒，貌似潘安。\n");
                write("他长的不胖不瘦，武功看起来好象"+HIB"略有小成"NOR+"，出手似乎很轻。\n");
                write("他看来"+HIG"身上并无丝毫伤痕。\n"NOR);
                write("他身穿布衣(Cloth)\n");
                return 1;
        }
        return 0;
} 
 
void do_drink()
{
    object *list, ob;
    int i, can_drink;
    if ((int)this_object()->query("water") >= 380) return;
    list = all_inventory(this_object());
    i = sizeof(list);
    can_drink = 0;
    while (i--) {
        if ((string)list[i]->query("liquid/type") == "alcohol") {
            ob = list[i];
            can_drink = 1;
        }
    }
    if (can_drink) {
        command("drink "+(string)ob->query("id"));
        if ((int)ob->query("liquid/remaining") == 0)
            command("drop wineskin");
    }
    else {
        command("sigh");
        command("say 酒..... 给我酒....");
    }
    return;
}
 
int accept_object(object who, object ob)
{
    if ((string)ob->query("liquid/type")=="alcohol") {
        if ((int)ob->query("liquid/remaining") == 0) {
            command("shake");
            command("say 空的我不要...");
            return 0;
        }
        else {
            command("smile");
            command("say 多谢!");
            return 1;
        }
    }
    else return 0;
}
 
void die() {
        
   object me, ob, owner;
        ob=this_object();
        
        if(objectp(me=query_temp("last_damage_from") ))     
        if(owner=me->query("possessed")) {
                me = owner;
        } 
        
        if (me)
        if(me->query("parrot/安子豪背景")) {
                me->set("parrot/遇刺",1);
        }
        ::die();
}  
