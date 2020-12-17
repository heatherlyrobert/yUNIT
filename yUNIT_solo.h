

static int         s_stepn     = 0;

static int         s_conda     = 0;
static int         s_condg     = 0;

static char        s_scrpn     = 0;
static int         s_scrpa     = 0;
static int         s_scrpg     = 0;

static int         s_unita     = 0;
static int         s_unitg     = 0;



static char
yUNIT_minchr            (char *a_desc, char a_act, char a_exp)
{
   char        x_res       =  '-';
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
   if (a_act == a_exp) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   printf ("  %s%02d) %-6.6s%s : %-40.40s\n", x_on, ++s_stepn, t, BACK_OFF, a_desc);
   printf ("      expect : %c\n", a_exp);
   printf ("      actual : %c\n", a_act);
   printf ("\n");
   return 0;
}

static char
yUNIT_minval            (char *a_desc, int a_act, int a_exp)
{
   char        x_res       =  '-';
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
   if (a_act == a_exp) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   if (a_act < 0 && a_exp == -999) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   printf ("  %s%02d) %-6.6s%s : %-40.40s\n", x_on, ++s_stepn, t, BACK_OFF, a_desc);
   printf ("      expect : %d\n", a_exp);
   printf ("      actual : %d\n", a_act);
   printf ("\n");
   return 0;
}

static char
yUNIT_minstr            (char *a_desc, char *a_act, char *a_exp)
{
   char        x_res       =  '-';
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   ++s_conda;
   ++s_scrpa;
   ++s_unita;
   if (strcmp (a_act, a_exp) == 0) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_condg;
      ++s_scrpg;
      ++s_unitg;
   }
   printf ("  %s%02d) %-6.6s%s : %-40.40s\n", x_on, ++s_stepn, t, BACK_OFF, a_desc);
   printf ("      expect : %2d[%s]\n", strlen (a_exp), a_exp);
   printf ("      actual : %2d[%s]\n", strlen (a_act), a_act);
   printf ("\n");
   return 0;
}

static char
yUNIT_minscrp           (char *a_desc)
{
   char        t           [LEN_RECD]  = "";
   sprintf (t, "%s ==============================================================================", a_desc);
   printf ("SCRP [%02d] %70.70s\n", ++s_scrpn, t);
   printf ("\n");
   s_scrpa = s_scrpg = 0;
   s_conda = s_condg = 0;
   s_stepn = 0;
   return 0;
}

static char
yUNIT_mincond           (char *a_desc)
{
   char        t           [LEN_RECD]  = "";
   sprintf (t, "  %s ----------------------------------------------------------------------------", a_desc);
   printf ("  GROUP %72.72s\n", t);
   printf ("\n");
   s_conda = s_condg = 0;
   s_stepn = 0;
   return 0;
}

static char
yUNIT_mindnoc           (void)
{
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   if (s_conda == s_condg) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
   }
   printf ("      %sDNOC  test %4d, pass %4d, fail %4d ========================================%s\n", x_on, s_conda, s_condg, s_conda - s_condg, BACK_OFF);
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


