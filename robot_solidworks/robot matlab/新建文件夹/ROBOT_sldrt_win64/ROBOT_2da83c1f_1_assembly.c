/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'ROBOT/Solver Configuration'.
 */

#include <math.h>
#include <string.h>
#include "pm_std.h"
#include "sm_std.h"
#include "ne_std.h"
#include "ne_dae.h"
#include "sm_ssci_run_time_errors.h"
#include "sm_CTarget.h"

void ROBOT_2da83c1f_1_checkTargets(const double *rtdv, const double *state)
{
  (void) rtdv;
  (void) state;
}

void ROBOT_2da83c1f_1_setTargets(const double *rtdv, CTarget *targets)
{
  (void) rtdv;
  (void) targets;
}

void ROBOT_2da83c1f_1_resetStateVector(const void *mech, double *state)
{
  double xx[1];
  (void) mech;
  xx[0] = 0.0;
  state[0] = xx[0];
  state[1] = xx[0];
  state[2] = xx[0];
  state[3] = xx[0];
  state[4] = xx[0];
  state[5] = xx[0];
  state[6] = xx[0];
  state[7] = xx[0];
  state[8] = xx[0];
  state[9] = xx[0];
  state[10] = xx[0];
  state[11] = xx[0];
  state[12] = xx[0];
  state[13] = xx[0];
  state[14] = xx[0];
  state[15] = xx[0];
  state[16] = xx[0];
  state[17] = xx[0];
  state[18] = xx[0];
  state[19] = xx[0];
  state[20] = xx[0];
  state[21] = xx[0];
  state[22] = xx[0];
  state[23] = xx[0];
  state[24] = xx[0];
  state[25] = xx[0];
  state[26] = xx[0];
  state[27] = xx[0];
  state[28] = xx[0];
  state[29] = xx[0];
  state[30] = xx[0];
  state[31] = xx[0];
  state[32] = xx[0];
  state[33] = xx[0];
  state[34] = xx[0];
  state[35] = xx[0];
  state[36] = xx[0];
  state[37] = xx[0];
  state[38] = xx[0];
  state[39] = xx[0];
  state[40] = xx[0];
  state[41] = xx[0];
  state[42] = xx[0];
  state[43] = xx[0];
  state[44] = xx[0];
  state[45] = xx[0];
}

void ROBOT_2da83c1f_1_initializeTrackedAngleState(const void *mech, const double
  *rtdv, const double *motionData, double *state, void *neDiagMgr0)
{
  NeuDiagnosticManager *neDiagMgr = (NeuDiagnosticManager *) neDiagMgr0;
  (void) mech;
  (void) rtdv;
  (void) motionData;
  (void) state;
  (void) neDiagMgr;
}

void ROBOT_2da83c1f_1_computeDiscreteState(const void *mech, const double *rtdv,
  double *state)
{
  (void) mech;
  (void) rtdv;
  (void) state;
}

void ROBOT_2da83c1f_1_adjustPosition(const void *mech, const double *dofDeltas,
  double *state)
{
  (void) mech;
  state[0] = state[0] + dofDeltas[0];
  state[2] = state[2] + dofDeltas[1];
  state[4] = state[4] + dofDeltas[2];
  state[6] = state[6] + dofDeltas[3];
  state[8] = state[8] + dofDeltas[4];
  state[10] = state[10] + dofDeltas[5];
  state[12] = state[12] + dofDeltas[6];
  state[14] = state[14] + dofDeltas[7];
  state[16] = state[16] + dofDeltas[8];
  state[18] = state[18] + dofDeltas[9];
  state[20] = state[20] + dofDeltas[10];
  state[22] = state[22] + dofDeltas[11];
  state[24] = state[24] + dofDeltas[12];
  state[26] = state[26] + dofDeltas[13];
  state[28] = state[28] + dofDeltas[14];
  state[30] = state[30] + dofDeltas[15];
  state[32] = state[32] + dofDeltas[16];
  state[34] = state[34] + dofDeltas[17];
  state[36] = state[36] + dofDeltas[18];
  state[38] = state[38] + dofDeltas[19];
  state[40] = state[40] + dofDeltas[20];
  state[42] = state[42] + dofDeltas[21];
  state[44] = state[44] + dofDeltas[22];
}

static void perturbState_0_0(double mag, double *state)
{
  state[0] = state[0] + mag;
}

static void perturbState_0_0v(double mag, double *state)
{
  state[0] = state[0] + mag;
  state[1] = state[1] - 0.875 * mag;
}

static void perturbState_1_0(double mag, double *state)
{
  state[2] = state[2] + mag;
}

static void perturbState_1_0v(double mag, double *state)
{
  state[2] = state[2] + mag;
  state[3] = state[3] - 0.875 * mag;
}

static void perturbState_2_0(double mag, double *state)
{
  state[4] = state[4] + mag;
}

static void perturbState_2_0v(double mag, double *state)
{
  state[4] = state[4] + mag;
  state[5] = state[5] - 0.875 * mag;
}

static void perturbState_3_0(double mag, double *state)
{
  state[6] = state[6] + mag;
}

static void perturbState_3_0v(double mag, double *state)
{
  state[6] = state[6] + mag;
  state[7] = state[7] - 0.875 * mag;
}

static void perturbState_4_0(double mag, double *state)
{
  state[8] = state[8] + mag;
}

static void perturbState_4_0v(double mag, double *state)
{
  state[8] = state[8] + mag;
  state[9] = state[9] - 0.875 * mag;
}

static void perturbState_5_0(double mag, double *state)
{
  state[10] = state[10] + mag;
}

static void perturbState_5_0v(double mag, double *state)
{
  state[10] = state[10] + mag;
  state[11] = state[11] - 0.875 * mag;
}

static void perturbState_6_0(double mag, double *state)
{
  state[12] = state[12] + mag;
}

static void perturbState_6_0v(double mag, double *state)
{
  state[12] = state[12] + mag;
  state[13] = state[13] - 0.875 * mag;
}

static void perturbState_7_0(double mag, double *state)
{
  state[14] = state[14] + mag;
}

static void perturbState_7_0v(double mag, double *state)
{
  state[14] = state[14] + mag;
  state[15] = state[15] - 0.875 * mag;
}

static void perturbState_8_0(double mag, double *state)
{
  state[16] = state[16] + mag;
}

static void perturbState_8_0v(double mag, double *state)
{
  state[16] = state[16] + mag;
  state[17] = state[17] - 0.875 * mag;
}

static void perturbState_9_0(double mag, double *state)
{
  state[18] = state[18] + mag;
}

static void perturbState_9_0v(double mag, double *state)
{
  state[18] = state[18] + mag;
  state[19] = state[19] - 0.875 * mag;
}

static void perturbState_10_0(double mag, double *state)
{
  state[20] = state[20] + mag;
}

static void perturbState_10_0v(double mag, double *state)
{
  state[20] = state[20] + mag;
  state[21] = state[21] - 0.875 * mag;
}

static void perturbState_11_0(double mag, double *state)
{
  state[22] = state[22] + mag;
}

static void perturbState_11_0v(double mag, double *state)
{
  state[22] = state[22] + mag;
  state[23] = state[23] - 0.875 * mag;
}

static void perturbState_12_0(double mag, double *state)
{
  state[24] = state[24] + mag;
}

static void perturbState_12_0v(double mag, double *state)
{
  state[24] = state[24] + mag;
  state[25] = state[25] - 0.875 * mag;
}

static void perturbState_13_0(double mag, double *state)
{
  state[26] = state[26] + mag;
}

static void perturbState_13_0v(double mag, double *state)
{
  state[26] = state[26] + mag;
  state[27] = state[27] - 0.875 * mag;
}

static void perturbState_14_0(double mag, double *state)
{
  state[28] = state[28] + mag;
}

static void perturbState_14_0v(double mag, double *state)
{
  state[28] = state[28] + mag;
  state[29] = state[29] - 0.875 * mag;
}

static void perturbState_15_0(double mag, double *state)
{
  state[30] = state[30] + mag;
}

static void perturbState_15_0v(double mag, double *state)
{
  state[30] = state[30] + mag;
  state[31] = state[31] - 0.875 * mag;
}

static void perturbState_16_0(double mag, double *state)
{
  state[32] = state[32] + mag;
}

static void perturbState_16_0v(double mag, double *state)
{
  state[32] = state[32] + mag;
  state[33] = state[33] - 0.875 * mag;
}

static void perturbState_17_0(double mag, double *state)
{
  state[34] = state[34] + mag;
}

static void perturbState_17_0v(double mag, double *state)
{
  state[34] = state[34] + mag;
  state[35] = state[35] - 0.875 * mag;
}

static void perturbState_18_0(double mag, double *state)
{
  state[36] = state[36] + mag;
}

static void perturbState_18_0v(double mag, double *state)
{
  state[36] = state[36] + mag;
  state[37] = state[37] - 0.875 * mag;
}

static void perturbState_19_0(double mag, double *state)
{
  state[38] = state[38] + mag;
}

static void perturbState_19_0v(double mag, double *state)
{
  state[38] = state[38] + mag;
  state[39] = state[39] - 0.875 * mag;
}

static void perturbState_20_0(double mag, double *state)
{
  state[40] = state[40] + mag;
}

static void perturbState_20_0v(double mag, double *state)
{
  state[40] = state[40] + mag;
  state[41] = state[41] - 0.875 * mag;
}

