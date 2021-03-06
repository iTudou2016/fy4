#include <ansi.h>
inherit QUESTNPC;
inherit F_MASTER;
//inherit SSERVER; 
void auto_fight();
void create()
{
        set_name("杜桐轩", ({ "du tongxuan", "du" }) );
        set("gender", "男性" );
        set("nickname",BLU"翰林学士"NOR); 
        set("organization/性质","正");
        set("npc_difficulty",8);
        set("age", 47);
        set("int", 25);
        set("per", 20);
        set("str", 100);
        set("class","official");
        set("dur", 35);
        set("cor", 35);
        set("fle",20);
        set("long",
"这人很高，很瘦，穿著极考究，态度极斯文，年纪虽不甚
大，两翼却已斑白，一张清瘤瘦削的脸上，仿佛带著三分
病容，却又带著七分威严，令人绝不敢对他有丝毫轻视。\n");
        set("force_factor", 150);
        set("max_gin", 50000);
        set("max_kee", 250000);
        set("max_sen", 50000);
                set("max_force",8000);
                set("force",8000); 
        set("combat_exp", 75000000);
        set("score", 12000);
        set_skill("unarmed", 200);
        set_skill("force", 250);
        set_skill("parry", 300);
        set_skill("literate", 160);
        set_skill("dodge", 300);
        set_skill("fengyu-piaoxiang",400);
        set_skill("move",500);
        set_skill("iron-cloth",200);
        set_skill("henglian",200); 
        set_skill("manjianghong",200);
        set_skill("changquan", 350);
                
        map_skill("unarmed", "changquan");
        map_skill("force","manjianghong");
        map_skill("iron-cloth","henglian");
        map_skill("dodge","fengyu-piaoxiang");
        map_skill("move","fengyu-piaoxiang");
        map_skill("parry","changquan");
     
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
        	(: perform_action,"dodge.zonghengsihai":),
                (: perform_action,"unarmed.yuhuan":),
        }) );
        setup();
        carry_object(__DIR__"obj/bluecloth")->wear();
        carry_object(__DIR__"obj/baiyubi");
        carry_object(__DIR__"obj/yubanzhi")->wear();
//      add_money("gold",15);
//        carry_object(__DIR__"obj/feiyunspear")->wield();
}
int accept_fight(object me)
{
	command("smile");
        command("say 在下公务繁忙，多有不便。");
        return 0;
}
void auto_fight() {
	object obj,me;
	obj = this_object();
	me = this_player();
	
        if(!me || !obj || !userp(me) || me->is_fighting(obj) || me->query_temp("is_unconcious")
                        ||!living(me) || environment(me)!=environment(obj)
                        || environment(me)->query("no_fight")
                        || obj->query_temp("is_unconcious")) {
                return;
        } 
	if(obj->query("organization/性质") == "正"){            //如果npc为正派人物
        	if( me->query("organization/性质") == "正"){
        		if(me->query("justice")>= 1000 )
        			message_vision("$N对$n抱拳道：好兄弟，组织振兴就靠你了！\n",obj,me);
        		else
        			message_vision("$N微笑地对$n道：兄弟今天精神不错啊。\n",obj,me);
        		if(me->query("improbity") < 1000&&me->query("improbity") > 500){
        			message_vision("$N对$n喝道：既然入我正派，岂能为虎作伥，我得教训教训你！\n",obj,me);
        			obj->fight_ob(me);
        			me->fight_ob(obj);
        		}else if(me->query("improbity") >=1000){
        			message_vision("$N对$n厉声道：你心术不正，害死诸多同道，看我清理门户！！\n",obj,me);
        			obj->kill_ob(me);
        		}
        	}else{
        		if (me->query("organization/性质") == "邪")
        		{
        			if(me->query("improbity") <1000)
        				message_vision("$N对$n道：看你也算是个人物，为何加入邪教，为虎作伥？可惜可惜！\n",obj,me);
        			else{
        				message_vision("$N对$n喝道：邪教人物，害死我诸多同道，坏事做尽，今天我要为武林除害！\n",obj,me);
        				obj->kill_ob(me);
        			}
        		}
        		else
        		{
        			if(me->query("improbity") <1000)
        				message_vision("$N望了$n几眼，叹气道：可惜可惜！好人不做，为何偏偏学坏？\n",obj,me);
        			else{
        				message_vision("$N对$n喝道：趁你还没有加入邪教，我先把你除了！！免得日后成为武林祸害！！\n",obj,me);
        				obj->kill_ob(me);
        			}
        		}
        	}
        }
	if(obj->query("organization/性质") == "邪"){
		if( me->query("organization/性质") == "邪"){
        		if(me->query("improbity")>= 1000 )
        			message_vision("$N讨好得对$n说到：以后还望大哥多多提拔。\n",obj,me);
        		else
        			message_vision("$N奸笑了两声，对$n道：兄弟今天又做了多少“买卖”？\n",obj,me);
        		if(me->query("justice") < 1000&&me->query("justice") > 500){
        			message_vision("$N对$n冷笑道：看不出来你还是好人一个，我得领教几招！\n",obj,me);
        			obj->fight_ob(me);
        			me->fight_ob(obj);
        		}else if(me->query("justice") >=1000){
        			message_vision("$N对$n冷笑道：你活不过今天了！！\n",obj,me);
        			obj->kill_ob(me);
        		}
        	}else{
        		if (me->query("organization/性质") == "正")
        		{
        			if(me->query("justice") <1000)
        				message_vision("$N对$n道：嘿嘿，还是加入我们邪教吧，油水多着呢。\n",obj,me);
        			else{
        				message_vision("$N对$n冷笑道：今天留你不得，要不然日后兄弟们可没有好日子过！\n",obj,me);
        				obj->kill_ob(me);
        			}
        		}
        		else
        		{
        			if(me->query("improbity") <1000)
        				message_vision("$N望了$n几眼，奸笑道：看你是块好材料，为什么要去找好事，不如跟我去打家劫舍来得痛快\n",obj,me);
        			else{
        				message_vision("$N对$n冷笑道：既然不是朋友，那就是敌人！！\n",obj,me);
        				obj->kill_ob(me);
        			}
        		}
        	}
        }            		
} 