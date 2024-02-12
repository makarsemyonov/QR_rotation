#include <math.h>
#include <stdio.h>

#include "matrix.h"

#define OS 5

static double f(int dimension, int i, int j) { 
  if (i==j && (j == 0 || j == dimension-1)) {
    return (double)-(dimension-2)/(2*dimension -2);
  }
  else if (i==j && 1<=j<=dimension-2) {
    return -1;
  }
  else if ((i - j == 1) || (j - i == 1)) {
    return 0.5;
  }
  else if ((i == 0 && j == dimension - 1)||(i == dimension - 1 && j == 0)){
    return(double)1/(2*dimension - 2);
  }
  else {
    return 0;
  }
}

int Input(int dimension, double *A, int inputMode, FILE *file) {
  if (inputMode == 1) {
    for (int i = 0; i < dimension; ++i)
      for (int j = 0; j < dimension; ++j)
        if (fscanf(file, "%lf", &A[i * dimension + j]) != 1)
          return -1;
  } else {
    for (int i = 0; i < dimension; ++i)
      for (int j = 0; j < dimension; ++j)
        A[i * dimension + j] = f(dimension, i, j);
  }

  return 0;
}

void Print(int dimension, double *A) {
  int temp;

  temp = (dimension > OS) ? OS : dimension;

  for (int i = 0; i < temp; ++i) {
    for (int j = 0; j < temp; ++j)
      printf("%10.3g ", A[i * dimension + j]);
    printf("\n");
  }
}

double SolutionError(int dimension, double *A, double *X) {
  double temp;
  double result;

  result = 0.0;
  for (int i = 0; i < dimension; ++i) {
    for (int j = 0; j < dimension; ++j) {
      temp = 0.0;
      for (int k = 0; k < dimension; ++k)
        temp += A[i * dimension + k] * X[k * dimension + j];
      if (i == j)
        temp -= 1.0;
      result += temp * temp;
    }
  }

  return sqrt(result);
}
