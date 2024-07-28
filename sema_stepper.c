#include<stdio.h>
#include<lpc21xx.h>
#include<rtl.h>
OS_SEM sema1;
OS_TID T1,T2;
OS_RESULT RE1;
void delay(void);
unsigned int i=0,cnt1,cnt2;
__task void job1(void);
__task void job2(void);

	
__task void job1(void){
os_tsk_prio_self(2);
T2 = os_tsk_create(job2,1);
while(1){
	RE1 = os_sem_wait(sema1,0x01);
 if(RE1 ==OS_R_SEM){
  IOSET0 = 0X00008000;
	 delay();
	IOCLR0 = 0X00008000;
	 delay();
	IOSET0 = 0X00004000;
	 delay();
	IOCLR0 = 0X00004000;
 delay();
	 IOSET0 = 0X00002000;
	 delay();
	IOCLR0 = 0X00002000;
 delay();
	 IOSET0 = 0X00001000;
	 delay();
	IOCLR0 = 0X00001000;
 delay();
	 os_sem_send(sema1);
	 cnt1++;

 }

}	
}


__task void job2(void){
while(1){
os_sem_wait(sema1,0x01);
  IOSET0 = 0X00001000;
	 delay();
	IOCLR0 = 0X00001000;
	 delay();
	IOSET0 = 0X00002000;
	 delay();
	IOCLR0 = 0X00002000;
 delay();
	 IOSET0 = 0X00004000;
	 delay();
	IOCLR0 = 0X00004000;
 delay();
	 IOSET0 = 0X00008000;
	 delay();
	IOCLR0 = 0X00008000;
 delay();
	 os_sem_send(sema1);
	 cnt2++;
}	
}
void delay(void){
unsigned int l;
	for(l=0;l<65000;l++);
}

int main(){
	cnt2=0;
	cnt1=0;
	PINSEL0= 0X00000000;
	IODIR0=0X0000F000;
	os_sem_init(sema1,1);
	os_sys_init(job1);
}
