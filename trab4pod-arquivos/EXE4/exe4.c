/*
4. Escreva um programa que leia o mesmo arquivo de entrada do exercício anterior e grave os dados em um outro arquivo do tipo binário. O valor que indica o número de alunos (primeira linha do arquivo) não deve ser gravado no arquivo binário. Nesta questão, o programa deve obrigatoriamente usar um vetor de estruturas do seguinte tipo:

Após gravar os dados, o programa deve realizar a leitura dos dados gravados e exibir na tela a lista de nomes de todos os alunos.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct aluno {
    char nome[51];
    float n1, n2;
} Aluno;

int main(void){
  FILE *fp = fopen("arquivo.txt", "r");
  
  if (fp == NULL) {
    printf("Erro na abertura do arquivo!");
    return 0;  //aborta o programa
  }

  int quantidadeAlunos = 0;

  fscanf(fp, "%d\n", &quantidadeAlunos);

  Aluno alunos[quantidadeAlunos];

  for(int i=0; i< quantidadeAlunos; i++){
    fscanf(fp, "%[A-Z ]\n", alunos[i].nome);
    fscanf(fp, "%f \n", &alunos[i].n1); 
    fscanf(fp, "%f\n", &alunos[i].n2);
  }

  fclose(fp);

  fp = fopen("arquivoBinario.bin", "wb");

  fwrite(alunos, sizeof(Aluno), quantidadeAlunos, fp);

  fclose(fp);

  fp = fopen("arquivoBinario.bin", "rb");

  Aluno alunosBinario[quantidadeAlunos];

  fread(alunosBinario, sizeof(Aluno), quantidadeAlunos, fp);

  printf("LISTA DE ALUNOS\n");
  
  for(int i=0; i< quantidadeAlunos; i++){
    printf("Nome: %s\n", alunosBinario[i].nome);
    printf("Nota1: %.2f \n", alunosBinario[i].n1); 
    printf("Nota2: %.2f\n", alunosBinario[i].n2);
  }

  fclose(fp);
 return 1; 
}