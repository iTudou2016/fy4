// hu.c
inherit NPC;
#include <ansi.h>
int wieldblade();
 
void create()
{
        set_name("�����", ({ "gu qingfeng", "qingfeng" }) );
        set("gender", "����" );
        set("age", 52);
        set("str", 30);
        set("str", 111);
        set("cor", 40);
        set("cps", 1);
        set("no_busy", 10);
                 set("reward_npc", 1);
        set("difficulty", 35);

        set("class","huashan");
            set("resistance/kee",99);
    set("resistance/sen",99);
    set("resistance/gin",99);

    set("long",
"����۵��˿��۴��䣬�����Ѱ߰��������ǵ����ϣ������ֺ�����ı��飬�Ų�
��Ȼ���ὡ������ȴ�������书�����ӡ� \n"
    );
        set("force_factor", 100);
        set("combat_exp", 7000000+random(3000000));
        set("attitude", "friendly");
        set_skill("move",100);
        set_skill("force",100);
        set_skill("unarmed",10);
        set_skill("dodge",999);
        set_skill("throwing",999);
        set_skill("tanzhi-shentong",999);
        
        
        //set_skill("tangforce",100);
        //set_skill("blade",180);
        //set_skill("tang-blade",180);        
        set_skill("perception", 220);
        //set("skill_public",1);
        map_skill("throwing", "tanzhi-shentong");
        //map_skill("force", "tangforce");
        set("chat_chance", 1);
        set("chat_msg", ({
                "�������૵����������޳�������ƲԹ�������˭���뵽����һ�ֲ������ڣ�������ȴ�Ѿ������ˡ���\n",
                "��������Ȼ��Ц������һ�Ӱ��£�����Ͳ����ˡ���\n",  
                "�����˺�Ȼ�����������ֲ��壬���ƿ�̾����������ǣ�Ҳ����һ���壮��Ӯ�ֺα�̫�����أ���\n",
        }));
        //set("skill_public", 1);
        set("chat_chance_combat", 99);
        set("chat_msg_combat", ({
                (: wieldblade  :),
        }) );
        setup();
        carry_object("/d/wudang/npc/obj/cloth")->wear();
        carry_object("/d/resort/npc/obj/bqi");
        
} 

int wieldblade()
{
command("wield piece");
perform_action("throwing.tanzhijinghun");
command("unwield piece");
return 1;
}