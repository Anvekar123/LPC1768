#include<rtl.h>
#include<lpc21xx.h>
#include<stdio.h>
void delay(void);
OS_TID tsk1,tsk2,tsk3; //declare task identification number
int cnt1,cnt2;
int i;
__task void job1(void); //led
__task void job2(void); // stepper motor
 
__task void job1(void)
{
IODIR0 = 0x00ff0000;
//IOSET0 = 0x000F0000;
os_tsk_prio_self(2); //assign priority to job1
tsk2 = os_tsk_create(job2,1); //create job2
while(1)
{
 IOCLR0 = 0x000f0000; //LEDS on
 for(i=0;i<65000;i++);
 for(i=0;i<65000;i++);
 IOSET0 = 0x000f0000; //LEDS off
 for(i=0;i<65000;i++);
 for(i=0;i<65000;i++);
os_tsk_prio(tsk2,2); //change priority to tsk2
 }
}

__task void job2(void) //job2function declaration
{
 PINSEL0 = 0x00000000;
 IODIR0 = 0x0000F000;
while(1)
 {
 IOSET0 = 0x00008000;
delay();
 IOCLR0 = 0x00008000;
 IOSET0 = 0x00004000;
delay(); 
 IOCLR0 = 0x00004000;
 IOSET0 = 0x00002000;
delay();
 IOCLR0 = 0x00002000;
 IOSET0 = 0x00001000;
delay();
 IOCLR0 = 0x00001000;
delay();
 }
}
void delay(void)
{
 unsigned long int j;
for (j=0; j<65000; j++);
}
int main(void)
{
cnt1= 0;
cnt2 =0;
os_sys_init(job1); //initialize job1
while(1);
}