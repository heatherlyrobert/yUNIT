/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YUNIT_unit_hguard
#define YUNIT_unit_hguard loaded


/*==========================---------------------=============================*/
/*===----                   shared unit test code                      ----===*/
/*==========================---------------------=============================*/



/*---(standard headers)---------------*/
#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>                   /* exit,atoi                                */
#include    <unistd.h>                   /* sleep                                    */
/*---(custom headers)-----------------*/
#include    <yUNIT.h>                    /* unit testing functions                   */

/*---(globals)------------------------*/
/*> static struct {                                                                    <* 
 *>    char        eterm;                    /+ handle console vs eterm           +/   <* 
 *>    int         level;                    /+ how loud things should be         +/   <* 
 *>    int         exec;                     /+ run scripts                       +/   <* 
 *>    int         scrp;                     /+ script selected for focus         +/   <* 
 *>    int         offset;                   /+ shared code condition offset      +/   <* 
 *>    int         origin;                   /+ shared code scription offset      +/   <* 
 *>    char        debug       [LEN_HUND];   /+ display debugging info            +/   <* 
 *>    char        CUSTOM      [LEN_RECD];   /+ holder for custom expect strings  +/   <* 
 *>    char       *s_rc;                                                               <* 
 *>    long        i_rc;                                                               <* 
 *>    double      r_rc;                                                               <* 
 *>    void       *p_rc;                                                               <* 
 *>    char       *scrps       [LEN_HUND];                                             <* 
 *>    char        all;                                                                <* 
 *> } myUNIT_RUN;                                                                      <*/


/*> static char    yUNIT_stats   (void);                                              <*/
/*> static char    yUNIT_verbs   (void);                                              <*/


static char
yUNIT_usage             (void)
{
   printf ("yUNIT -- heatherly unit testing framework\n");
   printf ("   #---(scope)--------------------#\n");
   printf ("   --all         = run all scripts and conditions\n");
   printf ("   <nn>          = only run script <nn>\n");
   printf ("   <nn>-<mm>     = run script between nn and mm (inclusive)\n");
   printf ("   <nn>,<mm>,... = run only scripts in list\n");
   printf ("   #---(verbosity)----------------#\n");
   printf ("   --quiet       = just returns a rc\n");
   printf ("   --none        = just returns a rc\n");
   printf ("   --test        = one line of summary statistics\n");
   printf ("   --scrp        = script level statistics only\n");
   printf ("   --cond        = condition level statistics only\n");
   printf ("   --step        = step header level statistics only\n");
   printf ("   --full        = full detail\n");
   printf ("   --loud        = full detail\n");
   printf ("   #---(information)--------------#\n");
   printf ("   --scrps       = script level inventory\n");
   printf ("   --conds       = condition level inventory\n");
   printf ("   --steps       = step level inventory\n");
   printf ("   --stats       = display conversion statistics\n");
   printf ("   #---(terminal)-----------------#\n");
   printf ("   --7bit        = base ascii characters only\n");
   printf ("   --8bit        = heatherly extended characters allowed\n");
   printf ("   --nocolor     = no terminal color codes\n");
   printf ("   --color       = add terminal color codes\n");
   printf ("   --console     = --7bit plus --nocolor\n");
   printf ("   --eterm       = --8bit plus --color\n");
   printf ("   #---(other)--------------------#\n");
   printf ("   --help        = usage information\n");
   exit   (0);
   return 0;
}

static char
yUNIT_init              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         j           =    0;
   /*---(display)-----------*/
   myUNIT_RUN.eterm   = 'y';
   myUNIT_RUN.level   = YUNIT_FULL;
   /*---(filters)-----------*/
   myUNIT_RUN.exec    = 1;
   myUNIT_RUN.scrp    = 0;
   /*---(helpers)-----------*/
   myUNIT_RUN.offset  = 0;
   myUNIT_RUN.origin  = 0;
   /*---(stats)-------------*/
   /*> yUNIT_stats ();                                                                <*/
   /*---(scripts)-----------*/
   for (j = 0; j < LEN_HUND; ++j)  myUNIT_RUN.scrps [j] = 'y';
   myUNIT_RUN.all     = 1;
   /*---(complete)----------*/
   return 0;
}

static char
yUNIT_run_scrp          (char a_scrp)
{
   if (myUNIT_RUN.scrps [a_scrp] == 'y')  return 1;
   return 0;
}

