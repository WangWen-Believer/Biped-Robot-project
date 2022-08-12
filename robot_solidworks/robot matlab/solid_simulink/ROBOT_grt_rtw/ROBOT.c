/*
 * ROBOT.c
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
#include "ROBOT_dt.h"

/* Block signals (auto storage) */
B_ROBOT_T ROBOT_B;

/* Block states (auto storage) */
DW_ROBOT_T ROBOT_DW;

/* Real-time model */
RT_MODEL_ROBOT_T ROBOT_M_;
RT_MODEL_ROBOT_T *const ROBOT_M = &ROBOT_M_;

/* Model step function */
void ROBOT_step(void)
{
  {
    NeslSimulationData *simulationData;
    real_T time;
    boolean_T tmp;
    real_T tmp_0[92];
    int_T tmp_1[24];
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    int32_T tmp_2;
    char *msg;

    /* Gain: '<S1>/Gain' incorporates:
     *  Constant: '<Root>/Constant1'
     *  Constant: '<S1>/Constant'
     *  Sum: '<S1>/Subtract'
     */
    ROBOT_B.Gain = (ROBOT_P.Constant1_Value + ROBOT_P.Constant_Value) *
      ROBOT_P.Gain_Gain;

    /* Gain: '<S16>/Gain' incorporates:
     *  Constant: '<Root>/Constant10'
     *  Constant: '<S16>/Constant'
     *  Sum: '<S16>/Subtract'
     */
    ROBOT_B.Gain_f = (ROBOT_P.Constant10_Value + ROBOT_P.Constant_Value_d) *
      ROBOT_P.Gain_Gain_c;

    /* Gain: '<S17>/Gain' incorporates:
     *  Constant: '<Root>/Constant11'
     *  Constant: '<S17>/Constant'
     *  Sum: '<S17>/Subtract'
     */
    ROBOT_B.Gain_c = (ROBOT_P.Constant11_Value + ROBOT_P.Constant_Value_g) *
      ROBOT_P.Gain_Gain_h;

    /* Gain: '<S19>/Gain' incorporates:
     *  Constant: '<Root>/Constant12'
     *  Constant: '<S19>/Constant'
     *  Sum: '<S19>/Subtract'
     */
    ROBOT_B.Gain_l = (ROBOT_P.Constant12_Value + ROBOT_P.Constant_Value_gd) *
      ROBOT_P.Gain_Gain_m;

    /* Gain: '<S2>/Gain' incorporates:
     *  Constant: '<Root>/Constant13'
     *  Constant: '<S2>/Constant'
     *  Sum: '<S2>/Subtract'
     */
    ROBOT_B.Gain_h = (ROBOT_P.Constant13_Value + ROBOT_P.Constant_Value_c) *
      ROBOT_P.Gain_Gain_o;

    /* Gain: '<S3>/Gain' incorporates:
     *  Constant: '<Root>/Constant14'
     *  Constant: '<S3>/Constant'
     *  Sum: '<S3>/Subtract'
     */
    ROBOT_B.Gain_o = (ROBOT_P.Constant14_Value + ROBOT_P.Constant_Value_j) *
      ROBOT_P.Gain_Gain_k;

    /* Gain: '<S4>/Gain' incorporates:
     *  Constant: '<Root>/Constant15'
     *  Constant: '<S4>/Constant'
     *  Sum: '<S4>/Subtract'
     */
    ROBOT_B.Gain_ce = (ROBOT_P.Constant15_Value + ROBOT_P.Constant_Value_l) *
      ROBOT_P.Gain_Gain_g;

    /* Gain: '<S5>/Gain' incorporates:
     *  Constant: '<Root>/Constant16'
     *  Constant: '<S5>/Constant'
     *  Sum: '<S5>/Subtract'
     */
    ROBOT_B.Gain_d = (ROBOT_P.Constant16_Value + ROBOT_P.Constant_Value_a) *
      ROBOT_P.Gain_Gain_g5;

    /* Gain: '<S6>/Gain' incorporates:
     *  Constant: '<Root>/Constant17'
     *  Constant: '<S6>/Constant'
     *  Sum: '<S6>/Subtract'
     */
    ROBOT_B.Gain_ho = (ROBOT_P.Constant17_Value + ROBOT_P.Constant_Value_h) *
      ROBOT_P.Gain_Gain_gm;

    /* Gain: '<S7>/Gain' incorporates:
     *  Constant: '<Root>/Constant18'
     *  Constant: '<S7>/Constant'
     *  Sum: '<S7>/Subtract'
     */
    ROBOT_B.Gain_f1 = (ROBOT_P.Constant18_Value + ROBOT_P.Constant_Value_gz) *
      ROBOT_P.Gain_Gain_kc;

    /* Gain: '<S8>/Gain' incorporates:
     *  Constant: '<Root>/Constant19'
     *  Constant: '<S8>/Constant'
     *  Sum: '<S8>/Subtract'
     */
    ROBOT_B.Gain_i = (ROBOT_P.Constant19_Value + ROBOT_P.Constant_Value_p) *
      ROBOT_P.Gain_Gain_j;

    /* Gain: '<S12>/Gain' incorporates:
     *  Constant: '<Root>/Constant2'
     *  Constant: '<S12>/Constant'
     *  Sum: '<S12>/Subtract'
     */
    ROBOT_B.Gain_j = (ROBOT_P.Constant2_Value + ROBOT_P.Constant_Value_m) *
      ROBOT_P.Gain_Gain_n;

    /* Gain: '<S9>/Gain' incorporates:
     *  Constant: '<Root>/Constant20'
     *  Constant: '<S9>/Constant'
     *  Sum: '<S9>/Subtract'
     */
    ROBOT_B.Gain_lg = (ROBOT_P.Constant20_Value + ROBOT_P.Constant_Value_b) *
      ROBOT_P.Gain_Gain_ma;

    /* Gain: '<S10>/Gain' incorporates:
     *  Constant: '<Root>/Constant21'
     *  Constant: '<S10>/Constant'
     *  Sum: '<S10>/Subtract'
     */
    ROBOT_B.Gain_dz = (ROBOT_P.Constant21_Value + ROBOT_P.Constant_Value_cb) *
      ROBOT_P.Gain_Gain_l;

    /* Gain: '<S11>/Gain' incorporates:
     *  Constant: '<Root>/Constant22'
     *  Constant: '<S11>/Constant'
     *  Sum: '<S11>/Subtract'
     */
    ROBOT_B.Gain_n = (ROBOT_P.a + ROBOT_P.Constant_Value_bj) *
      ROBOT_P.Gain_Gain_ov;

    /* Gain: '<S13>/Gain' incorporates:
     *  Constant: '<Root>/Constant23'
     *  Constant: '<S13>/Constant'
     *  Sum: '<S13>/Subtract'
     */
    ROBOT_B.Gain_ox = (ROBOT_P.Constant23_Value + ROBOT_P.Constant_Value_f) *
      ROBOT_P.Gain_Gain_gd;

    /* Gain: '<S14>/Gain' incorporates:
     *  Constant: '<Root>/Constant3'
     *  Constant: '<S14>/Constant'
     *  Sum: '<S14>/Subtract'
     */
    ROBOT_B.Gain_cl = (ROBOT_P.Constant3_Value + ROBOT_P.Constant_Value_ar) *
      ROBOT_P.Gain_Gain_kl;

    /* Gain: '<S15>/Gain' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Constant: '<S15>/Constant'
     *  Sum: '<S15>/Subtract'
     */
    ROBOT_B.Gain_fa = (ROBOT_P.Constant4_Value + ROBOT_P.Constant_Value_fd) *
      ROBOT_P.Gain_Gain_d;

    /* Gain: '<S23>/Gain' incorporates:
     *  Constant: '<Root>/Constant5'
     *  Constant: '<S23>/Constant'
     *  Sum: '<S23>/Subtract'
     */
    ROBOT_B.Gain_k = (ROBOT_P.Constant5_Value + ROBOT_P.Constant_Value_n) *
      ROBOT_P.Gain_Gain_dq;

    /* Gain: '<S21>/Gain' incorporates:
     *  Constant: '<Root>/Constant6'
     *  Constant: '<S21>/Constant'
     *  Sum: '<S21>/Subtract'
     */
    ROBOT_B.Gain_m = (ROBOT_P.Constant6_Value + ROBOT_P.Constant_Value_ng) *
      ROBOT_P.Gain_Gain_e;

    /* Gain: '<S18>/Gain' incorporates:
     *  Constant: '<Root>/Constant7'
     *  Constant: '<S18>/Constant'
     *  Sum: '<S18>/Subtract'
     */
    ROBOT_B.Gain_im = (ROBOT_P.Constant7_Value + ROBOT_P.Constant_Value_ad) *
      ROBOT_P.Gain_Gain_a;

    /* Gain: '<S22>/Gain' incorporates:
     *  Constant: '<Root>/Constant8'
     *  Constant: '<S22>/Constant'
     *  Sum: '<S22>/Subtract'
     */
    ROBOT_B.Gain_a = (ROBOT_P.Constant8_Value + ROBOT_P.Constant_Value_no) *
      ROBOT_P.Gain_Gain_f;

    /* Gain: '<S20>/Gain' incorporates:
     *  Constant: '<Root>/Constant9'
     *  Constant: '<S20>/Constant'
     *  Sum: '<S20>/Subtract'
     */
    ROBOT_B.Gain_dw = (ROBOT_P.Constant9_Value + ROBOT_P.Constant_Value_pw) *
      ROBOT_P.Gain_Gain_p;

    /* SimscapeInputBlock: '<S123>/INPUT_21_1_1' */
    ROBOT_B.INPUT_21_1_1[0] = ROBOT_B.Gain_im;
    ROBOT_B.INPUT_21_1_1[1] = 0.0;
    ROBOT_B.INPUT_21_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_21_1_1_discrete[0] = !(ROBOT_B.INPUT_21_1_1[0] ==
        ROBOT_DW.INPUT_21_1_1_discrete[1]);
      ROBOT_DW.INPUT_21_1_1_discrete[1] = ROBOT_B.INPUT_21_1_1[0];
    }

    ROBOT_B.INPUT_21_1_1[0] = ROBOT_DW.INPUT_21_1_1_discrete[1];
    ROBOT_B.INPUT_21_1_1[3] = ROBOT_DW.INPUT_21_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_21_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_15_1_1' */
    ROBOT_B.INPUT_15_1_1[0] = ROBOT_B.Gain_j;
    ROBOT_B.INPUT_15_1_1[1] = 0.0;
    ROBOT_B.INPUT_15_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_15_1_1_discrete[0] = !(ROBOT_B.INPUT_15_1_1[0] ==
        ROBOT_DW.INPUT_15_1_1_discrete[1]);
      ROBOT_DW.INPUT_15_1_1_discrete[1] = ROBOT_B.INPUT_15_1_1[0];
    }

    ROBOT_B.INPUT_15_1_1[0] = ROBOT_DW.INPUT_15_1_1_discrete[1];
    ROBOT_B.INPUT_15_1_1[3] = ROBOT_DW.INPUT_15_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_15_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_17_1_1' */
    ROBOT_B.INPUT_17_1_1[0] = ROBOT_B.Gain_cl;
    ROBOT_B.INPUT_17_1_1[1] = 0.0;
    ROBOT_B.INPUT_17_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_17_1_1_discrete[0] = !(ROBOT_B.INPUT_17_1_1[0] ==
        ROBOT_DW.INPUT_17_1_1_discrete[1]);
      ROBOT_DW.INPUT_17_1_1_discrete[1] = ROBOT_B.INPUT_17_1_1[0];
    }

    ROBOT_B.INPUT_17_1_1[0] = ROBOT_DW.INPUT_17_1_1_discrete[1];
    ROBOT_B.INPUT_17_1_1[3] = ROBOT_DW.INPUT_17_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_17_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_8_1_1' */
    ROBOT_B.INPUT_8_1_1[0] = ROBOT_B.Gain_d;
    ROBOT_B.INPUT_8_1_1[1] = 0.0;
    ROBOT_B.INPUT_8_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_8_1_1_discrete[0] = !(ROBOT_B.INPUT_8_1_1[0] ==
        ROBOT_DW.INPUT_8_1_1_discrete[1]);
      ROBOT_DW.INPUT_8_1_1_discrete[1] = ROBOT_B.INPUT_8_1_1[0];
    }

    ROBOT_B.INPUT_8_1_1[0] = ROBOT_DW.INPUT_8_1_1_discrete[1];
    ROBOT_B.INPUT_8_1_1[3] = ROBOT_DW.INPUT_8_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_8_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_14_1_1' */
    ROBOT_B.INPUT_14_1_1[0] = ROBOT_B.Gain_n;
    ROBOT_B.INPUT_14_1_1[1] = 0.0;
    ROBOT_B.INPUT_14_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_14_1_1_discrete[0] = !(ROBOT_B.INPUT_14_1_1[0] ==
        ROBOT_DW.INPUT_14_1_1_discrete[1]);
      ROBOT_DW.INPUT_14_1_1_discrete[1] = ROBOT_B.INPUT_14_1_1[0];
    }

    ROBOT_B.INPUT_14_1_1[0] = ROBOT_DW.INPUT_14_1_1_discrete[1];
    ROBOT_B.INPUT_14_1_1[3] = ROBOT_DW.INPUT_14_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_14_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_22_1_1' */
    ROBOT_B.INPUT_22_1_1[0] = ROBOT_B.Gain_l;
    ROBOT_B.INPUT_22_1_1[1] = 0.0;
    ROBOT_B.INPUT_22_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_22_1_1_discrete[0] = !(ROBOT_B.INPUT_22_1_1[0] ==
        ROBOT_DW.INPUT_22_1_1_discrete[1]);
      ROBOT_DW.INPUT_22_1_1_discrete[1] = ROBOT_B.INPUT_22_1_1[0];
    }

    ROBOT_B.INPUT_22_1_1[0] = ROBOT_DW.INPUT_22_1_1_discrete[1];
    ROBOT_B.INPUT_22_1_1[3] = ROBOT_DW.INPUT_22_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_22_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_1_1_1' */
    ROBOT_B.INPUT_1_1_1[0] = ROBOT_B.Gain_m;
    ROBOT_B.INPUT_1_1_1[1] = 0.0;
    ROBOT_B.INPUT_1_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_1_1_1_discrete[0] = !(ROBOT_B.INPUT_1_1_1[0] ==
        ROBOT_DW.INPUT_1_1_1_discrete[1]);
      ROBOT_DW.INPUT_1_1_1_discrete[1] = ROBOT_B.INPUT_1_1_1[0];
    }

    ROBOT_B.INPUT_1_1_1[0] = ROBOT_DW.INPUT_1_1_1_discrete[1];
    ROBOT_B.INPUT_1_1_1[3] = ROBOT_DW.INPUT_1_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_1_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_20_1_1' */
    ROBOT_B.INPUT_20_1_1[0] = ROBOT_B.Gain_c;
    ROBOT_B.INPUT_20_1_1[1] = 0.0;
    ROBOT_B.INPUT_20_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_20_1_1_discrete[0] = !(ROBOT_B.INPUT_20_1_1[0] ==
        ROBOT_DW.INPUT_20_1_1_discrete[1]);
      ROBOT_DW.INPUT_20_1_1_discrete[1] = ROBOT_B.INPUT_20_1_1[0];
    }

    ROBOT_B.INPUT_20_1_1[0] = ROBOT_DW.INPUT_20_1_1_discrete[1];
    ROBOT_B.INPUT_20_1_1[3] = ROBOT_DW.INPUT_20_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_20_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_11_1_1' */
    ROBOT_B.INPUT_11_1_1[0] = ROBOT_B.Gain_i;
    ROBOT_B.INPUT_11_1_1[1] = 0.0;
    ROBOT_B.INPUT_11_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_11_1_1_discrete[0] = !(ROBOT_B.INPUT_11_1_1[0] ==
        ROBOT_DW.INPUT_11_1_1_discrete[1]);
      ROBOT_DW.INPUT_11_1_1_discrete[1] = ROBOT_B.INPUT_11_1_1[0];
    }

    ROBOT_B.INPUT_11_1_1[0] = ROBOT_DW.INPUT_11_1_1_discrete[1];
    ROBOT_B.INPUT_11_1_1[3] = ROBOT_DW.INPUT_11_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_11_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_18_1_1' */
    ROBOT_B.INPUT_18_1_1[0] = ROBOT_B.Gain_fa;
    ROBOT_B.INPUT_18_1_1[1] = 0.0;
    ROBOT_B.INPUT_18_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_18_1_1_discrete[0] = !(ROBOT_B.INPUT_18_1_1[0] ==
        ROBOT_DW.INPUT_18_1_1_discrete[1]);
      ROBOT_DW.INPUT_18_1_1_discrete[1] = ROBOT_B.INPUT_18_1_1[0];
    }

    ROBOT_B.INPUT_18_1_1[0] = ROBOT_DW.INPUT_18_1_1_discrete[1];
    ROBOT_B.INPUT_18_1_1[3] = ROBOT_DW.INPUT_18_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_18_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_23_1_1' */
    ROBOT_B.INPUT_23_1_1[0] = ROBOT_B.Gain_dw;
    ROBOT_B.INPUT_23_1_1[1] = 0.0;
    ROBOT_B.INPUT_23_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_23_1_1_discrete[0] = !(ROBOT_B.INPUT_23_1_1[0] ==
        ROBOT_DW.INPUT_23_1_1_discrete[1]);
      ROBOT_DW.INPUT_23_1_1_discrete[1] = ROBOT_B.INPUT_23_1_1[0];
    }

    ROBOT_B.INPUT_23_1_1[0] = ROBOT_DW.INPUT_23_1_1_discrete[1];
    ROBOT_B.INPUT_23_1_1[3] = ROBOT_DW.INPUT_23_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_23_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_13_1_1' */
    ROBOT_B.INPUT_13_1_1[0] = ROBOT_B.Gain_dz;
    ROBOT_B.INPUT_13_1_1[1] = 0.0;
    ROBOT_B.INPUT_13_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_13_1_1_discrete[0] = !(ROBOT_B.INPUT_13_1_1[0] ==
        ROBOT_DW.INPUT_13_1_1_discrete[1]);
      ROBOT_DW.INPUT_13_1_1_discrete[1] = ROBOT_B.INPUT_13_1_1[0];
    }

    ROBOT_B.INPUT_13_1_1[0] = ROBOT_DW.INPUT_13_1_1_discrete[1];
    ROBOT_B.INPUT_13_1_1[3] = ROBOT_DW.INPUT_13_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_13_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_12_1_1' */
    ROBOT_B.INPUT_12_1_1[0] = ROBOT_B.Gain_lg;
    ROBOT_B.INPUT_12_1_1[1] = 0.0;
    ROBOT_B.INPUT_12_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_12_1_1_discrete[0] = !(ROBOT_B.INPUT_12_1_1[0] ==
        ROBOT_DW.INPUT_12_1_1_discrete[1]);
      ROBOT_DW.INPUT_12_1_1_discrete[1] = ROBOT_B.INPUT_12_1_1[0];
    }

    ROBOT_B.INPUT_12_1_1[0] = ROBOT_DW.INPUT_12_1_1_discrete[1];
    ROBOT_B.INPUT_12_1_1[3] = ROBOT_DW.INPUT_12_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_12_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_7_1_1' */
    ROBOT_B.INPUT_7_1_1[0] = ROBOT_B.Gain_ce;
    ROBOT_B.INPUT_7_1_1[1] = 0.0;
    ROBOT_B.INPUT_7_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_7_1_1_discrete[0] = !(ROBOT_B.INPUT_7_1_1[0] ==
        ROBOT_DW.INPUT_7_1_1_discrete[1]);
      ROBOT_DW.INPUT_7_1_1_discrete[1] = ROBOT_B.INPUT_7_1_1[0];
    }

    ROBOT_B.INPUT_7_1_1[0] = ROBOT_DW.INPUT_7_1_1_discrete[1];
    ROBOT_B.INPUT_7_1_1[3] = ROBOT_DW.INPUT_7_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_7_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_2_1_1' */
    ROBOT_B.INPUT_2_1_1[0] = ROBOT_B.Gain_a;
    ROBOT_B.INPUT_2_1_1[1] = 0.0;
    ROBOT_B.INPUT_2_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_2_1_1_discrete[0] = !(ROBOT_B.INPUT_2_1_1[0] ==
        ROBOT_DW.INPUT_2_1_1_discrete[1]);
      ROBOT_DW.INPUT_2_1_1_discrete[1] = ROBOT_B.INPUT_2_1_1[0];
    }

    ROBOT_B.INPUT_2_1_1[0] = ROBOT_DW.INPUT_2_1_1_discrete[1];
    ROBOT_B.INPUT_2_1_1[3] = ROBOT_DW.INPUT_2_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_2_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_16_1_1' */
    ROBOT_B.INPUT_16_1_1[0] = ROBOT_B.Gain_ox;
    ROBOT_B.INPUT_16_1_1[1] = 0.0;
    ROBOT_B.INPUT_16_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_16_1_1_discrete[0] = !(ROBOT_B.INPUT_16_1_1[0] ==
        ROBOT_DW.INPUT_16_1_1_discrete[1]);
      ROBOT_DW.INPUT_16_1_1_discrete[1] = ROBOT_B.INPUT_16_1_1[0];
    }

    ROBOT_B.INPUT_16_1_1[0] = ROBOT_DW.INPUT_16_1_1_discrete[1];
    ROBOT_B.INPUT_16_1_1[3] = ROBOT_DW.INPUT_16_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_16_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_3_1_1' */
    ROBOT_B.INPUT_3_1_1[0] = ROBOT_B.Gain_k;
    ROBOT_B.INPUT_3_1_1[1] = 0.0;
    ROBOT_B.INPUT_3_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_3_1_1_discrete[0] = !(ROBOT_B.INPUT_3_1_1[0] ==
        ROBOT_DW.INPUT_3_1_1_discrete[1]);
      ROBOT_DW.INPUT_3_1_1_discrete[1] = ROBOT_B.INPUT_3_1_1[0];
    }

    ROBOT_B.INPUT_3_1_1[0] = ROBOT_DW.INPUT_3_1_1_discrete[1];
    ROBOT_B.INPUT_3_1_1[3] = ROBOT_DW.INPUT_3_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_3_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_4_1_1' */
    ROBOT_B.INPUT_4_1_1[0] = ROBOT_B.Gain;
    ROBOT_B.INPUT_4_1_1[1] = 0.0;
    ROBOT_B.INPUT_4_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_4_1_1_discrete[0] = !(ROBOT_B.INPUT_4_1_1[0] ==
        ROBOT_DW.INPUT_4_1_1_discrete[1]);
      ROBOT_DW.INPUT_4_1_1_discrete[1] = ROBOT_B.INPUT_4_1_1[0];
    }

    ROBOT_B.INPUT_4_1_1[0] = ROBOT_DW.INPUT_4_1_1_discrete[1];
    ROBOT_B.INPUT_4_1_1[3] = ROBOT_DW.INPUT_4_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_4_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_5_1_1' */
    ROBOT_B.INPUT_5_1_1[0] = ROBOT_B.Gain_h;
    ROBOT_B.INPUT_5_1_1[1] = 0.0;
    ROBOT_B.INPUT_5_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_5_1_1_discrete[0] = !(ROBOT_B.INPUT_5_1_1[0] ==
        ROBOT_DW.INPUT_5_1_1_discrete[1]);
      ROBOT_DW.INPUT_5_1_1_discrete[1] = ROBOT_B.INPUT_5_1_1[0];
    }

    ROBOT_B.INPUT_5_1_1[0] = ROBOT_DW.INPUT_5_1_1_discrete[1];
    ROBOT_B.INPUT_5_1_1[3] = ROBOT_DW.INPUT_5_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_5_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_6_1_1' */
    ROBOT_B.INPUT_6_1_1[0] = ROBOT_B.Gain_o;
    ROBOT_B.INPUT_6_1_1[1] = 0.0;
    ROBOT_B.INPUT_6_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_6_1_1_discrete[0] = !(ROBOT_B.INPUT_6_1_1[0] ==
        ROBOT_DW.INPUT_6_1_1_discrete[1]);
      ROBOT_DW.INPUT_6_1_1_discrete[1] = ROBOT_B.INPUT_6_1_1[0];
    }

    ROBOT_B.INPUT_6_1_1[0] = ROBOT_DW.INPUT_6_1_1_discrete[1];
    ROBOT_B.INPUT_6_1_1[3] = ROBOT_DW.INPUT_6_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_6_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_9_1_1' */
    ROBOT_B.INPUT_9_1_1[0] = ROBOT_B.Gain_ho;
    ROBOT_B.INPUT_9_1_1[1] = 0.0;
    ROBOT_B.INPUT_9_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_9_1_1_discrete[0] = !(ROBOT_B.INPUT_9_1_1[0] ==
        ROBOT_DW.INPUT_9_1_1_discrete[1]);
      ROBOT_DW.INPUT_9_1_1_discrete[1] = ROBOT_B.INPUT_9_1_1[0];
    }

    ROBOT_B.INPUT_9_1_1[0] = ROBOT_DW.INPUT_9_1_1_discrete[1];
    ROBOT_B.INPUT_9_1_1[3] = ROBOT_DW.INPUT_9_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_9_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_10_1_1' */
    ROBOT_B.INPUT_10_1_1[0] = ROBOT_B.Gain_f1;
    ROBOT_B.INPUT_10_1_1[1] = 0.0;
    ROBOT_B.INPUT_10_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_10_1_1_discrete[0] = !(ROBOT_B.INPUT_10_1_1[0] ==
        ROBOT_DW.INPUT_10_1_1_discrete[1]);
      ROBOT_DW.INPUT_10_1_1_discrete[1] = ROBOT_B.INPUT_10_1_1[0];
    }

    ROBOT_B.INPUT_10_1_1[0] = ROBOT_DW.INPUT_10_1_1_discrete[1];
    ROBOT_B.INPUT_10_1_1[3] = ROBOT_DW.INPUT_10_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_10_1_1' */

    /* SimscapeInputBlock: '<S123>/INPUT_19_1_1' */
    ROBOT_B.INPUT_19_1_1[0] = ROBOT_B.Gain_f;
    ROBOT_B.INPUT_19_1_1[1] = 0.0;
    ROBOT_B.INPUT_19_1_1[2] = 0.0;
    if (rtmIsMajorTimeStep(ROBOT_M)) {
      ROBOT_DW.INPUT_19_1_1_discrete[0] = !(ROBOT_B.INPUT_19_1_1[0] ==
        ROBOT_DW.INPUT_19_1_1_discrete[1]);
      ROBOT_DW.INPUT_19_1_1_discrete[1] = ROBOT_B.INPUT_19_1_1[0];
    }

    ROBOT_B.INPUT_19_1_1[0] = ROBOT_DW.INPUT_19_1_1_discrete[1];
    ROBOT_B.INPUT_19_1_1[3] = ROBOT_DW.INPUT_19_1_1_discrete[0];

    /* End of SimscapeInputBlock: '<S123>/INPUT_19_1_1' */

    /* SimscapeExecutionBlock: '<S123>/STATE_1' */
    simulationData = (NeslSimulationData *)ROBOT_DW.STATE_1_SimulationData;
    time = ROBOT_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = NULL;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = NULL;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(ROBOT_M);
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    tmp_1[0] = 0;
    tmp_0[0] = ROBOT_B.INPUT_21_1_1[0];
    tmp_0[1] = ROBOT_B.INPUT_21_1_1[1];
    tmp_0[2] = ROBOT_B.INPUT_21_1_1[2];
    tmp_0[3] = ROBOT_B.INPUT_21_1_1[3];
    tmp_1[1] = 4;
    tmp_0[4] = ROBOT_B.INPUT_15_1_1[0];
    tmp_0[5] = ROBOT_B.INPUT_15_1_1[1];
    tmp_0[6] = ROBOT_B.INPUT_15_1_1[2];
    tmp_0[7] = ROBOT_B.INPUT_15_1_1[3];
    tmp_1[2] = 8;
    tmp_0[8] = ROBOT_B.INPUT_17_1_1[0];
    tmp_0[9] = ROBOT_B.INPUT_17_1_1[1];
    tmp_0[10] = ROBOT_B.INPUT_17_1_1[2];
    tmp_0[11] = ROBOT_B.INPUT_17_1_1[3];
    tmp_1[3] = 12;
    tmp_0[12] = ROBOT_B.INPUT_8_1_1[0];
    tmp_0[13] = ROBOT_B.INPUT_8_1_1[1];
    tmp_0[14] = ROBOT_B.INPUT_8_1_1[2];
    tmp_0[15] = ROBOT_B.INPUT_8_1_1[3];
    tmp_1[4] = 16;
    tmp_0[16] = ROBOT_B.INPUT_14_1_1[0];
    tmp_0[17] = ROBOT_B.INPUT_14_1_1[1];
    tmp_0[18] = ROBOT_B.INPUT_14_1_1[2];
    tmp_0[19] = ROBOT_B.INPUT_14_1_1[3];
    tmp_1[5] = 20;
    tmp_0[20] = ROBOT_B.INPUT_22_1_1[0];
    tmp_0[21] = ROBOT_B.INPUT_22_1_1[1];
    tmp_0[22] = ROBOT_B.INPUT_22_1_1[2];
    tmp_0[23] = ROBOT_B.INPUT_22_1_1[3];
    tmp_1[6] = 24;
    tmp_0[24] = ROBOT_B.INPUT_1_1_1[0];
    tmp_0[25] = ROBOT_B.INPUT_1_1_1[1];
    tmp_0[26] = ROBOT_B.INPUT_1_1_1[2];
    tmp_0[27] = ROBOT_B.INPUT_1_1_1[3];
    tmp_1[7] = 28;
    tmp_0[28] = ROBOT_B.INPUT_20_1_1[0];
    tmp_0[29] = ROBOT_B.INPUT_20_1_1[1];
    tmp_0[30] = ROBOT_B.INPUT_20_1_1[2];
    tmp_0[31] = ROBOT_B.INPUT_20_1_1[3];
    tmp_1[8] = 32;
    tmp_0[32] = ROBOT_B.INPUT_11_1_1[0];
    tmp_0[33] = ROBOT_B.INPUT_11_1_1[1];
    tmp_0[34] = ROBOT_B.INPUT_11_1_1[2];
    tmp_0[35] = ROBOT_B.INPUT_11_1_1[3];
    tmp_1[9] = 36;
    tmp_0[36] = ROBOT_B.INPUT_18_1_1[0];
    tmp_0[37] = ROBOT_B.INPUT_18_1_1[1];
    tmp_0[38] = ROBOT_B.INPUT_18_1_1[2];
    tmp_0[39] = ROBOT_B.INPUT_18_1_1[3];
    tmp_1[10] = 40;
    tmp_0[40] = ROBOT_B.INPUT_23_1_1[0];
    tmp_0[41] = ROBOT_B.INPUT_23_1_1[1];
    tmp_0[42] = ROBOT_B.INPUT_23_1_1[2];
    tmp_0[43] = ROBOT_B.INPUT_23_1_1[3];
    tmp_1[11] = 44;
    tmp_0[44] = ROBOT_B.INPUT_13_1_1[0];
    tmp_0[45] = ROBOT_B.INPUT_13_1_1[1];
    tmp_0[46] = ROBOT_B.INPUT_13_1_1[2];
    tmp_0[47] = ROBOT_B.INPUT_13_1_1[3];
    tmp_1[12] = 48;
    tmp_0[48] = ROBOT_B.INPUT_12_1_1[0];
    tmp_0[49] = ROBOT_B.INPUT_12_1_1[1];
    tmp_0[50] = ROBOT_B.INPUT_12_1_1[2];
    tmp_0[51] = ROBOT_B.INPUT_12_1_1[3];
    tmp_1[13] = 52;
    tmp_0[52] = ROBOT_B.INPUT_7_1_1[0];
    tmp_0[53] = ROBOT_B.INPUT_7_1_1[1];
    tmp_0[54] = ROBOT_B.INPUT_7_1_1[2];
    tmp_0[55] = ROBOT_B.INPUT_7_1_1[3];
    tmp_1[14] = 56;
    tmp_0[56] = ROBOT_B.INPUT_2_1_1[0];
    tmp_0[57] = ROBOT_B.INPUT_2_1_1[1];
    tmp_0[58] = ROBOT_B.INPUT_2_1_1[2];
    tmp_0[59] = ROBOT_B.INPUT_2_1_1[3];
    tmp_1[15] = 60;
    tmp_0[60] = ROBOT_B.INPUT_16_1_1[0];
    tmp_0[61] = ROBOT_B.INPUT_16_1_1[1];
    tmp_0[62] = ROBOT_B.INPUT_16_1_1[2];
    tmp_0[63] = ROBOT_B.INPUT_16_1_1[3];
    tmp_1[16] = 64;
    tmp_0[64] = ROBOT_B.INPUT_3_1_1[0];
    tmp_0[65] = ROBOT_B.INPUT_3_1_1[1];
    tmp_0[66] = ROBOT_B.INPUT_3_1_1[2];
    tmp_0[67] = ROBOT_B.INPUT_3_1_1[3];
    tmp_1[17] = 68;
    tmp_0[68] = ROBOT_B.INPUT_4_1_1[0];
    tmp_0[69] = ROBOT_B.INPUT_4_1_1[1];
    tmp_0[70] = ROBOT_B.INPUT_4_1_1[2];
    tmp_0[71] = ROBOT_B.INPUT_4_1_1[3];
    tmp_1[18] = 72;
    tmp_0[72] = ROBOT_B.INPUT_5_1_1[0];
    tmp_0[73] = ROBOT_B.INPUT_5_1_1[1];
    tmp_0[74] = ROBOT_B.INPUT_5_1_1[2];
    tmp_0[75] = ROBOT_B.INPUT_5_1_1[3];
    tmp_1[19] = 76;
    tmp_0[76] = ROBOT_B.INPUT_6_1_1[0];
    tmp_0[77] = ROBOT_B.INPUT_6_1_1[1];
    tmp_0[78] = ROBOT_B.INPUT_6_1_1[2];
    tmp_0[79] = ROBOT_B.INPUT_6_1_1[3];
    tmp_1[20] = 80;
    tmp_0[80] = ROBOT_B.INPUT_9_1_1[0];
    tmp_0[81] = ROBOT_B.INPUT_9_1_1[1];
    tmp_0[82] = ROBOT_B.INPUT_9_1_1[2];
    tmp_0[83] = ROBOT_B.INPUT_9_1_1[3];
    tmp_1[21] = 84;
    tmp_0[84] = ROBOT_B.INPUT_10_1_1[0];
    tmp_0[85] = ROBOT_B.INPUT_10_1_1[1];
    tmp_0[86] = ROBOT_B.INPUT_10_1_1[2];
    tmp_0[87] = ROBOT_B.INPUT_10_1_1[3];
    tmp_1[22] = 88;
    tmp_0[88] = ROBOT_B.INPUT_19_1_1[0];
    tmp_0[89] = ROBOT_B.INPUT_19_1_1[1];
    tmp_0[90] = ROBOT_B.INPUT_19_1_1[2];
    tmp_0[91] = ROBOT_B.INPUT_19_1_1[3];
    tmp_1[23] = 92;
    simulationData->mData->mInputValues.mN = 92;
    simulationData->mData->mInputValues.mX = &tmp_0[0];
    simulationData->mData->mInputOffsets.mN = 24;
    simulationData->mData->mInputOffsets.mX = &tmp_1[0];
    simulationData->mData->mOutputs.mN = 0;
    simulationData->mData->mOutputs.mX = NULL;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    diagnosticManager = (NeuDiagnosticManager *)
      ROBOT_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_2 = ne_simulator_method((NeslSimulator *)ROBOT_DW.STATE_1_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diagnosticManager);
    if (tmp_2 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(ROBOT_M));
      if (tmp) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(ROBOT_M, msg);
      }
    }

    /* End of SimscapeExecutionBlock: '<S123>/STATE_1' */
  }

  /* Matfile logging */
  rt_UpdateTXYLogVars(ROBOT_M->rtwLogInfo, (ROBOT_M->Timing.t));

  {
    NeslSimulationData *simulationData;
    real_T time;
    boolean_T tmp;
    real_T tmp_0[92];
    int_T tmp_1[24];
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    int32_T tmp_2;
    char *msg;

    /* Update for SimscapeExecutionBlock: '<S123>/STATE_1' */
    simulationData = (NeslSimulationData *)ROBOT_DW.STATE_1_SimulationData;
    time = ROBOT_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = NULL;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = NULL;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(ROBOT_M);
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    tmp_1[0] = 0;
    tmp_0[0] = ROBOT_B.INPUT_21_1_1[0];
    tmp_0[1] = ROBOT_B.INPUT_21_1_1[1];
    tmp_0[2] = ROBOT_B.INPUT_21_1_1[2];
    tmp_0[3] = ROBOT_B.INPUT_21_1_1[3];
    tmp_1[1] = 4;
    tmp_0[4] = ROBOT_B.INPUT_15_1_1[0];
    tmp_0[5] = ROBOT_B.INPUT_15_1_1[1];
    tmp_0[6] = ROBOT_B.INPUT_15_1_1[2];
    tmp_0[7] = ROBOT_B.INPUT_15_1_1[3];
    tmp_1[2] = 8;
    tmp_0[8] = ROBOT_B.INPUT_17_1_1[0];
    tmp_0[9] = ROBOT_B.INPUT_17_1_1[1];
    tmp_0[10] = ROBOT_B.INPUT_17_1_1[2];
    tmp_0[11] = ROBOT_B.INPUT_17_1_1[3];
    tmp_1[3] = 12;
    tmp_0[12] = ROBOT_B.INPUT_8_1_1[0];
    tmp_0[13] = ROBOT_B.INPUT_8_1_1[1];
    tmp_0[14] = ROBOT_B.INPUT_8_1_1[2];
    tmp_0[15] = ROBOT_B.INPUT_8_1_1[3];
    tmp_1[4] = 16;
    tmp_0[16] = ROBOT_B.INPUT_14_1_1[0];
    tmp_0[17] = ROBOT_B.INPUT_14_1_1[1];
    tmp_0[18] = ROBOT_B.INPUT_14_1_1[2];
    tmp_0[19] = ROBOT_B.INPUT_14_1_1[3];
    tmp_1[5] = 20;
    tmp_0[20] = ROBOT_B.INPUT_22_1_1[0];
    tmp_0[21] = ROBOT_B.INPUT_22_1_1[1];
    tmp_0[22] = ROBOT_B.INPUT_22_1_1[2];
    tmp_0[23] = ROBOT_B.INPUT_22_1_1[3];
    tmp_1[6] = 24;
    tmp_0[24] = ROBOT_B.INPUT_1_1_1[0];
    tmp_0[25] = ROBOT_B.INPUT_1_1_1[1];
    tmp_0[26] = ROBOT_B.INPUT_1_1_1[2];
    tmp_0[27] = ROBOT_B.INPUT_1_1_1[3];
    tmp_1[7] = 28;
    tmp_0[28] = ROBOT_B.INPUT_20_1_1[0];
    tmp_0[29] = ROBOT_B.INPUT_20_1_1[1];
    tmp_0[30] = ROBOT_B.INPUT_20_1_1[2];
    tmp_0[31] = ROBOT_B.INPUT_20_1_1[3];
    tmp_1[8] = 32;
    tmp_0[32] = ROBOT_B.INPUT_11_1_1[0];
    tmp_0[33] = ROBOT_B.INPUT_11_1_1[1];
    tmp_0[34] = ROBOT_B.INPUT_11_1_1[2];
    tmp_0[35] = ROBOT_B.INPUT_11_1_1[3];
    tmp_1[9] = 36;
    tmp_0[36] = ROBOT_B.INPUT_18_1_1[0];
    tmp_0[37] = ROBOT_B.INPUT_18_1_1[1];
    tmp_0[38] = ROBOT_B.INPUT_18_1_1[2];
    tmp_0[39] = ROBOT_B.INPUT_18_1_1[3];
    tmp_1[10] = 40;
    tmp_0[40] = ROBOT_B.INPUT_23_1_1[0];
    tmp_0[41] = ROBOT_B.INPUT_23_1_1[1];
    tmp_0[42] = ROBOT_B.INPUT_23_1_1[2];
    tmp_0[43] = ROBOT_B.INPUT_23_1_1[3];
    tmp_1[11] = 44;
    tmp_0[44] = ROBOT_B.INPUT_13_1_1[0];
    tmp_0[45] = ROBOT_B.INPUT_13_1_1[1];
    tmp_0[46] = ROBOT_B.INPUT_13_1_1[2];
    tmp_0[47] = ROBOT_B.INPUT_13_1_1[3];
    tmp_1[12] = 48;
    tmp_0[48] = ROBOT_B.INPUT_12_1_1[0];
    tmp_0[49] = ROBOT_B.INPUT_12_1_1[1];
    tmp_0[50] = ROBOT_B.INPUT_12_1_1[2];
    tmp_0[51] = ROBOT_B.INPUT_12_1_1[3];
    tmp_1[13] = 52;
    tmp_0[52] = ROBOT_B.INPUT_7_1_1[0];
    tmp_0[53] = ROBOT_B.INPUT_7_1_1[1];
    tmp_0[54] = ROBOT_B.INPUT_7_1_1[2];
    tmp_0[55] = ROBOT_B.INPUT_7_1_1[3];
    tmp_1[14] = 56;
    tmp_0[56] = ROBOT_B.INPUT_2_1_1[0];
    tmp_0[57] = ROBOT_B.INPUT_2_1_1[1];
    tmp_0[58] = ROBOT_B.INPUT_2_1_1[2];
    tmp_0[59] = ROBOT_B.INPUT_2_1_1[3];
    tmp_1[15] = 60;
    tmp_0[60] = ROBOT_B.INPUT_16_1_1[0];
    tmp_0[61] = ROBOT_B.INPUT_16_1_1[1];
    tmp_0[62] = ROBOT_B.INPUT_16_1_1[2];
    tmp_0[63] = ROBOT_B.INPUT_16_1_1[3];
    tmp_1[16] = 64;
    tmp_0[64] = ROBOT_B.INPUT_3_1_1[0];
    tmp_0[65] = ROBOT_B.INPUT_3_1_1[1];
    tmp_0[66] = ROBOT_B.INPUT_3_1_1[2];
    tmp_0[67] = ROBOT_B.INPUT_3_1_1[3];
    tmp_1[17] = 68;
    tmp_0[68] = ROBOT_B.INPUT_4_1_1[0];
    tmp_0[69] = ROBOT_B.INPUT_4_1_1[1];
    tmp_0[70] = ROBOT_B.INPUT_4_1_1[2];
    tmp_0[71] = ROBOT_B.INPUT_4_1_1[3];
    tmp_1[18] = 72;
    tmp_0[72] = ROBOT_B.INPUT_5_1_1[0];
    tmp_0[73] = ROBOT_B.INPUT_5_1_1[1];
    tmp_0[74] = ROBOT_B.INPUT_5_1_1[2];
    tmp_0[75] = ROBOT_B.INPUT_5_1_1[3];
    tmp_1[19] = 76;
    tmp_0[76] = ROBOT_B.INPUT_6_1_1[0];
    tmp_0[77] = ROBOT_B.INPUT_6_1_1[1];
    tmp_0[78] = ROBOT_B.INPUT_6_1_1[2];
    tmp_0[79] = ROBOT_B.INPUT_6_1_1[3];
    tmp_1[20] = 80;
    tmp_0[80] = ROBOT_B.INPUT_9_1_1[0];
    tmp_0[81] = ROBOT_B.INPUT_9_1_1[1];
    tmp_0[82] = ROBOT_B.INPUT_9_1_1[2];
    tmp_0[83] = ROBOT_B.INPUT_9_1_1[3];
    tmp_1[21] = 84;
    tmp_0[84] = ROBOT_B.INPUT_10_1_1[0];
    tmp_0[85] = ROBOT_B.INPUT_10_1_1[1];
    tmp_0[86] = ROBOT_B.INPUT_10_1_1[2];
    tmp_0[87] = ROBOT_B.INPUT_10_1_1[3];
    tmp_1[22] = 88;
    tmp_0[88] = ROBOT_B.INPUT_19_1_1[0];
    tmp_0[89] = ROBOT_B.INPUT_19_1_1[1];
    tmp_0[90] = ROBOT_B.INPUT_19_1_1[2];
    tmp_0[91] = ROBOT_B.INPUT_19_1_1[3];
    tmp_1[23] = 92;
    simulationData->mData->mInputValues.mN = 92;
    simulationData->mData->mInputValues.mX = &tmp_0[0];
    simulationData->mData->mInputOffsets.mN = 24;
    simulationData->mData->mInputOffsets.mX = &tmp_1[0];
    diagnosticManager = (NeuDiagnosticManager *)
      ROBOT_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_2 = ne_simulator_method((NeslSimulator *)ROBOT_DW.STATE_1_Simulator,
      NESL_SIM_UPDATE, simulationData, diagnosticManager);
    if (tmp_2 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(ROBOT_M));
      if (tmp) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(ROBOT_M, msg);
      }
    }

    /* End of Update for SimscapeExecutionBlock: '<S123>/STATE_1' */
  }

  /* External mode */
  rtExtModeUploadCheckTrigger(2);

  {                                    /* Sample time: [0.0s, 0.0s] */
    rtExtModeUpload(0, ROBOT_M->Timing.t[0]);
  }

  {                                    /* Sample time: [0.5s, 0.0s] */
    rtExtModeUpload(1, (((ROBOT_M->Timing.clockTick1+ROBOT_M->Timing.clockTickH1*
                          4294967296.0)) * 0.5));
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(ROBOT_M)!=-1) &&
        !((rtmGetTFinal(ROBOT_M)-ROBOT_M->Timing.t[0]) > ROBOT_M->Timing.t[0] *
          (DBL_EPSILON))) {
      rtmSetErrorStatus(ROBOT_M, "Simulation finished");
    }

    if (rtmGetStopRequested(ROBOT_M)) {
      rtmSetErrorStatus(ROBOT_M, "Simulation finished");
    }
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
  if (!(++ROBOT_M->Timing.clockTick0)) {
    ++ROBOT_M->Timing.clockTickH0;
  }

  ROBOT_M->Timing.t[0] = ROBOT_M->Timing.clockTick0 * ROBOT_M->Timing.stepSize0
    + ROBOT_M->Timing.clockTickH0 * ROBOT_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.5s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.5, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    ROBOT_M->Timing.clockTick1++;
    if (!ROBOT_M->Timing.clockTick1) {
      ROBOT_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void ROBOT_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ROBOT_M, 0,
                sizeof(RT_MODEL_ROBOT_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&ROBOT_M->solverInfo, &ROBOT_M->Timing.simTimeStep);
    rtsiSetTPtr(&ROBOT_M->solverInfo, &rtmGetTPtr(ROBOT_M));
    rtsiSetStepSizePtr(&ROBOT_M->solverInfo, &ROBOT_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&ROBOT_M->solverInfo, (&rtmGetErrorStatus(ROBOT_M)));
    rtsiSetRTModelPtr(&ROBOT_M->solverInfo, ROBOT_M);
  }

  rtsiSetSimTimeStep(&ROBOT_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&ROBOT_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(ROBOT_M, &ROBOT_M->Timing.tArray[0]);
  rtmSetTFinal(ROBOT_M, -1);
  ROBOT_M->Timing.stepSize0 = 0.5;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    ROBOT_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ROBOT_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(ROBOT_M->rtwLogInfo, (NULL));
    rtliSetLogT(ROBOT_M->rtwLogInfo, "tout");
    rtliSetLogX(ROBOT_M->rtwLogInfo, "");
    rtliSetLogXFinal(ROBOT_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(ROBOT_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(ROBOT_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(ROBOT_M->rtwLogInfo, 0);
    rtliSetLogDecimation(ROBOT_M->rtwLogInfo, 1);
    rtliSetLogY(ROBOT_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(ROBOT_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(ROBOT_M->rtwLogInfo, (NULL));
  }

  /* External mode info */
  ROBOT_M->Sizes.checksums[0] = (1339606787U);
  ROBOT_M->Sizes.checksums[1] = (820518362U);
  ROBOT_M->Sizes.checksums[2] = (3341637844U);
  ROBOT_M->Sizes.checksums[3] = (2944994238U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    ROBOT_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(ROBOT_M->extModeInfo,
      &ROBOT_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(ROBOT_M->extModeInfo, ROBOT_M->Sizes.checksums);
    rteiSetTPtr(ROBOT_M->extModeInfo, rtmGetTPtr(ROBOT_M));
  }

  /* block I/O */
  (void) memset(((void *) &ROBOT_B), 0,
                sizeof(B_ROBOT_T));

  /* states (dwork) */
  (void) memset((void *)&ROBOT_DW, 0,
                sizeof(DW_ROBOT_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    ROBOT_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(ROBOT_M->rtwLogInfo, 0.0, rtmGetTFinal
    (ROBOT_M), ROBOT_M->Timing.stepSize0, (&rtmGetErrorStatus(ROBOT_M)));

  {
    NeslSimulator *tmp;
    NeuDiagnosticManager *diagnosticManager;
    real_T modelParameters_mSolverTolerance;
    real_T modelParameters_mFixedStepSize;
    boolean_T modelParameters_mVariableStepSolver;
    NeuDiagnosticTree *diagnosticTree;
    int32_T tmp_0;
    char *msg;
    NeslSimulationData *simulationData;
    real_T time;
    NeModelParameters expl_temp;
    NeParameterBundle expl_temp_0;

    /* Start for SimscapeExecutionBlock: '<S123>/STATE_1' */
    tmp = nesl_lease_simulator("ROBOT/Solver Configuration_1", 0, 0);
    ROBOT_DW.STATE_1_Simulator = (void *)tmp;
    modelParameters_mVariableStepSolver = pointer_is_null
      (ROBOT_DW.STATE_1_Simulator);
    if (modelParameters_mVariableStepSolver) {
      ROBOT_2da83c1f_1_gateway();
      tmp = nesl_lease_simulator("ROBOT/Solver Configuration_1", 0, 0);
      ROBOT_DW.STATE_1_Simulator = (void *)tmp;
    }

    simulationData = nesl_create_simulation_data();
    ROBOT_DW.STATE_1_SimulationData = (void *)simulationData;
    diagnosticManager = rtw_create_diagnostics();
    ROBOT_DW.STATE_1_DiagnosticManager = (void *)diagnosticManager;
    modelParameters_mSolverTolerance = 0.001;
    modelParameters_mFixedStepSize = 0.5;
    modelParameters_mVariableStepSolver = false;
    diagnosticManager = (NeuDiagnosticManager *)
      ROBOT_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    expl_temp.mVariableStepSolver = modelParameters_mVariableStepSolver;
    expl_temp.mUseSimState = false;
    expl_temp.mStartTime = 0.0;
    expl_temp.mSolverType = NE_SOLVER_TYPE_ODE;
    expl_temp.mSolverTolerance = modelParameters_mSolverTolerance;
    expl_temp.mRTWModifiedTimeStamp = 4.39592853E+8;
    expl_temp.mLoggingMode = SSC_LOGGING_NONE;
    expl_temp.mLoadInitialState = false;
    expl_temp.mLinTrimCompile = false;
    expl_temp.mFixedStepSize = modelParameters_mFixedStepSize;
    tmp_0 = nesl_initialize_simulator((NeslSimulator *)
      ROBOT_DW.STATE_1_Simulator, expl_temp, diagnosticManager);
    if (tmp_0 != 0) {
      modelParameters_mVariableStepSolver = error_buffer_is_empty
        (rtmGetErrorStatus(ROBOT_M));
      if (modelParameters_mVariableStepSolver) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(ROBOT_M, msg);
      }
    }

    expl_temp_0.mRealParameters.mN = 0;
    expl_temp_0.mRealParameters.mX = NULL;
    expl_temp_0.mLogicalParameters.mN = 0;
    expl_temp_0.mLogicalParameters.mX = NULL;
    expl_temp_0.mIntegerParameters.mN = 0;
    expl_temp_0.mIntegerParameters.mX = NULL;
    expl_temp_0.mIndexParameters.mN = 0;
    expl_temp_0.mIndexParameters.mX = NULL;
    nesl_simulator_set_rtps((NeslSimulator *)ROBOT_DW.STATE_1_Simulator,
      expl_temp_0);
    simulationData = (NeslSimulationData *)ROBOT_DW.STATE_1_SimulationData;
    time = ROBOT_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = NULL;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = NULL;
    modelParameters_mVariableStepSolver = false;
    simulationData->mData->mFoundZcEvents = modelParameters_mVariableStepSolver;
    simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(ROBOT_M);
    modelParameters_mVariableStepSolver = false;
    simulationData->mData->mIsSolverAssertCheck =
      modelParameters_mVariableStepSolver;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    diagnosticManager = (NeuDiagnosticManager *)
      ROBOT_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_0 = ne_simulator_method((NeslSimulator *)ROBOT_DW.STATE_1_Simulator,
      NESL_SIM_INITIALIZEONCE, simulationData, diagnosticManager);
    if (tmp_0 != 0) {
      modelParameters_mVariableStepSolver = error_buffer_is_empty
        (rtmGetErrorStatus(ROBOT_M));
      if (modelParameters_mVariableStepSolver) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(ROBOT_M, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S123>/STATE_1' */
  }
}

/* Model terminate function */
void ROBOT_terminate(void)
{
  /* Terminate for SimscapeExecutionBlock: '<S123>/STATE_1' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)
    ROBOT_DW.STATE_1_DiagnosticManager);
  nesl_destroy_simulation_data((NeslSimulationData *)
    ROBOT_DW.STATE_1_SimulationData);
  nesl_erase_simulator("ROBOT/Solver Configuration_1");
}
