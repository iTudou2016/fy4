 // rm.c
#include "/doc/help.h" 
inherit F_CLEAN_UP;
int help(object me); 
int main(object me, string file)
{
        seteuid(geteuid(me));
    if (!file) return notify_fail("��Ҫɾ���Ǹ�����?\n");
        if( rm(resolve_path(me->query("cwd"), file)) ) {
                write("Ok.\n");
                log_file("static/REMOVE_LOG",
                        sprintf("%s(%s) removed %s on %s\n",
                                me->name(1), me->query("id"), file, ctime(time()) ) );
        }
                        
        else
                write("��û��ɾ�����������Ȩ����\n");
        return 1;
}  
int help(object me)
{
  write(@HELP
ָ���ʽ : rm <����> 
��ָ�������(��)ɾ����Ȩ�޸ĵĵ�����
HELP
    );
    return 1;
}  