# Mission 2

## 文件结构

总共包含4个文件（文件夹），文件结构如下

```java
+--+ Mission 2 文件夹
      +--+ exe1 文件夹

         |    +---  build-exe1-Desktop-Debug 文件夹     //编译后的生成的文件夹,包含可执行文件exe1

         |    +---  exe1 文件夹                         //项目文件,包含代码文件
    
      +--+ exe2 文件夹

         |    +---  build-exe2-Desktop-Debug 文件夹    //编译后的生成的文件夹,包含可执行文件exe2

         |    +---  exe2 文件夹                        //项目文件,包含代码文件
      +--+ exe3 文件夹

         |    +---  build-exe3-Desktop-Debug 文件夹    //编译后的生成的文件夹,包含可执行文件exe3

         |    +---  exe1 文件夹                        //项目文件,包含代码文件
      +--+ Mission_2_show 文件夹

         |    +---  1_2.c                             //1_2测试代码文件

         |    +---  1_2                               //1_2测试程序可执行文件
         
         |    +---  exe1                              //调用外部程序exe1
    
         |    +---  exe2                              //调用外部程序exe2
    
         |    +---  exe3                              //调用外部程序exe3
      +--+ QT_learning_notes.md                       //QT安装以及学习笔记
      +--+ README.md                                  //说明文档  
```

## 使用方法

实测无法直接运行Mission_2_show中的1_2,需要下载相应的库,也可按`QT_learning_notes.md  `中的教程下载Qt Creator,即可运行.

## 运行效果

通过1_2创建三个并发进程,分别调用三个exe,显示lcdnumber形式的时间.