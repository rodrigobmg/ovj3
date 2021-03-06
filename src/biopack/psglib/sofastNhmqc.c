/*
 * Copyright (C) 2015  University of Oregon
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Apache License, as specified in the README file.
 *
 * For more information, see the README file.
 */


/*  SOFAST N15 HMQC with options

   standard version (ipap_flg='n' dm2='nny')   

   IPAP version (ipap_flg='y', dm2='nnn'),                

   SE-IPAP version ( SE='y',dm2='nnn')

   ab_flg='a','b'  and  dm2='nnn'              
        (no 15N decoupling)                  
   interest : cryogenic probes, JNH couplings  

If ipap_flg='n' the experiment is States-Haberkorn and uses default
coefficients for wft2da (non-sensitivity enhanced processing).

With ipap_flg='y' and ab_flg='a','b' phase=1,2 array='ab_flg,phase'
you can acquire both antiphase and in-phase spectra at the same time. 

        wft2d(1,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0)     for anti-phase signals
        wft2d(0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,-1)     for in-phase signals
        wft2d(1,0,0,0,0,1,0,0,0,0,-1,0,0,0,0,-1)    for sum (one component)
        wft2d(1,0,0,0,0,-1,0,0,0,0,-1,0,0,0,0,1)    for diff (other component)

The BioPack setup macro (sofastNhmqc) will use Pbox to create
the necessary shaped pulses and decoupling patterns. It will also
use the created shapefiles to obtain parameter values for the pulse
widths and power levels (and dmf value for decoupling).

submitted by Bernhard Brutscher, August 2005,


HET-SOFAST options added to basic sofastNhmqc.c: (B.Brutscher, December 2006)

Shaped 1H pulses are calculated within the sequence if autocal='y' using
these variable (otherwise, the shapes/powers/widths are those generated by the
setup macro):

Typical settings:
  shbw=4: excitation band width
  shofs=8.2 center of excitation (set >9 to minimize H2O excitation)
   NOTE: values are in ppm of referenced chemical shift (tof at H2O)
  flipangle (120) to be used with d1 ~ 100 to 300 ms
            (140) for fast pulsing d1 ~ 1 ms

flags:
set hetsofast_flg='n' for standard N15 HMQC SOFAST experiment

set hetsofast_flg-'a' for selective inversion of aliphatic protons 
to measure "proton spin density

set hetsofast_flg='n' for H2O inversion to measure water accessibility

set c13refoc ='y'  for refocussing C13 180 in t1 (for 13C labelled proteins)
set ipap_flg = 'y' for IPAP (no 15N decoupling during acquisition)

Three experiments have to be recorded:
(a) reference experiment, hetsofast_flg='n'
(b) aliphatic-perturbed spectrum, hetsofast_flg='a'
(c) water-perturbed spectrum, hetsofast_flg='b'

The ratio of peak intensities in (b) over (a) gives insight into proton density 


Optimization of cancellation of water signal:
 A fine power (tpwrsf) is available for optimization of water suppression. If 
 tpwrsf<4095.0 it is active. To optimize tpwrsf,
 set nt=1 ssfilter='n' d1=3 ss=0 gain=2 array('tpwrsf',20,1800,20) go wft dssh dssl

please note :
  1) the automatic 15N decoupling works but it is done within the sequence(autocal='y' and dmm2='ccp')
     so the vnmr parameters don't show the changes (only "dps" shows the change in power, but not dmf2)
  2) For large 15N spectral width, one can lose one point in the indirect dimension 
     when the 1H and 15N pulses cross each other

References:

Schanda, P. and Brutscher, B. (2005) J. Am. Chem. Soc., 127, 8014-8015.
Schanda, P., Kupce, E. and Brutscher, B. (2005) J. Biomol. NMR, 33, 199-211.
Schanda, P., Forge, V. and Brutscher, B. (2006) Magn. Reson. in Chem., 44, S177-S184.


SE option added to basic sofastNhmqc.c: (B.Brutscher, April 2008)
 (Thomas Kern, Paul Schanda and Bernhard Brutscher, JMR, 190, 333-338 (2008))

Modified for BioPack, GG, Varian, April 2008
*/

