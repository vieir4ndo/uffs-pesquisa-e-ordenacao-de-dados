#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void imprimeArray(int A[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", A[i]);
  }
  printf("\n");
}

void setArray(int dst[], int src[], int n)
{
  for (int i = 0; i < n; i++)
  {
    dst[i] = src[i];
  }
}

void generateRandArray(int randArray[], int n)
{
  for (int i = 0; i < n; i++)
  {
    randArray[i] = rand() % 100;
  }
}

void generateRandAscArray(int randArray[], int n)
{
  for (int i = 0; i < n; i++)
    randArray[i] = i;
}

void generateRandDscArray(int randArray[], int n)
{
  for (int i = 0; i < n; i++)
  {
    randArray[i] = n - i;
  }
}

void swapValue(int *src, int *dst)
{
  int temp = *src;
  *src = *dst;
  *dst = temp;
}

long bubbleSort(int A[], int n)
{
  clock_t start, end;
  start = clock();

  int i, j;
  long comp = 0;
  bool flag;
  for (i = 0; i < n - 1; i++)
  {
    flag = false;
    for (j = 0; j < n - i - 1; j++)
    {
      if (A[j] > A[j + 1])
      {
        swapValue(&A[j], &A[j + 1]);
        flag = true;
      }
      comp++;
    }
    if (flag == false)
      break;
  }
  end = clock();
  double difTempo = ((double)end - start) / CLOCKS_PER_SEC;
  printf("Tempo BubbleSort: %lf (ms)\n", difTempo * 1000);
  return comp;
}

long selectionSort(int A[], int n)
{
  clock_t start, end;
  start = clock();
  int i, j, min_idx;
  long comp = 0;

  for (i = 0; i < n - 1; i++)
  {
    min_idx = i;
    for (j = i + 1; j < n; j++)
    {
      if (A[j] < A[min_idx])
        min_idx = j;
      comp++;
    }
    swapValue(&A[min_idx], &A[i]);
  }
  end = clock();
  double difTempo = ((double)end - start) / CLOCKS_PER_SEC;
  printf("Tempo SelectionSort: %lf (ms)\n", difTempo * 1000);
  return comp;
}

long insertionSort(int A[], int n)
{
  clock_t start, end;
  start = clock();
  int i, j, p;
  long comp = 0;

  for (i = 1; i < n; i++)
  {
    p = A[i];
    for (j = i; j > 0; j--)
    {
      comp++;
      if (p < A[j - 1])
        A[j] = A[j - 1];
      else
        break;
    }
    A[j] = p;
  }

  end = clock();
  double difTempo = ((double)end - start) / CLOCKS_PER_SEC;
  printf("Tempo InsertionSort: %lf (ms)\n", difTempo * 1000);
  return comp;
}

int main(void)
{

  int op = 2;

  while (op != 1 && op == 2)
  {
    int n, type;

    printf("Informe o tamanho do vetor\n");
    scanf("%d", &n);

    if (n < 0)
      continue;

    printf("Deseja um vetor: 1-Rand, 2-Asc, 3-Dsc\n");
    scanf("%d", &type);

    int aux[n], A[n], B[n], C[n];

    switch (type)
    {
    case 1:
      generateRandArray(aux, n);
      break;
    case 2:
      generateRandAscArray(aux, n);
      break;
    case 3:
      generateRandDscArray(aux, n);
      break;
    }

    setArray(A, aux, n);
    setArray(B, aux, n);
    setArray(C, aux, n);

    long comp = bubbleSort(A, n);
    printf("Comparações BubbleSort: %ld\n", comp);
    printf("\n");
    comp = selectionSort(B, n);
    printf("Comparações SelectionSort: %ld\n", comp);
    printf("\n");
    comp = insertionSort(C, n);
    printf("Comparações InsertionSort: %ld\n", comp);
    printf("\n");

    printf("Deseja sair: 1-Sim, 2-Não\n");
    scanf("%d", &op);
    system("clear");
  }
  return 0;
}