static char
yUNIT_args              (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         j           =    0;
   char       *a           = NULL;     /* cli argument holder     */
   int         v           =    5;     /* verbosity level         */
   int         l           =    0;     /* length of argument      */
   int         x_bad       =    0;     /* number of bad arguments */
   char        t           [10] = "";  /* temp string             */
   char        x_beg       =    0;
   char        x_end       =    0;
   char        n           =    0;
   /*---(process args)-------------------*/
   for (i = 1; i < a_argc; ++i) {
      a = a_argv[i];
      l = strlen (a);
      /*---(verbosity)--------------------*/
      if      (strcmp (a, "--quiet"     )  == 0)      v = 0;
      else if (strcmp (a, "--none"      )  == 0)      v = 0;
      else if (strcmp (a, "--test"      )  == 0)      v = 1;
      else if (strcmp (a, "--scrp"      )  == 0)      v = 2;
      else if (strcmp (a, "--cond"      )  == 0)      v = 3;
      else if (strcmp (a, "--step"      )  == 0)      v = 4;
      else if (strcmp (a, "--full"      )  == 0)      v = 5;
      else if (strcmp (a, "--maxx"      )  == 0)      v = 6;
      else if (strcmp (a, "--loud"      )  == 0)      v = 6;
      /*---(information)------------------*/
      else if (strcmp (a, "--scrps"     )  == 0)    { myUNIT_RUN.exec = 0; v = 2; }
      else if (strcmp (a, "--conds"     )  == 0)    { myUNIT_RUN.exec = 0; v = 3; }
      else if (strcmp (a, "--steps"     )  == 0)    { myUNIT_RUN.exec = 0; v = 4; }
      /*> else if (strcmp (a, "--stats"     )  == 0)      UNIT_stats ();              <*/
      /*---(help)-------------------------*/
      /*> else if (strcmp (a, "--help"      )  == 0)      UNIT_usage ();              <*/
      /*---(fomatting)--------------------*/
      else if (strcmp (a, "--console"   )  == 0)      myUNIT_RUN.eterm = '-';
      else if (strcmp (a, "--eterm"     )  == 0)      myUNIT_RUN.eterm = 'y';
      /*---(scope)------------------------*/
      else if (strcmp (a, "--all"       )  == 0)  {
         myUNIT_RUN.all     = 1;
         for (j = 0; j < LEN_HUND; ++j)  myUNIT_RUN.scrps [j] = 'y';
      }
      else if (l == 2) {
         myUNIT_RUN.all  = 0;
         for (j = 0; j < LEN_HUND; ++j)  myUNIT_RUN.scrps [j] = '-';
         x_beg = atoi(a);
         myUNIT_RUN.scrps [x_beg] = 'y';
      }
      else if (l == 5 && a [2] == '-') {
         myUNIT_RUN.all  = 0;
         for (j = 0; j < LEN_HUND; ++j)  myUNIT_RUN.scrps [j] = '-';
         sprintf (t, "%-2.2s", a);
         x_beg = atoi(t);
         sprintf (t, "%-2.2s", a + 3);
         x_end = atoi(t);
         if (x_beg <= 0 || x_end <= 0) {
            return rce;
         }
         for (j = x_beg; j <= x_end; ++j)  myUNIT_RUN.scrps [j] = 'y';
      }
      else if (l >= 5 && a [2] == ',') {
         myUNIT_RUN.all  = 0;
         for (j = 0; j < LEN_HUND; ++j)  myUNIT_RUN.scrps [j] = '-';
         for (n = 0; n < LEN_HUND; ++n) {
            if (l <  2 + (n * 3))  break;
            sprintf (t, "%-2.2s", a + (n * 3));
            x_beg = atoi(t);
            if (x_beg <= 0)   return rce;
            myUNIT_RUN.scrps [x_beg] = 'y';
         }
      }
      else {
         printf("option not understood <<%s>>\n", a);
         ++x_bad;
      }
      /*---(done)-------------------------*/
   }
   /*---(check results)------------------*/
   if (x_bad > 0) {
      printf("FATAL, exiting\n");
      exit (-1);
   }
   myUNIT_RUN.level = v;
   /*---(complete)-----------------------*/
   return 0;
}

static char
yUNIT_reset_rc          (void)
{
   myUNIT_RUN.s_rc  = NULL;
   myUNIT_RUN.i_rc  = 0;
   myUNIT_RUN.r_rc  = 0.0;
   myUNIT_RUN.p_rc  = NULL;
   return 0;
}

#endif
