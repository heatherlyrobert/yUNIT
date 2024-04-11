#include "yUNIT.h"
#include "yUNIT_priv.h"


static char S_saved     =  '-';
static char S_proj      [LEN_LABEL] = "";
static char S_unit      [LEN_TITLE] = "";
static char S_scrp      =    0;
static char S_desc      [LEN_LONG]  = "";
static char S_terse     [LEN_LABEL] = "";
static char S_wave      =  '·';
static char S_stage     =  '·';
static char S_expe      [LEN_SHORT] = "";

char
yunit_unage             (char a_age [LEN_SHORT], int *r_secs)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_age       [LEN_SHORT] = "";
   int         l           =    0;
   char        x_unit      =  '-';
   int         x_multi     =    0;
   int         x_num       =    0;
   if (r_secs != NULL)  *r_secs = 0;
   --rce;  if (a_age == NULL)  return rce;
   strncpy (x_age, a_age, LEN_SHORT);
   l = strlen (x_age);
   --rce;  if (l  < 2)         return rce;
   --rce;  if (l  > 3)         return rce;
   x_unit = x_age [l - 1];
   --rce;  switch (x_unit) {
   case  's' : x_multi = 1;                         break;
   case  'm' : x_multi = 60;                        break;
   case  'h' : x_multi = 60 * 60;                   break;
   case  'd' : x_multi = 60 * 60 * 24;              break;
   case  'o' : x_multi = 60 * 60 * 24 * 30;         break;
   case  'y' : x_multi = 60 * 60 * 24 * 365;        break;
   case  'c' : x_multi = 60 * 60 * 24 * 365 * 100;  break;
   default   : return rce;
   }
   x_age [l - 1] = '\0';
   x_num = atoi (x_age);
   --rce;  if (x_num == 0 && strcmp (x_age, "0") != 0)  return rce;
   x_num *= x_multi;
   if (r_secs != NULL)  *r_secs = x_num;
   return 0;
}

char
yunit_wave              (char a_act, FILE *f, char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_desc [LEN_LONG], char a_terse [LEN_LABEL], char a_wave, char a_stage, char a_nunit, char a_nscrp, short a_ncond, short a_nstep, char a_expe [LEN_SHORT], char a_result, short a_npass, short a_nfail, short a_nbadd, short a_nvoid, short a_actual)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   long        x_now       =    0;
   tTIME      *x_broke     = NULL;
   char        t           [LEN_TITLE] = "";
   int         x_expect    =    0;
   /*---(handle begin)-------------------*/
   if (a_act == 'b') {
      strncpy (S_proj , a_proj , LEN_LABEL);
      strncpy (S_unit , a_unit , LEN_TITLE);
      S_scrp  = a_scrp;
      strncpy (S_desc , a_desc , LEN_LONG);
      strncpy (S_terse, a_terse, LEN_LABEL);
      S_wave  = a_wave;
      S_stage = a_stage;
      strncpy (S_expe , a_expe , LEN_SHORT);
      S_saved = 'y';
      return 0;
   }
   --rce;  if (strchr ("ae", a_act) != NULL && S_saved != 'y') {
      return rce;
   }
   /*---(already open)-------------------*/
   --rce;  if (f == NULL) {
      return rce;
   }
   x_now   = time (NULL);
   x_broke = localtime (&x_now);
   /*> fprintf (f, "%p %10ld\n", f, x_now);                                           <*/
   strftime (t, LEN_TITLE, "%y.%m.%d.%H.%M.%S.%u.%W.%j", x_broke);
   /*> fprintf (f, "%p %-26.26s %10ld\n", f, t, x_now);                               <*/
   /*---(write)--------------------------*/
   rc = yunit_unage (a_expe, &x_expect);
   if (a_scrp == 1 && a_act != 'a') {
      fprintf (f, "## ouroboros-aperantos (tail-eater) master unit testing sequencer\n");
      fprintf (f, "## single unit test wave file\n");
      fprintf (f, "##--  timestamp-----------------  epoch-----  project-------------  unit--------------------------  sc  description-----------------------------------------------------------  terse---------------  w  s  nun  nsc  nco  nst  est  exp  R  pas  fai  bad  voi  act \n");
   }
   fprintf (f, "WAVE  %-26.26s  %10ld  %-20.20s  %-30.30s  %2d  %-70.70s  %-20.20s  %c  %c  %3d  %3d  %3d  %3d  %3.3s  %3d  %c  %3d  %3d  %3d  %3d  %3d \n",
         t, x_now, a_proj, a_unit, a_scrp, a_desc, a_terse, a_wave, a_stage, a_nunit, a_nscrp, a_ncond, a_nstep, a_expe, x_expect, a_result, a_npass, a_nfail, a_nbadd, a_nvoid, a_actual);
   fflush  (f);
   S_saved = '-';
   /*---(complete)-----------------------*/
   return 0;
}

char
yUNIT_wave_beg          (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_desc [LEN_LONG], char a_terse [LEN_LABEL], char a_wave, char a_stage, char a_expe [LEN_SHORT])
{
   return yunit_wave ('b', NULL, a_proj, a_unit, a_scrp, a_desc, a_terse, a_wave, a_stage, 0, 0, 0, 0, a_expe, '-', 0, 0, 0, 0, 0);
}

char
yUNIT_wave_end          (void *f, char a_nunit, char a_nscrp, short a_ncond, short a_nstep)
{
   return yunit_wave ('e', f, S_proj, S_unit, S_scrp, S_desc, S_terse, S_wave, S_stage, a_nunit, a_nscrp, a_ncond, a_nstep, S_expe, '-', 0, 0, 0, 0, 0);
}

char
yUNIT_wave_act          (void *f, char a_nunit, char a_nscrp, short a_ncond, short a_nstep, char a_result, short a_npass, short a_nfail, short a_nbadd, short a_nvoid, short a_actual)
{
   return yunit_wave ('a', f, S_proj, S_unit, S_scrp, S_desc, S_terse, S_wave, S_stage, a_nunit, a_nscrp, a_ncond, a_nstep, S_expe, a_result, a_npass, a_nfail, a_nbadd, a_nvoid, a_actual);
}
