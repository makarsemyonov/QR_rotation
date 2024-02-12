#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "algorithm.h"

#define FN "matrix.txt"

int main(void) {
  int N;
  int Result;
  int inputMode;
  double *A = NULL;
  double *X = NULL;
  FILE *file = NULL;
  clock_t t;
  printf("Выберите режим заполнения : 1 - из файла %s.", FN);
  printf(" 2 - из формулы.\n");
  scanf("%d", &inputMode);

  switch (inputMode) {
  case 1:
    file = fopen(FN, "r");

    if (!file) {
      printf("Ошибка при открытии файла\n");

      return -1;
    }

    if (fscanf(file, "%d", &N) != 1) {
      printf("Ошибка чтения файла!\n");

      fclose(file);

      return -2;
    }

    break;
  case 2:
    printf("Введите N: ");
    scanf("%d", &N);

    break;
  default:
    printf("Неправильный номер N!\n");

    return -3;
  }

  if (N < 1) {
    printf("Неправильный номер N!\n");

    if (inputMode == 1)
      fclose(file);

    return -4;
  }

  A = (double *)malloc(N * N * sizeof(double));
  X = (double *)malloc(N * N * sizeof(double));

  if (!(A && X)) {
    printf("Недостаточно памяти!\n");

    if (A)
      free(A);
    if (X)
      free(X);

    if (inputMode == 1)
      fclose(file);

    return -5;
  }

  Result = Input(N, A, inputMode, file);

  if (inputMode == 1)
    fclose(file);

  if (Result == -1) {
    printf("Ошибка чтения файла!\n");
    free(A);
    free(X);
    return -6;
  }
  printf("Матрица A:\n");
  Print(N, A);
  printf("\n");
  t = clock();
  Result = InverseMatrix(N, A, X);
  t = clock() - t;
  switch (Result) {
  case -1:
    printf("Невозможно найти обратную матрицу.\n");
    break;
  case 0:
    printf("Обратная матрица A^(-1):\n");
    Print(N, X);
    printf("Время расчета = %.3f сек.", (double)t / CLOCKS_PER_SEC);
    if (inputMode == 1) {
      file = fopen(FN, "r");
      fscanf(file, "%d", &N);
    }
    Input(N, A, inputMode, file);
    if (inputMode == 1)
      fclose(file);
    printf("\n||A * A^(-1) - b|| = %e\n", SolutionError(N, A, X));
    break;
  default:
    printf("Неизвестная ошибка!\n");
    break;
  }
  free(A);
  free(X);
  return 0;
}
