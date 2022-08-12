/**
 * \file vmath.h
 * \author Peter Corke
 * \brief Simple vector/matrix maths library.
 *
 * Permission to use and distribute is granted, provided that this message
 * is retained, and due credit given when the results are incorporated in
 * publised work.
 *
 * \note All vectors and matrices are passed by reference.
 *
 * Copyright (c) 2002  Peter I. Corke
 *
 * Permission to use and distribute is granted, provided that this message
 * is retained, and due credit given when the results are incorporated in
 * publised work.
 *
 * $Id: vmath.h,v 1.2 2002/02/11 01:48:51 pic Exp $
 *
 */
#ifndef	_vmath_h_
#define	_vmath_h_
typedef struct vector {
	double	x, y, z;
} Vect;

typedef struct matrix {
	Vect	n, o, a;
} Rot;

typedef struct homogeneous_matrix {
	Vect	n, o, a, p;
} Transform;
void	vect_cross (Vect *r, Vect *a, Vect *b);
double	vect_dot (Vect *a, Vect *b);
void	vect_add (Vect *r, Vect *a, Vect *b);
void	scal_mult (Vect *r, Vect *a, double s);
void	rot_vect_mult (Vect *r, Rot *m, Vect *v);
void	rot_trans_vect_mult (Vect *r, Rot *m, Vect *v);
void	mat_vect_mult (Vect *r, double *m, Vect *v);
void	rot_print(char *s, Rot *m);
void	vect_print(char *s, Vect *v);
#endif
