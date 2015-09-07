/*
 * Copyright (C) 2015  Stanford University
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Apache License, as specified in the README file.
 *
 * For more information, see the README file.
 */
/* dspfuncs.h - DSP functions */
/*
*/
/*
 * Varian, Inc. All Rights Reserved.
 * This software contains proprietary and confidential
 * information of Varian, Inc. and its contributors.
 * Use, disclosure and reproduction is prohibited without
 * prior consent.
 */

#ifndef INCdspfuncsh
#define INCdspfuncsh

#include "shrexpinfo.h"

#define DSP_DECFACTOR	0
#define DSP_NTAPS	1
#define DSP_NAME	2

#define OS_MAX_COEFF	50000
#define OS_MIN_COEFF	3

struct _dspInfo
{
   float	*filter;
   float	*chargeup;
   float	*buffer;
   float	*data;
   float	filtsum;
   float	oslsfrq;
   float	osfiltfactor;
   float	lvl;
   float	tlt;
   int		oscoeff;
   int		osfactor;
   int		offset;
   char		name[128];
   int		tshift;
};

typedef struct _dspInfo dspInfo;

/* ------------- Make C header file C++ compliant ------------------- */
#ifdef __cplusplus
extern "C" {
#endif

extern int  initDSP(SHR_EXP_INFO ExpInfo);
extern int  dspExec(char *dataPtr, char *outPtr, unsigned long np,
                    unsigned long fidsize, unsigned long ct);
 
#ifdef __cplusplus
}
#endif

#endif

