#include "yUNIT.h"
#include "yUNIT_priv.h"


static long  S_beg      = 0;

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
yUNIT_scrp (int a_line, int a_seqn, cchar *a_stage, cchar *a_desc, cchar *a_dur, cchar *a_terse, cchar *a_focu)
{
   char        x_header    [LEN_HUND]  = "";
   char        x_desc      [LEN_HUND]  = "???";
   char        x_dur       [LEN_TERSE] = "???";
   char        x_terse     [LEN_LABEL] = "???";
   char        x_focu      [LEN_HUND]  = "???";
   /*---(start)------------------------*/
   S_beg = time (NULL);
   /*---(defense)----------------------*/
   if (a_seqn > 99)  a_seqn = 99;
   if (a_focu  != NULL)  strncpy (x_focu , a_focu , LEN_HUND);
   if (a_dur   != NULL)  strncpy (x_dur  , a_dur  , LEN_TERSE);
   if (a_terse != NULL)  strncpy (x_terse, a_terse, LEN_LABEL);
   if (a_desc  != NULL)  strncpy (x_desc , a_desc , LEN_HUND);
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
      snprintf (x_header, LEN_HUND, "  %-3.3s : %-14.14s : %s", x_dur, x_terse,x_focu);
      IF_COND   yunit_printf  ("%s\n", x_header);
   }
   /*---(wave-record)------------------*/
   yUNIT_wave_beg (myUNIT.proj, myUNIT.unit, a_seqn, x_desc, x_terse, a_stage [0], a_stage [1], x_dur);
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_prcs_wave         (void)
{
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        x_wave      [LEN_TITLE] = "";
   char        x_result    =  '-';
   long        x_end       =    0;
   long        x_dur       =    0;
   /*---(name)---------------------------*/
   sprintf (x_wave, "%s.wave", myUNIT.unit);
   x_end = time (NULL);
   x_dur = x_end - S_beg;
   if (x_dur < 0)  x_dur = 0;
   /*---(open)---------------------------*/
   f = fopen (x_wave, "at");
   --rce;  if (f == NULL) {
      return rce;
   }
   if      (SCRP_FAIL > 0)  x_result = 'F';
   else if (SCRP_BADD > 0)  x_result = 'W';
   else                     x_result = 'P';
   yUNIT_wave_act (f, 0, 1, SCRP_COND, SCRP_TEST, x_result,  SCRP_PASS, SCRP_FAIL, SCRP_BADD, SCRP_VOID, x_dur);
   fclose (f);
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
      yUNIT_prcs_wave ();
   } else  {
      yunit_footer (TYPE_DRCS);
      IF_COND   yunit_printf  ("%s\n", s_print);
   }
   /*---(complete)---------------------*/
   return 0;
}
