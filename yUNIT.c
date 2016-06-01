/*===[[ START ]]==============================================================*/
#include <stdio.h>        /* printf(), snprintf()                             */
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>       /* malloc(), free()                                 */

#include "yUNIT.h"
#include "yVAR.h"



/*===[[ CONSTANTS ]]==========================================================*/
#define  DISP_SUMM     if (o->is_noisy == 1)
#define  DISP_SCRP     if (o->is_noisy >= 2)
#define  DISP_COND     if (o->is_noisy >= 3)
#define  DISP_STEP     if (o->is_noisy >= 4)
#define  DISP_FULL     if (o->is_noisy >= 5)
#define  DISP_SECT     if (o->is_noisy == 4)

#define  YUNIT_SUCC    0
#define  YUNIT_FAIL    1
#define  YUNIT_WARN    2



/*===[[ TEST STRUCTURE ]]=====================================================*/
typedef struct cUNIT tUNIT;
struct cUNIT {
   /*---(identification)-----------*/
   char      its_name[100];
   /*---(working vars)-------------*/
   int       its_line;
   int       its_seqn;
   char      its_refn[100];
   char      its_desc[100];
   char      its_meth[100];
   char      its_args[200];
   char      its_test[100];
   char      its_expe[500];
   char      its_fixd[500];
   char      its_actu[500];
   int       its_resu;
   int       its_code;
   char      its_comm[100];
   /*---(counters)-----------------*/
   int       its_cond_test;
   int       its_cond_pass;
   int       its_cond_fail;
   int       its_cond_badd;
   int       its_cond_void;
   int       its_scrp_test;
   int       its_scrp_pass;
   int       its_scrp_fail;
   int       its_scrp_badd;
   int       its_scrp_void;
   int       its_unit_test;
   int       its_unit_pass;
   int       its_unit_fail;
   int       its_unit_badd;
   int       its_unit_void;
   /*---(flags)--------------------*/
   int       is_forced_fail;
   int       is_noisy;
   char      is_eterm;
   void     *is_leak_begin;
   void     *is_leak_end;
};


/*===[[ TESTING ]]============================================================*/
void     *my_unit = NULL;

FILE     *yUNIT_stdin;



/*====================------------------------------------====================*/
/*===----                           test-level                         ----===*/
/*====================------------------------------------====================*/
static void      o___TEST____________________o (void) {;}

void*      /*----: create a new unit test ------------------------------------*/
yUNIT_unit         (cchar *a_name, cchar a_noisy, cchar a_eterm)
{  /*---(allocate test)--------------------*/
   tUNIT     *o         = malloc(sizeof(tUNIT));
   /*---(setup defaults)-------------------*/
   yUNIT_noisy  (o, a_noisy);
   /*> yUNIT_eterm  (o, 'y');                                                         <*/
   /*---(print header)---------------------*/
   DISP_SCRP {
      printf("yUNIT - heatherly unit testing framework ------------------------------------ (start)\n");
   }
   DISP_STEP {
      printf ("\n");
      printf ("  focus         : (PS) Programming Support\n");
      printf ("  niche         : (ut) unit testing\n");
      printf ("  application   : yUNIT       (automated unit testing)\n");
      printf ("  purpose       : provide a consistent, fullsome, automated unit testing framework\n");
      printf ("\n");
      printf ("  base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)\n");
      printf ("  lang_name     : gnu/ansi-c  (wicked, limitless, universal, and everlasting)\n");
      printf ("  dependencies  : yVAR\n");
      printf ("  size_goal     : tiny        (approximately 500 slocL)\n");
      printf ("\n");
      printf ("  author        : the_heatherlys\n");
      printf ("  created       : 2008-08 from previous c/c++ and bash versions\n");
      printf ("  priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)\n");
      printf ("  end_goals     : loosely coupled, strict interface, maintainable, portable\n");
      printf ("\n");
      printf ("-------------------------------------------------------------------------------------\n");
      printf ("\n");
      printf ("starting up...\n");
      printf ("   create a new unit test\n");
   }
   if (o == NULL) {
      DISP_SUMM printf("   NEW TEST COULD NOT BE ALLOCATED (FATAL)\n");
      return NULL;
   }
   strncpy(o->its_name, a_name, 100);
   DISP_STEP   printf("   assign to program <<%s>>\n", o->its_name);
   /*---(reset summary counters)-------*/
   DISP_STEP   printf("   initiaize summary counters\n");
   o->its_unit_test  = 0;
   o->its_unit_pass  = 0;
   o->its_unit_fail  = 0;
   o->its_unit_badd  = 0;
   o->its_unit_void  = 0;
   yUNIT_eterm (o, a_eterm);
   yUNIT_mode  (o, 0, 1, "normal");
   /*---(leak testing)---------------------*/
   o->is_leak_begin  = malloc(sizeof(int));
   free(o->is_leak_begin);
   /*---(complete)-------------------------*/
   DISP_STEP   printf("\n");
   return o;
}

