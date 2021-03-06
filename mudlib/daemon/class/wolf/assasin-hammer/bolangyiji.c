 //［博浪一击］
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int tobe_or_nottobe(object me,object target,int extra, object weapon);
int perform(object me, object target)
{
        string msg;
        int extra,i;
        object weapon;
        
        extra = me->query_skill("assasin-hammer",1);
        if(me->query("class")!="wolfmount")
                return notify_fail("只有狼山弟子才能使用「博浪一击」刺杀。\n");
        if ( extra < 100) 
                return notify_fail("你的［博浪七杀］锤法还不够纯熟！\n");
        if( !target || !target->is_character()) 
                return notify_fail(HIR"你要刺杀谁？\n"NOR);
        if (target->query("combat_exp")*10<me->query("combat_exp"))
                return notify_fail("此人经验太差，根本不必刺杀\n");
        if(environment(me)->query("no_fight")) 
                return notify_fail("这里不准刺杀！！\n");
        if(me->is_busy())
                return notify_fail("你现在没空！！\n"); 
        if( target==me) return notify_fail(HIR"你不想活了？\n"NOR);
                
        weapon=me->query_temp("weapon");
        
        if((int)me->query("bellicosity") > 100 
                ||(int)me->query("cps")< (int)target->query("cps")
                || me->query_skill("assasin-hammer",1)/2< target->query_skill("perception",1))
                tell_object(target, HIR"\n你忽然觉得一股杀气迫在眉睫！直觉告诉你，还是离开这里为妙。\n"NOR);
        
        tell_object(me, HIB"\n你全神贯注，算准" + target->query("name") + "的方位举动，暗暗准备出手！\n"NOR);
        
        extra = extra*(me->query("kar") + me->query("cps"));
        call_out("tobe_or_nottobe",3, me, target, extra, weapon);
        me->start_busy(6);
        return 1;
}
           
int tobe_or_nottobe(object me,object target,int extra, object weapon)
{
        string msg;
        int hit_rate;
        int hit_damage;
        if(!me||!target||environment(target)!=environment(me)) {
                tell_object(me, WHT"真可惜，你要刺杀的目标溜走了。\n"NOR);      
                return 0;
        }
        if(!present(weapon,me)||weapon->query("equipped")!="wielded"){
                tell_object(me, WHT"手软了？你怎么把武器收起来了？ \n"NOR);
                return 0;
        }
                 
        msg = YEL "\n$N跃身而起，手中"+weapon->query("name")+YEL"一转，带起阵阵风雷之声。\n$N手一抖，" + weapon->query("name") + YEL"脱手飞出，如风卷黄沙呼啸着击向$n。 \n"NOR;
        hit_rate = 15;
        hit_rate += 100 * random((extra*200 + (int) me ->query("combat_exp")));
        hit_rate = hit_rate / (200+ (int) target->query("combat_exp"));
        hit_damage = (int) me->query("str") * extra + weapon->weight();
        hit_damage = hit_damage/160 + hit_damage*hit_rate/40000;
        message_vision(msg, me, target);
        
        if (hit_rate>150) {
                msg = HIR"只见" +weapon->query("name")+ HIR"带着一阵低啸和猛烈的劲风“轰”地击中了$n的头部！\n"NOR;
                if (hit_damage>(int) target->query("max_kee"))
                        msg += HIW"\n结果$n被砸得脑浆迸流，惨不忍睹！！！\n"NOR;
                else
                        msg += RED"\n结果$n被砸得口中鲜血狂喷！！！\n"NOR;              
                target->start_busy(1);
        }
        else if (hit_rate>60){
                msg = HIR"只见" +weapon->query("name")+ HIR"带着一阵低啸和猛烈的劲风“轰”地击中了$n的胸口！\n"NOR;
                msg += RED"\n结果$n被砸得口中鲜血狂喷！！！\n"NOR;
                target->start_busy(1);
        }
        else if (hit_rate>35){
                msg = HIR"只见" +weapon->query("name")+ HIR"带着一阵劲风“轰”地击中了$n！\n"NOR;
                msg += WHT"\n结果$n被砸得面如死灰，抽搐不止！！！\n"NOR;
                target->start_busy(1);
   }
        else {
                msg = HIR"只见" +weapon->query("name")+ HIR"带着一阵劲风贴着$n的脑袋飞过，只差几寸没有击中！\n"NOR;
                hit_damage = 0;
        }
        target->receive_wound("kee", hit_damage, me);
        weapon->move(environment(me));
        message_vision(msg, me, target);
        COMBAT_D->report_status(target);
        target->kill_ob(me);
        me->kill_ob(target);    
        return 1;
}      
