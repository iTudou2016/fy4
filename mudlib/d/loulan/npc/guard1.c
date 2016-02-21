#include <ansi.h>
inherit NPC; 
void create()
{
        set_name("������", ({ "fang xinqi","fang" }) );
        set("gender", "����" );
        create_family("�����", 1, "�����һ��");
        set("long",
"��������������ļ�����ʮ�����ս���꣬������һ�а١�������֯����װ��\n��ǰ����һ����ͭ���ľ���Ψ�о��Ͽ̵��ֲ�ͬ�����Ͽ��š�һ���֡� \n"  
                );
        set("attitude", "peaceful");
        set("chat_chance_combat",20);
        set("chat_msg_combat",({
                (:perform_action,"blade.shiwanshenmo":),
                (:perform_action,"dodge.huanyingqianchong":),
              }));
        set("age", 25);
//        set("str", 20);
        set("cps", 40);
        set("int", 50);
        set("per", 40);
        set("cor", 40);
        set("agi", 30);
        set("combat_exp", 700000);
        set("force", 800);
        set("max_force", 800);
/*        set("max_kee", 800);
        set("max_gin", 800);
        set("max_sen", 800); */
        set("force_factor", 30); 
        set("chat_chance", 1);
        set("chat_msg", ({
                "��������Ȼ�������ձ�����ү�ļ��գ�ʵ�ڵ�С�Ĳ��ǡ�\n",
                }) ); 
        set_skill("unarmed", 80);
        set_skill("blade", 100);
        set_skill("bat-blade", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("move", 100);
        set_skill("meng-steps", 100);
        set_skill("changquan", 100);
        map_skill("dodge", "meng-steps");
        map_skill("blade", "bat-blade");
        map_skill("parry", "bat-blade");
                
        setup();
        carry_object(__DIR__"obj/jinzhuang")->wear();
        carry_object(__DIR__"obj/doupeng")->wear();
        carry_object(__DIR__"obj/huxinjing")->wear();
        carry_object("/obj/weapon/blade")->wield();
} 
void init()
{       
        object me;
        ::init();
        me = this_player();
        if( interactive(me) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 0, me);
        }
} 
void greeting(object me)
{
        object *inv;
        int i;
        object ob;
        ob = this_object();
        if( userp(me) )
        {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("owner")=="������" && (int)inv[i]->query("equipped"))
                        {
                                message_vision(HIY"$N��ȵ���������˴󵨣�����ð�䱾�\n"NOR,ob);
                                ob->kill_ob(me);
                                me->kill_ob(ob);
                        }
           }
        }
}     