char       /*----: change the color level)------------------------------------*/
yUNIT_eterm        (cvoid *a_unit, cchar a_eterm)
{  /*---(allocate test)--------------------*/
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(setup verbosity)------------------*/
   if (a_eterm == 'y')  {
      DISP_COND   printf ("   assign color mode to ETERM\n");
      o->is_eterm = 'y';
   } else {
      DISP_COND   printf ("   assign color mode to CONSOLE\n");
      o->is_eterm = '-';
   }
   return o->is_eterm;
}

char       /*----: change the verbosity level --------------------------------*/
yUNIT_noisy        (cvoid *a_unit, cchar a_noisy)
{  /*---(allocate test)--------------------*/
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(setup verbosity)------------------*/
   if (a_noisy >= 0 && a_noisy <= 5) o->is_noisy = a_noisy;
   else                              o->is_noisy = 5;
   return o->is_noisy;
}

char       /*----: close a unit test -----------------------------------------*/
yUNIT_tinu         (void  *a_unit)
{  /*---(variables)------------------------*/
   tUNIT    *o       = (tUNIT *) a_unit;
   char    x_on      [20] = "";
   char    x_off     [20] = "";
   int     x_failed  = o->its_unit_fail;
   /*---(print message)---------------*/
   if (o->is_eterm == 'y') {
      if        (o->its_unit_fail > 0) {
         strcpy(x_on, "\e[41m");
      } else if (o->its_unit_badd > 0) {
         strcpy(x_on, "\e[43m");
      } else {
         strcpy(x_on, "\e[42m");
      }
      strcpy(x_off, "\e[0m");
   }
   DISP_SCRP   {
      printf("\n%sTINU   step=%-4d", x_on, o->its_unit_test);
      printf("  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s\n",
            o->its_unit_pass, o->its_unit_fail,
            o->its_unit_badd, o->its_unit_void,
            x_off);
      printf("\n");
   }
   DISP_STEP   {
      printf("shutting down...\n");
      printf("   clear unit test for <<%s>>\n", o->its_name);
      printf("   free the unit test\n");
      printf("\n");
   }
   DISP_SCRP   {
      printf("yUNIT - heatherly unit testing framework --------------------------------- (complete)\n");
   }
   DISP_SUMM {
      if (o->its_unit_fail > 0) printf("FAILED  :: %d of %d steps failed\n",
            o->its_unit_fail, o->its_unit_test);
      else                      printf("success :: %d of %d steps passed\n",
            o->its_unit_pass, o->its_unit_test);
   }
   /*---(leak testing)---------------------*/
   o->is_leak_end    = malloc(sizeof(int));
   free(o->is_leak_end);
   if (o->is_leak_begin != o->is_leak_end) {
      DISP_COND   printf("\nMEMORY LEAK    :: start=%p, end=%p, so %d bytes lost\n", o->is_leak_begin, o->is_leak_end, (int) (o->is_leak_end - o->is_leak_begin)); 
   } else {
      DISP_COND   printf("\nno memory leak :: start=%p, end=%p\n", o->is_leak_begin, o->is_leak_end); 
   }
   /*---(complete)--------------------------*/
   free(o);
   if (x_failed > 100) x_failed = 100;
   /*> printf ("done, done\n");                                                       <*/
   return -x_failed;
}



/*====================------------------------------------====================*/
/*===----                         script-level                         ----===*/
/*====================------------------------------------====================*/
static void      o___SCRIPT__________________o (void) {;}

