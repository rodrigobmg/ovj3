/*
 * Copyright (C) 2015  University of Oregon
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Apache License, as specified in the README file.
 *
 * For more information, see the README file.
 */
/* 
 */
#include	"bp.h"
#ifndef	M_PI
#define M_PI	3.14159265358979323846
#endif
#define		PRINT_POS	0
#define		PRINT_CENTER	0

/* fractional number and table based version */
/* table based increment */

bp_2d_ti (bound, bpc, p_prof_float, matrix)
struct		boundary	bound[];
BP_CTRL		*bpc;
float		*p_prof_float;
int		*matrix;
{
float		*p_prof_act;
short		*p_exp_prof, exp_prof[MAX_SIZE * RES];
short		*p_inc_tab, *p_inc_tab_end, inc_tab[MAX_SIZE];
int		*p_imag_act, *p_imag_end;
register int 	line, angle_ph;
double		pos_meas_line, pos_meas_inc, pos_meas_inc_res, pos_meas_inc_act;
int		pos_meas_act_tab;
short		*pos_meas_act_tab_high;
double		phi_act;
double		phi_sin, phi_cos, phi_inc;


phi_act      = bpc->angle_start * M_PI / 180.0; 
phi_inc      = (bpc->angle_end - bpc->angle_start) * M_PI / 
               (180.0 * bpc->n_proj);

/* adressing for fractional numbers - hardware dependent part */
#if	ASPECT_X32
pos_meas_act_tab_high  = (short *)&pos_meas_act_tab + 1;
#endif
#if	SUN
pos_meas_act_tab_high  = (short *)&pos_meas_act_tab;
#endif

for (angle_ph = 0; angle_ph < bpc->n_proj; angle_ph++) {

    phi_sin            = sin (phi_act + angle_ph * phi_inc);
    phi_cos            = cos (phi_act + angle_ph * phi_inc);
    pos_meas_inc       = bpc->resize * phi_cos;
    p_inc_tab          = inc_tab;
    p_inc_tab_end      = inc_tab + bpc->i_size;
    pos_meas_inc_res   = pos_meas_inc * (double)RES;
    for (pos_meas_inc_act=0; p_inc_tab<p_inc_tab_end; p_inc_tab++) {
        *p_inc_tab = (short)(pos_meas_inc_act + 0.5);
        pos_meas_inc_act += pos_meas_inc_res;
        }
    /*
     * expanding the profile RES * p_size elements in array exp_prof
     */
    p_prof_act = p_prof_float + angle_ph * bpc->p_size;
    prof_exp_float_ti (p_prof_act, bpc, exp_prof);

    for (line = 1; line < bpc->i_size-1; line++) {
       /*
        * get position of the center of the current line projected on the
        * profile
        */
       pos_meas_line  = bpc->resize * ((bpc->i_center_y-(double)line) * phi_sin) + 
                        bpc->offset_x * phi_cos + bpc->offset_y * phi_sin +
                        (double)(bpc->p_size - 1) / 2.0; 
       /*
        * take into account, that the effect of the rounding error for
        * pos_meas_act_frac is reduced to the half, if pos_meas_inc_frac
        * is already used for setting up the starting position.
        */
       pos_meas_act_tab = (int) (0.5 + RES * 65536.0 * pos_meas_line +
                                   pos_meas_inc_res * 65536.0 *
                                  ((double)bound[line].l + 1.0 - bpc->i_center_x) );

       /*
        * looping speed up by using pointer p_imag_act as loop variable
        */
       p_imag_act = matrix + line * bpc->i_size + bound[line].l + 1;
       p_imag_end = p_imag_act + bound[line].r - bound[line].l - 1;

       p_exp_prof = exp_prof + *pos_meas_act_tab_high;
       p_inc_tab  = inc_tab;

#if PRINT_POS
       printf ("l=%3d pos_meas_act = %lf  ...  ",line,
                (double)pos_meas_act_tab / (65536.0 * RES) );
#endif
#if PRINT_CENTER
       if (line == bpc->i_size/2) {
           printf ("l=%3d pos_meas_act = %lf  ...  ",line,
                (double)pos_meas_act_tab / (65536.0 * RES) );
           }
#endif

       for (;p_imag_act<p_imag_end; p_imag_act++) {
           /*
            * no rounding in exp_prof useful, since pos. and neg. values should
            * have the same occurance, thus avoiding error accumulation
            */
           *p_imag_act       += (int) *(p_exp_prof + (*p_inc_tab++));
           }   /* end of loop column */
#if PRINT_POS
       printf ("pos_meas_act = %lf\n", (double)(pos_meas_act_tab + 
                    ((double)*p_inc_tab * 65536.0)) /
                    (65536.0 * RES) - pos_meas_inc);
#endif
#if PRINT_CENTER
       if (line == bpc->i_size/2) {
           printf ("pos_meas_act = %lf\n", (double)(pos_meas_act_tab + 
                    ((double)*p_inc_tab * 65536.0)) /
                    (65536.0 * RES) - pos_meas_inc);
           }
#endif
       }   /* end of loop line */
   }   /* end of loop phi */
return(1);
}


prof_exp_float_ti (p_prof_float, bpc, exp_prof)
float		*p_prof_float;
BP_CTRL		*bpc;
short		*exp_prof;
{
short		*p_exp_prof, *p_exp_prof_next;
int		*p_prof_int, *p_prof_end;
int		act_prof, dif_prof;
float		scale;
p_prof_int = (int *)p_prof_float;
p_prof_end = p_prof_int + bpc->p_size - 1;
p_exp_prof = exp_prof;
scale = bpc->scale;
*p_prof_int = (int) *p_prof_float * scale;
for (; p_prof_int<p_prof_end; p_prof_int++) {
    act_prof         = (*p_prof_int) << RES_POW;
    *(p_prof_int+1)  = (int) (*(float *)(p_prof_int+1) * scale);
    dif_prof         = (int) *(p_prof_int+1) - *p_prof_int;
    if (dif_prof >= 0) { act_prof += RES/2; }
    else               { act_prof += (RES/2 - 1); } 
    p_exp_prof_next = p_exp_prof + RES;
    for (; p_exp_prof<p_exp_prof_next; p_exp_prof++) {
        *p_exp_prof = (short)(act_prof >> RES_POW);
        act_prof += dif_prof;
        }
    }
}
