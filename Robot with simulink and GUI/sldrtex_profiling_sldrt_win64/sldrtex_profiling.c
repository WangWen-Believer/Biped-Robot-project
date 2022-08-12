/*
 * sldrtex_profiling.c
 *
 * Code generation for model "sldrtex_profiling".
 *
 * Model version              : 1.71
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Sun Jan 20 22:43:26 2019
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "sldrtex_profiling.h"
#include "sldrtex_profiling_private.h"
#include "sldrtex_profiling_dt.h"

/* list of Simulink Desktop Real-Time timers */
const int SLDRTTimerCount = 2;
const double SLDRTTimers[4] = {
  0.02, 0.0,
  0.1, 0.0,
};

/* Block signals (auto storage) */
B_sldrtex_profiling_T sldrtex_profiling_B;

/* Block states (auto storage) */
DW_sldrtex_profiling_T sldrtex_profiling_DW;

/* Real-time model */
RT_MODEL_sldrtex_profiling_T sldrtex_profiling_M_;
RT_MODEL_sldrtex_profiling_T *const sldrtex_profiling_M = &sldrtex_profiling_M_;
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(sldrtex_profiling_M, 1);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (sldrtex_profiling_M->Timing.TaskCounters.TID[1])++;
  if ((sldrtex_profiling_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [0.1s, 0.0s] */
    sldrtex_profiling_M->Timing.TaskCounters.TID[1] = 0;
  }
}

real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T lo;
  uint32_T hi;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

/* Model output function for TID0 */
void sldrtex_profiling_output0(void)   /* Sample time: [0.02s, 0.0s] */
{
  real_T minV;
  int32_T iU;
  real_T rtb_Matrixmultiply100x100[10000];
  int32_T i;
  int32_T i_0;
  real_T *rtb_UniformRandomNumber100x100_0;

  {                                    /* Sample time: [0.02s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* UniformRandomNumber: '<Root>/Uniform Random Number 100x100' */
  rtb_UniformRandomNumber100x100_0 =
    &sldrtex_profiling_DW.UniformRandomNumber100x100_NextOutput[0];

  /* Product: '<Root>/Matrix multiply 100x100' */
  for (iU = 0; iU < 100; iU++) {
    for (i = 0; i < 100; i++) {
      rtb_Matrixmultiply100x100[i + 100 * iU] = 0.0;
      for (i_0 = 0; i_0 < 100; i_0++) {
        rtb_Matrixmultiply100x100[i + 100 * iU] +=
          rtb_UniformRandomNumber100x100_0[100 * i_0 + i] *
          rtb_UniformRandomNumber100x100_0[100 * iU + i_0];
      }
    }
  }

  /* End of Product: '<Root>/Matrix multiply 100x100' */

  /* MinMax: '<Root>/MinMax 10000 elements' */
  minV = rtb_Matrixmultiply100x100[0];
  for (iU = 0; iU < 9999; iU++) {
    if (!((minV < rtb_Matrixmultiply100x100[iU + 1]) || rtIsNaN
          (rtb_Matrixmultiply100x100[iU + 1]))) {
      minV = rtb_Matrixmultiply100x100[iU + 1];
    }
  }

  sldrtex_profiling_B.MinMax10000elements = minV;

  /* End of MinMax: '<Root>/MinMax 10000 elements' */

  /* S-Function (sldrttet): '<Root>/Execution Time' */
  /* S-Function Block: <Root>/Execution Time */
  {
    RTBIO_DriverIO(INTERNALIO, (IODEVICE) RTBIOTOTALEXECUTIONTIME, IOREAD, 0, 0,
                   &sldrtex_profiling_B.Modelexecutiontime, 0);

    {
      static const int timers[2] = {
        0,
        1,
      };

      RTBIO_DriverIO(INTERNALIO, (IODEVICE) RTBIOTASKEXECUTIONTIME, IOREAD, 2,
                     timers, &sldrtex_profiling_B.Taskexecutiontimes[0], 0);
    }
  }
}

/* Model update function for TID0 */
void sldrtex_profiling_update0(void)   /* Sample time: [0.02s, 0.0s] */
{
  int32_T iU;

  /* Update for UniformRandomNumber: '<Root>/Uniform Random Number 100x100' */
  for (iU = 0; iU < 10000; iU++) {
    sldrtex_profiling_DW.UniformRandomNumber100x100_NextOutput[iU] =
      (sldrtex_profiling_P.UniformRandomNumber100x100_Maximum[iU] -
       sldrtex_profiling_P.UniformRandomNumber100x100_Minimum) *
      rt_urand_Upu32_Yd_f_pw_snf(&sldrtex_profiling_DW.RandSeed_p[iU]) +
      sldrtex_profiling_P.UniformRandomNumber100x100_Minimum;
  }

  /* End of Update for UniformRandomNumber: '<Root>/Uniform Random Number 100x100' */

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++sldrtex_profiling_M->Timing.clockTick0)) {
    ++sldrtex_profiling_M->Timing.clockTickH0;
  }

  sldrtex_profiling_M->Timing.t[0] = sldrtex_profiling_M->Timing.clockTick0 *
    sldrtex_profiling_M->Timing.stepSize0 +
    sldrtex_profiling_M->Timing.clockTickH0 *
    sldrtex_profiling_M->Timing.stepSize0 * 4294967296.0;
}

