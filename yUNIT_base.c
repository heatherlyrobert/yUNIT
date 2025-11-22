#include    "yUNIT.h"
#include    "yUNIT_priv.h"

#include    <ySTR_uver.h>
#include    <yLOG_uver.h>
#include    <yENV_uver.h>

void     *yUNIT_p_rc;
long      yUNIT_i_rc;
double    yUNIT_r_rc;
char     *yUNIT_s_rc;
char      yUNIT_systext [1000];

char      zUNIT_debug = '-';

tUNIT   myUNIT;


char          s_prefix    [LEN_RECD]  = "";
char          s_print     [LEN_RECD]  = "";
char          s_suffix    [LEN_RECD]  = "";
char          s_sect      [LEN_RECD]  = "";


/*===[[ TESTING ]]============================================================*/
/*> void     *my_unit = NULL;                                                         <*/

/*> char      s_unit         [LEN_RECD] = "";                                         <*/
FILE     *yUNIT_stdin    = NULL;
FILE     *yUNIT_out      = NULL;



/*====================------------------------------------====================*/
/*===----                         supporting                           ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT___________o (void) {;}

char      verstring    [LEN_HUND];

char*
yUNIT_version           (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang      ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (verstring, LEN_HUND, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return verstring;
}

char  yUNIT_debugging (void)  { zUNIT_debug = 'y'; return zUNIT_debug;  }




/*====================------------------------------------====================*/
/*===----                      manage output file                      ----===*/
/*====================------------------------------------====================*/
static void      o___OUTPUT__________________o (void) {;}

char
yunit_open         (char a_name [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_name      [LEN_HUND]  = "";
   /*---(defense)------------------------*/
   --rce;  if (yUNIT_out != NULL)    return rce;
   --rce;  if (a_name == NULL || strlen (a_name) == 0) {
      strcpy (x_name, "/dev/null");
   } else {
      if (strstr (a_name, ".urun") == NULL)  snprintf (x_name, LEN_HUND, "%s.urun", a_name);
      else                                   strcpy   (x_name, a_name);
   }
   /*---(open)---------------------------*/
   yUNIT_out = fopen (x_name, "wt");
   --rce;  if (yUNIT_out == NULL) {
      return rce;
   }
   /*---(save name)------------------------*/
   strncpy (myUNIT.name, x_name, LEN_HUND);
   /*---(complete)-------------------------*/
   return 0;
}

char
yUNIT_printf            (char *a_format, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   va_list     x_vlist;
   /*---(defense)------------------------*/
   --rce;  if (yUNIT_out == NULL)    return rce;
   --rce;  if (a_format  == NULL)    return rce;
   /*---(write)--------------------------*/
   va_start (x_vlist, a_format);
   vfprintf (yUNIT_out, a_format, x_vlist);
   va_end   (x_vlist);
   fflush   (yUNIT_out);
   /*---(complete)-------------------------*/
   return 0;
}

char
yunit_close        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (yUNIT_out == NULL)    return rce;
   /*---(write)--------------------------*/
   fclose (yUNIT_out);
   yUNIT_out = NULL;
   /*---(complete)-------------------------*/
   return 0;
}

char
yunit_remove                 (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_RECD]  = "";
   /*---(defense)------------------------*/
   --rce;  if (yUNIT_out != NULL)    return rce;
   /*---(write)--------------------------*/
   sprintf (t, "rm -f %s 2> /dev/null", myUNIT.name);
   system  (t);
   /*---(complete)-------------------------*/
   return 0;
}

char
yunit_close_and_remove       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (yUNIT_out == NULL)    return rce;
   /*---(write)--------------------------*/
   yunit_close  ();
   yunit_remove ();
   /*---(complete)-------------------------*/
   return 0;
}

char
yunit_cycle        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_RECD]  = "";
   /*---(defense)------------------------*/
   --rce;  if (yUNIT_out == NULL)    return rce;
   /*---(write)--------------------------*/
   yunit_close  ();
   yunit_remove ();
   yunit_open   (myUNIT.name);
   /*---(complete)-------------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      global configuration                    ----===*/
/*====================------------------------------------====================*/
static void      o___CONFIG__________________o (void) {;}

char
yUNIT_unique            (int a_nscrp, int a_ncond, int a_nstep, int a_uscrp, int a_ucond, int a_ustep)
{
   myUNIT.nscrp = a_nscrp;
   myUNIT.ncond = a_ncond;
   myUNIT.nstep = a_nstep;
   myUNIT.uscrp = a_uscrp;
   myUNIT.ucond = a_ucond;
   myUNIT.ustep = a_ustep;
   return 0;
}