static void perturbState_21_0(double mag, double *state)
{
  state[42] = state[42] + mag;
}

static void perturbState_21_0v(double mag, double *state)
{
  state[42] = state[42] + mag;
  state[43] = state[43] - 0.875 * mag;
}

static void perturbState_22_0(double mag, double *state)
{
  state[44] = state[44] + mag;
}

static void perturbState_22_0v(double mag, double *state)
{
  state[44] = state[44] + mag;
  state[45] = state[45] - 0.875 * mag;
}

void ROBOT_2da83c1f_1_perturbState(const void *mech, size_t stageIdx, size_t
  primIdx, double mag, boolean_T doPerturbVelocity, double *state)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) mag;
  (void) doPerturbVelocity;
  (void) state;
  switch ((stageIdx * 6 + primIdx) * 2 + (doPerturbVelocity ? 1 : 0))
  {
   case 0:
    perturbState_0_0(mag, state);
    break;

   case 1:
    perturbState_0_0v(mag, state);
    break;

   case 12:
    perturbState_1_0(mag, state);
    break;

   case 13:
    perturbState_1_0v(mag, state);
    break;

   case 24:
    perturbState_2_0(mag, state);
    break;

   case 25:
    perturbState_2_0v(mag, state);
    break;

   case 36:
    perturbState_3_0(mag, state);
    break;

   case 37:
    perturbState_3_0v(mag, state);
    break;

   case 48:
    perturbState_4_0(mag, state);
    break;

   case 49:
    perturbState_4_0v(mag, state);
    break;

   case 60:
    perturbState_5_0(mag, state);
    break;

   case 61:
    perturbState_5_0v(mag, state);
    break;

   case 72:
    perturbState_6_0(mag, state);
    break;

   case 73:
    perturbState_6_0v(mag, state);
    break;

   case 84:
    perturbState_7_0(mag, state);
    break;

   case 85:
    perturbState_7_0v(mag, state);
    break;

   case 96:
    perturbState_8_0(mag, state);
    break;

   case 97:
    perturbState_8_0v(mag, state);
    break;

   case 108:
    perturbState_9_0(mag, state);
    break;

   case 109:
    perturbState_9_0v(mag, state);
    break;

   case 120:
    perturbState_10_0(mag, state);
    break;

   case 121:
    perturbState_10_0v(mag, state);
    break;

   case 132:
    perturbState_11_0(mag, state);
    break;

   case 133:
    perturbState_11_0v(mag, state);
    break;

   case 144:
    perturbState_12_0(mag, state);
    break;

   case 145:
    perturbState_12_0v(mag, state);
    break;

   case 156:
    perturbState_13_0(mag, state);
    break;

   case 157:
    perturbState_13_0v(mag, state);
    break;

   case 168:
    perturbState_14_0(mag, state);
    break;

   case 169:
    perturbState_14_0v(mag, state);
    break;

   case 180:
    perturbState_15_0(mag, state);
    break;

   case 181:
    perturbState_15_0v(mag, state);
    break;

   case 192:
    perturbState_16_0(mag, state);
    break;

   case 193:
    perturbState_16_0v(mag, state);
    break;

   case 204:
    perturbState_17_0(mag, state);
    break;

   case 205:
    perturbState_17_0v(mag, state);
    break;

   case 216:
    perturbState_18_0(mag, state);
    break;

   case 217:
    perturbState_18_0v(mag, state);
    break;

   case 228:
    perturbState_19_0(mag, state);
    break;

   case 229:
    perturbState_19_0v(mag, state);
    break;

   case 240:
    perturbState_20_0(mag, state);
    break;

   case 241:
    perturbState_20_0v(mag, state);
    break;

   case 252:
    perturbState_21_0(mag, state);
    break;

   case 253:
    perturbState_21_0v(mag, state);
    break;

   case 264:
    perturbState_22_0(mag, state);
    break;

   case 265:
    perturbState_22_0v(mag, state);
    break;
  }
}

void ROBOT_2da83c1f_1_computeDofBlendMatrix(const void *mech, size_t stageIdx,
  size_t primIdx, const double *state, int partialType, double *matrix)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) state;
  (void) partialType;
  (void) matrix;
  switch ((stageIdx * 6 + primIdx))
  {
  }
}

void ROBOT_2da83c1f_1_projectPartiallyTargetedPos(const void *mech, size_t
  stageIdx, size_t primIdx, const double *origState, int partialType, double
  *state)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) origState;
  (void) partialType;
  (void) state;
  switch ((stageIdx * 6 + primIdx))
  {
  }
}