#include <standard.h>
#include "bionmr.h"
#include <Pbox_psg.h>


static shape sh90, shref,shdec;

static int 

   phi1[2] = {0,2},
   phi2[2] = {0,2};


pulsesequence()
{
   char   
          autocal[MAXSTR],
          shname1[MAXSTR],
	  shname2[MAXSTR],
          ipap_flg[MAXSTR],
          ab_flg[MAXSTR],
	  f1180[MAXSTR],
          SE[MAXSTR],        /*Use Sensitivity Enhancement */
          c13refoc[MAXSTR],
          refpat[MAXSTR],    /* pulse shape pattern refocus. pulse*/
          hetsofast_flg[MAXSTR],
          grad3_flg[MAXSTR];     /*gradient flag */

   int   
          t1_counter,
          phase;


   double d2_init=0.0,
          pwS,pwS1,pwS2, 
          tpwrsf = getval("tpwrsf"),
   	  adjust = getval("adjust"),
          gzlvl1 = getval("gzlvl1"),
          gzlvl2 = getval("gzlvl2"), 
          gzlvl3 = getval("gzlvl3"), 
          gstab = getval("gstab"),
          gt1 = getval("gt1"),
          gt2 = getval("gt2"),
          gt3 = getval("gt3"),
          shlvl1 = getval("shlvl1"),
          shlvl2 = getval("shlvl2"),
          shdmf2 = getval("shdmf2"),
          shbw = getval("shbw"),
          shpw1 = getval("shpw1"),
          shpw2 = getval("shpw2"),
          shpw3 = 0.0,

          shofs = getval("shofs"),
          flipangle = getval("flipangle"),
          pwNlvl = getval("pwNlvl"),
          pwN = getval("pwN"),
          dpwr2 = getval("dpwr2"),
          d2 = getval("d2"),
          tau1,
          taunh = 1.0/(2.0*getval("JNH"));

void compo_pulse();
void compo1_pulse();
void makeshape_pc9();
void makeshape_refoc();
void makeshape_ndec();

   getstr("autocal",autocal);
   getstr("f1180",f1180);
   getstr("c13refoc",c13refoc);
   getstr("hetsofast_flg",hetsofast_flg);
   getstr("refpat", refpat); /* pulse pattern refocussing pulse */
   getstr("ipap_flg",ipap_flg);
   getstr("grad3_flg",grad3_flg);
   getstr("ab_flg",ab_flg);
   getstr("SE",SE);
   getstr("shname1",shname1);
   getstr("shname2",shname2);

 pwS = c_shapedpw("sech",200.0,0.0,zero, 0.0, 0.0);
 pwS1 = hn_simshapedpw(refpat,shbw,shofs-4.8,"isnob3",50.0,0.0, zero, zero, 0.0, 0.0);
 pwS2 = h_shapedpw(refpat,shbw,3.5,zero, 0.0, 0.0);



 if (hetsofast_flg[0] == 'a')
   shpw3 = h_shapedpw("isnob5",4.0,-3.0,two, 2.0e-6, 2.0e-6);
 if (hetsofast_flg[0] == 'b')
   shpw3 = h_shapedpw("gaus180",0.015,0.0,two, 2.0e-6, 2.0e-6);

  phase = (int) (getval("phase") + 0.5);
   
   settable(t1,2,phi1);
   settable(t2,2,phi2);

if (autocal[0] == 'y')
{
(void) makeshape_pc9(flipangle, shbw, shofs);  /*create pc9 pulse*/
   sh90 = getRsh("hn_pc9");
   shpw1 = sh90.pw;
   shlvl1 = sh90.pwr;
     sprintf(shname1,"hn_pc9");


(void) makeshape_refoc(refpat, shbw, shofs);  /* create refocussing pulse */
   shref = getDsh("hn_refoc");
   shpw2 = shref.pw;
   shlvl2 = shref.pwr;
   shdmf2 = shref.dmf;
   sprintf(shname2,"hn_refoc");

  if (dmm2[2] == 'p')  /* waveform capability present on channel 3 */
 {
  (void) makeshape_ndec();  /* create n15 wurst decoupling */
   shdec = getDsh("hncompdec");
   dpwr2 = shdec.pwr;
   dmf2 = shdec.dmf;
   dres2 = shdec.dres;
   sprintf(dseq2,"hncompdec");
 }

}

   if  (tpwrsf <4095.0) shlvl2 = shlvl2+6.0;

  if (phase == 1) ;
  if (phase == 2) tsadd(t1,1,4);

    tau1 = d2;
    if((f1180[A] == 'y') && (ni > 1.0))
        { tau1 += ( 1.0 / (2.0*sw1) ); if(tau1 < 0.2e-6) tau1 = 0.0; }
    tau1 = tau1;
  
    if (f1180[0] == 'y')  tau1 = tau1-pwN*4.0/3.0;

    


   if( ix == 1) d2_init = d2;
   t1_counter = (int) ( (d2-d2_init)*sw1 + 0.5 );
   if(t1_counter % 2)
        { tsadd(t1,2,4); tsadd(t2,2,4); }



   status(A);

   decoffset(dof);
   dec2power(pwNlvl);
   dec2offset(dof2);
   obsoffset(tof);
   obspower(tpwr);


/**********************************************/
 if (hetsofast_flg[0] != 'n')
 {
     if (hetsofast_flg[0] == 'a')
     h_shapedpulse("isnob5",4.0,-3.0,two, 2.0e-6, 2.0e-6);
     if (hetsofast_flg[0] == 'b')
     h_shapedpulse("gaus180",0.015,0.0,two, 2.0e-6, 2.0e-6);
     zgradpulse(gzlvl2, gt2);
     delay(gstab);
     delay(d1-gt2-shpw3);
     lk_hold();
 }
 else
 {
     zgradpulse(gzlvl2, gt2);
     delay(gstab);
     delay(d1-gt2);
     lk_hold();
 }
   obspower(shlvl1);
   shaped_pulse(shname1,shpw1,zero,2.0e-4,2.0e-6);

if (SE[0] == 'y')
 {

  if (ipap_flg[0] == 'y')
  {
    if ((tau1+pwN*2.0) < pwS2) delay((pwS2*0.5-tau1*0.5-pwN)*0.5);
    if (grad3_flg[0]== 'y')
     delay(taunh*0.5-shpw1*0.533-pwS1*0.5+(gt3*2.0+2.0*gstab+pwN*3.0));
    else
     delay(taunh*0.5-shpw1*0.533-pwS1*0.5+pwN);

    hn_simshapedpulse(refpat,shbw,shofs-4.8,"bip720_50_20",40.0,0.0, zero, zero, 0.0, 0.0);
    obspower(shlvl2);
    obspwrf(4095.0);
    compo1_pulse(shname2,shpw2,pwN,shdmf2,t1,tau1,c13refoc,pwS,taunh,pwS1,pwS2,gt1,gt3,gzlvl3,grad3_flg,gstab);
    obspower(shlvl2);
    obspwrf(4095.0);
    zgradpulse(gzlvl1, gt1);
    delay(gstab);
    h_sim3shapedpulse(refpat,shbw,shofs-4.8,0.0,2.0*pwN, one, zero, zero, 0.0, 0.0);
    zgradpulse(gzlvl1, gt1);
    delay(gstab);
    delay(taunh*0.5-gt1-gstab-POWER_DELAY-pwS1*0.5);
    if ((tau1+pwN*2.0) < pwS2) delay((pwS2*0.5-tau1*0.5-pwN)*0.5);
    if (ab_flg[0] == 'a')
      dec2rgpulse(pwN,one,0.0,0.0);
    else
      dec2rgpulse(pwN,three,0.0,0.0);
    if (grad3_flg[0]== 'y')
     {
      delay(gt3+gstab);
      dec2rgpulse(pwN*2.0,zero,0.0,0.0);
      zgradpulse(gzlvl3,gt3);
      delay(gstab);
     }
  }
  else
  {
    zgradpulse(gzlvl1, gt1);
    delay(gstab);
    if ((tau1+pwN*2.0) < pwS2) 
     delay(taunh-gt1-gstab-shpw1*0.533-adjust-(pwS2*0.5-tau1*0.5-pwN)*0.5);
    else
     delay(taunh-gt1-gstab-shpw1*0.533-adjust);
    obspower(shlvl2);
    obspwrf(tpwrsf);
    compo_pulse(shname2,shpw2,pwN,shdmf2,t1,tau1,c13refoc,pwS);
    obspower(shlvl1);
    obspwrf(4095.0);
    zgradpulse(gzlvl1, gt1);
    delay(gstab);
    if ((tau1+pwN*2.0) < pwS2) 
     delay(taunh-gt1-gstab-POWER_DELAY-(pwS2*0.5-tau1*0.5-pwN)*0.5);
    else
     delay(taunh-gt1-gstab-POWER_DELAY);
  }
 }
else
 {
  if ((ni == 0) || (ni == 1))
   {
    zgradpulse(gzlvl1, gt1);
    delay(gstab);
    delay(taunh-gt1-gstab-WFG_START_DELAY+pwN*4.0-shpw1*0.533-adjust);
    obspwrf(tpwrsf);
    obspower(shlvl2);

    xmtrphase(zero);
    xmtron();
    obsunblank();
    obsprgon(shname2,1/shdmf2,9.0);
    delay(shpw2);
    obsprgoff();
    obsblank();
    xmtroff();

    obspower(shlvl2);
    obspwrf(4095.0);
    dec2rgpulse(pwN,t1,0.0,0.0);
    dec2rgpulse(pwN*2.0,zero,0.0,0.0);
    dec2rgpulse(pwN,zero,0.0,0.0);
   }
  else
   {
    zgradpulse(gzlvl1, gt1);
    delay(gstab);
    delay(taunh-gt1-gstab-shpw1*0.533-adjust);
    obspower(shlvl2);
    obspwrf(tpwrsf);
    compo_pulse(shname2,shpw2,pwN,shdmf2,t1,tau1,c13refoc,pwS);
    obspower(shlvl1);
    obspwrf(4095.0);
   }

  if (ipap_flg[0] == 'y')
   {
   if (ab_flg[0] == 'b')
     {
     zgradpulse(gzlvl1, gt1);
     delay(gstab);
     delay(taunh-gt1-gstab-pwN-POWER_DELAY);
     dec2rgpulse(pwN,one,0.0,0.0);
     }
   else
     {
     zgradpulse(gzlvl1, gt1);
     delay(gstab);
     delay(taunh*0.5-gt1-pwN-gstab);
     dec2rgpulse(pwN*2.0,zero,0.0,0.0);
     delay(taunh*0.5-pwN-POWER_DELAY);
     }
   }
  else
   {
   zgradpulse(gzlvl1, gt1);
   delay(gstab);
   delay(taunh-gt1-gstab-POWER_DELAY);
   }
 }
 dec2power(dpwr2);
 lk_sample(); 
 setreceiver(t2);
 status(C);


}