void    /*  PURPOSE :: break out a section                                    */
yUNIT_sect    (
      void     *a_unit,           /* unit test object                         */
      char     *a_desc)           /* short description                        */
{
   tUNIT      *o           = (tUNIT *) a_unit;
   int         len         = strlen (a_desc);
   int         x_pre       = (65 - len) / 2;
   int         x_suf       = 65 - x_pre - len;
   char        x_header    [300] = "";
   /*---(print title)------------------*/
   if (len < 65)   sprintf(x_header, "%*.*s%s%*.*s", x_pre, x_pre, "", a_desc, x_suf, x_suf, "");
   else            sprintf(x_header, "%65.65s", a_desc);
   DISP_COND   printf("\n\n\n");
   DISP_SCRP   printf("\n");
   /*> DISP_ALL    printf("=====---------------------------------------------------------------------------=====\n");   <*/
   /*> DISP_ALL    printf("===-------                             SECTION                             -------===\n");   <*/
   DISP_SCRP   printf("===-------%s-------===\n", x_header);
   /*> DISP_ALL    printf("=====---------------------------------------------------------------------------=====\n");   <*/
   return;
}

void    /*  PURPOSE :: record the start of a new script                       */
yUNIT_scrp (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_focu,           /* focus function                           */
      char     *a_desc)           /* short description                        */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(reset summary counters)-------*/
   o->its_scrp_test = 0;
   o->its_scrp_pass = 0;
   o->its_scrp_fail = 0;
   o->its_scrp_badd = 0;
   o->its_scrp_void = 0;
   /*---(print title)------------------*/
   char  x_header[300] = "";
   /*> snprintf(x_header, 300, "SCRP [%02d] %s :: %s", a_seqn, a_focu, a_desc);       <*/
   snprintf(x_header, 300, "SCRP [%02d] %s", a_seqn, a_desc);
   strncat(x_header, " ", 80);
   strncat(x_header, "================================================", 80);
   strncat(x_header, "================================================", 80);
   DISP_COND   printf("\n\n");
   DISP_STEP   printf("\n===[[ NEW SCRIPT ]]==================================================================");
   DISP_SCRP   printf("\n%-78.78s [%04d]\n", x_header, a_line);
   snprintf(x_header, 300, "  focus : %s", a_focu);
   DISP_COND   printf("%-85.85s\n", x_header);
   return;
}

void
yUNIT_prcs (
      void     *a_unit)           /* unit test object                         */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   char   x_on [20] = "";
   char    x_off     [20] = "";
   if (o->is_eterm == 'y') {
      if        (o->its_scrp_fail > 0) {
         strcpy(x_on , "\e[41m");
      } else if (o->its_scrp_badd > 0) {
         strcpy(x_on , "\e[43m");
      } else {
         strcpy(x_on , "\e[42m");
      }
      strcpy(x_off, "\e[0m");
   }
   /*---(accumulate in counters)-----------*/
   o->its_unit_test += o->its_scrp_test;
   o->its_unit_pass += o->its_scrp_pass;
   o->its_unit_fail += o->its_scrp_fail;
   o->its_unit_badd += o->its_scrp_badd;
   o->its_unit_void += o->its_scrp_void;
   /*---(print message)-------------------*/
   DISP_COND   printf("\n");
   DISP_SCRP   {
      printf("  %sPRCS   step=%-4d", x_on , o->its_scrp_test);
      printf("  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s\n",
            o->its_scrp_pass, o->its_scrp_fail, o->its_scrp_badd, o->its_scrp_void, x_off);
   }
   DISP_COND   printf("\n");
   return;
}



/*====================------------------------------------====================*/
/*===----                       condition-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___CONDITION_______________o (void) {;}

void
yUNIT_cond (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc)           /* short description                        */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(save key data)----------------*/
   o->its_line = a_line;
   strncpy(o->its_desc, a_desc, 100);
   /*---(reset summary counters)-------*/
   o->its_cond_test = 0;
   o->its_cond_pass = 0;
   o->its_cond_fail = 0;
   o->its_cond_badd = 0;
   o->its_cond_void = 0;
   /*---(print message)----------------*/
   DISP_COND   {
      char  x_header[300] = "";
      strncat(x_header, o->its_desc, 80);
      strncat(x_header, " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --", 80);
      strncat(x_header, " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --", 80);
      printf("\n  COND [%03d] %65.65s [%04d]\n", a_seqn, x_header, a_line);
   }
   /*---(remove old stdin)-------------*/
   system("/bin/rm -f yUNIT.stdin");
   yUNIT_stdin = NULL;
   /*---(complete)---------------------*/
   return;
}

