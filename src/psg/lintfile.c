/*
 * Copyright (C) 2015  Stanford University
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Apache License, as specified in the README file.
 *
 * For more information, see the README file.
 */

/* 
   This file contains the functions the user may call within a pulse
   sequence.  The functions are stripped of their internals.  This
   file is then passed through lint to generate the lint library
   "libl-lpsg.ln".  The lint library is used in the seqgenmake makefile
   to check the user's pulse sequence with lint.

   The "libl-lpsg.ln" was generated by "lint -a -n -z -DLINT -Cpsg lintfile.c"
*/

/* LINT LIBRARY */

#include <stdio.h>
#include <varargs.h>
#define MAXPATHL 128
#define MAXSTR 256
#define PSG_REV_NUM 2
#define NOTFOUND -1
#define OK 1
#define NOTOK 0
#define MAXTABLE  60
#define MAX_RFCHAN_NUM 3
#include "oopc.h"

/* defines from macros.h  */
#define  DELAY1 0
#define  DELAY2 1
#define  DELAY3 2
#define  DELAY4 3
#define  DELAY5 4
#define NSEC 1
#define USEC 2
#define MSEC 3
#define SEC  4
/* Note: defines duplicated in acodes.h, macros.h */
#define         TCNT 1
#define         HSLINE 2
#define         TCNT_HSLINE 3
#define         TWRD 4
#define         TWRD_HSLINE 5
#define         TWRD_TCNT 6
/*----------------------------------------*/

int bgflag = 0;

/* --- code type definitions, can be changed for different machines */
typedef char codechar;		/* 1 bytes */
typedef short codeint;		/* 2 bytes */
typedef long  codelong;		/* 4 bytes */

int          PSfile;	/* file discriptor for Acode disk file */
char       **cnames;	/* pointer array to variable names */
codeint     *preCodes;	/* pointer to the start of the Acodes array */
codeint     *Codes;	/* pointer to the start of the Acodes array */
long	     Codesize;	/* size of the malloc space for codes */
long	     CodeEnd;	/* End Address  of the malloc space for codes */
codeint     *Codeptr; 	/* pointer into the Acode array */
codeint     *codestadr;	/* acode start address in Codes */
int          nnames;	/* number of variable names */
int          ntotal;	/* total number of variable names */
int          ncvals;	/* NUMBER OF VARIABLE  values */
codelong     codestart;	/* Beginning offset of a PS lc,auto struct & code */
codelong     startofAcode;	/* Beginning offset of actual Acodes */
double     **cvals;		/* pointer array to variable values */

char rftype[MAXSTR];	/* type of rf system used for trans & decoupler */
char rfband[MAXSTR];	/* RF band of trans & dec  (high or low) */
double  cattn[MAX_RFCHAN_NUM];/* indicates coarse attn for channels */
double  fattn[MAX_RFCHAN_NUM]; /* indicates fine attn for channels */
char rfwg[MAXSTR];       /* y/n for rf waveform generators */
char gradtype[MAXSTR];   /* char keys w-waveform gen s-sisco n-none */


/* --- global flags --- */
int  acqiflag = 0;      /* if 'acqi' was an argument, then interactive output*/
int  ok;		/* global error flag */
int  ap_ovrride;	/* global flag to reset HSL's after AP event */
int  rcvroff_flag;	/* global flag to indicate status of receiver */
int  automated;		/* True if system is an automated one */
int  H1freq;		/* Proton Freq. of instrument 200,300,400,500 */
int  ptsval[2];		/* PTS type for trans & decoupler */
int  phtable_flag = 0;	/* global flag for phasetables */
int  newdec;		/* True if system uses the direct synthesis for dec */
int  newtrans; 		/* True if system uses the direct synthesis for trans */
int  newtransamp;	/* True if system uses linear amplifiers for trans */
int  newdecamp;		/* True if system uses linear amplifiers for dec */
int  vttype;		/* VT type 0=none,1=varian,2=oxford */

/* table address and index for implementation of phasetables */

/* acquisition */
double  sw; 		/* Sweep width */
double  nf;		/* For E.A.T., number of fids in Pulse sequence */
double  np; 		/* Number of data points to acquire */
double  nt; 		/* number of transients */
double  sfrq;   	/* Transmitter Frequency MHz */
double  dfrq; 		/* Decoupler Frequency MHz */
double  dfrq2; 		/* 2nd Decoupler Frequency MHz */
double  fb;		/* Filter Bandwidth */
double  bs;		/* Block Size */
double  tof;		/* Transmitter Offset */
double  dof;		/* Decoupler Offset */
double  dof2;		/* 2nd Decoupler Offset */
double  gain; 		/* receiver gain value, or 'n' for autogain */
double  dlp; 		/* decoupler Low Power value */
double  dhp; 		/* decoupler High Power value */
double  tpwr; 		/* Transmitter pulse power */
double  tpwrf;          /* Transmitter fine linear attenuator for pulse power*/
double  dpwr; 		/* decoupler power */
double  dpwrf;          /* Decoupler fine linear attenuator for pulse power */
double  dpwr2; 		/* 2nd decoupler power */
double  filter;         /* pulse Amp filter setting */
double  xmf;            /* transmitter modulation frequency */
double  dmf;            /* decoupler modulation frequency */
double  dmf2;           /* decoupler modulation frequency */
double  vttemp; 	/* VT temperauture setting */
double  vtwait;         /* VT temperature timeout setting */
double  vtc;            /* VT temperature cooling gas setting */
int     dhpflag;	/* decoupler High Power Flag */

    /* --- pulse widths --- */
