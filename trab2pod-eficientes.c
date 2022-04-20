#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void printArray(int A[], int n) {
  printf("\n");
  for (int i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");
}

void setArray(int dst[], int src[], int n) {
  for (int i = 0; i < n; i++) {
    dst[i] = src[i];
  }
}

void generateRandArray(int randArray[], int n) {
  for (int i = 0; i < n; i++) {
    randArray[i] = rand() % 100;
  }
}

void generateRandAscArray(int randArray[], int n) {
  for (int i = 0; i < n; i++)
    randArray[i] = i;
}

void generateRandDscArray(int randArray[], int n) {
  for (int i = 0; i < n; i++) {
    randArray[i] = n - i;
  }
}

void swapValue(int * src, int * dst) {
  int temp = * src;
  * src = * dst;
  * dst = temp;
}

void intercala(int A[], int start, int middle, int end) {
  int aux[end - start + 1];
  int i = start;
  int j = middle + 1;
  int k = 0;

  while (i <= middle && j <= end) {
    if (A[i] <= A[j]) {
      aux[k] = A[i];
      i++;
    } else {
      aux[k] = A[j];
      j++;
    }
    k++;
  }

  while (i <= middle) {
    aux[k] = A[i];
    k++;
    i++;
  }

  while (j <= end) {
    aux[k] = A[j];
    k++;
    j++;
  }

  for (int k = start; k <= end; k++) {
    A[k] = aux[k - start];
  }
}

void mergeSort(int A[], int start, int end) {
  if (start < end) {
    int middle = start + (end - start) / 2;

    mergeSort(A, start, middle);
    mergeSort(A, middle + 1, end);

    intercala(A, start, middle, end);
  }
}

void callMergeSort(int A[], int start, int end) {
  clock_t startTime, endTime;
  startTime = clock();

  mergeSort(A, start, end);

  endTime = clock();
  double difTempo = ((double) endTime -
    startTime) / CLOCKS_PER_SEC;
  printf("Tempo MergeSort: %lf (ms)\n", difTempo * 1000);
}

int particiona(int A[], int start, int end) {
  int posPivo = end;
  int k = start;

  for (int i = start; i < end; i++) {
    if (A[i] <= A[posPivo]) {
      swapValue( & A[i], & A[k]);
      k++;
    }
  }

  if (A[k] > A[posPivo]) {
    swapValue( & A[k], & A[posPivo]);
    posPivo = k;
  }
  return posPivo;
}

void quickSort(int A[], int start, int end) {
  if (start < end) {
    int posPivo = particiona(A, start, end);

    quickSort(A, start, posPivo - 1);
    quickSort(A, posPivo + 1, end);
  }
}

void callQuickSort(int A[], int start, int end) {
  clock_t startTime, endTime;
  startTime = clock();

  quickSort(A, start, end);

  endTime = clock();
  double difTempo = ((double) endTime - startTime) / CLOCKS_PER_SEC;
  printf("Tempo QuickSort: %lf (ms)\n", difTempo * 1000);
}

void criaHeap(int A[], int i, int n) {
  int maior = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && A[left] > A[maior]) {
    maior = left;
  }

  if (right < n && A[right] > A[maior]) {
    maior = right;
  }

  if (maior != i) {
    swapValue( & A[i], & A[maior]);
    criaHeap(A, maior, n);
  }
}

void heapSort(int A[], int n) {
  clock_t startTime, endTime;
  startTime = clock();

  for (int k = n / 2 - 1; k >= 0; k--)
    criaHeap(A, k, n);

  for (int k = n - 1; k > 0; k--) {
    swapValue( & A[0], & A[k]);
    criaHeap(A, 0, k);
  }

  endTime = clock();
  double difTempo = ((double) endTime - startTime) / CLOCKS_PER_SEC;
  printf("Tempo HeapSort: %lf (ms)\n", difTempo * 1000);
}

int main(void) {

  int printMerge = false, printQuick = false, printHeap = false, printAux = false;

  int op = 2;

  while (op != 1 && op == 2) {
    int n, type;

    printf("Informe o tamanho do vetor\n");
    scanf("%d", & n);

    if (n < 0)
      continue;

    printf("Deseja um vetor: 1-Rand, 2-Asc, 3-Dsc\n");
    scanf("%d", & type);

    int aux[n], A[n], B[n], C[n];

    switch (type) {
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

    if (printAux)
      printArray(aux, n);
    printf("\n");

    setArray(A, aux, n);
    setArray(B, aux, n);
    setArray(C, aux, n);

    callMergeSort(A, 0, n - 1);
    if (printMerge)
      printArray(A, n);

    callQuickSort(B, 0, n - 1);
    if (printQuick)
      printArray(B, n);

    heapSort(C, n);
    if (printHeap)
      printArray(C, n);

    printf("\n");

    printf("Deseja sair: 1-Sim, 2-Não\n");
    scanf("%d", & type);
    system("clear");
  }
  return 0;
}