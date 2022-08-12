/**
 * \file frne.c
 * \author Peter Corke
 * \brief MEX file body
 *
 *
 *  FRNE	 MEX file version of RNE.M
 *
 *	TAU = FRNE(ROBOT, Q, QD, QDD)
 *	TAU = FRNE(ROBOT, [Q QD QDD])
 *
 *	where	Q, QD and QDD are row vectors of the manipulator state; pos,
 *	vel, and accel.
 *
 *	Returns the joint torque required to achieve the specified joint 
 *	position, velocity and acceleration state.  Gravity is taken
 *	from the robot object.
 *
 *	TAU = RNE(ROBOT, Q, QD, QDD, GRAV)
 *	TAU = RNE(ROBOT, [Q QD QDD], GRAV)
 *
 *	GRAV overrides the gravity vector in the robot object.
 *
 *	An external force/moment acting on the end of the manipulator may 
 *	also be	specified by a 6-element vector [Fx Fy Fz Mx My Mz].
 *
 *	TAU = RNE(ROBOT, Q, QD, QDD, GRAV, FEXT)
 *	TAU = RNE(ROBOT, [Q QD QDD], GRAV, FEXT)
 *
 */

/*
 * Updated 3/00 for Matlab 5 and object support.
 * Updated 1/02 for MDH support.
 *
 * Copyright (c) 2002  Peter I. Corke
 *
 * Permission to use and distribute is granted, provided that this message
 * is retained, and due credit given when the results are incorporated in
 * publised work.
 *
 * $Id: frne.c,v 1.5 2002/02/15 01:13:34 pic Exp $
 *
 */

#include "mex.h"
#include <math.h>

#include	"frne.h"

/*
#define	DEBUG
*/

/* Input Arguments */
#define	ROBOT_IN	prhs[0]
#define	A1_IN		prhs[1]
#define	A2_IN		prhs[2]
#define	A3_IN		prhs[3]
#define	A4_IN		prhs[4]
#define	A5_IN		prhs[5]

/* Output Arguments */
#define	TAU_OUT	plhs[0]

/* Some useful things */
#define	NUMROWS(x)	mxGetM(x)
#define	NUMCOLS(x)	mxGetN(x)
#define	NUMELS(x)	(mxGetN(x)*mxGetM(x))
#define	POINTER(x)	mxGetPr(x)

/* forward defines */
static void rot_mat (Link *l, double th, double d, DHType type);
static int mstruct_getfield_number(mxArray *m, char *field);
static int mstruct_getint(mxArray *m, int i, char *field);
static double mstruct_getreal(mxArray *m, int i, char *field);
static double * mstruct_getrealvect(mxArray *m, int i, char *field);
void error(char *s, ...);


/*
 * enums for all the fields we want to pull out of the Matlab robot object
 */
enum {
	FLD_ALPHA,
	FLD_A,
	FLD_THETA,
	FLD_D,
	FLD_SIGMA,
	FLD_OFFSET,
	FLD_M,
	FLD_R,
	FLD_I,
	FLD_JM,
	FLD_G,
	FLD_B,
	FLD_TC,
	FLD_MAX
};


/* default values for gravity and external load */

/**
 * MEX function entry point.
 */
