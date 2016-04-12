/*
 *   xpcethetcatinit.c - xPC Target ethercat init
 *
 *   Copyright 2008-2013 The MathWorks, Inc.
*/


#define S_FUNCTION_LEVEL   2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME    ertethercatinit


#define VERBOSE 1

// #include <stddef.h>
// #include <stdlib.h>
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
// #include "xpcethercatutils.h"
#endif

#ifndef MATLAB_MEX_FILE
// #include <windows.h>
#include  "io_config_xml.h"
#endif

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif


// PARAMETERS

typedef enum {
   S_CONFIG_FILE = 0,
//   S_DEVICE_ID,
//   S_PCI_BUS,
//   S_PCI_SLOT,
   S_ERROR_REPORTING_LEVEL,
   S_ENABLE_DC,
//   S_LOGFILE,
   S_SAMPLETIME,
   NUM_S_PARAMS
} s_params;

                   
// #define   CONFIG_FILE            ssGetSFcnParam(S,S_CONFIG_FILE)      // String
// #define   ETH_DEVICE_ID          ssGetSFcnParam(S,S_DEVICE_ID)        // integer
// #define   ETH_PCI_BUS            ssGetSFcnParam(S,S_PCI_BUS)
// #define   ETH_PCI_SLOT           ssGetSFcnParam(S,S_PCI_SLOT)
// #define   ETH_ERR_RPT_LEVEL      ssGetSFcnParam(S,S_ERROR_REPORTING_LEVEL)
// #define   ETH_ENA_DC             ssGetSFcnParam(S,S_ENABLE_DC)
 #define   LOGFILE                ssGetSFcnParam(S, S_LOGFILE )
 #define   SAMPLETIME             ssGetSFcnParam(S, S_SAMPLETIME )

static char_T      msg[256];
static int_T       j;



/*** Simulation Code
#ifdef MATLAB_MEX_FILE

#endif
*******************/

#define MDL_RTW  /* Change to #undef to remove function */
#if defined(MDL_RTW) && defined(MATLAB_MEX_FILE)



