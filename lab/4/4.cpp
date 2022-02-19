#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>
using namespace std;

void printdir(char* dir,int depth);

int main(int argc,char*argv[])
{
    if(argc!=2)
    {
        printf("Please enter the correct format\n");
    }
    else{
        printdir(argv[1],0);
    }
}

void printdir(char* dir,int depth)
{
    DIR *dp;//目录指针
    struct dirent*entry;//目录项结构指针
    struct stat statbuf;//保存了所有的文件状态信息
    if((dp=opendir(dir))==NULL)
    {
        printf("DEPTH:%d\n",depth);
        printf("OPENDIR ERROR!\n");
        return;
    }
    if(chdir(dir)==-1)//改变目录,与用户通过cd命令改变目录一样，
    			//程序也可以通chdir来改变目录
    {
        printf("DEPTH:%d\n",depth);
        printf("CHDIR ERROR!\n");
    }
    while((entry=readdir(dp))!=NULL)
    {
        lstat(entry->d_name,&statbuf);//以该目录项的名字为参数，得到该目录项的相关信息
        if(S_ISDIR(statbuf.st_mode)){//是目录
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
            
            cout<<"Depth: "<<depth<<"   DirName: "<<entry->d_name<<"    SIZE: "<<statbuf.st_size
            <<"    ATIME: "<<strtok(ctime(&statbuf.st_atime)+4, "\n")<<endl;
            printdir( (entry->d_name), depth+4);
        }
        else{
            cout<<"Depth: "<<depth<<"   FileName: "<<entry->d_name<<"cSIZE: "<<statbuf.st_size
            <<"    ATIME: "<<strtok(ctime(&statbuf.st_atime)+4, "\n")<<endl;
        }
    }
    chdir("..");	
	closedir(dp);	
	return;
}