double  pw; 		/* pulse width */
double  p1; 		/* A pulse width */
double  pw90;		/* 90 degree pulse width */
double  hst;    	/* time homospoil is active */

/* --- delays --- */
double  alfa; 		/* Time after rec is turned on that acqbegins */
double  beta; 		/* audio filter time constant */
double  d1; 		/* delay */
double  d2; 		/* A delay, used in 2D experiments */
double  pad; 		/* Pre-acquisition delay */
double  rof1; 		/* Time receiver is turned off before pulse */
double  rof2;		/* Time after pulse before receiver turned on */

/* --- total time of experiment --- */
double  totaltime; 	/* total timer events for a fid */
double  exptime; 	/* total time for an exp duration estimate */

/* --- programmable decoupling sequences --- */
char  xseq[MAXSTR];
char  dseq[MAXSTR];
char  dseq2[MAXSTR];
 
/* --- status control --- */
char  xm[MAXSTR];	/* transmitter status control */
char  xmm[MAXSTR]; 	/* transmitter modulation type control */
char  dm[MAXSTR];	/* decoupler status control */
char  dmm[MAXSTR]; 	/* decoupler modulation type control */
char  dm2[MAXSTR];      /* 2nd decoupler status control */
char  dmm2[MAXSTR];     /* 2nd decoupler modulation type control */
char  homo[MAXSTR]; 	/* homospoil decoupler mode control */
char  hs[MAXSTR]; 	/* homospoil status control */
int   xmsize;		/* number of characters in xm */
int   xmmsize;		/* number of characters in xmm */
int   dmsize;		/* number of characters in dm */
int   dmmsize;		/* number of characters in dmm */
int   dm2size;          /* number of characters in dm2 */
int   dmm2size;         /* number of characters in dmm2 */
int   homosize;		/* number of characters in homo */
int   hssize; 		/* number of characters in hs */

int curfifocount;		/* current number of word in fifo */
int setupflag;			/* alias used to invoke PSG ,go=0,su=1,etc */
int ra_flag;                    /* ra flag */
int statusindx;			/* current status index */
int HSlines;			/* High Speed output board lines */

/* --- Explicit acquisition parameters --- */
int hwlooping;			/* hardware looping inprogress flag */
int hwloopelements;		/* PSG elements in hardware loop */
int starthwfifocnt;		/* fifo count at start of hwloop */
int acqtriggers;			/*# of data acquires */
int noiseacquire;		/* noise acquiring flag */

/*- These values are used so that they are changed only when their values do */
int oldlkmode;			/* previous value of lockmode */
int oldspin;			/* previous value of spin */
int oldwhenshim;		/* previous value of shimming mask */
double oldvttemp;			/* previous value of vt tempature */

/*- These values are used so that they are included in the Acode only when */
/*  the next value out of the arrayed values has been obtained */
int oldpadindex;		/* previous value of pad value index */
int newpadindex;		/* new value of pad value index */

/* --- Pulse Seq. globals --- */
double xmtrstep;		/* phase step size trans */
double decstep;			/* phase step size dec */
codeint idc = PSG_REV_NUM;	/* PSG software rev number,(initacqparms)*/
codeint npr$ptr;		/* offset into code to np */
codeint ct;			/* offset into code to ct */
codeint oph;			/* offset into code to oph */
codeint ssval;			/* offset into code to variable ss */
codeint ssctr;			/* offset into code to variable ssct */
codeint bsval;			/* offset into code to variable bs */
codeint bsctr;			/* offset into code to bsct */
codeint HSlines$ptr;		/* offset into code to squi */
codeint nsp$ptr;		/* offset into code to nsp */
codeint id2;			/* offset into code to variable id2 */
codeint id3;			/* offset into code to variable id3 */
codeint id4;			/* offset into code to variable id4 */
codeint zero;			/* offset into code to variable zero */
codeint one;			/* offset into code to variable one */
codeint two;			/* offset into code to variable two */
codeint three;			/* offset into code to variable three */
codeint rf500$ptr;       /* offset into code to rf500 variables */
codeint tablert;         /* offset into code to table variable */
codeint v1;			/* offset into code to v1 */
codeint v2;			/* offset into code to v2 */
codeint v3;			/* offset into code to v3 */
codeint v4;			/* offset into code to v4 */
codeint v5;			/* offset into code to v5 */
codeint v6;			/* offset into code to v6 */
codeint v7;			/* offset into code to v7 */
codeint v8;			/* offset into code to v8 */
codeint v9;			/* offset into code to v9 */
codeint v10;			/* offset into code to v10 */
codeint v11;			/* offset into code to v11 */
codeint v12;			/* offset into code to v12 */
codeint v13;			/* offset into code to v13 */
codeint v14;			/* offset into code to v14 */
codeint tpwrrt;			/* offset to special tpwr */
codeint dhprt;			/* offset to special dhprt */
codeint tphsrt;			/* offset to special tphsrt */
codeint dphsrt;			/* offset to special dphsrt */

codeint dlvlrt;			/* offset to special dlvlrt */

codeint hwloop$ptr;		/* offset to hardware loop Acode */
codeint multhwlp$ptr;		/* offset to multiple hardware loop flag */
codeint nsc$ptr;		/* offset to NSC Acode */