void
yUNIT_dnoc (
      void     *a_unit)           /* unit test object                         */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   char   x_on       [20] = "";
   char   x_off      [20] = "";
   if (o->is_eterm == 'y') {
      if        (o->its_cond_fail > 0) {
         strcpy(x_on , "\e[41m");
      } else if (o->its_cond_badd > 0) {
         strcpy(x_on , "\e[43m");
      } else {
         strcpy(x_on , "\e[42m");
      }
      strcpy(x_off, "\e[0m");
   }
   /*---(accumulate in counters)-----------*/
   o->its_scrp_test += o->its_cond_test;
   o->its_scrp_pass += o->its_cond_pass;
   o->its_scrp_fail += o->its_cond_fail;
   o->its_scrp_badd += o->its_cond_badd;
   o->its_scrp_void += o->its_cond_void;
   /*---(print message)----------------*/
   DISP_STEP   printf("\n");
   DISP_COND   {
      printf("      %sDNOC   step=%-4d", x_on , o->its_cond_test);
      printf("  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s\n",
            o->its_cond_pass, o->its_cond_fail, o->its_cond_badd, o->its_cond_void, x_off);
   }
   DISP_FULL   printf("\n");
   /*---(close stdin and remove)-------*/
   if (yUNIT_stdin != NULL) fclose(yUNIT_stdin);
   system("/bin/rm -f yUNIT.stdin");
   /*---(complete)---------------------*/
   return;
}

void    /*  PURPOSE :: group conditions                                       */
yUNIT_group   (
      void     *a_unit,           /* unit test object                         */
      char     *a_desc)           /* short description                        */
{
   tUNIT      *o           = (tUNIT *) a_unit;
   int         len         = strlen (a_desc);
   int         x_pre       = (63 - len) / 2;
   int         x_suf       = 63 - x_pre - len;
   char        x_header    [300] = "";
   /*---(print title)------------------*/
   if (len < 65)   sprintf(x_header, "%*.*s%s%*.*s", x_pre, x_pre, "", a_desc, x_suf, x_suf, "");
   else            sprintf(x_header, "%65.65s", a_desc);
   DISP_COND   printf("\n");
   /*> DISP_ALL    printf("=====---------------------------------------------------------------------------=====\n");   <*/
   /*> DISP_ALL    printf("===-------                             SECTION                             -------===\n");   <*/
   DISP_COND   printf("  ===-------%s-------===\n", x_header);
   /*> DISP_ALL    printf("=====---------------------------------------------------------------------------=====\n");   <*/
   DISP_COND   printf("\n");
   return;
}



/*====================------------------------------------====================*/
/*===----                       specialty-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;}

void               /*  rerturn = (none)                                       */
yUNIT_mode (       /*  PURPOSE = ENABLE FORCED FAILURES                       */
      void     *a_unit,           /*  unit test object                        */
      int       a_line,           /*  reference number to script file line    */
      int       a_seqn,           /*  sequence number                         */
      char     *a_desc)           /*  short description                       */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   int seq1 = (a_seqn / 26);
   int seq2 = (a_seqn % 26) + 1;
   if (seq1 == 0) {
      seq1  = seq2 - 1;
      seq2  = ' ' - 96;
   }
   char   x_on  [20] = "";
   char   x_off [20] = "";
   if (o->is_eterm == 'y') {
      strcpy(x_on , "\e[46m");
      strcpy(x_off, "\e[0m");
   }
   if (strcmp(a_desc, "FORCED_FAIL") == 0) {
      o->is_forced_fail = 1;
      DISP_STEP
         printf("\n  %s%c%c) MODE  %s : ENABLE FORCED FAILURE (pass=fail, fail=pass) .  .  .  .  .  .   [%04i]\n",
               x_on, seq1 + 96, seq2 + 96, x_off, a_line);
   } else {
      o->is_forced_fail = 0;
      DISP_STEP
         printf("\n  %s%c%c) MODE  %s : normal (a pass is a pass ;)   .  .  .  .  .  .  .  .  .  .  .   [%04i]\n",
               x_on, seq1 + 96, seq2 + 96, x_off, a_line);
   }
   /*---(complete)---------------------*/
   return;
}


void               /*  rerturn = (none)                                       */
yUNIT_code (       /*  PURPOSE = describe manual code lines                   */
      void     *a_unit,           /*  unit test object                        */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_code)           /* actual code line                         */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare sequence)---------------*/
   int seq1 = (a_seqn / 26);
   int seq2 = (a_seqn % 26) + 1;
   if (seq1 == 0) {
      seq1  = seq2 - 1;
      seq2  = ' ' - 96;
   }
   /*---(prepare color)------------------*/
   char   x_on  [20] = "";
   char   x_off [20] = "";
   if (o->is_eterm == 'y') {
      strcpy (x_on , "\e[46m");
      strcpy (x_off, "\e[0m");
   }
   /*---(dispaly)------------------------*/
   DISP_STEP {
      char  x_header[300] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      printf("\n  %s%c%c) CODE  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      printf(" %63.63s [%04d]\n", x_header, a_line);
      printf("      code   : %-70.70s\n", a_code);
   }
   /*---(complete)---------------------*/
   return;
}

