/*
3. Considere um arquivo de dados do tipo texto com o seguinte conteúdo:
3
ZE SA
8.5
10.0
ANTONIO SANTOS
7.5
8.5
SEBASTIAO OLIVEIRA
5.0
6.0
O arquivo acima é um exemplo. Você deve acrescentar mais alguns alunos. A primeira linha contém o número total de alunos no arquivo. As linhas seguintes contém os seguintes dados:
• nome do aluno (máximo 50 caracteres);
• nota da primeira prova;
• nota da segunda prova.

Escreva um programa que imprima os nomes de todos os alunos que têm a média aritmética das duas notas menor que 7.0.

Dica: para ler strings com espaço no scanf ou fscanf, utilize o código %[A-Z ] (caracteres maiúsculos de A a Z e espaço em branco).
*/
#include <stdio.h>
#include <stdlib.h>

int main(void){
  FILE *fp = fopen("arquivo.txt", "r");
  
  if (fp == NULL) {
    printf("Erro na abertura do arquivo!");
    return 0;  //aborta o programa
  }

  int quantidadeAlunos = 0;

  fscanf(fp, "%d\n", &quantidadeAlunos);

  char nomes[50][quantidadeAlunos];
  float nota1[quantidadeAlunos];
  float nota2[quantidadeAlunos];
  float media;

  printf("Lista de Alunos com notas menores que 7:\n");

  for(int i=0; i< quantidadeAlunos; i++){
    fscanf(fp, "%[A-Z ]\n", nomes[i]);
    fscanf(fp, "%f \n", &nota1[i]); 
    fscanf(fp, "%f\n", &nota2[i]);

    media = (nota1[i] + nota2[i])/2;

    if (media < 7){
      printf("%s\n", nomes[i]);
    }
    
  }

  fclose(fp);

 return 1; 
}