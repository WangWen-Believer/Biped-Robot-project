

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void ep7_11_Outputs_wrapper(real_T *y0,
			const real_T *xC,
			const real_T *m, const int_T p_width0,
			const real_T *M, const int_T p_width1,
			const real_T *g, const int_T p_width2,
			const real_T *l, const int_T p_width3)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/*ÿÿÿÿÿÿÿÿ*/
y[0]=xC[0];
y[1]=xC[2];

/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Derivatives function
 *
 */
void ep7_11_Derivatives_wrapper(const real_T *u0,
			real_T *y0,
			real_T *dx,
			real_T *xC,
			const real_T *m, const int_T p_width0,
			const real_T *M, const int_T p_width1,
			const real_T *g, const int_T p_width2,
			const real_T *l, const int_T p_width3)
{
/* %%%-SFUNWIZ_wrapper_Derivatives_Changes_BEGIN --- EDIT HERE TO _END */
dx[0]=xC[1];
dx[1]=((u[0]+m[0]*l[0]*xC[3]*xC[3]*sin([xC[2]))*cos(xC[2])-
     (g[0]*sin(xC[2])+l[0]*xC[3]*xC[3]*sin(xC[2])*cos(xC[2])*m[0])/(M[0]*cos(xC[2]));
dx[2]=xC[3];


/* %%%-SFUNWIZ_wrapper_Derivatives_Changes_END --- EDIT HERE TO _BEGIN */
}
