#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

typedef struct 
{
    int ano;
    char modelo[100];
} Veiculo;

int findMax(Veiculo v[], int n)
{
    int max = v[0].ano;

    for (int i = 1; i < n; i++){
      if (v[i].ano > max) {
        max = v[i].ano;
      }
    }
        
    return max;
}
 
void countingSort(Veiculo v[], int n, int pos)
{
    Veiculo aux[n]; 
    int i, count[10] = { 0 };
 
    for (i = 0; i < n; i++)
        count[(v[i].ano / pos) % 10]++;
 
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    for (i = n - 1; i >= 0; i--) {
        aux[count[(v[i].ano / pos) % 10] - 1].ano = v[i].ano;
        strcpy(aux[count[(v[i].ano / pos) % 10] - 1].modelo, v[i].modelo);
        count[(v[i].ano / pos) % 10]--;
    }
 
    for (i = 0; i < n; i++) {
        v[i].ano = aux[i].ano;
        strcpy(v[i].modelo, aux[i].modelo);
    }
}

void radixSort(Veiculo v[], int n)
{
    int max = findMax(v, n);

    for (int pos = 1; max / pos > 0; pos *= 10)
        countingSort(v, n, pos);
}

int main(void) {

  Veiculo v[15];

  int anos[15] = {2010, 2000, 2000, 2001, 2002, 2002, 2003, 2010, 1999, 1985, 1999, 1996, 2005, 2021, 2022};
  char modelos[15][100] = {"Gol", "Saveiro", "Fiorino", "Vectra", "Ranger", "Golf", "Civic", "HB20", "Palio", "Focus", "147", "Pegeout", "Strada", "Ford Ká", "Hilux"};

  for (int i =0; i<15; i++){
    strcpy(v[i].modelo, modelos[i]);
    v[i].ano = anos[i];
  }

  radixSort(v, 15);

  printf("Lista de veículos ordenados \n");
  printf("ano - modelo \n");

  for (int i =0; i<15; i++){
    printf("%d - %s \n", v[i].ano, v[i].modelo);
  }

  return 0;
}