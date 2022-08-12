/*
 * ROBOT.h
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

#ifndef RTW_HEADER_ROBOT_h_
#define RTW_HEADER_ROBOT_h_
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef ROBOT_COMMON_INCLUDES_
# define ROBOT_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#include "nesl_rtw.h"
#include "ROBOT_2da83c1f_1_gateway.h"
#endif                                 /* ROBOT_COMMON_INCLUDES_ */

#include "ROBOT_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T Gain;                         /* '<S1>/Gain' */
  real_T Gain_f;                       /* '<S16>/Gain' */
  real_T Gain_c;                       /* '<S17>/Gain' */
  real_T Gain_l;                       /* '<S19>/Gain' */
  real_T Gain_h;                       /* '<S2>/Gain' */
  real_T Gain_o;                       /* '<S3>/Gain' */
  real_T Gain_ce;                      /* '<S4>/Gain' */
  real_T Gain_d;                       /* '<S5>/Gain' */
  real_T Gain_ho;                      /* '<S6>/Gain' */
  real_T Gain_f1;                      /* '<S7>/Gain' */
  real_T Gain_i;                       /* '<S8>/Gain' */
  real_T Gain_j;                       /* '<S12>/Gain' */
  real_T Gain_lg;                      /* '<S9>/Gain' */
  real_T Gain_dz;                      /* '<S10>/Gain' */
  real_T Gain_n;                       /* '<S11>/Gain' */
  real_T Gain_ox;                      /* '<S13>/Gain' */
  real_T Gain_cl;                      /* '<S14>/Gain' */
  real_T Gain_fa;                      /* '<S15>/Gain' */
  real_T Gain_k;                       /* '<S23>/Gain' */
  real_T Gain_m;                       /* '<S21>/Gain' */
  real_T Gain_im;                      /* '<S18>/Gain' */
  real_T Gain_a;                       /* '<S22>/Gain' */
  real_T Gain_dw;                      /* '<S20>/Gain' */
  real_T INPUT_21_1_1[4];              /* '<S123>/INPUT_21_1_1' */
  real_T INPUT_15_1_1[4];              /* '<S123>/INPUT_15_1_1' */
  real_T INPUT_17_1_1[4];              /* '<S123>/INPUT_17_1_1' */
  real_T INPUT_8_1_1[4];               /* '<S123>/INPUT_8_1_1' */
  real_T INPUT_14_1_1[4];              /* '<S123>/INPUT_14_1_1' */
  real_T INPUT_22_1_1[4];              /* '<S123>/INPUT_22_1_1' */
  real_T INPUT_1_1_1[4];               /* '<S123>/INPUT_1_1_1' */
  real_T INPUT_20_1_1[4];              /* '<S123>/INPUT_20_1_1' */
  real_T INPUT_11_1_1[4];              /* '<S123>/INPUT_11_1_1' */
  real_T INPUT_18_1_1[4];              /* '<S123>/INPUT_18_1_1' */
  real_T INPUT_23_1_1[4];              /* '<S123>/INPUT_23_1_1' */
  real_T INPUT_13_1_1[4];              /* '<S123>/INPUT_13_1_1' */
  real_T INPUT_12_1_1[4];              /* '<S123>/INPUT_12_1_1' */
  real_T INPUT_7_1_1[4];               /* '<S123>/INPUT_7_1_1' */
  real_T INPUT_2_1_1[4];               /* '<S123>/INPUT_2_1_1' */
  real_T INPUT_16_1_1[4];              /* '<S123>/INPUT_16_1_1' */
  real_T INPUT_3_1_1[4];               /* '<S123>/INPUT_3_1_1' */
  real_T INPUT_4_1_1[4];               /* '<S123>/INPUT_4_1_1' */
  real_T INPUT_5_1_1[4];               /* '<S123>/INPUT_5_1_1' */
  real_T INPUT_6_1_1[4];               /* '<S123>/INPUT_6_1_1' */
  real_T INPUT_9_1_1[4];               /* '<S123>/INPUT_9_1_1' */
  real_T INPUT_10_1_1[4];              /* '<S123>/INPUT_10_1_1' */
  real_T INPUT_19_1_1[4];              /* '<S123>/INPUT_19_1_1' */
} B_ROBOT_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T INPUT_21_1_1_discrete[2];     /* '<S123>/INPUT_21_1_1' */
  real_T INPUT_15_1_1_discrete[2];     /* '<S123>/INPUT_15_1_1' */
  real_T INPUT_17_1_1_discrete[2];     /* '<S123>/INPUT_17_1_1' */
  real_T INPUT_8_1_1_discrete[2];      /* '<S123>/INPUT_8_1_1' */
  real_T INPUT_14_1_1_discrete[2];     /* '<S123>/INPUT_14_1_1' */
  real_T INPUT_22_1_1_discrete[2];     /* '<S123>/INPUT_22_1_1' */
  real_T INPUT_1_1_1_discrete[2];      /* '<S123>/INPUT_1_1_1' */
  real_T INPUT_20_1_1_discrete[2];     /* '<S123>/INPUT_20_1_1' */
  real_T INPUT_11_1_1_discrete[2];     /* '<S123>/INPUT_11_1_1' */
  real_T INPUT_18_1_1_discrete[2];     /* '<S123>/INPUT_18_1_1' */
  real_T INPUT_23_1_1_discrete[2];     /* '<S123>/INPUT_23_1_1' */
  real_T INPUT_13_1_1_discrete[2];     /* '<S123>/INPUT_13_1_1' */
  real_T INPUT_12_1_1_discrete[2];     /* '<S123>/INPUT_12_1_1' */
  real_T INPUT_7_1_1_discrete[2];      /* '<S123>/INPUT_7_1_1' */
  real_T INPUT_2_1_1_discrete[2];      /* '<S123>/INPUT_2_1_1' */
  real_T INPUT_16_1_1_discrete[2];     /* '<S123>/INPUT_16_1_1' */
  real_T INPUT_3_1_1_discrete[2];      /* '<S123>/INPUT_3_1_1' */
  real_T INPUT_4_1_1_discrete[2];      /* '<S123>/INPUT_4_1_1' */
  real_T INPUT_5_1_1_discrete[2];      /* '<S123>/INPUT_5_1_1' */
  real_T INPUT_6_1_1_discrete[2];      /* '<S123>/INPUT_6_1_1' */
  real_T INPUT_9_1_1_discrete[2];      /* '<S123>/INPUT_9_1_1' */
  real_T INPUT_10_1_1_discrete[2];     /* '<S123>/INPUT_10_1_1' */
  real_T INPUT_19_1_1_discrete[2];     /* '<S123>/INPUT_19_1_1' */
  void* SINK_1_Simulator;              /* '<S123>/SINK_1' */
  void* SINK_1_SimulationData;         /* '<S123>/SINK_1' */
  void* SINK_1_DiagnosticManager;      /* '<S123>/SINK_1' */
  void* SINK_1_Logger;                 /* '<S123>/SINK_1' */
  void* SINK_1_SampleTimeIdx;          /* '<S123>/SINK_1' */
  void* STATE_1_Simulator;             /* '<S123>/STATE_1' */
  void* STATE_1_SimulationData;        /* '<S123>/STATE_1' */
  void* STATE_1_DiagnosticManager;     /* '<S123>/STATE_1' */
  void* STATE_1_Logger;                /* '<S123>/STATE_1' */
  void* STATE_1_SampleTimeIdx;         /* '<S123>/STATE_1' */
  boolean_T SINK_1_CallSimulatorOutput;/* '<S123>/SINK_1' */
  boolean_T STATE_1_CallSimulatorOutput;/* '<S123>/STATE_1' */
} DW_ROBOT_T;

