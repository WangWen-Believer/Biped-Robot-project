/* Copyright 1994-2010 The MathWorks, Inc.
 *
 * File: rt_backsubrr_dbl.c     
 *
 * Abstract:
 *      Simulink Coder support routine which performs
 *      backward substitution: solving Ux=b for real
 *      double precision float operands.
 *
 */

#include "rt_matrixlib.h"

/* Function: rt_BackwardSubstitutionRR_Dbl =====================================
 * Abstract: Backward substitution: Solving Ux=b 
 *           U: real, double
 *           b: real, double
 *           U is an upper (or unit upper) triangular full matrix.
 *           The entries in the lower triangle are ignored.
 *           U is a NxN matrix
 *           X is a NxP matrix
 *           B is a NxP matrix
 */
void rt_BackwardSubstitutionRR_Dbl(real_T          *pU,
                                   const real_T    *pb,
                                   real_T          *x,
                                   int_T            N,
                                   int_T            P,
                                   boolean_T        unit_upper)
{
  int_T i,k;
  for(k=P; k>0; k--) {
    real_T *pUcol = pU;
    for(i=0; i<N; i++) {
      real_T *xj = x + k*N-1;
      real_T s = 0.0;
      real_T *pUrow = pUcol--;          /* access current row of U */

      {
        int_T j = i;
        while(j-- > 0) {
          s += *pUrow * *xj--;
          pUrow -= N;
        }
      }

      if (unit_upper) {
        *xj = *pb-- - s;
      } else {
        *xj = (*pb-- - s) / *pUrow;
      }
    }
  }
}

/* [EOF] rt_backsubrr_dbl.c */