void ROBOT_2da83c1f_1_propagateMotion(const void *mech, const double *rtdv,
  const double *state, double *motionData)
{
  double xx[320];
  (void) mech;
  (void) rtdv;
  xx[0] = 0.4991993443073;
  xx[1] = 0.5051758095082685;
  xx[2] = 0.4954980610448412;
  xx[3] = - 0.500079081377766;
  xx[4] = 0.5;
  xx[5] = xx[4] * state[0];
  xx[6] = 8.80516773834511e-3;
  xx[7] = sin(xx[5]);
  xx[8] = 0.9999055672473656;
  xx[9] = 0.01055109514808228;
  xx[10] = cos(xx[5]);
  xx[11] = - (xx[6] * xx[7]);
  xx[12] = - (xx[8] * xx[7]);
  xx[13] = xx[9] * xx[7];
  pm_math_quatCompose(xx + 0, xx + 10, xx + 14);
  xx[0] = - 3.22986598173323e-3;
  xx[1] = - 0.02639646878354535;
  xx[2] = - 9.939110078155124e-3;
  pm_math_quatXform(xx + 14, xx + 0, xx + 10);
  xx[0] = - 0.501641780684723;
  xx[1] = - 0.4976214364098542;
  xx[2] = 0.5027606110855342;
  xx[3] = - 0.497956019983446;
  xx[5] = xx[4] * state[2];
  xx[7] = 0.9999356812616955;
  xx[13] = sin(xx[5]);
  xx[18] = 7.715298454225028e-6;
  xx[19] = 0.01134166126206115;
  xx[20] = cos(xx[5]);
  xx[21] = - (xx[7] * xx[13]);
  xx[22] = xx[18] * xx[13];
  xx[23] = xx[19] * xx[13];
  pm_math_quatCompose(xx + 0, xx + 20, xx + 24);
  xx[0] = 0.02935804209142335;
  xx[1] = 0.03600179404177633;
  xx[2] = - 2.586231194248891e-4;
  pm_math_quatXform(xx + 24, xx + 0, xx + 20);
  xx[0] = 0.0295405246419396 - xx[20];
  xx[1] = - (8.250534995959181e-4 + xx[21]);
  xx[2] = 0.02868716604795884 - xx[22];
  xx[20] = 0.5460553414275259;
  xx[21] = 0.4565214381045248;
  xx[22] = - 0.5366456332323102;
  xx[23] = - 0.4532363676737975;
  xx[3] = xx[4] * state[4];
  xx[5] = 0.01122964448530347;
  xx[13] = sin(xx[3]);
  xx[28] = 6.169682634902114e-3;
  xx[29] = 0.9999179116812131;
  xx[30] = cos(xx[3]);
  xx[31] = - (xx[5] * xx[13]);
  xx[32] = xx[28] * xx[13];
  xx[33] = xx[29] * xx[13];
  pm_math_quatCompose(xx + 20, xx + 30, xx + 34);
  xx[20] = - 0.01036434756115468;
  xx[21] = - 0.05405897814627767;
  xx[22] = - 0.02604489784088932;
  pm_math_quatXform(xx + 34, xx + 20, xx + 30);
  xx[3] = 0.02635765094712477 - xx[30];
  xx[13] = - (0.03599818276591955 + xx[31]);
  xx[20] = - (2.271164136009043e-4 + xx[32]);
  xx[30] = 0.01701204546345425;
  xx[31] = 0.01058511911577453;
  xx[32] = 0.7081121773874674;
  xx[33] = 0.7058156202564765;
  xx[21] = xx[4] * state[6];
  xx[22] = 2.311443388461287e-3;
  xx[23] = sin(xx[21]);
  xx[38] = 0.999993798634778;
  xx[39] = 2.657051269574495e-3;
  xx[40] = cos(xx[21]);
  xx[41] = xx[22] * xx[23];
  xx[42] = xx[38] * xx[23];
  xx[43] = xx[39] * xx[23];
  pm_math_quatCompose(xx + 30, xx + 40, xx + 44);
  xx[30] = - 9.893540522622714e-3;
  xx[31] = 0.02578328389149156;
  xx[32] = 0.01755311911437975;
  pm_math_quatXform(xx + 44, xx + 30, xx + 40);
  xx[21] = 1.986400484240173e-3 - xx[40];
  xx[23] = 0.02013634744889968 - xx[41];
  xx[30] = 0.02539025728228318 - xx[42];
  xx[40] = - 0.488733079620889;
  xx[41] = 0.4747905395352491;
  xx[42] = 0.5315226192074705;
  xx[43] = 0.5031874657848106;
  xx[31] = xx[4] * state[8];
  xx[32] = 0.06264933046377247;
  xx[33] = sin(xx[31]);
  xx[48] = 0.9969693228662613;
  xx[49] = 0.04612191080203276;
  xx[50] = cos(xx[31]);
  xx[51] = xx[32] * xx[33];
  xx[52] = xx[48] * xx[33];
  xx[53] = - (xx[49] * xx[33]);
  pm_math_quatCompose(xx + 40, xx + 50, xx + 54);
  xx[40] = 3.083569551604105e-3;
  xx[41] = 0.01357334607326524;
  xx[42] = 6.890358344876871e-3;
  pm_math_quatXform(xx + 54, xx + 40, xx + 50);
  xx[31] = 0.03146188839042668 - xx[50];
  xx[33] = 3.115273808221738e-5 - xx[51];
  xx[40] = - (0.01391758627121785 + xx[52]);
  xx[50] = 0.6870649120317744;
  xx[51] = 0.3097544704682211;
  xx[52] = 0.4742308498873955;
  xx[53] = 0.4550813945821131;
  xx[41] = xx[4] * state[10];
  xx[42] = 0.36972776152383;
  xx[43] = sin(xx[41]);
  xx[58] = 0.8572701290486278;
  xx[59] = 0.358314538080061;
  xx[60] = cos(xx[41]);
  xx[61] = xx[42] * xx[43];
  xx[62] = - (xx[58] * xx[43]);
  xx[63] = - (xx[59] * xx[43]);
  pm_math_quatCompose(xx + 50, xx + 60, xx + 64);
  xx[50] = 0.02417951922197712;
  xx[51] = - 0.05120843729472828;
  xx[52] = - 8.50238479435652e-3;
  pm_math_quatXform(xx + 64, xx + 50, xx + 60);
  xx[50] = 0.4836599984678736;
  xx[51] = 0.4464343736326479;
  xx[52] = 0.6898069896278929;
  xx[53] = - 0.3015554227364954;
  xx[41] = xx[4] * state[12];
  xx[43] = 6.371293911993092e-4;
  xx[63] = sin(xx[41]);
  xx[68] = 0.9995572178960189;
  xx[69] = 0.02974831454233073;
  xx[70] = cos(xx[41]);
  xx[71] = xx[43] * xx[63];
  xx[72] = - (xx[68] * xx[63]);
  xx[73] = - (xx[69] * xx[63]);
  pm_math_quatCompose(xx + 50, xx + 70, xx + 74);
  xx[50] = - 2.918705149343171e-5;
  xx[51] = - 0.01252189717303689;
  xx[52] = 5.761055201783171e-5;
  pm_math_quatXform(xx + 74, xx + 50, xx + 70);
  xx[41] = 0.05616411811087859 - xx[70];
  xx[50] = 0.0571835327366057 - xx[71];
  xx[51] = 1.27783800291701e-3 - xx[72];
  xx[70] = 0.5825318883848122;
  xx[71] = - 0.4010029746776625;
  xx[72] = - 0.3908090503280067;
  xx[73] = 0.589170178722763;
  xx[52] = xx[4] * state[14];
  xx[53] = 1.097608589360951e-3;
  xx[63] = sin(xx[52]);
  xx[78] = 0.3697051536817836;
  xx[79] = 0.929148478229671;
  xx[80] = cos(xx[52]);
  xx[81] = xx[53] * xx[63];
  xx[82] = - (xx[78] * xx[63]);
  xx[83] = - (xx[79] * xx[63]);
  pm_math_quatCompose(xx + 70, xx + 80, xx + 84);
  xx[70] = 0.03061615818801665;
  xx[71] = - 0.01322209564824609;
  xx[72] = - 0.0382619833945911;
  pm_math_quatXform(xx + 84, xx + 70, xx + 80);
  xx[52] = 0.04059779762393732 - xx[80];
  xx[63] = 0.0193170576621871 - xx[81];
  xx[70] = 1.635538743043486e-4 - xx[82];
  xx[80] = - 0.7275997837833986;
  xx[81] = - 0.02609949381063035;
  xx[82] = 0.02069459829421983;
  xx[83] = - 0.685192750007341;
  xx[71] = xx[4] * state[16];
  xx[72] = 0.01481066366728059;
  xx[73] = sin(xx[71]);
  xx[88] = 0.02657170442164313;
  xx[89] = 0.9995371872851282;
  xx[90] = cos(xx[71]);
  xx[91] = xx[72] * xx[73];
  xx[92] = - (xx[88] * xx[73]);
  xx[93] = - (xx[89] * xx[73]);
  pm_math_quatCompose(xx + 80, xx + 90, xx + 94);
  xx[80] = 0.01467032838716747;
  xx[81] = 9.001466616098122e-4;
  xx[82] = 0.05430148122180607;
  pm_math_quatXform(xx + 94, xx + 80, xx + 90);
  xx[71] = - (0.04372636409114516 + xx[90]);
  xx[73] = - (3.436367721230651e-3 + xx[91]);
  xx[80] = 0.05337145165178726 - xx[92];
  xx[90] = 0.7209450228618058;
  xx[91] = 0.01540619596358531;
  xx[92] = 0.6924952431953817;
  xx[93] = - 0.02124291148809812;
  xx[81] = xx[4] * state[18];
  xx[82] = 0.02550084463230211;
  xx[83] = sin(xx[81]);
  xx[98] = 0.07003559973507219;
  xx[99] = 0.9972184924542806;
  xx[100] = cos(xx[81]);
  xx[101] = - (xx[82] * xx[83]);
  xx[102] = - (xx[98] * xx[83]);
  xx[103] = - (xx[99] * xx[83]);
  pm_math_quatCompose(xx + 90, xx + 100, xx + 104);
  xx[90] = 7.384449039615354e-4;
  xx[91] = 8.782132757742589e-3;
  xx[92] = 0.02104352117641159;
  pm_math_quatXform(xx + 104, xx + 90, xx + 100);
  xx[81] = - (0.04584639526640044 + xx[100]);
  xx[83] = - (1.667456195280402e-3 + xx[101]);
  xx[90] = - (4.019034562627846e-4 + xx[102]);
  xx[100] = - 0.4660778899715878;
  xx[101] = - 0.4623990275144091;
  xx[102] = - 0.683381556690801;
  xx[103] = 0.3192932630172755;
  xx[91] = xx[4] * state[20];
  xx[92] = 6.371293912065812e-4;
  xx[93] = sin(xx[91]);
  xx[108] = 0.02974831454233251;
  xx[109] = cos(xx[91]);
  xx[110] = - (xx[92] * xx[93]);
  xx[111] = xx[68] * xx[93];
  xx[112] = - (xx[108] * xx[93]);
  pm_math_quatCompose(xx + 100, xx + 109, xx + 113);
  xx[100] = 2.918705149378412e-5;
  xx[101] = 0.01252189717303686;
  xx[102] = 5.761055201769299e-5;
  pm_math_quatXform(xx + 113, xx + 100, xx + 109);
  xx[91] = - (0.07647175644016949 + xx[109]);
  xx[93] = 3.407073744455119e-4 - xx[110];
  xx[100] = 4.140473136936829e-4 - xx[111];
  xx[109] = 0.1696300705120354;
  xx[110] = - 0.01390716656233632;
  xx[111] = 0.9852897020712987;
  xx[112] = - 0.01537637436268199;
  xx[101] = xx[4] * state[22];
  xx[102] = 0.9432678151620474;
  xx[103] = sin(xx[101]);
  xx[117] = 0.0215703356316459;
  xx[118] = 0.3313314797904912;
  xx[119] = cos(xx[101]);
  xx[120] = xx[102] * xx[103];
  xx[121] = xx[117] * xx[103];
  xx[122] = - (xx[118] * xx[103]);
  pm_math_quatCompose(xx + 109, xx + 119, xx + 123);
  xx[109] = 0.0378257361915316;
  xx[110] = 0.02691855590336052;
  xx[111] = - 0.01377708912967916;
  pm_math_quatXform(xx + 123, xx + 109, xx + 119);
  xx[101] = - (0.0405977976239372 + xx[119]);
  xx[103] = - (0.01931705766218732 + xx[120]);
  xx[109] = 1.635538743045994e-4 - xx[121];
  xx[119] = 0.6556354619410489;
  xx[120] = 2.64068932041089e-3;
  xx[121] = - 0.7550725033429714;
  xx[122] = - 8.261359693557619e-4;
  xx[110] = xx[4] * state[24];
  xx[111] = 0.01982983347127269;
  xx[112] = sin(xx[110]);
  xx[127] = 0.01933003204555117;
  xx[128] = 0.9996164902429429;
  xx[129] = cos(xx[110]);
  xx[130] = xx[111] * xx[112];
  xx[131] = - (xx[127] * xx[112]);
  xx[132] = xx[128] * xx[112];
  pm_math_quatCompose(xx + 119, xx + 129, xx + 133);
  xx[119] = 0.01925958587157782;
  xx[120] = 6.240341084765325e-4;
  xx[121] = - 0.05446997619858423;
  pm_math_quatXform(xx + 133, xx + 119, xx + 129);
  xx[110] = 0.05458138978900429 - xx[129];
  xx[112] = - (0.04577468096523879 + xx[130]);
  xx[119] = 6.433943884371046e-3 - xx[131];
  xx[129] = - 0.01703518939330801;
  xx[130] = - 0.7227375455097629;
  xx[131] = 0.01737012217934593;
  xx[132] = - 0.6906942315441274;
  xx[120] = xx[4] * state[26];
  xx[121] = 0.02583706276149814;
  xx[122] = sin(xx[120]);
  xx[137] = 0.07033036209197371;
  xx[138] = 0.9971890925776668;
  xx[139] = cos(xx[120]);
  xx[140] = - (xx[121] * xx[122]);
  xx[141] = xx[137] * xx[122];
  xx[142] = - (xx[138] * xx[122]);
  pm_math_quatCompose(xx + 129, xx + 139, xx + 143);
  xx[129] = 7.434614751766506e-4;
  xx[130] = - 8.782553494620477e-3;
  xx[131] = 0.02104694588617022;
  pm_math_quatXform(xx + 143, xx + 129, xx + 139);
  xx[120] = - (0.04097722408321847 + xx[139]);
  xx[122] = - (1.769105081555034e-3 + xx[140]);
  xx[129] = 5.493507031209963e-4 - xx[141];
  xx[139] = 0.808058515386717;
  xx[140] = - 0.5536740475567987;
  xx[141] = - 0.1177453437013583;
  xx[142] = 0.1631640855388713;
  xx[130] = xx[4] * state[28];
  xx[131] = 1.484620017240163e-3;
  xx[132] = sin(xx[130]);
  xx[147] = 9.229790256801926e-4;
  xx[148] = 0.9999984720053939;
  xx[149] = cos(xx[130]);
  xx[150] = xx[131] * xx[132];
  xx[151] = xx[147] * xx[132];
  xx[152] = xx[148] * xx[132];
  pm_math_quatCompose(xx + 139, xx + 149, xx + 153);
  xx[139] = - 3.500659222250415e-5;
  xx[140] = - 2.66433610359981e-5;
  xx[141] = - 0.02167323854278397;
  pm_math_quatXform(xx + 153, xx + 139, xx + 149);
  xx[130] = - (0.0191573579648151 + xx[149]);
  xx[132] = 0.04963827558211937 - xx[150];
  xx[139] = 9.566317857259074e-3 - xx[151];
  xx[149] = - 0.9799620651713762;
  xx[150] = - 5.964624902333182e-4;
  xx[151] = 0.1991088984165456;
  xx[152] = - 5.444412631233409e-3;
  xx[140] = xx[4] * state[30];
  xx[141] = 0.920126753310796;
  xx[142] = sin(xx[140]);
  xx[157] = 3.149253572448663e-5;
  xx[158] = 0.391620679803754;
  xx[159] = cos(xx[140]);
  xx[160] = xx[141] * xx[142];
  xx[161] = xx[157] * xx[142];
  xx[162] = - (xx[158] * xx[142]);
  pm_math_quatCompose(xx + 149, xx + 159, xx + 163);
  xx[149] = 1.536362692233358e-3;
  xx[150] = - 3.998727840422418e-3;
  xx[151] = - 9.537646412640167e-3;
  pm_math_quatXform(xx + 163, xx + 149, xx + 159);
  xx[140] = - (0.01913949502225024 + xx[159]);
  xx[142] = - (4.244816014990821e-3 + xx[160]);
  xx[149] = 0.01213906931306866 - xx[161];
  xx[159] = - 0.7905366672633474;
  xx[160] = - 0.06410752291137295;
  xx[161] = - 0.4859731457059045;
  xx[162] = 0.3671132044356831;
  xx[150] = xx[4] * state[32];
  xx[151] = 0.5568218239321161;
  xx[152] = sin(xx[150]);
  xx[167] = 0.6914685293270615;
  xx[168] = 0.4602398606630924;
  xx[169] = cos(xx[150]);
  xx[170] = - (xx[151] * xx[152]);
  xx[171] = - (xx[167] * xx[152]);
  xx[172] = - (xx[168] * xx[152]);
  pm_math_quatCompose(xx + 159, xx + 169, xx + 173);
  xx[159] = - 8.534316509889412e-3;
  xx[160] = - 9.101773917150512e-3;
  xx[161] = - 0.01573699175212805;
  pm_math_quatXform(xx + 173, xx + 159, xx + 169);
  xx[150] = 1.624659067754514e-3 - xx[169];
  xx[152] = - (6.363405802280539e-7 + xx[170]);
  xx[159] = 0.01007666448438912 - xx[171];
  xx[169] = 0.05399662808619699;
  xx[170] = 0.3328043742661185;
  xx[171] = - 0.4028538291834181;
  xx[172] = 0.8509021124294594;
  xx[160] = xx[4] * state[34];
  xx[161] = 6.296232699670407e-3;
  xx[162] = sin(xx[160]);
  xx[177] = 5.947949081371294e-4;
  xx[178] = 0.9999800016364372;
  xx[179] = cos(xx[160]);
  xx[180] = xx[161] * xx[162];
  xx[181] = - (xx[177] * xx[162]);
  xx[182] = xx[178] * xx[162];
  pm_math_quatCompose(xx + 169, xx + 179, xx + 183);
  xx[169] = - 3.799393584838624e-3;
  xx[170] = - 2.753395776504228e-3;
  xx[171] = 0.02253009478038719;
  pm_math_quatXform(xx + 183, xx + 169, xx + 179);
  xx[160] = 8.009643636265877e-3 - xx[179];
  xx[162] = - (9.600823971459397e-3 + xx[180]);
  xx[169] = 0.01562282858737205 - xx[181];
  xx[179] = - 7.069641591237186e-4;
  xx[180] = - 0.9999761382903185;
  xx[181] = 5.27165295319329e-3;
  xx[182] = 4.408256662295412e-3;
  xx[170] = xx[4] * state[36];
  xx[171] = 0.999905553896681;
  xx[172] = sin(xx[170]);
  xx[187] = 0.01053682136615303;
  xx[188] = 8.82375668690405e-3;
  xx[189] = cos(xx[170]);
  xx[190] = - (xx[171] * xx[172]);
  xx[191] = xx[187] * xx[172];
  xx[192] = xx[188] * xx[172];
  pm_math_quatCompose(xx + 179, xx + 189, xx + 193);
  xx[179] = - 0.02679622357277588;
  xx[180] = - 9.935294733264433e-3;
  xx[181] = 3.233849799576197e-3;
  pm_math_quatXform(xx + 193, xx + 179, xx + 189);
  xx[179] = - 0.5028960700883474;
  xx[180] = - 0.5079765523218769;
  xx[181] = - 0.4963483493590561;
  xx[182] = - 0.4926395041705614;
  xx[170] = xx[4] * state[38];
  xx[172] = 0.9999356812616957;
  xx[192] = sin(xx[170]);
  xx[197] = 7.715298458388364e-6;
  xx[198] = 0.01134166126207947;
  xx[199] = cos(xx[170]);
  xx[200] = xx[172] * xx[192];
  xx[201] = - (xx[197] * xx[192]);
  xx[202] = - (xx[198] * xx[192]);
  pm_math_quatCompose(xx + 179, xx + 199, xx + 203);
  xx[179] = - 0.02533843967359211;
  xx[180] = 0.03600221606860162;
  xx[181] = 3.617657516123626e-4;
  pm_math_quatXform(xx + 203, xx + 179, xx + 199);
  xx[170] = - (1.403039915678841e-3 + xx[199]);
  xx[179] = - (0.02600916663331617 + xx[200]);
  xx[180] = - (0.02961461826731904 + xx[201]);
  xx[199] = - 0.6277727129295252;
  xx[200] = - 0.7779911183031492;
  xx[201] = 0.02486547329992229;
  xx[202] = 3.598469131593875e-3;
  xx[181] = xx[4] * state[40];
  xx[182] = 0.9983830344344976;
  xx[192] = sin(xx[181]);
  xx[207] = 0.04524897135752665;
  xx[208] = 0.03440707985939795;
  xx[209] = cos(xx[181]);
  xx[210] = xx[182] * xx[192];
  xx[211] = - (xx[207] * xx[192]);
  xx[212] = - (xx[208] * xx[192]);
  pm_math_quatCompose(xx + 199, xx + 209, xx + 213);
  xx[199] = 0.03138775984728189;
  xx[200] = 0.0482710246526309;
  xx[201] = - 0.01350668089361715;
  pm_math_quatXform(xx + 213, xx + 199, xx + 209);
  xx[181] = 0.02964743933847563 - xx[209];
  xx[192] = - (0.03599820814925153 + xx[210]);
  xx[199] = - (2.644304791534871e-4 + xx[211]);
  xx[209] = 0.5003677438883952;
  xx[210] = 0.4815111712447052;
  xx[211] = 0.477934081074098;
  xx[212] = - 0.5379201864500418;
  xx[200] = xx[4] * state[42];
  xx[201] = 2.311443388491929e-3;
  xx[202] = sin(xx[200]);
  xx[217] = 0.9999937986347783;
  xx[218] = 2.657051269523869e-3;
  xx[219] = cos(xx[200]);
  xx[220] = xx[201] * xx[202];
  xx[221] = xx[217] * xx[202];
  xx[222] = xx[218] * xx[202];
  pm_math_quatCompose(xx + 209, xx + 219, xx + 223);
  xx[209] = - 0.01001336574788117;
  xx[210] = - 0.0260563946297341;
  xx[211] = 0.01741537757656649;
  pm_math_quatXform(xx + 223, xx + 209, xx + 219);
  xx[200] = - (0.02649406766351854 + xx[219]);
  xx[202] = - (0.02247166617680568 + xx[220]);
  xx[209] = 4.303589688849823e-3 - xx[221];
  xx[219] = 0.9959728757072301;
  xx[220] = 2.516758736191865e-3;
  xx[221] = - 0.08748115921584165;
  xx[222] = 0.01946133508235365;
  xx[210] = xx[4] * state[44];
  xx[4] = 0.9983141841375302;
  xx[211] = sin(xx[210]);
  xx[212] = 0.0412824565969751;
  xx[227] = 0.04079887899363344;
  xx[228] = cos(xx[210]);
  xx[229] = xx[4] * xx[211];
  xx[230] = - (xx[212] * xx[211]);
  xx[231] = - (xx[227] * xx[211]);
  pm_math_quatCompose(xx + 219, xx + 228, xx + 232);
  xx[219] = - 0.03859440464093979;
  xx[220] = 9.091870791946941e-3;
  xx[221] = 1.58505388307718e-3;
  pm_math_quatXform(xx + 232, xx + 219, xx + 228);
  xx[210] = - (0.01965399087276073 + xx[228]);
  xx[211] = 1.676453710764403e-4 - xx[229];
  xx[219] = - (0.02082009718482823 + xx[230]);
  xx[220] = - (xx[6] * state[1]);
  xx[6] = - (xx[8] * state[1]);
  xx[8] = xx[9] * state[1];
  xx[9] = 0.01021668315434028 * state[1];
  xx[221] = 1.215941546968537e-4 * state[1];
  xx[222] = 2.997135641258827e-3 * state[1];
  xx[228] = xx[220];
  xx[229] = xx[6];
  xx[230] = xx[8];
  pm_math_quatInverseXform(xx + 24, xx + 228, xx + 236);
  xx[231] = xx[236] - xx[7] * state[3];
  xx[7] = xx[237] + xx[18] * state[3];
  xx[18] = xx[238] + xx[19] * state[3];
  pm_math_cross3(xx + 228, xx + 0, xx + 236);
  xx[228] = xx[236] - xx[9];
  xx[229] = xx[237] + xx[221];
  xx[230] = xx[238] + xx[222];
  pm_math_quatInverseXform(xx + 24, xx + 228, xx + 236);
  xx[19] = xx[236] + 4.083221482028722e-4 * state[3];
  xx[228] = xx[237] - 7.436248360610575e-5 * state[3];
  xx[229] = xx[238] + 0.03599970495786363 * state[3];
  xx[236] = xx[231];
  xx[237] = xx[7];
  xx[238] = xx[18];
  pm_math_quatInverseXform(xx + 34, xx + 236, xx + 239);
  xx[230] = xx[239] - xx[5] * state[5];
  xx[5] = xx[240] + xx[28] * state[5];
  xx[28] = xx[241] + xx[29] * state[5];
  xx[239] = xx[3];
  xx[240] = xx[13];
  xx[241] = xx[20];
  pm_math_cross3(xx + 236, xx + 239, xx + 242);
  xx[236] = xx[242] + xx[19];
  xx[237] = xx[243] + xx[228];
  xx[238] = xx[244] + xx[229];
  pm_math_quatInverseXform(xx + 34, xx + 236, xx + 239);
  xx[29] = xx[239] - 0.05389385178170958 * state[5];
  xx[236] = xx[240] + 0.0106559717126973 * state[5];
  xx[237] = xx[241] - 6.710078409916341e-4 * state[5];
  xx[238] = xx[230];
  xx[239] = xx[5];
  xx[240] = xx[28];
  pm_math_quatInverseXform(xx + 44, xx + 238, xx + 241);
  xx[244] = xx[241] + xx[22] * state[7];
  xx[22] = xx[242] + xx[38] * state[7];
  xx[38] = xx[243] + xx[39] * state[7];
  xx[241] = xx[21];
  xx[242] = xx[23];
  xx[243] = xx[30];
  pm_math_cross3(xx + 238, xx + 241, xx + 245);
  xx[238] = xx[245] + xx[29];
  xx[239] = xx[246] + xx[236];
  xx[240] = xx[247] + xx[237];
  pm_math_quatInverseXform(xx + 44, xx + 238, xx + 241);
  xx[39] = xx[241] - 0.01748450275387965 * state[7];
  xx[238] = xx[242] + 6.686068553002791e-5 * state[7];
  xx[239] = xx[243] - 9.953075770248402e-3 * state[7];
  xx[240] = xx[244];
  xx[241] = xx[22];
  xx[242] = xx[38];
  pm_math_quatInverseXform(xx + 54, xx + 240, xx + 245);
  xx[248] = xx[31];
  xx[249] = xx[33];
  xx[250] = xx[40];
  pm_math_cross3(xx + 240, xx + 248, xx + 251);
  xx[240] = xx[251] + xx[39];
  xx[241] = xx[252] + xx[238];
  xx[242] = xx[253] + xx[239];
  pm_math_quatInverseXform(xx + 54, xx + 240, xx + 248);
  xx[240] = xx[42] * state[11];
  xx[42] = - (xx[58] * state[11]);
  xx[58] = - (xx[59] * state[11]);
  xx[59] = 0.01105988704518323 * state[11];
  xx[241] = 5.520305563389003e-3 * state[11];
  xx[242] = 1.795198671644804e-3 * state[11];
  xx[251] = xx[240];
  xx[252] = xx[42];
  xx[253] = xx[58];
  pm_math_quatInverseXform(xx + 74, xx + 251, xx + 254);
  xx[243] = xx[254] + xx[43] * state[13];
  xx[43] = xx[255] - xx[68] * state[13];
  xx[254] = xx[256] - xx[69] * state[13];
  xx[255] = xx[41];
  xx[256] = xx[50];
  xx[257] = xx[51];
  pm_math_cross3(xx + 251, xx + 255, xx + 258);
  xx[255] = xx[258] + xx[59];
  xx[256] = xx[259] + xx[241];
  xx[257] = xx[260] - xx[242];
  pm_math_quatInverseXform(xx + 74, xx + 255, xx + 258);
  xx[69] = xx[258] + 4.300903788666212e-4 * state[13];
  xx[255] = xx[259] - 8.315602124560331e-7 * state[13];
  xx[256] = xx[260] + 3.715219671187979e-5 * state[13];
  xx[257] = xx[243];
  xx[258] = xx[43];
  xx[259] = xx[254];
  pm_math_quatInverseXform(xx + 84, xx + 257, xx + 260);
  xx[263] = xx[260] + xx[53] * state[15];
  xx[53] = xx[261] - xx[78] * state[15];
  xx[78] = xx[262] - xx[79] * state[15];
  xx[260] = xx[52];
  xx[261] = xx[63];
  xx[262] = xx[70];
  pm_math_cross3(xx + 257, xx + 260, xx + 264);
  xx[257] = xx[264] + xx[69];
  xx[258] = xx[265] + xx[255];
  xx[259] = xx[266] + xx[256];
  pm_math_quatInverseXform(xx + 84, xx + 257, xx + 260);
  xx[79] = xx[260] - 1.860362400492146e-3 * state[15];
  xx[257] = xx[261] + 0.02840496010801466 * state[15];
  xx[258] = xx[262] - 0.01130443878229363 * state[15];
  xx[259] = xx[263];
  xx[260] = xx[53];
  xx[261] = xx[78];
  pm_math_quatInverseXform(xx + 94, xx + 259, xx + 264);
  xx[262] = xx[264] + xx[72] * state[17];
  xx[72] = xx[265] - xx[88] * state[17];
  xx[88] = xx[266] - xx[89] * state[17];
  xx[264] = xx[71];
  xx[265] = xx[73];
  xx[266] = xx[80];
  pm_math_cross3(xx + 259, xx + 264, xx + 267);
  xx[259] = xx[267] + xx[79];
  xx[260] = xx[268] + xx[257];
  xx[261] = xx[269] + xx[258];
  pm_math_quatInverseXform(xx + 94, xx + 259, xx + 264);
  xx[89] = xx[264] + 5.431528463936659e-4 * state[17];
  xx[259] = xx[265] + 0.01546777974766987 * state[17];
  xx[260] = xx[266] - 4.031473991285829e-4 * state[17];
  xx[264] = xx[262];
  xx[265] = xx[72];
  xx[266] = xx[88];
  pm_math_quatInverseXform(xx + 104, xx + 264, xx + 267);
  xx[270] = xx[81];
  xx[271] = xx[83];
  xx[272] = xx[90];
  pm_math_cross3(xx + 264, xx + 270, xx + 273);
  xx[264] = xx[273] + xx[89];
  xx[265] = xx[274] + xx[259];
  xx[266] = xx[275] + xx[260];
  pm_math_quatInverseXform(xx + 104, xx + 264, xx + 270);
  pm_math_quatInverseXform(xx + 113, xx + 251, xx + 264);
  xx[261] = xx[264] - xx[92] * state[21];
  xx[92] = xx[265] + xx[68] * state[21];
  xx[68] = xx[266] - xx[108] * state[21];
  xx[264] = xx[91];
  xx[265] = xx[93];
  xx[266] = xx[100];
  pm_math_cross3(xx + 251, xx + 264, xx + 273);
  xx[264] = xx[273] + xx[59];
  xx[265] = xx[274] + xx[241];
  xx[266] = xx[275] - xx[242];
  pm_math_quatInverseXform(xx + 113, xx + 264, xx + 273);
  xx[108] = xx[273] - 4.300903788665039e-4 * state[21];
  xx[264] = xx[274] + 8.315602124662383e-7 * state[21];
  xx[265] = xx[275] + 3.715219671232309e-5 * state[21];
  xx[273] = xx[261];
  xx[274] = xx[92];
  xx[275] = xx[68];
  pm_math_quatInverseXform(xx + 123, xx + 273, xx + 276);
  xx[266] = xx[276] + xx[102] * state[23];
  xx[102] = xx[277] + xx[117] * state[23];
  xx[117] = xx[278] - xx[118] * state[23];
  xx[276] = xx[101];
  xx[277] = xx[103];
  xx[278] = xx[109];
  pm_math_cross3(xx + 273, xx + 276, xx + 279);
  xx[273] = xx[279] + xx[108];
  xx[274] = xx[280] + xx[264];
  xx[275] = xx[281] + xx[265];
  pm_math_quatInverseXform(xx + 123, xx + 273, xx + 276);
  xx[118] = xx[276] - 8.621788524729222e-3 * state[23];
  xx[273] = xx[277] - 4.626276161403507e-4 * state[23];
  xx[274] = xx[278] - 0.02457549358911488 * state[23];
  xx[275] = xx[266];
  xx[276] = xx[102];
  xx[277] = xx[117];
  pm_math_quatInverseXform(xx + 133, xx + 275, xx + 278);
  xx[281] = xx[278] + xx[111] * state[25];
  xx[111] = xx[279] - xx[127] * state[25];
  xx[127] = xx[280] + xx[128] * state[25];
  xx[278] = xx[110];
  xx[279] = xx[112];
  xx[280] = xx[119];
  pm_math_cross3(xx + 275, xx + 278, xx + 282);
  xx[275] = xx[282] + xx[118];
  xx[276] = xx[283] + xx[273];
  xx[277] = xx[284] + xx[274];
  pm_math_quatInverseXform(xx + 133, xx + 275, xx + 278);
  xx[128] = xx[278] - 4.291116001318472e-4 * state[25];
  xx[275] = xx[279] - 0.0203323301896813 * state[25];
  xx[276] = xx[280] - 3.846629045331276e-4 * state[25];
  xx[277] = xx[281];
  xx[278] = xx[111];
  xx[279] = xx[127];
  pm_math_quatInverseXform(xx + 143, xx + 277, xx + 282);
  xx[285] = xx[120];
  xx[286] = xx[122];
  xx[287] = xx[129];
  pm_math_cross3(xx + 277, xx + 285, xx + 288);
  xx[277] = xx[288] + xx[128];
  xx[278] = xx[289] + xx[275];
  xx[279] = xx[290] + xx[276];
  pm_math_quatInverseXform(xx + 143, xx + 277, xx + 285);
  pm_math_quatInverseXform(xx + 153, xx + 251, xx + 277);
  xx[280] = xx[277] + xx[131] * state[29];
  xx[131] = xx[278] + xx[147] * state[29];
  xx[147] = xx[279] + xx[148] * state[29];
  xx[277] = xx[130];
  xx[278] = xx[132];
  xx[279] = xx[139];
  pm_math_cross3(xx + 251, xx + 277, xx + 288);
  xx[251] = xx[288] + xx[59];
  xx[252] = xx[289] + xx[241];
  xx[253] = xx[290] - xx[242];
  pm_math_quatInverseXform(xx + 153, xx + 251, xx + 277);
  xx[148] = xx[277] - 6.639375731533006e-6 * state[29];
  xx[251] = xx[278] + 2.830014953581964e-6 * state[29];
  xx[252] = xx[279] + 7.244916738688701e-9 * state[29];
  xx[277] = xx[280];
  xx[278] = xx[131];
  xx[279] = xx[147];
  pm_math_quatInverseXform(xx + 163, xx + 277, xx + 288);
  xx[253] = xx[288] + xx[141] * state[31];
  xx[141] = xx[289] + xx[157] * state[31];
  xx[157] = xx[290] - xx[158] * state[31];
  xx[288] = xx[140];
  xx[289] = xx[142];
  xx[290] = xx[149];
  pm_math_cross3(xx + 277, xx + 288, xx + 291);
  xx[277] = xx[291] + xx[148];
  xx[278] = xx[292] + xx[251];
  xx[279] = xx[293] + xx[252];
  pm_math_quatInverseXform(xx + 163, xx + 277, xx + 288);
  xx[158] = xx[288] + 1.566284879886802e-3 * state[31];
  xx[277] = xx[289] - 8.174172225931404e-3 * state[31];
  xx[278] = xx[290] + 3.679384849138341e-3 * state[31];
  xx[288] = xx[253];
  xx[289] = xx[141];
  xx[290] = xx[157];
  pm_math_quatInverseXform(xx + 173, xx + 288, xx + 291);
  xx[279] = xx[291] - xx[151] * state[33];
  xx[151] = xx[292] - xx[167] * state[33];
  xx[167] = xx[293] - xx[168] * state[33];
  xx[291] = xx[150];
  xx[292] = xx[152];
  xx[293] = xx[159];
  pm_math_cross3(xx + 288, xx + 291, xx + 294);
  xx[288] = xx[294] + xx[158];
  xx[289] = xx[295] + xx[277];
  xx[290] = xx[296] + xx[278];
  pm_math_quatInverseXform(xx + 173, xx + 288, xx + 291);
  xx[168] = xx[291] - 6.692635383459758e-3 * state[33];
  xx[288] = xx[292] + 4.834867809258377e-3 * state[33];
  xx[289] = xx[293] + 8.331449323393829e-4 * state[33];
  xx[290] = xx[279];
  xx[291] = xx[151];
  xx[292] = xx[167];
  pm_math_quatInverseXform(xx + 183, xx + 290, xx + 293);
  xx[296] = xx[160];
  xx[297] = xx[162];
  xx[298] = xx[169];
  pm_math_cross3(xx + 290, xx + 296, xx + 299);
  xx[290] = xx[299] + xx[168];
  xx[291] = xx[300] + xx[288];
  xx[292] = xx[301] + xx[289];
  pm_math_quatInverseXform(xx + 183, xx + 290, xx + 296);
  xx[290] = - (xx[171] * state[37]);
  xx[171] = xx[187] * state[37];
  xx[187] = xx[188] * state[37];
  xx[188] = 1.217411210021088e-4 * state[37];
  xx[291] = 2.997101018129851e-3 * state[37];
  xx[292] = 0.01021670340446539 * state[37];
  xx[299] = xx[290];
  xx[300] = xx[171];
  xx[301] = xx[187];
  pm_math_quatInverseXform(xx + 203, xx + 299, xx + 302);
  xx[305] = xx[302] + xx[172] * state[39];
  xx[172] = xx[303] - xx[197] * state[39];
  xx[197] = xx[304] - xx[198] * state[39];
  xx[302] = xx[170];
  xx[303] = xx[179];
  xx[304] = xx[180];
  pm_math_cross3(xx + 299, xx + 302, xx + 306);
  xx[299] = xx[306] - xx[188];
  xx[300] = xx[307] - xx[291];
  xx[301] = xx[308] - xx[292];
  pm_math_quatInverseXform(xx + 203, xx + 299, xx + 302);
  xx[198] = xx[302] - 4.083221482035284e-4 * state[39];
  xx[299] = xx[303] + 7.436248360813993e-5 * state[39];
  xx[300] = xx[304] - 0.03599970495786338 * state[39];
  xx[301] = xx[305];
  xx[302] = xx[172];
  xx[303] = xx[197];
  pm_math_quatInverseXform(xx + 213, xx + 301, xx + 306);
  xx[304] = xx[306] + xx[182] * state[41];
  xx[182] = xx[307] - xx[207] * state[41];
  xx[207] = xx[308] - xx[208] * state[41];
  xx[306] = xx[181];
  xx[307] = xx[192];
  xx[308] = xx[199];
  pm_math_cross3(xx + 301, xx + 306, xx + 309);
  xx[301] = xx[309] + xx[198];
  xx[302] = xx[310] + xx[299];
  xx[303] = xx[311] + xx[300];
  pm_math_quatInverseXform(xx + 213, xx + 301, xx + 306);
  xx[208] = xx[306] - 2.272028417008573e-3 * state[41];
  xx[301] = xx[307] - 0.01240487989603491 * state[41];
  xx[302] = xx[308] - 0.04961323591426266 * state[41];
  xx[306] = xx[304];
  xx[307] = xx[182];
  xx[308] = xx[207];
  pm_math_quatInverseXform(xx + 223, xx + 306, xx + 309);
  xx[303] = xx[309] + xx[201] * state[43];
  xx[201] = xx[310] + xx[217] * state[43];
  xx[217] = xx[311] + xx[218] * state[43];
  xx[309] = xx[200];
  xx[310] = xx[202];
  xx[311] = xx[209];
  pm_math_cross3(xx + 306, xx + 309, xx + 312);
  xx[306] = xx[312] + xx[208];
  xx[307] = xx[313] + xx[301];
  xx[308] = xx[314] + xx[302];
  pm_math_quatInverseXform(xx + 223, xx + 306, xx + 309);
  xx[218] = xx[309] - 0.01748450275387981 * state[43];
  xx[306] = xx[310] + 6.68606855300597e-5 * state[43];
  xx[307] = xx[311] - 9.953075770248237e-3 * state[43];
  xx[308] = xx[303];
  xx[309] = xx[201];
  xx[310] = xx[217];
  pm_math_quatInverseXform(xx + 232, xx + 308, xx + 311);
  xx[314] = xx[210];
  xx[315] = xx[211];
  xx[316] = xx[219];
  pm_math_cross3(xx + 308, xx + 314, xx + 317);
  xx[308] = xx[317] + xx[218];
  xx[309] = xx[318] + xx[306];
  xx[310] = xx[319] + xx[307];
  pm_math_quatInverseXform(xx + 232, xx + 308, xx + 314);
  motionData[0] = xx[14];
  motionData[1] = xx[15];
  motionData[2] = xx[16];
  motionData[3] = xx[17];
  motionData[4] = - (1.123111416140438e-3 + xx[10]);
  motionData[5] = 0.1665126591109976 - xx[11];
  motionData[6] = 0.3095853829912624 - xx[12];
  motionData[7] = xx[24];
  motionData[8] = xx[25];
  motionData[9] = xx[26];
  motionData[10] = xx[27];
  motionData[11] = xx[0];
  motionData[12] = xx[1];
  motionData[13] = xx[2];
  motionData[14] = xx[34];
  motionData[15] = xx[35];
  motionData[16] = xx[36];
  motionData[17] = xx[37];
  motionData[18] = xx[3];
  motionData[19] = xx[13];
  motionData[20] = xx[20];
  motionData[21] = xx[44];
  motionData[22] = xx[45];
  motionData[23] = xx[46];
  motionData[24] = xx[47];
  motionData[25] = xx[21];
  motionData[26] = xx[23];
  motionData[27] = xx[30];
  motionData[28] = xx[54];
  motionData[29] = xx[55];
  motionData[30] = xx[56];
  motionData[31] = xx[57];
  motionData[32] = xx[31];
  motionData[33] = xx[33];
  motionData[34] = xx[40];
  motionData[35] = xx[64];
  motionData[36] = xx[65];
  motionData[37] = xx[66];
  motionData[38] = xx[67];
  motionData[39] = 0.0243268885838597 - xx[60];
  motionData[40] = 0.1126626591109976 - xx[61];
  motionData[41] = 0.3519853829912625 - xx[62];
  motionData[42] = xx[74];
  motionData[43] = xx[75];
  motionData[44] = xx[76];
  motionData[45] = xx[77];
  motionData[46] = xx[41];
  motionData[47] = xx[50];
  motionData[48] = xx[51];
  motionData[49] = xx[84];
  motionData[50] = xx[85];
  motionData[51] = xx[86];
  motionData[52] = xx[87];
  motionData[53] = xx[52];
  motionData[54] = xx[63];
  motionData[55] = xx[70];
  motionData[56] = xx[94];
  motionData[57] = xx[95];
  motionData[58] = xx[96];
  motionData[59] = xx[97];
  motionData[60] = xx[71];
  motionData[61] = xx[73];
  motionData[62] = xx[80];
  motionData[63] = xx[104];
  motionData[64] = xx[105];
  motionData[65] = xx[106];
  motionData[66] = xx[107];
  motionData[67] = xx[81];
  motionData[68] = xx[83];
  motionData[69] = xx[90];
  motionData[70] = xx[113];
  motionData[71] = xx[114];
  motionData[72] = xx[115];
  motionData[73] = xx[116];
  motionData[74] = xx[91];
  motionData[75] = xx[93];
  motionData[76] = xx[100];
  motionData[77] = xx[123];
  motionData[78] = xx[124];
  motionData[79] = xx[125];
  motionData[80] = xx[126];
  motionData[81] = xx[101];
  motionData[82] = xx[103];
  motionData[83] = xx[109];
  motionData[84] = xx[133];
  motionData[85] = xx[134];
  motionData[86] = xx[135];
  motionData[87] = xx[136];
  motionData[88] = xx[110];
  motionData[89] = xx[112];
  motionData[90] = xx[119];
  motionData[91] = xx[143];
  motionData[92] = xx[144];
  motionData[93] = xx[145];
  motionData[94] = xx[146];
  motionData[95] = xx[120];
  motionData[96] = xx[122];
  motionData[97] = xx[129];
  motionData[98] = xx[153];
  motionData[99] = xx[154];
  motionData[100] = xx[155];
  motionData[101] = xx[156];
  motionData[102] = xx[130];
  motionData[103] = xx[132];
  motionData[104] = xx[139];
  motionData[105] = xx[163];
  motionData[106] = xx[164];
  motionData[107] = xx[165];
  motionData[108] = xx[166];
  motionData[109] = xx[140];
  motionData[110] = xx[142];
  motionData[111] = xx[149];
  motionData[112] = xx[173];
  motionData[113] = xx[174];
  motionData[114] = xx[175];
  motionData[115] = xx[176];
  motionData[116] = xx[150];
  motionData[117] = xx[152];
  motionData[118] = xx[159];
  motionData[119] = xx[183];
  motionData[120] = xx[184];
  motionData[121] = xx[185];
  motionData[122] = xx[186];
  motionData[123] = xx[160];
  motionData[124] = xx[162];
  motionData[125] = xx[169];
  motionData[126] = xx[193];
  motionData[127] = xx[194];
  motionData[128] = xx[195];
  motionData[129] = xx[196];
  motionData[130] = - (1.523111416140227e-3 + xx[189]);
  motionData[131] = 0.05891845911099853 - xx[190];
  motionData[132] = 0.3095853829912625 - xx[191];
  motionData[133] = xx[203];
  motionData[134] = xx[204];
  motionData[135] = xx[205];
  motionData[136] = xx[206];
  motionData[137] = xx[170];
  motionData[138] = xx[179];
  motionData[139] = xx[180];
  motionData[140] = xx[213];
  motionData[141] = xx[214];
  motionData[142] = xx[215];
  motionData[143] = xx[216];
  motionData[144] = xx[181];
  motionData[145] = xx[192];
  motionData[146] = xx[199];
  motionData[147] = xx[223];
  motionData[148] = xx[224];
  motionData[149] = xx[225];
  motionData[150] = xx[226];
  motionData[151] = xx[200];
  motionData[152] = xx[202];
  motionData[153] = xx[209];
  motionData[154] = xx[232];
  motionData[155] = xx[233];
  motionData[156] = xx[234];
  motionData[157] = xx[235];
  motionData[158] = xx[210];
  motionData[159] = xx[211];
  motionData[160] = xx[219];
  motionData[161] = xx[220];
  motionData[162] = xx[6];
  motionData[163] = xx[8];
  motionData[164] = - xx[9];
  motionData[165] = xx[221];
  motionData[166] = xx[222];
  motionData[167] = xx[231];
  motionData[168] = xx[7];
  motionData[169] = xx[18];
  motionData[170] = xx[19];
  motionData[171] = xx[228];
  motionData[172] = xx[229];
  motionData[173] = xx[230];
  motionData[174] = xx[5];
  motionData[175] = xx[28];
  motionData[176] = xx[29];
  motionData[177] = xx[236];
  motionData[178] = xx[237];
  motionData[179] = xx[244];
  motionData[180] = xx[22];
  motionData[181] = xx[38];
  motionData[182] = xx[39];
  motionData[183] = xx[238];
  motionData[184] = xx[239];
  motionData[185] = xx[245] + xx[32] * state[9];
  motionData[186] = xx[246] + xx[48] * state[9];
  motionData[187] = xx[247] - xx[49] * state[9];
  motionData[188] = xx[248] - 7.495504550274049e-3 * state[9];
  motionData[189] = xx[249] + 5.738964567729521e-4 * state[9];
  motionData[190] = xx[250] + 2.223863204230623e-3 * state[9];
  motionData[191] = xx[240];
  motionData[192] = xx[42];
  motionData[193] = xx[58];
  motionData[194] = xx[59];
  motionData[195] = xx[241];
  motionData[196] = - xx[242];
  motionData[197] = xx[243];
  motionData[198] = xx[43];
  motionData[199] = xx[254];
  motionData[200] = xx[69];
  motionData[201] = xx[255];
  motionData[202] = xx[256];
  motionData[203] = xx[263];
  motionData[204] = xx[53];
  motionData[205] = xx[78];
  motionData[206] = xx[79];
  motionData[207] = xx[257];
  motionData[208] = xx[258];
  motionData[209] = xx[262];
  motionData[210] = xx[72];
  motionData[211] = xx[88];
  motionData[212] = xx[89];
  motionData[213] = xx[259];
  motionData[214] = xx[260];
  motionData[215] = xx[267] - xx[82] * state[19];
  motionData[216] = xx[268] - xx[98] * state[19];
  motionData[217] = xx[269] - xx[99] * state[19];
  motionData[218] = xx[270] - 7.283909563081741e-3 * state[19];
  motionData[219] = xx[271] + 1.997633498528372e-4 * state[19];
  motionData[220] = xx[272] + 1.722343712751907e-4 * state[19];
  motionData[221] = xx[261];
  motionData[222] = xx[92];
  motionData[223] = xx[68];
  motionData[224] = xx[108];
  motionData[225] = xx[264];
  motionData[226] = xx[265];
  motionData[227] = xx[266];
  motionData[228] = xx[102];
  motionData[229] = xx[117];
  motionData[230] = xx[118];
  motionData[231] = xx[273];
  motionData[232] = xx[274];
  motionData[233] = xx[281];
  motionData[234] = xx[111];
  motionData[235] = xx[127];
  motionData[236] = xx[128];
  motionData[237] = xx[275];
  motionData[238] = xx[276];
  motionData[239] = xx[282] - xx[121] * state[27];
  motionData[240] = xx[283] + xx[137] * state[27];
  motionData[241] = xx[284] - xx[138] * state[27];
  motionData[242] = xx[285] + 7.277627224710882e-3 * state[27];
  motionData[243] = xx[286] + 1.975804119990227e-4 * state[27];
  motionData[244] = xx[287] - 1.746274710961173e-4 * state[27];
  motionData[245] = xx[280];
  motionData[246] = xx[131];
  motionData[247] = xx[147];
  motionData[248] = xx[148];
  motionData[249] = xx[251];
  motionData[250] = xx[252];
  motionData[251] = xx[253];
  motionData[252] = xx[141];
  motionData[253] = xx[157];
  motionData[254] = xx[158];
  motionData[255] = xx[277];
  motionData[256] = xx[278];
  motionData[257] = xx[279];
  motionData[258] = xx[151];
  motionData[259] = xx[167];
  motionData[260] = xx[168];
  motionData[261] = xx[288];
  motionData[262] = xx[289];
  motionData[263] = xx[293] + xx[161] * state[35];
  motionData[264] = xx[294] - xx[177] * state[35];
  motionData[265] = xx[295] + xx[178] * state[35];
  motionData[266] = xx[296] - 2.739939927439236e-3 * state[35];
  motionData[267] = xx[297] + 3.941172322667344e-3 * state[35];
  motionData[268] = xx[298] + 1.95958804814312e-5 * state[35];
  motionData[269] = xx[290];
  motionData[270] = xx[171];
  motionData[271] = xx[187];
  motionData[272] = - xx[188];
  motionData[273] = - xx[291];
  motionData[274] = - xx[292];
  motionData[275] = xx[305];
  motionData[276] = xx[172];
  motionData[277] = xx[197];
  motionData[278] = xx[198];
  motionData[279] = xx[299];
  motionData[280] = xx[300];
  motionData[281] = xx[304];
  motionData[282] = xx[182];
  motionData[283] = xx[207];
  motionData[284] = xx[208];
  motionData[285] = xx[301];
  motionData[286] = xx[302];
  motionData[287] = xx[303];
  motionData[288] = xx[201];
  motionData[289] = xx[217];
  motionData[290] = xx[218];
  motionData[291] = xx[306];
  motionData[292] = xx[307];
  motionData[293] = xx[311] + xx[4] * state[45];
  motionData[294] = xx[312] - xx[212] * state[45];
  motionData[295] = xx[313] - xx[227] * state[45];
  motionData[296] = xx[314] - 3.055032181343929e-4 * state[45];
  motionData[297] = xx[315] + 7.773329321191826e-6 * state[45];
  motionData[298] = xx[316] - 7.48327173747066e-3 * state[45];
}

