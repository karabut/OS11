#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERROR -1

extern char **environ;

int execvpe(char* file, char* const argv[], char* envp[])
{
    //сохраняем старый адрес массива указателей
    char **prevEnv = environ;
    //меняем на переданный нами адрес массива указателей
    environ = envp;
    //вызываем функцию execvp
    if(execvp(file, argv) == ERROR){
        perror("error in execvp");
    }
    //возвращаем старый адрес массива указателей
    environ = prevEnv;
    return ERROR;
}

int main(int argc, char *argv[])
{
    char *newArgv[2] = {"prog.out", (char *) 0};
    char *newEnvp[4] = {"RANDOM_VAR1=operating", "RANDOM_VAR2=system", "PATH=/home/students/19200/e.karabut2/lab11", (char *) 0};
    execvpe(newArgv[0], newArgv, newEnvp);

    EXIT_FAILURE;
}
