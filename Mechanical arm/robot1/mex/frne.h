/**
 * \file frne.h
 * \author Peter Corke
 * \brief Definitions for MEX file
 *
 * Copyright (c) 2002  Peter I. Corke
 *
 * Permission to use and distribute is granted, provided that this message
 * is retained, and due credit given when the results are incorporated in
 * publised work.
 *
 * $Id: frne.h,v 1.2 2002/02/11 01:48:49 pic Exp $
 *
 */

#ifndef	_rne_h_
#define	_rne_h_

#include	<math.h>

#include	"vmath.h"

#define	TRUE	1
#define	FALSE	0

/*
 * Accessing information within a MATLAB structure is inconvenient and slow.
 * To get around this we build our own robot and link data structures, and
 * copy the information from the MATLAB objects once per call.  If the call
 * is for multiple states values then our efficiency becomes very high.
 */

/* Robot kinematic convention */
typedef
	enum _dhtype {
		STANDARD,
		MODIFIED
} DHType;

/* Link joint type */
typedef
	enum _axistype {
		REVOLUTE = 0,
		PRISMATIC = 1
} Sigma;

/* A robot link structure */
typedef struct _link {
	/**********************************************************
	 *************** kinematic parameters *********************
	 **********************************************************/
	double	alpha;		/* link twist */
	double	A;		/* link offset */
	double	D;		/* link length */
	double	theta;		/* link rotation angle */
	double	offset;		/* link coordinate offset */
	int	sigma; 		/* axis type; revolute or prismatic */

	/**********************************************************
	 ***************** dynamic parameters *********************
	 **********************************************************/

	/**************** of links ********************************/
	Vect	*rbar;		/* centre of mass of link wrt link origin */
	double	m;		/* mass of link */
	double	*I;		/* inertia tensor of link wrt link origin */

	/**************** of actuators *****************************/
		/* these parameters are motor referenced */
	double	Jm;		/* actuator inertia */
	double	G;		/* gear ratio */
	double	B;		/* actuator friction damping coefficient */
	double	*Tc;		/* actuator Coulomb friction coeffient */

	/**********************************************************
	 **************** intermediate variables ******************
	 **********************************************************/
	Vect	r;		/* distance of ith origin from i-1th wrt ith */
	Rot	R;		/* link rotation matrix */
	Vect	omega;		/* angular velocity */
	Vect	omega_d;	/* angular acceleration */
	Vect	acc;		/* acceleration */
	Vect	abar;		/* acceleration of centre of mass */
	Vect	f;		/* inter-link force */
	Vect	n;		/* inter-link moment */
} Link;

/* A robot */
typedef struct _robot {
	int	njoints;	/* number of joints */
	Vect	*gravity;	/* gravity vector */
	DHType	dhtype;		/* kinematic convention */
	Link	*links;		/* the links */
} Robot;

#endif
