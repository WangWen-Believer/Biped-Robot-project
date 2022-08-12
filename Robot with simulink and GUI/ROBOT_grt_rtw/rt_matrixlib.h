#ifndef rt_matrixlib_h
#define rt_matrixlib_h

/* Copyright 2007-2013 The MathWorks, Inc.
 *
 * File    : rt_matrixlib.h
 * Abstract:
 *     Function prototypes for .c sources in rtw/c/src/matrixmath.
 *
 */


/*==========*
 * Includes *
 *==========*/

#include "rtwtypes.h"
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Matrix Multiplication Utility Functions */
extern void rt_MatMultRR_Dbl(real_T         *y, 
                             const real_T   *A, 
                             const real_T   *B, 
                             const int_T dims[3]);

#ifdef CREAL_T
extern void rt_MatMultRC_Dbl(creal_T       *y,
                             const real_T  *A,
                             const creal_T *B,
                             const int_T dims[3]);

extern void rt_MatMultCR_Dbl(creal_T       *y,
                             const creal_T *A,
                             const real_T  *B,
                             const int_T dims[3]);

extern void rt_MatMultCC_Dbl(creal_T       *y,
                             const creal_T *A,
                             const creal_T *B,
                             const int_T dims[3]);
#endif

extern void rt_MatMultRR_Sgl(real32_T       *y,
                             const real32_T *A,
                             const real32_T *B,
                             const int_T  dims[3]);

#ifdef CREAL_T
extern void rt_MatMultRC_Sgl(creal32_T       *y,
                             const real32_T  *A,
                             const creal32_T *B,
                             const int_T   dims[3]);

extern void rt_MatMultCR_Sgl(creal32_T       *y,
                             const creal32_T *A,
                             const real32_T  *B,
                             const int_T   dims[3]);

extern void rt_MatMultCC_Sgl(creal32_T       *y,
                             const creal32_T *A,
                             const creal32_T *B,
                             const int_T   dims[3]);
#endif

extern void rt_MatMultAndIncRR_Dbl(real_T       *y,
                                   const real_T *A,
                                   const real_T *B,
                                   const int_T dims[3]);

#ifdef CREAL_T
extern void rt_MatMultAndIncRC_Dbl(creal_T       *y,
                                   const real_T  *A,
                                   const creal_T *B,
                                   const int_T dims[3]);

extern void rt_MatMultAndIncCR_Dbl(creal_T       *y,
                                   const creal_T *A,
                                   const real_T  *B,
                                   const int_T dims[3]);

extern void rt_MatMultAndIncCC_Dbl(creal_T       *y,
                                   const creal_T *A,
                                   const creal_T *B,
                                   const int_T dims[3]);
#endif
extern void rt_MatMultAndIncRR_Sgl(real32_T       *y,
                                   const real32_T *A,
                                   const real32_T *B,
                                   const int_T  dims[3]);

#ifdef CREAL_T
extern void rt_MatMultAndIncRC_Sgl(creal32_T       *y,
                                   const real32_T  *A,
                                   const creal32_T *B,
                                   const int_T   dims[3]);

extern void rt_MatMultAndIncCR_Sgl(creal32_T       *y,
                                   const creal32_T *A,
                                   const real32_T  *B,
                                   const int_T   dims[3]);

extern void rt_MatMultAndIncCC_Sgl(creal32_T       *y,
                                   const creal32_T *A,
                                   const creal32_T *B,
                                   const int_T   dims[3]);
#endif 

/* Matrix Inversion Utility Functions */
extern void rt_lu_real(real_T      *A,
                       const int_T n,
                       int32_T     *piv);

#ifdef CREAL_T
extern void rt_lu_cplx(creal_T *A,
                       const int_T n,
                       int32_T *piv);
#endif

extern void rt_lu_real_sgl(real32_T      *A,
                           const int_T n,
                           int32_T     *piv);

#ifdef CREAL_T
extern void rt_lu_cplx_sgl(creal32_T *A,
                           const int_T n,
                           int32_T *piv);
#endif

extern void rt_BackwardSubstitutionRR_Dbl(real_T          *pU,
                                          const real_T    *pb,
                                          real_T          *x,
                                          int_T            N,
                                          int_T            P,
                                          boolean_T        unit_upper);

#ifdef CREAL_T
extern void rt_BackwardSubstitutionRC_Dbl(real_T          *pU,
                                          const creal_T   *pb,
                                          creal_T         *x,
                                          int_T            N,
                                          int_T            P,
                                          boolean_T        unit_upper);

extern void rt_BackwardSubstitutionCC_Dbl(creal_T         *pU,
                                          const creal_T   *pb,
                                          creal_T         *x,
                                          int_T            N,
                                          int_T            P,
                                          boolean_T        unit_upper);
#endif

extern void rt_ForwardSubstitutionRR_Dbl(real_T        *pL,
                                         const real_T  *pb,
                                         real_T        *x,
                                         int_T          N,
                                         int_T          P,
                                         const int32_T *piv,
                                         boolean_T      unit_lower);

#ifdef CREAL_T
extern void rt_ForwardSubstitutionRC_Dbl(real_T        *pL,
                                         const creal_T   *pb,
                                         creal_T   *x,
                                         int_T     N,
                                         int_T     P,
                                         const int32_T   *piv,
                                         boolean_T unit_lower);

extern void rt_ForwardSubstitutionCR_Dbl(creal_T   *pL,
                                         const real_T    *pb,
                                         creal_T   *x,
                                         int_T     N,
                                         int_T     P,
                                         const int32_T   *piv,
                                         boolean_T unit_lower);

