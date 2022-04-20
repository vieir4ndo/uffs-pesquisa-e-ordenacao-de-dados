/*
5. Considere um arquivo binário formado por uma sequência de números float seguidos de um número inteiro.

O primeiro número float da lista aparece no final do arquivo. O número inteiro que vem depois do float indica qual é o próximo elemento da lista (considerando posições iniciando em zero). O valor inteiro -1 indica que não há mais números a serem lidos.

Escreva um programa que leia e mostre os números float, na ordem que está determinada no arquivo. Use o arquivo fornecido abaixo para testar seu programa.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct minhaStruct {
    float f;
    int i;
} MinhaStruct;

int main(void){

  FILE *fp = fopen("num.bin", "rb");
  
  if (fp == NULL) {
    printf("Erro na abertura do arquivo!");
    return 0;  //aborta o programa
  }

  MinhaStruct dados[8];

  fread(dados, sizeof(MinhaStruct), 8, fp);

  float lista[8];

  int proximaPosicao = 7;
  int j =0;

  do {
    lista[j] = dados[proximaPosicao].f;
    proximaPosicao = dados[proximaPosicao].i;

    printf("%.2f\n", j, lista[j]);
    j++;
  } while(proximaPosicao != -1);

  fclose(fp);

  return 1;
  
}