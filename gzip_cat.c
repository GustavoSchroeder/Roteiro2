#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
const int BUFSIZE = 1000;

void main(char* arquivo){ //arquivo contem o caminho do arquivo informado no FIFO
  scanf("%c",&arquivo);
  //arquivo = "/tmp/graubSISOP.txt.gz"; //usado apenas para um teste
  int pfd[2]; //vetor aonde o pipe serÃ¡ utilizado
  //variÃ¡veis que serÃ£o utilizadas caso nÃ£o exista a extensão.gz
  int fim = strlen(arquivo); //strlen = retorna tamanho da string
  char* extensao = &arquivo[fim-3];
  int compara = strcmp(extensao, ".gz");
  char* copia;
  char buffer[BUFSIZE]; //inicialmente igual do p-- array de bytes
  char* p = buffer; //inicialmente igual do buffer
  int n = 1;
  int file;
  
  if(compara != 0){ //caso o arquivo nÃ£o seja .gz
    file = open(arquivo,O_RDONLY);
    while(n >= 0){
      n = read(file,//descritor do arquivo
      p,//endereÃƒÂ§o do buffer
      BUFSIZE);// tamanho maximo do buffer)
      write(1, p, n);
    break;
  }
 }
 else if(compara == 0){
  if (pipe(pfd)<0) { //abertura do pipe no vetor
    perror("pipe()");
    exit(EXIT_FAILURE);
    }
  else{ //pipe aberto
    switch(fork()){ //Inicio do switch do fork
    case -1: //problema com fork
    perror("Erro no fork");
    exit(EXIT_FAILURE);
    case 0: //fork executado corretamente
    close(1); //fecha o descritor 0, que equivale a leitura
    dup(pfd[1]);
    close(pfd[1]);
    close(pfd[0]);
    execlp("gzip", "gzip","-c","-d", arquivo,NULL); //parametro C do gzip exibe na tela, parametro D descompacta
    perror("exec falhou"); //saida do gzip serÃ¡ gravada no pipe
    exit(-1);
    break;
    default:
    close(0);
    dup(pfd[0]);
    close(pfd[0]);
    close(pfd[1]);
    execlp("cat","cat",0); //cat vai ler o que esta salvo no descritor 0 do pipe
    perror("exec falhou");
    break;
     } //final do switch do fork
    }
  }
}
