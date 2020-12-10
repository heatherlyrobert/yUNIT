#include "yUNIT.h"
#include "yUNIT_priv.h"



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
