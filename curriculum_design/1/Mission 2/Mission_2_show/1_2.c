#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t p1,p2;
    if ((p1 = fork()) == 0)
        execv("./exe1",NULL);
    else 
        if ((p2 = fork()) == 0)
            execv("./exe2",NULL);
        else
            execv("./exe3",NULL);
}