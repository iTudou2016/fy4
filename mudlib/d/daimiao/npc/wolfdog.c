 inherit NPC;
void create()
{
        set_name("��Ȯ", ({ "wolfdog" }) );
        set("race", "Ұ��");
        set("gender", "����");
        set("age", 20);
        set("long", "����һֻ��������������ޱȵ���Ȯ��Ƥ����������ޱȣ�
���������Ϊ��ɽ���������Ŭ��֮һ��\n");
        
        set("str", 50);
        set("cor", 52);
        set("cps", 22); 
        set("max_kee", 5000);
        set("max_gin", 5000);
        set("max_sen", 5000);
        
        set("attitude", "friendly");
        set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
        set("verbs", ({ "bite", "claw" }) ); 
        set("chat_chance_combat", 1);
        set("chat_msg_combat", ({
                "��Ȯ������̹�ʹ�㲻��������\n"
        }) );
        set("combat_exp", 2200000);
                
        set_temp("apply/attack", 250);
        set_temp("apply/dodge",200);
        set_temp("apply/move",320);
        set_temp("apply/damage",30);
        
        setup();
}       