/* Parameters (auto storage) */
struct P_ROBOT_T_ {
  real_T a;                            /* Variable: a
                                        * Referenced by: '<Root>/Constant22'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Gain_Gain;                    /* Expression: pi/180
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T Constant_Value_d;             /* Expression: 0
                                        * Referenced by: '<S16>/Constant'
                                        */
  real_T Constant10_Value;             /* Expression: 0
                                        * Referenced by: '<Root>/Constant10'
                                        */
  real_T Gain_Gain_c;                  /* Expression: pi/180
                                        * Referenced by: '<S16>/Gain'
                                        */
  real_T Constant_Value_g;             /* Expression: 0
                                        * Referenced by: '<S17>/Constant'
                                        */
  real_T Constant11_Value;             /* Expression: -180
                                        * Referenced by: '<Root>/Constant11'
                                        */
  real_T Gain_Gain_h;                  /* Expression: pi/180
                                        * Referenced by: '<S17>/Gain'
                                        */
  real_T Constant_Value_gd;            /* Expression: 0
                                        * Referenced by: '<S19>/Constant'
                                        */
  real_T Constant12_Value;             /* Expression: 180
                                        * Referenced by: '<Root>/Constant12'
                                        */
  real_T Gain_Gain_m;                  /* Expression: pi/180
                                        * Referenced by: '<S19>/Gain'
                                        */
  real_T Constant_Value_c;             /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Constant13_Value;             /* Expression: -90
                                        * Referenced by: '<Root>/Constant13'
                                        */
  real_T Gain_Gain_o;                  /* Expression: pi/180
                                        * Referenced by: '<S2>/Gain'
                                        */
  real_T Constant_Value_j;             /* Expression: 0
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T Constant14_Value;             /* Expression: 90
                                        * Referenced by: '<Root>/Constant14'
                                        */
  real_T Gain_Gain_k;                  /* Expression: pi/180
                                        * Referenced by: '<S3>/Gain'
                                        */
  real_T Constant_Value_l;             /* Expression: 0
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Constant15_Value;             /* Expression: 0
                                        * Referenced by: '<Root>/Constant15'
                                        */
  real_T Gain_Gain_g;                  /* Expression: pi/180
                                        * Referenced by: '<S4>/Gain'
                                        */
  real_T Constant_Value_a;             /* Expression: 0
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T Constant16_Value;             /* Expression: 180
                                        * Referenced by: '<Root>/Constant16'
                                        */
  real_T Gain_Gain_g5;                 /* Expression: pi/180
                                        * Referenced by: '<S5>/Gain'
                                        */
  real_T Constant_Value_h;             /* Expression: 0
                                        * Referenced by: '<S6>/Constant'
                                        */
  real_T Constant17_Value;             /* Expression: 90
                                        * Referenced by: '<Root>/Constant17'
                                        */
  real_T Gain_Gain_gm;                 /* Expression: pi/180
                                        * Referenced by: '<S6>/Gain'
                                        */
  real_T Constant_Value_gz;            /* Expression: 0
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Constant18_Value;             /* Expression: 90
                                        * Referenced by: '<Root>/Constant18'
                                        */
  real_T Gain_Gain_kc;                 /* Expression: pi/180
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T Constant_Value_p;             /* Expression: 0
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Constant19_Value;             /* Expression: 0
                                        * Referenced by: '<Root>/Constant19'
                                        */
  real_T Gain_Gain_j;                  /* Expression: pi/180
                                        * Referenced by: '<S8>/Gain'
                                        */
  real_T Constant_Value_m;             /* Expression: 0
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T Gain_Gain_n;                  /* Expression: pi/180
                                        * Referenced by: '<S12>/Gain'
                                        */
  real_T Constant_Value_b;             /* Expression: 0
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Constant20_Value;             /* Expression: 0
                                        * Referenced by: '<Root>/Constant20'
                                        */
  real_T Gain_Gain_ma;                 /* Expression: pi/180
                                        * Referenced by: '<S9>/Gain'
                                        */
  real_T Constant_Value_cb;            /* Expression: 0
                                        * Referenced by: '<S10>/Constant'
                                        */
  real_T Constant21_Value;             /* Expression: 0
                                        * Referenced by: '<Root>/Constant21'
                                        */
  real_T Gain_Gain_l;                  /* Expression: pi/180
                                        * Referenced by: '<S10>/Gain'
                                        */
  real_T Constant_Value_bj;            /* Expression: 0
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T Gain_Gain_ov;                 /* Expression: pi/180
                                        * Referenced by: '<S11>/Gain'
                                        */
  real_T Constant_Value_f;             /* Expression: 0
                                        * Referenced by: '<S13>/Constant'
                                        */
  real_T Constant23_Value;             /* Expression: -90
                                        * Referenced by: '<Root>/Constant23'
                                        */
  real_T Gain_Gain_gd;                 /* Expression: pi/180
                                        * Referenced by: '<S13>/Gain'
                                        */
  real_T Constant_Value_ar;            /* Expression: 0
                                        * Referenced by: '<S14>/Constant'
                                        */
  real_T Constant3_Value;              /* Expression: -90
                                        * Referenced by: '<Root>/Constant3'
                                        */
  real_T Gain_Gain_kl;                 /* Expression: pi/180
                                        * Referenced by: '<S14>/Gain'
                                        */
  real_T Constant_Value_fd;            /* Expression: 0
                                        * Referenced by: '<S15>/Constant'
                                        */
  real_T Constant4_Value;              /* Expression: 180
                                        * Referenced by: '<Root>/Constant4'
                                        */
  real_T Gain_Gain_d;                  /* Expression: pi/180
                                        * Referenced by: '<S15>/Gain'
                                        */
  real_T Constant_Value_n;             /* Expression: 0
                                        * Referenced by: '<S23>/Constant'
                                        */
  real_T Constant5_Value;              /* Expression: 180
                                        * Referenced by: '<Root>/Constant5'
                                        */
  real_T Gain_Gain_dq;                 /* Expression: pi/180
                                        * Referenced by: '<S23>/Gain'
                                        */
  real_T Constant_Value_ng;            /* Expression: 0
                                        * Referenced by: '<S21>/Constant'
                                        */
  real_T Constant6_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant6'
                                        */
  real_T Gain_Gain_e;                  /* Expression: pi/180
                                        * Referenced by: '<S21>/Gain'
                                        */
  real_T Constant_Value_ad;            /* Expression: 0
                                        * Referenced by: '<S18>/Constant'
                                        */
  real_T Constant7_Value;              /* Expression: -90
                                        * Referenced by: '<Root>/Constant7'
                                        */
  real_T Gain_Gain_a;                  /* Expression: pi/180
                                        * Referenced by: '<S18>/Gain'
                                        */
  real_T Constant_Value_no;            /* Expression: 0
                                        * Referenced by: '<S22>/Constant'
                                        */
  real_T Constant8_Value;              /* Expression: 180
                                        * Referenced by: '<Root>/Constant8'
                                        */
  real_T Gain_Gain_f;                  /* Expression: pi/180
                                        * Referenced by: '<S22>/Gain'
                                        */
  real_T Constant_Value_pw;            /* Expression: 0
                                        * Referenced by: '<S20>/Constant'
                                        */
  real_T Constant9_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant9'
                                        */
  real_T Gain_Gain_p;                  /* Expression: pi/180
                                        * Referenced by: '<S20>/Gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ROBOT_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_ROBOT_T ROBOT_P;

/* Block signals (auto storage) */
extern B_ROBOT_T ROBOT_B;

/* Block states (auto storage) */
extern DW_ROBOT_T ROBOT_DW;

/* Model entry point functions */
extern void ROBOT_initialize(void);
extern void ROBOT_step(void);
extern void ROBOT_terminate(void);

/* Real-time Model object */
extern RT_MODEL_ROBOT_T *const ROBOT_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ROBOT'
 * '<S1>'   : 'ROBOT/POSITION 1'
 * '<S2>'   : 'ROBOT/POSITION 10'
 * '<S3>'   : 'ROBOT/POSITION 11'
 * '<S4>'   : 'ROBOT/POSITION 12'
 * '<S5>'   : 'ROBOT/POSITION 13'
 * '<S6>'   : 'ROBOT/POSITION 14'
 * '<S7>'   : 'ROBOT/POSITION 15'
 * '<S8>'   : 'ROBOT/POSITION 16'
 * '<S9>'   : 'ROBOT/POSITION 17'
 * '<S10>'  : 'ROBOT/POSITION 18'
 * '<S11>'  : 'ROBOT/POSITION 19'
 * '<S12>'  : 'ROBOT/POSITION 2'
 * '<S13>'  : 'ROBOT/POSITION 20'
 * '<S14>'  : 'ROBOT/POSITION 3'
 * '<S15>'  : 'ROBOT/POSITION 4'
 * '<S16>'  : 'ROBOT/POSITION 5'
 * '<S17>'  : 'ROBOT/POSITION 6'
 * '<S18>'  : 'ROBOT/POSITION 7'
 * '<S19>'  : 'ROBOT/POSITION 8'
 * '<S20>'  : 'ROBOT/POSITION 9'
 * '<S21>'  : 'ROBOT/POSITION1'
 * '<S22>'  : 'ROBOT/POSITION2'
 * '<S23>'  : 'ROBOT/POSITION5'
 * '<S24>'  : 'ROBOT/Solver Configuration'
 * '<S25>'  : 'ROBOT/back_batter_1_RIGID'
 * '<S26>'  : 'ROBOT/back_of_batter_1_RIGID'
 * '<S27>'  : 'ROBOT/body_1_1_RIGID'
 * '<S28>'  : 'ROBOT/bottom_left_2_RIGID'
 * '<S29>'  : 'ROBOT/bottom_right_1_RIGID'
 * '<S30>'  : 'ROBOT/buttocks_1_RIGID'
 * '<S31>'  : 'ROBOT/ear_left_1_RIGID'
 * '<S32>'  : 'ROBOT/ear_left_2_1_RIGID'
 * '<S33>'  : 'ROBOT/ear_left_2_2_RIGID'
 * '<S34>'  : 'ROBOT/ear_right_1_1_RIGID'
 * '<S35>'  : 'ROBOT/face_1_1_RIGID'
 * '<S36>'  : 'ROBOT/face_1_RIGID'
 * '<S37>'  : 'ROBOT/hand_1_RIGID'
 * '<S38>'  : 'ROBOT/hand_right_1_RIGID'
 * '<S39>'  : 'ROBOT/left_foot_1_RIGID'
 * '<S40>'  : 'ROBOT/left_foot_cover_1_RIGID'
 * '<S41>'  : 'ROBOT/little_servo_1_RIGID'
 * '<S42>'  : 'ROBOT/middle_head_1_RIGID'
 * '<S43>'  : 'ROBOT/neck_1_1_RIGID'
 * '<S44>'  : 'ROBOT/neck_2_1_RIGID'
 * '<S45>'  : 'ROBOT/neck_3_1_RIGID'
 * '<S46>'  : 'ROBOT/right_foot_1_RIGID'
 * '<S47>'  : 'ROBOT/right_foot_cover_1_RIGID'
 * '<S48>'  : 'ROBOT/servo_10_RIGID'
 * '<S49>'  : 'ROBOT/servo_11_RIGID'
 * '<S50>'  : 'ROBOT/servo_12_RIGID'
 * '<S51>'  : 'ROBOT/servo_13_RIGID'
 * '<S52>'  : 'ROBOT/servo_14_RIGID'
 * '<S53>'  : 'ROBOT/servo_15_RIGID'
 * '<S54>'  : 'ROBOT/servo_16_RIGID'
 * '<S55>'  : 'ROBOT/servo_17_RIGID'
 * '<S56>'  : 'ROBOT/servo_18_RIGID'
 * '<S57>'  : 'ROBOT/servo_1_RIGID'
 * '<S58>'  : 'ROBOT/servo_2_RIGID'
 * '<S59>'  : 'ROBOT/servo_3_RIGID'
 * '<S60>'  : 'ROBOT/servo_4_RIGID'
 * '<S61>'  : 'ROBOT/servo_5_RIGID'
 * '<S62>'  : 'ROBOT/servo_6_RIGID'
 * '<S63>'  : 'ROBOT/servo_8_RIGID'
 * '<S64>'  : 'ROBOT/servo_9_RIGID'
 * '<S65>'  : 'ROBOT/shank_left_1_RIGID'
 * '<S66>'  : 'ROBOT/shank_right_1_RIGID'
 * '<S67>'  : 'ROBOT/sholder_righr_1_RIGID'
 * '<S68>'  : 'ROBOT/shoulder_left_1_1_RIGID'
 * '<S69>'  : 'ROBOT/shoulder_left_1_RIGID'
 * '<S70>'  : 'ROBOT/shoulder_right_end_1_RIGID'
 * '<S71>'  : 'ROBOT/shoulder_right_middle_1_RIGID'
 * '<S72>'  : 'ROBOT/shouler_left_end_1_RIGID'
 * '<S73>'  : 'ROBOT/thigh_1_RIGID'
 * '<S74>'  : 'ROBOT/thigh_2_RIGID'
 * '<S75>'  : 'ROBOT/zhijiao_1_RIGID'
 * '<S76>'  : 'ROBOT/zhijiao_2_RIGID'
 * '<S77>'  : 'ROBOT/POSITION 1/Simulink-PS Converter'
 * '<S78>'  : 'ROBOT/POSITION 1/Simulink-PS Converter/EVAL_KEY'
 * '<S79>'  : 'ROBOT/POSITION 10/Simulink-PS Converter'
 * '<S80>'  : 'ROBOT/POSITION 10/Simulink-PS Converter/EVAL_KEY'
 * '<S81>'  : 'ROBOT/POSITION 11/Simulink-PS Converter'
 * '<S82>'  : 'ROBOT/POSITION 11/Simulink-PS Converter/EVAL_KEY'
 * '<S83>'  : 'ROBOT/POSITION 12/Simulink-PS Converter'
 * '<S84>'  : 'ROBOT/POSITION 12/Simulink-PS Converter/EVAL_KEY'
 * '<S85>'  : 'ROBOT/POSITION 13/Simulink-PS Converter'
 * '<S86>'  : 'ROBOT/POSITION 13/Simulink-PS Converter/EVAL_KEY'
 * '<S87>'  : 'ROBOT/POSITION 14/Simulink-PS Converter'
 * '<S88>'  : 'ROBOT/POSITION 14/Simulink-PS Converter/EVAL_KEY'
 * '<S89>'  : 'ROBOT/POSITION 15/Simulink-PS Converter'
 * '<S90>'  : 'ROBOT/POSITION 15/Simulink-PS Converter/EVAL_KEY'
 * '<S91>'  : 'ROBOT/POSITION 16/Simulink-PS Converter'
 * '<S92>'  : 'ROBOT/POSITION 16/Simulink-PS Converter/EVAL_KEY'
 * '<S93>'  : 'ROBOT/POSITION 17/Simulink-PS Converter'
 * '<S94>'  : 'ROBOT/POSITION 17/Simulink-PS Converter/EVAL_KEY'
 * '<S95>'  : 'ROBOT/POSITION 18/Simulink-PS Converter'
 * '<S96>'  : 'ROBOT/POSITION 18/Simulink-PS Converter/EVAL_KEY'
 * '<S97>'  : 'ROBOT/POSITION 19/Simulink-PS Converter'
 * '<S98>'  : 'ROBOT/POSITION 19/Simulink-PS Converter/EVAL_KEY'
 * '<S99>'  : 'ROBOT/POSITION 2/Simulink-PS Converter'
 * '<S100>' : 'ROBOT/POSITION 2/Simulink-PS Converter/EVAL_KEY'
 * '<S101>' : 'ROBOT/POSITION 20/Simulink-PS Converter'
 * '<S102>' : 'ROBOT/POSITION 20/Simulink-PS Converter/EVAL_KEY'
 * '<S103>' : 'ROBOT/POSITION 3/Simulink-PS Converter'
 * '<S104>' : 'ROBOT/POSITION 3/Simulink-PS Converter/EVAL_KEY'
 * '<S105>' : 'ROBOT/POSITION 4/Simulink-PS Converter'
 * '<S106>' : 'ROBOT/POSITION 4/Simulink-PS Converter/EVAL_KEY'
 * '<S107>' : 'ROBOT/POSITION 5/Simulink-PS Converter'
 * '<S108>' : 'ROBOT/POSITION 5/Simulink-PS Converter/EVAL_KEY'
 * '<S109>' : 'ROBOT/POSITION 6/Simulink-PS Converter'
 * '<S110>' : 'ROBOT/POSITION 6/Simulink-PS Converter/EVAL_KEY'
 * '<S111>' : 'ROBOT/POSITION 7/Simulink-PS Converter'
 * '<S112>' : 'ROBOT/POSITION 7/Simulink-PS Converter/EVAL_KEY'
 * '<S113>' : 'ROBOT/POSITION 8/Simulink-PS Converter'
 * '<S114>' : 'ROBOT/POSITION 8/Simulink-PS Converter/EVAL_KEY'
 * '<S115>' : 'ROBOT/POSITION 9/Simulink-PS Converter'
 * '<S116>' : 'ROBOT/POSITION 9/Simulink-PS Converter/EVAL_KEY'
 * '<S117>' : 'ROBOT/POSITION1/Simulink-PS Converter'
 * '<S118>' : 'ROBOT/POSITION1/Simulink-PS Converter/EVAL_KEY'
 * '<S119>' : 'ROBOT/POSITION2/Simulink-PS Converter'
 * '<S120>' : 'ROBOT/POSITION2/Simulink-PS Converter/EVAL_KEY'
 * '<S121>' : 'ROBOT/POSITION5/Simulink-PS Converter'
 * '<S122>' : 'ROBOT/POSITION5/Simulink-PS Converter/EVAL_KEY'
 * '<S123>' : 'ROBOT/Solver Configuration/EVAL_KEY'
 * '<S124>' : 'ROBOT/body_1_1_RIGID/body_1_sldasm_Part_1_1_RIGID'
 * '<S125>' : 'ROBOT/body_1_1_RIGID/body_1_sldasm_Part_2_1_RIGID'
 * '<S126>' : 'ROBOT/body_1_1_RIGID/body_1_sldasm_Part_3_1_RIGID'
 * '<S127>' : 'ROBOT/body_1_1_RIGID/body_1_sldasm_Part_4_1_RIGID'
 * '<S128>' : 'ROBOT/body_1_1_RIGID/body_1_sldasm_Part_5_1_RIGID'
 * '<S129>' : 'ROBOT/body_1_1_RIGID/body_1_sldasm_Part_6_1_RIGID'
 * '<S130>' : 'ROBOT/body_1_1_RIGID/body_1_sldasm_Part_7_1_RIGID'
 * '<S131>' : 'ROBOT/body_1_1_RIGID/body_1_sldasm_Part_8_1_RIGID'
 * '<S132>' : 'ROBOT/bottom_left_2_RIGID/bottom_left_sldasm_Part_1_1_RIGID'
 * '<S133>' : 'ROBOT/bottom_right_1_RIGID/bottom_right_sldasm_Part_1_1_RIGID'
 * '<S134>' : 'ROBOT/ear_left_1_RIGID/ear_left_sldasm_Part_1_1_RIGID'
 * '<S135>' : 'ROBOT/ear_left_2_1_RIGID/ear_left_2_sldasm_Part_1_1_RIGID'
 * '<S136>' : 'ROBOT/ear_left_2_2_RIGID/ear_left_2_sldasm_Part_1_1_RIGID'
 * '<S137>' : 'ROBOT/ear_right_1_1_RIGID/ear_right_1_sldasm_Part_1_1_RIGID'
 * '<S138>' : 'ROBOT/face_1_1_RIGID/face_1_sldasm_Part_1_1_RIGID'
 * '<S139>' : 'ROBOT/face_1_RIGID/face_sldasm_Part_1_1_RIGID'
 * '<S140>' : 'ROBOT/hand_1_RIGID/hand_sldasm_Part_1_1_RIGID'
 * '<S141>' : 'ROBOT/hand_right_1_RIGID/hand_right_sldasm_Part_1_1_RIGID'
 * '<S142>' : 'ROBOT/left_foot_1_RIGID/left_foot_sldasm_Part_1_1_RIGID'
 * '<S143>' : 'ROBOT/left_foot_1_RIGID/left_foot_sldasm_Part_2_1_RIGID'
 * '<S144>' : 'ROBOT/left_foot_cover_1_RIGID/left_foot_cover_sldasm_Part_1_1_RIGID'
 * '<S145>' : 'ROBOT/left_foot_cover_1_RIGID/left_foot_cover_sldasm_Part_2_1_RIGID'
 * '<S146>' : 'ROBOT/left_foot_cover_1_RIGID/left_foot_cover_sldasm_Part_3_1_RIGID'
 * '<S147>' : 'ROBOT/little_servo_1_RIGID/little_servo_sldasm_Part_1_1_RIGID'
 * '<S148>' : 'ROBOT/middle_head_1_RIGID/middle_head_sldasm_Part_1_1_RIGID'
 * '<S149>' : 'ROBOT/neck_1_1_RIGID/neck_1_sldasm_Part_1_1_RIGID'
 * '<S150>' : 'ROBOT/neck_2_1_RIGID/neck_2_sldasm_Part_1_1_RIGID'
 * '<S151>' : 'ROBOT/neck_3_1_RIGID/neck_3_sldasm_Part_1_1_RIGID'
 * '<S152>' : 'ROBOT/neck_3_1_RIGID/neck_3_sldasm_Part_1_2_RIGID'
 * '<S153>' : 'ROBOT/neck_3_1_RIGID/neck_3_sldasm_Part_2_1_RIGID'
 * '<S154>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_10_1_RIGID'
 * '<S155>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_11_1_RIGID'
 * '<S156>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_1_1_RIGID'
 * '<S157>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_2_1_RIGID'
 * '<S158>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_3_1_RIGID'
 * '<S159>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_4_1_RIGID'
 * '<S160>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_5_1_RIGID'
 * '<S161>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_6_1_RIGID'
 * '<S162>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_7_1_RIGID'
 * '<S163>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_8_1_RIGID'
 * '<S164>' : 'ROBOT/right_foot_1_RIGID/right_foot_sldasm_Part_9_1_RIGID'
 * '<S165>' : 'ROBOT/right_foot_cover_1_RIGID/right_foot_cover_sldasm_Part_1_1_RIGID'
 * '<S166>' : 'ROBOT/right_foot_cover_1_RIGID/right_foot_cover_sldasm_Part_2_1_RIGID'
 * '<S167>' : 'ROBOT/right_foot_cover_1_RIGID/right_foot_cover_sldasm_Part_3_1_RIGID'
 * '<S168>' : 'ROBOT/servo_10_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S169>' : 'ROBOT/servo_11_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S170>' : 'ROBOT/servo_12_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S171>' : 'ROBOT/servo_13_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S172>' : 'ROBOT/servo_14_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S173>' : 'ROBOT/servo_15_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S174>' : 'ROBOT/servo_16_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S175>' : 'ROBOT/servo_17_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S176>' : 'ROBOT/servo_18_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S177>' : 'ROBOT/servo_1_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S178>' : 'ROBOT/servo_2_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S179>' : 'ROBOT/servo_3_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S180>' : 'ROBOT/servo_4_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S181>' : 'ROBOT/servo_5_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S182>' : 'ROBOT/servo_6_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S183>' : 'ROBOT/servo_8_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S184>' : 'ROBOT/servo_9_RIGID/servo_sldasm_Part_1_1_RIGID'
 * '<S185>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_10_1_RIGID'
 * '<S186>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_11_1_RIGID'
 * '<S187>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_12_1_RIGID'
 * '<S188>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_13_1_RIGID'
 * '<S189>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_14_1_RIGID'
 * '<S190>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_1_1_RIGID'
 * '<S191>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_2_1_RIGID'
 * '<S192>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_3_1_RIGID'
 * '<S193>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_4_1_RIGID'
 * '<S194>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_5_1_RIGID'
 * '<S195>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_6_1_RIGID'
 * '<S196>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_7_1_RIGID'
 * '<S197>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_8_1_RIGID'
 * '<S198>' : 'ROBOT/shank_left_1_RIGID/shank_left_sldasm_Part_9_1_RIGID'
 * '<S199>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_10_1_RIGID'
 * '<S200>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_11_1_RIGID'
 * '<S201>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_12_1_RIGID'
 * '<S202>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_13_1_RIGID'
 * '<S203>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_14_1_RIGID'
 * '<S204>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_15_1_RIGID'
 * '<S205>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_16_1_RIGID'
 * '<S206>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_17_1_RIGID'
 * '<S207>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_18_1_RIGID'
 * '<S208>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_19_1_RIGID'
 * '<S209>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_1_1_RIGID'
 * '<S210>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_2_1_RIGID'
 * '<S211>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_3_1_RIGID'
 * '<S212>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_4_1_RIGID'
 * '<S213>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_5_1_RIGID'
 * '<S214>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_6_1_RIGID'
 * '<S215>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_7_1_RIGID'
 * '<S216>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_8_1_RIGID'
 * '<S217>' : 'ROBOT/shank_right_1_RIGID/shank_right_sldasm_Part_9_1_RIGID'
 * '<S218>' : 'ROBOT/sholder_righr_1_RIGID/sholder_righr_sldasm_Part_1_1_RIGID'
 * '<S219>' : 'ROBOT/shoulder_left_1_1_RIGID/shoulder_left_1_sldasm_Part_1_1_RIGID'
 * '<S220>' : 'ROBOT/shoulder_left_1_1_RIGID/shoulder_left_1_sldasm_Part_2_1_RIGID'
 * '<S221>' : 'ROBOT/shoulder_left_1_1_RIGID/shoulder_left_1_sldasm_Part_3_1_RIGID'
 * '<S222>' : 'ROBOT/shoulder_left_1_1_RIGID/shoulder_left_1_sldasm_Part_4_1_RIGID'
 * '<S223>' : 'ROBOT/shoulder_left_1_RIGID/shoulder_left_sldasm_Part_1_1_RIGID'
 * '<S224>' : 'ROBOT/shoulder_right_end_1_RIGID/shoulder_right_end_sldasm_Part_1_1_RIGID'
 * '<S225>' : 'ROBOT/shoulder_right_middle_1_RIGID/shoulder_right_middle_sldasm_Part_1_1_RIGID'
 * '<S226>' : 'ROBOT/shoulder_right_middle_1_RIGID/shoulder_right_middle_sldasm_Part_2_1_RIGID'
 * '<S227>' : 'ROBOT/shoulder_right_middle_1_RIGID/shoulder_right_middle_sldasm_Part_3_1_RIGID'
 * '<S228>' : 'ROBOT/shouler_left_end_1_RIGID/shouler_left_end_sldasm_Part_1_1_RIGID'
 * '<S229>' : 'ROBOT/shouler_left_end_1_RIGID/shouler_left_end_sldasm_Part_2_1_RIGID'
 * '<S230>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_10_1_RIGID'
 * '<S231>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_11_1_RIGID'
 * '<S232>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_12_1_RIGID'
 * '<S233>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_1_1_RIGID'
 * '<S234>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_2_1_RIGID'
 * '<S235>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_3_1_RIGID'
 * '<S236>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_4_1_RIGID'
 * '<S237>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_5_1_RIGID'
 * '<S238>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_6_1_RIGID'
 * '<S239>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_7_1_RIGID'
 * '<S240>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_8_1_RIGID'
 * '<S241>' : 'ROBOT/thigh_1_RIGID/thigh_sldasm_Part_9_1_RIGID'
 * '<S242>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_10_1_RIGID'
 * '<S243>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_11_1_RIGID'
 * '<S244>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_12_1_RIGID'
 * '<S245>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_1_1_RIGID'
 * '<S246>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_2_1_RIGID'
 * '<S247>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_3_1_RIGID'
 * '<S248>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_4_1_RIGID'
 * '<S249>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_5_1_RIGID'
 * '<S250>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_6_1_RIGID'
 * '<S251>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_7_1_RIGID'
 * '<S252>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_8_1_RIGID'
 * '<S253>' : 'ROBOT/thigh_2_RIGID/thigh_sldasm_Part_9_1_RIGID'
 * '<S254>' : 'ROBOT/zhijiao_1_RIGID/zhijiao_sldasm_Part_1_1_RIGID'
 * '<S255>' : 'ROBOT/zhijiao_2_RIGID/zhijiao_sldasm_Part_1_1_RIGID'
 */
#endif                                 /* RTW_HEADER_ROBOT_h_ */