/*************************************************************/
/* pulse sandwich including incremented time period          */
/* flanked by 15N pulses and 1H and 13C shaped refocusing    */
/* pulses                                                    */
/*************************************************************/
void compo_pulse(h1shape,h1pw,n15pw,h1dmf,n15phase,inc_delay,c_flg,Cpw)
  char h1shape[MAXSTR],c_flg[MAXSTR];
  double h1pw,n15pw,inc_delay,h1dmf,Cpw;
  codeint n15phase;

{
  if ((inc_delay+n15pw*2.0) > h1pw)
  {
     dec2rgpulse(n15pw,n15phase,0.0,0.0);
     delay((inc_delay-h1pw)*0.5);

    xmtrphase(zero);
    xmtron();
    obsunblank();
    obsprgon(h1shape,1/h1dmf,9.0);

    if (c_flg[0] =='y')
    {
    delay((h1pw-Cpw)*0.5);
    c_shapedpulse("sech",200.0,0.0,zero,0.0,0.0);
    delay((h1pw-Cpw)*0.5);
    }
    else delay(h1pw);

    obsprgoff();
    obsblank();
    xmtroff();

     delay((inc_delay-h1pw)*0.5);
     dec2rgpulse(n15pw,zero,0.0,0.0);
  }
  else
  {
    xmtrphase(zero);
    xmtron();
    obsunblank();
    obsprgon(h1shape,1/h1dmf,9.0);
    delay((h1pw-inc_delay-n15pw*2.0)*0.5);
     dec2rgpulse(n15pw,n15phase,0.0,0.0);

    if ((c_flg[0] =='y') && (inc_delay >= Cpw))
    {
    delay((inc_delay-Cpw)*0.5);
    c_shapedpulse("sech",200.0,0.0,zero,0.0,0.0);
    delay((inc_delay-Cpw)*0.5);
    }
    else delay(inc_delay);

     dec2rgpulse(n15pw,zero,0.0,0.0);
    delay((h1pw-inc_delay-n15pw*2.0)*0.5);
    obsprgoff();
    obsblank();
    xmtroff();
  }

}

