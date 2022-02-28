#include <linux/module.h> 
#include <linux/version.h> 
#include <linux/types.h> 
#include <linux/fs.h> 
#include <linux/mm.h> 
#include <linux/errno.h> 
#include <asm/segment.h> 

long int major = 0;//用于接收主设备号

//read
static ssize_t dev_read(struct file *flip,char *buf,size_t count, loff_t*f_pos){ 
	int left;   
	for(left = count ; left > 0 ; left--)   {   
        put_user(6,buf);   
        buf++;   
    }   
	return count; 
} 

//write
static ssize_t dev_write(struct file *flip,const char *file,size_t count, loff_t*f_pos) { return count; } 
 
//open
static int dev_open(struct inode *inode,struct file *file ) {return 0; } 

//release
static int dev_release(struct inode *inode,struct file *file ){}

//结构顺序
struct file_operations fops={
	.read = dev_read,
	.write=dev_write,
	.open=dev_open,
	.release=dev_release
};

//内核模块初始化
static int init_mymodule(void) { 
	int result;
	result = register_chrdev(0, "chardev", &fops); 
    /**********************************
     * @param major: 主设备号,major如果为0的话，系统会给我们随机分配主设备号
     * @param name : 设备的名字
     * @param fops : 该设备对应的一些列操作函数
     * @return : 成功返回主设备号
     * ****************************/
	if (result < 0) { 
		printk(KERN_INFO "ERROR: Can't get major number!\n"); 
		return result;
	} 
	if (major == 0) 
        major = result; /* dynamic */ 
	return 0; 
}


static void cleanup_mymodule(void) { unregister_chrdev(major,"alex"); } 

MODULE_LICENSE("GPL");
module_init(init_mymodule);
module_exit(cleanup_mymodule);