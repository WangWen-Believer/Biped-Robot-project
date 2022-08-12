/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'ROBOT/Solver Configuration'.
 */

#include "pm_std.h"
#include "ne_std.h"
#include "ne_dae.h"
#include "pm_default_allocator.h"
#include "sm_ssci_NeDaePrivateData.h"
#include "sm_CTarget.h"

PmfMessageId sm_ssci_recordRunTimeError(
  const char *errorId, const char *errorMsg, NeuDiagnosticManager* mgr);

#define pm_allocator_alloc(_allocator, _m, _n) ((_allocator)->mCallocFcn((_allocator), (_m), (_n)))
#define PM_ALLOCATE_ARRAY(_name, _type, _size, _allocator)\
 _name = (_type *) pm_allocator_alloc(_allocator, sizeof(_type), _size)
#define pm_size_to_int(_size)          ((int32_T) (_size))

PmIntVector *pm_create_int_vector(size_t, PmAllocator *);
int_T pm_create_int_vector_fields (PmIntVector *, size_t, PmAllocator *);
int_T pm_create_real_vector_fields(PmRealVector *, size_t, PmAllocator *);
int_T pm_create_char_vector_fields(PmCharVector *, size_t, PmAllocator *);
int_T pm_create_bool_vector_fields(PmBoolVector *, size_t, PmAllocator *);
void pm_rv_equals_rv(const PmRealVector *, const PmRealVector *);
void sm_ssci_setupLoggerFcn_codeGen(const NeDae *dae,
  NeLoggerBuilder *neLoggerBuilder);
int32_T sm_ssci_logFcn_codeGen(const NeDae *dae,
  const NeSystemInput *systemInput,
  PmRealVector *output);
extern const NeAssertData ROBOT_2da83c1f_1_assertData[];
void ROBOT_2da83c1f_1_computeRuntimeParameters(
  const double *runtimeRootVariables,
  double *runtimeParameters);
void ROBOT_2da83c1f_1_validateRuntimeParameters(
  const double *runtimeParameters,
  int32_T *assertSatisfactionFlags);
void ROBOT_2da83c1f_1_computeAsmRuntimeDerivedValues(
  const double *runtimeParameters,
  double *runtimeDerivedValues);
void ROBOT_2da83c1f_1_computeSimRuntimeDerivedValues(
  const double *runtimeParameters,
  double *runtimeDerivedValues);
PmfMessageId ROBOT_2da83c1f_1_deriv(
  const double *,
  const int *,
  const double *,
  const double *, const double *, const double *,
  const double *,
  double *,
  double *,
  NeuDiagnosticManager *neDiagMgr);
PmfMessageId ROBOT_2da83c1f_1_checkDynamics(
  const double *,
  const double *,
  const double *, const double *, const double *,
  const double *,
  double *,
  NeuDiagnosticManager *neDiagMgr);
PmfMessageId ROBOT_2da83c1f_1_outputDyn(
  const double *,
  const int *,
  const double *,
  const double *, const double *, const double *,
  const double *,
  double *,
  double *,
  int *,
  double *,
  NeuDiagnosticManager *neDiagMgr);
PmfMessageId ROBOT_2da83c1f_1_outputKin(
  const double *,
  const double *,
  const double *, const double *, const double *,
  const double *,
  double *,
  NeuDiagnosticManager *neDiagMgr);
PmfMessageId ROBOT_2da83c1f_1_output (
  const double *,
  const double *,
  const double *, const double *, const double *,
  const double *,
  double *,
  NeuDiagnosticManager *neDiagMgr);
void ROBOT_2da83c1f_1_checkTargets(
  const double *runtimeDerivedValues,
  const double *stateVector);
void ROBOT_2da83c1f_1_setTargets(
  const double *runtimeDerivedValues,
  CTarget *targets);
void ROBOT_2da83c1f_1_resetStateVector(const void *mech, double *stateVector);
void ROBOT_2da83c1f_1_initializeTrackedAngleState(
  const void *mech,
  const double *runtimeDerivedValues,
  const double *motionData,
  double *stateVector,
  void *neDiagMgr);
void ROBOT_2da83c1f_1_computeDiscreteState(
  const void *mech,
  const double *runtimeDerivedValues,
  double *stateVector);
void ROBOT_2da83c1f_1_adjustPosition(
  const void *mech,
  const double *dofDeltas,
  double *stateVector);
void ROBOT_2da83c1f_1_perturbState(
  const void *mech,
  size_t stageIdx,
  size_t primitiveIdx,
  double magnitude,
  boolean_T doPerturbVelocity,
  double *stateVector);
void ROBOT_2da83c1f_1_computeDofBlendMatrix(
  const void *mech,
  size_t stageIdx,
  size_t primitiveIdx,
  const double *stateVector,
  int partialType,
  double *matrix);
void ROBOT_2da83c1f_1_projectPartiallyTargetedPos(
  const void *mech,
  size_t stageIdx,
  size_t primitiveIdx,
  const double *origStateVector,
  int partialType,
  double *stateVector);
void ROBOT_2da83c1f_1_propagateMotion(
  const void *mech,
  const double *runtimeDerivedValues,
  const double *stateVector,
  double *motionData);
size_t ROBOT_2da83c1f_1_computeAssemblyError(
  const void *mech,
  const double *runtimeDerivedValues,
  size_t constraintIdx,
  const double *stateVector,
  const double *motionData,
  double *error);
size_t ROBOT_2da83c1f_1_computeAssemblyJacobian(
  const void *mech,
  const double *runtimeDerivedValues,
  size_t constraintIdx,
  boolean_T forVelocitySatisfaction,
  const double *stateVector,
  const double *motionData,
  double *J);
size_t ROBOT_2da83c1f_1_computeFullAssemblyJacobian(
  const void *mech,
  const double *runtimeDerivedValues,
  const double *stateVector,
  const double *motionData,
  double *J);
int ROBOT_2da83c1f_1_isInKinematicSingularity(
  const void *mech,
  const double *runtimeDerivedValues,
  size_t constraintIdx,
  const double *motionData);
PmfMessageId ROBOT_2da83c1f_1_convertStateVector(
  const void *asmMech,
  const double *asmRuntimeDerivedValues,
  const void *simMech,
  const double *asmStateVector,
  double *simStateVector,
  void *neDiagMgr);
void ROBOT_2da83c1f_1_constructStateVector(
  const void *mech,
  const double *solverStateVector,
  const double *u,
  const double *uDot,
  const double *discreteStateVector,
  double *fullStateVector);
void ROBOT_2da83c1f_1_extractSolverStateVector(
  const void *mech,
  const double *fullStateVector,
  double *solverStateVector);
int ROBOT_2da83c1f_1_isPositionViolation(
  const void *mech,
  const double *runtimeDerivedValues,
  const int *constraintEqnEnableFlags,
  const double *stateVector);
