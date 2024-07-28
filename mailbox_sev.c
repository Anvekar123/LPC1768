#include<stdio.h>
#include<lpc21xx.h>
#include<rtl.h>
os_mbx_declare (msgbox,100);
U32 mpool[8* sizeof(U32)];
unsigned int no,i,cnt1=0;
void sev(unsigned int);
void delay(void);

long unsigned int disp[16]={0x003f0000,0x00060000,0x005b0000,0x004f0000,0x00660000,0x006d0000,0x007d0000,0x00700000,0x007f0000,0x006f0000,};
 OS_TID t2,t1;
 OS_RESULT re1;
 

__task void job1(void);
__task void job2(void);

__task void job1(void){
t1= os_tsk_self();
t2= os_tsk_create(job2,0);
	while(1){
	  U32*mptr;
		os_mbx_init(msgbox,sizeof(msgbox));
		mptr= _alloc_box(mpool);
		while(cnt1!=10){
		mptr[0]=cnt1;
			os_mbx_send(msgbox,mptr,0xffff);
			os_dly_wait(30);
			os_dly_wait(30);
			cnt1++;
		}
		cnt1=0;
	}
}

__task void job2(void){
while(1){
U32*rptr;
	os_mbx_wait(msgbox,(void**)&rptr,0xffff);
	no = *rptr;
	sev(no);
	os_dly_wait(30);
	no=0;
}
}
void delay(){
unsigned int i;
	for(i=0;i<65000;i++);
	for(i=0;i<65000;i++);
	for(i=0;i<65000;i++);
}
void sev(unsigned int k)
{
IODIR0=0X0FF00000;
IOSET0=0XF0000000;
delay();
IOSET0= k;
delay();
IOCLR0 = 0X00FF0000;
}

int main(){
_init_box(mpool,sizeof(mpool),sizeof(U32));
os_sys_init(job1);


}
