#ifndef __MATRIX_H_INCLUDED__
#define __MATRIX_H_INCLUDED__

int Input(int dimension, double *A, int inputMode, FILE *fin);

void Print(int dimension, double *A);

double SolutionError(int dimension, double *A, double *X);

#endif
