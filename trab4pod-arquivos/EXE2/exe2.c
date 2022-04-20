//2. Um arquivo do tipo texto, chamado ‘‘numeros.txt’’, contém uma lista de 20 números 
//inteiros separados por vírgula. Escreva um programa que leia estes números, os coloque
// em ordem crescente usando o algoritmo de ordenação interna de sua preferência e depois 
//grave os valores ordenados em outro arquivo chamado ‘‘numeros_ord.txt’’, um valor por linha.

#include <stdio.h>
#include <stdlib.h>

int comparador(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

int main(void) {
  FILE *fp = fopen("numeros.txt", "r");
  
  if (fp == NULL) {
    printf("Erro na abertura do arquivo!");
    return 0;  //aborta o programa
  }
  
  int numeros[20];

  for (int i =0; i<20; i++){
    int j = fscanf(fp, "%d,", &numeros[i]);
  }

  fclose(fp);

  qsort(numeros, 20, sizeof(int), comparador);

  fp = fopen("numeros_ord.txt", "w");

  for(int i =0; i< 20; i++){
    int j = fprintf(fp, "%d\n", numeros[i]);
  }

  fclose(fp);
  
  return 1;
}