void 
mexFunction(
	int		nlhs,
	mxArray		*plhs[],
	int		nrhs,
	const mxArray	*prhs[]
) {
	double	*q, *qd, *qdd;
	double	*tau;
	unsigned int	m,n;
	int	j, njoints, p, nq;
	double	*fext = NULL;
	double *grav = NULL;
	Robot		robot;
	mxArray		*link0;
	mxArray		*mx_robot;
	mxArray		*mx_links;
	static int	firstime = 0;
	int	fieldmap[FLD_MAX];

	if (  !mxIsStruct(ROBOT_IN) ||
	      (strcmp(mxGetClassName(ROBOT_IN), "robot") != 0)
	)
		mexErrMsgTxt("first argument is not a robot structure\n");

	mx_robot = (mxArray *)ROBOT_IN;
	njoints = mstruct_getint(mx_robot, 0, "n");

/***********************************************************************
 * Handle the different calling formats.
 * Setup pointers to q, qd and qdd inputs 
 ***********************************************************************/
	switch (nrhs) {
	case 2:
	/*
	 * TAU = RNE(ROBOT, [Q QD QDD])
	 */ 
		if (NUMCOLS(A1_IN) != 3 * njoints)
			mexErrMsgTxt("RNE too few cols in [Q QD QDD]");
		q = POINTER(A1_IN);
		nq = NUMROWS(A1_IN);
		qd = &q[njoints*nq];
		qdd = &q[2*njoints*nq];
		break;
		
	case 3:
	/*
	 * TAU = RNE(ROBOT, [Q QD QDD], GRAV)
	 */ 
		if (NUMCOLS(A1_IN) != (3 * njoints))
			mexErrMsgTxt("RNE too few cols in [Q QD QDD]");
		q = POINTER(A1_IN);
		nq = NUMROWS(A1_IN);
		qd = &q[njoints*nq];
		qdd = &q[2*njoints*nq];

		if (NUMELS(A2_IN) != 3)
			mexErrMsgTxt("RNE gravity vector expected");
		grav = POINTER(A2_IN);
		break;

	case 4:
	/*
	 * TAU = RNE(ROBOT, Q, QD, QDD)
	 * TAU = RNE(ROBOT, [Q QD QDD], GRAV, FEXT)
	 */ 
		if (NUMCOLS(A1_IN) == (3 * njoints)) {
			q = POINTER(A1_IN);
			nq = NUMROWS(A1_IN);
			qd = &q[njoints*nq];
			qdd = &q[2*njoints*nq];

			if (NUMELS(A2_IN) != 3)
				mexErrMsgTxt("RNE gravity vector expected");
			grav = POINTER(A2_IN);
			if (NUMELS(A3_IN) != 6)
				mexErrMsgTxt("RNE Fext vector expected");
			fext = POINTER(A3_IN);
		} else {
			int	nqd = NUMROWS(A2_IN),
				nqdd = NUMROWS(A3_IN);

			nq = NUMROWS(A1_IN);
			if ((nq != nqd) || (nqd != nqdd))
				mexErrMsgTxt("RNE Q QD QDD must be same length");
			if ( (NUMCOLS(A1_IN) != njoints) ||
			     (NUMCOLS(A2_IN) != njoints) ||
			     (NUMCOLS(A3_IN) != njoints)
			) 
				mexErrMsgTxt("RNE Q must have Naxis columns");
			q = POINTER(A1_IN);
			qd = POINTER(A2_IN);
			qdd = POINTER(A3_IN);
		}
		break;

	case 5: {
	/*
	 * TAU = RNE(ROBOT, Q, QD, QDD, GRAV)
	 */
		int	nqd = NUMROWS(A2_IN),
			nqdd = NUMROWS(A3_IN);

		nq = NUMROWS(A1_IN);
		if ((nq != nqd) || (nqd != nqdd))
			mexErrMsgTxt("RNE Q QD QDD must be same length");
		if ( (NUMCOLS(A1_IN) != njoints) ||
		     (NUMCOLS(A2_IN) != njoints) ||
		     (NUMCOLS(A3_IN) != njoints)
		) 
			mexErrMsgTxt("RNE Q must have Naxis columns");
		q = POINTER(A1_IN);
		qd = POINTER(A2_IN);
		qdd = POINTER(A3_IN);
		if (NUMELS(A4_IN) != 3)
			mexErrMsgTxt("RNE gravity vector expected");
		grav = POINTER(A4_IN);
		break;
	}

	case 6: {
	/*
	 * TAU = RNE(ROBOT, Q, QD, QDD, GRAV, FEXT)
	 */
		int	nqd = NUMROWS(A2_IN),
			nqdd = NUMROWS(A3_IN);

		nq = NUMROWS(A1_IN);
		if ((nq != nqd) || (nqd != nqdd))
			mexErrMsgTxt("RNE Q QD QDD must be same length");
		if ( (NUMCOLS(A1_IN) != njoints) ||
		     (NUMCOLS(A2_IN) != njoints) ||
		     (NUMCOLS(A3_IN) != njoints)
		) 
			mexErrMsgTxt("RNE Q must have Naxis columns");
		q = POINTER(A1_IN);
		qd = POINTER(A2_IN);
		qdd = POINTER(A3_IN);
		if (NUMELS(A4_IN) != 3)
			mexErrMsgTxt("RNE gravity vector expected");
		grav = POINTER(A4_IN);
		if (NUMELS(A5_IN) != 6)
			mexErrMsgTxt("RNE Fext vector expected");
		fext = POINTER(A5_IN);
		break;
	}
	default:
		mexErrMsgTxt("RNE wrong number of arguments.");
	}


	if (firstime == 0) {
		mexPrintf("Fast RNE: (c) Peter Corke 2002\n");
		firstime = 1;
	}

	/*
	 * fill out the robot structure
	 */
	robot.njoints = njoints;

	if (grav)
		robot.gravity = (Vect *)grav;
	else
		robot.gravity = (Vect *)mxGetPr( mxGetField(mx_robot, 0, "gravity") );
	robot.dhtype = mstruct_getint(mx_robot, 0, "mdh");

	/* build link structure */
	robot.links = (Link *)mxCalloc(njoints, sizeof(Link));


/***********************************************************************
 * Now we have to get pointers to data spread all across a cell-array
 * of Matlab structures.
 *
 * Matlab structure elements can be found by name (slow) or by number (fast).
 * We assume that since the link structures are all created by the same
 * constructor, the index number for each element will be the same for all
 * links.  However we make no assumption about the numbers themselves.
 ***********************************************************************/

	/* get pointer to link structures */
	mx_links = mxGetField(mx_robot, 0, "link");
	if (mx_links == NULL)
		mexErrMsgTxt("couldnt find element link in robot structure");

	/*
	 * Elements of the link structure are:
	 *
	 *	alpha: 
	 *	A:
	 *	theta:
	 *	D:
	 *	offset:
	 *	sigma:
	 *	mdh:
	 *	m:
	 *	r:
	 *	I:
	 *	Jm:
	 *	G:
	 *	B:
	 *	Tc:
	 */

	/* take the first link as the template */
	link0 = mxGetCell(mx_links, 0);

	/* and lookup each structure element, and save the index */
	fieldmap[FLD_ALPHA] = mstruct_getfield_number(link0, "alpha");
	fieldmap[FLD_A] = mstruct_getfield_number(link0, "A");
	fieldmap[FLD_THETA] = mstruct_getfield_number(link0, "theta");
	fieldmap[FLD_D] = mstruct_getfield_number(link0, "D");
	fieldmap[FLD_SIGMA] = mstruct_getfield_number(link0, "sigma");
	fieldmap[FLD_OFFSET] = mstruct_getfield_number(link0, "offset");
	fieldmap[FLD_M] = mstruct_getfield_number(link0, "m");
	fieldmap[FLD_R] = mstruct_getfield_number(link0, "r");
	fieldmap[FLD_I] = mstruct_getfield_number(link0, "I");
	fieldmap[FLD_JM] = mstruct_getfield_number(link0, "Jm");
	fieldmap[FLD_G] = mstruct_getfield_number(link0, "G");
	fieldmap[FLD_B] = mstruct_getfield_number(link0, "B");
	fieldmap[FLD_TC] = mstruct_getfield_number(link0, "Tc");

	/*
	 * now for each link structure, use the saved index to copy the
	 * data into the corresponding Link structure.
	 */
	for (j=0; j<njoints; j++) {
		Link	*l = &robot.links[j];

		mxArray	*m = mxGetCell(mx_links, j);

		l->alpha = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_ALPHA]) );
		l->A = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_A]) );
		l->theta = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_THETA]) );
		l->D = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_D]) );
		l->sigma = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_SIGMA]) );
		l->offset = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_OFFSET]) );
		l->m = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_M]) );
		l->rbar = (Vect *)mxGetPr( mxGetFieldByNumber(m, 0, fieldmap[FLD_R]) );
		l->I = mxGetPr( mxGetFieldByNumber(m, 0, fieldmap[FLD_I]) );
		l->Jm = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_JM]) );
		l->G = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_G]) );
		l->B = mxGetScalar( mxGetFieldByNumber(m, 0, fieldmap[FLD_B]) );
		l->Tc = mxGetPr( mxGetFieldByNumber(m, 0, fieldmap[FLD_TC]) );
	}

	/* Create a matrix for the return argument */
	TAU_OUT = mxCreateDoubleMatrix(nq, njoints, mxREAL);
	tau = mxGetPr(TAU_OUT);