void
yUNIT_load (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_recd)           /* record to load                           */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   int seq1 = (a_seqn / 26);
   int seq2 = (a_seqn % 26) + 1;
   if (seq1 == 0) {
      seq1  = seq2 - 1;
      seq2  = ' ' - 96;
   }
   /*---(prepare color)------------------*/
   char   x_on  [20] = "";
   char   x_off [20] = "";
   if (o->is_eterm == 'y') {
      strcpy (x_on , "\e[46m");
      strcpy (x_off, "\e[0m");
   }
   /*---(display)------------------------*/
   /*> printf ("yUNIT_load 0.0 : %p\n", yUNIT_stdin);                                 <*/
   DISP_STEP {
      char  x_header[300] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      printf("\n  %s%c%c) CODE  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      printf(" %63.63s [%04d]\n", x_header, a_line);
      printf("      load   : %-.65s\n", a_recd);
   }
   /*---(close it in case)-------------*/
   /*> printf ("yUNIT_load 1.0 : %p\n", yUNIT_stdin);                                 <*/
   if (yUNIT_stdin != NULL) fclose(yUNIT_stdin);
   /*> printf ("yUNIT_load 2.0 : %p\n", yUNIT_stdin);                                 <*/
   /*---(write new data)---------------*/
   yUNIT_stdin = fopen(STDIN, "a");
   /*> printf ("yUNIT_load 3.0 : %p\n", yUNIT_stdin);                                 <*/
   fprintf (yUNIT_stdin, "%s\n", a_recd);
   fclose  (yUNIT_stdin);
   /*> printf ("yUNIT_load 4.0 : %p\n", yUNIT_stdin);                                 <*/
   /*---(reopen for next steps)--------*/
   yUNIT_stdin = fopen(STDIN, "r");
   /*> printf ("yUNIT_load 5.0 : %p\n", yUNIT_stdin);                                 <*/
   /*---(complete)---------------------*/
   return;
}

void
yUNIT_sys    (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_cmd )           /* record to execute                        */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   int seq1 = (a_seqn / 26);
   int seq2 = (a_seqn % 26) + 1;
   if (seq1 == 0) {
      seq1  = seq2 - 1;
      seq2  = ' ' - 96;
   }
   /*---(prepare color)------------------*/
   char   x_on  [20] = "";
   char   x_off [20] = "";
   if (o->is_eterm == 'y') {
      strcpy (x_on , "\e[46m");
      strcpy (x_off, "\e[0m");
   }
   /*---(display)------------------------*/
   /*> printf ("yUNIT_load 0.0 : %p\n", yUNIT_stdin);                                 <*/
   DISP_STEP {
      char  x_header[300] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      printf("\n  %s%c%c) CODE  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      printf(" %63.63s [%04d]\n", x_header, a_line);
      printf("      sys    : %-.65s\n", a_cmd);
   }
   /*---(run system command)-----------*/
   char     x_sys [1000];
   sprintf (x_sys, "%s > /tmp/yUNIT_sys_verb.tmp", a_cmd);
   /*> printf ("SYS COMMAND : %s\n", x_sys);                                          <*/
   system (x_sys);
   /*---(open file)--------------------*/
   FILE  *f;
   f = fopen ("/tmp/yUNIT_sys_verb.tmp", "r");
   if (f == NULL) return -1;
   /*---(read one line)----------------*/
   char        x_text      [1000] = "";
   int         x_len       = 0;
   fgets (x_text, 1000, f);
   x_len = strlen (x_text);
   x_text [--x_len] = '\0';
   strcpy (yUNIT_systext, x_text);
   /*---(close)------------------------*/
   fclose (f);
   /*---(complete)---------------------*/
   return;
}



/*====================------------------------------------====================*/
/*===----                          step-level                          ----===*/
/*====================------------------------------------====================*/
static void      o___STEP____________________o (void) {;}

