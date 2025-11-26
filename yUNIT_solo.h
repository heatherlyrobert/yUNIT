/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YUNIT_solo_hguard
#define YUNIT_solo_hguard loaded



/*====================------------------------------------====================*/
/*===----                  special mini unit test                      ----===*/
/*====================------------------------------------====================*/
static void      o___MINI_UNIT_______________o (void) {;}

#include    <yCOLOR_solo.h>
#include    <time.h>

/*> static char  myunit_debug = '-';                                                    <* 
 *> static char  yunit_debugging (void)  { myunit_debug = 'y'; return myunit_debug; }   <* 
 *> #define   DEBUG_UUNIT   if (myunit_debug == 'y')                                    <*/



typedef struct tm        tTIME;

static char  s_home      [LEN_PATH]  = "";
static FILE *s_out       = NULL;

static int   s_stepn     = 0;

static int   s_condt     = 0;
static int   s_condn     = 0;
static int   s_conda     = 0;
static int   s_condg     = 0;

static char  s_scrpn     = 0;
static int   s_scrpa     = 0;
static int   s_scrpg     = 0;

static int   s_unita     = 0;
static int   s_unitg     = 0;
static char  s_unit      [LEN_TITLE] = "";
static char  s_system    [LEN_RECD]  = "";

static char
yUNIT_mintuo            (void)
{
   if (s_out != NULL && s_out != stdout) {
      fclose (s_out);
   }
   s_out = NULL;
   return 1;
}

