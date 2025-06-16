#include "yUNIT.h"
#include "yUNIT_priv.h"


static long  S_beg      = 0;

/*====================------------------------------------====================*/
/*===----                         script-level                         ----===*/
/*====================------------------------------------====================*/
static void      o___SCRIPT__________________o (void) {;}

char
yUNIT_scrp              (int a_line, int a_seqn, char a_stage [LEN_SHORT], char a_desc [LEN_LONG], char a_dur [LEN_SHORT], char a_terse [LEN_LABEL], char a_focu [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_line      [LEN_TERSE] = "";
   char        x_seqn      [LEN_TERSE] = "";
   char        x_desc      [LEN_LONG]  = "";
   char        x_fstage    [LEN_SHORT] = "??/?";
   char        x_header    [LEN_HUND]  = "";
   char        x_dur       [LEN_SHORT] = "???";
   char        x_terse     [LEN_LABEL] = "???";
   char        x_focu      [LEN_HUND]  = "???";
   char        l           =    0;
   char        x_wave      =  '·';
   char        x_stage     =  '·';
   char        x_rate      =  '·';
   /*---(handle counters)--------------*/
   yunit_actual_accum (TYPE_SCRP, 0, 0);
   /*---(start)------------------------*/
   S_beg = time (NULL);
   /*---(prepare)----------------------*/
   yunit_final_prep  (TYPE_SCRP, '-', a_line, a_seqn, a_desc, 85 - 24, YSTR_TEXT_LEF, 1, YSTR_EQUAL, x_line, x_seqn, x_desc);
   if (a_stage != NULL)  strncpy (x_fstage, a_stage, LEN_SHORT);
   if (a_dur   != NULL)  strncpy (x_dur   , a_dur  , LEN_SHORT);
   if (a_terse != NULL)  strncpy (x_terse , a_terse, LEN_LABEL);
   if (a_focu  != NULL)  strncpy (x_focu  , a_focu , LEN_HUND);
   /*---(show sect)--------------------*/
   yUNIT_sect   ("SCRP");
   /*---(print leader)-----------------*/
   IF_SCRP   yUNIT_printf  ("\n");
   IF_STEP   yUNIT_printf  ("===[[ NEW SCRIPT ]]==================================================================\n");
   /*---(print title)------------------*/
   snprintf (s_print, LEN_RECD, "SCRP %-4.4s %61.61s[%4s]=%-7.7s", x_seqn, x_desc, x_fstage, x_line);
   IF_SUMM   yUNIT_printf  ("%s\n", s_print);
   /*---(print detail)-----------------*/
   IF_STEP {
      if (strlen (x_focu) > 0)  {
         snprintf (x_header, LEN_HUND, "  %-3.3s : %-14.14s : %s", x_dur, x_terse, x_focu);
         IF_COND   yUNIT_printf  ("%s\n", x_header);
      }
   }
   /*---(wave-record)------------------*/
   l = strlen (a_stage);
   if (l > 0 && a_stage [0] != 0 && strchr (YSTR_NUMBER, a_stage [0]) != NULL)   x_wave  = x_fstage [0];
   if (l > 1 && a_stage [1] != 0 && strchr (YSTR_LOWER , a_stage [1]) != NULL)   x_stage = x_fstage [1];
   if (l > 3 && a_stage [3] != 0 && strchr (YSTR_UPLOW , a_stage [3]) != NULL)   x_rate  = x_fstage [2];
   yUNIT_wave_beg (myUNIT.proj, myUNIT.unit, a_seqn, x_desc, x_terse, x_wave, x_stage, x_rate, x_dur);
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_prcs_wave         (void)
{
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        x_wave      [LEN_TITLE] = "";
   char        x_result    =  '·';
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
   yunit_actual_pcrs  (f, x_dur);
   fclose (f);
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_prcs              (char a_exec)
{
   /*---(print message)-------------------*/
   IF_COND   yUNIT_printf ("\n");
   if (a_exec == 1) {
      yunit_final_footer (TYPE_PRCS);
      IF_SUMM   yUNIT_printf  ("%s\n", s_print);
      yUNIT_prcs_wave ();
   } else  {
      yunit_final_footer (TYPE_DRCS);
      IF_COND   yUNIT_printf  ("%s\n", s_print);
   }
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_sect              (char a_desc [LEN_LONG])
{  /*---(design notes)--------------------------------------------------------*/
   /* a SECT title is only printed when the next SCRP is found so footers     */
   /* will be correctly situated.                                             */
   char        x_desc      [LEN_LONG]  = "";
   yunit_final_prep  (TYPE_SECT, '-', 0, 0, a_desc, 85 - 24, YSTR_TEXT_CEN, 1, YSTR_DASH, NULL, NULL, x_desc);
   /*---(print title)--------------------*/
   if (a_desc != NULL && strcmp (a_desc, "SCRP") == 0) {
      /*---(print)----------*/
      if (strcmp (s_sect, "") != 0) {
         /*> IF_COND   yUNIT_printf ("\n");                                           <*/
         IF_SCRP   yUNIT_printf ("\n");
         IF_COND   yUNIT_printf ("=========================------------------------------------========================\n");
         strcpy (s_print, s_sect);
         IF_SCRP   yUNIT_printf ("%s\n", s_print);
         IF_COND   yUNIT_printf ("=========================------------------------------------========================\n");
      }
      /*---(clear)----------*/
      strcpy (s_sect, "");
   }
   /*---(save title)---------------------*/
   else {
      sprintf (s_print, "SECT ===----%s----=== TCES", x_desc);
      strcpy  (s_sect, s_print);
   }
   /*---(complete)-----------------------*/
   return 0;
}