unsigned long	ix;		/* FID currently in Acode generation */
int 	nth2D;			/* 2D Element currently in Acode generation (VIS usage)*/
int     arrayelements;		/* number of array elements */
int     fifolpsize;		/* fifo loop size (63, 512, 1k, 2k, 4k) */
int     ap_interface;           /* ap bus interface type 1=500style, 2=amt style */
/*int     acqbitmask;             /* global settings for acquisition  */

/* --- Pulse Seq. globals --- */
char vnHost[50];		/* vn machine Host name */
char acqHost[50];		/* Acq. machine Host name */
char vnHeader[50];		/* header sent to vnmr */
int vnPort;			/* vn message port for acquisition */
int vnPid;			/* vn pid for async message usage */
int acqPort;			/* Acq. message port for acquisition */
int acqPid;			/* Acq. pid for async message usage */

/*  Objects   */
Object Ext_Trig;		/* External Trigger Device */
Object ToAttn;			/* AMT Interface Obs attenuator */
Object DoAttn;			/* AMT Interface Dec attenuator */
Object Do2Attn;			/* AMT Interface Dec2 attenuator */
Object ToLnAttn;		/* Solids Linear attenuator, Observe Channel */
Object DoLnAttn;		/* Solids Linear attenuator, Decoupler Channel */
Object RF_Rout;			/* RF Routing Relay Bank */
Object RF_Opts;			/* RF Amp & etc. Options Bank */
Object RF_Opts2;		/* RF Amp & etc. Options Bank */
Object RF_Amp1_2;		/* Amp 1/2 cw vs. pulse */
Object RF_Amp3_4;		/* Amp 3/4 cw vs. pulse */
Object RF_Amp_Sol;		/* Amp Solids control*/
Object RF_hilo;
Object RF_Mod;
Object HS_Rotor;		/* High Speed Rotor Device */
Object RFChan1;          /* RF Channel Device */
Object RFChan2;          /* RF Channel Device */
Object RFChan3;          /* RF Channel Device */
Object RF_Channel[MAX_RFCHAN_NUM+1]; /* index array of RF channel Objects */


int OBSch;               /* The Acting Observe Channel */
int DECch;               /* The Acting Decoupler Channel */
int DEC2ch;              /* The Acting 2nd Decoupler Channel */
int NUMch;               /* Number of channels configured */

char    filepath[MAXPATHL];		/* file path for Codes */
char    filexpath[MAXPATHL];		/* file path for exp# file */
char    fileRFpattern[MAXPATHL];	/* path for obs & dec RF pattern file */
char    filegrad[MAXPATHL];		/* path for Gradient file */
char    filexpan[MAXPATHL];		/* path for Future Expansion file */

/* Used by locksys.c  routines from vnmr */
char systemdir[MAXPATHL];       /* vnmr system directory */
char userdir[MAXPATHL];         /* vnmr user system directory */
char curexpdir[MAXPATHL];       /* current experiment path */

/* Real-time AP table variables */
struct _Tableinfo
{
   int		reset;
   int          table_number;
   int          *table_pointer;
   int          *hold_pointer;
   int          table_size;
   int          divn_factor;
   int          auto_inc;
   int          wrflag;
   codeint      indexptr;
   codeint      destptr;
};
 
typedef struct _Tableinfo       Tableinfo;
Tableinfo       *Table[MAXTABLE];

codeint         t1, t2, t3, t4, t5, t6,
                t7, t8, t9, t10, t11, t12,
                t13, t14, t15, t16, t17, t18,
                t19, t20, t21, t22, t23, t24,
                t25, t26, t27, t28, t29, t30,
                t31, t32, t33, t34, t35, t36,
                t37, t38, t39, t40, t41, t42,
                t43, t44, t45, t46, t47, t48,
                t49, t50, t51, t52, t53, t54,
                t55, t56, t57, t58, t59, t60;

int             table_order[MAXTABLE],        
                tmptable_order[MAXTABLE],
                loadtablecall,
                last_table;

/*------------------------------------------------------------------
    RF and Gradient pattern structures
------------------------------------------------------------------*/
typedef struct _RFpattern {
    double  phase;
    double  amp;
    double  time;
} RFpattern;

typedef struct _Gpattern {
    double  amp;
    double  time;
} Gpattern;


main(argc,argv) int argc; char *argv[]; {   return(0); }

abort(error) int error; { exit(error); }

text_error(error_mess) char *error_mess; { }

close_error(int) { }

var_active(varname,tree) char	*varname; int	tree; { return 0; }

double getval(variable) char *variable; { return((double) 1.0); }

getstr(variable,buf) char *variable; char buf[]; { return; }
double sign_add(arg1,arg2) double arg1, arg2; { return((double) 1.0); }
putcode(word) codeint word; { }
clearapdatatable() { }
decblankon() { }
decblankoff() { }
declvlon() { }
declvloff() { }
decpwr(level) double level; { }
spareon() { }
spareoff() { }
   /* for macro expansion in macros.h for lint */
findsname(name,item,count) char *name, *item[]; int count; { return 0;}

HSgate(bit,state) int bit, state;	{ return; }

gatedecoupler(statindex) int  statindex; { }
gatedmmode(statindex) int  statindex; { }
extern int bgflag;
getparm(varname,vartype,tree,varaddr,size)
char *varname, *vartype, *varaddr; int tree, size;
{
}

