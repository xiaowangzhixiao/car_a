#include "siic.h"
#include "at24.h"
#include "clock.h"


//初始化siic接口
void at24cxx_config(void)
{
	siic_config();//iic初始化
}
//在at24cxx指定地址读出一个数据
//read_addr:开始读数的地址  
//返回值  :读到的数据
uint8_t at24cxx_read_one_byte(uint16_t read_addr)
{				  
	uint8_t temp=0;		  	    																 
    siic_start();  
	if(EE_TYPE>AT24C16) {
		siic_send_byte(0XA0);	   //发送读命令
		siic_wait_ack();
		siic_send_byte(read_addr>>8);//发送高地址	    
	}else siic_send_byte(0XA0+((read_addr/256)<<1));   //发送器件地址0XA0,读数据 	   
	siic_wait_ack(); 
    siic_send_byte(read_addr%256);   //发送低地址
	siic_wait_ack();	    
	siic_start();  	 	   
	siic_send_byte(0XA1);           //进入接收模式			   
	siic_wait_ack();	 
    temp = siic_read_byte(0);		   
    siic_stop();//产生一个停止条件	    
	return temp;
}
//在at24cxx指定地址写入一个数据
//write_addr  :写入数据的目的地址    
//data_to_write:要写入的数据
void at24cxx_write_one_byte(uint16_t write_addr,uint8_t data_to_write)
{				   	  	    																 
    siic_start();  
	if(EE_TYPE>AT24C16) {
		siic_send_byte(0XA0);	    //发送写命令
		siic_wait_ack();
		siic_send_byte(write_addr>>8);//发送高地址	  
	}else siic_send_byte(0XA0+((write_addr/256)<<1));   //发送器件地址0XA0,写数据 	 
	siic_wait_ack();	   
    siic_send_byte(write_addr%256);   //发送低地址
	siic_wait_ack(); 	 										  		   
	siic_send_byte(data_to_write);     //发送字节							   
	siic_wait_ack();  		    	   
    siic_stop();//产生一个停止条件 
	delay_ms(10);	 
}
//在at24cxx里面的指定地址开始写入长度为len的数据
//该函数用于写入16bit或者32bit的数据.
//write_addr  :开始写入的地址  
//data_to_write:数据数组首地址
//len        :要写入数据的长度2,4
void at24cxx_write_len_byte(uint16_t write_addr,uint32_t data_to_write,uint8_t len)
{  	
	uint8_t t;
	for(t=0;t<len;t++) {
		at24cxx_write_one_byte(write_addr+t,(data_to_write>>(8*t))&0xff);
	}												    
}

//在at24cxx里面的指定地址开始读出长度为len的数据
//该函数用于读出16bit或者32bit的数据.
//read_addr   :开始读出的地址 
//返回值     :数据
//len        :要读出数据的长度2,4
uint32_t at24cxx_read_len_byte(uint16_t read_addr,uint8_t len)
{  	
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<len;t++) {
		temp<<=8;
		temp += at24cxx_read_one_byte(read_addr+len-t-1); 	 				   
	}
	return temp;												    
}
//检查at24cxx是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
uint8_t at24cxx_check(void)
{
	uint8_t temp;
	temp = at24cxx_read_one_byte(255);//避免每次开机都写at24cxx			   
	if(temp==0X55)return 0;		   
	else {							  //排除第一次初始化的情况
		at24cxx_write_one_byte(255,0X55);
	    temp = at24cxx_read_one_byte(255);	  
		if(temp == 0X55)return 0;
	}
	return 1;											  
}

//在at24cxx里面的指定地址开始读出指定个数的数据
//read_addr :开始读出的地址 对24c02为0~255
//p_buffer  :数据数组首地址
//num_to_read:要读出数据的个数
void at24cxx_read(uint16_t read_addr,uint8_t *p_buffer,uint16_t num_to_read)
{
	while(num_to_read) {
		*p_buffer++=at24cxx_read_one_byte(read_addr++);	
		num_to_read--;
	}
}  
//在at24cxx里面的指定地址开始写入指定个数的数据
//write_addr :开始写入的地址 对24c02为0~255
//p_buffer   :数据数组首地址
//num_to_write:要写入数据的个数
void at24cxx_write(uint16_t write_addr,uint8_t *p_buffer,uint16_t num_to_write)
{
	while(num_to_write--) {
		at24cxx_write_one_byte(write_addr,*p_buffer);
		write_addr++;
		p_buffer++;
	}
}
