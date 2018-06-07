#include "serialSend.h"

void serial_send(int fd,struct termios *options,unsigned char sendbuff[])
{
	
		  /*串口发送*/  		
		  cfsetospeed(options,B115200);    
		  //修改控制模式，保证程序不会占用串口  
		  options->c_cflag |= CLOCAL;  
		  //修改控制模式，使得能够从串口中读取输入数据  
		  options->c_cflag |= CREAD;  
		  
		  //不使用流控制  
		  options->c_cflag &= ~CRTSCTS;  
	    
		  //设置数据位，8位
		  options->c_cflag |= CS8; 

		  //无校验位
		  options->c_cflag &= ~PARENB;   
		  options->c_iflag &= ~INPCK;     
		  
		  //一个停止位
		  options->c_cflag &= ~CSTOPB; 
		  
		  
		  //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读  
		  tcflush(fd,TCIFLUSH);  
		      
			//激活配置 (将修改后的termios数据设置到串口中）  
		  int test= tcsetattr(fd,TCSANOW,options) ; 
				  
		  write(fd,(sendbuff),8);		    
  
}