int ROBOT_2da83c1f_1_isVelocityViolation(
  const void *mech,
  const double *runtimeDerivedValues,
  const int *constraintEqnEnableFlags,
  const double *stateVector);
PmfMessageId ROBOT_2da83c1f_1_projectStateSim(
  const void *mech,
  const double *runtimeDerivedValues,
  const int *constraintEqnEnableFlags,
  const double *inputVector,
  double *stateVector,
  void *neDiagMgr);
void ROBOT_2da83c1f_1_computeConstraintError(
  const void *mech,
  const double *runtimeDerivedValues,
  const double *stateVector,
  double *error);
PmfMessageId ROBOT_2da83c1f_1_assemble(const double *u, double *udot, double *x,
  NeuDiagnosticManager *neDiagMgr)
{
  (void) x;
  (void) u;
  (void) udot;
  (void) neDiagMgr;
  return NULL;
}

static
  void dae_cg_setParameters_function(const NeDae *dae,
  const NeParameterBundle *paramBundle)
{
  const NeDaePrivateData *smData = dae->mPrivateData;
  const double *runtimeRootVariables = paramBundle->mRealParameters.mX;
  if (smData->mRuntimeParameterScalars.mN == 0)
    return;
  ROBOT_2da83c1f_1_computeRuntimeParameters(
    runtimeRootVariables,
    smData->mRuntimeParameterScalars.mX);
  ROBOT_2da83c1f_1_computeAsmRuntimeDerivedValues(
    smData->mRuntimeParameterScalars.mX,
    smData->mAsmRuntimeDerivedValueScalars.mX);
  ROBOT_2da83c1f_1_computeSimRuntimeDerivedValues(
    smData->mRuntimeParameterScalars.mX,
    smData->mSimRuntimeDerivedValueScalars.mX);
  sm_core_computeRedundantConstraintEquations(
    &dae->mPrivateData->mSimulationDelegate,
    smData->mSimRuntimeDerivedValueScalars.mX);

#if 0

  {
    size_t i;
    const size_t n = smData->mSimulationDelegate.mRunTimeEnabledEquations.mSize;
    pmf_printf("\nRuntime Enabled Equations (%lu)\n", n);
    for (i = 0; i < n; ++i)
      pmf_printf("  %2lu:  %d\n", i,
                 smData->mSimulationDelegate.mRunTimeEnabledEquations.mValues[i]);
  }

#endif

}

static
  PmfMessageId dae_cg_pAssert_method(const NeDae *dae,
  const NeSystemInput *systemInput,
  NeDaeMethodOutput *daeMethodOutput,
  NeuDiagnosticManager *neDiagMgr)
{
  const NeDaePrivateData *smData = dae->mPrivateData;
  const double *runtimeParams = smData->mRuntimeParameterScalars.mX;
  int32_T *assertSatisfactionFlags = daeMethodOutput->mPASSERT.mX;
  (void) systemInput;
  (void) neDiagMgr;
  ROBOT_2da83c1f_1_validateRuntimeParameters(
    runtimeParams, assertSatisfactionFlags);
  return NULL;
}

static
  PmfMessageId dae_cg_deriv_method(const NeDae *dae,
  const NeSystemInput *systemInput,
  NeDaeMethodOutput *daeMethodOutput,
  NeuDiagnosticManager *neDiagMgr)
{
  const NeDaePrivateData *smData = dae->mPrivateData;
  PmfMessageId errorId = NULL;
  double errorResult = 0.0;
  if (smData->mCachedDerivativesAvailable)
    memcpy(daeMethodOutput->mXP0.mX, smData->mCachedDerivatives.mX,
           0 * sizeof(real_T));
  else
    errorId = ROBOT_2da83c1f_1_deriv(
      smData->mSimRuntimeDerivedValueScalars.mX,
      smData->mSimulationDelegate
      .mRunTimeEnabledEquations.mValues,
      systemInput->mX.mX,
      systemInput->mU.mX,
      systemInput->mU.mX + 23,
      systemInput->mV.mX + 23,
      systemInput->mD.mX,
      daeMethodOutput->mXP0.mX,
      &errorResult,
      neDiagMgr);
  return errorId;
}

static
  PmfMessageId dae_cg_output_method(const NeDae *dae,
  const NeSystemInput *systemInput,
  NeDaeMethodOutput *daeMethodOutput,
  NeuDiagnosticManager *neDiagMgr)
{
  PmfMessageId errorId = NULL;
  (void) dae;
  (void) systemInput;
  (void) daeMethodOutput;
  (void) neDiagMgr;
  return errorId;
}

static
  PmfMessageId dae_cg_project_solve(const NeDae *dae,
  const NeSystemInput *systemInput,
  NeuDiagnosticManager *neDiagMgr)
{
  NeDaePrivateData *smData = dae->mPrivateData;
  return
    sm_core_projectState(
    false,
    &smData->mSimulationDelegate,
    smData->mSimRuntimeDerivedValueScalars.mX,
    systemInput->mU.mX,
    systemInput->mU.mX + 23,
    systemInput->mD.mX,
    systemInput->mX.mX, neDiagMgr);
}

static
  PmfMessageId dae_cg_check_solve(const NeDae *dae,
  const NeSystemInput *systemInput,
  NeuDiagnosticManager *neDiagMgr)
{
  NeDaePrivateData *smData = dae->mPrivateData;
  PmfMessageId errorId = NULL;
  if (smData->mNumConstraintEqns > 0)
    errorId = sm_core_projectState(
      false,
      &smData->mSimulationDelegate,
      smData->mSimRuntimeDerivedValueScalars.mX,
      systemInput->mU.mX,
      systemInput->mU.mX + 23,
      systemInput->mD.mX,
      systemInput->mX.mX, neDiagMgr);
  if (errorId == NULL && smData->mDoCheckDynamics) {
    double result = 0.0;
    errorId = ROBOT_2da83c1f_1_checkDynamics(
      smData->mSimRuntimeDerivedValueScalars.mX,
      systemInput->mX.mX,
      systemInput->mU.mX,
      systemInput->mU.mX + 23,
      systemInput->mV.mX + 23,
      systemInput->mD.mX,
      &result, neDiagMgr);
  }

  return errorId;
}

static
  PmfMessageId dae_cg_projectMaybe_solve(const NeDae *dae,
  const NeSystemInput *systemInput,
  NeuDiagnosticManager *neDiagMgr)
{
  NeDaePrivateData *smData = dae->mPrivateData;
  return
    sm_core_projectState(
    true,
    &smData->mSimulationDelegate,
    smData->mSimRuntimeDerivedValueScalars.mX,
    systemInput->mU.mX,
    systemInput->mU.mX + 23,
    systemInput->mD.mX,
    systemInput->mX.mX, neDiagMgr);
}

