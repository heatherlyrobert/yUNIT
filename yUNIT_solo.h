/*====================------------------------------------====================*/
/*===----                  special mini unit test                      ----===*/
/*====================------------------------------------====================*/
static void      o___MINI_UNIT_______________o (void) {;}

static int         s_stepn     = 0;

static int         s_condn     = 0;
static int         s_conda     = 0;
static int         s_condg     = 0;

static char        s_scrpn     = 0;
static int         s_scrpa     = 0;
static int         s_scrpg     = 0;

static int         s_unita     = 0;
static int         s_unitg     = 0;

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
   if (a_act < 0 && a_exp == -999) {
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
yunit_minscrp           (int a_line, char *a_desc)
{
   char        t           [LEN_RECD]  = "";
   sprintf (t, "%s ==============================================================================", a_desc);
   printf ("SCRP [%02d] %63.63s[%05d]\n", ++s_scrpn, t, a_line);
   printf ("\n");
   s_scrpa = s_scrpg = 0;
   s_conda = s_condg = 0;
   s_condn = s_stepn = 0;
   return 0;
}

#define  yUNIT_minscrp(a)    yunit_minscrp(__LINE__,a)

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
   printf ("      %sDNOC  test %4d, pass %4d, fail %4d ====================================%s\n", x_on, s_conda, s_condg, s_conda - s_condg, BACK_OFF);
   printf ("\n\n");
   return 0;
}

static char
yUNIT_minprcs           (void)
{
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   if (s_scrpa == s_scrpg) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
   }
   printf ("  %sPRCS  test %4d, pass %4d, fail %4d ========================================%s\n", x_on, s_scrpa, s_scrpg, s_scrpa - s_scrpg, BACK_OFF);
   printf ("\n\n");
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
   printf ("%sTINU  test %4d, pass %4d, fail %4d ==========================================%s\n", x_on, s_unita, s_unitg, s_unita - s_unitg, BACK_OFF);
   printf ("\n\n");
   return 0;
}


