#include "yUNIT.h"
#include "yUNIT_priv.h"



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
