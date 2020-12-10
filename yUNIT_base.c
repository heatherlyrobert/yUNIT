#include "yUNIT.h"
#include "yUNIT_priv.h"


char     s_sect      [LEN_LINE]   = "";


/*===[[ TESTING ]]============================================================*/
void     *my_unit = NULL;

FILE     *yUNIT_stdin;
FILE     *yUNIT_out;



/*====================------------------------------------====================*/
/*===----                           test-level                         ----===*/
/*====================------------------------------------====================*/
static void      o___TEST____________________o (void) {;}

void*      /*----: create a new unit test ------------------------------------*/
yUNIT_unit         (cchar *a_name, cchar a_noisy, cchar a_eterm)
{  /*---(allocate test)--------------------*/
   tUNIT     *o         = malloc(sizeof(tUNIT));
   char       t         [LEN_ARGS];
   /*---(setup defaults)-------------------*/
   yUNIT_noisy  (o, a_noisy);
   /*> yUNIT_eterm  (o, 'y');                                                         <*/
   /*---(open output)----------------------*/
   if (a_name != NULL)   snprintf (t, LEN_ARGS, "%s.urun", a_name);
   else                  snprintf (t, LEN_ARGS, "unittest.urun");
   yUNIT_out = fopen (t, "w");
   if (yUNIT_out == NULL)   return -1;
   /*---(print header)---------------------*/
   DISP_SCRP {
      fprintf (yUNIT_out, "yUNIT - heatherly unit testing framework ------------------------------------ (start)\n");
   }
   DISP_STEP {
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
   if (o == NULL) {
      DISP_SUMM fprintf(yUNIT_out, "   NEW TEST COULD NOT BE ALLOCATED (FATAL)\n");
      return NULL;
   }
   strncpy(o->its_name, a_name, LEN_NORM);
   DISP_STEP   fprintf(yUNIT_out, "   assign to program <<%s>>\n", o->its_name);
   /*---(reset summary counters)-------*/
   DISP_STEP   fprintf(yUNIT_out, "   initiaize summary counters\n");
   o->its_unit_test  = 0;
   o->its_unit_pass  = 0;
   o->its_unit_fail  = 0;
   o->its_unit_badd  = 0;
   o->its_unit_void  = 0;
   yUNIT_eterm (o, a_eterm);
   yUNIT_mode  (o, 0, 1, "normal");
   /*---(leak testing)---------------------*/
   o->is_leak_begin  = malloc(sizeof(int));
   free(o->is_leak_begin);
   /*---(complete)-------------------------*/
   DISP_STEP   fprintf(yUNIT_out, "\n");
   return o;
}

char       /*----: change the color level)------------------------------------*/
yUNIT_eterm        (cvoid *a_unit, cchar a_eterm)
{  /*---(allocate test)--------------------*/
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(setup verbosity)------------------*/
   if (a_eterm == 'y')  {
      DISP_COND   fprintf (yUNIT_out, "   assign color mode to ETERM\n");
      o->is_eterm = 'y';
   } else {
      DISP_COND   fprintf (yUNIT_out, "   assign color mode to CONSOLE\n");
      o->is_eterm = '-';
   }
   return o->is_eterm;
}

char       /*----: change the verbosity level --------------------------------*/
yUNIT_noisy        (cvoid *a_unit, cchar a_noisy)
{  /*---(allocate test)--------------------*/
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(setup verbosity)------------------*/
   if (a_noisy >= 0 && a_noisy <= 5) o->is_noisy = a_noisy;
   else                              o->is_noisy = 5;
   return o->is_noisy;
}

char       /*----: close a unit test -----------------------------------------*/
yUNIT_tinu         (void  *a_unit)
{  /*---(variables)------------------------*/
   tUNIT    *o       = (tUNIT *) a_unit;
   char    x_on      [20] = "";
   char    x_off     [20] = "";
   int     x_failed  = o->its_unit_fail;
   /*---(print message)---------------*/
   if (o->is_eterm == 'y') {
      if        (o->its_unit_fail > 0) {
         strcpy(x_on, "\e[41m");
      } else if (o->its_unit_badd > 0) {
         strcpy(x_on, "\e[43m");
      } else {
         strcpy(x_on, "\e[42m");
      }
      strcpy(x_off, "\e[0m");
   }
   DISP_SCRP   {
      fprintf(yUNIT_out, "\n%sTINU   step=%-4d", x_on, o->its_unit_test);
      fprintf(yUNIT_out, "  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s\n",
            o->its_unit_pass, o->its_unit_fail,
            o->its_unit_badd, o->its_unit_void,
            x_off);
      fprintf(yUNIT_out, "\n");
   }
   DISP_STEP   {
      fprintf(yUNIT_out, "shutting down...\n");
      fprintf(yUNIT_out, "   clear unit test for <<%s>>\n", o->its_name);
      fprintf(yUNIT_out, "   free the unit test\n");
      fprintf(yUNIT_out, "\n");
   }
   DISP_SCRP   {
      fprintf(yUNIT_out, "yUNIT - heatherly unit testing framework --------------------------------- (complete)\n");
   }
   DISP_SUMM {
      if (o->its_unit_fail > 0) fprintf(yUNIT_out, "FAILED  :: %d of %d steps failed\n",
            o->its_unit_fail, o->its_unit_test);
      else                      fprintf(yUNIT_out, "success :: %d of %d steps passed\n",
            o->its_unit_pass, o->its_unit_test);
   }
   /*---(leak testing)---------------------*/
   o->is_leak_end    = malloc(sizeof(int));
   free(o->is_leak_end);
   if (o->is_leak_begin != o->is_leak_end) {
      DISP_COND   fprintf(yUNIT_out, "\nMEMORY LEAK    :: start=%p, end=%p, so %d bytes lost\n", o->is_leak_begin, o->is_leak_end, (int) (o->is_leak_end - o->is_leak_begin)); 
   } else {
      DISP_COND   fprintf(yUNIT_out, "\nno memory leak :: start=%p, end=%p\n", o->is_leak_begin, o->is_leak_end); 
   }
   /*---(complete)--------------------------*/
   free(o);
   if (x_failed > 100) x_failed = 100;
   fclose (yUNIT_out);
   /*> printf ("done, done\n");                                                       <*/
   return -x_failed;
}

/*===[[ END ]]================================================================*/
