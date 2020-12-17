#include "yUNIT.h"
#include "yUNIT_priv.h"



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
   printf ("entering yunit_open (%p)\n", yUNIT_out);
   --rce;  if (yUNIT_out != NULL)    return rce;
   --rce;  if (a_name == NULL || strlen (a_name) == 0) {
      strcpy (x_name, "/dev/null");
   } else {
      snprintf (x_name, LEN_HUND, "%s.urun", a_name);
   }
   printf ("file [%s]\n", x_name);
   /*---(ground)-------------------------*/
   yUNIT_out = fopen (x_name, "wt");
   --rce;  if (yUNIT_out == NULL) {
      return rce;
   }
   printf ("yUNIT_out (%p)\n", yUNIT_out);
   /*---(complete)-------------------------*/
   return 0;
}

char
yunit_write        (cchar *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (yUNIT_out == NULL)    return rce;
   --rce;  if (a_recd    == NULL)    return rce;
   /*---(write)--------------------------*/
   fprintf (yUNIT_out, "%s\n", a_recd);
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



/*====================------------------------------------====================*/
/*===----                      global configuration                    ----===*/
/*====================------------------------------------====================*/
static void      o___CONFIG__________________o (void) {;}

char       /*----: change the color level)------------------------------------*/
yUNIT_eterm             (cchar a_eterm)
{
   /*---(setup verbosity)------------------*/
   if (a_eterm == YUNIT_ETERM)  {
      IF_COND   if (yUNIT_out != NULL)  fprintf (yUNIT_out, "   assign color mode to ETERM\n");
      myUNIT.eterm = YUNIT_ETERM;
   } else {
      IF_COND   if (yUNIT_out != NULL)  fprintf (yUNIT_out, "   assign color mode to CONSOLE\n");
      myUNIT.eterm = YUNIT_CONSOLE;
   }
   return myUNIT.eterm;
}

char       /*----: change the verbosity level --------------------------------*/
yUNIT_level             (cchar a_level)
{
   if (a_level >= YUNIT_MUTE && a_level <= YUNIT_FULL)
      myUNIT.level = a_level;
   else
      myUNIT.level = YUNIT_FULL;
   return myUNIT.level;
}



/*====================------------------------------------====================*/
/*===----                           test-level                         ----===*/
/*====================------------------------------------====================*/
static void      o___TEST____________________o (void) {;}

char       /*----: create a new unit test ------------------------------------*/
yUNIT_unit         (cchar *a_name, cchar a_level, cchar a_eterm)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_HUND];
   /*> tUNIT      *o           = NULL;                                                <*/
   /*---(defaulting)---------------------*/
   /*> o = (tUNIT *) malloc (sizeof (tUNIT));                                         <*/
   strcpy (s_unit, "");
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)  return rce;
   /*---(setup defaults)-------------------*/
   yUNIT_level  (a_level);
   /*> yUNIT_eterm  (o, 'y');                                                         <*/
   /*---(open output)----------------------*/
   yunit_open (a_name);
   /*---(print header)---------------------*/
   IF_SCRP {
      fprintf (yUNIT_out, "yUNIT - heatherly unit testing framework ------------------------------------ (start)\n");
   }
   IF_STEP {
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "  focus         : (PS) Programming Support\n");
      fprintf (yUNIT_out, "  niche         : (ut) unit testing\n");
      fprintf (yUNIT_out, "  application   : yUNIT       (automated unit testing)\n");
      fprintf (yUNIT_out, "  purpose       : provide a consistent, fullsome, automated unit testing framework\n");
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "  base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)\n");
      fprintf (yUNIT_out, "  lang_name     : gnu/ansi-c  (wicked, limitless, universal, and everlasting)\n");
      fprintf (yUNIT_out, "  dependencies  : yVAR\n");
      fprintf (yUNIT_out, "  size_goal     : tiny        (approximately 500 slocL)\n");
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "  author        : the_heatherlys\n");
      fprintf (yUNIT_out, "  created       : 2008-08 from previous c/c++ and bash versions\n");
      fprintf (yUNIT_out, "  priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)\n");
      fprintf (yUNIT_out, "  end_goals     : loosely coupled, strict interface, maintainable, portable\n");
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "-------------------------------------------------------------------------------------\n");
      fprintf (yUNIT_out, "\n");
      fprintf (yUNIT_out, "starting up...\n");
      fprintf (yUNIT_out, "   create a new unit test\n");
   }
   strncpy (myUNIT.name, a_name, LEN_HUND);
   IF_STEP   fprintf(yUNIT_out, "   assign to program <<%s>>\n", myUNIT.name);
   /*---(reset summary counters)-------*/
   IF_STEP   fprintf(yUNIT_out, "   initiaize summary counters\n");
   UNIT_TEST  = 0;
   UNIT_PASS  = 0;
   UNIT_FAIL  = 0;
   UNIT_BADD  = 0;
   UNIT_VOID  = 0;
   yUNIT_eterm (a_eterm);
   /*> yUNIT_mode  (0, 1, "normal");                                                  <*/
   /*---(leak testing)---------------------*/
   myUNIT.is_leak_begin  = malloc(sizeof(int));
   free(myUNIT.is_leak_begin);
   /*---(complete)-------------------------*/
   IF_STEP   fprintf(yUNIT_out, "\n");
   return 0;
   /*> return o;                                                                      <*/
}

char       /*----: close a unit test -----------------------------------------*/
yUNIT_tinu              (void)
{  /*---(variables)------------------------*/
   int     x_failed  = UNIT_FAIL;
   /*---(print message)---------------*/
   IF_COND   fprintf(yUNIT_out, "\n");
   IF_SCRP   {
      yunit_footer (TYPE_TINU);
      fprintf(yUNIT_out, "%s\n", s_print);
      fprintf(yUNIT_out, "\n");
   }
   IF_STEP   {
      fprintf(yUNIT_out, "shutting down...\n");
      fprintf(yUNIT_out, "   clear unit test for <<%s>>\n", myUNIT.name);
      fprintf(yUNIT_out, "   free the unit test\n");
      fprintf(yUNIT_out, "\n");
   }
   IF_SCRP   {
      fprintf(yUNIT_out, "yUNIT - heatherly unit testing framework --------------------------------- (complete)\n");
   }
   IF_SUMM {
      if (UNIT_FAIL > 0) fprintf(yUNIT_out, "FAILED  :: %d of %d steps failed\n",
            UNIT_FAIL, UNIT_TEST);
      else                      fprintf(yUNIT_out, "success :: %d of %d steps passed\n",
            UNIT_PASS, UNIT_TEST);
   }
   /*---(leak testing)---------------------*/
   myUNIT.is_leak_end    = malloc(sizeof(int));
   free(myUNIT.is_leak_end);
   if (myUNIT.is_leak_begin != myUNIT.is_leak_end) {
      IF_COND   fprintf(yUNIT_out, "\nMEMORY LEAK    :: start=%p, end=%p, so %d bytes lost\n", myUNIT.is_leak_begin, myUNIT.is_leak_end, (int) (myUNIT.is_leak_end - myUNIT.is_leak_begin)); 
   } else {
      IF_COND   fprintf(yUNIT_out, "\nno memory leak :: start=%p, end=%p\n", myUNIT.is_leak_begin, myUNIT.is_leak_end); 
   }
   /*---(complete)--------------------------*/
   if (x_failed > 100) x_failed = 100;
   yunit_close ();
   /*> printf ("done, done\n");                                                       <*/
   return -x_failed;
}



/*===[[ END ]]================================================================*/