/* Model output function for TID1 */
void sldrtex_profiling_output1(void)   /* Sample time: [0.1s, 0.0s] */
{
  real_T minV;
  int32_T iU;
  int32_T i;
  int32_T i_0;

  /* UniformRandomNumber: '<Root>/Uniform Random Number 200x200' */
  memcpy(&sldrtex_profiling_B.UniformRandomNumber200x200[0],
         &sldrtex_profiling_DW.UniformRandomNumber200x200_NextOutput[0], 40000U *
         sizeof(real_T));

  /* S-Function (sldrttstamp): '<Root>/Timestamp3' */
  /* S-Function Block: <Root>/Timestamp3 */
  {
    sldrtex_profiling_B.Timestamp3 = sldrt_read_timestamp();
  }

  /* Product: '<Root>/Matrix Mulltiply 200x200' */
  for (iU = 0; iU < 200; iU++) {
    for (i = 0; i < 200; i++) {
      sldrtex_profiling_B.MatrixMulltiply200x200[i + 200 * iU] = 0.0;
      for (i_0 = 0; i_0 < 200; i_0++) {
        sldrtex_profiling_B.MatrixMulltiply200x200[i + 200 * iU] +=
          sldrtex_profiling_B.UniformRandomNumber200x200[200 * i_0 + i] *
          sldrtex_profiling_B.UniformRandomNumber200x200[200 * iU + i_0];
      }
    }
  }

  /* End of Product: '<Root>/Matrix Mulltiply 200x200' */

  /* S-Function (sldrttstamp): '<Root>/Timestamp1' */
  /* S-Function Block: <Root>/Timestamp1 */
  {
    sldrtex_profiling_B.Timestamp1 = sldrt_read_timestamp();
  }

  /* MinMax: '<Root>/MinMax 40000 elements' */
  minV = sldrtex_profiling_B.MatrixMulltiply200x200[0];
  for (iU = 0; iU < 39999; iU++) {
    if (!((minV < sldrtex_profiling_B.MatrixMulltiply200x200[iU + 1]) || rtIsNaN
          (sldrtex_profiling_B.MatrixMulltiply200x200[iU + 1]))) {
      minV = sldrtex_profiling_B.MatrixMulltiply200x200[iU + 1];
    }
  }

  sldrtex_profiling_B.MinMax40000elements = minV;

  /* End of MinMax: '<Root>/MinMax 40000 elements' */

  /* S-Function (sldrttstamp): '<Root>/Timestamp2' */
  /* S-Function Block: <Root>/Timestamp2 */
  {
    sldrtex_profiling_B.Timestamp2 = sldrt_read_timestamp();
  }

  /* Sum: '<Root>/Subtract3' */
  sldrtex_profiling_B.MatrixMultiplyblock = sldrtex_profiling_B.Timestamp1 -
    sldrtex_profiling_B.Timestamp3;

  /* Sum: '<Root>/Subtract1' */
  sldrtex_profiling_B.MinMaxblock = sldrtex_profiling_B.Timestamp2 -
    sldrtex_profiling_B.Timestamp1;
}

