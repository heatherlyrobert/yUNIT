#include "yUNIT.h"
#include "yUNIT_priv.h"


char     s_sect      [LEN_LINE]   = "";


/*===[[ TESTING ]]============================================================*/
void     *my_unit = NULL;

FILE     *yUNIT_stdin;
FILE     *yUNIT_out;



/*====================------------------------------------====================*/
/*===----                           test-level                         ----===*/
/*====================------------------------------------====================*/
static void      o___TEST____________________o (void) {;}

void*      /*----: create a new unit test ------------------------------------*/
yUNIT_unit         (cchar *a_name, cchar a_noisy, cchar a_eterm)
{  /*---(allocate test)--------------------*/
   tUNIT     *o         = malloc(sizeof(tUNIT));
   char       t         [LEN_ARGS];
   /*---(setup defaults)-------------------*/
   yUNIT_noisy  (o, a_noisy);
   /*> yUNIT_eterm  (o, 'y');                                                         <*/
   /*---(open output)----------------------*/
   if (a_name != NULL)   snprintf (t, LEN_ARGS, "%s.urun", a_name);
   else                  snprintf (t, LEN_ARGS, "unittest.urun");
   yUNIT_out = fopen (t, "w");
   if (yUNIT_out == NULL)   return -1;
   /*---(print header)---------------------*/
   DISP_SCRP {
      fprintf (yUNIT_out, "yUNIT - heatherly unit testing framework ------------------------------------ (start)\n");
   }
   DISP_STEP {
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "  focus         : (PS) Programming Support\n");
      fprintf (yUNIT_out, "  niche         : (ut) unit testing\n");
      fprintf (yUNIT_out, "  application   : yUNIT       (automated unit testing)\n");
      fprintf (yUNIT_out, "  purpose       : provide a consistent, fullsome, automated unit testing framework\n");
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "  base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)\n");
      fprintf (yUNIT_out, "  lang_name     : gnu/ansi-c  (wicked, limitless, universal, and everlasting)\n");
      fprintf (yUNIT_out, "  dependencies  : yVAR\n");
      fprintf (yUNIT_out, "  size_goal     : tiny        (approximately 500 slocL)\n");
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "  author        : the_heatherlys\n");
      fprintf (yUNIT_out, "  created       : 2008-08 from previous c/c++ and bash versions\n");
      fprintf (yUNIT_out, "  priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)\n");
      fprintf (yUNIT_out, "  end_goals     : loosely coupled, strict interface, maintainable, portable\n");
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "-------------------------------------------------------------------------------------\n");
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "starting up...\n");
      fprintf (yUNIT_out, "   create a new unit test\n");
   }
   if (o == NULL) {
      DISP_SUMM fprintf(yUNIT_out, "   NEW TEST COULD NOT BE ALLOCATED (FATAL)\n");
      return NULL;
   }
   strncpy(o->its_name, a_name, LEN_NORM);
   DISP_STEP   fprintf(yUNIT_out, "   assign to program <<%s>>\n", o->its_name);
   /*---(reset summary counters)-------*/
   DISP_STEP   fprintf(yUNIT_out, "   initiaize summary counters\n");
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
   DISP_STEP   fprintf(yUNIT_out, "\n");
   return o;
}

