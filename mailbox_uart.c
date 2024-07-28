#include<stdio.h>
#include<lpc21xx.h>
#include<rtl.h>

os_mbx_declare (mgsbox,100);
U32 mpool[8 *sizeof(U32)];
OS_RESULT re1;
OS_TID t1,t2;
unsigned int cnt1=0,cnt2=0,i=0;
unsigned char msg1[] = "hello from task 1\r\n",rev;
void init_serial(void);

__task void job1(void);
__task void job2(void);

__task void job1(void){
 t1=os_tsk_self();
	os_tsk_create(job2,0);
	while(1){
U32 *mptr;
	os_mbx_init(mgsbox,sizeof(mgsbox));
	mptr = _alloc_box(mpool);
		while(!(cnt1==15)){ cnt1++;} 
		os_dly_wait(10);
		if(cnt1==15){
			while(msg1[i]!='\0')
				{
				mptr[0]= msg1[i];
		os_mbx_send(mgsbox,mptr,0xffff);
			cnt1=0;
			os_dly_wait(10);
			}
		}
	}
}

__task void job2(void){
while(1){
	U32 *rptr;
	os_mbx_wait(mgsbox,(void**)&rptr,0xffff);
	rev = *rptr;
		os_dly_wait(10);
	while(!(U0LSR&0X20));
		U0THR = cnt2;
		os_dly_wait(10);
	
	cnt2= 0;
}
}
void init_serial(void){
PINSEL0 = 0X0000005;
	U0LCR = 0X083;
  U0DLL = 0X61;
	U0LCR = 0X03;
}

int main(){
init_serial();
	_init_box(mpool,sizeof(mpool),sizeof(U32));
	os_sys_init_prio(job1,10);

}