static
  PmfMessageId dae_cg_assemble_solve(const NeDae *dae,
  const NeSystemInput *systemInput,
  NeuDiagnosticManager *neDiagMgr)
{
  NeDaePrivateData *smData = dae->mPrivateData;
  const SmMechanismDelegate *delegate = &smData->mAssemblyDelegate;
  const double *runtimeDerivedValues =
    smData->mAsmRuntimeDerivedValueScalars.mX;
  PmfMessageId errorId = NULL;
  size_t i;
  const size_t numTargets = 92;
  unsigned int asmStatus = 0;
  double *assemblyFullStateVector = smData->mAssemblyFullStateVector.mX;
  double *simulationFullStateVector = smData->mSimulationFullStateVector.mX;
  (*delegate->mSetTargets)(runtimeDerivedValues, smData->mTargets);

  {
    const double *u = systemInput->mU.mX;
    const double *uDot = u + smData->mInputVectorSize;
    CTarget *target = smData->mTargets + smData->mNumInternalTargets;
    for (i = 0; i < smData->mNumInputMotionPrimitives; ++i) {
      const size_t inputOffset = smData->mMotionInputOffsets.mX[i];
      (target++)->mValue[0] = u [inputOffset];
      (target++)->mValue[0] = uDot[inputOffset];
    }
  }

  errorId = sm_core_computeStateVector(
    delegate, runtimeDerivedValues, numTargets, smData->mTargets,
    assemblyFullStateVector, neDiagMgr);
  if (errorId != NULL)
    return errorId;
  asmStatus = sm_core_checkAssembly(
    delegate, runtimeDerivedValues, numTargets, smData->mTargets,
    assemblyFullStateVector, NULL, NULL, NULL);
  if (asmStatus != 1) {
    return sm_ssci_recordRunTimeError(
      "sm:compiler:messages:simulationErrors:AssemblyFailure",
      asmStatus == 2 ?
      "Model not assembled due to a position violation. The failure occurred during the attempt to assemble all joints in the system and satisfy any motion inputs. If an Update Diagram operation completes successfully, the failure is likely caused by motion inputs. Consider adjusting the motion inputs to specify a different starting configuration. Also consider adjusting or adding joint targets to better guide the assembly."
      :
      (asmStatus == 3 ?
       "Model not assembled due to a velocity violation. The failure occurred during the attempt to assemble all joints in the system and satisfy any motion inputs. If an Update Diagram operation completes successfully, the failure is likely caused by motion inputs. Consider adjusting the motion inputs to specify a different starting configuration. Also consider adjusting or adding joint targets to better guide the assembly."
       :
       "Model not assembled due to a singularity violation. The failure occurred during the attempt to assemble all joints in the system and satisfy any motion inputs. If an Update Diagram operation completes successfully, the failure is likely caused by motion inputs. Consider adjusting the motion inputs to specify a different starting configuration. Also consider adjusting or adding joint targets to better guide the assembly."),
      neDiagMgr);
  }

#if 0

  ROBOT_2da83c1f_1_checkTargets(
    smData->mSimRuntimeDerivedValueScalars.mX,
    assemblyFullStateVector);

#endif

  errorId =
    (*delegate->mConvertStateVector)(
    NULL, runtimeDerivedValues, NULL,
    assemblyFullStateVector, simulationFullStateVector,
    neDiagMgr);
  for (i = 0; i < smData->mStateVectorSize; ++i)
    systemInput->mX.mX[i] = simulationFullStateVector[smData->
      mStateVectorMap.mX[i]];
  memcpy(systemInput->mD.mX,
         simulationFullStateVector +
         smData->mFullStateVectorSize - smData->mDiscreteStateSize,
         smData->mDiscreteStateSize * sizeof(double));
  return errorId;
}

typedef struct {
  size_t first;
  size_t second;
} SizePair;

static void checkMemAllocStatus(int_T status)
{
  (void) status;
}

static
  PmCharVector cStringToCharVector(const char *src)
{
  const size_t n = strlen(src);
  PmCharVector charVect;
  const int_T status =
    pm_create_char_vector_fields(&charVect, n + 1, pm_default_allocator());
  checkMemAllocStatus(status);
  strcpy(charVect.mX, src);
  return charVect;
}

static
  void initBasicAttributes(NeDaePrivateData *smData)
{
  size_t i;
  smData->mStateVectorSize = 0;
  smData->mFullStateVectorSize = 46;
  smData->mDiscreteStateSize = 0;
  smData->mInputVectorSize = 23;
  smData->mOutputVectorSize = 0;
  smData->mNumConstraintEqns = 0;
  smData->mDoCheckDynamics = false;
  for (i = 0; i < 4; ++i)
    smData->mChecksum[i] = 0;
}