void
yUNIT_void (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args,           /* method's arguments                       */
      char     *a_test)           /* test to conduct                          */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu = 0;
   o->its_code = 0;
   /*---(record the key data)--------------------*/
   strncpy(o->its_test, a_test, 100);
   strncpy(o->its_expe, "void", 500);
   strncpy(o->its_fixd, ""    , 500);
   strncpy(o->its_actu, "void", 100);
   yUNIT__recd(o, a_line, a_seqn, a_desc, a_meth, a_args);
   /*---(complete)-------------------------------*/
   return;
}

void
yUNIT_int     (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args,           /* method's arguments                       */
      char     *a_test,           /* test to conduct                          */
      char     *a_expe,           /* expected result                          */
      long      a_actu)           /* actual result                            */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu =  1;
   o->its_code = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "i_") != NULL) {
      o->its_code = yVAR_integer(a_test, atol(a_expe), a_actu);
      if (o->its_code > 0) o->its_resu = 0;
   } else {
      o->its_resu = 1;
   }
   /*---(save return)----------------------------*/
   yUNIT_i_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy(o->its_test, a_test, 100);
   strncpy(o->its_expe, a_expe, 500);
   strncpy(o->its_fixd, ""    , 500);
   snprintf(o->its_actu, 500, "%ld", a_actu);
   yUNIT__recd(o, a_line, a_seqn, a_desc, a_meth, a_args);
   /*---(complete)-------------------------------*/
   return;
}

void
yUNIT_point   (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args,           /* method's arguments                       */
      char     *a_test,           /* test to conduct                          */
      void     *a_expe,           /* expected result                          */
      void     *a_actu)           /* actual result                            */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu   =  1;
   o->its_code   = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "p_") != NULL) {
      o->its_code = yVAR_pointer(a_test, a_expe, a_actu);
      if (o->its_code > 0) o->its_resu = 0;
   } else {
      o->its_resu = 1;
   }
   if (strcmp(a_test, "p_exists") == 0) a_expe = a_actu;
   /*---(save return)----------------------------*/
   yUNIT_p_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy(o->its_test, a_test, 100);
   snprintf(o->its_expe, 500, "%p",  a_expe);
   if (strcmp(a_test, "p_exists") == 0) strncpy(o->its_expe, "---any---", 100);
   strncpy(o->its_fixd, ""    , 500);
   snprintf(o->its_actu, 500, "%p",  a_actu);
   if (a_actu != NULL) o->is_leak_end = a_actu;
   yUNIT__recd(o, a_line, a_seqn, a_desc, a_meth, a_args);
   /*---(complete)-------------------------------*/
   return;
}

void
yUNIT_real (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args,           /* method's arguments                       */
      char     *a_test,           /* test to conduct                          */
      char     *a_expe,           /* expected result                          */
      double    a_actu)           /* actual result                            */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu = 1;
   o->its_code = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "r_") != NULL) {
      o->its_code = yVAR_real(a_test, atof(a_expe), a_actu);
      if (o->its_code > 0) o->its_resu = 0;
   } else {
      o->its_resu = 1;
   }
   /*---(save return)----------------------------*/
   yUNIT_r_rc = a_actu;

   /*---(record the key data)--------------------*/
   strncpy(o->its_test, a_test, 100);
   strncpy(o->its_expe, yVAR_expect(), 500);
   strncpy(o->its_fixd, ""    , 500);
   strncpy(o->its_actu, yVAR_actual(), 500);
   yUNIT__recd(o, a_line, a_seqn, a_desc, a_meth, a_args);
   /*---(complete)-------------------------------*/
   return;
}

void
yUNIT_string (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args,           /* method's arguments                       */
      char     *a_test,           /* test to conduct                          */
      char     *a_expe,           /* expected result                          */
      char     *a_actu)           /* actual result                            */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu = 1;
   o->its_code = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "s_") != NULL) {
      o->its_code = yVAR_string(a_test, a_expe, a_actu);
      if (o->its_code > 0) o->its_resu = 0;
   } else {
      o->its_resu = 1;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy(o->its_test, a_test, 100);
   strncpy(o->its_expe, a_expe, 500);
   strncpy(o->its_fixd, "",     500);
   strncpy(o->its_actu, a_actu, 500);
   yUNIT__recd(o, a_line, a_seqn, a_desc, a_meth, a_args);
   /*---(complete)-------------------------------*/
   return;
}

