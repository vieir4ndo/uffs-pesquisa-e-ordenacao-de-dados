/*1. Escreva um programa que abra um arquivo contendo um texto qualquer 
e conte o número de caracteres de cada tipo (espaços em branco, quebras 
de linha e caracteres em geral) presentes no mesmo. Exiba as 3 contagens na tela.*/

#include <stdio.h>

int main(void) {
  FILE *fp = fopen("exe1.txt", "r");
  
  if (fp == NULL) {
    printf("Erro na abertura do arquivo!");
    return 0;  //aborta o programa
  }
  
  int espacos = 0, quebras = 0, caracteres = 0;

  char c;

   while(!feof(fp)) {
      c = fgetc(fp);
      if (c == EOF){
        break;
      }
       if (c == ' '){
         espacos++;
         continue;
       }
       if (c == '\n'){
         quebras++;
         continue;
       }
       caracteres++;
  }

  printf("Espaços em branco: %d \n", espacos);
  printf("Quebras de linha: %d \n", quebras);
  printf("Caracteres em geral: %d \n", caracteres);

  fclose(fp);

  return 1;
}