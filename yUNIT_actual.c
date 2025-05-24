#include "yUNIT.h"
#include "yUNIT_priv.h"



/*---(prog level -- tbd)--------*/
static int     s_prog_scrp = 0;
static int     s_prog_cond = 0;
static int     s_prog_test = 0;
static int     s_prog_pass = 0;
static int     s_prog_fail = 0;
static int     s_prog_badd = 0;
static int     s_prog_void = 0;
/*---(unit level)---------------*/
static int     s_unit_scrp = 0;
static int     s_unit_cond = 0;
static int     s_unit_test = 0;
static int     s_unit_pass = 0;
static int     s_unit_fail = 0;
static int     s_unit_badd = 0;
static int     s_unit_void = 0;
/*---(script level)-------------*/
static int     s_scrp_cond = 0;
static int     s_scrp_test = 0;
static int     s_scrp_pass = 0;
static int     s_scrp_fail = 0;
static int     s_scrp_badd = 0;
static int     s_scrp_void = 0;
/*---(condition-level)----------*/
static int     s_cond_test = 0;
static int     s_cond_pass = 0;
static int     s_cond_fail = 0;
static int     s_cond_badd = 0;
static int     s_cond_void = 0;
/*---(step_level)---------------*/
static  char   s_resu      = YUNIT_FAIL;
static  int    s_rc        =  -1;
/*---(temporary)----------------*/
static char s_actuals  [LEN_HUND]  = "";
/*---(done)---------------------*/

/*---(prog level -- tbd)--------*/
#define      PROG_SCRP      s_prog_scrp
#define      PROG_COND      s_prog_cond
#define      PROG_TEST      s_prog_test
#define      PROG_PASS      s_prog_pass
#define      PROG_FAIL      s_prog_fail
#define      PROG_BADD      s_prog_badd
#define      PROG_VOID      s_prog_void
/*---(unit level)---------------*/
#define      UNIT_SCRP      s_unit_scrp
#define      UNIT_COND      s_unit_cond
#define      UNIT_TEST      s_unit_test
#define      UNIT_PASS      s_unit_pass
#define      UNIT_FAIL      s_unit_fail
#define      UNIT_BADD      s_unit_badd
#define      UNIT_VOID      s_unit_void
/*---(script level)-------------*/
#define      SCRP_COND      s_scrp_cond
#define      SCRP_TEST      s_scrp_test
#define      SCRP_PASS      s_scrp_pass
#define      SCRP_FAIL      s_scrp_fail
#define      SCRP_BADD      s_scrp_badd
#define      SCRP_VOID      s_scrp_void
/*---(condition-level)----------*/
#define      COND_TEST      s_cond_test
#define      COND_PASS      s_cond_pass
#define      COND_FAIL      s_cond_fail
#define      COND_BADD      s_cond_badd
#define      COND_VOID      s_cond_void
/*---(step-level)---------------*/
#define      STEP_RESU      s_resu
#define      STEP_RC        s_rc
/*---(done)---------------------*/



/*====================------------------------------------====================*/
/*===----                        basic statistics                      ----===*/
/*====================------------------------------------====================*/
static void      o___STATS_____________o (void) {;}

char
yunit_actual_clear      (char a_type)
{
   /*---(levels)-------------------------*/
   switch (a_type) {
   case TYPE_UNIT :
      UNIT_SCRP = UNIT_COND = 0;
      UNIT_TEST = UNIT_PASS = UNIT_FAIL = UNIT_BADD = UNIT_VOID = 0;
      break;
   case TYPE_SCRP :
      SCRP_COND = 0;
      SCRP_TEST = SCRP_PASS = SCRP_FAIL = SCRP_BADD = SCRP_VOID = 0;
      break;
   case TYPE_COND :
      COND_TEST = COND_PASS = COND_FAIL = COND_BADD = COND_VOID = 0;
      break;
   }
   /*---(details)------------------------*/
   STEP_RESU = YUNIT_FAIL;
   STEP_RC   = -1;
   /*---(complete)-----------------------*/
   return 0;
}

char
yunit_actual_init       (void)
{
   yunit_actual_clear (TYPE_COND);
   yunit_actual_clear (TYPE_SCRP);
   yunit_actual_clear (TYPE_UNIT);
   return 0;
}

