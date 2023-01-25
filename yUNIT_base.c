#include "yUNIT.h"
#include "yUNIT_priv.h"

void     *yUNIT_p_rc;
long      yUNIT_i_rc;
double    yUNIT_r_rc;
char     *yUNIT_s_rc;
char      yUNIT_systext [1000];


tUNIT   myUNIT;


char          s_prefix    [LEN_RECD]  = "";
char          s_print     [LEN_RECD]  = "";
char          s_suffix    [LEN_RECD]  = "";
char          s_sect      [LEN_RECD]  = "";


/*===[[ TESTING ]]============================================================*/
/*> void     *my_unit = NULL;                                                         <*/

char      s_unit         [LEN_RECD] = "";
FILE     *yUNIT_stdin    = NULL;
FILE     *yUNIT_out      = NULL;



/*====================------------------------------------====================*/
/*===----                      manage output file                      ----===*/
/*====================------------------------------------====================*/
static void      o___OUTPUT__________________o (void) {;}

char
yunit_open         (cchar *a_name)
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
   /*---(ground)-------------------------*/
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
yunit_printf            (char *a_format, ...)
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
yUNIT_unique            (int a_scrp, int a_cond, int a_step)
{
   myUNIT.nscrp = a_scrp;
   myUNIT.ncond = a_cond;
   myUNIT.nstep = a_step;
   return 0;
}

char       /*----: change the color level)------------------------------------*/
yUNIT_eterm             (cchar a_eterm, cchar a_quiet)
{
   char        t           [LEN_HUND]  = "";
   /*---(setup verbosity)------------------*/
   if (a_eterm == YUNIT_ETERM)  {
      sprintf (t, "assign format/color to (%c) ETERM", a_eterm);
      myUNIT.eterm = YUNIT_ETERM;
      myUNIT.mono  = 0;
      myUNIT.pure  = 0;
   } else {
      sprintf (t, "assign format/color to (%c) CONSOLE", a_eterm);
      myUNIT.eterm = YUNIT_CONSOLE;
      myUNIT.mono  = 1;
      myUNIT.pure  = 1;
   }
   if (a_quiet != 'y')  IF_COND   yunit_printf ("   %-75.75s %5dx\n", t, myUNIT.nstep);
   return myUNIT.eterm;
}

char       /*----: change the verbosity level --------------------------------*/
yUNIT_level             (cchar a_level, cchar a_quiet)
{
   char        t           [LEN_HUND]  = "";
   if (a_level >= YUNIT_MUTE && a_level <= YUNIT_FULL) myUNIT.level = a_level;
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
   }
   if (a_quiet != 'y' && myUNIT.level > YUNIT_SCRP) yunit_printf ("   %-75.75s %5dc\n", t, myUNIT.ncond);
   return myUNIT.level;
}



/*====================------------------------------------====================*/
/*===----                           test-level                         ----===*/
/*====================------------------------------------====================*/
static void      o___TEST____________________o (void) {;}

char       /*----: create a new unit test ------------------------------------*/
yUNIT_unit         (cchar *a_name, cchar a_level, cchar a_eterm, cchar a_exec)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND];
   /*---(defaulting)---------------------*/
   strcpy (s_unit, "");
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)  return rce;
   /*---(open output)----------------------*/
   yunit_open (a_name);
   /*---(print header)---------------------*/
   if (a_level > 1)  yunit_printf ("yUNIT - heatherly unit testing framework ---------------------------------------(beg)\n");
   if (a_level > 2)  yunit_printf ("   patron : %-66.66s %5ds\n", P_ONELINE, myUNIT.nscrp);
   /*---(reset summary counters)-------*/
   UNIT_SCRP  = UNIT_COND  = UNIT_TEST  = UNIT_PASS  = UNIT_FAIL  = UNIT_BADD  = UNIT_VOID  = 0;
   /*---(setup defaults)-------------------*/
   yUNIT_level (a_level, '-');
   yUNIT_eterm (a_eterm, '-');
   /*---(leak testing)---------------------*/
   myUNIT.is_leak_begin  = malloc(sizeof(int));
   free(myUNIT.is_leak_begin);
   /*---(complete)-------------------------*/
   /*> if (a_exec == 1)  yunit_printf ("\n");                                         <*/
   return 0;
}

char       /*----: close a unit test -----------------------------------------*/
yUNIT_tinu              (cchar a_exec)
{  /*---(variables)------------------------*/
   int     x_failed  = UNIT_FAIL + UNIT_BADD;
   /*---(print message)---------------*/
   IF_SCRP   yunit_printf ("\n");
   IF_SCRP {
      if (a_exec == 1)  yunit_footer (TYPE_TINU);
      else              yunit_footer (TYPE_DINU);
      yunit_printf ("%s\n", s_print);
   }
   IF_COND  yunit_printf ("\n");
   IF_SCRP  {
      yunit_printf ("\n");
      yunit_printf ("yUNIT - heatherly unit testing framework ---------------------------------------(end)\n");
   }
   /*---(leak testing)---------------------*/
   /*> myUNIT.is_leak_end    = malloc(sizeof(int));                                   <*/
   /*> free(myUNIT.is_leak_end);                                                      <*/
   /*> if (myUNIT.is_leak_begin != myUNIT.is_leak_end) {                                                                                                                                            <* 
    *>    IF_COND   yunit_printf ("\nMEMORY LEAK    :: start=%p, end=%p, so %d bytes lost\n", myUNIT.is_leak_begin, myUNIT.is_leak_end, (int) (myUNIT.is_leak_end - myUNIT.is_leak_begin));    <* 
    *> } else {                                                                                                                                                                                     <* 
    *>    IF_COND   yunit_printf ("\nno memory leak :: start=%p, end=%p\n", myUNIT.is_leak_begin, myUNIT.is_leak_end);                                                                         <* 
    *> }                                                                                                                                                                                            <*/
   /*---(complete)--------------------------*/
   if (x_failed > 100) x_failed = 100;
   yunit_close ();
   /*> pr("%d\n", -x_failed);                                                    <*/
   /*> printf ("done, done\n");                                                       <*/
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
   if      (n <  32)    return '�';
   else if (n == 32)    return '�';
   else if (n < 127)    return n;
   else if (n < 161)    return '�';
   else if (n < 161)    return '�';
   else                 return n;
}

static int s_pointer = 42;

int*
yUNIT_testptr           (void)
{
   return &s_pointer;
}


/*===[[ END ]]================================================================*/