/*************************************************************/
/* pulse sandwich including incremented time period          */
/* flanked by 15N pulses and 1H and 13C shaped refocusing    */
/* pulses (for IPAP version)                                 */
/*************************************************************/
void compo1_pulse(h1shape,h1pw,n15pw,h1dmf,n15phase,inc_delay,c_flg,Cpw,dnh,sh1,sh2,grad1,gt3,gzlvl3,grad3_flg,gstab)
  char h1shape[MAXSTR],c_flg[MAXSTR],grad3_flg[MAXSTR];
  double gstab,h1pw,n15pw,inc_delay,h1dmf,Cpw,dnh,sh1,sh2,grad1,gt3,gzlvl3;
  codeint n15phase;

{
  if ((inc_delay+n15pw*2.0) > h1pw)
  {
     delay(dnh*0.5-sh1*0.5-gt3-gstab);
          if (grad3_flg[0]== 'y')
          {
           zgradpulse(-gzlvl3, gt3);
           delay(gstab);
           }
           else delay(gt3+gstab);
     dec2rgpulse(n15pw,n15phase,0.0,0.0);
     delay((inc_delay-h1pw)*0.5);

    xmtrphase(zero);
    xmtron();
    obsunblank();
    obsprgon(h1shape,1/h1dmf,9.0);

    if (c_flg[0] =='y')
    {
    delay((h1pw-Cpw)*0.5);
    c_shapedpulse("sech",200.0,0.0,zero,0.0,0.0);
    delay((h1pw-Cpw)*0.5);
    }
    else delay(h1pw);

    obsprgoff();
    obsblank();
    xmtroff();

     delay((inc_delay-h1pw)*0.5);
     dec2rgpulse(n15pw,zero,0.0,0.0);
     delay(dnh*0.5-grad1-gstab-sh1*0.5);
  }
  else
  {
    delay(dnh*0.5-sh1*0.5-((sh2-inc_delay-n15pw*2.0)*0.25)-gt3-gstab);
          if (grad3_flg[0]== 'y')
          {
           zgradpulse(-gzlvl3, gt3);
           delay(gstab);
           }
           else delay(gt3+gstab);
    xmtrphase(zero);
    xmtron();
    obsunblank();
    obsprgon(h1shape,1/h1dmf,9.0);
    delay((h1pw-inc_delay-n15pw*2.0)*0.5);
     dec2rgpulse(n15pw,n15phase,0.0,0.0);

    if ((c_flg[0] =='y') && (inc_delay >= Cpw))
    {
    delay((inc_delay-Cpw)*0.5);
    c_shapedpulse("sech",200.0,0.0,zero,0.0,0.0);
    delay((inc_delay-Cpw)*0.5);
    }
    else delay(inc_delay);

     dec2rgpulse(n15pw,zero,0.0,0.0);
    delay((h1pw-inc_delay-n15pw*2.0)*0.5);
    obsprgoff();
    obsblank();
    xmtroff();
    delay(dnh*0.5-sh1*0.5-((sh2-inc_delay-n15pw*2.0)*0.25)-grad1-gstab);
  }

}
/*****************************************************/
/* Function that creates pc9 shape using Pbox        */
/*****************************************************/
void makeshape_pc9(flip,pulsebw, pulseofs )
  double flip,pulsebw, pulseofs;

