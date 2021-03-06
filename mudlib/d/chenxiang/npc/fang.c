#include <ansi.h>
inherit NPC;
void create()
{
        set_name("方龙香", ({ "fang longxiang", "fang" }) );
        set("long",
                "他是这里的老板，眼角虽有了皱纹，但眼睛却还是雪亮，一只断手装\n了个铁钩子。\n");
        set("nickname", HIC"铁钩银划"NOR);
        set("title", "青龙会 分舵舵主");
        set("chat_chance",1);
        set("chat_msg", ({
        "方龙香朝屋后的花园望了望，恨声道：卫天鹰算什么东西，有什么\n资格叫我替他看着那几箱珠宝。\n",
                        })  );
        set("inquiry",([
        "孔雀翎"  :"据说天下的暗器一共有三百六\n十几种，但自从世上有暗器以来，孔雀翎无疑是其中最成功，最可怕\n的一种。\n",
                ]) );
        set("combat_exp", 1000000);
        set("int",30);
        set("cor",25);
        
        set_skill("sword",100);
        set_skill("move", 100);
        set_skill("parry",100);
        set_skill("dodge", 100);
        set_skill("force", 100);
        set_skill("literate", 80);
        set_skill("unarmed",100); 
        set_skill("yunwu-strike", 120);
        set_skill("siqi-sword", 120);
        set_skill("xianjing", 120);
        set_skill("liuquan-steps", 120); 
        map_skill("unarmed", "yunwu-strike");
        map_skill("sword", "siqi-sword");
        map_skill("force", "xianjing");
        map_skill("dodge", "liuquan-steps"); 
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "dodge.liushuichanchan" :),
        }) );  
        setup();
        carry_object("/obj/armor/cloth")->wear();
        carry_object(__DIR__"obj/hook")->wield();
}      
