#include <ansi.h>
inherit QUESTNPC;
//inherit F_MASTER;
//inherit SSERVER; 
void create()
{
        set_name("����", ({ "yue gang", "yue" }) );
        set("gender", "����" );
//        set("vendetta_mark", "authority");
        set("class","quest_npc");
        set("npc_difficulty",4);
        set("organization/����","��");
        set("age", 35);
        set("int", 41);
        set("per", 17);
        set("str", 100);
        set("dur", 50);
        set("cor", 30);
    	set("title", "��͢���� ��Զ�󽫾�");
        set("long",
"�����ǳ�͢��Ʒ��Ա��һ�ּҴ���ƽǹ�������뻯��\n"
                );
        set("force_factor", 80);
        set("max_gin", 30000);
        set("max_kee", 480000);
        set("max_sen", 22000);
        set("max_force",5000);
        set("force",5000); 
        set("combat_exp", 40000000);
        set("score", 20000);
        set_skill("unarmed", 220);
        set_skill("spear", 300);
        set_skill("force", 200);
        set_skill("parry", 200);
        set_skill("literate", 80);
        set_skill("dodge", 250); 
        set_skill("yue-strike", 250);
        set_skill("yue-spear", 250);
        set_skill("manjianghong", 200);
        
        map_skill("unarmed", "yue-strike");
        map_skill("spear","yue-spear");
        map_skill("force", "manjianghong");
        map_skill("parry", "yue-spear");
        
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action,"spear.qingheluo":),
        }) );
        setup();
        carry_object(__DIR__"obj/suozijia")->wear();
        carry_object(__DIR__"obj/feiyunspear")->wield();
}
int accept_fight(object me)
{
	command("smile");
        command("say ��������æ�����в��㡣");
        return 0;
}
/*
object offensive_target(object me)
{
        int sz;
        object *enemy; 
        enemy = me->query_enemy();
        if( !enemy || !arrayp(enemy) ) return 0; 
        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4; 
        if( sz > 0 ) return enemy[random(sz)];
        else return 0;
}  
*/     