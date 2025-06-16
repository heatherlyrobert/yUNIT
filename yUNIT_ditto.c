#include "yUNIT.h"
#include "yUNIT_priv.h"



typedef struct cDITTOS tDITTOS;
static struct cDITTOS {
   int         c_step;                      /* all step count                                        */
   int         c_real;                      /* steps returning non-void                              */
   int         c_void;                      /* steps returning void                                  */
   int         c_skips;                     /* skipped steps                                         */
};
static tDITTOS  s_dittos [LEN_TERSE];


char
yunit_ditto_purge       (void)
{
   int         i           =    0;
   for (i = 0; i < LEN_TERSE; ++i) {
      s_dittos [i].c_step  = 0;
      s_dittos [i].c_real  = 0;
      s_dittos [i].c_void  = 0;
      s_dittos [i].c_skips = 0;
   }
   return 0;
}

char
yunit_ditto_step        (char a_usage, char a_type, char a_dittoing, char a_skip)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =    0;
   /*---(quick-out)----------------------*/
   if (strchr ("xv", a_type) == NULL)   return 0;
   /*---(defense)------------------------*/
   if (a_usage != YUNIT_CONVERT)  return 0;
   if (a_dittoing < '0')          return 0;
   if (a_dittoing > '9')          return 0;
   /*---(prepare)------------------------*/
   n = a_dittoing - '0';
   /*---(count)--------------------------*/
   switch (a_type) {
   case YUNIT_IS_EXEC : /* exec     */  ++(s_dittos [n].c_real);  break;
   case YUNIT_IS_VOID : /* void     */  ++(s_dittos [n].c_void);  break;
   }
   /*---(add total)----------------------*/
   ++(s_dittos [n].c_step);
   /*---(record skip)--------------------*/
   if (a_skip == 'y')  ++s_dittos [n].c_skips;
   /*---(complete)-----------------------*/
   return 1;
}

char
yunit_ditto_apply       (char a_usage, char a_type, char a_dtarget)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =    0;
   int         d           =    0;
   /*---(quick-out)----------------------*/
   if (a_usage != YUNIT_CONVERT)  return 0;
   /*---(defense)------------------------*/
   if (a_type  != YUNIT_IS_DITT)  return 0;
   if (a_dtarget < '0')  return 0;
   if (a_dtarget > '9')  return 0;
   /*---(prepare)------------------------*/
   n = a_dtarget - '0';
   /*---(statistics)---------------------*/
   d = s_dittos [n].c_step;
   SCRP.c_dstep += d;  UNIT.c_dstep += d;  FULL.c_dstep += d;  
   d = s_dittos [n].c_real;
   SCRP.c_dreal += d;  UNIT.c_dreal += d;  FULL.c_dreal += d;  
   d = s_dittos [n].c_void;
   SCRP.c_dvoid += d;  UNIT.c_dvoid += d;  FULL.c_dvoid += d;  
   d = s_dittos [n].c_skips;
   SCRP.c_dskip += d;  UNIT.c_dskip += d;  FULL.c_dskip += d;  
   /*---(complete)-----------------------*/
   return 1;
}

char*
yunit_ditto_show        (char a_ditto)
{
   char        n           =    0;
   if (a_ditto < '0')             return "(bad-ref)";
   if (a_ditto > '9')             return "(bad-ref)";
   n = a_ditto - '0';
   sprintf (s_print, "%d)  %3ds  %3dx  %3dv  %3dk", n, s_dittos [n].c_step, s_dittos [n].c_real, s_dittos [n].c_void, s_dittos [n].c_skips);
   return s_print;
}