void
yUNIT_round   (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args,           /* method's arguments                       */
      char     *a_test,           /* test to conduct                          */
      char     *a_expe,           /* expected result                          */
      char     *a_actu)           /* actual result                            */
{
   /*---(locals)---------------------------------*/
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu  =  YUNIT_FAIL;
   o->its_code  =  -666;               /* indicates unhandled test            */
   strncpy(o->its_fixd, "",     500);
   /*---(do the comparisons)---------------------*/
   if (strncmp(a_test, "u_round/", 8) == 0) {
      o->its_code = yVAR_round(a_test, a_expe, a_actu);
      if      (o->its_code >=    0) o->its_resu = YUNIT_SUCC;
      else if (o->its_code <= -600) o->its_resu = YUNIT_WARN;
      else                          o->its_resu = YUNIT_FAIL;
   } else {
      o->its_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy(o->its_test, a_test, 100);
   strncpy(o->its_expe, a_expe, 500);
   if (o->its_code >  0) strncpy(o->its_fixd, yVAR_mod(), 500);
   strncpy(o->its_actu, a_actu, 500);
   yUNIT__recd(o, a_line, a_seqn, a_desc, a_meth, a_args);
   /*---(complete)-------------------------------*/
   return;
}

void
yUNIT_ustr    (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args,           /* method's arguments                       */
      char     *a_test,           /* test to conduct                          */
      char     *a_expe,           /* expected result                          */
      char     *a_actu)           /* actual result                            */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   char    x_modd[500]  = "";
   char    x_actu[500]  = "";
   /*---(prepare)--------------------------------*/
   o->its_resu = 1;
   o->its_code = -666;
   strncpy(x_modd, a_expe, 499);
   strncpy(x_actu, a_actu, 499);
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "u_") != NULL) {
      o->its_code = yVAR_ustring(a_test, x_modd, x_actu);
      if (o->its_code > 0) o->its_resu = 0;
   } else {
      o->its_resu = 1;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy(o->its_test, a_test, 100);
   strncpy(o->its_expe, a_expe, 500);
   strncpy(o->its_fixd, yVAR_mod(), 500);
   strncpy(o->its_actu, x_actu, 500);
   yUNIT__recd(o, a_line, a_seqn, a_desc, a_meth, a_args);
   /*---(complete)-------------------------------*/
   return;
}

void               /*  rerturn = (none)                                       */
yUNIT_badd (       /*  PURPOSE = describe manual code lines                   */
      void     *a_unit,           /*  unit test object                        */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_test)           /* test requested                           */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   int seq1 = (a_seqn / 26);
   int seq2 = (a_seqn % 26) + 1;
   if (seq1 == 0) {
      seq1  = seq2 - 1;
      seq2  = ' ' - 96;
   }
   /*---(prepare color)------------------*/
   char   x_on  [20] = "";
   char   x_off [20] = "";
   if (o->is_eterm == 'y') {
      strcpy (x_on , "\e[46m");
      strcpy (x_off, "\e[0m");
   }
   ++o->its_cond_test;
   ++o->its_cond_badd;
   DISP_STEP {
      char  x_header[300] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      printf("\n  %s%c%c) BADD  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      printf(" %63.63s [%04d]\n", x_header, a_line);
      printf("      test   : %s (not a recognized test)\n", a_test);
   }
   /*---(complete)---------------------*/
   return;
}

void               /*  rerturn = (none)                                       */
yUNIT_removed (    /*  PURPOSE = notify of old/obsolete test types            */
      void     *a_unit,           /*  unit test object                        */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args,           /* method's arguments                       */
      char     *a_test,           /* test requested                           */
      char     *a_expe)           /* expected result                          */
{  /*---(locals)-----------+-----------+-*/
   tUNIT      *o           = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu =  1;
   o->its_code = -666;
   /*---(record the key data)--------------------*/
   strncpy     (o->its_test, a_test, 100);
   strncpy     (o->its_expe, a_expe, 500);
   strncpy     (o->its_fixd, ""    , 500);
   strncpy     (o->its_actu, ""    , 500);
   yUNIT__recd (o, a_line, a_seqn, a_desc, a_meth, a_args);
   /*---(complete)---------------------*/
   return;
}

void               /*  rerturn = (none)                                       */
yUNIT_unknown (    /*  PURPOSE = notify of confusing lines in script file     */
      void     *a_unit,           /*  unit test object                        */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args,           /* method's arguments                       */
      char     *a_test,           /* test requested                           */
      char     *a_expe)           /* expected result                          */
{  /*---(locals)-----------+-----------+-*/
   tUNIT      *o           = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu =  1;
   o->its_code = -666;
   /*---(record the key data)--------------------*/
   strncpy     (o->its_test, a_test, 100);
   strncpy     (o->its_expe, a_expe, 500);
   strncpy     (o->its_fixd, ""    , 500);
   strncpy     (o->its_actu, ""    , 500);
   yUNIT__recd (o, a_line, a_seqn, a_desc, a_meth, a_args);
   /*---(complete)---------------------*/
   return;
}


