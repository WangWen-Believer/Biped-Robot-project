/*
 * sldrtex_profiling_dt.h
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

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&sldrtex_profiling_B.UniformRandomNumber200x200[0]), 0, 0, 80136
  }
  ,

  { (char_T *)(&sldrtex_profiling_DW.UniformRandomNumber200x200_NextOutput[0]),
    0, 0, 50000 },

  { (char_T *)(&sldrtex_profiling_DW.Blockprofiling_PWORK.LoggedData[0]), 11, 0,
    4 },

  { (char_T *)(&sldrtex_profiling_DW.ExecutionTime_DIMS2), 6, 0, 1 },

  { (char_T *)(&sldrtex_profiling_DW.RandSeed[0]), 7, 0, 50000 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  5U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&sldrtex_profiling_P.UniformRandomNumber200x200_Minimum), 0, 0,
    50005 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  1U,
  rtPTransitions
};

/* [EOF] sldrtex_profiling_dt.h */
