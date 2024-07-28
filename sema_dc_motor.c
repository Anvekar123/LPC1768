#include<stdio.h>
#include<lpc21xx.h>
#include<rtl.h>
OS_SEM sema1;
OS_TID t1,t2;
OS_RESULT RE1;
unsigned int cnt1=0, cnt2=0;
void delay(void);
__task void job1(void);
__task void job2(void);

__task void job1(void){
os_tsk_prio_self(2);
t2=os_tsk_create(job2,0);	
while(1){

RE1=os_sem_wait(sema1,0x01);
	if(RE1 == OS_R_SEM){
	IOSET0 = 0X00000400;
	IOCLR0 = 0X00000800;
		delay();
		delay();
	IOSET0 = 0X00000800;
	IOCLR0 = 0X00000400;
		delay();
		delay();
	cnt1++;
os_sem_send(sema1);	
	}

}

}

__task void job2(void){
while(1){
	IOSET0 = 0X00000400;
	IOCLR0 = 0X00000800;
		delay();
		delay();
	IOSET0 = 0X00000800;
	IOCLR0 = 0X00000400;
		delay();
		delay();
	os_sem_send(sema1);
	cnt2++;
	
	}
}



void delay(void)
{
unsigned int k;
	  for(k=0;k<65000;k++);
		for(k=0;k<65000;k++);
}



int main(){
PINSEL1 = 0X00000000;
IODIR0 = 0X00000C00;
IOCLR0 = 0X00000C00;

	os_sem_init(sema1,1);
	os_sys_init(job1);
}
