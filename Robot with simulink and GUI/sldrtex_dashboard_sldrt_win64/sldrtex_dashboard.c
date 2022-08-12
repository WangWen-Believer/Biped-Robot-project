/*
 * sldrtex_dashboard.c
 *
 * Code generation for model "sldrtex_dashboard".
 *
 * Model version              : 1.61
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Sun Jan 20 21:53:22 2019
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "sldrtex_dashboard.h"
#include "sldrtex_dashboard_private.h"
#include "sldrtex_dashboard_dt.h"

/* list of Simulink Desktop Real-Time timers */
const int SLDRTTimerCount = 1;
const double SLDRTTimers[2] = {
  0.1, 0.0,
};

/* Block signals (auto storage) */
B_sldrtex_dashboard_T sldrtex_dashboard_B;

/* Continuous states */
X_sldrtex_dashboard_T sldrtex_dashboard_X;

/* Block states (auto storage) */
DW_sldrtex_dashboard_T sldrtex_dashboard_DW;

/* Real-time model */
RT_MODEL_sldrtex_dashboard_T sldrtex_dashboard_M_;
RT_MODEL_sldrtex_dashboard_T *const sldrtex_dashboard_M = &sldrtex_dashboard_M_;

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE5_A[6] = {
    1.0/5.0, 3.0/10.0, 4.0/5.0, 8.0/9.0, 1.0, 1.0
  };

  static const real_T rt_ODE5_B[6][6] = {
    { 1.0/5.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

    { 3.0/40.0, 9.0/40.0, 0.0, 0.0, 0.0, 0.0 },

    { 44.0/45.0, -56.0/15.0, 32.0/9.0, 0.0, 0.0, 0.0 },

    { 19372.0/6561.0, -25360.0/2187.0, 64448.0/6561.0, -212.0/729.0, 0.0, 0.0 },

    { 9017.0/3168.0, -355.0/33.0, 46732.0/5247.0, 49.0/176.0, -5103.0/18656.0,
      0.0 },

    { 35.0/384.0, 0.0, 500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE5_IntgData *id = (ODE5_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T *f4 = id->f[4];
  real_T *f5 = id->f[5];
  real_T hB[6];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  sldrtex_dashboard_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  sldrtex_dashboard_output();
  sldrtex_dashboard_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE5_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  sldrtex_dashboard_output();
  sldrtex_dashboard_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE5_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  sldrtex_dashboard_output();
  sldrtex_dashboard_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++) {
    hB[i] = h * rt_ODE5_B[3][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  sldrtex_dashboard_output();
  sldrtex_dashboard_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++) {
    hB[i] = h * rt_ODE5_B[4][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  sldrtex_dashboard_output();
  sldrtex_dashboard_derivatives();

  /* tnew = t + hA(6);
     ynew = y + f*hB(:,6); */
  for (i = 0; i <= 5; i++) {
    hB[i] = h * rt_ODE5_B[5][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4] + f5[i]*hB[5]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void sldrtex_dashboard_output(void)
{
  if (rtmIsMajorTimeStep(sldrtex_dashboard_M)) {
    /* set solver stop time */
    if (!(sldrtex_dashboard_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&sldrtex_dashboard_M->solverInfo,
                            ((sldrtex_dashboard_M->Timing.clockTickH0 + 1) *
        sldrtex_dashboard_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&sldrtex_dashboard_M->solverInfo,
                            ((sldrtex_dashboard_M->Timing.clockTick0 + 1) *
        sldrtex_dashboard_M->Timing.stepSize0 +
        sldrtex_dashboard_M->Timing.clockTickH0 *
        sldrtex_dashboard_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(sldrtex_dashboard_M)) {
    sldrtex_dashboard_M->Timing.t[0] = rtsiGetT(&sldrtex_dashboard_M->solverInfo);
  }

  /* Integrator: '<S1>/Integrator1' */
  /* Limited  Integrator  (w/ Saturation Port) */
  if (sldrtex_dashboard_X.Integrator1_CSTATE >=
      sldrtex_dashboard_P.Integrator1_UpperSat) {
    sldrtex_dashboard_X.Integrator1_CSTATE =
      sldrtex_dashboard_P.Integrator1_UpperSat;
    sldrtex_dashboard_B.Overflow = 1.0;
  } else if (sldrtex_dashboard_X.Integrator1_CSTATE <=
             sldrtex_dashboard_P.Integrator1_LowerSat) {
    sldrtex_dashboard_X.Integrator1_CSTATE =
      sldrtex_dashboard_P.Integrator1_LowerSat;
    sldrtex_dashboard_B.Overflow = -1.0;
  } else {
    sldrtex_dashboard_B.Overflow = 0.0;
  }

  sldrtex_dashboard_B.hWaterlevel = sldrtex_dashboard_X.Integrator1_CSTATE;

  /* End of Integrator: '<S1>/Integrator1' */

  /* Gain: '<S1>/A: Output valve' incorporates:
   *  Gain: '<S1>/Outflow coefficient'
   *  Sqrt: '<S1>/Sqrt'
   */
  sldrtex_dashboard_B.Q2Outputflow = sldrtex_dashboard_P.Outflowcoefficient_Gain
    * sqrt(sldrtex_dashboard_B.hWaterlevel) *
    sldrtex_dashboard_P.AOutputvalve_Gain;
  if (rtmIsMajorTimeStep(sldrtex_dashboard_M)) {
    /* ToAsyncQueueBlock: '<S1>/HiddenToAsyncQueue_InsertedFor_A: Output valve_at_outport_0' */
    if (rtmIsMajorTimeStep(sldrtex_dashboard_M)) {
      {
        double time = sldrtex_dashboard_M->Timing.t[1];
        void *pData = (void *)&sldrtex_dashboard_B.Q2Outputflow;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(1715488304U, time, pData, size);
      }
    }

    /* ToAsyncQueueBlock: '<S1>/HiddenToAsyncQueue_InsertedFor_Integrator1_at_outport_0' */
    if (rtmIsMajorTimeStep(sldrtex_dashboard_M)) {
      {
        double time = sldrtex_dashboard_M->Timing.t[1];
        void *pData = (void *)&sldrtex_dashboard_B.hWaterlevel;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(270074550U, time, pData, size);
      }
    }

    /* ToAsyncQueueBlock: '<S1>/HiddenToAsyncQueue_InsertedFor_Integrator1_at_outport_1' */
    if (rtmIsMajorTimeStep(sldrtex_dashboard_M)) {
      {
        double time = sldrtex_dashboard_M->Timing.t[1];
        void *pData = (void *)&sldrtex_dashboard_B.Overflow;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(1520272018U, time, pData, size);
      }
    }
  }

  /* Gain: '<S1>/Tank Area' incorporates:
   *  Constant: '<S1>/Q1: Input flow'
   *  Sum: '<S1>/Sum'
   */
  sldrtex_dashboard_B.TankArea = (sldrtex_dashboard_P.Q1Inputflow_Value -
    sldrtex_dashboard_B.Q2Outputflow) * sldrtex_dashboard_P.TankArea_Gain;
  if (rtmIsMajorTimeStep(sldrtex_dashboard_M)) {
    /* S-Function (sldrtsync): '<S1>/Real-Time Synchronization' */
    /* S-Function Block: <S1>/Real-Time Synchronization */
    {
    }
  }
}

/* Model update function */
void sldrtex_dashboard_update(void)
{
  if (rtmIsMajorTimeStep(sldrtex_dashboard_M)) {
    rt_ertODEUpdateContinuousStates(&sldrtex_dashboard_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++sldrtex_dashboard_M->Timing.clockTick0)) {
    ++sldrtex_dashboard_M->Timing.clockTickH0;
  }

  sldrtex_dashboard_M->Timing.t[0] = rtsiGetSolverStopTime
    (&sldrtex_dashboard_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++sldrtex_dashboard_M->Timing.clockTick1)) {
      ++sldrtex_dashboard_M->Timing.clockTickH1;
    }

    sldrtex_dashboard_M->Timing.t[1] = sldrtex_dashboard_M->Timing.clockTick1 *
      sldrtex_dashboard_M->Timing.stepSize1 +
      sldrtex_dashboard_M->Timing.clockTickH1 *
      sldrtex_dashboard_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void sldrtex_dashboard_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_sldrtex_dashboard_T *_rtXdot;
  _rtXdot = ((XDot_sldrtex_dashboard_T *) sldrtex_dashboard_M->derivs);

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  lsat = (sldrtex_dashboard_X.Integrator1_CSTATE <=
          sldrtex_dashboard_P.Integrator1_LowerSat);
  usat = (sldrtex_dashboard_X.Integrator1_CSTATE >=
          sldrtex_dashboard_P.Integrator1_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (sldrtex_dashboard_B.TankArea > 0.0)) ||
      (usat && (sldrtex_dashboard_B.TankArea < 0.0))) {
    _rtXdot->Integrator1_CSTATE = sldrtex_dashboard_B.TankArea;
  } else {
    /* in saturation */
    _rtXdot->Integrator1_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S1>/Integrator1' */
}

/* Model initialize function */
void sldrtex_dashboard_initialize(void)
{
  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  sldrtex_dashboard_X.Integrator1_CSTATE = sldrtex_dashboard_P.Integrator1_IC;
}

/* Model terminate function */
void sldrtex_dashboard_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  sldrtex_dashboard_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  sldrtex_dashboard_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  sldrtex_dashboard_initialize();
}

void MdlTerminate(void)
{
  sldrtex_dashboard_terminate();
}

/* Registration function */
RT_MODEL_sldrtex_dashboard_T *sldrtex_dashboard(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)sldrtex_dashboard_M, 0,
                sizeof(RT_MODEL_sldrtex_dashboard_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&sldrtex_dashboard_M->solverInfo,
                          &sldrtex_dashboard_M->Timing.simTimeStep);
    rtsiSetTPtr(&sldrtex_dashboard_M->solverInfo, &rtmGetTPtr
                (sldrtex_dashboard_M));
    rtsiSetStepSizePtr(&sldrtex_dashboard_M->solverInfo,
                       &sldrtex_dashboard_M->Timing.stepSize0);
    rtsiSetdXPtr(&sldrtex_dashboard_M->solverInfo, &sldrtex_dashboard_M->derivs);
    rtsiSetContStatesPtr(&sldrtex_dashboard_M->solverInfo, (real_T **)
                         &sldrtex_dashboard_M->contStates);
    rtsiSetNumContStatesPtr(&sldrtex_dashboard_M->solverInfo,
      &sldrtex_dashboard_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&sldrtex_dashboard_M->solverInfo,
      &sldrtex_dashboard_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&sldrtex_dashboard_M->solverInfo,
      &sldrtex_dashboard_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&sldrtex_dashboard_M->solverInfo,
      &sldrtex_dashboard_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&sldrtex_dashboard_M->solverInfo, (&rtmGetErrorStatus
      (sldrtex_dashboard_M)));
    rtsiSetRTModelPtr(&sldrtex_dashboard_M->solverInfo, sldrtex_dashboard_M);
  }

  rtsiSetSimTimeStep(&sldrtex_dashboard_M->solverInfo, MAJOR_TIME_STEP);
  sldrtex_dashboard_M->intgData.y = sldrtex_dashboard_M->odeY;
  sldrtex_dashboard_M->intgData.f[0] = sldrtex_dashboard_M->odeF[0];
  sldrtex_dashboard_M->intgData.f[1] = sldrtex_dashboard_M->odeF[1];
  sldrtex_dashboard_M->intgData.f[2] = sldrtex_dashboard_M->odeF[2];
  sldrtex_dashboard_M->intgData.f[3] = sldrtex_dashboard_M->odeF[3];
  sldrtex_dashboard_M->intgData.f[4] = sldrtex_dashboard_M->odeF[4];
  sldrtex_dashboard_M->intgData.f[5] = sldrtex_dashboard_M->odeF[5];
  sldrtex_dashboard_M->contStates = ((real_T *) &sldrtex_dashboard_X);
  rtsiSetSolverData(&sldrtex_dashboard_M->solverInfo, (void *)
                    &sldrtex_dashboard_M->intgData);
  rtsiSetSolverName(&sldrtex_dashboard_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = sldrtex_dashboard_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    sldrtex_dashboard_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    sldrtex_dashboard_M->Timing.sampleTimes =
      (&sldrtex_dashboard_M->Timing.sampleTimesArray[0]);
    sldrtex_dashboard_M->Timing.offsetTimes =
      (&sldrtex_dashboard_M->Timing.offsetTimesArray[0]);

    /* task periods */
    sldrtex_dashboard_M->Timing.sampleTimes[0] = (0.0);
    sldrtex_dashboard_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    sldrtex_dashboard_M->Timing.offsetTimes[0] = (0.0);
    sldrtex_dashboard_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(sldrtex_dashboard_M, &sldrtex_dashboard_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = sldrtex_dashboard_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    sldrtex_dashboard_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(sldrtex_dashboard_M, -1);
  sldrtex_dashboard_M->Timing.stepSize0 = 0.1;
  sldrtex_dashboard_M->Timing.stepSize1 = 0.1;

  /* External mode info */
  sldrtex_dashboard_M->Sizes.checksums[0] = (3943179687U);
  sldrtex_dashboard_M->Sizes.checksums[1] = (822749830U);
  sldrtex_dashboard_M->Sizes.checksums[2] = (2918975763U);
  sldrtex_dashboard_M->Sizes.checksums[3] = (977457696U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    sldrtex_dashboard_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(sldrtex_dashboard_M->extModeInfo,
      &sldrtex_dashboard_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(sldrtex_dashboard_M->extModeInfo,
                        sldrtex_dashboard_M->Sizes.checksums);
    rteiSetTPtr(sldrtex_dashboard_M->extModeInfo, rtmGetTPtr(sldrtex_dashboard_M));
  }

  sldrtex_dashboard_M->solverInfoPtr = (&sldrtex_dashboard_M->solverInfo);
  sldrtex_dashboard_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&sldrtex_dashboard_M->solverInfo, 0.1);
  rtsiSetSolverMode(&sldrtex_dashboard_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  sldrtex_dashboard_M->blockIO = ((void *) &sldrtex_dashboard_B);

  {
    sldrtex_dashboard_B.hWaterlevel = 0.0;
    sldrtex_dashboard_B.Overflow = 0.0;
    sldrtex_dashboard_B.Q2Outputflow = 0.0;
    sldrtex_dashboard_B.TankArea = 0.0;
  }

  /* parameters */
  sldrtex_dashboard_M->defaultParam = ((real_T *)&sldrtex_dashboard_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &sldrtex_dashboard_X;
    sldrtex_dashboard_M->contStates = (x);
    (void) memset((void *)&sldrtex_dashboard_X, 0,
                  sizeof(X_sldrtex_dashboard_T));
  }

  /* states (dwork) */
  sldrtex_dashboard_M->dwork = ((void *) &sldrtex_dashboard_DW);
  (void) memset((void *)&sldrtex_dashboard_DW, 0,
                sizeof(DW_sldrtex_dashboard_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    sldrtex_dashboard_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  sldrtex_dashboard_M->Sizes.numContStates = (1);/* Number of continuous states */
  sldrtex_dashboard_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  sldrtex_dashboard_M->Sizes.numY = (0);/* Number of model outputs */
  sldrtex_dashboard_M->Sizes.numU = (0);/* Number of model inputs */
  sldrtex_dashboard_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  sldrtex_dashboard_M->Sizes.numSampTimes = (2);/* Number of sample times */
  sldrtex_dashboard_M->Sizes.numBlocks = (11);/* Number of blocks */
  sldrtex_dashboard_M->Sizes.numBlockIO = (4);/* Number of block outputs */
  sldrtex_dashboard_M->Sizes.numBlockPrms = (9);/* Sum of parameter "widths" */
  return sldrtex_dashboard_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
