#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

int pipefd[2]; //无名管道,0只读，1只写
pid_t s1, s2;  //两个子进程的pid
int flag = 0;//父进程结束标志，置1说明要立即关闭父进程
void kill_both(int) //全部杀死,等待子进程全部杀死后，将flag置1
{
    signal(SIGINT, SIG_DFL);
    close(pipefd[1]);
    kill(s1, SIGUSR1);
    kill(s2, SIGUSR2);
    waitpid(s1, NULL, 0); //等待进程s1结束
    waitpid(s2, NULL, 0); //等待进程s2结束
    flag = 1;
}
void kill_s1(int) //杀死子进程1
{
    close(pipefd[0]);
    cout<<"s1 get "<<time<<"message."<<endl;
    cout << "Child Process 1 is Killed by Parent!" << endl;
    exit(1);
}
void kill_s2(int) //杀死子进程2
{
    close(pipefd[0]);
    cout<<"s2 get "<<time<<"message."<<endl;
    cout << "Child Process 2 is Killed by Parent!" << endl;
    exit(1);
}

int main()
{
    char buffer[128];          //缓冲区
    int time = 0;              //计时器
    signal(SIGINT, kill_both); //父进程控制进程终止
    pipe(pipefd);              //管道初始化
    s1 = fork();               //子进程s1创建
    if (s1 == 0)
    {                            //s1子进程运行
        close(pipefd[1]);
        signal(SIGINT, SIG_IGN); //子进程s1忽略ctrl+c
        signal(SIGUSR1, kill_s1);
        while (1)
        { //写入缓冲区,通过管道读取
            int read_bufs=read(pipefd[0],buffer,128);
            if( read_bufs <=0 ){
                cout<<"s1 get "<<time<<"message."<<endl;
                break;
            };
            cout <<"s1 Get: "<< buffer;
            time++;
            //sleep(1); //间隔一秒
        }
        cout << "time out:Child Process 1 is Killed by Parent!" << endl;
        close(pipefd[0]);
        return 0;
    }
    else{
        s2 = fork();               //子进程s2创建
        if (s2==0)
        {                            //s2子进程运行
            close(pipefd[1]);
            signal(SIGINT, SIG_IGN); //子进程s2忽略ctrl+c
            signal(SIGUSR2, kill_s2);
            while (1)
            {
                int read_bufs=read(pipefd[0],buffer,128);
                if( read_bufs <=0  ){
                    cout<<"s2 get "<<time<<"message."<<endl;
                    break;
                }
                cout <<"s2 Get: "<< buffer;
                time++;
                //sleep(1); //间隔一秒
            }
            cout << "time out:Child Process 2 is Killed by Parent!" << endl;
            close(pipefd[0]);
            return 0;
        }
        else
        { //父进程执行
            close(pipefd[0]);
            while (time < 10)
            {
                sprintf(buffer, "I send you %d times.\n", time+1);
                write(pipefd[1], buffer, 128);
                sleep(1); //间隔一秒
                time++;
                if (flag == 1)//父进程结束标志为1说明要立即关闭父进程
                { 
                    close(pipefd[0]);
                    close(pipefd[1]);
                    cout << "Parent Process is Killed!" << endl;
                    return 0;
                }
            }
            cout<<"time out!"<<endl;    
            //kill(s1, SIGUSR1);//计时器达到最大值，自动关闭子进程
            //kill(s2, SIGUSR2);
            
            close(pipefd[1]);
            waitpid(s1, NULL, 0); //等待进程s1结束
            waitpid(s2, NULL, 0); //等待进程s2结束
            cout << "Parent Process is Killed!" << endl;
            return 0;
        }
    }   
}