size_t ROBOT_2da83c1f_1_computeAssemblyError(const void *mech, const double
  *rtdv, size_t constraintIdx, const double *state, const double *motionData,
  double *error)
{
  (void) mech;
  (void)rtdv;
  (void) state;
  (void) motionData;
  (void) error;
  (void) state;
  switch (constraintIdx)
  {
  }

  return 0;
}

size_t ROBOT_2da83c1f_1_computeAssemblyJacobian(const void *mech, const double
  *rtdv, size_t constraintIdx, boolean_T forVelocitySatisfaction, const double
  *state, const double *motionData, double *J)
{
  (void) mech;
  (void) rtdv;
  (void) state;
  (void) forVelocitySatisfaction;
  (void) motionData;
  (void) J;
  switch (constraintIdx)
  {
  }

  return 0;
}

size_t ROBOT_2da83c1f_1_computeFullAssemblyJacobian(const void *mech, const
  double *rtdv, const double *state, const double *motionData, double *J)
{
  (void) mech;
  (void) rtdv;
  (void) state;
  (void) motionData;
  (void) J;
  return 0;
}

int ROBOT_2da83c1f_1_isInKinematicSingularity(const void *mech, const double
  *rtdv, size_t constraintIdx, const double *motionData)
{
  (void) mech;
  (void) rtdv
    ;
  (void) motionData;
  switch (constraintIdx)
  {
  }

  return 0;
}

