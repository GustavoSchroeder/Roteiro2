#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


const int BUFSIZE = 200;

int main(int argc, char* argv[])
{
    char path;
    char buffer[BUFSIZE]; //inicialmente igual do p-- array de bytes
    char* p = buffer; //inicialmente igual do buffer
    int pfd[2];
    int n;
    n = 1;
    int file;
    pid_t pid;

    file = open(argv[0], O_RDONLY);
    if (file == -1){
    perror("Falha no open()");
    }

    if(argv[0] == '.gz'){

        if (pipe(pfd)<0) {
            perror("pipe()");
            exit(EXIT_FAILURE);
        }

        dup2(file, 0);

        if(pid=fork()<0){
            perror("Erro no fork");
            exit(EXIT_FAILURE);
        }
        else if(pid==0){ //processo filho
            if(execl("/usr/bin/gzip", "gzip -cd", NULL)<0){
            perror("exec falhou");
            exit(-1);
            }
        else{
        write(1, p, n);
    }

    int i;
    for(i=0; i<n; i++){
        printf("%c", p[i]);
            }
        }
    }
    else{
    while(n >= 0){

            n = read(file,//descrito do arquivo
                p,//endereço do buffer
                BUFSIZE);// tamanho maximo do buffer)
            write(1, p, n);
        }
        }

    //int i;
    //for(i=0; i<n; i++){
    //    printf("%c", p[i]);
    //}
}
