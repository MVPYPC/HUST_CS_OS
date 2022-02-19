#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
//#include <ctime>

void printdir(char* dir,int depth);

int main(int argc,char* argv[]){
    printdir(argv[1],0);
    return 0;
}

void prinfdir(char *dir, int depth){
    DIR *dp;                              //目录指针
    struct dirent *entry;                 //目录项结构指针
    struct stat buf;                      //保存了所有的文件状态信息
    //打开dir目录
    if((dp = opendir(dir)) == NULL){     
        printf("Opendir ERROR!\n");       //打印出错信息
        return;                           //返回
    }

    //将dir设置为当前目录
    if(chdir(dir) == -1){
        printf("Chdir ERROR!\n");
        return;
    }

    //读目录项
    printf("\nCurrent working directory: %s\n",getcwd(NULL,NULL));

    //以该目录项的名字为参数，调用lstat得到该目录项的相关信息
    while((entry=readdir(dp))!=NULL){
    	lstat(entry->d_name,&statbuf);   
        if(S_ISDIR(statbuf.st_mode)){
        	char modestr[11];
        	strcpy(modestr,"----------");
        	 if (S_ISDIR(statbuf.st_mode))modestr[0] =  'd' ;
	         if (S_ISCHR(statbuf.st_mode))modestr[0] =  'c' ;
	         if (S_ISBLK(statbuf.st_mode))modestr[0] =  'b' ;
	 
	         if (statbuf.st_mode&S_IRUSR)modestr[1] =  'r' ;
	         if (statbuf.st_mode&S_IWUSR)modestr[2] =  'w' ;
	         if (statbuf.st_mode&S_IXUSR)modestr[3] =  'x' ;
	 
	         if (statbuf.st_mode&S_IRGRP)modestr[4] =  'r' ;
	         if (statbuf.st_mode&S_IWGRP)modestr[5] =  'w' ;
	         if (statbuf.st_mode&S_IXGRP)modestr[6] =  'x' ;
	 
	         if (statbuf.st_mode&S_IROTH)modestr[7] =  'r' ;
	         if (statbuf.st_mode&S_IWOTH)modestr[8] =  'w' ;
	         if (statbuf.st_mode&S_IXOTH)modestr[9] =  'x' ; 

            //目录项的名字是“..” 或 “.”
            if(!strcmp(entry->d_name,".")||!strcmp(entry->d_name,".."))
               	 continue;                //跳过该目录项

            //打印目录项的深度、目录名等信息
            printf("%s  filename:%s  last modefied time:%.12s\n",modestr,entry->d_name,4+ctime(&statbuf.st_atime));
            //递归调用printdir,打印子目录的信息,其中的depth+4;
            printdir(entry->d_name,depth+4);
        } 
	 	else{
	 		char modestr[11];
        	strcpy(modestr,"----------");
        	 if (S_ISDIR(statbuf.st_mode))modestr[0] =  'd' ;
	         if (S_ISCHR(statbuf.st_mode))modestr[0] =  'c' ;
	         if (S_ISBLK(statbuf.st_mode))modestr[0] =  'b' ;
	 
	         if (statbuf.st_mode&S_IRUSR)modestr[1] =  'r' ;
	         if (statbuf.st_mode&S_IWUSR)modestr[2] =  'w' ;
	         if (statbuf.st_mode&S_IXUSR)modestr[3] =  'x' ;
	 
	         if (statbuf.st_mode&S_IRGRP)modestr[4] =  'r' ;
	         if (statbuf.st_mode&S_IWGRP)modestr[5] =  'w' ;
	         if (statbuf.st_mode&S_IXGRP)modestr[6] =  'x' ;
	 
	         if (statbuf.st_mode&S_IROTH)modestr[7] =  'r' ;
	         if (statbuf.st_mode&S_IWOTH)modestr[8] =  'w' ;
	         if (statbuf.st_mode&S_IXOTH)modestr[9] =  'x' ; 
	 		printf("%s  filename:%s  last modefied time:%.12s\n",modestr,entry->d_name,4+ctime(&statbuf.st_atime));
        }
    }
    char a[100];
    strcpy(a,getcwd(NULL,NULL));
    int k=0;
    for(int i=0;i<strlen(a);i++){
    	if(a[i]=='/'){
    		k=i;
    	}
    }
    a[k]=0;
    if(chdir(a)==-1){
    	printf("chdir error!\n");
    	return;
    }   
    
    //返回父目录
    chdir("..");

    //关闭目录项	
	closedir(dp);	
	return;
}