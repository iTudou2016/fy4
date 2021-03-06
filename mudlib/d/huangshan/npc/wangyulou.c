 inherit NPC;
#include <ansi.h>
int kill_him();
int fanghe();
int peiyu();
void smart_fight();
void smart_attack(); 
void create()
{
        object armor;
        set_name("王雨楼", ({ "wang yulou" }) );
        set("gender", "男性");
        set("age", 55);
        set("long",
"侠名遍江湖，仁义传四海，一个浓眉长髯，面如重枣的紫袍老人。\n"
);
        set("inquiry", ([
            "俞独鹤" : (: kill_him :),
             "俞放鹤" : (: fanghe :),
              "俞佩玉" : (: peiyu :),
   ]));
                        
        set("chat_chance", 1);
        set("chat_msg", ({
                "王雨楼笑道：“先天无极门的威名，岂是你这小辈可以想象的！”\n",
                "王雨楼道：好地方呀好地方！\n",
        }) );
          
        set("attitude", "friendly");
        set("title","江南大侠");
        set("nickname", HIG"义薄云天"NOR);
        set("score", 0);
        set("reward_npc", 1);
        set("difficulty",5);
        set("class","beggar");
        
        set("combat_exp", 4500000);        
        set("int", 30);
        set("cps", 20);
        set("spi", 30);
        set("fle",50);
        set("str",36);
        
        set("force", 1500);
        set("max_force",1500);
        set("force_factor", 100);
        set("atman", 100);
        set("max_atman", 100);
        set("mana", 500);
        set("max_mana", 500);
 
        switch (random(3)) {
                case 0: set("resistance/kee",30);
                        break;
                case 1: set("resistance/gin",30);
                        break;
                default: set("resistance/sen",30);
                }
        
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
               (: smart_fight() :),
        }) );           
          
        set_skill("move", 200);
        set_skill("force", 200);
        set_skill("spells", 150);
        set_skill("unarmed", 200);
        set_skill("sword", 200);
        set_skill("parry", 150);
        set_skill("dodge", 150);
        set_skill("magic",150);
        set_skill("qixing",100);        
        set_skill("qidaoforce", 150);
        set_skill("fall-steps",200);
        set_skill("dragonstrike",180);
        
        map_skill("spells","qixing");        
        map_skill("unarmed","dragonstrike");
        map_skill("force", "qidaoforce");
        map_skill("dodge","fall-steps");
        map_skill("move","fall-steps");
        
        
        set_temp("apply/dodge", 30);
        set_temp("apply/armor", 30);
        setup(); 
        add_money("gold", random(3));
        armor=new("/obj/armor/cloth");
        armor->set_name(HIY"烟雨潇潇环金袍"NOR,({"cloth"}) );
        armor->move(this_object());
        armor->wear();
} 
 
int kill_him()
{
        object me;
        me = this_player();
        command("say 看来你知道得真不少！！ \n");
        this_object()->kill_ob(me);
        me->kill_ob(this_object());
        return 1;
} 
int fanghe()
{
    command( "say 放鹤兄是我先天无极门的掌门人。");     
    return 1;
}  
int peiyu()
{
    command ("say 这小子是我义兄不成材的儿子。");
    return 1;
} 
smart_fight()
{
        int i;
        object *enemy, who;
        who = this_object();
        enemy = this_object()->query_enemy();
        i = sizeof(enemy);
   if (i>2 && enemy[1]->is_zombie()) {
                who->cast_spell("zombie-bolt");
                return;
        }
        who->smart_attack();
        return;
} 
smart_attack() {
        this_object()->perform_action("unarmed.xianglongwuhui");        
        return;
        }    
