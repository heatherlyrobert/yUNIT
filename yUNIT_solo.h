
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YUNIT_solo_hguard
#define YUNIT_solo_hguard loaded

/*====================------------------------------------====================*/
/*===----                  special mini unit test                      ----===*/
/*====================------------------------------------====================*/
static void      o___MINI_UNIT_______________o (void) {;}

#include    <ySTR_solo.h>
#include    <yCOLOR_solo.h>
#include    <time.h>


static int         s_stepn     = 0;

static int         s_condt     = 0;
static int         s_condn     = 0;
static int         s_conda     = 0;
static int         s_condg     = 0;

static char        s_scrpn     = 0;
static int         s_scrpa     = 0;
static int         s_scrpg     = 0;

static int         s_unita     = 0;
static int         s_unitg     = 0;
static char        s_unit      [LEN_TITLE] = "";
static char        s_system    [LEN_RECD]  = "";

static char
yunit_minchr            (int a_line, char *a_desc, char a_act, char a_exp)
{
   char        x_res       =  '-';
   char        x_note      [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ";
   int         l           = 0;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
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
   printf ("  %s%02d) %-6.6s%s : %-57.57s [%05d]\n", x_on, ++s_stepn, x_note, BACK_OFF, t, a_line);
   printf ("      expect : %c\n", a_exp);
   printf ("      actual : %c\n", a_act);
   printf ("\n");
   return 0;
}

#define  yUNIT_minchr(a,b,c)    yunit_minchr(__LINE__,a,b,c)

static char
yunit_minval            (int a_line, char *a_desc, int a_act, int a_exp)
{
   char        x_res       =  '-';
   char        x_note      [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ";
   int         l           = 0;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
   if (a_act == a_exp) {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   else if (a_act < 0 && a_exp == -999) {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   else if (a_act >= 0 && a_exp == 999) {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   l = strlen (a_desc) + 1;
   sprintf (t, "%s %s", a_desc, x_fill + l);
   printf ("  %s%02d) %-6.6s%s : %-57.57s [%05d]\n", x_on, ++s_stepn, x_note, BACK_OFF, t, a_line);
   printf ("      expect : %d\n", a_exp);
   printf ("      actual : %d\n", a_act);
   printf ("\n");
   return 0;
}

#define  yUNIT_minval(a,b,c)    yunit_minval(__LINE__,a,b,c)

static char
yunit_minpoint          (int a_line, char *a_desc, void *a_act, void *a_exp)
{
   char        x_res       =  '-';
   char        x_note      [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ";
   int         l           = 0;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
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
   printf ("  %s%02d) %-6.6s%s : %-57.57s [%05d]\n", x_on, ++s_stepn, x_note, BACK_OFF, t, a_line);
   printf ("      expect : %p\n", a_exp);
   printf ("      actual : %p\n", a_act);
   printf ("\n");
   return 0;
}

#define  yUNIT_minpoint(a,b,c)    yunit_minpoint(__LINE__,a,b,c)

static char
yunit_minstr            (int a_line, char *a_desc, char *a_act, char *a_exp)
{
   char        x_res       =  '-';
   char        x_note      [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ";
   int         l           = 0;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
   if (strcmp (a_act, a_exp) == 0) {
      strcpy (x_note, "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   l = strlen (a_desc) + 1;
   sprintf (t, "%s %s", a_desc, x_fill + l);
   printf ("  %s%02d) %-6.6s%s : %-57.57s [%05d]\n", x_on, ++s_stepn, x_note, BACK_OFF, t, a_line);
   printf ("      expect : %2d[%s]\n", strlen (a_exp), a_exp);
   printf ("      actual : %2d[%s]\n", strlen (a_act), a_act);
   printf ("\n");
   return 0;
}

#define  yUNIT_minstr(a,b,c)    yunit_minstr(__LINE__,a,b,c)

static char
yunit_minscrp           (int a_line, char a_proj [LEN_LABEL], char a_unit [LEN_LABEL], char a_desc [LEN_LONG])
{
   char        t           [LEN_RECD]  = "";
   char        x_wave      [LEN_RECD] = "";
   sprintf (t, "%s ==============================================================================", a_desc);
   printf ("SCRP [%02d] %63.63s[%05d]\n", ++s_scrpn, t, a_line);
   printf ("\n");
   s_scrpa = s_scrpg = 0;
   s_conda = s_condg = 0;
   s_condn = s_stepn = 0;
   strcpy  (s_unit, a_unit);
   sprintf (s_system, "rm -f %s.wave", s_unit);
   system  (s_system);
   sprintf (x_wave, "printf \"WAVE  ··´··´··´··´··´··´·´··´···  0           %-20.20s  %-30.30s  %2d  %-70.70s  ·········´·········´  ·  ·  ", a_proj, a_unit, s_scrpn, a_desc);
   strcpy  (s_system, x_wave);
   return 0;
}

#define  yUNIT_minscrp(a)         yunit_minscrp(__LINE__,"","",a)
#define  yUNIT_minscrpy(a,b,c)    yunit_minscrp(__LINE__,a,b,c)

static char
yunit_mincond           (int a_line, char *a_desc)
{
   char        t           [LEN_RECD]  = "";
   char       *x_fill      = " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --";
   int         l           = 0;
   l = strlen (a_desc) + 1;
   sprintf (t, "%s %s", a_desc, x_fill + l);
   printf ("  COND [%03d] %60.60s[%05d]\n", ++s_condn, t, a_line);
   printf ("\n");
   ++s_condt;
   s_conda = s_condg = 0;
   s_stepn = 0;
   return 0;
}

#define  yUNIT_mincond(a)    yunit_mincond(__LINE__,a)

static char
yUNIT_mindnoc           (void)
{
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   if (s_conda == s_condg) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
   }
   printf ("      %sDNOC  scrp ··, cond ···, test %4d, pass %4d, fail %4d =================%s\n", x_on, s_conda, s_condg, s_conda - s_condg, BACK_OFF);
   printf ("\n\n");
   return 0;
}

static char
yUNIT_minprcs           (void)
{
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   char        x_wave      [LEN_RECD] = "";
   char        x_result    =  'F';
   if (s_scrpa == s_scrpg) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_result = 'Ï';
   }
   printf ("  %sPRCS  scrp ··, cond %3d, test %4d, pass %4d, fail %4d =====================%s\n", x_on, s_condn, s_scrpa, s_scrpg, s_scrpa - s_scrpg, BACK_OFF);
   printf ("\n\n");
   sprintf (x_wave, "  0    1  %3d  %4d   0s    0  %c  %4d  %4d  %4d  %4d  %4d  %3d \n\" >> %s.wave", s_condn, s_scrpa, x_result, s_scrpg, s_scrpa - s_scrpg, 0, 0, 0, 0, s_unit);
   strcat  (s_system, x_wave);
   system  (s_system);
   return 0;
}

static char
yUNIT_mintinu           (void)
{
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   if (s_unita == s_unitg) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
   }
   printf ("%sTINU  scrp %2d, cond %3d, test %4d, pass %4d, fail %4d =======================%s\n", x_on, s_scrpn, s_condt, s_unita, s_unitg, s_unita - s_unitg, BACK_OFF);
   printf ("\n\n");
   return 0;
}

#endif
