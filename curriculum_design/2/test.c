int main(int argc, char const *argv[])
{
    long int callreturn;

    //判断参数是否完整
    if (argc != 3)
    {
        printf("输入参数不正确！\n");
        return -1;
    }

    printf("调用sys_mycopy\n");
    callreturn = syscall(333, argv[1] , argv[2]);
    printf("callreturn = %ld\n",callreturn);
    if (callreturn == -1)
        printf("文件打开失败\n");
    if (callreturn == -2)
        printf("文件写入失败 \n");
    else
    {
        printf("%s 成功！\n", argv[2]);
    }

    return 0;
}
