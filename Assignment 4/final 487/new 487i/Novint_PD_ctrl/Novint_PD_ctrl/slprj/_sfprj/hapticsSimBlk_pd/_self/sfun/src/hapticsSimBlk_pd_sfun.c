/* Include files */

#include "hapticsSimBlk_pd_sfun.h"
#include "c2_hapticsSimBlk_pd.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _hapticsSimBlk_pdMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void hapticsSimBlk_pd_initializer(void)
{
}

void hapticsSimBlk_pd_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_hapticsSimBlk_pd_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==2) {
    c2_hapticsSimBlk_pd_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_hapticsSimBlk_pd_process_check_sum_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1381643739U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3691047368U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3975566506U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(582538047U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1111706181U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(143518171U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1807347616U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(387581059U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 2:
        {
          extern void sf_c2_hapticsSimBlk_pd_get_check_sum(mxArray *plhs[]);
          sf_c2_hapticsSimBlk_pd_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2964486417U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1384482678U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4172579957U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(983071074U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3100052202U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(39055510U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2625485534U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4011950317U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_hapticsSimBlk_pd_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(aiChksum, "6EabRskunBDRTVlTqRKkZD") == 0) {
          extern mxArray *sf_c2_hapticsSimBlk_pd_get_autoinheritance_info(void);
          plhs[0] = sf_c2_hapticsSimBlk_pd_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_hapticsSimBlk_pd_get_eml_resolved_functions_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        extern const mxArray
          *sf_c2_hapticsSimBlk_pd_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_hapticsSimBlk_pd_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

void hapticsSimBlk_pd_debug_initialize(void)
{
  _hapticsSimBlk_pdMachineNumber_ = sf_debug_initialize_machine(
    "hapticsSimBlk_pd","sfun",0,1,0,0,0);
  sf_debug_set_machine_event_thresholds(_hapticsSimBlk_pdMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_hapticsSimBlk_pdMachineNumber_,0);
}

void hapticsSimBlk_pd_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_hapticsSimBlk_pd_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info(
      "hapticsSimBlk_pd", "hapticsSimBlk_pd");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_hapticsSimBlk_pd_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
