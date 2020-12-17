#include "yUNIT.h"
#include "yUNIT_priv.h"



/*====================------------------------------------====================*/
/*===----                         script-level                         ----===*/
/*====================------------------------------------====================*/
static void      o___SCRIPT__________________o (void) {;}

char    /*  PURPOSE :: break out a section                                    */
yUNIT_sect    (cchar *a_desc)
{  /*---(design notes)--------------------------------------------------------*/
   /* a SECT title is only printed when the next SCRP is found so footers     */
   /* will be correctly situated.                                             */
   /*---(print title)--------------------*/
   if (a_desc != NULL && strcmp (a_desc, "SCRP") == 0) {
      /*---(print)----------*/
      if (strcmp (s_sect, "") != 0) {
         IF_COND   fprintf(yUNIT_out, "\n\n\n");
         IF_SCRP   fprintf(yUNIT_out, "\n");
         IF_COND   fprintf(yUNIT_out, "=========================------------------------------------========================\n");
         strcpy (s_print, s_sect);
         IF_SCRP   fprintf(yUNIT_out, "%s\n", s_print);
         IF_COND   fprintf(yUNIT_out, "=========================------------------------------------========================\n");
      }
      /*---(clear)----------*/
      strcpy (s_sect, "");
   }
   /*---(save title)---------------------*/
   else {
      yunit_header (TYPE_SECT, 0, 0, NULL, a_desc);
      strcpy (s_sect, s_print);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char    /*  PURPOSE :: record the start of a new script                       */
yUNIT_scrp (int a_line, int a_seqn, cchar *a_focu, cchar *a_desc)
{
   char        x_header    [LEN_HUND] = "";
   char        x_focu      [LEN_HUND] = "???";
   char        x_desc      [LEN_HUND] = "???";
   /*---(defense)----------------------*/
   if (a_focu != NULL)  strncpy (x_focu, a_focu, LEN_HUND);
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   /*---(show sect)--------------------*/
   yUNIT_sect   ("SCRP");
   /*---(reset summary counters)-------*/
   SCRP_TEST = SCRP_PASS = SCRP_FAIL = SCRP_BADD = SCRP_VOID = 0;
   /*---(print title)------------------*/
   yunit_header (TYPE_SCRP, a_line, a_seqn, NULL, x_desc);
   IF_COND   fprintf (yUNIT_out, "\n\n");
   IF_STEP   fprintf (yUNIT_out, "\n===[[ NEW SCRIPT ]]==================================================================");
   IF_SCRP   fprintf (yUNIT_out, "\n%s\n", s_print);
   snprintf(x_header, LEN_HUND, "  focus : %s", x_focu);
   IF_COND   fprintf (yUNIT_out, "%-85.85s\n", x_header);
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_prcs              (void)
{
   /*---(print message)-------------------*/
   IF_COND   fprintf(yUNIT_out, "\n");
   IF_SCRP   {
      yunit_footer (TYPE_PRCS);
      fprintf (yUNIT_out, "%s\n", s_print);
   }
   IF_COND   fprintf(yUNIT_out, "\n");
   /*---(complete)---------------------*/
   return 0;
}
