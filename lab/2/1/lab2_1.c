
#ifndef __LAB2_1_C__
#define __LAB2_1_C__

#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdio.h>
#include <signal.h>


void P(int semid, int index);  //P操作函数
void V(int semid, int index);  //V操作函数
void *subp1();                 //线程执行函数1
void *subp2();                 //线程执行函数2

int semid = 0;                 //信号灯
int selled = 1;                //已售
int all = 10;                  //售票总数
pthread_t p1,p2;               //线程句柄定义

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};

int main(){
    //创建信号灯
    int semsnum = 1;           //信号灯个数
    semid = semget(IPC_PRIVATE,semsnum,IPC_CREAT | 0666);
    if(semid == -1)
        printf("Semget ERROR!\n");
    else{
        printf("Semget Success!\n");
        //信号灯赋初值
        union semun arg1;
        arg1.val = 1;
        if (semctl(semid, 0, SETVAL, arg1) == -1)
            printf("Semctl ERROR!\n");
        else{
            printf("Semctl Success!\n");
            //创建多个线程
            if(pthread_create(&p1,NULL,(void *)subp1,NULL) == -1){
                printf("pthread_create p1 ERROR!\n");    
                exit(0);
            }
            
            if(pthread_create(&p2,NULL,(void *)subp2,NULL) == -1){
                printf("pthread_create p2 ERROR!\n");    
                exit(0);
            }
            printf("pthread_create Success!\n");
            //等待线程运行结束
            if(pthread_join(p1, NULL) != 0)
                printf("pthread_join p1 ERROR!\n");
            if(pthread_join(p2, NULL) != 0)
                printf("pthread_join p2 ERROR!\n");
            printf("pthread_join Success!\n");
            //删除信号灯
            union semun sem_union;
            if (semctl(semid, 1, IPC_RMID, sem_union) == -1)
                printf("Delete ERROR!\n");
            else
                printf("Delete Success!\n");
            
            
        }
    }
    return 0;
}

void *subp1(){
    int sell1 = 1;//线程1卖的票数
	while (1) {
		P(semid, 0);
		if (selled > all) {
			printf("Sold out!\n");
			V(semid, 0);
			break;
		}
		printf("p1 sold No.%d ticket. \n", selled);
		sell1++;
		selled++;
		V(semid, 0);
	}
	printf("p1 had sold %d tickets in total.\n", sell1 - 1);
	printf("p1 exit.\n");
    return ((void *)0);
}

void *subp2(){
    int sell2 = 1;
	while (1) {
		P(semid, 0);
		if (selled > all) {
			printf("Sold out!\n");
			V(semid, 0);
			break;
		}
		printf("p2 sold No.%d ticket. \n", selled);
		sell2++;
		selled++;
		V(semid, 0);
	}
	printf("p2 had sold %d ticket(s).\n", sell2 - 1);
	printf("p2 exit.\n");
	pthread_exit(0);
    return ((void *)0);
}

void P(int semid, int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    if(semop(semid, &sem, 1) == -1)
        printf("Pfunc ERROR!\n");
    return;
}

void V(int semid, int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    if(semop(semid, &sem, 1) == -1)
        printf("Vfunc ERROR!\n");
    return;
}

#endif