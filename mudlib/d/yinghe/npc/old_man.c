 inherit NPC;
#include <ansi.h>
void smart_fight(); 
void create()
{
        set_name("无名老人", ({ "wu ming", "old man"}) );
        set("gender", "男性" ); 
        set("age", 100);
                
        set("long",
                "充满风霜的脸庞让人无法看出具体的年龄，身穿一件蓝布衫。充满智慧的
双眸似乎一眼就可以吧你看穿。\n"
                );
        set("class","yinghe");
        set("combat_exp", 5500000);
        set("score", 900);
        
        set("fle",50);
        set("cor",40);
        set("cps",30);
        set("str",40);
        set("per",40);
        
        set("force",1500);
        set("max_force",1500);
        set("force_factor",100);
        set("atman",1500);
        set("max_atman",1500);
        set("mana",1500);
        set("max_mana",1500);
                
        set("no_busy",6);
        
    set("resistance/kee",30);
    set("resistance/gin",30+random(40));
    set("resistance/sen",30);
        
    
    set_skill("perception",200);
        set_skill("iron-cloth", 200);
   set_skill("unarmed", 200);
        set_skill("dragonstrike", 200);
        set_skill("force", 200);
        set_skill("lingxi-zhi", 150);
        set_skill("spells",200);
        set_skill("parry",200);
        set_skill("kwan-yin-spells",200);
        set_skill("jin-gang",150);
        set_skill("move",400);
                
        map_skill("iron-cloth","jin-gang");
        map_skill("spells","kwan-yin-spells");
        map_skill("unarmed", "lingxi-zhi");
        map_skill("force", "bolomiduo");
        
    add_temp("apply/iron-cloth", 200);
         
        setup();
    carry_object(__DIR__"obj/b_cloth")->wear();
        
}    
