#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <asm/uaccess.h>

asmlinkage sys_mySysCall(const char* file1, const char* file2)
{
    const int SIZE = 1024;
    char buf[SIZE];
    mm_segment_t old_fs = get_fs();//保护现场
    set_fs(KERNEL_DS);
    //设置文件句柄
    int fp_read = sys_open(file1, O_RDONLY, 0);
    if(fp_read == -1){
        printk("open file1 ERROR\n");
        return -1;
    }
    int fp_write = sys_write(file2, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    if(fp_write == -1){
        printk("open file2 ERROR\n");
        return -1;
    }
    //文件打开无误,开始读/写
    do{
        int num = sys_read(fp_read, buf, SIZE);
        if(num != 0)
            sys_write(fp_write, buf, num);
        else
            break;
    }while(true);
    //文件读写完毕,还原现场
    set_fs(old_fs);
    return 0;
}

