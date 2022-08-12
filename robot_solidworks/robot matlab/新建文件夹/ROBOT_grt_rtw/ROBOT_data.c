/*
 * ROBOT_data.c
 *
 * Code generation for model "ROBOT".
 *
 * Model version              : 1.2
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Sat Feb 03 21:08:40 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ROBOT.h"
#include "ROBOT_private.h"

/* Block parameters (auto storage) */
P_ROBOT_T ROBOT_P = {
  45.0,                                /* Variable: a
                                        * Referenced by: '<Root>/Constant22'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant1'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S1>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S16>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant10'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S16>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S17>/Constant'
                                        */
  -180.0,                              /* Expression: -180
                                        * Referenced by: '<Root>/Constant11'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S17>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S19>/Constant'
                                        */
  180.0,                               /* Expression: 180
                                        * Referenced by: '<Root>/Constant12'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S19>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
                                        */
  -90.0,                               /* Expression: -90
                                        * Referenced by: '<Root>/Constant13'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S2>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant'
                                        */
  90.0,                                /* Expression: 90
                                        * Referenced by: '<Root>/Constant14'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S3>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant15'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S4>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant'
                                        */
  180.0,                               /* Expression: 180
                                        * Referenced by: '<Root>/Constant16'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S5>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Constant'
                                        */
  90.0,                                /* Expression: 90
                                        * Referenced by: '<Root>/Constant17'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S6>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Constant'
                                        */
  90.0,                                /* Expression: 90
                                        * Referenced by: '<Root>/Constant18'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S7>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S8>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant19'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S8>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant2'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S12>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S9>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant20'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S9>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S10>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant21'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S10>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S11>/Constant'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S11>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S13>/Constant'
                                        */
  -90.0,                               /* Expression: -90
                                        * Referenced by: '<Root>/Constant23'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S13>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S14>/Constant'
                                        */
  -90.0,                               /* Expression: -90
                                        * Referenced by: '<Root>/Constant3'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S14>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S15>/Constant'
                                        */
  180.0,                               /* Expression: 180
                                        * Referenced by: '<Root>/Constant4'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S15>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S23>/Constant'
                                        */
  180.0,                               /* Expression: 180
                                        * Referenced by: '<Root>/Constant5'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S23>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S21>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant6'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S21>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S18>/Constant'
                                        */
  -90.0,                               /* Expression: -90
                                        * Referenced by: '<Root>/Constant7'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S18>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S22>/Constant'
                                        */
  180.0,                               /* Expression: 180
                                        * Referenced by: '<Root>/Constant8'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<S22>/Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S20>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant9'
                                        */
  0.017453292519943295                 /* Expression: pi/180
                                        * Referenced by: '<S20>/Gain'
                                        */
};