rgradient(gid,rgamp) char gid; double rgamp; { }
/* gradient(gid,gamp) char gid; int gamp; { } */

/* vgradient(gid,gamp0,gampi,mult) char gid; int gamp0,gampi; codeint mult; { } */
getorientation(c1,c2,c3,orientname) char  *c1,*c2,*c3,*orientname; { return(0); }

hsdelay(time) double time; { }
starthardloop(rtindex) codeint	rtindex; { }
endhardloop() { }
acquire(datapts,dwell) double datapts; double dwell; { }
donoisecalc() { }
test4acquire() { }
okinhwloop() { }
notinhwloop(name) char *name; { }
initHSlines() { }
convertdbl(value,topint,botint) double value; int *topint; int *botint; { }
initdecmodfreq(freq,mode) double freq; int mode; { }
rfbandselect(band,mode) char band; int mode; { }
pulseampfilter(mode) int mode; { }
setlkfrqflt(rate,mode) double rate; int mode; { }
decouplerattn(mode) int mode; { }
dofiltercontrol(mode) int mode; { }
dowlfiltercontrol(mode) int mode; { }
initialRF() { }
INITVAL(value,index) double value; codeint index; { }
loop(count,counter) codeint count; codeint counter; { }
endloop(counter) codeint    counter; { }
ifzero(rtvar) codeint rtvar;	{   }
elsenz(rtvar) codeint rtvar; { }
endif(rtvar) codeint rtvar; { }
push(word)
codeint word; { }
codeint pop() { }
validrtvar(rtvar)
codeint rtvar; { return 0; }
incr(a) codeint a; { }
decr(a) codeint a; { }
assign(a,b) codeint a; codeint b; { }
dbl(a,b) codeint a; codeint b; { }
hlv(a,b) codeint a; codeint b; { }
modn(a,b,c) codeint a; codeint b; codeint c; { }
mod4(a,b) codeint a; codeint b; { }
mod2(a,b) codeint a; codeint b; { }
add(a,b,c) codeint a; codeint b; codeint c; { }
sub(a,b,c) codeint a; codeint b; codeint c; { }
mult(a,b,c) codeint a; codeint b; codeint c; { }
divn(a,b,c) codeint a; codeint b; codeint c; { }
orr(a,b,c) codeint a; codeint b; codeint c; { }
ifnz(a,b,c) codeint a; codeint b; codeint c; { }
ifmi(a,b,c) codeint a; codeint b; codeint c; { }
setapchip(apaddr,apreg,wordflag,rtflag,value) int apaddr,apreg,wordflag,rtflag,value; { }
offset(offset,device) double offset; int device; { }
power(powerptr,device) codeint powerptr; int device; { }
rlpower(powerval,device) double powerval; int device; { }
void setprgmode(mode,device) int mode; int device; { }
pwrf(value,device) int value; int device; { return; }
stepsize(stepsiz,device) double stepsiz; int device; { return; }
phaseshift(basephase,mult,device) double basephase; codeint mult; int device; { }
loadtable(filename) char	filename[MAXSTR]; { }
checkforcomments(filedescriptor) FILE	*filedescriptor; { }
setreceiver(tablename) codeint	tablename; { }
tablertv(tablename) codeint	tablename; { }
writetable(tableinfo) Tableinfo	*tableinfo; { }

settable(tablename, numelements, tablearray)
codeint	tablename; int	numelements, tablearray[];
{
}

getelem(tablename, AP_indexpointer, AP_destpointer)
codeint	tablename, AP_indexpointer, AP_destpointer;
{
}

tabletop(operationtype, table1name, table2name, modulovalue)
codeint	table1name, table2name; int	operationtype, modulovalue;
{
}

tablesop(operationtype, tablename, scalarvalue, modulovalue)
codeint	tablename; int	operationtype, scalarvalue, modulovalue;
{
}

int reparse_release(startindex, endindex)
int     startindex, endindex;
{
}

FILE *open_table(basename, concatname, inputname, permission)
char    inputname[MAXSTR], basename[MAXSTR], concatname[MAXSTR], permission[3];
{
}

int read_number(tablefile, eofflag) int     eofflag; FILE    *tablefile; { }

int check_bounds(paramval, maxvalue, minvalue)
int     paramval, maxvalue, minvalue; 
{ 
}

load_element(outcount, incount, table_index, elempntrpntr,
             values, incntflag)
int     outcount, incount, incntflag, table_index, *values, **elempntrpntr;
{
}

int store_in_table(table_index, elementpntr)
int     table_index, *elementpntr;
{
}

writedebug(fd, ntables) int     ntables; FILE    *fd; { }

int checktable(tblinfo, tblname, namechk, numberchk,
        sizechk, destchk, indxchk, writechk)
codeint  tblname; int namechk, numberchk, sizechk, destchk, writechk, indxchk;
Tableinfo       *tblinfo;
{
}

reset_table(tblinfo) Tableinfo       *tblinfo; { }
int table_math(optype, value1, value2)
int     optype, *value1, *value2;
{
}
preacqdelay() { }

elemvalues(elem) int elem; { return(1); }
elemindex(fid,elem) int fid; int elem; { return(1); }

gensim2pulse(pw1, pw2, phase1, phase2, rx1, rx2, device1, device2)
codeint	phase1, phase2; int device1, device2; double pw1, pw2, rx1, rx2;
{
	return;
}

gensim3pulse(pw1, pw2, pw3, phase1, phase2, phase3, rx1, rx2,
		device1, device2, device3)