static
  void initStateVector(NeDaePrivateData *smData)
{
  PmAllocator *alloc = pm_default_allocator();
  const int32_T *stateVectorMap = NULL;
  const CTarget targets[92] = {
    { 0, 78, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 78, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 79, 0, false, 0, 1, "deg", false, true, +1.000000000000000000e+00, true,
      1, { +3.141017982595840900e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 79, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 80, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 80, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 81, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 81, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 82, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 82, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 83, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 83, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 84, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 84, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 85, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 85, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 86, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 86, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 87, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 87, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 88, 0, false, 0, 1, "deg", false, true, +1.000000000000000000e+00, true,
      1, { +3.141017982595840900e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 88, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 89, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 89, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 90, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 90, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 91, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 91, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 92, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 92, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 93, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 93, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 94, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 94, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 95, 0, false, 0, 1, "deg", false, true, +1.000000000000000000e+00, true,
      1, { +3.141017982595840900e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 95, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 96, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 96, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 97, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 97, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 98, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 98, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 99, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 99, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 100, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 100, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 95, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 95, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 79, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 79, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 80, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 80, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 87, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 87, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 94, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 94, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 88, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 88, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 81, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 81, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 98, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 98, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 99, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 99, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 86, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 86, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 83, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 83, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 96, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 96, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 97, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 97, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 91, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 91, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 93, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 93, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 89, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 89, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 82, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 82, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 90, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 90, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 85, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 85, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 100, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 100, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 78, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 78, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 92, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 92, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 84, 0, false, 0, 3, "", false, false, +1.000000000000000000e+00, true,
      1, { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } },

    { 0, 84, 0, false, 0, 3, "", true, false, +1.000000000000000000e+00, true, 1,
      { +0.000000000000000000e+00, +0.000000000000000000e+00,
        +0.000000000000000000e+00, +0.000000000000000000e+00 }, { +
        0.000000000000000000e+00 } }
  };

  const size_t numTargets = 92;
  int_T status;
  size_t i;
  status = pm_create_real_vector_fields(
    &smData->mAssemblyFullStateVector, 46, alloc);
  checkMemAllocStatus(status);
  status = pm_create_real_vector_fields(
    &smData->mSimulationFullStateVector, 46, alloc);
  checkMemAllocStatus(status);
  status = pm_create_int_vector_fields(
    &smData->mStateVectorMap, smData->mStateVectorSize, alloc);
  checkMemAllocStatus(status);
  memcpy(smData->mStateVectorMap.mX, stateVectorMap,
         smData->mStateVectorSize * sizeof(int32_T));
  smData->mNumInternalTargets = 46;
  smData->mNumInputMotionPrimitives = 23;
  PM_ALLOCATE_ARRAY(smData->mTargets, CTarget, numTargets, alloc);
  for (i = 0; i < numTargets; ++i)
    sm_compiler_CTarget_copy(targets + i, smData->mTargets + i);
}

static void initAsserts(NeDaePrivateData *smData)
{
  PmAllocator *alloc = pm_default_allocator();
  int_T status = 0;
  smData->mNumParamAsserts = 0;
  smData->mParamAssertObjects = NULL;
  smData->mParamAssertPaths = NULL;
  smData->mParamAssertDescriptors = NULL;
  smData->mParamAssertMessages = NULL;
  smData->mParamAssertMessageIds = NULL;
  status = pm_create_bool_vector_fields(
    &smData->mParamAssertIsWarnings, smData->mNumParamAsserts, alloc);
  checkMemAllocStatus(status);
  if (smData->mNumParamAsserts > 0) {
    const NeAssertData *ad = ROBOT_2da83c1f_1_assertData;
    size_t i;
    PM_ALLOCATE_ARRAY(smData->mParamAssertObjects,
                      PmCharVector, 0, alloc);
    PM_ALLOCATE_ARRAY(smData->mParamAssertPaths,
                      PmCharVector, 0, alloc);
    PM_ALLOCATE_ARRAY(smData->mParamAssertDescriptors,
                      PmCharVector, 0, alloc);
    PM_ALLOCATE_ARRAY(smData->mParamAssertMessages,
                      PmCharVector, 0, alloc);
    PM_ALLOCATE_ARRAY(smData->mParamAssertMessageIds,
                      PmCharVector, 0, alloc);
    for (i = 0; i < smData->mNumParamAsserts; ++i, ++ad) {
      smData->mParamAssertObjects [i] = cStringToCharVector(ad->mObject );
      smData->mParamAssertPaths [i] = cStringToCharVector(ad->mPath );
      smData->mParamAssertDescriptors[i] = cStringToCharVector(ad->mDescriptor);
      smData->mParamAssertMessages [i] = cStringToCharVector(ad->mMessage );
      smData->mParamAssertMessageIds [i] = cStringToCharVector(ad->mMessageID );
      smData->mParamAssertIsWarnings.mX[i] = ad->mIsWarn;
    }
  }
}

static
  void initVariables(NeDaePrivateData *smData)
{
  const char **varFullPaths = NULL;
  const char **varObjects = NULL;
  smData->mNumVarScalars = 0;
  smData->mVarFullPaths = NULL;
  smData->mVarObjects = NULL;
  if (smData->mNumVarScalars > 0) {
    size_t s;
    PmAllocator *alloc = pm_default_allocator();
    PM_ALLOCATE_ARRAY(smData->mVarFullPaths, PmCharVector, 0, alloc);
    PM_ALLOCATE_ARRAY(smData->mVarObjects, PmCharVector, 0, alloc);
    for (s = 0; s < smData->mNumVarScalars; ++s) {
      smData->mVarFullPaths[s] = cStringToCharVector(varFullPaths[s]);
      smData->mVarObjects[s] = cStringToCharVector(varObjects[s]);
    }
  }
}

static
  void initRuntimeParameters(NeDaePrivateData *smData)
{
  PmAllocator *alloc = pm_default_allocator();
  int_T status = 0;
  size_t i = 0;
  const int32_T *rtpRootVarRows = NULL;
  const int32_T *rtpRootVarCols = NULL;
  const char **rtpFullPaths = NULL;
  smData->mNumRtpRootVars = 0;
  status = pm_create_int_vector_fields(
    &smData->mRtpRootVarRows, smData->mNumRtpRootVars, alloc);
  checkMemAllocStatus(status);
  memcpy(smData->mRtpRootVarRows.mX, rtpRootVarRows,
         smData->mNumRtpRootVars * sizeof(int32_T));
  status = pm_create_int_vector_fields(
    &smData->mRtpRootVarCols, smData->mNumRtpRootVars, alloc);
  checkMemAllocStatus(status);
  memcpy(smData->mRtpRootVarCols.mX, rtpRootVarCols,
         smData->mNumRtpRootVars * sizeof(int32_T));
  smData->mRtpFullPaths = NULL;
  if (smData->mNumRtpRootVars > 0) {
    size_t v;
    PM_ALLOCATE_ARRAY(smData->mRtpFullPaths, PmCharVector, 0, alloc);
    for (v = 0; v < smData->mNumRtpRootVars; ++v) {
      smData->mRtpFullPaths[v] = cStringToCharVector(rtpFullPaths[v]);
    }
  }

  smData->mNumRuntimeRootVarScalars = 0;
  status = pm_create_real_vector_fields(
    &smData->mRuntimeParameterScalars, 0,
    alloc);
  checkMemAllocStatus(status);
  for (i = 0; i < smData->mRuntimeParameterScalars.mN; ++i)
    smData->mRuntimeParameterScalars.mX[i] = 0.0;
  status = pm_create_real_vector_fields(
    &smData->mAsmRuntimeDerivedValueScalars, 0,
    alloc);
  checkMemAllocStatus(status);
  for (i = 0; i < smData->mAsmRuntimeDerivedValueScalars.mN; ++i)
    smData->mAsmRuntimeDerivedValueScalars.mX[i] = 0.0;
  status = pm_create_real_vector_fields(
    &smData->mSimRuntimeDerivedValueScalars, 0,
    alloc);
  checkMemAllocStatus(status);
  for (i = 0; i < smData->mSimRuntimeDerivedValueScalars.mN; ++i)
    smData->mSimRuntimeDerivedValueScalars.mX[i] = 0.0;
}

static
  void initIoInfoHelper(
  size_t n,
  const char *portPathsSource[],
  const char *unitsSource[],
  const SizePair dimensions[],
  boolean_T doInputs,
  NeDaePrivateData *smData)
{
  PmCharVector *portPaths = NULL;
  PmCharVector *units = NULL;
  NeDsIoInfo *infos = NULL;
  if (n > 0) {
    size_t s;
    PmAllocator *alloc = pm_default_allocator();
    PM_ALLOCATE_ARRAY(portPaths, PmCharVector, n, alloc);
    PM_ALLOCATE_ARRAY(units, PmCharVector, n, alloc);
    PM_ALLOCATE_ARRAY(infos, NeDsIoInfo, n, alloc);
    for (s = 0; s < n; ++s) {
      portPaths[s] = cStringToCharVector(portPathsSource[s]);
      units[s] = cStringToCharVector(unitsSource[s]);

      {
        NeDsIoInfo *info = infos + s;
        info->mName = info->mIdentifier = portPaths[s].mX;
        info->mM = dimensions[s].first;
        info->mN = dimensions[s].second;
        info->mUnit = units[s].mX;
      }
    }
  }

  if (doInputs) {
    smData->mNumInputs = n;
    smData->mInputPortPaths = portPaths;
    smData->mInputUnits = units;
    smData->mInputInfos = infos;
  } else {
    smData->mNumOutputs = n;
    smData->mOutputPortPaths = portPaths;
    smData->mOutputUnits = units;
    smData->mOutputInfos = infos;
  }
}

static
  void initIoInfo(NeDaePrivateData *smData)
{
  const char *inputPortPaths[23] = {
    "Revolute1.qi",
    "Revolute10.qi",
    "Revolute11.qi",
    "Revolute13.qi",
    "Revolute14.qi",
    "Revolute15.qi",
    "Revolute16.qi",
    "Revolute17.qi",
    "Revolute18.qi",
    "Revolute2.qi",
    "Revolute20.qi",
    "Revolute21.qi",
    "Revolute22.qi",
    "Revolute23.qi",
    "Revolute24.qi",
    "Revolute25.qi",
    "Revolute3.qi",
    "Revolute4.qi",
    "Revolute5.qi",
    "Revolute6.qi",
    "Revolute7.qi",
    "Revolute8.qi",
    "Revolute9.qi"
  };

  const char *inputUnits[23] = {
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad",
    "rad"
  };

  const SizePair inputDimensions[23] = {
    { 1, 1 }, { 1, 1 }, { 1, 1 }, { 1, 1 },

    { 1, 1 }, { 1, 1 }, { 1, 1 }, { 1, 1 },

    { 1, 1 }, { 1, 1 }, { 1, 1 }, { 1, 1 },

    { 1, 1 }, { 1, 1 }, { 1, 1 }, { 1, 1 },

    { 1, 1 }, { 1, 1 }, { 1, 1 }, { 1, 1 },

    { 1, 1 }, { 1, 1 }, { 1, 1 }
  };

  const char **outputPortPaths = NULL;
  const char **outputUnits = NULL;
  const SizePair *outputDimensions = NULL;
  initIoInfoHelper(23, inputPortPaths, inputUnits, inputDimensions,
                   true, smData);
  initIoInfoHelper(0, outputPortPaths, outputUnits, outputDimensions,
                   false, smData);
}

static
  void initInputDerivs(NeDaePrivateData *smData)
{
  const int32_T numInputDerivs[23] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2
  };

  PmAllocator *alloc = pm_default_allocator();
  const int_T status = pm_create_int_vector_fields(
    &smData->mNumInputDerivs, smData->mInputVectorSize, alloc);
  checkMemAllocStatus(status);
  memcpy(smData->mNumInputDerivs.mX, numInputDerivs,
         23 * sizeof(int32_T));
  smData->mInputOrder = 2;
}

static
  void initDirectFeedthrough(NeDaePrivateData *smData)
{
  const boolean_T directFeedthroughVector[23] = {
    true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true,
    true, true, true
  };

  const boolean_T *directFeedthroughMatrix = NULL;
  PmAllocator *alloc = pm_default_allocator();

  {
    const int_T status = pm_create_bool_vector_fields(
      &smData->mDirectFeedthroughVector, 23, alloc);
    checkMemAllocStatus(status);
    memcpy(smData->mDirectFeedthroughVector.mX, directFeedthroughVector,
           23 * sizeof(boolean_T));
  }

  {
    const int_T status = pm_create_bool_vector_fields(
      &smData->mDirectFeedthroughMatrix, 0, alloc);
    checkMemAllocStatus(status);
    memcpy(smData->mDirectFeedthroughMatrix.mX, directFeedthroughMatrix,
           0 * sizeof(boolean_T));
  }
}

static
  void initOutputDerivProc(NeDaePrivateData *smData)
{
  PmAllocator *alloc = pm_default_allocator();
  const int32_T *outputFunctionMap = NULL;
  smData->mOutputFunctionMap = pm_create_int_vector(0, alloc);
  memcpy(smData->mOutputFunctionMap->mX, outputFunctionMap,
         0 * sizeof(int32_T));
  smData->mNumOutputClasses = 0;
  smData->mHasKinematicOutputs = false;
  smData->mHasDynamicOutputs = false;
  smData->mIsOutputClass0Dynamic = false;
  smData->mDoComputeDynamicOutputs = false;
  smData->mCachedDerivativesAvailable = false;

  {
    size_t i = 0;
    const int_T status = pm_create_real_vector_fields(
      &smData->mCachedDerivatives, 0, pm_default_allocator());
    checkMemAllocStatus(status);
    for (i = 0; i < smData->mCachedDerivatives.mN; ++i)
      smData->mCachedDerivatives.mX[i] = 0.0;
  }
}

#if 0

static void initializeSizePairVector(const SmSizePair *data,
  SmSizePairVector *vector)
{
  const size_t n = sm_core_SmSizePairVector_size(vector);
  size_t i;
  for (i = 0; i < n; ++i, ++data)
    sm_core_SmSizePairVector_setValue(vector, i, data++);
}

#endif

static
  void initAssemblyDelegate(SmMechanismDelegate *delegate)
{
  SmMechanismDelegateScratchpad *scratchpad = NULL;
  const SmSizePair jointToStageIdx[23] = {
    { 78, 20 }, { 79, 1 }, { 80, 2 }, { 81, 6 }, { 82, 16 }, { 83, 10 },

    { 84, 22 }, { 85, 18 }, { 86, 9 }, { 87, 3 }, { 88, 5 }, { 89, 15 },

    { 90, 17 }, { 91, 13 }, { 92, 21 }, { 93, 14 }, { 94, 4 }, { 95, 0 },

    { 96, 11 }, { 97, 12 }, { 98, 7 }, { 99, 8 }, { 100, 19 }
  };

  const size_t primitiveIndices[23 + 1] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23
  };

  const SmSizePair stateOffsets[23] = {
    { 0, 1 }, { 2, 3 }, { 4, 5 }, { 6, 7 }, { 8, 9 }, { 10, 11 },

    { 12, 13 }, { 14, 15 }, { 16, 17 }, { 18, 19 }, { 20, 21 }, { 22, 23 },

    { 24, 25 }, { 26, 27 }, { 28, 29 }, { 30, 31 }, { 32, 33 }, { 34, 35 },

    { 36, 37 }, { 38, 39 }, { 40, 41 }, { 42, 43 }, { 44, 45 }
  };

  const SmSizePair dofOffsets[23] = {
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 },

    { 6, 7 }, { 7, 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 }, { 11, 12 },

    { 12, 13 }, { 13, 14 }, { 14, 15 }, { 15, 16 }, { 16, 17 }, { 17, 18 },

    { 18, 19 }, { 19, 20 }, { 20, 21 }, { 21, 22 }, { 22, 23 }
  };

  const size_t remodIndices[23] = {
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18,
    20, 22, 24, 26, 28, 30, 32, 34, 36, 38,
    40, 42, 44
  };

  const size_t *equationsPerConstraint = NULL;
  const size_t dofToVelSlot[23] = {
    1, 3, 5, 7, 9, 11, 13, 15, 17, 19,
    21, 23, 25, 27, 29, 31, 33, 35, 37, 39,
    41, 43, 45
  };

  const size_t *constraintDofs = NULL;
  const size_t constraintDofOffsets[0 + 1] = {
    0
  };

  const size_t Jm = 0;
  const size_t Jn = 23;
  SmSizePair zeroSizePair;
  zeroSizePair.mFirst = zeroSizePair.mSecond = 0;
  sm_core_MechanismDelegate_allocScratchpad(delegate);
  scratchpad = delegate->mScratchpad;
  delegate->mTargetStrengthFree = 0;
  delegate->mTargetStrengthSuggested = 1;
  delegate->mTargetStrengthDesired = 2;
  delegate->mTargetStrengthRequired = 3;
  delegate->mConsistencyTol = +1.000000000000000100e-09;
  delegate->mDof = 23;
  delegate->mStateSize = 46;
  delegate->mContinuousStateSize = 46;
  delegate->mNumStages = 23;
  delegate->mNumConstraints = 0;
  delegate->mNumAllConstraintEquations = 0;
  sm_core_SmSizePairVector_create(
    &delegate->mJointToStageIdx, delegate->mNumStages, &zeroSizePair);
  memcpy(sm_core_SmSizePairVector_nonConstValues(&delegate->mJointToStageIdx),
         jointToStageIdx, delegate->mNumStages * sizeof(SmSizePair));
  sm_core_SmSizeTVector_create(
    &delegate->mPrimitiveIndices, delegate->mNumStages + 1, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mPrimitiveIndices),
         primitiveIndices, (delegate->mNumStages + 1) * sizeof(size_t));
  sm_core_SmSizePairVector_create(
    &delegate->mStateOffsets, 23, &zeroSizePair);
  memcpy(sm_core_SmSizePairVector_nonConstValues(&delegate->mStateOffsets),
         stateOffsets, 23 * sizeof(SmSizePair));
  sm_core_SmSizePairVector_create(
    &delegate->mDofOffsets, 23, &zeroSizePair);
  memcpy(sm_core_SmSizePairVector_nonConstValues(&delegate->mDofOffsets),
         dofOffsets, 23 * sizeof(SmSizePair));
  sm_core_SmSizeTVector_create(
    &delegate->mRemodIndices, 23, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mRemodIndices),
         remodIndices, 23 * sizeof(size_t));
  sm_core_SmSizeTVector_create(
    &delegate->mEquationsPerConstraint, delegate->mNumConstraints, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mEquationsPerConstraint),
         equationsPerConstraint, delegate->mNumConstraints * sizeof(size_t));
  sm_core_SmIntVector_create(
    &delegate->mRunTimeEnabledEquations,
    delegate->mNumAllConstraintEquations, 1);
  sm_core_SmSizeTVector_create(
    &delegate->mDofToVelSlot, delegate->mDof, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mDofToVelSlot),
         dofToVelSlot, delegate->mDof * sizeof(size_t));
  sm_core_SmSizeTVector_create(
    &delegate->mConstraintDofs, 0, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mConstraintDofs),
         constraintDofs, 0 * sizeof(size_t));
  sm_core_SmSizeTVector_create(
    &delegate->mConstraintDofOffsets, delegate->mNumConstraints + 1, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mConstraintDofOffsets),
         constraintDofOffsets, (delegate->mNumConstraints + 1) * sizeof(size_t));
  sm_core_SmBoundedSet_create(&scratchpad->mPosRequired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosDesired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosSuggested, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosFree, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosNonRequired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosSuggAndFree, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelRequired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelDesired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelSuggested, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelFree, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelNonRequired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelSuggAndFree, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mConstraintFilter, 0);
  sm_core_SmBoundedSet_create(&scratchpad->mActiveConstraints, 0);
  sm_core_SmBoundedSet_create(&scratchpad->mActiveDofs, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mActiveDofs0, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mNewConstraints, 0);
  sm_core_SmBoundedSet_create(&scratchpad->mNewDofs, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mUnsatisfiedConstraints, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mActiveConstraintsVect,
    0, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mActiveDofsVect, 23, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mFullDofToActiveDof, 23, 0);
  sm_core_SmSizePairVector_create(
    &scratchpad->mPartiallyPosTargetedPrims, 23, &zeroSizePair);
  sm_core_SmSizePairVector_create(
    &scratchpad->mPartiallyVelTargetedPrims, 23, &zeroSizePair);
  sm_core_SmSizeTVector_create(&scratchpad->mPosPartialTypes, 23, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mVelPartialTypes, 23, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mPartiallyActivePrims, 23, 0);
  sm_core_SmSizePairVector_create(
    &scratchpad->mBaseFrameVelOffsets, 0, &zeroSizePair);
  sm_core_SmSizePairVector_create(
    &scratchpad->mCvVelOffsets, 23, &zeroSizePair);
  sm_core_SmRealVector_create(
    &scratchpad->mCvAzimuthValues, 23, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mInitialState, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mStartState, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mTestState, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mFullStateVector, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mJacobianRowMaj, Jm * Jn, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mJacobian, Jm * Jn, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mJacobianPrimSubmatrix, Jm * 6, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mConstraintNonhomoTerms, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mConstraintError, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mBestConstraintError, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mDeltas,
    Jn * (Jm <= Jn ? Jm : Jn), 0.0);
  sm_core_SmRealVector_create(&scratchpad->mSvdWork, 576, 0.0);
  sm_core_SmRealVector_create(
    &scratchpad->mLineSearchScaledDeltaVect, 23, 0.0);
  sm_core_SmRealVector_create(
    &scratchpad->mLineSearchTestStateVect, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mLineSearchErrorVect, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mActiveDofVelsVect, 23, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mVelSystemRhs, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mMotionData, 299, 0.0);
  delegate->mSetTargets = ROBOT_2da83c1f_1_setTargets;
  delegate->mResetStateVector = ROBOT_2da83c1f_1_resetStateVector;
  delegate->mInitializeTrackedAngleState =
    ROBOT_2da83c1f_1_initializeTrackedAngleState;
  delegate->mComputeDiscreteState = ROBOT_2da83c1f_1_computeDiscreteState;
  delegate->mAdjustPosition = ROBOT_2da83c1f_1_adjustPosition;
  delegate->mPerturbState = ROBOT_2da83c1f_1_perturbState;
  delegate->mComputeDofBlendMatrix = ROBOT_2da83c1f_1_computeDofBlendMatrix;
  delegate->mProjectPartiallyTargetedPos =
    ROBOT_2da83c1f_1_projectPartiallyTargetedPos;
  delegate->mPropagateMotion = ROBOT_2da83c1f_1_propagateMotion;
  delegate->mComputeAssemblyError = ROBOT_2da83c1f_1_computeAssemblyError;
  delegate->mComputeAssemblyJacobian = ROBOT_2da83c1f_1_computeAssemblyJacobian;
  delegate->mComputeFullAssemblyJacobian =
    ROBOT_2da83c1f_1_computeFullAssemblyJacobian;
  delegate->mIsInKinematicSingularity =
    ROBOT_2da83c1f_1_isInKinematicSingularity;
  delegate->mConvertStateVector = ROBOT_2da83c1f_1_convertStateVector;
  delegate->mConstructStateVector = ROBOT_2da83c1f_1_constructStateVector;
  delegate->mExtractSolverStateVector =
    ROBOT_2da83c1f_1_extractSolverStateVector;
  delegate->mIsPositionViolation = ROBOT_2da83c1f_1_isPositionViolation;
  delegate->mIsVelocityViolation = ROBOT_2da83c1f_1_isVelocityViolation;
  delegate->mProjectStateSim = ROBOT_2da83c1f_1_projectStateSim;
  delegate->mComputeConstraintError = ROBOT_2da83c1f_1_computeConstraintError;
  delegate->mMech = NULL;
}

