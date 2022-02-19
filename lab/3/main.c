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

#define LENGTH 20                //缓冲区大小
#define CIRCLE 8                  //环形缓冲区个数
#define SEMNUM 3                  //信号灯个数

pid_t ReadPid;                    //读进程
pid_t WritePid;                   //写进程
int circleBuffer;                 //环形缓冲
int num;                          //用来记录Readpid进行操作次数,以便使Writepid能够正确终止
int semid;                        //信号灯
FILE* readFile;                   //读文件指针
FILE* writeFile;                  //写文件指针

union semun {
    int val;
    struct semid_ds*buf;
    unsigned short* arry;
};
typedef struct share{
    int* pin; 
    int* pout;
    int* pend;
    char* circleBuffer[CIRCLE];
}share;


int CreateShmId(int id);          //创建共享内存区
void P(int semid, int index);     //P操作函数
void V(int semid, int index);     //V操作函数
int delSem();                     //删除信号灯函数


int main(int argc,char* argv[]){
    //创建两个进程readbuf、writebuf
    if((ReadPid = fork()) < 0){
        printf("ReadPid create ERROR!\n");
        exit(0);
    }
    else if(ReadPid == 0){
        printf("Readbuf created.\n");
        execl("./readbuf","readbuf",NULL);
        exit(0);
    }
    if((WritePid = fork()) < 0){
        printf("WritePid create ERROR!\n");
        exit(0);
    }
    else if(WritePid == 0){
        printf("Writebuf created.\n");
        execl("./writebuf","writebuf",NULL);
        exit(0);
    }

    //等待两个进城运行结束    
    waitpid(ReadPid, NULL, 0);
    waitpid(WritePid, NULL, 0);
    printf("Finish copying!\n");

    //删除信号灯    
    if(delSem() == -1){
        printf("Release Sem ERROR!\n");
        return 0;
    }

    //删除共享内存组    
    if (shmctl(shr, IPC_RMID, 0) < 0){ 
        printf("Release circleBuffer ERROR!\n");
        return 0;
    }
    
    //关闭文件指针
    fclose(readFile);
    fclose(writeFile);
    return 0;
}


int CreateShmId(int id){
    int shmid = shmget(id, LENGTH, IPC_CREAT | 0666);
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


int delSem(){
    union semun sem_union;
    if (semctl(semid, 1, IPC_RMID, sem_union) == -1) {
        printf("delSemvalue failed\n");
        return -1;
    }
    else 
        return 1;
}
