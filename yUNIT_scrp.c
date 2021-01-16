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
         IF_COND   yunit_printf ("\n");
         IF_SCRP   yunit_printf ("\n");
         IF_COND   yunit_printf ("=========================------------------------------------========================\n");
         strcpy (s_print, s_sect);
         IF_SCRP   yunit_printf ("%s\n", s_print);
         IF_COND   yunit_printf ("=========================------------------------------------========================\n");
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
yUNIT_scrp (int a_line, int a_seqn, cchar *a_stage, cchar *a_desc, cchar *a_focu)
{
   char        x_header    [LEN_HUND] = "";
   char        x_focu      [LEN_HUND] = "???";
   char        x_desc      [LEN_HUND] = "???";
   /*---(defense)----------------------*/
   if (a_seqn > 99)  a_seqn = 99;
   if (a_focu != NULL)  strncpy (x_focu, a_focu, LEN_HUND);
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   /*---(show sect)--------------------*/
   yUNIT_sect   ("SCRP");
   /*---(reset summary counters)-------*/
   UNIT_SCRP++;
   SCRP_COND = SCRP_TEST = SCRP_PASS = SCRP_FAIL = SCRP_BADD = SCRP_VOID = 0;
   /*---(print title)------------------*/
   IF_SCRP   yunit_printf  ("\n");
   IF_COND   yunit_printf  ("\n");
   IF_STEP   yunit_printf  ("===[[ NEW SCRIPT ]]==================================================================\n");
   IF_SUMM   yunit_printf  ("%s\n", yunit_header (TYPE_SCRP, a_line, a_seqn, a_stage, x_desc));
   if (strlen (x_focu) > 0)  {
      snprintf (x_header, LEN_HUND, "  focus : %s", x_focu);
      IF_COND   yunit_printf  ("%s\n", x_header);
   }
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_prcs              (cchar a_exec)
{
   /*---(print message)-------------------*/
   IF_COND   yunit_printf ("\n");
   if (a_exec == 1) {
      yunit_footer (TYPE_PRCS);
      IF_SUMM   yunit_printf  ("%s\n", s_print);
   } else  {
      yunit_footer (TYPE_DRCS);
      IF_COND   yunit_printf  ("%s\n", s_print);
   }
   /*---(complete)---------------------*/
   return 0;
}