codeint	phase1,		/* phase for first RF channel			*/
	phase2,		/* phase for second RFchannel			*/
	phase3;		/* phase for third RF channel			*/
int	device1,	/* name of first RF channel, e.g., TODEV	*/
	device2,	/* name of second RF channel			*/
	device3;	/* name of third RF channel			*/
double	pw1,		/* pulse length for first RF channel		*/
	pw2,		/* pulse length for second RF channel		*/
	pw3,		/* pulse length for third RF channel		*/
	rx1,		/* pre-pulse delay				*/
	rx2;		/* post-pulse delay				*/
{
	return;
}

write_to_acqi(label, value, units, min, max, type, scale, counter)
char *label; 
double value, units; int min, max, type, scale;
codeint         counter;
{
}

incdelay(wbase, wincr, mult)
double          wbase, wincr;
codeint         mult;
{
	return;
}

apovrride() { }
rcvron() { }
rcvroff() { }
var1on() { }
var1off() { }
var2on() { }
var2off() { }
sp1on() { }
sp1off() { }
sp2on() { }
sp2off() { }

setPTS(ptsvalue,device) double ptsvalue; int device; { }

setSISPTS(base,offset,device,setoop) long base,offset; int setoop,device; { }

apcodes(boardadd,breg,longw) int boardadd, breg; long longw; { }

long ptsconv(value) int value; { }

long ptsofs(ofsint) long ofsint; { long ptsobcd = 0; return(ptsobcd); }

setdirectPTS(specfreq,offset,device) double specfreq; double offset; int device; { }

double
setoffsetsyn(specfreq,offset,device,setpts)
double specfreq;	/* base freq. (sfrq or dfrq) */
double offset;		/* freq offset (tof or dof) */
int    device;          /* DODEV or TODEV */
int    setpts;		/* PTS is set if TRUE */
{
    return((double) 1.0);
}

setparm(varname,vartype,tree,varaddr,index)
char *varname;
char *vartype;
int   tree;
char *varaddr;	/* For Reals, pointer is recased as double; ie.(double *) */
int	 index;
{
    return(0);
}

observepower(reqpower) double	reqpower; { }

decouplepower(reqpower) double	reqpower; { }
setrfattenuation(ampval, device) int 	device; double 	ampval; { }
status(index) int    index; { }
STATUSDELAY(index,delaytime) int    index; double delaytime; { }
timerwords(time,tword1,tword2) double  time; int  *tword1; int  *tword2; { }

Object ObjectNew(dispatch, name) 
Functionp dispatch; char *name;
{
   return( (Object) 0);
}

/*VARARGS2*/
SetDeviceAttr(obj, va_alist) Object obj; va_dcl { return(0); }
/*VARARGS2*/
SetAPAttr(obj, va_alist) Object obj; va_dcl { return(0); }
/*VARARGS2*/
SetAPBit(obj, va_alist) Object obj; va_dcl { return(0); }
/*VARARGS2*/
SetAttnAttr(obj,va_alist) Object obj; va_dcl { return(0); }
/*VARARGS2*/
SetEventAttr(obj,va_alist) Object obj; va_dcl { return(0); }
/*VARARGS2*/
sync_on_event(dev_obj, va_alist) Object dev_obj; va_dcl { }
/*VARARGS1*/
int G_Power(va_alist) va_dcl { }
/*VARARGS1*/
int G_Pulse(va_alist) va_dcl { }
/*VARARGS1*/
int G_Delay(va_alist) va_dcl { }
/*VARARGS1*/
int G_RTDelay(va_alist) va_dcl { }
/*VARARGS1*/
int G_Sweep(va_alist) va_dcl { }

/*VARARGS0*/
int fprintf(va_alist) va_dcl { }
/*VARARGS0*/
int printf(va_alist) va_dcl { }


genshaped_pulse(name, width, phase, rx1, rx2, g1,
                        g2, rfdevice)
char  *name; codeint  phase; int  rfdevice;
double  width, rx1, rx2, g1, g2; { return; }


gensim2shaped_pulse(name1, name2, width1, width2, phase1,
                   phase2, rx1, rx2, g1, g2, rfdevice1,
                   rfdevice2)
char  *name1, *name2; codeint  phase1, phase2; int   rfdevice1, rfdevice2;
double  width1, width2, rx1, rx2, g1, g2; { return; }


gensim3shaped_pulse(name1, name2, name3, width1, width2,
                 width3, phase1, phase2, phase3, rx1,
                 rx2, g1, g2, rfdevice1, rfdevice2,
                 rfdevice3)
char  *name1, *name2, *name3; codeint  phase1, phase2, phase3;
int  rfdevice1, rfdevice2, rfdevice3;
double  width1, width2, width3, rx1, rx2, g1, g2; { return; }

gen_apshaped_pulse(shape, width, phase, tbl1, tbl2, rx1, rx2, device)
char shape[MAXSTR]; codeint phase, tbl1, tbl2; int device;
double width, rx1, rx2; { }

genspinlock(name, pw_90, deg_res, phsval, ncycles, rfdevice)
char  *name; int  ncycles, rfdevice; double  pw_90, deg_res;
codeint  phsval; { return; }

gen2spinlock(name1, name2, pw90_1, pw90_2, deg_res1, deg_res2, phs_1, phs_2,
		 ncycles, rfdev1, rfdev2)