char       /*----: change the color level)------------------------------------*/
yUNIT_eterm             (char a_eterm, char a_quiet)
{
   char        t           [LEN_HUND]  = "";
   char        i           =    0;
   char        x_all       [LEN_SHORT] = "";
   char        x_uniq      [LEN_SHORT] = "";
   /*---(prepare)--------------------------*/
   snprintf (x_all , LEN_SHORT, "%4d" , myUNIT.nstep);
   for (i = 0; i < LEN_SHORT; ++i)  if (x_all  [i] == ' ')  x_all  [i] = '·';
   snprintf (x_uniq, LEN_SHORT, "%4d", myUNIT.ustep);
   for (i = 0; i < LEN_SHORT; ++i)  if (x_uniq [i] == ' ')  x_uniq [i] = '·';
   /*---(setup verbosity)------------------*/
   if (a_eterm == YUNIT_ETERM)  {
      sprintf (t, "assign format/color to (%c) ETERM", a_eterm);
      YUNIT_TERM  = YUNIT_ETERM;
      YUNIT_MONO  = '-';
      YUNIT_PURE  = '-';
      YUNIT_BEG   = 'å';
      YUNIT_END   = 'æ';
      strlcpy (YUNIT_ELIPSIS, "···"     , LEN_TERSE);
      strlcpy (YUNIT_SDOTS  , " "       , LEN_FULL);
      strlcat (YUNIT_SDOTS  , YSTR_ESTEP, LEN_FULL);
      strlcpy (YUNIT_NDOTS  , YSTR_EDOTS, LEN_FULL);
   } else {
      sprintf (t, "assign format/color to (%c) CONSOLE", a_eterm);
      YUNIT_TERM  = YUNIT_CONSOLE;
      YUNIT_MONO  = 'y';
      YUNIT_PURE  = 'y';
      YUNIT_BEG   = '[';
      YUNIT_END   = ']';
      strlcpy (YUNIT_ELIPSIS, "   "     , LEN_TERSE);
      strlcpy (YUNIT_SDOTS  , YSTR_CSTEP, LEN_FULL);
      strlcpy (YUNIT_NDOTS  , YSTR_EMPTY, LEN_FULL);
   }
   if (a_quiet != 'y')  IF_COND   yUNIT_printf ("   %-65.65s x ···· %4s %-4s\n", t, x_all, x_uniq);
   return YUNIT_TERM;
}

char       /*----: change the verbosity level --------------------------------*/
yUNIT_level             (char a_level, char a_quiet)
{
   char        t           [LEN_HUND]  = "";
   char        i           =    0;
   char        x_all       [LEN_SHORT] = "";
   char        x_uniq      [LEN_SHORT] = "";
   /*---(prepare)--------------------------*/
   snprintf (x_all , LEN_SHORT, "%4d" , myUNIT.ncond);
   for (i = 0; i < LEN_SHORT; ++i)  if (x_all  [i] == ' ')  x_all  [i] = '·';
   snprintf (x_uniq, LEN_SHORT, "%4d", myUNIT.ucond);
   for (i = 0; i < LEN_SHORT; ++i)  if (x_uniq [i] == ' ')  x_uniq [i] = '·';
   /*---(setup output level)---------------*/
   if (a_level >= YUNIT_MUTE && a_level <= YUNIT_MAXX) myUNIT.level = a_level;
   else                                                myUNIT.level = YUNIT_FULL;
   switch (myUNIT.level) {
   case YUNIT_MUTE  : case YUNIT_SUMM  : case YUNIT_SCRP  :
      break;
   case YUNIT_COND  :
      sprintf (t, "assign output level to (%d) YUNIT_COND", myUNIT.level);
      break;
   case YUNIT_STEP  :
      sprintf (t, "assign output level to (%d) YUNIT_STEP", myUNIT.level);
      break;
   case YUNIT_FULL  : 
      sprintf (t, "assign output level to (%d) YUNIT_FULL", myUNIT.level);
      break;
   case YUNIT_MAXX  : 
      sprintf (t, "assign output level to (%d) YUNIT_MAXX", myUNIT.level);
      break;
   }
   if (a_quiet != 'y' && myUNIT.level > YUNIT_SCRP) yUNIT_printf ("   %-65.65s c ···· %4s %-4s\n", t, x_all, x_uniq);
   return myUNIT.level;
}



/*====================------------------------------------====================*/
/*===----                           test-level                         ----===*/
/*====================------------------------------------====================*/
static void      o___TEST____________________o (void) {;}