char
yunit_actual_accum      (char a_type, char a_resu, int a_rc)
{
   switch (a_type) {
   case TYPE_UNIT :
      /*---(check unit)------------------*/
      yunit_actual_clear (TYPE_COND);
      yunit_actual_clear (TYPE_SCRP);
      yunit_actual_clear (TYPE_UNIT);
      break;
   case TYPE_SCRP :
      /*---(check script)----------------*/
      UNIT_SCRP++;
      yunit_actual_clear (TYPE_COND);
      yunit_actual_clear (TYPE_SCRP);
      break;
   case TYPE_COND : case TYPE_CCND : case TYPE_DOND : case TYPE_SOND : case TYPE_GOND :
      /*---(check condition)-------------*/
      UNIT_COND++; SCRP_COND++;
      yunit_actual_clear (TYPE_COND);
      break;
   case TYPE_LOCAL  : case TYPE_CODE   : case TYPE_LOAD   : case TYPE_MODE   :
   case TYPE_FILE   : case TYPE_APPEND : case TYPE_SYSTEM : case TYPE_STEP   :
      ++COND_TEST;  ++SCRP_TEST;  ++UNIT_TEST;
      /*---(check forced)----------------*/
      if (a_type = TYPE_STEP && YUNIT_FORCED == 'y') {
         if (a_resu == YUNIT_SUCC)   a_resu = YUNIT_FFAIL;
         if (a_resu == YUNIT_FAIL)   a_resu = YUNIT_FSUCC;
      }
      /*---(handle step)-----------------*/
      switch (a_resu) {
      case YUNIT_SUCC  :  ++COND_PASS;  ++SCRP_PASS;  ++UNIT_PASS;  break;
      case YUNIT_FAIL  :  ++COND_FAIL;  ++SCRP_FAIL;  ++UNIT_FAIL;  break;
      case YUNIT_FSUCC :  ++COND_PASS;  ++SCRP_PASS;  ++UNIT_PASS;  break;
      case YUNIT_FFAIL :  ++COND_FAIL;  ++SCRP_FAIL;  ++UNIT_FAIL;  break;
      case YUNIT_VOID  :  ++COND_VOID;  ++SCRP_VOID;  ++UNIT_VOID;  break;
      default          :  ++COND_BADD;  ++SCRP_BADD;  ++UNIT_BADD;  break;
      }
      STEP_RESU = a_resu;
      STEP_RC   = a_rc;
      break;
      /*---(done)------------------------*/
   case TYPE_DISP   :
      ++COND_TEST;  ++SCRP_TEST;  ++UNIT_TEST;
      break;
   }
   return 0;
}