static
  void initSimulationDelegate(SmMechanismDelegate *delegate)
{
  SmMechanismDelegateScratchpad *scratchpad = NULL;
  const SmSizePair jointToStageIdx[23] = {
    { 78, 20 }, { 79, 1 }, { 80, 2 }, { 81, 6 }, { 82, 16 }, { 83, 10 },

    { 84, 22 }, { 85, 18 }, { 86, 9 }, { 87, 3 }, { 88, 5 }, { 89, 15 },

    { 90, 17 }, { 91, 13 }, { 92, 21 }, { 93, 14 }, { 94, 4 }, { 95, 0 },

    { 96, 11 }, { 97, 12 }, { 98, 7 }, { 99, 8 }, { 100, 19 }
  };

  const size_t primitiveIndices[23 + 1] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23
  };

  const SmSizePair stateOffsets[23] = {
    { 0, 1 }, { 2, 3 }, { 4, 5 }, { 6, 7 }, { 8, 9 }, { 10, 11 },

    { 12, 13 }, { 14, 15 }, { 16, 17 }, { 18, 19 }, { 20, 21 }, { 22, 23 },

    { 24, 25 }, { 26, 27 }, { 28, 29 }, { 30, 31 }, { 32, 33 }, { 34, 35 },

    { 36, 37 }, { 38, 39 }, { 40, 41 }, { 42, 43 }, { 44, 45 }
  };

  const SmSizePair dofOffsets[23] = {
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 },

    { 6, 7 }, { 7, 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 }, { 11, 12 },

    { 12, 13 }, { 13, 14 }, { 14, 15 }, { 15, 16 }, { 16, 17 }, { 17, 18 },

    { 18, 19 }, { 19, 20 }, { 20, 21 }, { 21, 22 }, { 22, 23 }
  };

  const size_t remodIndices[23] = {
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18,
    20, 22, 24, 26, 28, 30, 32, 34, 36, 38,
    40, 42, 44
  };

  const size_t *equationsPerConstraint = NULL;
  const size_t dofToVelSlot[23] = {
    1, 3, 5, 7, 9, 11, 13, 15, 17, 19,
    21, 23, 25, 27, 29, 31, 33, 35, 37, 39,
    41, 43, 45
  };

  const size_t *constraintDofs = NULL;
  const size_t constraintDofOffsets[0 + 1] = {
    0
  };

  const size_t Jm = 0;
  const size_t Jn = 23;
  SmSizePair zeroSizePair;
  zeroSizePair.mFirst = zeroSizePair.mSecond = 0;
  sm_core_MechanismDelegate_allocScratchpad(delegate);
  scratchpad = delegate->mScratchpad;
  delegate->mTargetStrengthFree = 0;
  delegate->mTargetStrengthSuggested = 1;
  delegate->mTargetStrengthDesired = 2;
  delegate->mTargetStrengthRequired = 3;
  delegate->mConsistencyTol = +1.000000000000000100e-09;
  delegate->mDof = 23;
  delegate->mStateSize = 46;
  delegate->mContinuousStateSize = 46;
  delegate->mNumStages = 23;
  delegate->mNumConstraints = 0;
  delegate->mNumAllConstraintEquations = 0;
  sm_core_SmSizePairVector_create(
    &delegate->mJointToStageIdx, delegate->mNumStages, &zeroSizePair);
  memcpy(sm_core_SmSizePairVector_nonConstValues(&delegate->mJointToStageIdx),
         jointToStageIdx, delegate->mNumStages * sizeof(SmSizePair));
  sm_core_SmSizeTVector_create(
    &delegate->mPrimitiveIndices, delegate->mNumStages + 1, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mPrimitiveIndices),
         primitiveIndices, (delegate->mNumStages + 1) * sizeof(size_t));
  sm_core_SmSizePairVector_create(
    &delegate->mStateOffsets, 23, &zeroSizePair);
  memcpy(sm_core_SmSizePairVector_nonConstValues(&delegate->mStateOffsets),
         stateOffsets, 23 * sizeof(SmSizePair));
  sm_core_SmSizePairVector_create(
    &delegate->mDofOffsets, 23, &zeroSizePair);
  memcpy(sm_core_SmSizePairVector_nonConstValues(&delegate->mDofOffsets),
         dofOffsets, 23 * sizeof(SmSizePair));
  sm_core_SmSizeTVector_create(
    &delegate->mRemodIndices, 23, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mRemodIndices),
         remodIndices, 23 * sizeof(size_t));
  sm_core_SmSizeTVector_create(
    &delegate->mEquationsPerConstraint, delegate->mNumConstraints, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mEquationsPerConstraint),
         equationsPerConstraint, delegate->mNumConstraints * sizeof(size_t));
  sm_core_SmIntVector_create(
    &delegate->mRunTimeEnabledEquations,
    delegate->mNumAllConstraintEquations, 1);
  sm_core_SmSizeTVector_create(
    &delegate->mDofToVelSlot, delegate->mDof, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mDofToVelSlot),
         dofToVelSlot, delegate->mDof * sizeof(size_t));
  sm_core_SmSizeTVector_create(
    &delegate->mConstraintDofs, 0, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mConstraintDofs),
         constraintDofs, 0 * sizeof(size_t));
  sm_core_SmSizeTVector_create(
    &delegate->mConstraintDofOffsets, delegate->mNumConstraints + 1, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mConstraintDofOffsets),
         constraintDofOffsets, (delegate->mNumConstraints + 1) * sizeof(size_t));
  sm_core_SmBoundedSet_create(&scratchpad->mPosRequired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosDesired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosSuggested, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosFree, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosNonRequired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mPosSuggAndFree, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelRequired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelDesired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelSuggested, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelFree, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelNonRequired, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mVelSuggAndFree, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mConstraintFilter, 0);
  sm_core_SmBoundedSet_create(&scratchpad->mActiveConstraints, 0);
  sm_core_SmBoundedSet_create(&scratchpad->mActiveDofs, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mActiveDofs0, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mNewConstraints, 0);
  sm_core_SmBoundedSet_create(&scratchpad->mNewDofs, 23);
  sm_core_SmBoundedSet_create(&scratchpad->mUnsatisfiedConstraints, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mActiveConstraintsVect,
    0, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mActiveDofsVect, 23, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mFullDofToActiveDof, 23, 0);
  sm_core_SmSizePairVector_create(
    &scratchpad->mPartiallyPosTargetedPrims, 23, &zeroSizePair);
  sm_core_SmSizePairVector_create(
    &scratchpad->mPartiallyVelTargetedPrims, 23, &zeroSizePair);
  sm_core_SmSizeTVector_create(&scratchpad->mPosPartialTypes, 23, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mVelPartialTypes, 23, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mPartiallyActivePrims, 23, 0);
  sm_core_SmSizePairVector_create(
    &scratchpad->mBaseFrameVelOffsets, 0, &zeroSizePair);
  sm_core_SmSizePairVector_create(
    &scratchpad->mCvVelOffsets, 23, &zeroSizePair);
  sm_core_SmRealVector_create(
    &scratchpad->mCvAzimuthValues, 23, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mInitialState, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mStartState, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mTestState, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mFullStateVector, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mJacobianRowMaj, Jm * Jn, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mJacobian, Jm * Jn, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mJacobianPrimSubmatrix, Jm * 6, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mConstraintNonhomoTerms, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mConstraintError, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mBestConstraintError, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mDeltas,
    Jn * (Jm <= Jn ? Jm : Jn), 0.0);
  sm_core_SmRealVector_create(&scratchpad->mSvdWork, 576, 0.0);
  sm_core_SmRealVector_create(
    &scratchpad->mLineSearchScaledDeltaVect, 23, 0.0);
  sm_core_SmRealVector_create(
    &scratchpad->mLineSearchTestStateVect, 46, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mLineSearchErrorVect, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mActiveDofVelsVect, 23, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mVelSystemRhs, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mMotionData, 299, 0.0);
  delegate->mSetTargets = NULL;
  delegate->mResetStateVector = ROBOT_2da83c1f_1_resetStateVector;
  delegate->mInitializeTrackedAngleState =
    ROBOT_2da83c1f_1_initializeTrackedAngleState;
  delegate->mComputeDiscreteState = ROBOT_2da83c1f_1_computeDiscreteState;
  delegate->mAdjustPosition = ROBOT_2da83c1f_1_adjustPosition;
  delegate->mPerturbState = ROBOT_2da83c1f_1_perturbState;
  delegate->mComputeDofBlendMatrix = NULL;
  delegate->mProjectPartiallyTargetedPos = NULL;
  delegate->mPropagateMotion = ROBOT_2da83c1f_1_propagateMotion;
  delegate->mComputeAssemblyError = ROBOT_2da83c1f_1_computeAssemblyError;
  delegate->mComputeAssemblyJacobian = ROBOT_2da83c1f_1_computeAssemblyJacobian;
  delegate->mComputeFullAssemblyJacobian =
    ROBOT_2da83c1f_1_computeFullAssemblyJacobian;
  delegate->mIsInKinematicSingularity =
    ROBOT_2da83c1f_1_isInKinematicSingularity;
  delegate->mConvertStateVector = ROBOT_2da83c1f_1_convertStateVector;
  delegate->mConstructStateVector = ROBOT_2da83c1f_1_constructStateVector;
  delegate->mExtractSolverStateVector =
    ROBOT_2da83c1f_1_extractSolverStateVector;
  delegate->mIsPositionViolation = ROBOT_2da83c1f_1_isPositionViolation;
  delegate->mIsVelocityViolation = ROBOT_2da83c1f_1_isVelocityViolation;
  delegate->mProjectStateSim = ROBOT_2da83c1f_1_projectStateSim;
  delegate->mComputeConstraintError = ROBOT_2da83c1f_1_computeConstraintError;
  delegate->mMech = NULL;
}