char  *name1, *name2; codeint  phs_1, phs_2; int  ncycles, rfdev1, rfdev2;
double  pw90_1, pw90_2, deg_res1, deg_res2; { return; }


int prg_dec_on(name, pw_90, deg_res, rfdevice)
char  *name; int  rfdevice; double  pw_90, deg_res;
{
	return(1);
}


void prg_dec_off(stopmode, rfdevice)
int  rfdevice, stopmode; { return; }


/* shapedgradient(name,width,amp,which,loops,wait_4_me)
 * char *name,which; double width,amp; int wait_4_me,loops;
 * {
 * }
 */
shaped_2D_gradient(name,width,amp,which,loops,wait_4_me,tag)
char *name,which; double width,amp; int wait_4_me,loops,tag;
{
}
shaped_2D_Vgradient(name,width,vx,vconst,vmult,which,loops,wait_4_me,tag)
char *name,which; double width; int vx, vmult,vconst; int wait_4_me,loops,tag;
{
}

int no_grad_wg(gid) char gid; { return(0); }
int wgtb(tb,itick,n) double tb; int itick,n; { return(1); }
point_wg(which_wg,where_on_wg) int which_wg, where_on_wg; { return; }
command_wg(which_wg,cmd_wg) int which_wg, cmd_wg; { return; }
int wfg_remap(dev_brd1, dev_brd2, dev_brd3)
int     dev_brd1, dev_brd2, dev_brd3;
{
	return;
}

/*-------------------------------------------------------------------
|  Macro function equivilents to allow lint to check parameters
|  to the macro. The convention is to use the macro's name but
|  in all capitals. (To use its own name would result in recusive macro
|  calls., this also gets around lint's limitation on macro expansions )
|				2/18/89  Greg B.
+------------------------------------------------------------------*/
/*--------------------------------------------------------------------
|    Changed from codeint to double for xgate() is now a macro in
|    in macros.h which calls sync_on_event()
+---------------------------------------------------------------------*/
XGATE(count) double count; { }
/*--------------------------------------------------------------------
| rotorsync() -  macro in macros.h which calls sync_on_event()
+---------------------------------------------------------------------*/
ROTORSYNC(rtparam) codeint rtparam; { }

/*--------------------------------------------------------------------
| rotorperiod() -  macro in macros.h which calls get_hardware()
+---------------------------------------------------------------------*/
ROTORPERIOD(rtparam) codeint rtparam; { }

/*--------------------------------------------------------------------
| User AP device calls
+---------------------------------------------------------------------*/
SETUSERAP(value,reg) int value,reg; { }

VSETUSERAP(rtparam,reg) codeint rtparam; int reg; { }

READUSERAP(rtparam) codeint rtparam; { }


/*---------------------------------------------------------------------
|  AP tables
+----------------------------------------------------------------------*/
SETAUTOINCREMENT(tname) codeint	tname; { }

SETDIVNFACTOR(tname, divn_factor) codeint tname; int divn_factor; { }

TSADD(tablename, scalarvalue, modulovalue)
codeint tablename; int     scalarvalue, modulovalue; { }

TSDIV(tablename, scalarvalue, modulovalue)
codeint tablename; int     scalarvalue, modulovalue; { }

TSMULT(tablename, scalarvalue, modulovalue)
codeint tablename; int     scalarvalue, modulovalue; { }

TSSUB(tablename, scalarvalue, modulovalue)
codeint tablename; int     scalarvalue, modulovalue; { }

TTADD(table1name, table2name, modulovalue)
codeint table1name, table2name; int     modulovalue; { }

TTDIV(table1name, table2name, modulovalue)
codeint table1name, table2name; int     modulovalue; { }

TTMULT(table1name, table2name, modulovalue)
codeint table1name, table2name; int     modulovalue; { }

TTSUB(table1name, table2name, modulovalue)
codeint table1name, table2name; int     modulovalue; { }

/*---------------------------------------------------------------------
|  Frequency offsets
+----------------------------------------------------------------------*/

IOFFSET( value, device, string )
double value;
int device;
char *string;
{
}

/*---------------------------------------------------------------------
|  Generic pulses
+----------------------------------------------------------------------*/
GENPULSE(pulsewidth, phaseptr, device)
double pulsewidth; codeint phaseptr; int device; { }
 
GENRGPULSE(pulsewidth, phaseptr, rx1, rx2, device)
double pulsewidth, rx1, rx2;  codeint phaseptr; int device;  { }


/*---------------------------------------------------------------------
|  Observe pulses
+----------------------------------------------------------------------*/
OBSPULSE() { }

PULSE(decpulse,phaseptr) double decpulse; codeint phaseptr; { }
  
RGPULSE(pulsewidth, phaseptr, rx1, rx2)
double pulsewidth, rx1, rx2; codeint phaseptr; { }

IOBSPULSE(string)
char *string; { }
  
IPULSE(decpulse,phaseptr,string) 
double decpulse; codeint phaseptr; char *string; { }
  
IRGPULSE(pulsewidth, phaseptr, rx1, rx2,string) 
double pulsewidth, rx1, rx2; codeint phaseptr; char *string; { }

SIMPULSE(transpw,decpw,transphase,decphase,rx1,rx2)
double transpw,decpw,rx1,rx2; codeint transphase,decphase; { }

/*---------------------------------------------------------------------
|  Main decoupler pulses
+----------------------------------------------------------------------*/
DECPULSE(decpulse,phaseptr) double decpulse; codeint phaseptr; { }
 