char
yunit_actual_last       (char a_type, char *r_resu, int *r_rc)
{
   char        x_resu      = YUNIT_VOID;
   int         x_rc        =    0;
   switch (a_type) {
   case TYPE_TINU  :
      if      (UNIT_TEST == 0)  x_resu = YUNIT_VOID;
      else if (UNIT_FAIL >  0)  x_resu = YUNIT_FAIL;
      else if (UNIT_BADD >  0)  x_resu = YUNIT_WARN;
      else                      x_resu = YUNIT_SUCC;
      break;
   case TYPE_PRCS  :
      if      (SCRP_TEST == 0)  x_resu = YUNIT_VOID;
      else if (SCRP_FAIL  > 0)  x_resu = YUNIT_FAIL;
      else if (SCRP_BADD  > 0)  x_resu = YUNIT_WARN;
      else                      x_resu = YUNIT_SUCC;
      break;
   case TYPE_DNOC  :
      if      (COND_TEST == 0)  x_resu = YUNIT_VOID;
      else if (COND_FAIL >  0)  x_resu = YUNIT_FAIL;
      else if (COND_BADD >  0)  x_resu = YUNIT_WARN;
      else                      x_resu = YUNIT_SUCC;
      break;
   case TYPE_LOCAL  : case TYPE_CODE   : case TYPE_LOAD   : case TYPE_MODE   :
   case TYPE_FILE   : case TYPE_APPEND : case TYPE_SYSTEM : case TYPE_STEP   :
      x_resu = STEP_RESU;
      x_rc   = STEP_RC;
      break;
   case TYPE_DISP   :
      break;
   }
   if (r_resu != NULL)  *r_resu = x_resu;
   if (r_rc   != NULL)  *r_rc   = x_rc;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          reporting                           ----===*/
/*====================------------------------------------====================*/
static void      o___REPORTING_________o (void) {;}

char*
yunit_actual_footer     (char a_type, char *r_unused)
{
   if (r_unused != NULL)  *r_unused = '-';
   switch (a_type) {
   case TYPE_TINU : /* full unit, normal run */
      sprintf (s_actuals, "TINU  scrp=%-4d cond=%-5d test=%-5d [ pass=%-5d fail=%-5d badd=%-5d void=%-5d ]",
            UNIT_SCRP, UNIT_COND, UNIT_TEST, UNIT_PASS, UNIT_FAIL, UNIT_BADD, UNIT_VOID);
      if (r_unused != NULL && UNIT_TEST == 0)  *r_unused = 'y';
      break;
   case TYPE_DINU : /* full unit, listing    */
      sprintf (s_actuals, "DINU  scrp=%-4d cond=%-5d test=%-5d [ ------------------------------------------- ]",
            UNIT_SCRP, UNIT_COND, UNIT_TEST);
      if (r_unused != NULL && UNIT_TEST == 0)  *r_unused = 'y';
      break;
   case TYPE_PRCS : /* script, normal run */
      sprintf (s_actuals, "PRCS  ------- cond=%-5d test=%-5d [ pass=%-5d fail=%-5d badd=%-5d void=%-5d ]",
            SCRP_COND, SCRP_TEST, SCRP_PASS, SCRP_FAIL, SCRP_BADD, SCRP_VOID);
      if (r_unused != NULL && SCRP_TEST == 0)  *r_unused = 'y';
      break;
   case TYPE_DRCS : /* script, listing    */
      sprintf (s_actuals, "DRCS  ------- cond=%-5d test=%-5d [ ------------------------------------------- ]",
            SCRP_COND, SCRP_TEST);
      if (r_unused != NULL && SCRP_TEST == 0)  *r_unused = 'y';
      break;
   case TYPE_DNOC :
      sprintf (s_actuals, "DNOC  -------------- test=%-5d [ pass=%-5d fail=%-5d badd=%-5d void=%-5d ]",
            COND_TEST, COND_PASS, COND_FAIL, COND_BADD, COND_VOID);
      if (r_unused != NULL && COND_TEST == 0)  *r_unused = 'y';
      break;
   case TYPE_DNOD :
      sprintf (s_actuals, "DNOD  -------------- test=%-5d [ ------------------------------------------- ]",
            COND_TEST);
      if (r_unused != NULL && COND_TEST == 0)  *r_unused = 'y';
      break;
   }
   return s_actuals;
}

char
yunit_actual_pcrs       (void *f, long a_dur)
{
   char        x_result    =  '-';
   if      (SCRP_FAIL > 0)  x_result = 'F';
   else if (SCRP_BADD > 0)  x_result = '?';
   else                     x_result = 'Ï';
   yUNIT_wave_act (f, 0, 1, SCRP_COND, SCRP_TEST, x_result,  SCRP_PASS, SCRP_FAIL, SCRP_BADD, SCRP_VOID, a_dur);
   return 0;
}

int
yunit_actual_wrap       (char a_level)
{
   int         i           =    0;
   char        x_stat      [LEN_SHORT] = "";
   if (a_level >= 3) {
      yUNIT_out = fopen (myUNIT.name, "r+");
      snprintf (x_stat, LEN_SHORT, "%4d" , UNIT_SCRP);
      for (i = 0; i < LEN_SHORT; ++i)  if (x_stat [i] == ' ')  x_stat [i] = '·';
      fseek (yUNIT_out, (86 * 1) + 71, SEEK_SET);
      fprintf (yUNIT_out, "%4s", x_stat);
      snprintf (x_stat, LEN_SHORT, "%4d" , UNIT_COND);
      for (i = 0; i < LEN_SHORT; ++i)  if (x_stat [i] == ' ')  x_stat [i] = '·';
      fseek (yUNIT_out, (86 * 2) + 71, SEEK_SET);
      fprintf (yUNIT_out, "%4s", x_stat);
      snprintf (x_stat, LEN_SHORT, "%4d" , UNIT_TEST);
      for (i = 0; i < LEN_SHORT; ++i)  if (x_stat [i] == ' ')  x_stat [i] = '·';
      fseek (yUNIT_out, (86 * 3) + 71, SEEK_SET);
      fprintf (yUNIT_out, "%4s", x_stat);
      fflush (yUNIT_out);
      yunit_close ();
   }
   return UNIT_FAIL + UNIT_BADD;
}



/*====================------------------------------------====================*/
/*===----                     unit testing support                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST__________o (void) {;}

char
yunit_force_unit        (int a_scrp, int a_cond, int a_test, int a_pass, int a_fail, int a_badd, int a_void)
{
   UNIT_SCRP = a_scrp;
   UNIT_COND = a_cond;
   UNIT_TEST = a_test;
   UNIT_PASS = a_pass;
   UNIT_FAIL = a_fail;
   UNIT_BADD = a_badd;
   UNIT_VOID = a_void;
   return 0;
}

char
yunit_force_scrp        (int a_cond, int a_test, int a_pass, int a_fail, int a_badd, int a_void)
{
   UNIT_SCRP = 1;
   UNIT_COND = SCRP_COND = a_cond;
   UNIT_TEST = SCRP_TEST = a_test;
   UNIT_PASS = SCRP_PASS = a_pass;
   UNIT_FAIL = SCRP_FAIL = a_fail;
   UNIT_BADD = SCRP_BADD = a_badd;
   UNIT_VOID = SCRP_VOID = a_void;
   return 0;
}

char
yunit_force_cond        (int a_test, int a_pass, int a_fail, int a_badd, int a_void)
{
   UNIT_SCRP = 1;
   UNIT_COND = SCRP_COND = 1;
   UNIT_TEST = SCRP_TEST = COND_TEST = a_test;
   UNIT_PASS = SCRP_PASS = COND_PASS = a_pass;
   UNIT_FAIL = SCRP_FAIL = COND_FAIL = a_fail;
   UNIT_BADD = SCRP_BADD = COND_BADD = a_badd;
   UNIT_VOID = SCRP_VOID = COND_VOID = a_void;
   return 0;
}

char
yunit_force_resu        (char a_resu, int a_rc)
{
   if (a_resu == YUNIT_FFAIL || a_resu == YUNIT_FSUCC)   YUNIT_FORCED = 'y';
   else                                                  YUNIT_FORCED = '-';
   STEP_RESU   = a_resu;
   STEP_RC     = a_rc;
   return 0;

}

