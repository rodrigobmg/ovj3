/*
 * Copyright (C) 2015  Stanford University
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Apache License, as specified in the README file.
 *
 * For more information, see the README file.
 */

#include "wjunk.h"
#include "vnmr_gxyzcalib_lm.h"

extern int abortflag;

void lm_gxyz_init(double x1[],double y1[], double w[], double sig[],
    int ndata, double a[], int ia[], int ma, double **covar, double **alpha,
    double *chisq, void (*funcs)(double, double, double [], double *,
    double [], int))
{
   Werrprintf("gxyzcalib fit function not available");
   abortflag = 1;
}

void lm_gxyz_iterate(double x1[],double y1[], double w[], double sig[],
    int ndata, double a[], int ia[], int ma, double **covar, double **alpha,
    double *chisq, void (*funcs)(double, double, double [], double *,
    double [], int))
{
   Werrprintf("gxyzcalib fit function not available");
   abortflag = 1;
}

void lm_gxyz_covar(double x1[],double y1[], double w[], double sig[],
    int ndata, double a[], int ia[], int ma, double **covar, double **alpha,
    double *chisq, void (*funcs)(double, double, double [], double *,
    double [], int))
{
   Werrprintf("gxyzcalib fit function not available");
   abortflag = 1;
}

