#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PUTENV_SUCCESS 0
#define ERROR -1

extern char** environ;

int execvpe(char* file, char* argv[], char* envp[]) {
    if(file == NULL) {
        perror("NULL pointer to file");
        return EXIT_FAILURE;
    }
    char** savedEnviron = environ;

    if (execvp(file, argv) == ERROR){
        environ = savedEnviron;
        perror("exec error");
        return EXIT_FAILURE;
    }
}

int main(int argc, char* argv[], char* envp[]) {

    //если общее количество аргументов меньше 2
    if(argc < 2) {
        printf("Need two or more args \n");
        return EXIT_FAILURE;
    }

    if(envp == NULL) {
        perror("Environment has not been set");
    }

    /*Функция putenv принимает строку в формате name=value и помещает ее в список переменных окружения.*/
    if(putenv("TEST=lab11") != PUTENV_SUCCESS){

        perror("error in putenv");

        return EXIT_FAILURE;

    }

    execvpe(argv[1], &argv[1], envp);

    perror("exec error");

    return EXIT_FAILURE;
}