PmfMessageId ROBOT_2da83c1f_1_convertStateVector(const void *asmMech, const
  double *rtdv, const void *simMech, const double *asmState, double *simState,
  void *neDiagMgr0)
{
  NeuDiagnosticManager *neDiagMgr = (NeuDiagnosticManager *) neDiagMgr0;
  (void) asmMech;
  (void) rtdv;
  (void) simMech;
  (void) neDiagMgr;
  simState[0] = asmState[0];
  simState[1] = asmState[1];
  simState[2] = asmState[2];
  simState[3] = asmState[3];
  simState[4] = asmState[4];
  simState[5] = asmState[5];
  simState[6] = asmState[6];
  simState[7] = asmState[7];
  simState[8] = asmState[8];
  simState[9] = asmState[9];
  simState[10] = asmState[10];
  simState[11] = asmState[11];
  simState[12] = asmState[12];
  simState[13] = asmState[13];
  simState[14] = asmState[14];
  simState[15] = asmState[15];
  simState[16] = asmState[16];
  simState[17] = asmState[17];
  simState[18] = asmState[18];
  simState[19] = asmState[19];
  simState[20] = asmState[20];
  simState[21] = asmState[21];
  simState[22] = asmState[22];
  simState[23] = asmState[23];
  simState[24] = asmState[24];
  simState[25] = asmState[25];
  simState[26] = asmState[26];
  simState[27] = asmState[27];
  simState[28] = asmState[28];
  simState[29] = asmState[29];
  simState[30] = asmState[30];
  simState[31] = asmState[31];
  simState[32] = asmState[32];
  simState[33] = asmState[33];
  simState[34] = asmState[34];
  simState[35] = asmState[35];
  simState[36] = asmState[36];
  simState[37] = asmState[37];
  simState[38] = asmState[38];
  simState[39] = asmState[39];
  simState[40] = asmState[40];
  simState[41] = asmState[41];
  simState[42] = asmState[42];
  simState[43] = asmState[43];
  simState[44] = asmState[44];
  simState[45] = asmState[45];
  return NULL;
}

