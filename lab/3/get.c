#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <malloc.h>
#include <sys/stat.h>
#include <errno.h>

#define LENGTH 20                 //缓冲区大小
#define CIRCLE 10                 //环形缓冲区个数
#define SEMNUM 3                  //信号灯个数

union semun {
    int val;
    struct semid_ds*buf;
    unsigned short* arry;
};
typedef struct share{
    int pin; 
    int pout;
    int pend;
    char* circleBuffer[CIRCLE];
}share;

int semid;                        //信号灯
FILE* readFile;                   //读文件指针
FILE* writeFile;                  //写文件指针

int CreateShmId(int id);          //创建共享内存区
void P(int semid, int index);     //P操作函数
void V(int semid, int index);     //V操作函数


//write
int main(int argc,char* argv[]){
    //创建共享内存组
    share* shr = (share*)shmat(CreateShmId(419), NULL, 0);

    //创建信号灯
    int semid = semget(100, SEMNUM, IPC_CREAT | 0666);
    if (semid == -1){
        printf("Semget ERROR!\n");
        exit(1);
    }

    //信号灯赋初值
    union semun sem[SEMNUM];
    sem[0].val = 20;             //empty信号灯
    sem[1].val = 0;              //full信号灯
    sem[2].val = 1;              //mutex互斥信号灯
    if(semctl(semid,0,SETVAL,sem[0])==-1){
        printf("sem[0] initial ERROR!\n");
        exit(0);
    }
    if(semctl(semid,1,SETVAL,sem[1])==-1){
        printf("sem[1] initial ERROR!\n");
        exit(0);
    }
    if(semctl(semid,2,SETVAL,sem[2])==-1){
        printf("sem[2] initial ERROR!\n");
        exit(0);
    }

    //WritePid
    int wtfl = open("output",O_CREAT | O_WRONLY, 0664);
    char* Write = (char*)malloc(LENGTH*sizeof(char));
    while(shr->pend == -1 || shr->pend != shr->pout){
        P(semid, 1);
        write(wtfl,shr->circleBuffer[shr->pout],LENGTH);
        shr->pout++;
        shr->pout = (shr->pout) % CIRCLE;//循环队列
        V(semid, 0);
    }
}


int CreateShmId(int id){
    int shmid = shmget(id, LENGTH*sizeof(char), IPC_CREAT | 0666);
    /*
    * @description: 得到一个共享内存标识符或创建一个共享内存对象
    * @param key:绑定的键值 
    * @param size:内存的大小
    * @param IPC_CREAT | 0666
    * @return: 返回共享内存的标识符/-1
    */
    if(shmid < 0){
            printf("ERROR: call shmget failed, %s.\n", strerror(errno));
            exit(-1);
        }
	return shmid;
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