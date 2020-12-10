#include "yUNIT.h"
#include "yUNIT_priv.h"



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