static char
yUNIT_minout            (char a_file [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(close if open)------------------*/
   yUNIT_mintuo ();
   /*---(open)---------------------------*/
   if      (a_file     == NULL)                s_out = stdout;
   else if (a_file [0] == '\0')                s_out = stdout;
   else if (strcmp (a_file, "(stdout)") == 0)  s_out = stdout;
   else {
      s_out = fopen (a_file, "wt");
      if (s_out == NULL) {
         s_out = stdout;
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   return 1;
}

static char
yunit_minchr            (int a_line, char *a_desc, char a_act, char a_exp)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_res       =  '-';
   char        x_note      [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ";
   int         l           = 0;
   /*---(defense)------------------------*/
   if (s_out == NULL)  return -10;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
   /*---(prepare colors)-----------------*/
   if (a_act == a_exp) {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   l = strlen (a_desc) + 1;
   sprintf (t, "%s %s", a_desc, x_fill + l);
   fprintf (s_out, "  %s%02d) %-6.6s%s : %-57.57s [%05d]\n", x_on, ++s_stepn, x_note, BACK_OFF, t, a_line);
   fprintf (s_out, "      expect : %c\n", a_exp);
   fprintf (s_out, "      actual : %c\n", a_act);
   fprintf (s_out, "\n");
   fflush  (s_out);
   /*---(complete)-----------------------*/
   return 0;
}

#define  yUNIT_minchr(a,b,c)    yunit_minchr(__LINE__,a,b,c)

static char
yunit_minval            (int a_line, char *a_desc, int a_act, int a_exp)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_res       =  '-';
   char        x_note      [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ";
   int         l           = 0;
   /*---(defense)------------------------*/
   if (s_out == NULL)  return -10;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
   /*---(prepare colors)-----------------*/
   if ((a_act == a_exp)
         || (a_act  < 0 && a_exp == -999)
         || (a_act >= 0 && a_exp ==  999)
         || (a_exp == 666)) {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   l = strlen (a_desc) + 1;
   sprintf (t, "%s %s", a_desc, x_fill + l);
   fprintf (s_out, "  %s%02d) %-6.6s%s : %-57.57s [%05d]\n", x_on, ++s_stepn, x_note, BACK_OFF, t, a_line);
   fprintf (s_out, "      expect : %d\n", a_exp);
   fprintf (s_out, "      actual : %d\n", a_act);
   fprintf (s_out, "\n");
   fflush  (s_out);
   /*---(complete)-----------------------*/
   return 0;
}

#define  yUNIT_minval(a,b,c)    yunit_minval(__LINE__,a,b,c)

static char
yunit_minptr            (int a_line, char *a_desc, void *a_act, void *a_exp)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_res       =  '-';
   char        x_note      [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ";
   int         l           = 0;
   /*---(defense)------------------------*/
   if (s_out == NULL)  return -10;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
   /*---(prepare colors)-----------------*/
   if (a_exp == 0 && a_act == NULL) {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   else if (a_exp == 1 && a_act != NULL) {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   else if (a_exp > 1 && a_exp == a_act) {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   l = strlen (a_desc) + 1;
   sprintf (t, "%s %s", a_desc, x_fill + l);
   fprintf (s_out, "  %s%02d) %-6.6s%s : %-57.57s [%05d]\n", x_on, ++s_stepn, x_note, BACK_OFF, t, a_line);
   fprintf (s_out, "      expect : %p\n", a_exp);
   fprintf (s_out, "      actual : %p\n", a_act);
   fprintf (s_out, "\n");
   fflush  (s_out);
   /*---(complete)-----------------------*/
   return 0;
}

#define  yUNIT_minptr(a,b,c)    yunit_minptr(__LINE__,a,b,c)

static char
yunit_minstr            (int a_line, char *a_desc, char *a_act, char *a_exp)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_res       =  '-';
   char        x_note      [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ";
   int         le          = 0;
   int         la          = 0;
   int         i           = 0;
   char        x_exp       [LEN_RECD] = "";
   /*---(defense)------------------------*/
   if (s_out == NULL)  return -10;
   /*---(update counters)----------------*/
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
   /*---(prepare)------------------------*/
   strcpy (x_exp, a_exp);
   le = strlen (x_exp);
   la = strlen (a_act);
   x_res = 'Y';
   /*---(fix expected)-------------------*/
   if (le > 0 && x_exp [le - 1] == '¬') {
      if (le < la) {
         for (i = le; i < la; ++i)   strlcat (x_exp, "¬", LEN_RECD);
      } else if (le > la) {
         for (i = la - 1; i >= le; -+i)  if (x_exp [i] == '¬')  x_exp [i] = '\0';
      }
      le = strlen (x_exp);
   }
   /*---(prepare)------------------------*/
   if (strcmp (a_exp, "¬") != 0) {
      for (i = 0; i < le; ++i) {
         if (x_exp [i] == '¬')        continue;
         if (x_exp [i] == a_act [i])  continue;
         x_res = '-';
         x_exp [i] = '°';
      }
      if (le != strlen (a_act))  x_res = '-';
   }
   /*---(update if passed)---------------*/
   if (x_res == 'Y') {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   /*---(present)------------------------*/
   le = strlen (a_desc) + 1;
   sprintf (t, "%s %s", a_desc, x_fill + le);
   fprintf (s_out, "  %s%02d) %-6.6s%s : %-57.57s [%05d]\n", x_on, ++s_stepn, x_note, BACK_OFF, t, a_line);
   fprintf (s_out, "      expect : %3då%sæ\n", strlen (x_exp), x_exp);
   fprintf (s_out, "      actual : %3då%sæ\n", strlen (a_act), a_act);
   fprintf (s_out, "\n");
   fflush  (s_out);
   /*---(complete)-----------------------*/
   if (x_res == 'Y')  return 1;
   return 0;
}

static char
yunit_minunit           (char a_file [LEN_TITLE], char a_func [LEN_TITLE], int a_line, int a_argc, char *a_argv [], char a_unit [LEN_TITLE], char a_oneline [LEN_HUND], char *r_nunit, char *r_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_out       [LEN_TITLE] = "temp.urun";
   char        x_prog      [LEN_TITLE] = "";
   char        x_oneline   [LEN_HUND]  = "";
   char        x_unit      [LEN_TITLE] = "(n/a)";
   char        x_nunit     =    0;
   char        x_list      =  '-';
   char        t           [LEN_RECD]  = "=================================================================================================================";
   char        l           =    0;
   /*---(default)------------------------*/
   if (r_nunit != NULL)  *r_nunit = x_nunit;
   if (r_list  != NULL)  *r_list  = x_list;
   /*---(direct output)------------------*/
   if      (a_unit     == NULL)  strcpy  (x_unit, "(stdout)");
   else if (a_unit [0] == '\0')  strcpy  (x_unit, "(stdout)");
   else  {
      strlcpy (x_unit, a_unit, LEN_TITLE);
      sprintf (x_out, "%s_munit.urun", x_unit);
   }
   rc = yUNIT_minout (x_out);
   /*---(defense)------------------------*/
   --rce;  if (a_unit == NULL || a_unit [0] == '\0')  { printf ("%sFATAL, yunit_munit a_unit is null/empty%s\n",      BOLD_ERR, BOLD_OFF);  yUNIT_mintuo ();  return rce; }
   --rce;  if (rc < 0)                                { printf ("%sFATAL, yunit_munit output not configured%s\n",     BOLD_ERR, BOLD_OFF);  yUNIT_mintuo ();  return rce; }
   --rce;  if (s_out  == NULL)                        { printf ("%sFATAL, yunit_munit output not configured%s\n",     BOLD_ERR, BOLD_OFF);  yUNIT_mintuo ();  return rce; }
   --rce;  if (s_out  == stdout)                      { printf ("%sFATAL, yunit_munit output not configured%s\n",     BOLD_ERR, BOLD_OFF);  yUNIT_mintuo ();  return rce; }
   --rce;  if (a_argc <  1)                           { printf ("%sFATAL, yunit_munit a_argc is negative/zero%s\n",   BOLD_ERR, BOLD_OFF);  yUNIT_mintuo ();  return rce; }
   --rce;  if (a_argv == NULL)                        { printf ("%sFATAL, yunit_munit a_argv is null/empty%s\n",      BOLD_ERR, BOLD_OFF);  yUNIT_mintuo ();  return rce; }
   --rce;  if (a_file == NULL || a_file [0] == '\0')  { printf ("%sWARNING, yunit_munit a_file is null/empty%s\n",    BOLD_YEL, BOLD_OFF); }
   --rce;  if (a_func == NULL || a_func [0] == '\0')  { printf ("%sWARNING, yunit_munit a_func is null/empty%s\n",    BOLD_YEL, BOLD_OFF); }
   --rce;  if (a_line <= 0)                           { printf ("%sWARNING, yunit_munit a_line is negative/zero%s\n", BOLD_YEL, BOLD_OFF); }
   /*---(handle prog name)---------------*/
   strlcpy (x_prog, a_argv [0], LEN_TITLE);
   /*---(handle oneline)-----------------*/
   if      (a_oneline     == NULL)  strcpy  (x_oneline, "(null)");
   else if (a_oneline [0] == '\0')  strcpy  (x_oneline, "(empty)");
   else                             strlcpy (x_oneline, a_oneline, LEN_HUND);
   /*---(handle args)--------------------*/
   if (a_argc >= 2) {
      if (strcmp (a_argv [1], "--list") == 0)       x_list  = 'y';
      else if (strcmp (a_argv [1], "--inst") == 0)  x_list  = '!';
      else                                          x_nunit = atoi (a_argv [1]);
   }
   /*---(unofficial headings)------------*/
   /*> printf ("## %s\n", x_oneline);                                                      <* 
    *> printf ("## pre-yUNIT unit testing : %s\n", x_prog);                                <* 
    *> if (x_nunit  >  0 )        printf ("## selected single script (%2d)\n", x_nunit);   <* 
    *> else                       printf ("## selected all scripts\n");                    <* 
    *> if (x_list == 'y')         printf ("## list script(s) only\n");                     <* 
    *> else if (x_list == '!')    printf ("## generate initial wave file\n");              <* 
    *> else                       printf ("## execute conditions and steps\n");            <*/
   /*---(official heading)---------------*/
   l = strlen (x_unit);
   l = 80 - 6 - l;
   fprintf (s_out, "UNIT %*.*s %s\n\n", l, l, t, x_unit);
   fflush  (s_out);
   /*---(save-back)----------------------*/
   if (r_nunit != NULL)  *r_nunit = x_nunit;
   if (r_list  != NULL)  *r_list  = x_list;
   /*---(complete)-----------------------*/
   return 1;
}
#define  yUNIT_minunit(a,b,c,d,e,f)   yunit_minunit(__FILE__,__FUNCTION__,__LINE__,a,b,c,d,e,f)

#define  yUNIT_minstr(a,b,c)    yunit_minstr(__LINE__,a,b,c)

static char
yunit_minscrp           (int a_line, char a_proj [LEN_LABEL], char a_unit [LEN_LABEL], char a_desc [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "";
   char        x_wave      [LEN_RECD] = "";
   long        x_now       =    0;
   tTIME      *x_broke     = NULL;
   /*---(defense)------------------------*/
   if (s_out == NULL)  return -10;
   /*---(remember home)------------------*/
   getcwd (s_home, LEN_PATH);
   printf ("remembering location å%sæ\n", s_home);
   /*---(display)------------------------*/
   sprintf (t, "%s ==============================================================================", a_desc);
   fprintf (s_out, "SCRP [%02d] %63.63s[%05d]\n", ++s_scrpn, t, a_line);
   fprintf (s_out, "\n");
   fflush  (s_out);
   s_scrpa = s_scrpg = 0;
   s_conda = s_condg = 0;
   s_condn = s_stepn = 0;
   strcpy  (s_unit, a_unit);
   x_now   = time (NULL);
   x_broke = localtime (&x_now);
   strftime (t, LEN_TITLE, "%y.%m.%d.%H.%M.%S.%u.%W.%j", x_broke);
   sprintf (x_wave, "printf \"WAVE  %-26.26s  %10ld  %-20.20s  %-30.30s  %2d  m  %-70.70s  ·········´·········´  ·  ·  ·  ", t, x_now, a_proj, a_unit, s_scrpn, a_desc);
   strcpy  (s_system, x_wave);
   /*---(complete)-----------------------*/
   return 0;
}

#define  yUNIT_minscrp(a)         yunit_minscrp(__LINE__,"","",a)
#define  yUNIT_minscrpy(a,b,c)    yunit_minscrp(__LINE__,a,b,c)

static char
yunit_mincond           (int a_line, char *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --";
   int         l           = 0;
   /*---(defense)------------------------*/
   if (s_out == NULL)  return -10;
   l = strlen (a_desc) + 1;
   sprintf (t, "%s %s", a_desc, x_fill + l);
   fprintf (s_out, "  COND [%03d] %60.60s[%05d]\n", ++s_condn, t, a_line);
   fprintf (s_out, "\n");
   fflush  (s_out);
   ++s_condt;
   s_conda = s_condg = 0;
   s_stepn = 0;
   /*---(complete)-----------------------*/
   return 0;
}

#define  yUNIT_mincond(a)    yunit_mincond(__LINE__,a)

static char
yUNIT_mindnoc           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   /*---(defense)------------------------*/
   if (s_out == NULL)  return -10;
   /*---(prepare colors)-----------------*/
   if (s_conda == s_condg) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
   }
   /*---(display)------------------------*/
   fprintf (s_out, "      %sDNOC  scrp ··, cond ···, test %4d, pass %4d, fail %4d =================%s\n", x_on, s_conda, s_condg, s_conda - s_condg, BACK_OFF);
   fprintf (s_out, "\n\n");
   fflush  (s_out);
   /*---(complete)-----------------------*/
   return 0;
}

static char
yUNIT_minprcs           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        x_wave      [LEN_RECD] = "";
   char        x_result    =  'F';
   /*---(defense)------------------------*/
   if (s_out == NULL)  return -10;
   /*---(prepare colors)-----------------*/
   if (s_scrpa == 0) {
      strcpy (t   , "NONE");
      strcpy (x_on, BACK_OFF);
      x_result = '-';
   } else if (s_scrpa == s_scrpg) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_result = 'Ï';
   }
   /*---(display)------------------------*/
   fprintf (s_out, "  %sPRCS  scrp ··, cond %3d, test %4d, pass %4d, fail %4d =====================%s\n", x_on, s_condn, s_scrpa, s_scrpg, s_scrpa - s_scrpg, BACK_OFF);
   fprintf (s_out, "\n\n");
   fflush  (s_out);
   /*---(make wave)----------------------*/
   sprintf (x_wave, "  0    1  %3d  %4d   0s    0  %c  %4d  %4d  %4d  %4d  %4d  %3d \n\" >> %s.wave", s_condn, s_scrpa, x_result, s_scrpg, s_scrpa - s_scrpg, 0, 0, 0, 0, s_unit);
   strcat  (s_system, x_wave);
   system  (s_system);
   /*---(return home)--------------------*/
   /*> printf ("returning to location å%sæ\n", s_home);                               <*/
   chdir (s_home);
   /*---(complete)-----------------------*/
   return 0;
}

static char
yunit_mintinu           (char a_file [LEN_TITLE], char a_func [LEN_TITLE], int a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_on        [10]  = BACK_RED;
   int         c           =    0;
   /*---(defense)------------------------*/
   if (s_out == NULL)  return -10;
   /*---(prepare colors)-----------------*/
   c = s_unita - s_unitg;
   if (c == 0) strcpy (x_on, BACK_GRN);
   /*---(display)------------------------*/
   fprintf (s_out, "%sTINU  scrp %2d, cond %3d, test %4d, pass %4d, fail %4d =======================%s\n", x_on, s_scrpn, s_condt, s_unita, s_unitg, s_unita - s_unitg, BACK_OFF);
   fprintf (s_out, "\n");
   /*---(flush/close)--------------------*/
   fflush  (s_out);
   yUNIT_mintuo ();
   /*---(complete)-----------------------*/
   if (c > 0)  return -10;
   return 1;
}

#define  yUNIT_mintinu()   yunit_mintinu(__FILE__,__FUNCTION__,__LINE__)

#endif
