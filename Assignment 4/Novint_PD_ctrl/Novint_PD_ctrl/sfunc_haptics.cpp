/*
 *   sfunc_haptics.cpp Simple C-MEX S-function for function call.
 *
 *   ABSTRACT:
 *     The purpose of this sfunction is to call a simple legacy 
 *     function during simulation:
 *
 *        void falconPlant(double u1[3], double y1[3])
 *
 * Simulink version           : 6.5 (R2006b) 03-Aug-2006
 *   C++ source code generated on : 13-Jan-2010 17:16:33
 */

/*
   %%%-MATLAB_Construction_Commands_Start
   def = legacy_code_initialize;
   def.SFunctionName = 'sfunc_haptics';
   def.OutputFcnSpec = 'void falconPlant(double u1[3], double y1[3])';
   def.StartFcnSpec = 'createHaptics()';
   def.TerminateFcnSpec = 'deleteHaptics()';
   def.HeaderFiles = {'haptics.h'};
   def.SourceFiles = {'haptics.cpp'};
   def.HostLibFiles = {'hdl.lib'};
   def.TargetLibFiles = {'hdl.lib'};
   def.IncPaths = {'C:\Program Files\novint\HDAL_SDK_1.1.0_Beta\include'};
   def.LibPaths = {'C:\Program Files\novint\HDAL_SDK_1.1.0_Beta\lib'};
   def.Options.useTlcWithAccel = false;
   def.Options.language = 'C++';
   legacy_code_sfcn_cmex_generate(def);
   legacy_code_compile(def);
   %%%-MATLAB_Construction_Commands_End
 */

/*
 * Must specify the S_FUNCTION_NAME as the name of the S-function.
 */
#define S_FUNCTION_NAME                 sfunc_haptics
#define S_FUNCTION_LEVEL                2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"

/*
 * Specific header file(s) required by the legacy code function.
 */
#include "haptics.h"

/* Function: mdlInitializeSizes ===========================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
  /* Number of expected parameters */
  ssSetNumSFcnParams(S, 0);

  /*
   * Set the number of input ports. 
   */
  if (!ssSetNumInputPorts(S, 1)) return;

  /*
   * Configure the input port 1
   */
  ssSetInputPortDataType(S, 0, SS_DOUBLE);
  ssSetInputPortWidth(S, 0, 3);
  ssSetInputPortComplexSignal(S, 0, COMPLEX_NO);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortAcceptExprInRTW(S, 0, 0);
  ssSetInputPortOverWritable(S, 0, 0);
  ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
  ssSetInputPortRequiredContiguous(S, 0, 1);

  /*
   * Set the number of output ports.
   */
  if (!ssSetNumOutputPorts(S, 1)) return;

  /*
   * Configure the output port 1
   */
  ssSetOutputPortDataType(S, 0, SS_DOUBLE);
  ssSetOutputPortWidth(S, 0, 3);
  ssSetOutputPortComplexSignal(S, 0, COMPLEX_NO);
  ssSetOutputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
  ssSetOutputPortOutputExprInRTW(S, 0, 0);

  /*
   * Set the number of sample time. 
   */
  ssSetNumSampleTimes(S, 1);
#if defined(ssSetModelReferenceSampleTimeDefaultInheritance)
  ssSetModelReferenceSampleTimeDefaultInheritance(S);
#endif

  /*
   * All options have the form SS_OPTION_<name> and are documented in
   * matlabroot/simulink/include/simstruc.h. The options should be
   * bitwise or'd together as in
   *   ssSetOptions(S, (SS_OPTION_name1 | SS_OPTION_name2))
   */
  ssSetOptions(S,
   SS_OPTION_CAN_BE_CALLED_CONDITIONALLY |
   SS_OPTION_EXCEPTION_FREE_CODE |
   SS_OPTION_WORKS_WITH_CODE_REUSE |
   SS_OPTION_SFUNCTION_INLINED_FOR_RTW |
   SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME);
}

/* Function: mdlInitializeSampleTimes =====================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
  ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

#define MDL_START
#if defined(MDL_START)
/* Function: mdlStart =====================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */
static void mdlStart(SimStruct *S)
{

  /*
   * Call the legacy code function
   */
  createHaptics();
}
#endif

/* Function: mdlOutputs ===================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block. Generally outputs are placed in the output vector(s),
 *    ssGetOutputPortSignal.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  /*
   * Get access to Parameter/Input/Output information
   */
  real_T *u1 = (real_T *) ssGetInputPortSignal(S, 0);
  real_T *y1 = (real_T *) ssGetOutputPortSignal(S, 0);

  /*
   * Call the legacy code function
   */
  falconPlant( u1, y1);
}

/* Function: mdlTerminate =================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.
 */
static void mdlTerminate(SimStruct *S)
{

  /*
   * Call the legacy code function
   */
  deleteHaptics();
}

/*
 * Required S-function trailer
 */
#ifdef MATLAB_MEX_FILE
# include "simulink.c"
#else
# include "cg_sfun.h"
#endif