#define	MEL(x,R,C)	(x[(R)+(C)*nq])

	/* for each point in the input trajectory */
	for (p=0; p<nq; p++) {
		/*
		 * update all position dependent variables
		 */
		for (j = 0; j < njoints; j++) {
			Link	*l = &robot.links[j];

			switch (l->sigma) {
			case REVOLUTE:
				rot_mat(l, MEL(q,p,j)+l->offset, l->D, robot.dhtype);
				break;
			case PRISMATIC:
				rot_mat(l, l->theta, MEL(q,p,j)+l->offset, robot.dhtype);
				break;
			}
#ifdef	DEBUG
			rot_print("R", &l->R);
			vect_print("p*", &l->r);
#endif
		}

		newton_euler(&robot, &tau[p], &qd[p], &qdd[p], fext, nq);

	}

	mxFree(robot.links);
}

/*
 *	Written by;
 *
 *		Peter I. Corke
 *		CSIRO Division of Manufacturing Technology
 *		Preston, Melbourne.  Australia. 3072.
 *
 *		pic@mlb.dmt.csiro.au
 *
 *  Permission to use and distribute is granted, provided that this message
 * is retained, and due credit given when the results are incorporated in
 * publised work.
 *
 */

/**
 * Return the link rotation matrix and translation vector.
 *
 * @param l Link object for which R and p* are required.
 * @param th Joint angle, overrides value in link object
 * @param d Link extension, overrides value in link object
 * @param type Kinematic convention.
 */