char       /*----: create a new unit test ------------------------------------*/
yUNIT_unit         (char a_name [LEN_TITLE], char a_level, char a_eterm, char a_exec)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND];
   char        i           =    0;
   char        x_all       [LEN_SHORT] = "";
   char        x_uniq      [LEN_SHORT] = "";
   char        x_name      [LEN_PATH]  = "";
   char       *p           = NULL;
   int         l           =    0;
   /*---(defaulting)---------------------*/
   /*> strcpy (s_unit, "");                                                           <*/
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)  return rce;
   /*---(open output)----------------------*/
   if (strchr (a_name, '/') == NULL) {
      getcwd (x_name, LEN_PATH);
      strcat (x_name, "/");
      strcat (x_name, a_name);
   } else {
      strcpy (x_name, a_name);
   }
   yunit_open (x_name);
   /*---(prepare)--------------------------*/
   snprintf (x_all , LEN_SHORT, "%4d" , myUNIT.nscrp);
   for (i = 0; i < LEN_SHORT; ++i)  if (x_all  [i] == ' ')  x_all  [i] = '·';
   snprintf (x_uniq, LEN_SHORT, "%4d", myUNIT.uscrp);
   for (i = 0; i < LEN_SHORT; ++i)  if (x_uniq [i] == ' ')  x_uniq [i] = '·';
   /*---(print header)---------------------*/
   switch (a_level) {
   case  YUNIT_SUMM : case  YUNIT_MUTE :
      break;
   case  YUNIT_SCRP :
      yUNIT_printf ("yUNIT - heatherly unit testing framework ---------------------------------------(beg)\n");
      break;
   case  YUNIT_COND : case  YUNIT_STEP : case  YUNIT_FULL :
      yUNIT_printf ("yUNIT - heatherly unit testing framework --------------------------- - actu once ndit\n");
      yUNIT_printf ("   patron : %-56.56s s ···· %4s %4s\n"  , P_ONELINE, x_all, x_uniq);
      break;
   }
   /*---(reset summary counters)-------*/
   yunit_actual_init ();
   /*---(setup defaults)-------------------*/
   yUNIT_level (a_level, '-');
   yUNIT_eterm (a_eterm, '-');
   /*---(get project name)---------------*/
   p = strchr (a_name, '_');
   if (p == NULL)  strcpy (myUNIT.proj, a_name);
   else {
      l = p - a_name;
      strncpy (myUNIT.proj, a_name, l);
   }
   /*---(get project name)---------------*/
   p = strchr (a_name, '.');
   if (p == NULL)  strcpy (myUNIT.unit, a_name);
   else {
      l = p - a_name;
      strncpy (myUNIT.unit, a_name, l);
   }
   /*---(leak testing)---------------------*/
   myUNIT.is_leak_begin  = malloc(sizeof(int));
   free(myUNIT.is_leak_begin);
   /*---(unit name)------------------------*/
   l = strlen (a_name);
   l = 85 - 6 - l;
   IF_SUMM  yUNIT_printf ("\nUNIT %*.*s %s\n", l, l, YSTR_EQUAL, a_name);
   /*---(complete)-------------------------*/
   /*> if (a_exec == 1)  yUNIT_printf ("\n");                                         <*/
   return 0;
}

char       /*----: close a unit test -----------------------------------------*/
yUNIT_tinu              (char a_exec)
{  /*---(variables)--------+-----+-----+-*/
   int         x_failed    =    0;
   char        i           =    0;
   /*---(print message)------------------*/
   IF_SCRP   yUNIT_printf ("\n");
   IF_SCRP {
      if (a_exec == 1)  yunit_final_footer (TYPE_TINU);
      else              yunit_final_footer (TYPE_DINU);
      yUNIT_printf ("%s\n", s_print);
   }
   /*> IF_COND  yUNIT_printf ("\n");                                                  <*/
   IF_SCRP  {
      yUNIT_printf ("\n");
      yUNIT_printf ("yUNIT - heatherly unit testing framework ---------------------------------------(end)\n");
   }
   /*---(leak testing)-------------------*/
   /*> myUNIT.is_leak_end    = malloc(sizeof(int));                                   <*/
   /*> free(myUNIT.is_leak_end);                                                      <*/
   /*> if (myUNIT.is_leak_begin != myUNIT.is_leak_end) {                                                                                                                                            <* 
    *>    IF_COND   yUNIT_printf ("¦MEMORY LEAK    :: start=%p, end=%p, so %d bytes lost\n", myUNIT.is_leak_begin, myUNIT.is_leak_end, (int) (myUNIT.is_leak_end - myUNIT.is_leak_begin));    <* 
    *> } else {                                                                                                                                                                                     <* 
    *>    IF_COND   yUNIT_printf ("¦no memory leak :: start=%p, end=%p\n", myUNIT.is_leak_begin, myUNIT.is_leak_end);                                                                         <* 
    *> }                                                                                                                                                                                            <*/
   /*---(update header)------------------*/
   fflush (yUNIT_out);
   yunit_close ();
   x_failed = yunit_actual_wrap (myUNIT.level);
   if (x_failed > 100) x_failed = 100;
   /*---(complete)-----------------------*/
   return -x_failed;
}


char*
yUNIT_teststring        (char n)
{
   switch (n) {
   case 0 : return "hello";
   case 1 : return "goodbye";
   default: return "something";
   }
}

float
yUNIT_testreal          (float n)
{
   return n * 3.1415927;
}

int
yUNIT_testint           (int n)
{
   return n % 5;
}

char
yUNIT_testchar          (char n)
{
   if      (n <  32)    return '´';
   else if (n == 32)    return '·';
   else if (n < 127)    return n;
   else if (n < 161)    return '´';
   else if (n < 161)    return '´';
   else                 return n;
}

static int s_pointer = 42;

int*
yUNIT_testptr           (void)
{
   return &s_pointer;
}


/*===[[ END ]]================================================================*/
