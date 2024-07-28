#include<stdio.h>
#include<rtl.h>
#include<lpc21xx.h>

OS_TID tsk1,tsk2;
int cnt1,cnt2;

__task void job1(void);
__task void job2(void);

__task void job1(void){
os_tsk_prio_self(2);
tsk2 = os_tsk_create(job2,0);
while(1){

cnt1++;
os_tsk_prio(tsk2,4);

}
}

__task void job2(void){

while(1){
cnt2++;
}
}

int main(void){
cnt1=0;
cnt2=0;
os_sys_init(job1);
while(1);
}