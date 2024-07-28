#include<rtl.h>
#include<lpc21xx.h>
#include<stdio.h>
OS_TID tsk1,tsk2,tsk3;
OS_RESULT RE1,RE2;
int cnt1,cnt2,cnt3,i;
__task void job1(void);
__task void job2(void);
__task void job3(void);


__task void job1(void)
{
	os_tsk_prio_self(1);
	os_tsk_create(job2,0);
	os_tsk_create(job3,0);
	
	while(1)
	{
		RE1=os_evt_wait_or(0x0001,0x0010);
		for(i=0;i<15;i++)
		{
			
			cnt1++;
			os_dly_wait(10);
			os_evt_set(0x0002,tsk2);
		}
	}
}
		
__task void job2(void)
{

	while(1)
	{
		RE1=os_evt_wait_or(0x0002,0x0020);
		for(i=0;i<15;i++)
		{
			
			cnt2++;
			os_dly_wait(10);
			os_evt_set(0x0003,tsk3);
		}
	}
}
		

__task void job3(void)
{

	while(1)
	{
		RE1=os_evt_wait_or(0x0003,0x0030);
		for(i=0;i<15;i++)
		{
			
			cnt3++;
			os_dly_wait(10);
			os_evt_set(0x0001,tsk1);
		}
	}
}

int main(void)
{
	cnt1=0;
	cnt2=0;
	cnt3=0;
	os_sys_init(job1);
	while(1);
}