{
  FILE  *inpf1;

  char cmd[MAXSTR];
  double compH = getval("compH"),
         pw = getval("pw"),
         tpwr = getval("tpwr"),
         sfrq = getval("sfrq");

      sprintf(cmd, "%s/shapelib/Pbox.inp", userdir);

      if((inpf1 = fopen(cmd, "wb")) == NULL)
    {
      printf("Cannot open \"%s\"\n", cmd);
      exit(1);
    }
      fprintf(inpf1, "{ pc9f %3.3fp %3.3fp 0.0 0.0 %3.3f }\n",pulsebw,pulseofs,flip);

      fprintf(inpf1, "refofs = 4.77p\n");
      fprintf(inpf1, "sfrq = %3.3f\n",sfrq);
      fclose(inpf1);
      sprintf(cmd, "Pbox hn_pc9.RF  -p %.0f -l %.1f \n",  tpwr-6
, 1.0e6*pw*2.0*compH);
          system(cmd);

}

/*****************************************************/
/* Function that creates refocussing shape using Pbox*/
/* programmed as decoupling                          */
/*****************************************************/
void makeshape_refoc(refocpat,pulsebw, pulseofs )

  double pulsebw, pulseofs;
  char refocpat[MAXSTR];


{
  FILE  *inpf2;

  char cmd1[MAXSTR];
  double compH = getval("compH"),
         pw = getval("pw"),
         tpwr = getval("tpwr"),
         sfrq = getval("sfrq");

      sprintf(cmd1, "%s/shapelib/Pbox.inp", userdir);

      if((inpf2 = fopen(cmd1, "wb")) == NULL)
    {
      printf("Cannot open \"%s\"\n", cmd1);
      exit(1);
    }
      fprintf(inpf2, "{ %s %3.3fp %3.3fp }\n",refocpat,pulsebw,pulseofs);
      fprintf(inpf2, "type = d\n");
      fprintf(inpf2, "refofs = 4.77p\n");
      fprintf(inpf2, "sfrq = %3.3f\n",sfrq);
      fclose(inpf2);
      sprintf(cmd1, "Pbox hn_refoc.DEC  -p %.0f -l %.1f \n",  tpwr-6
, 1.0e6*pw*2.0*compH);
          system(cmd1);

}

/*****************************************************/
/* Function that creates n15 decoupling shape in Pbox*/
/*****************************************************/
void makeshape_ndec( )

{
  FILE  *inpf3;

  char cmd1[MAXSTR];
  double compN = getval("compN"),
         pwN = getval("pwN"),
         pwNlvl = getval("pwNlvl"),
         dfrq2 = getval("dfrq2");

      sprintf(cmd1, "%s/shapelib/Pbox.inp", userdir);

      if((inpf3 = fopen(cmd1, "wb")) == NULL)
    {
      printf("Cannot open \"%s\"\n", cmd1);
      exit(1);
    }
      fprintf(inpf3, "{ %s %s %s }\n","WURST40","40p/2m","119p");
      fprintf(inpf3, "type = d\n");
      fprintf(inpf3, "refofs = 119p\n");
      fprintf(inpf3, "sfrq = %3.3f\n",dfrq2);
      fprintf(inpf3, "sucyc =  %s\n","d");
      fclose(inpf3);
      sprintf(cmd1, "Pbox hncompdec.DEC  -p %.0f -l %.1f \n",  pwNlvl-6
, 1.0e6*pwN*2.0*compN);
          system(cmd1);

}