static
  void initMechanismDelegates(NeDaePrivateData *smData)
{
  PmAllocator *alloc = pm_default_allocator();
  const int32_T motionInputOffsets[23] = {
    17, 1, 2, 9, 16, 10, 3, 20, 21, 8,
    5, 18, 19, 13, 15, 11, 4, 12, 7, 22,
    0, 14, 6
  };

  int_T status = 0;
  initAssemblyDelegate(&smData->mAssemblyDelegate);
  initSimulationDelegate(&smData->mSimulationDelegate);
  status = pm_create_int_vector_fields(
    &smData->mMotionInputOffsets, smData->mNumInputMotionPrimitives, alloc);
  checkMemAllocStatus(status);
  memcpy(smData->mMotionInputOffsets.mX, motionInputOffsets,
         23 * sizeof(int32_T));
}

static
  void initComputationFcnPtrs(NeDaePrivateData *smData)
{
  smData->mSetParametersFcn = dae_cg_setParameters_function;
  smData->mPAssertFcn = dae_cg_pAssert_method;
  smData->mDerivativeFcn = dae_cg_deriv_method;
  smData->mOutputFcn = dae_cg_output_method;
  smData->mProjectionFcn = dae_cg_project_solve;
  smData->mProjectionMaybeFcn = dae_cg_projectMaybe_solve;
  smData->mCheckFcn =
    (smData->mStateVectorSize == 0) ? dae_cg_check_solve : NULL;
  smData->mAssemblyFcn = dae_cg_assemble_solve;
  smData->mSetupLoggerFcn = sm_ssci_setupLoggerFcn_codeGen;
  smData->mLogFcn = sm_ssci_logFcn_codeGen;
  smData->mResidualsFcn = NULL;
  smData->mLinearizeFcn = NULL;
  smData->mGenerateFcn = NULL;
}

static
  void initLiveLinkToSm(NeDaePrivateData *smData)
{
  smData->mLiveSmLink = NULL;
  smData->mLiveSmLink_destroy = NULL;
  smData->mLiveSmLink_copy = NULL;
}

void ROBOT_2da83c1f_1_NeDaePrivateData_create(NeDaePrivateData *smData)
{
  initBasicAttributes (smData);
  initStateVector (smData);
  initAsserts (smData);
  initVariables (smData);
  initRuntimeParameters (smData);
  initIoInfo (smData);
  initInputDerivs (smData);
  initDirectFeedthrough (smData);
  initOutputDerivProc (smData);
  initMechanismDelegates (smData);
  initComputationFcnPtrs (smData);
  initLiveLinkToSm (smData);
}
