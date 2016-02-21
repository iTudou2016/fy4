#include <ansi.h>
inherit NPC; 
void create()
{
        set_name("花寡妇", ({ "hua gua fu", "hua", "gua fu" }) );
        set("gender", "女性");
        set("per", 24);
        set("str", 40);
        set("age", 35);
        set("class", "ghost");
        create_family("幽灵山庄", 2, "弟子");
        set("combat_exp", 200000);
        set("long",
                "她长得并不美，颧骨太高了些，嘴也太大了些。
但她无疑是个很特别的女人，大多数男人只要看她一眼，
立刻就会被她吸引住。\n"
        );
        set("no_arrest",1);
        set_skill("unarmed", 100);
        set_skill("move", 50);
        set_skill("dodge", 50);
        set_skill("whip", 100);
        set_skill("snowwhip", 100);
        map_skill("whip", "snowwhip");
        setup();
} 
void init()
{
        object          me; 
        ::init();
        if( interactive(me = this_player()) && !is_fighting() ) {
                add_action("do_sleep", "sleep");
                call_out("greeting", 1, me);
        }
} 
int greeting(object me)
{
        remove_call_out("greeting");
        if(environment(me) == environment(this_object())) {
                if( (string)me->query("family/family_name")!="幽灵山庄" ) {
                   message_vision(HIY "\n$N倒在床上，用一双迷迷蒙蒙的眼睛打量着$n" +
                                "，道：上床呀，为什么还不上床？\n"NOR, this_object(), me);
                }
                call_out("greeting", 10, me);
        }
        return 1;
} 
int do_sleep(string arg)
{
        object *inv;
        int i; 
        if(!arg || arg != "hua gua fu") return 0;
        remove_call_out("greeting");
//      this_player()->set_temp("disable_inputs",1);
        this_player()->start_busy(3);
        this_player()->ccommand("remove all");
        message_vision(HIY "\n$N迫不极耐的脱下衣服，跳上床去，一把抱住了$n\n．．．．．．\n．．．\n"NOR, this_player(), this_object());
/*      inv = all_inventory(this_player());
        for(i=0;i<sizeof(inv);i++) {
                if(inv[i]->query("no_drop")){
                        destruct(inv[i]);
                } else {
                        inv[i]->move(environment(this_player()));
                }
        }*/
        call_out("do_smoke", 5, this_player());
        return 1;
} 
int do_smoke(object me)
{
        if (!objectp(me) || me->is_ghost() || environment(me)!=environment(this_object()))
                return 1;
        say(HIR "\n窗隙里慢慢伸进了一只吸管\n"NOR);
        call_out("do_smoke1", 2, me);
        return 1;
} 
int do_smoke1(object me)
{
        if (!objectp(me) || me->is_ghost() || environment(me)!=environment(this_object()))
                return 1;
   say(HIR "\n从吸管里喷出一股暗紫色的浓烟。\n"NOR);
        me->unconcious();
//      me->delete_temp("disable_inputs");
// kick,who change this?
// will cause crash
        me->move(AREA_GHOST"dijiao2");
        return 1;
} 
//??
//I think don't need bah?
/*
void die()
{
        int i;
        object *players;
        players = filter_array(all_inventory(environment()),(:userp($1):)); 
        for (i=0; i<sizeof(players); i++) {
                if (players[i]->query_temp("is_unconcious")) {
                        players[i]->revive();
                        message_vision(HIB"$N如大梦初醒，发现身边的花寡妇已经死了，不由得惊叫起来。\n"NOR, players[i]);
                }
        }
        ::die();
}*/      