char       /*----: change the color level)------------------------------------*/
yUNIT_eterm        (cvoid *a_unit, cchar a_eterm)
{  /*---(allocate test)--------------------*/
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(setup verbosity)------------------*/
   if (a_eterm == 'y')  {
      DISP_COND   fprintf (yUNIT_out, "   assign color mode to ETERM\n");
      o->is_eterm = 'y';
   } else {
      DISP_COND   fprintf (yUNIT_out, "   assign color mode to CONSOLE\n");
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
      fprintf(yUNIT_out, "\n%sTINU   step=%-4d", x_on, o->its_unit_test);
      fprintf(yUNIT_out, "  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s\n",
            o->its_unit_pass, o->its_unit_fail,
            o->its_unit_badd, o->its_unit_void,
            x_off);
      fprintf(yUNIT_out, "\n");
   }
   DISP_STEP   {
      fprintf(yUNIT_out, "shutting down...\n");
      fprintf(yUNIT_out, "   clear unit test for <<%s>>\n", o->its_name);
      fprintf(yUNIT_out, "   free the unit test\n");
      fprintf(yUNIT_out, "\n");
   }
   DISP_SCRP   {
      fprintf(yUNIT_out, "yUNIT - heatherly unit testing framework --------------------------------- (complete)\n");
   }
   DISP_SUMM {
      if (o->its_unit_fail > 0) fprintf(yUNIT_out, "FAILED  :: %d of %d steps failed\n",
            o->its_unit_fail, o->its_unit_test);
      else                      fprintf(yUNIT_out, "success :: %d of %d steps passed\n",
            o->its_unit_pass, o->its_unit_test);
   }
   /*---(leak testing)---------------------*/
   o->is_leak_end    = malloc(sizeof(int));
   free(o->is_leak_end);
   if (o->is_leak_begin != o->is_leak_end) {
      DISP_COND   fprintf(yUNIT_out, "\nMEMORY LEAK    :: start=%p, end=%p, so %d bytes lost\n", o->is_leak_begin, o->is_leak_end, (int) (o->is_leak_end - o->is_leak_begin)); 
   } else {
      DISP_COND   fprintf(yUNIT_out, "\nno memory leak :: start=%p, end=%p\n", o->is_leak_begin, o->is_leak_end); 
   }
   /*---(complete)--------------------------*/
   free(o);
   if (x_failed > 100) x_failed = 100;
   fclose (yUNIT_out);
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
{  /*---(design notes)--------------------------------------------------------*/
   /* a SECT title is only printed when the next SCRP is found so footers     */
   /* will be correctly situated.                                             */
   /*---(locals)-----------+-----------+-*/
   tUNIT      *o           = (tUNIT *) a_unit;
   int         x_len       = 0;
   int         x_pre       = 0;
   int         x_suf       = 0;
   char       *x_dashes    = "-----------------------------------------------------------";
   /*---(print title)--------------------*/
   if (strcmp (a_desc, "SCRP") == 0) {
      /*---(print)----------*/
      if (strcmp (s_sect, "") != 0) {
         DISP_COND   fprintf(yUNIT_out, "\n\n\n");
         DISP_SCRP   fprintf(yUNIT_out, "\n");
         DISP_COND   fprintf(yUNIT_out, "=========================------------------------------------========================\n");
         DISP_SCRP   fprintf(yUNIT_out, "===-------%s-------===\n", s_sect);
         DISP_COND   fprintf(yUNIT_out, "=========================------------------------------------========================\n");
      }
      /*---(clear)----------*/
      strcpy (s_sect, "");
   }
   /*---(save title)---------------------*/
   else {
      /*---(format)---------*/
      if (a_desc != NULL) {
         x_len       = strlen (a_desc);
         x_pre       = (65 - x_len) / 2;
         x_suf       = (65 - x_pre) - x_len;
         if (x_len < 65)   sprintf(s_sect, "%*.*s[[ %s ]]%*.*s", x_pre - 3, x_pre - 3, x_dashes, a_desc, x_suf - 3, x_suf - 3, x_dashes);
         else              sprintf(s_sect, "%65.65s", a_desc);
      }
   }
   /*---(complete)-----------------------*/
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
   tUNIT      *o           = (tUNIT *) a_unit;
   char        x_header    [LEN_HEAD] = "";
   /*---(show sect)--------------------*/
   yUNIT_sect   (a_unit, "SCRP");
   /*---(reset summary counters)-------*/
   o->its_scrp_test = 0;
   o->its_scrp_pass = 0;
   o->its_scrp_fail = 0;
   o->its_scrp_badd = 0;
   o->its_scrp_void = 0;
   /*---(print title)------------------*/
   /*> snprintf(x_header, LEN_HEAD, "SCRP [%02d] %s :: %s", a_seqn, a_focu, a_desc);       <*/
   snprintf(x_header, LEN_HEAD, "SCRP [%02d] %s", a_seqn, a_desc);
   strncat(x_header, " ", 80);
   strncat(x_header, "================================================", 80);
   strncat(x_header, "================================================", 80);
   DISP_COND   fprintf(yUNIT_out, "\n\n");
   DISP_STEP   fprintf(yUNIT_out, "\n===[[ NEW SCRIPT ]]==================================================================");
   DISP_SCRP   fprintf(yUNIT_out, "\n%-77.77s [%05d]\n", x_header, a_line);
   snprintf(x_header, LEN_HEAD, "  focus : %s", a_focu);
   DISP_COND   fprintf(yUNIT_out, "%-85.85s\n", x_header);
   /*---(complete)---------------------*/
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
   DISP_COND   fprintf(yUNIT_out, "\n");
   DISP_SCRP   {
      fprintf(yUNIT_out, "  %sPRCS   step=%-4d", x_on , o->its_scrp_test);
      fprintf(yUNIT_out, "  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s\n",
            o->its_scrp_pass, o->its_scrp_fail, o->its_scrp_badd, o->its_scrp_void, x_off);
   }
   DISP_COND   fprintf(yUNIT_out, "\n");
   /*---(complete)---------------------*/
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
   strncpy(o->its_desc, a_desc, LEN_NORM);
   /*---(reset summary counters)-------*/
   o->its_cond_test = 0;
   o->its_cond_pass = 0;
   o->its_cond_fail = 0;
   o->its_cond_badd = 0;
   o->its_cond_void = 0;
   /*---(print message)----------------*/
   DISP_COND   {
      char  x_header[LEN_HEAD] = "";
      strncat(x_header, o->its_desc, 80);
      strncat(x_header, " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --", 80);
      strncat(x_header, " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --", 80);
      fprintf(yUNIT_out, "\n  COND [%03d] %64.64s [%05d]\n", a_seqn, x_header, a_line);
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
   DISP_STEP   fprintf(yUNIT_out, "\n");
   DISP_COND   {
      fprintf(yUNIT_out, "      %sDNOC   step=%-4d", x_on , o->its_cond_test);
      fprintf(yUNIT_out, "  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s\n",
            o->its_cond_pass, o->its_cond_fail, o->its_cond_badd, o->its_cond_void, x_off);
   }
   DISP_FULL   fprintf(yUNIT_out, "\n");
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
   char        x_header    [LEN_HEAD] = "";
   /*---(print title)------------------*/
   if (len < 65)   sprintf(x_header, "%*.*s%s%*.*s", x_pre, x_pre, "", a_desc, x_suf, x_suf, "");
   else            sprintf(x_header, "%65.65s", a_desc);
   DISP_COND   fprintf(yUNIT_out, "\n");
   /*> DISP_ALL    fprintf(yUNIT_out, "=====---------------------------------------------------------------------------=====\n");   <*/
   /*> DISP_ALL    fprintf(yUNIT_out, "===-------                             SECTION                             -------===\n");   <*/
   DISP_COND   fprintf(yUNIT_out, "  ===-------%s-------===\n", x_header);
   /*> DISP_ALL    fprintf(yUNIT_out, "=====---------------------------------------------------------------------------=====\n");   <*/
   /*> DISP_COND   fprintf(yUNIT_out, "\n");                                                      <*/
   return;
}

void    /*  PURPOSE :: display a shared condition message                     */
yUNIT_share_head        (void *a_unit, char *a_desc)
{
   tUNIT      *o           = (tUNIT *) a_unit;
   int         len         = strlen (a_desc);
   int         x_pre       = (63 - len) / 2;
   int         x_suf       = 63 - x_pre - len;
   char        x_header    [LEN_HEAD] = "";
   char        x_on        [20] = "";
   char        x_off       [20] = "";
   /*---(print title)------------------*/
   if (len < 65)   sprintf(x_header, "%*.*s%s%*.*s", x_pre, x_pre, "", a_desc, x_suf, x_suf, "");
   else            sprintf(x_header, "%65.65s", a_desc);
   DISP_COND   fprintf(yUNIT_out, "\n");
   if (o->is_eterm == 'y') {
      strcpy(x_on , "\e[46m");
      strcpy(x_off, "\e[0m");
   }
   DISP_COND   fprintf(yUNIT_out, "%s  SHARE ===----%s----===%s\n", x_on, x_header, x_off);
   return;
}

void    /*  PURPOSE :: display a shared condition message                     */
yUNIT_share_foot        (void *a_unit, char a_share)
{
   tUNIT      *o           = (tUNIT *) a_unit;
   /*> char        x_header    [LEN_HEAD] = "123456789 123456789 123456789 123456789 123456789 123456789 12345";   <*/
   char        x_header    [LEN_HEAD] = "-----------------------------------------------------------------";
   char        x_on        [20] = "";
   char        x_off       [20] = "";
   /*---(print title)------------------*/
   DISP_COND   fprintf(yUNIT_out, "\n");
   if (o->is_eterm == 'y') {
      strcpy(x_on , "\e[46m");
      strcpy(x_off, "\e[0m");
   }
   DISP_COND   fprintf(yUNIT_out, "%s  ERAHS (%c) ===-%s-===%s\n", x_on, a_share, x_header, x_off);
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
         fprintf(yUNIT_out, "\n  %s%c%c) MODE  %s : ENABLE FORCED FAILURE (pass=fail, fail=pass) .  .  .  .  .  .  [%05i]\n",
               x_on, seq1 + 96, seq2 + 96, x_off, a_line);
   } else {
      o->is_forced_fail = 0;
      DISP_STEP
         fprintf(yUNIT_out, "\n  %s%c%c) MODE  %s : normal (a pass is a pass ;)   .  .  .  .  .  .  .  .  .  .  .  [%05i]\n",
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
      char  x_header[LEN_HEAD] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      fprintf(yUNIT_out, "\n  %s%c%c) CODE  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      fprintf(yUNIT_out, " %62.62s [%05d]\n", x_header, a_line);
      fprintf(yUNIT_out, "      code   : %-70.70s\n", a_code);
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
      char     *a_meth,           /* input method (stdin, ncurses, STDIN)     */
      char     *a_recd)           /* record to load                           */
{
   /*> printf ("recd :%s:\n", a_recd);                                                <*/
   int       x_flags = 0;         /* stdin file flags                         */
   int       i       = 0;
   int       x_ch    = 0;
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
   DISP_STEP {
      char  x_header[LEN_HEAD] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      fprintf(yUNIT_out, "\n  %s%c%c) CODE  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      fprintf(yUNIT_out, " %62.62s [%05d]\n", x_header, a_line);
      fprintf(yUNIT_out, "      load   : (%-10.10s) %-.55s\n", a_meth, a_recd);
   }
   /*---(normal stdin)-----------------*/
   if (strcmp (a_meth, "stdin") == 0) {
      /*---(clear existing)------------*/
      /*> x_flags     = fcntl  (stdin, F_GETFL, 0);                                   <* 
       *> fcntl (stdin, F_SETFL, x_flags | O_NONBLOCK);                               <* 
       *> printf ("clearing stdin...\n");                                             <* 
       *> while (getc (stdin) != -1);   /+ clear existing  +/                         <* 
       *> fcntl  (stdin, F_SETFL, x_flags);                                           <*/
      /*---(load new)------------------*/
      /*> printf ("loading stdin...\n");                                              <*/
      for (i = strlen (a_recd) - 1; i >= 0; --i) {
         ungetc (a_recd [i], stdin);
      }
   }
   /*---(ncurses input)----------------*/
   else if (strcmp (a_meth, "ncurses") == 0) {
      while (x_ch = getch ()) {
         /*> fprintf (yUNIT_out, "pulled %3d\n", x_ch);                                           <*/
         if (x_ch < 0)  break;
         /* clear existing  */
      }
      /*> fprintf (yUNIT_out, "placing <<%s>>\n", a_recd);                                        <*/
      if (strlen (a_recd) > 0) {
         for (i = strlen (a_recd) - 1; i >= 0; --i) {
            /*> fprintf (yUNIT_out, "ungetch %3d = %c\n", a_recd[i], a_recd[i]);                  <*/
            ungetch (a_recd [i]);
         }
      }
   }
   /*---(file input)-------------------*/
   else {
      /*---(close it in case)----------*/
      /*> fprintf (yUNIT_out, "yUNIT_load 1.0 : %p\n", yUNIT_stdin);                              <*/
      if (yUNIT_stdin != NULL) fclose(yUNIT_stdin);
      /*> fprintf (yUNIT_out, "yUNIT_load 2.0 : %p\n", yUNIT_stdin);                              <*/
      /*---(write new data)------------*/
      yUNIT_stdin = fopen(STDIN, "a");
      /*> fprintf (yUNIT_out, "yUNIT_load 3.0 : %p\n", yUNIT_stdin);                              <*/
      /*> fprintf (yUNIT_out, "yUNIT_load 3.5 : %s\n", a_recd);                                   <*/
      fprintf (yUNIT_stdin, "%s\n", a_recd);
      fclose  (yUNIT_stdin);
      /*> fprintf (yUNIT_out, "yUNIT_load 4.0 : %p\n", yUNIT_stdin);                              <*/
      /*---(reopen for next steps)-----*/
      yUNIT_stdin = fopen(STDIN, "r");
      /*> fprintf (yUNIT_out, "yUNIT_load 5.0 : %p\n", yUNIT_stdin);                              <*/
   }
   /*> fprintf (yUNIT_out, "done with load\n");                                                   <*/
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
   /*> fprintf (yUNIT_out, "yUNIT_load 0.0 : %p\n", yUNIT_stdin);                                 <*/
   DISP_STEP {
      char  x_header[LEN_HEAD] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      fprintf(yUNIT_out, "\n  %s%c%c) CODE  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      fprintf(yUNIT_out, " %62.62s [%05d]\n", x_header, a_line);
      fprintf(yUNIT_out, "      sys    : %-.65s\n", a_cmd);
   }
   /*---(run system command)-----------*/
   char     x_sys [LEN_RECD];
   sprintf (x_sys, "%s > /tmp/yUNIT_sys_verb.tmp", a_cmd);
   /*> fprintf (yUNIT_out, "SYS COMMAND : %s\n", x_sys);                                          <*/
   system (x_sys);
   /*---(open file)--------------------*/
   FILE  *f;
   f = fopen ("/tmp/yUNIT_sys_verb.tmp", "r");
   if (f == NULL) return -1;
   /*---(read one line)----------------*/
   char        x_text      [LEN_RECD] = "";
   int         x_len       = 0;
   fgets (x_text, LEN_RECD, f);
   x_len = strlen (x_text);
   x_text [--x_len] = '\0';
   strcpy (yUNIT_systext, x_text);
   /*---(close)------------------------*/
   fclose (f);
   /*---(complete)---------------------*/
   return;
}

char
yUNIT_user_del          (cchar *a_name)
{
   char        rce          =  -10;
   char        rc           =    0;
   char        t            [LEN_RECD ] = "";
   --rce;  if (a_name == NULL) return rce;
   snprintf (t, LEN_RECD, "userdel --remove %s >> /dev/null 2>&1", a_name);
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   return 0; 
}

char
yUNIT_user_add          (cchar *a_name, cchar *a_pass, cchar *a_shell)
{
   char        rce          =  -10;
   char        rc           =    0;
   char        t            [LEN_RECD  ] = "";
   char        s            [LEN_RECD  ] = "";
   --rce;  if (a_name == NULL) return rce;
   --rce;  if (a_pass == NULL) return rce;
   yUNIT_user_del (a_name);
   snprintf (t, LEN_RECD, "useradd --gid nobody --create-home --no-user-group %s", a_name);
   if (a_shell != NULL && strlen (a_shell) > 0) {
      snprintf (s, LEN_RECD, "  --shell \"%s\"", a_shell);
      strcat   (t, s);
   }
   strcat   (t, "  >> /dev/null 2>&1");
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   snprintf (t, LEN_RECD, "printf \"%s\n%s\n\" | passwd %s >> /dev/null 2>&1", a_pass, a_pass, a_name);
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   return 0; 
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
   o->its_resu  = YUNIT_SUCC;
   o->its_code  = 0;
   /*---(record the key data)--------------------*/
   strncpy  (o->its_test, a_test, LEN_NORM);
   strncpy  (o->its_expe, "void", LEN_LINE);
   strncpy  (o->its_fixd, ""    , LEN_LINE);
   strncpy  (o->its_actu, "void", LEN_LINE);
   yUNIT__recd (o, a_line, a_seqn, a_desc, a_meth, a_args);
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
      long long a_expe,           /* expected result                          */
      long long a_actu)           /* actual result                            */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu  =  YUNIT_FAIL;
   o->its_code  = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "i_") != NULL) {
      o->its_code = yVAR_integer(a_test, a_expe, a_actu);
      if (o->its_code > 0) o->its_resu = YUNIT_SUCC;
   } else {
      o->its_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_i_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy  (o->its_test, a_test, LEN_NORM);
   strncpy  (o->its_fixd, ""    , LEN_LINE);
   snprintf (o->its_expe, LEN_LINE, "%lld", a_expe);
   snprintf (o->its_actu, LEN_LINE, "%lld", a_actu);
   /*> printf ("%20lld == [%s]\n", a_expe, o->its_expe);                              <*/
   /*> printf ("%20lld == [%s]\n", a_actu, o->its_actu);                              <*/
   yUNIT__recd (o, a_line, a_seqn, a_desc, a_meth, a_args);
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
   o->its_resu   =  YUNIT_FAIL;
   o->its_code   = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "p_") != NULL) {
      o->its_code = yVAR_pointer (a_test, a_expe, a_actu);
      if (o->its_code > 0) o->its_resu = YUNIT_SUCC;
   } else {
      o->its_resu = YUNIT_WARN;
   }
   if (strcmp (a_test, "p_exists") == 0) a_expe = a_actu;
   /*---(save return)----------------------------*/
   yUNIT_p_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy   (o->its_test, a_test, LEN_NORM);
   snprintf  (o->its_expe, LEN_LINE, "%p",  a_expe);
   if (strcmp(a_test, "p_exists") == 0) strncpy(o->its_expe, "---any---", LEN_NORM);
   strncpy   (o->its_fixd, ""    , LEN_LINE);
   snprintf  (o->its_actu, LEN_LINE, "%p",  a_actu);
   if (a_actu != NULL) o->is_leak_end = a_actu;
   yUNIT__recd (o, a_line, a_seqn, a_desc, a_meth, a_args);
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
      double    a_expe,           /* expected result                          */
      double    a_actu)           /* actual result                            */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare)--------------------------------*/
   o->its_resu   =  YUNIT_FAIL;
   o->its_code   = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "r_") != NULL) {
      o->its_code = yVAR_real (a_test, a_expe, a_actu);
      if (o->its_code > 0) o->its_resu = YUNIT_SUCC;
   } else {
      o->its_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_r_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy  (o->its_test, a_test, LEN_NORM);
   snprintf (o->its_expe, LEN_LINE, "%lf", a_expe);
   strncpy  (o->its_fixd, ""    , LEN_LINE);
   snprintf (o->its_actu, LEN_LINE, "%lf", a_actu);
   yUNIT__recd (o, a_line, a_seqn, a_desc, a_meth, a_args);
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
   o->its_resu   =  YUNIT_FAIL;
   o->its_code   = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "s_") != NULL) {
      o->its_code = yVAR_string (a_test, a_expe, a_actu);
      if (o->its_code > 0) o->its_resu = YUNIT_SUCC;
   } else {
      o->its_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy (o->its_test, a_test, LEN_NORM);
   strncpy (o->its_expe, a_expe, LEN_LINE);
   strncpy (o->its_fixd, "",     LEN_LINE);
   strncpy (o->its_actu, a_actu, LEN_LINE);
   yUNIT__recd (o, a_line, a_seqn, a_desc, a_meth, a_args);
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
   strncpy (o->its_fixd, "",     LEN_LINE);
   /*---(do the comparisons)---------------------*/
   if (strncmp (a_test, "u_round/", 8) == 0) {
      o->its_code = yVAR_round (a_test, a_expe, a_actu);
      if      (o->its_code >=    0) o->its_resu = YUNIT_SUCC;
      else if (o->its_code <= -600) o->its_resu = YUNIT_WARN;
      else                          o->its_resu = YUNIT_FAIL;
   } else {
      o->its_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy  (o->its_test, a_test, LEN_NORM);
   strncpy  (o->its_expe, a_expe, LEN_LINE);
   if (o->its_code >  0) strncpy(o->its_fixd, yVAR_modded (), LEN_LINE);
   strncpy  (o->its_actu, a_actu, LEN_LINE);
   yUNIT__recd (o, a_line, a_seqn, a_desc, a_meth, a_args);
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
   char    x_modd[LEN_LINE]  = "";
   char    x_actu[LEN_LINE]  = "";
   /*---(prepare)--------------------------------*/
   o->its_resu   =  YUNIT_FAIL;
   o->its_code   = -666;
   strncpy(x_modd, a_expe, 499);
   strncpy(x_actu, a_actu, 499);
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "u_") != NULL) {
      o->its_code = yVAR_ustring (a_test, x_modd, x_actu);
      if (o->its_code > 0) o->its_resu = YUNIT_SUCC;
   } else {
      o->its_resu = YUNIT_FAIL;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy (o->its_test, a_test, LEN_NORM);
   strncpy (o->its_expe, a_expe, LEN_LINE);
   strncpy (o->its_fixd, yVAR_modded (), LEN_LINE);
   strncpy (o->its_actu, x_actu, LEN_LINE);
   yUNIT__recd (o, a_line, a_seqn, a_desc, a_meth, a_args);
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
      char  x_header[LEN_HEAD] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      fprintf(yUNIT_out, "\n  %s%c%c) BADD  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      fprintf(yUNIT_out, " %62.62s [%05d]\n", x_header, a_line);
      fprintf(yUNIT_out, "      test   : %s (not a recognized test)\n", a_test);
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
   o->its_resu   =  YUNIT_FAIL;
   o->its_code   = -666;
   /*---(record the key data)--------------------*/
   strncpy     (o->its_test, a_test, LEN_NORM);
   strncpy     (o->its_expe, a_expe, LEN_LINE);
   strncpy     (o->its_fixd, ""    , LEN_LINE);
   strncpy     (o->its_actu, ""    , LEN_LINE);
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
   o->its_resu   =  YUNIT_FAIL;
   o->its_code   = -666;
   /*---(record the key data)--------------------*/
   strncpy     (o->its_test, a_test, LEN_NORM);
   strncpy     (o->its_expe, a_expe, LEN_LINE);
   strncpy     (o->its_fixd, ""    , LEN_LINE);
   strncpy     (o->its_actu, ""    , LEN_LINE);
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
   strncpy(o->its_desc, a_desc, LEN_NORM);
   strncpy(o->its_meth, a_meth, LEN_NORM);
   strncpy(o->its_args, a_args, LEN_ARGS);
   long int _gcpu = 0;
   /*---(mark result)----------------------------*/
   char  x_resu[6]   = "FAIL";
   char  x_on1  [20] = "";
   char  x_on2  [20] = "";
   char  x_off  [20] = "";
   if (o->its_resu == YUNIT_SUCC) {
      strncpy (x_resu, "PASS", 5);
      if (!o->is_forced_fail) {
         ++o->its_cond_pass;
         if (strcmp (o->its_test, "intg_FAIL") == 0) {
            strcpy (x_on1  , "\e[41m");
            strcpy (x_on2  , "\e[42m");
            strcpy (x_off  , "\e[0m");
         } else {
            strcpy (x_on1  , "\e[42m");
            strcpy (x_on2  , x_on1  );
            strcpy (x_off  , "\e[0m");
         }
      } else {
         ++o->its_cond_fail;
         strcpy(x_on1  , "\e[42m");
         strcpy(x_on2  , "\e[41m");
         strcpy(x_off  , "\e[0m");
         strncpy(x_resu, "OUCH", 5);
      }
   } else if (o->its_resu == YUNIT_FAIL) {
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
      char  x_header[LEN_HEAD] = "";
      strncat(x_header, o->its_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      int seq1 = (o->its_seqn / 26);
      int seq2 = (o->its_seqn % 26) + 1;
      if (seq1 == 0) {
         seq1  = seq2 - 1;
         seq2  = ' ' - 96;
      }
      DISP_FULL   fprintf(yUNIT_out, "\n");
      fprintf(yUNIT_out, "  %s%c%c)", x_on1  , seq1 + 96, seq2 + 96);
      fprintf(yUNIT_out, " %s%-5.5s %s :", x_on2  , x_resu, x_off);
      fprintf(yUNIT_out, " %62.62s [%05d]\n", x_header, a_line);
   }
   DISP_FULL   {
      if (strlen(o->its_args) <= 50) fprintf(yUNIT_out, "      method : %-s (%.50s)\n", o->its_meth, o->its_args);
      else                           fprintf(yUNIT_out, "      method : %-s (%.48s>>\n", o->its_meth, o->its_args);
      fprintf(yUNIT_out, "      test   : %-15s(@ %ld msecs with rc = %d) %s\n", o->its_test, _gcpu, o->its_code, (o->its_code <= -600) ? "----- BAD TEST -----" : "");
      if (strcmp(o->its_test, "void") != 0) {
         fprintf(yUNIT_out, "      expect : %-s>>\n", o->its_expe);
         if (strlen(o->its_fixd) > 0) fprintf(yUNIT_out, "      altered: %-s>>\n", o->its_fixd);
         fprintf(yUNIT_out, "      actual : %-s>>\n", o->its_actu);
      } else {
         fprintf(yUNIT_out, "      expect : void\n");
         fprintf(yUNIT_out, "      actual : void\n");
      }
   }
   /*---(complete)-------------------------------*/
   return;
}

/*===[[ END ]]================================================================*/
