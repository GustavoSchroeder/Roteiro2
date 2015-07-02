<b># Roteiro2</b>

Exercício Desenvolvido na matérias de Sistema Operacionais na Unisinos. 

<i>Descrição do Problema</i>

Desenvolver um programa que recebe eternamente nomes de arquivos, separados por linhas, através de um FIFO, o mesmo e fornecido por parâmetro completa via linha de comando.
Para cada arquivo recebido o processo irá utilizar criar um processo gzip_cat (feito na etapa 1), para realizar o processamento do arquivo recebido via linha de comando.
Os dados não poderão se misturar na tela, uma lógica deverá ser implementada que assegure que um processo irá aguardar outro exibir seu relatório, para assim exibir seu relatório. 
  
  <i>Projeto de Solução</i>
  
O FIFO é um arquivo especial do tipo “First In First Out” (primeiro a chegar primeiro a sair), uma vez que o PIPE é aberto funciona como um PIPE normal.
O FIFO permite criar canais de comunicação entre processos não relacionados. São criados pelo comando mkfifo (const char *pathname,mode_t mode). Este comando cria um arquivo especial FIFO, onde o pathname é o caminho, absoluto ou relativo, para aonde se encontra o arquivo FIFO no diretório de arquivos, e mode são as permissões que serão
atribuídas ao FIFO.
Retorna 0 em caso de sucesso e -1 em caso de erro.
O FIFO é aberto com a função open () como um arquivo convencional, owrite escreve informações sempre no final do FIFO, o read lê bytes do início do arquivo, e a função close somente fecha o FIFO.
Se tentarmos escrever em um FIFO que não está aberto para leitura em nenhum processo será gerado o sinal SIGPIPE, e o tratamento padrão para este sinal é matar o processo.
Quando um escritor de arquivo fecha o canal, um final de arquivo é gerado para o processo que está lendo o FIFO.
O open () sobre um FIFO é bloqueado até que haja pelo menos um leitor e um escritor.
