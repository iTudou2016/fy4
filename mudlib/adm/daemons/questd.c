 // questd.c
// Copyright (C) 1995 - 2001, by FengYun Workshop. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
//  
#pragma optimize
#include <ansi.h> 
void give_reward(object who,object accomplisher, mapping quest);
string wait_period(int timep);
void log_quest(object me, object owner, mapping quest, int reward_exp, int reward_pot, int used_time, int base); 
void create() {
        seteuid(ROOT_UID);
} 
int accept_quest_object(object who, object ob, object me)
{
        int val, delay, i;
        object* mem;
        mapping quest; 
        if(ob->is_character()) {
                return 0;
        } 
        mem = pointerp(who->query_team()) ? who->query_team() : ({ who });
        for(i=0; i<sizeof(mem); i++) {
                if (mem[i]) {
                        if(mapp(quest = mem[i]->query("quest")) 
                                && (string)ob->query("name") == quest["quest"]
                                && (string)(quest["quest_type"]) == "寻"
                                && (time() - mem[i]->query("task_time") <= 900)) {
                                give_reward(mem[i], who, quest);
                                return 1;
                        }
                }
        } 
        val = ob->value();
        // decreased gold to cancel quest from 1-9 gold to 50  silver - 4.5 gold 
        if(val && who->query("quest") && val >=5000 && val <= 50000) {
                who->set("quest", 0 );
                tell_object(who, me->name() + "说道：好吧，这个任务就算了吧．．\n");
                who->delete_temp("quest_number");
                delay = ((who->query("task_time") + 1000 - time()) * 100 - val * 2) * 60 /10000;
           if (who->query("combat_exp")<600000) {
                        delay = delay/2 + (delay/6)*(who->query("combat_exp")/200000);
                }
                who->set("next_time", time() + delay);
                return 1;
        }
        return 0;
} 
int give_quest(object who, mapping me)
{
        mapping quest;
        int i,combatexp, max_exp;
        string tag = "_default";
        string qstr;
        object* mem;
    
        if(who->is_ghost() || who->is_zombie()) {
                tell_object(who,"鬼魂不可要任务．\n");  
                return notify_fail("\n");
        }
        
        if(who->query("combat_exp") > 25000000 ){
                tell_object(who,"这些小事就不用麻烦您老人家了。。。\n");  
                return notify_fail("\n");
        }
        
        if((quest =  who->query("quest")) && (time() - who->query("task_time") < 900)) {
                return 0;
        }
        
        if((who->query("next_time")) > time()) {
                return notify_fail("\n");
        }
        
        max_exp = 0;
        combatexp =0;
        
        //need to use max_exp in team
        //A team's quest depends on the max_exp player
        mem = pointerp(who->query_team()) ? who->query_team() : ({ who });
        //For the quest system, if his exp > 3000000, then return back to do 1M quest.
        //chnaged cap for 5M quest to 15M -- ice @12-18-2003
        for(i=0; i<sizeof(mem); i++) {
                if (mem[i]) {
                        max_exp = (int)mem[i]->query("combat_exp");
                   if (max_exp>15000000) {
                                max_exp = 15000000;
                        }
                        combatexp = (max_exp>combatexp) ? max_exp : combatexp;
                }
        }  
// qlist_common are basically the same as a combination of small/middle/large
// with more random/seasonal items and quests acrossing the exp boundary.  
        if(!random(5) && combatexp<2400000) {
                tag="_common";
        } else  if (!random(5) && combatexp>=2400000 && combatexp<3000000)
                tag="_common_2";
          else  {       
                if(combatexp/1000 <= 100) {
                        tag="_small";
                } else if(combatexp/1000 <= 1000) {
                        tag="_middle";
                } else if(combatexp/1000 <= 6500) {
                        tag="_large";
                } else {
                        tag="_super";
				}
		  }
        quest = QUEST_D(tag)->query_quest(combatexp/1000);
        who->set("quest", quest);
        who->set("task_time", (int)time());
        who->add_temp("quest_number", 1);
        
        if(quest["quest_type"] == "寻") {
                qstr = HIW"找回『"NOR + quest["quest"] + HIW"』给" 
                                + me["employer"] + HIW"。"NOR;
        } else if(quest["quest_type"] == "杀") {
                qstr = HIW"替" + me["employer"] + HIW"杀了『"NOR
                                + quest["quest"] + HIW"』。"NOR;
        } 
        for(i=0; i<sizeof(mem); i++) {
                if (mem[i]) {
                    if (mem[i] == who) tell_object(who, HIW + me["name"] + HIW"说道：请" + qstr + NOR"\n");
                    else tell_object(mem[i], HIW + "队伍成员 "+ who->name() + HIW" 现在的任务是: " + qstr + NOR"\n");
                }
        } 
        
   CHANNEL_D->do_sys_channel("qst", sprintf("%s让%s(%s)%s\n",
                me["name"],
                HIW + who->name(),
                HIW + who->query("id"),
                HIW + qstr));
        return 1;
} 
void give_reward(object who, object accomplisher, mapping quest) 
{
        int i, base, d_reward, team_size, q_bonus, max_exp,e_reward,single_exp;
        int used_time,t_reward;
        int combat_exp,pot,score, ratio, sum_exp, i_pot,
                reward_silver, reward_exp, reward_score,reward_pot;
        int team_bonus, silver;
        int accomp_exp, accomp_pot, accomp_silver;
        
        string reward_msg;
        object ob;
        object* mem;
        
                
        mem = pointerp(who->query_team()) ? who->query_team() : ({ who });
        team_size = sizeof(mem);
        sum_exp = 0;
        max_exp = 0; 
        // Check if max_exp player left team and calculate max_exp, sum_exp
        for(i=0; i<team_size; i++) {
                if (mem[i]) {
                    q_bonus = (int)mem[i]->query("combat_exp");
                    max_exp = (max_exp>q_bonus) ? max_exp : q_bonus;
                    sum_exp += q_bonus;             
                }
        }
        
        q_bonus = quest["exp_bonus"]; 
        //Max_exp player left team
        if (700*q_bonus > max_exp){
                q_bonus = max_exp/1024 ;
        }
        
   //Calculate base bonus
        
        // For less than 10K players, the base bonus is 20+ exp/3
        if(q_bonus < 10) {
                base= 20 + q_bonus/3;
        } else if (q_bonus < 800){
    // For players exp from 10k to 800k, the bonus is a curve
    // the reward grows almost linear at low end, but slower when 
    // close to 800k
                base= 30 + (q_bonus *2)/9- (q_bonus*q_bonus)/7000;
        // When exp is >800k, the reward is linear again but at much 
        // lower rate
        } else if (q_bonus < 2200) base= 50 + q_bonus/12;
        // <- < 2.2M reach reward max 
        else  base= 40 + q_bonus/24 + random(q_bonus/24); 
        // Further lower high exp quest bonus, and cap base at 260
        if(base > 160) {
                base = 260 - 3*16000/(base*2);  
        }
        
        //Check difficulty
        if(quest["difficulty"]) {
                d_reward = base * (quest["difficulty"]-5)/10;
                if (accomplisher->query("combat_exp")>10000000)
                        d_reward=d_reward/2;
        }
        
        used_time = (int) time() - who->query("task_time");
        if(used_time < 60) {  //Get 50% bonus for finishing within 1 minutes
                t_reward = base / 2;
        } else if (used_time < 360) {  //Get a little bonus for finishing within 6 minutes
                t_reward = base * (360 - used_time) /600;
        }
                
        combat_exp = base + d_reward + t_reward;
        combat_exp = combat_exp + random(combat_exp); 
        //Add some bonus for team to share 
        
//      tell_object(who,"q_bonus is"+(string)(q_bonus)+".\n");
//      tell_object(who,"exp reward is"+(string)(combat_exp)+".\n");
   
        if (q_bonus<1024) {
                team_bonus = combat_exp;
                team_bonus = team_bonus < (team_size -1)* (combat_exp/5) ? team_bonus : (team_size -1)* (combat_exp/5) ;
                combat_exp += team_bonus;       
        } else {
                team_bonus =  combat_exp*(2/5) ;
                team_bonus = team_bonus < (team_size -1)* (combat_exp/12) ? team_bonus : (team_size -1)* (combat_exp/12) ;
                combat_exp += team_bonus;       
        }
        
//      tell_object(who,"team_bonus is"+(string)(team_bonus)+".\n");
//      tell_object(who,"total exp reward"+(string)(combat_exp)+".\n");
        
        if(q_bonus < 200) 
        pot = combat_exp / 7 + 1;
        else
        pot = combat_exp / 6 + 1;
        
        silver = 20 + random(40);
        
        // add some more money for 1M+ players
        if (q_bonus>1000) silver = silver*3/2;
        
        accomp_exp = combat_exp;
        accomp_pot = pot;
        accomp_silver = silver;
        
        if (sum_exp == 0) sum_exp = 1;
        for(i=0; i<sizeof(mem); i++) {
                if (mem[i])
                if (mem[i]!=accomplisher) {
                        
                        ratio = ( 100*mem[i]->query("combat_exp"))/sum_exp;
                        reward_exp= combat_exp*ratio/100>0 ? combat_exp*ratio/100 : 1;
                        if((silver/team_size ) > 0 && objectp(ob = new("/obj/money/silver"))) {
                                reward_silver= (silver*ratio)/100>0 ? (silver*ratio)/100 : 1;
                                ob->set_amount(reward_silver);
                                if(mem[i]->query("env/savemymoney"))
                                        mem[i]->add("deposit",reward_silver*100);
                           else
                                        ob->move(mem[i]);
                        }
                
/*                        accomp_exp = accomp_exp - reward_exp;
                        accomp_pot = accomp_pot - pot * (ratio/100);
                        accomp_silver = accomp_silver - reward_silver;  */
                        
                         i_pot=pot*ratio/100;                                             
                        if (mem[i]->query("combat_exp")>20000000) {
                                        reward_exp=combat_exp/8+random(combat_exp/8);i_pot=accomp_pot/6+random(accomp_pot/6);
                                }
                                else if (mem[i]->query("combat_exp")>15000000) {reward_exp=accomp_exp/6;i_pot=i_pot/3;  }
                                else if (mem[i]->query("combat_exp")>10000000) {reward_exp=accomp_exp/4;i_pot=i_pot*2/5;}
                                else if (mem[i]->query("combat_exp")>8000000) {reward_exp=accomp_exp/4;i_pot=i_pot/2;}
                                else if (mem[i]->query("combat_exp")>5000000) {reward_exp=reward_exp/2;i_pot=i_pot*2/3;}
                                else if (mem[i]->query("combat_exp")>4000000) {reward_exp=reward_exp*(3/4);i_pot=i_pot*3/5;}
                                else if (mem[i]->query("combat_exp")>2000000) {reward_exp=reward_exp*(3/4);i_pot=i_pot*3/4;}
                        mem[i]->add("combat_exp", reward_exp);
                        mem[i]->add("potential", i_pot);
                        mem[i]->add("score", (score*ratio) / 100);      
                        
                        log_quest(mem[i], who, quest, reward_exp, i_pot, used_time, base);
                                                 
                        score =  mem[i]== accomplisher? 1 : 0;
                        reward_msg = mem[i]==who ? HIW : HIW+"队伍成员 "+who->name()+" 的";
                        reward_msg +="任务被"+accomplisher->name()+"完成，你被奖励了：\n\t\t" +
                                chinese_number(reward_exp) + "点实战经验\n\t\t"+
                                chinese_number(i_pot) + "点潜能\n\t\t" +
                                chinese_number(score) + "点评价\n\t\t" + 
                                chinese_number(reward_silver) + "两银子\n" + NOR;
                        
                        tell_object(mem[i],reward_msg);
                }
        }
        
        score = 1+random(accomplisher->query("combat_exp")/1500000);
        if (accomplisher->query("combat_exp")>20000000) {
                accomp_exp=accomp_exp/4;accomp_pot=accomp_pot/3;
           }
                else if (accomplisher->query("combat_exp")>15000000) {accomp_exp=accomp_exp/4;accomp_pot=accomp_pot/3;}
                else if (accomplisher->query("combat_exp")>10000000) {accomp_exp=accomp_exp*2/5;accomp_pot=accomp_pot*2/5;}
                else if (accomplisher->query("combat_exp")>8000000) {accomp_exp=accomp_exp*2/5;accomp_pot=accomp_pot/2;}
                else if (accomplisher->query("combat_exp")>5000000) {accomp_exp=accomp_exp/2;accomp_pot=accomp_pot*2/3;}
                else if (accomplisher->query("combat_exp")>4000000) {accomp_exp=accomp_exp*3/5;accomp_pot=accomp_pot*3/5;}
                else if (accomplisher->query("combat_exp")>2000000) {accomp_exp=accomp_exp*3/4;accomp_pot=accomp_pot*3/4;}          
        accomplisher ->add("score", score);
        accomplisher->add("combat_exp", accomp_exp);
        accomplisher->add("potential", accomp_pot);
        
        log_quest(accomplisher, who, quest, accomp_exp, accomp_pot,used_time, base);
        
        if(objectp(ob = new("/obj/money/silver"))) {
                ob->set_amount(accomp_silver);
                if(accomplisher->query("env/savemymoney"))
                        accomplisher->add("deposit",accomp_silver*100);
                else
                        ob->move(accomplisher);
        }
        reward_msg = accomplisher==who ? HIW : HIW+"队伍成员 "+who->name()+" 的";
        reward_msg +="任务被你完成，你被奖励了：\n\t\t" +
        chinese_number(accomp_exp) + "点实战经验\n\t\t"+
        chinese_number(accomp_pot) + "点潜能\n\t\t" +
        chinese_number(score) + "点评价\n\t\t" + 
        chinese_number(accomp_silver) + "两银子\n" + NOR;
        
        tell_object(accomplisher,reward_msg);
        
        who->set("quest", 0 );
} 
string wait_period(int timep) {
        int t, d, h, m, s;
        string delay = "";
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;
   
        if(d) {
                delay += chinese_number(d) + "天";
        }
        if(h) {
                delay += chinese_number(h) + "小时";
        }
        if(m) {
                delay += chinese_number(m) + "分";
        }
        if(s) {
                delay += chinese_number(s) + "秒";
        }
        return delay;
} 
int flower_delivery_reward(object me, object who,object flower) 
{
        mapping delivery;
        int exp,pot,success_time;
        object coin;
        if(!mapp(delivery = flower->query("delivery"))) return 0;
        if(base_name(who) != delivery["receiver"]) return 0;
        if (flower->query("delivery_time") != me->query("delivery_time")) return 0;
        success_time = (int)me->query("delivery/success");
        me ->set("delivery/success",success_time+1);
        switch (random(3))
        {
        case 0:
                message_vision("$N兴奋地惊叫一声：“这是他送来的么？ ”\n",who);
                break;
        case 1:
                message_vision("$N甜甜地对$n一笑。\n",who,me);
                break;
        case 2:
                message_vision("$N满面春风，笑意盈盈，拍了拍$n道：“这是给你的，辛苦你了”。\n",who,me );
                coin = new("/obj/money/silver");
                coin->set_amount(random(200)+1);
                coin->move(me);
                tell_object(me,who->name()+"递给你一些钱。\n");
                break;
        }

        pot = 100+random(200);
        exp = 800+random(1000);
        me->add("combat_exp",exp);
        me->add("potential",pot);
        tell_object(me,"你被奖励了：\n" + chinese_number(exp) + "点实战经验\n"
                        + chinese_number(pot) + "点潜能\n");
        me->delete("delivery");
        me->delete("delivery_time");
        /*
        if(!undefinedp(quest["fin_func"])) {
                call_other(this_object(),quest["fin_func"],me,who,quest_item);
        }*/
        if(flower) {
                destruct(flower);
        }
        return 1;
} 
void log_quest(object me, object owner, mapping quest, int reward_exp, int reward_pot, int used_time, int base) 
{
        if (reward_exp <1000) return; 
        log_file("QUEST_REWARD",
                        sprintf("%s(%s) 完成了 %s(%s) 的任务 ：  %s %s 难度 %d 时间 %s\n奖励经验：%d 奖励潜能：%d used_time: %d  base: %d\n",
                                me->name(1), geteuid(me), owner->name(1), geteuid(owner), quest["quest_type"], quest["quest"], quest["difficulty"], ctime(time()), 
                                reward_exp, reward_pot , used_time, base)); 
}     