extern void rt_ForwardSubstitutionCC_Dbl(creal_T   *pL,
                                         const creal_T   *pb,
                                         creal_T   *x,
                                         int_T     N,
                                         int_T     P,
                                         const int32_T   *piv,
                                         boolean_T unit_lower);
#endif

extern void rt_BackwardSubstitutionRR_Sgl(real32_T          *pU,
                                          const real32_T    *pb,
                                          real32_T          *x,
                                          int_T              N,
                                          int_T              P,
                                          boolean_T          unit_upper);

#ifdef CREAL_T
extern void rt_BackwardSubstitutionRC_Sgl(real32_T          *pU,
                                          const creal32_T   *pb,
                                          creal32_T         *x,
                                          int_T              N,
                                          int_T              P,
                                          boolean_T          unit_upper);

extern void rt_BackwardSubstitutionCC_Sgl(creal32_T         *pU,
                                          const creal32_T   *pb,
                                          creal32_T         *x,
                                          int_T              N,
                                          int_T              P,
                                          boolean_T          unit_upper);
#endif

extern void rt_ForwardSubstitutionRR_Sgl(real32_T    *pL,
                                         const real32_T    *pb,
                                         real32_T    *x,
                                         int_T     N,
                                         int_T     P,
                                         const int32_T   *piv,
                                         boolean_T unit_lower);

#ifdef CREAL_T
extern void rt_ForwardSubstitutionRC_Sgl(real32_T    *pL,
                                         const creal32_T   *pb,
                                         creal32_T   *x,
                                         int_T     N,
                                         int_T     P,
                                         const int32_T   *piv,
                                         boolean_T unit_lower);

extern void rt_ForwardSubstitutionCR_Sgl(creal32_T   *pL,
                                         const real32_T    *pb,
                                         creal32_T   *x,
                                         int_T     N,
                                         int_T     P,
                                         const int32_T   *piv,
                                         boolean_T unit_lower);

extern void rt_ForwardSubstitutionCC_Sgl(creal32_T   *pL,
                                         const creal32_T   *pb,
                                         creal32_T   *x,
                                         int_T     N,
                                         int_T     P,
                                         const int32_T   *piv,
                                         boolean_T unit_lower);
#endif


extern void rt_MatDivRR_Dbl(real_T        *Out,
                            const real_T  *In1,
                            const real_T  *In2,
                            real_T        *lu,
                            int32_T       *piv,
                            real_T        *x,
                            const int_T    dims[3]);

#ifdef CREAL_T
extern void rt_MatDivRC_Dbl(creal_T       *Out,
                            const real_T  *In1,
                            const creal_T *In2,
                            real_T        *lu,
                            int32_T       *piv,
                            creal_T       *x,
                            const int_T    dims[3]);

extern void rt_MatDivCR_Dbl(creal_T       *Out,
                            const creal_T *In1,
                            const real_T  *In2,
                            creal_T       *lu,
                            int32_T       *piv,
                            creal_T       *x,
                            const int_T    dims[3]);

extern void rt_MatDivCC_Dbl(creal_T       *Out,
                            const creal_T *In1,
                            const creal_T *In2,
                            creal_T       *lu,
                            int32_T       *piv,
                            creal_T       *x,
                            const int_T    dims[3]);
#endif

extern void rt_MatDivRR_Sgl(real32_T        *Out,
                            const real32_T  *In1,
                            const real32_T  *In2,
                            real32_T        *lu,
                            int32_T         *piv,
                            real32_T        *x,
                            const int_T      dims[3]);

#ifdef CREAL_T
extern void rt_MatDivRC_Sgl(creal32_T       *Out,
                            const real32_T  *In1,
                            const creal32_T *In2,
                            real32_T        *lu,
                            int32_T         *piv,
                            creal32_T       *x,
                            const int_T      dims[3]);

extern void rt_MatDivCR_Sgl(creal32_T       *Out,
                            const creal32_T *In1,
                            const real32_T  *In2,
                            creal32_T       *lu,
                            int32_T         *piv,
                            creal32_T       *x,
                            const int_T      dims[3]);

extern void rt_MatDivCC_Sgl(creal32_T       *Out,
                            const creal32_T *In1,
                            const creal32_T *In2,
                            creal32_T       *lu,
                            int32_T         *piv,
                            creal32_T       *x,
                            const int_T      dims[3]);
#endif


/* Matrix multiplication defines */

/* Quick (approximate) complex absolute value: */
#define CQABS(X) (fabs((X).re) + fabs((X).im))

/* Quick (approximate) complex absolute value for singles: */
#define CQABSSGL(X) (real32_T)(fabs( (real_T) (X).re) + fabs( (real_T) (X).im)) 

#ifdef CREAL_T
extern void rt_ComplexTimes_Dbl(creal_T       *Out,
                                const creal_T In1,
                                const creal_T In2);

extern void rt_ComplexRDivide_Dbl(creal_T       *Out,
                                  const creal_T In1,
                                  const creal_T In2);

extern void rt_ComplexReciprocal_Dbl(creal_T       *Out,
                                     const creal_T In1);

extern void rt_ComplexTimes_Sgl(creal32_T       *Out,
                                const creal32_T In1,
                                const creal32_T In2);

extern void rt_ComplexRDivide_Sgl(creal32_T       *Out,
                                  const creal32_T In1,
                                  const creal32_T In2);

extern void rt_ComplexReciprocal_Sgl(creal32_T       *Out,
                                     const creal32_T In1);

#endif

extern real_T rt_Hypot_Dbl(real_T In1,
                           real_T In2);

extern real32_T rt_Hypot_Sgl(real32_T In1,
                             real32_T In2);

#ifdef __cplusplus
}
#endif

#endif /* rt_matrixlib_h */
