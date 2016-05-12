#include "cmd_func.h"
#include "cmd.h"
#include "parameter.h"  //���̹����ģ������Ҫ��ֲ�����룬��ȥ����ͷ�ļ�
#include "stm32f4xx.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"
#include "movement.h"
#include "maxon.h"


void cmd_param_func(int argc,char *argv[]){
    float param_value;
   // char param_name[PARAM_NAME_LENGTH];
    list_node *p;
    int group;
    if(argc < 2){
        uprintf(CMD_USARTx,"param <cmd>");
    }
    if(strcmp(argv[1],"print") == 0){
        param_print(param_group_now());
    }else if(strcmp(argv[1],"set") == 0){
        param_value = atof((char *)argv[3]);
        if(param_set(argv[2],param_value) < 0){
            uprintf(CMD_USARTx,"not found param name:%s",argv[2]);
        }
    }else if(strcmp(argv[1],"save") == 0){   //���������оƬ��
        param_save_to_flash();
    }else if(strcmp(argv[1],"switch") == 0){   //�л�������
        param_switch(atoi(argv[2]));
    }else if(strcmp(argv[1],"mobile-print") == 0){
        group = atoi(argv[2]);
        p = get_param_list();
        p = p->link;
        while(p != NULL){
            uprintf(CMD_USARTx,"[P#%s#%4f]",p->data->param_name,p->data->param_value[group]);
            p = p->link;
        }
		}else if(strcmp(argv[1],"reset") == 0){
				param_list_reset();
		}
		else{
        uprintf(CMD_USARTx,"arg not found");
        return;
    }
}

void cmd_reboot_func(int argc,char *argv[]){
    NVIC_SystemReset();
}

void cmd_stop_func(int argc,char *argv[]){
		stop_all();
		maxon_stop();
}

void cmd_maxon_func(int argc,char *argv[]){
		if(argc < 2){
        uprintf(CMD_USARTx,"param <cmd>");
    }
		if(strcmp(argv[1], "baud") == 0){
				maxon_baud();
		}else if(strcmp(argv[1], "up") == 0){
				maxon_up();
		}else if(strcmp(argv[1], "down") == 0){
				maxon_down();
		}else if(strcmp(argv[1], "current") == 0){
				maxon_current();
		}else if(strcmp(argv[1], "config") == 0){
				maxon_config();
		}else if(strcmp(argv[1], "cmove") == 0){
				maxon_current_move();
		}else if(strcmp(argv[1], "ask") == 0){
				uprintf(USART1, "g r0x%c%c\r\n\n", argv[2], argv[3]);
		}
}
