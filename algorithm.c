#include <math.h>
#include "algorithm.h"

int InverseMatrix(int dimension, double *A, double *X) {
  double Var;
  double tempValue1;
  double tempValue2;
  double cosinus;
  double sinus;

  for (int i = 0; i < dimension; ++i)
    for (int j = 0; j < dimension; ++j)
      X[i * dimension + j] = (double)(i == j);

  for (int i = 0; i < dimension; ++i) {
    for (int j = i + 1; j < dimension; ++j) {
      tempValue1 = A[i * dimension + i];
      tempValue2 = A[j * dimension + i];

      Var = sqrt(tempValue1 * tempValue1 + tempValue2 * tempValue2);

      if (Var < 1e-100)
        return -1;

      cosinus = tempValue1 / Var;
      sinus = -tempValue2 / Var;

      A[i * dimension + i] = Var;
      A[j * dimension + i] = 0.0;

      for (int k = i + 1; k < dimension; ++k) {
        tempValue1 = A[i * dimension + k];
        tempValue2 = A[j * dimension + k];

        A[i * dimension + k] = tempValue1 * cosinus - tempValue2 * sinus;
        A[j * dimension + k] = tempValue1 * sinus + tempValue2 * cosinus;
      }

      for (int k = 0; k < dimension; ++k) {
        tempValue1 = X[k * dimension + i];
        tempValue2 = X[k * dimension + j];

        X[k * dimension + i] = tempValue1 * cosinus - tempValue2 * sinus;
        X[k * dimension + j] = tempValue1 * sinus + tempValue2 * cosinus;
      }
    }
  }

  for (int i = 0; i < dimension; ++i)
    for (int j = i + 1; j < dimension; ++j) {
      tempValue1 = X[i * dimension + j];
      X[i * dimension + j] = X[j * dimension + i];
      X[j * dimension + i] = tempValue1;
    }

  for (int k = 0; k < dimension; ++k)
    for (int i = dimension - 1; i >= 0; --i) {
      tempValue1 = X[i * dimension + k];
      for (int j = i + 1; j < dimension; ++j)
        tempValue1 -= A[i * dimension + j] * X[j * dimension + k];
      X[i * dimension + k] = tempValue1 / A[i * dimension + i];
    }

  return 0;
}
