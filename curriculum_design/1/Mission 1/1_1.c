#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <errno.h>

#define SIZE 1024 //每次get字节数

int main(int argc, char* argv[]){
    //检查参数个数
    if(argc != 3){
        printf("Parameter num ERROR!");
        exit(0);
    }

    //变量定义
    int fs = open(argv[1], O_RDONLY);//源文件指针
    /*
    * @description: 用于打开文件
    * @param pathname: 指向欲打开的文件路径字符串 (const char *) 
    * @param flags: 所能使用的旗标 (int)
    * @param mode: 可选，Linux2.2以后特有的旗标，以避免一些系统安全问题。(mode_t)
    * @return: 若所有欲核查的权限都通过了检查则返回 0 值，表示成功，只要有一个权限被禁止则返回-1。
    * https://blog.csdn.net/weibo1230123/article/details/79036611
    */
    if(fs == -1){
        printf("Open %s ERROR: %s\n", argv[1], strerror(errno));
        exit(0);
    }
    int fd = open(argv[2], O_WRONLY|O_CREAT, 0666);//目标文件指针
    if(fd == -1){
        printf("Create %s ERROR: %s\n", argv[2], strerror(errno));
        exit(0);
    }
    char buf[SIZE];//缓冲区
    int len = 0;   //计数器，记录read读取了多少个字节

    //拷贝
    while ((len = read(fs, buf, SIZE)) > 0)
        write(fd, buf, len);
    
    printf("FINISHED!\n");
    close(fs);
    close(fd);
    return 0;
}