/*
 * Copyright (C) 2015  University of Oregon
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Apache License, as specified in the README file.
 *
 * For more information, see the README file.
 */

#include "oopc.h"
#include  "acqparms.h"

extern int bgflag;

/*------------------------------------------------
|  pre_expsequence():
|  This routine is for users that want to preform
|  functions once prior to the experiment.
|  Change the follow function to suit your needs.
+------------------------------------------------*/
void pre_expsequence()
{
  /*-----------------------------------------------------------------------
  |  You are responsible for any any fifo words generated to be outputed 
  |  failure to do so may result in unpredictable and possibly destructive
  |  settings of the hardware!!!!
  +----------------------------------------------------------------------*/
  /* Example of outputing fifo words:  */
#ifdef XXX
  G_Delay(DELAY_TIME, 0.01, 0);  /* time for SFIFO code to stuff halt before foo */
  putcode(STFIFO);            /* start fifo */
  putcode(SFIFO);             /* Stop and wait for fifo to finish */
  curfifocount = 0;
#endif
  return;
}