static void
rot_mat (
	Link	*l,
	double	th,
	double	d,
	DHType	type
) {
	double		st, ct, sa, ca;

#ifdef	sun
	sincos(th, &st, &ct);
	sincos(l->alpha, &sa, &ca);
#else
	st = sin(th);
	ct = cos(th);
	sa = sin(l->alpha);
	ca = cos(l->alpha);
#endif

	switch (type) {
case STANDARD:
	l->R.n.x = ct;		l->R.o.x = -ca*st;	l->R.a.x = sa*st;
	l->R.n.y = st;		l->R.o.y = ca*ct;	l->R.a.y = -sa*ct;
	l->R.n.z = 0.0;		l->R.o.z = sa;		l->R.a.z = ca;

	l->r.x = l->A;
	l->r.y = d * sa;
	l->r.z = d * ca;
	break;
case MODIFIED:
	l->R.n.x = ct;		l->R.o.x = -st;		l->R.a.x = 0.0;
	l->R.n.y = st*ca;	l->R.o.y = ca*ct;	l->R.a.y = -sa;
	l->R.n.z = st*sa;	l->R.o.z = ct*sa;	l->R.a.z = ca;

	l->r.x = l->A;
	l->r.y = -d * sa;
	l->r.z = d * ca;
	break;
	}
}

/*************************************************************************
 * Matlab structure access methods
 *************************************************************************/
static mxArray *
mstruct_get_element(mxArray *m, int i, char *field)
{
	mxArray	*e;

	if (mxIsCell(m)) {
#ifdef	DEBUG
		mexPrintf("%d x %d\n", mxGetM(m), mxGetN(m));
#endif
		/* get the i'th cell from the cell array */
		if ((e = mxGetCell(m, i)) == NULL)
			error("get_element: field %s: cant get cell element %d",field, i);
	} else
		e = m;

	if (!mxIsStruct(e))
		mexErrMsgTxt("get_element: expecting a structure");
	if ((e = mxGetField(e, 0, field)) != NULL)
		return e;
	else {
		error("No such field as %s", field);
	}
}

static int
mstruct_getfield_number(mxArray *m, char *field)
{
	int	f;
	
	if ((f = mxGetFieldNumber(m, field)) < 0)
		error("no element %s in link structure");

	return f;
}

static int
mstruct_getint(mxArray *m, int i, char *field)
{
	mxArray	*e;

	e = mstruct_get_element(m, i, field);

	return (int) mxGetScalar(e);
}

static double
mstruct_getreal(mxArray *m, int i, char *field)
{
	mxArray	*e;

	e = mstruct_get_element(m, i, field);

	return mxGetScalar(e);
}

static double *
mstruct_getrealvect(mxArray *m, int i, char *field)
{
	mxArray	*e;

	e = mstruct_get_element(m, i, field);

	return mxGetPr(e);
}

#include	<stdarg.h>

/**
 * Error message handler.  Takes printf() style format string and variable
 * arguments and sends resultant string to Matlab via \t mexErrMsgTxt().
 *
 * @param s Error message string, \t  printf() style.
 */
void
error(char *s, ...)
{
	char	b[BUFSIZ];

	va_list	ap;

	va_start(ap, s);

	vsprintf(b, s, ap);

	mexErrMsgTxt(b);
}