void ROBOT_2da83c1f_1_constructStateVector(const void *mech, const double
  *solverState, const double *u, const double *uDot, double *discreteState,
  double *fullState)
{
  (void) mech;
  (void) solverState;
  (void) discreteState;
  fullState[0] = u[17];
  fullState[1] = uDot[17];
  fullState[2] = u[1];
  fullState[3] = uDot[1];
  fullState[4] = u[2];
  fullState[5] = uDot[2];
  fullState[6] = u[9];
  fullState[7] = uDot[9];
  fullState[8] = u[16];
  fullState[9] = uDot[16];
  fullState[10] = u[10];
  fullState[11] = uDot[10];
  fullState[12] = u[3];
  fullState[13] = uDot[3];
  fullState[14] = u[20];
  fullState[15] = uDot[20];
  fullState[16] = u[21];
  fullState[17] = uDot[21];
  fullState[18] = u[8];
  fullState[19] = uDot[8];
  fullState[20] = u[5];
  fullState[21] = uDot[5];
  fullState[22] = u[18];
  fullState[23] = uDot[18];
  fullState[24] = u[19];
  fullState[25] = uDot[19];
  fullState[26] = u[13];
  fullState[27] = uDot[13];
  fullState[28] = u[15];
  fullState[29] = uDot[15];
  fullState[30] = u[11];
  fullState[31] = uDot[11];
  fullState[32] = u[4];
  fullState[33] = uDot[4];
  fullState[34] = u[12];
  fullState[35] = uDot[12];
  fullState[36] = u[7];
  fullState[37] = uDot[7];
  fullState[38] = u[22];
  fullState[39] = uDot[22];
  fullState[40] = u[0];
  fullState[41] = uDot[0];
  fullState[42] = u[14];
  fullState[43] = uDot[14];
  fullState[44] = u[6];
  fullState[45] = uDot[6];
}

void ROBOT_2da83c1f_1_extractSolverStateVector(const void *mech, const double
  *fullState, double *solverState)
{
  (void) mech;
  (void) fullState;
  (void) solverState;
}

int ROBOT_2da83c1f_1_isPositionViolation(const void *mech, const double *rtdv,
  const int *eqnEnableFlags, const double *state)
{
  (void) mech;
  (void) rtdv;
  (void) eqnEnableFlags;
  (void) state;
  return 0;
}

int ROBOT_2da83c1f_1_isVelocityViolation(const void *mech, const double *rtdv,
  const int *eqnEnableFlags, const double *state)
{
  (void) mech;
  (void) rtdv;
  (void) eqnEnableFlags;
  (void) state;
  return 0;
}

PmfMessageId ROBOT_2da83c1f_1_projectStateSim(const void *mech, const double
  *rtdv, const int *eqnEnableFlags, const double *input, double *state, void
  *neDiagMgr0)
{
  NeuDiagnosticManager *neDiagMgr = (NeuDiagnosticManager *) neDiagMgr0;
  (void) mech;
  (void) rtdv;
  (void) eqnEnableFlags;
  (void) input;
  (void) state;
  (void) neDiagMgr;
  return NULL;
}