/* Model update function for TID1 */
void sldrtex_profiling_update1(void)   /* Sample time: [0.1s, 0.0s] */
{
  int32_T iU;

  /* Update for UniformRandomNumber: '<Root>/Uniform Random Number 200x200' */
  for (iU = 0; iU < 40000; iU++) {
    sldrtex_profiling_DW.UniformRandomNumber200x200_NextOutput[iU] =
      (sldrtex_profiling_P.UniformRandomNumber200x200_Maximum[iU] -
       sldrtex_profiling_P.UniformRandomNumber200x200_Minimum) *
      rt_urand_Upu32_Yd_f_pw_snf(&sldrtex_profiling_DW.RandSeed[iU]) +
      sldrtex_profiling_P.UniformRandomNumber200x200_Minimum;
  }

  /* End of Update for UniformRandomNumber: '<Root>/Uniform Random Number 200x200' */

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++sldrtex_profiling_M->Timing.clockTick1)) {
    ++sldrtex_profiling_M->Timing.clockTickH1;
  }

  sldrtex_profiling_M->Timing.t[1] = sldrtex_profiling_M->Timing.clockTick1 *
    sldrtex_profiling_M->Timing.stepSize1 +
    sldrtex_profiling_M->Timing.clockTickH1 *
    sldrtex_profiling_M->Timing.stepSize1 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void sldrtex_profiling_output(int_T tid)
{
  switch (tid) {
   case 0 :
    sldrtex_profiling_output0();
    break;

   case 1 :
    sldrtex_profiling_output1();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void sldrtex_profiling_update(int_T tid)
{
  switch (tid) {
   case 0 :
    sldrtex_profiling_update0();
    break;

   case 1 :
    sldrtex_profiling_update1();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void sldrtex_profiling_initialize(void)
{
  /* Start for S-Function (sldrttet): '<Root>/Execution Time' */

  /* S-Function Block: <Root>/Execution Time */
  sldrtex_profiling_DW.ExecutionTime_DIMS2 = 2;

  {
    int32_T iU;
    uint32_T tseed;
    int32_T r;
    int32_T t;
    real_T y1;

    /* InitializeConditions for UniformRandomNumber: '<Root>/Uniform Random Number 200x200' */
    for (iU = 0; iU < 40000; iU++) {
      y1 = floor(sldrtex_profiling_P.UniformRandomNumber200x200_Seed);
      if (rtIsNaN(y1) || rtIsInf(y1)) {
        y1 = 0.0;
      } else {
        y1 = fmod(y1, 4.294967296E+9);
      }

      tseed = y1 < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-y1 : (uint32_T)y1;
      r = (int32_T)(tseed >> 16U);
      t = (int32_T)(tseed & 32768U);
      tseed = ((((tseed - ((uint32_T)r << 16U)) + t) << 16U) + t) + r;
      if (tseed < 1U) {
        tseed = 1144108930U;
      } else {
        if (tseed > 2147483646U) {
          tseed = 2147483646U;
        }
      }

      y1 = (sldrtex_profiling_P.UniformRandomNumber200x200_Maximum[iU] -
            sldrtex_profiling_P.UniformRandomNumber200x200_Minimum) *
        rt_urand_Upu32_Yd_f_pw_snf(&tseed) +
        sldrtex_profiling_P.UniformRandomNumber200x200_Minimum;
      sldrtex_profiling_DW.UniformRandomNumber200x200_NextOutput[iU] = y1;
      sldrtex_profiling_DW.RandSeed[iU] = tseed;
    }

    /* End of InitializeConditions for UniformRandomNumber: '<Root>/Uniform Random Number 200x200' */

    /* InitializeConditions for UniformRandomNumber: '<Root>/Uniform Random Number 100x100' */
    for (iU = 0; iU < 10000; iU++) {
      y1 = floor(sldrtex_profiling_P.UniformRandomNumber100x100_Seed);
      if (rtIsNaN(y1) || rtIsInf(y1)) {
        y1 = 0.0;
      } else {
        y1 = fmod(y1, 4.294967296E+9);
      }

      tseed = y1 < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-y1 : (uint32_T)y1;
      r = (int32_T)(tseed >> 16U);
      t = (int32_T)(tseed & 32768U);
      tseed = ((((tseed - ((uint32_T)r << 16U)) + t) << 16U) + t) + r;
      if (tseed < 1U) {
        tseed = 1144108930U;
      } else {
        if (tseed > 2147483646U) {
          tseed = 2147483646U;
        }
      }

      y1 = (sldrtex_profiling_P.UniformRandomNumber100x100_Maximum[iU] -
            sldrtex_profiling_P.UniformRandomNumber100x100_Minimum) *
        rt_urand_Upu32_Yd_f_pw_snf(&tseed) +
        sldrtex_profiling_P.UniformRandomNumber100x100_Minimum;
      sldrtex_profiling_DW.UniformRandomNumber100x100_NextOutput[iU] = y1;
      sldrtex_profiling_DW.RandSeed_p[iU] = tseed;
    }

    /* End of InitializeConditions for UniformRandomNumber: '<Root>/Uniform Random Number 100x100' */
  }
}

/* Model terminate function */
void sldrtex_profiling_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  sldrtex_profiling_output(tid);
}

void MdlUpdate(int_T tid)
{
  sldrtex_profiling_update(tid);
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
  sldrtex_profiling_initialize();
}

void MdlTerminate(void)
{
  sldrtex_profiling_terminate();
}

/* Registration function */
RT_MODEL_sldrtex_profiling_T *sldrtex_profiling(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)sldrtex_profiling_M, 0,
                sizeof(RT_MODEL_sldrtex_profiling_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = sldrtex_profiling_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    sldrtex_profiling_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    sldrtex_profiling_M->Timing.sampleTimes =
      (&sldrtex_profiling_M->Timing.sampleTimesArray[0]);
    sldrtex_profiling_M->Timing.offsetTimes =
      (&sldrtex_profiling_M->Timing.offsetTimesArray[0]);

    /* task periods */
    sldrtex_profiling_M->Timing.sampleTimes[0] = (0.02);
    sldrtex_profiling_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    sldrtex_profiling_M->Timing.offsetTimes[0] = (0.0);
    sldrtex_profiling_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(sldrtex_profiling_M, &sldrtex_profiling_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = sldrtex_profiling_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits =
      sldrtex_profiling_M->Timing.perTaskSampleHitsArray;
    sldrtex_profiling_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    sldrtex_profiling_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(sldrtex_profiling_M, 2.0);
  sldrtex_profiling_M->Timing.stepSize0 = 0.02;
  sldrtex_profiling_M->Timing.stepSize1 = 0.1;

  /* External mode info */
  sldrtex_profiling_M->Sizes.checksums[0] = (1301872827U);
  sldrtex_profiling_M->Sizes.checksums[1] = (3462230155U);
  sldrtex_profiling_M->Sizes.checksums[2] = (1371858433U);
  sldrtex_profiling_M->Sizes.checksums[3] = (2408090048U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    sldrtex_profiling_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(sldrtex_profiling_M->extModeInfo,
      &sldrtex_profiling_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(sldrtex_profiling_M->extModeInfo,
                        sldrtex_profiling_M->Sizes.checksums);
    rteiSetTPtr(sldrtex_profiling_M->extModeInfo, rtmGetTPtr(sldrtex_profiling_M));
  }

  sldrtex_profiling_M->solverInfoPtr = (&sldrtex_profiling_M->solverInfo);
  sldrtex_profiling_M->Timing.stepSize = (0.02);
  rtsiSetFixedStepSize(&sldrtex_profiling_M->solverInfo, 0.02);
  rtsiSetSolverMode(&sldrtex_profiling_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  sldrtex_profiling_M->blockIO = ((void *) &sldrtex_profiling_B);

  {
    int32_T i;
    for (i = 0; i < 40000; i++) {
      sldrtex_profiling_B.UniformRandomNumber200x200[i] = 0.0;
    }

    for (i = 0; i < 40000; i++) {
      sldrtex_profiling_B.MatrixMulltiply200x200[i] = 0.0;
    }

    for (i = 0; i < 128; i++) {
      sldrtex_profiling_B.Taskexecutiontimes[i] = 0.0;
    }

    sldrtex_profiling_B.Timestamp3 = 0.0;
    sldrtex_profiling_B.Timestamp1 = 0.0;
    sldrtex_profiling_B.MinMax40000elements = 0.0;
    sldrtex_profiling_B.Timestamp2 = 0.0;
    sldrtex_profiling_B.MatrixMultiplyblock = 0.0;
    sldrtex_profiling_B.MinMaxblock = 0.0;
    sldrtex_profiling_B.MinMax10000elements = 0.0;
    sldrtex_profiling_B.Modelexecutiontime = 0.0;
  }

  /* parameters */
  sldrtex_profiling_M->defaultParam = ((real_T *)&sldrtex_profiling_P);

  /* states (dwork) */
  sldrtex_profiling_M->dwork = ((void *) &sldrtex_profiling_DW);
  (void) memset((void *)&sldrtex_profiling_DW, 0,
                sizeof(DW_sldrtex_profiling_T));

  {
    int32_T i;
    for (i = 0; i < 40000; i++) {
      sldrtex_profiling_DW.UniformRandomNumber200x200_NextOutput[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 10000; i++) {
      sldrtex_profiling_DW.UniformRandomNumber100x100_NextOutput[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    sldrtex_profiling_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  sldrtex_profiling_M->Sizes.numContStates = (0);/* Number of continuous states */
  sldrtex_profiling_M->Sizes.numY = (0);/* Number of model outputs */
  sldrtex_profiling_M->Sizes.numU = (0);/* Number of model inputs */
  sldrtex_profiling_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  sldrtex_profiling_M->Sizes.numSampTimes = (2);/* Number of sample times */
  sldrtex_profiling_M->Sizes.numBlocks = (16);/* Number of blocks */
  sldrtex_profiling_M->Sizes.numBlockIO = (11);/* Number of block outputs */
  sldrtex_profiling_M->Sizes.numBlockPrms = (50005);/* Sum of parameter "widths" */
  return sldrtex_profiling_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