/*====================------------------------------------====================*/
/*===----                            display                           ----===*/
/*====================------------------------------------====================*/
static void      o___DISPLAY_________________o (void) {;}

void
yUNIT__recd (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* method                                   */
      char     *a_args)           /* method's arguments                       */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(capture key data)-----------------------*/
   ++o->its_cond_test;
   o->its_line = a_line;
   o->its_seqn = a_seqn;
   strncpy(o->its_desc, a_desc, 100);
   strncpy(o->its_meth, a_meth, 100);
   strncpy(o->its_args, a_args, 200);
   long int _gcpu = 0;
   /*---(mark result)----------------------------*/
   char  x_resu[6]   = "FAIL";
   char  x_on1  [20] = "";
   char  x_on2  [20] = "";
   char  x_off  [20] = "";
   if (o->its_resu == 0) {
      strncpy(x_resu, "PASS", 5);
      if (!o->is_forced_fail) {
         ++o->its_cond_pass;
         if (strcmp(o->its_test, "intg_FAIL") == 0) {
            strcpy(x_on1  , "\e[41m");
            strcpy(x_on2  , "\e[42m");
            strcpy(x_off  , "\e[0m");
         } else {
            strcpy(x_on1  , "\e[42m");
            strcpy(x_on2  , x_on1  );
            strcpy(x_off  , "\e[0m");
         }
      } else {
         ++o->its_cond_fail;
         strcpy(x_on1  , "\e[42m");
         strcpy(x_on2  , "\e[41m");
         strcpy(x_off  , "\e[0m");
         strncpy(x_resu, "OUCH", 5);
      }
   } else if (o->its_resu == 1) {
      strncpy(x_resu, "FAIL", 5);
      if (!o->is_forced_fail) {
         ++o->its_cond_fail;
         strcpy(x_on1  , "\e[41m");
         strcpy(x_on2  , x_on1  );
         strcpy(x_off  , "\e[0m");
      } else {
         ++o->its_cond_pass;
         strcpy(x_on1  , "\e[41m");
         strcpy(x_on2  , "\e[42m");
         strcpy(x_off  , "\e[0m");
         strncpy(x_resu, "FOR_F", 5);
      }
   } else {
      strncpy(x_resu, "WARN", 5);
      ++o->its_cond_badd;
      strcpy(x_on1  , "\e[43m");
      strcpy(x_on2  , x_on1  );
      strcpy(x_off  , "\e[0m");
   }
   if (o->is_eterm == '-') {
      strcpy (x_on1  , "");
      strcpy (x_on2  , "");
      strcpy(x_off  , "");
   }
   /*---(print message)----------------*/
   DISP_STEP {
      char  x_header[300] = "";
      strncat(x_header, o->its_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      int seq1 = (o->its_seqn / 26);
      int seq2 = (o->its_seqn % 26) + 1;
      if (seq1 == 0) {
         seq1  = seq2 - 1;
         seq2  = ' ' - 96;
      }
      DISP_FULL   printf("\n");
      printf("  %s%c%c)", x_on1  , seq1 + 96, seq2 + 96);
      printf(" %s%-5.5s %s :", x_on2  , x_resu, x_off);
      printf(" %63.63s [%04d]\n", x_header, a_line);
   }
   DISP_FULL   {
      if (strlen(o->its_args) <= 50) printf("      method : %-s (%.50s)\n", o->its_meth, o->its_args);
      else                           printf("      method : %-s (%.49s>>\n", o->its_meth, o->its_args);
      printf("      test   : %-15s(@ %ld msecs with rc = %d) %s\n", o->its_test, _gcpu, o->its_code, (o->its_code <= -600) ? "----- BAD TEST -----" : "");
      if (strcmp(o->its_test, "void") != 0) {
         printf("      expect : %-s>>\n", o->its_expe);
         if (strlen(o->its_fixd) > 0) printf("      altered: %-s>>\n", o->its_fixd);
         printf("      actual : %-s>>\n", o->its_actu);
      } else {
         printf("      expect : void\n");
         printf("      actual : void\n");
      }
   }
   /*---(complete)-------------------------------*/
   return;
}

/*===[[ END ]]================================================================*/