DECRGPULSE(pulsewidth, phaseptr, rx1, rx2)
double pulsewidth, rx1, rx2; codeint phaseptr; { }
 
IDECPULSE(decpulse,phaseptr,string)
double decpulse; codeint phaseptr; char *string; { }
 
IDECRGPULSE(pulsewidth, phaseptr, rx1, rx2,string)
double pulsewidth, rx1, rx2; codeint phaseptr; char *string; { }


/*---------------------------------------------------------------------
|  2nd decoupler pulses
+----------------------------------------------------------------------*/
DEC2RGPULSE(pulsewidth, phaseptr, rx1, rx2)
double pulsewidth, rx1, rx2; codeint phaseptr; { }

IDEC2RGPULSE(pulsewidth, phaseptr, rx1, rx2,string)
double pulsewidth, rx1, rx2; codeint phaseptr; char *string; { }


/*---------------------------------------------------------------------
|  delays
+----------------------------------------------------------------------*/
DELAY(time) double time; { }

IDELAY(time, string)
double time; char *string; { }

INITDELAY(incrtime,index)
double incrtime; int index; { }

INCDELAY(multparam,index)
int multparam,index; { }

VDELAY(base,rtcnt)
int base,rtcnt;  { }


/*---------------------------------------------------------------------
|  phase shifts
+----------------------------------------------------------------------*/
STEPSIZE(stepsiz,device) double stepsiz; int device; {  }

/*---------------------------------------------------------------------
|  power
+----------------------------------------------------------------------*/
PWRF(value, device)  double value; int device; { }

IPWRF(value, device, string)  double value; int device; char *string; { }


/*---------------------------------------------------------------------
|  RF on/off
+----------------------------------------------------------------------*/
RFON(device)  int device; { }

XMTRON()  { }

DECON()  { }

DEC2ON()  { }

RFOFF(device)  int device; { }

XMTROFF()  { }

DECOFF()  { }

DEC2OFF()  { }


/*---------------------------------------------------------------------
|  quadrature phaseshifts
+----------------------------------------------------------------------*/
GENQDPHASE(phaseptr, device) codeint phaseptr; int device; { }

TXPHASE(phaseptr) codeint phaseptr; { }

DECPHASE(phaseptr) codeint phaseptr; { }

DEC2PHASE(phaseptr) codeint phaseptr;   {  }


/*--------------------------------------------------------------------- 
|  hardware small-angle phaseshifts
+----------------------------------------------------------------------*/
GENSAPHASE(phaseptr, device) codeint phaseptr; int device;  { }

XMTRPHASE(phaseptr) codeint phaseptr; { }

DCPLRPHASE(phaseptr) codeint phaseptr;  { }

DCPLR2PHASE(phaseptr) codeint phaseptr;   {  }


/*---------------------------------------------------------------------
|  WFG shaped pulses
+----------------------------------------------------------------------*/
SHAPED_PULSE(name, width, phase, rx1, rx2)
double width,rx1,rx2; codeint phase; char *name; { }

DECSHAPED_PULSE(name, width, phase, rx1, rx2)
double width,rx1,rx2; codeint phase; char *name; { }

DEC2SHAPED_PULSE(name, width, phase, rx1, rx2)
double width,rx1,rx2;  codeint phase; char *name; { }

SIMSHAPED_PULSE(n1, n2, w1, w2, ph1, ph2, r1, r2)
double w1,w2,r1,r2;   codeint ph1,ph2;  char *n1,*n2; { }

SIM3SHAPED_PULSE(n1, n2, n3, w1, w2, w3, ph1, ph2, ph3, r1, r2)
double w1,w2,w3,r1,r2;  codeint ph1,ph2,ph3;  char *n1,*n2,*n3; { }

SHAPEDVPULSE(name, width, rtamp, phase, rx1, rx2)
char *name; codeint rtamp, phase;
double width, rx1, rx2; { }


/*--------------------------------------------------------------------- 
|  AP bus-based shaped pulses 
+----------------------------------------------------------------------*/
APSHAPED_PULSE(shape, width, phase, tbl1, tbl2, rx1, rx2)
char shape[MAXSTR]; codeint phase, tbl1, tbl2;
double width, rx1, rx2; { }

APSHAPED_DECPULSE(shape, width, phase, tbl1, tbl2, rx1, rx2)
char shape[MAXSTR]; codeint phase, tbl1, tbl2;
double width, rx1, rx2; { }

APSHAPED_DEC2PULSE(shape, width, phase, tbl1, tbl2, rx1, rx2)
char shape[MAXSTR]; codeint phase, tbl1, tbl2;
double width, rx1, rx2; { }

/*---------------------------------------------------------------------
|  WFG spin locks
+----------------------------------------------------------------------*/
SPINLOCK(name, pp_90, pp_res, phase, nloops)
int phase,nloops; double pp_res,pp_90; char *name; {  }

DECSPINLOCK(name, pp_90, pp_res, phase, nloops)
int phase,nloops; double pp_res,pp_90; char *name; {  }

DEC2SPINLOCK(name, pp_90, pp_res, phase, nloops)
int phase,nloops; double pp_res,pp_90; char *name; {  }


/*--------------------------------------------------------------------- 
|  Programmable decoupling with WFG
+----------------------------------------------------------------------*/ 
OBSPRGON(name, pp_90, pp_res)
double pp_res,pp_90; char *name; {  }

