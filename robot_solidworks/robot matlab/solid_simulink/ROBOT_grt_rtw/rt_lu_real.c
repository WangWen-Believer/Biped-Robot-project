/* Copyright 1994-2010 The MathWorks, Inc.
 *
 * File: rt_lu_real.c     
 *
 * Abstract:
 *      Real-Time Workshop support routine for lu_real
 *
 */

#include <math.h>
#include "rt_matrixlib.h"

/* Function: rt_lu_real  =======================================================
 * Abstract: A is real.
 *
 */
void rt_lu_real(real_T      *A,    /* in and out                         */
                const int_T n,     /* number or rows = number of columns */
                int32_T     *piv)  /* pivote vector                      */
{
  int_T k;

  /* initialize row-pivot indices: */
  for (k = 0; k < n; k++) {
    piv[k] = k;
  }

  /* Loop over each column: */
  for (k = 0; k < n; k++) {
    const int_T kn = k*n;
    int_T p = k;

    /* Scan the lower triangular part of this column only
     * Record row of largest value
     */
    {
      int_T i;
      real_T Amax = fabs(A[p+kn]);      /* assume diag is max */
      for (i = k+1; i < n; i++) {
        real_T q = fabs(A[i+kn]);
        if (q > Amax) {p = i; Amax = q;}
      }
    }

    /* swap rows if required */
    if (p != k) {
      int_T j;
      int32_T t1;
      for (j = 0; j < n; j++) {
        real_T t;
        const int_T j_n = j*n;
        t = A[p+j_n]; A[p+j_n] = A[k+j_n]; A[k+j_n] = t;
      }
      /* swap pivot row indices */
      t1 = piv[p]; piv[p] = piv[k]; piv[k] = t1;
    }

    /* column reduction */
    {
      real_T Adiag = A[k+kn];
      int_T i,j;
      if (Adiag != 0.0) {               /* non-zero diagonal entry */

        /* divide lower triangular part of column by max */
        Adiag = 1.0/Adiag;
        for (i = k+1; i < n; i++) {
          A[i+kn] *= Adiag;
        }

        /* subtract multiple of column from remaining columns */
        for (j = k+1; j < n; j++) {
          int_T j_n = j*n;
          for (i = k+1; i < n; i++) {
            A[i+j_n] -= A[i+kn]*A[k+j_n];
          }
        }
      }
    }
  }
}

/* [EOF] rt_lu_real.c */