static void mdlRTW(SimStruct *S)
{
	mxArray *prhs[3];
	mxArray *plhs[3];
	
	prhs[2] = mxCreateString(ssGetModelName(ssGetRootSS(S)));
//	prhs[2] = mxCreateString(ssGetModelName(S));
	
	//Test, add gpio&rcc
	prhs[0] = mxCreateString("Libraries\\STM32F4xx_StdPeriph_Driver\\src\\stm32f4xx_gpio.c");
	prhs[1] = mxCreateDoubleScalar(1);//for Firmware
    mexCallMATLAB(0, NULL, 3, prhs, "codertarget.stm32f4discovery.internal.addSrcFileOrIncludeDirToBuildInfo");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);

	prhs[0] = mxCreateString("Libraries\\STM32F4xx_StdPeriph_Driver\\src\\stm32f4xx_rcc.c");
	prhs[1] = mxCreateDoubleScalar(1);//for Firmware
    mexCallMATLAB(0, NULL, 3, prhs, "codertarget.stm32f4discovery.internal.addSrcFileOrIncludeDirToBuildInfo");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);
	mxDestroyArray(prhs[2]);

	//Add common include dir "osal"
	mexCallMATLAB(1, plhs, 0, NULL, "getErtEthercatPath");
	prhs[0] = plhs[0];
	prhs[1] = mxCreateString("\\..\\..\\osal\\");
	mexCallMATLAB(1, plhs, 2, prhs,"strcat");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);
	prhs[0] = plhs[0];
	prhs[1] = mxCreateDoubleScalar(0);//for Externel
	prhs[2] = mxCreateString(ssGetModelName(ssGetRootSS(S)));
	mexCallMATLAB(0, NULL, 3, prhs, "codertarget.stm32f4discovery.internal.addSrcFileOrIncludeDirToBuildInfo");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);
	mxDestroyArray(prhs[2]);	

	//Add common include dir "osal/stm32"
	mexCallMATLAB(1, plhs, 0, NULL, "getErtEthercatPath");
	prhs[0] = plhs[0];
	prhs[1] = mxCreateString("\\..\\..\\osal\\stm32f4\\");
	mexCallMATLAB(1, plhs, 2, prhs,"strcat");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);
	prhs[0] = plhs[0];
	prhs[1] = mxCreateDoubleScalar(0);//for Externel
	prhs[2] = mxCreateString(ssGetModelName(ssGetRootSS(S)));
	mexCallMATLAB(0, NULL, 3, prhs, "codertarget.stm32f4discovery.internal.addSrcFileOrIncludeDirToBuildInfo");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);
	mxDestroyArray(prhs[2]);

	//Add common include dir "oshw/stm32f4"
	mexCallMATLAB(1, plhs, 0, NULL, "getErtEthercatPath");
	prhs[0] = plhs[0];
	prhs[1] = mxCreateString("\\..\\..\\oshw\\stm32f4\\");
	mexCallMATLAB(1, plhs, 2, prhs,"strcat");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);
	prhs[0] = plhs[0];
	prhs[1] = mxCreateDoubleScalar(0);//for Externel
	prhs[2] = mxCreateString(ssGetModelName(ssGetRootSS(S)));
	mexCallMATLAB(0, NULL, 3, prhs, "codertarget.stm32f4discovery.internal.addSrcFileOrIncludeDirToBuildInfo");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);
	mxDestroyArray(prhs[2]);
	
	//Add common include dir "soem"
	mexCallMATLAB(1, plhs, 0, NULL, "getErtEthercatPath");
	prhs[0] = plhs[0];
	prhs[1] = mxCreateString("\\..\\..\\soem\\");
	mexCallMATLAB(1, plhs, 2, prhs,"strcat");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);
	prhs[0] = plhs[0];
	prhs[1] = mxCreateDoubleScalar(0);//for Externel
	prhs[2] = mxCreateString(ssGetModelName(ssGetRootSS(S)));
	mexCallMATLAB(0, NULL, 3, prhs, "codertarget.stm32f4discovery.internal.addSrcFileOrIncludeDirToBuildInfo");
	mxDestroyArray(prhs[0]);
	mxDestroyArray(prhs[1]);
	mxDestroyArray(prhs[2]);	
	
    // mexCallMATLAB(0, NULL, 3, prhs, "codertarget.stm32f4discovery.internal.addSrcFileOrIncludeDirToBuildInfo");
    // int_T      deviceIndex;
    // int_T      pciSlot;
    // int_T      pciBus;
    // int_T      cpuIndex=0;
    
    // char_T     cbuf[132];
    // int_T      errRptLvl;
    // int_T      enaDC;
    // char       *logfilename;
    
    // pciBus=(int_T)mxGetPr(ETH_PCI_BUS)[0];
    // pciSlot = (int_T)mxGetPr(ETH_PCI_SLOT)[0];
    // deviceIndex = (int_T)mxGetPr(ETH_DEVICE_ID)[0];
    // deviceIndex = deviceIndex;
    // errRptLvl = (int_T)mxGetPr(ETH_ERR_RPT_LEVEL)[0];
    // enaDC = (int_T)mxGetPr(ETH_ENA_DC)[0];
    // logfilename = mxArrayToString( LOGFILE );
    
    // sprintf(cbuf, "%d", deviceIndex);
    // ssWriteRTWStrParam(S,"deviceIndex", cbuf);

    // sprintf(cbuf,"%d",pciBus);          
    // ssWriteRTWStrParam(S,"pciBus", cbuf);
   
    // sprintf(cbuf, "%d", pciSlot);
    // ssWriteRTWStrParam(S,"pciSlot", cbuf);
    
    // sprintf(cbuf, "%d",errRptLvl); 
    // ssWriteRTWStrParam(S,"errorReportingLevel", cbuf);
    
    // sprintf(cbuf, "io_config_xml_%d.h",deviceIndex);
    // ssWriteRTWStrParam(S,"xml_include_file", cbuf);
   
    // sprintf(cbuf, "%d", enaDC);
    // ssWriteRTWStrParam(S,"enaDC", cbuf);
    
    // ssWriteRTWStrParam(S, "logFileName", logfilename );
    // mxFree( logfilename );
}  
#endif




static void mdlInitializeSizes(SimStruct *S)
{
   int_T                num_params;
      
   ssSetNumSFcnParams(S, NUM_S_PARAMS);
   if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
      sprintf(msg, "%d input args expected, %d passed", NUM_S_PARAMS, ssGetSFcnParamsCount(S));
      ssSetErrorStatus(S, msg);
      return;
   }

   ssSetNumContStates(S, 0);
   ssSetNumDiscStates(S, 0);

   if ( ! ssSetNumInputPorts(S, 0) ) return;

   if ( ! ssSetNumOutputPorts(S,1) ) return;
   ssSetOutputPortDataType(S, 0, SS_INT32);
   ssSetOutputPortWidth(S, 0, 6);


   // The PDO parameter S_NUM_SIGNALS specifies the number of outputs.
   
   num_params = (int32_T)ssGetSFcnParamsCount(S);
   
   ssSetNumSampleTimes(S, 0);
   ssSetNumIWork(S, 0);
   ssSetNumRWork(S, 0);
   ssSetNumPWork(S, 0);
   ssSetNumModes(S, 0);
   ssSetNumNonsampledZCs(S, 0);

   ssSetSimStateCompliance(S, HAS_NO_SIM_STATE );

   for ( j = 0 ; j < NUM_S_PARAMS ; j++ )
      ssSetSFcnParamTunable(S, j, SS_PRM_NOT_TUNABLE);

   ssSetOptions(S, SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE |
                   SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    real_T sampletime = mxGetPr(SAMPLETIME)[0];
    
    if (sampletime == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, sampletime);
    	ssSetOffsetTime(S, 0, 0.0);
    }
}

#define MDL_START
static void mdlStart(SimStruct *S)
{
	osalSetSimStruct(S);
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
}

static void mdlTerminate(SimStruct *S)
{

}





#ifdef MATLAB_MEX_FILE
#include "simulink.c"
#else
#include "cg_sfun.h"
#endif

