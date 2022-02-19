#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <pthread.h>

void P(int semid, int index);  //P操作函数
void V(int semid, int index);  //V操作函数
void *subp1();                 //线程执行函数1
void *subp2();                 //线程执行函数2
void *subp3();                 //线程执行函数3

int sum = 0;                       //zonghe
int count = 0;                     //jishu
int semid;

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};



void main(){
    int semnum = 3;
    semid = semget(IPC_PRIVATE, semnum, IPC_CREAT | 0666);
    if (semid == -1)
    {
        printf("Semget ERROR!\n");
        exit(1);
    }
    union semun sem[3];
    sem[0].val=1;
    sem[1].val=0;
    sem[2].val=0;
    if(semctl(semid,0,SETVAL,sem[0])==-1){
        printf("sem[0] initial ERROR!\n");
        exit(1);
    }
    if(semctl(semid,1,SETVAL,sem[1])==-1){
        printf("sem[1] initial ERROR!\n");
        exit(1);
    } 
    if(semctl(semid,2,SETVAL,sem[2])==-1){
        printf("sem[2] initial ERROR!\n");
        exit(1);
    } 

    pthread_t p1,p2,p3;
    if(pthread_create(&p1,NULL,(void*)subp1,NULL)){
        printf("pthread1 creating ERROR!\n");
        exit(1);
    }
    if(pthread_create(&p2,NULL,(void*)subp2,NULL)){
        printf("pthread2 creating ERROR!\n");
        exit(1);
    }
    if(pthread_create(&p3,NULL,(void*)subp3,NULL)){
        printf("pthread3 creating ERROR!\n");
        exit(1);
    }
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    semctl(semid,0,IPC_RMID,NULL);
    exit(0);
}


void P(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}
void V(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}
void *subp1(){
    sum=0;
    for(int i=1;i<=100;i++){
        P(semid,0);
        sum=sum+i;
        if(sum%2==1)
            V(semid,1);
        else
            V(semid,2);
    }
}
void *subp2(){
    while(1)
    {
        P(semid,1);
        if(count<100){     0
            printf("Print thread1:%d\n",sum);
            count++;
        }
        else
            break;
        if(count==100){
            V(semid,2);
            break;
        }
        V(semid,0);
    }
}
void *subp3(){
    while(1)
    {
        P(semid,2);
        if(count<100){
            printf("Print thread2:%d\n",sum);
            count++;
        }
        else
            break;
        if(count==100){
            V(semid,1);
            break;
        }
        V(semid,0);
    }
}


