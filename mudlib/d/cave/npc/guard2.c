#include <ansi.h>
inherit NPC; 
void create()
{
        set_name("ˮ������", ({ "prison guard", "guard" }) );
        set("long", "�������������д��ε�ˮ�����䡣\n");
        set("title","������ ����");
        set("attitude", "heroism");
        set("class","wudang");
        set("str", 50);
        set("cor", 26);
        set("cps", 25); 
        set("combat_exp", 1000000); 
        set("chat_chance", 2); 
        set("chat_msg", ({
        "ˮ������̾�˿����������ˮһ������ͷ��Ҫ�ð˷֣���С��һ�����У��������ӣ�\n",
        }) ); 
        set_skill("unarmed", 150);
        set_skill("sword", 150);
        set_skill("parry", 120);
        set_skill("dodge", 120);
        set_skill("move", 100);
        set_skill("dragonstrike",120);
        set_skill("taiji-sword",120);
        set_skill("five-steps",100);
        
        map_skill("sword","taiji-sword");
        map_skill("parry","taiji-sword");
        map_skill("unarmed","dragonstrike");
        map_skill("dodge","five-steps");
  
        switch (random(5)) {
                case 0: set("resistance/sen",30);
                        break;
                case 1: set("resistance/gin",30);
                        break;
                default: set("resistance/kee",30);
                }
        setup(); 
        carry_object("/obj/armor/cloth")->wear();
        carry_object("/obj/weapon/sword")->wield();
} 
void init()
{
    object ob; 
    ::init();
    if( interactive(ob = this_player()) && !is_fighting() ) 
    {
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
    }
} 
void greeting(object ob)
{   
        string where, location;
        if( !interactive(ob) || environment(ob) != environment() )
                return;
        if (!ob->query("vendetta/authority") ){
            message_vision("$N�ٺٵ�����������˽��������ĵ�ͷ���������ɣ�\n", this_object() );
                this_object()->kill_ob(ob);
                ob->kill_ob(this_object());
        }
        return;
}  