DECPRGON(name, pp_90, pp_res)
double pp_res,pp_90; char *name; {  }

DEC2PRGON(name, pp_90, pp_res)
double pp_res,pp_90; char *name; {  }

OBSPRGOFF()  { }

DECPRGOFF()  { }

DEC2PRGOFF()  { }

/*---------------------------------------------------------------*/
/*- SISCO Lint defines (gradients)				-*/
/*---------------------------------------------------------------*/

RGRADIENT(gid,rgamp) char gid; double rgamp; { }

VGRADIENT(gid,gamp0,gampi,mult)
char gid; int gamp0,gampi; codeint mult; { }

INCGRADIENT(gid,gamp0,gamp1,gamp2,gamp3,mult1,mult2,mult3)
char gid; int gamp0,gamp1,gamp2,gamp3; codeint mult1,mult2,mult3; { }

double SHAPED_INC_GRADIENT(axis,pattern,width,a0,a1,a2,a3,x1,x2,x3,loops,wait)
char axis; char *pattern; double width; double a0, a1, a2, a3; 
codeint x1, x2, x3; int loops; int wait; { }

SHAPEDGRADIENT(name,width,amp,which,loops,wait_4_me)
char *name,which; double width,amp; int wait_4_me,loops; { }

SHAPED_2D_GRADIENT(name,width,amp,which,loops,wait_4_me,tag)
char *name,which; double width,amp; int wait_4_me,loops,tag; { }

SHAPED_V_GRADIENT(name,width,amp_const,amp_incr,amp_vmult,which,vloops,
		wait_4_me,tag)
char *name,which; double width,amp_const,amp_incr;
codeint amp_vmult,vloops; int wait_4_me,tag; {  }

OBLIQUE_GRADIENT(level1,level2,level3,ang1,ang2,ang3)
double level1,level2,level3; double ang1,ang2,ang3; { }

OBLIQUE_SHAPEDGRADIENT(pat,width,lvl1,lvl2,lvl3,ang1,ang2,ang3,loops,wait)
char pat[]; double width; double lvl1,lvl2,lvl3; 
double ang1,ang2,ang3; int loops,wait; { }

OBLIQUE_SHAPED3GRADIENT(pat1,pat3,pat3,width,lvl1,lvl2,lvl3,ang1,ang2,ang3,loops,wait)
char pat1[],pat2[],pat3[]; double width; double lvl1,lvl2,lvl3; 
double ang1,ang2,ang3; int loops,wait; { }

PHASE_ENCODE_GRADIENT(stat1,stat2,stat3,step2,vmult2,lim2,ang1,ang2,ang3)
double  lim2,stat1,stat2,stat3,step2,ang1,ang2,ang3; codeint vmult2; { }

PHASE_ENCODE_SHAPEDGRADIENT(pat,width,stat1,stat2,stat3,step2,
        vmult2,lim2,ang1,ang2,ang3,vloops,wait,tag)
char pat[]; int tag,wait; codeint vmult2,vloops;
double  lim2,stat1,stat2,stat3,step2,ang1,ang2,ang3,width; { }

PHASE_ENCODE3_GRADIENT(stat1, stat2, stat3, step1, step2, step3,
		       vmult1, vmult2, vmult3, lim1, lim2, lim3,
		       ang1, ang2, ang3)
double  lim1,lim2,lim3,stat1,stat2,stat3,step1,step2,step3;
double  ang1,ang2,ang3; codeint vmult1,vmult2,vmult3; { }

PHASE_ENCODE3_SHAPEDGRADIENT(pat, width, stat1, stat2, stat3, 
			step1, step2, step3, vmult1, vmult2, vmult3,
			lim1, lim2, lim3, ang1, ang2, ang3, loops, wait)
char    *pat; double width,lim1,lim2,lim3,stat1,stat2,stat3;
double  step1,step2,step3,ang1,ang2,ang3; codeint vmult1,vmult2,vmult3;
int     loops,wait; { }

OBLIQUE_GRADPULSE(level1,level2,level3,ang1,ang2,ang3,gradtime)
double level1,level2,level3; double ang1,ang2,ang3,gradtime; { }


POSITION_OFFSET(pos,grad,resfrq,device)
double pos,grad,resfrq; int device; { }

POSITION_OFFSET_LIST(posarray,grad,nslices,resfrq,device,listno,apv1)
double posarray[],resfrq,grad,nslices; int device, listno; codeint apv1; { }

SETHKDELAY(delaytim)
double delaytim; { }

int CREATE_OFFSET_LIST(list,nvals,device,list_no)
double *list; int nvals; int device; int list_no; { return(0); }

int CREATE_DELAY_LIST(list,nvals,list_no)
double *list; int nvals; int list_no; { return(0); }

VGET_ELEM(list_no, vindex)
int list_no; codeint vindex; { }

INIT_VSCAN(rtvar,npts)
codeint rtvar; double npts; { }

VSCAN(rtvar)
codeint rtvar; { }

INIT_RFPATTERN (pat_name, rfpat_struct, nsteps)
char *pat_name; RFpattern *rfpat_struct; int nsteps; { }

INIT_GPATTERN (pat_name, gradpat_struct, nsteps)
char *pat_name; Gpattern *gradpat_struct; int nsteps; { }

int GETARRAY (parname, array, arraysize)
int arraysize; char *parname; double array[]; { return(0); }

RLPOWER(powerval,device) double powerval; int device; { }

