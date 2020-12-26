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
#include    <yVAR.h>                     /* complex comparison functions             */
#include    <ySTR_solo.h>                /* string lengths                           */



/*---(globals)------------------------*/
struct {
   char        eterm;                    /* handle console vs eterm                  */
   int         level;                    /* how loud things should be                */
   int         exec;                     /* run scripts                              */
   int         scrp;                     /* script selected for focus                */
   int         cond;                     /* condition selected for focus             */
   int         offset;                   /* shared code condition offset             */
   int         origin;                   /* shared code scription offset             */
   char        debug       [LEN_HUND];   /* display debugging info                   */
   char        CUSTOM      [LEN_RECD];   /* holder for custom expect strings         */
} g;



char
yUNIT_usage             (void)
{
   printf ("yUNIT -- heatherly unit testing framework\n");
   printf ("   #---(scope)--------------------#\n");
   printf ("   --all         = run all scripts and conditions\n");
   printf ("   <nn>          = only run script <nn>\n");
   printf ("   <nn>.<nnn>    = only show detail on condition <nnn>\n");
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

char
yUNIT_init              (void)
{
   g.eterm   = 'y';
   g.level   = YUNIT_FULL;
   g.exec    = 1;
   g.scrp    = 0;
   g.cond    = 0;
   g.offset  = 0;
   g.origin  = 0;
   return 0;
}

char
yUNIT_args              (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;     /* loop iterator -- args   */
   char       *a           = NULL;     /* cli argument holder     */
   int         v           =    5;     /* verbosity level         */
   int         l           =    0;     /* length of argument      */
   int         x_bad       =    0;     /* number of bad arguments */
   char        x_temp      [10] = "";  /* temp string             */
   /*---(process args)-------------------*/
   for (i = 1; i < a_argc; ++i) {
      a = a_argv[i];
      l = strlen(a);
      /*---(verbosity)--------------------*/
      if      (strcmp (a, "--quiet"     )  == 0)      v = 0;
      else if (strcmp (a, "--none"      )  == 0)      v = 0;
      else if (strcmp (a, "--test"      )  == 0)      v = 1;
      else if (strcmp (a, "--scrp"      )  == 0)      v = 2;
      else if (strcmp (a, "--cond"      )  == 0)      v = 3;
      else if (strcmp (a, "--step"      )  == 0)      v = 4;
      else if (strcmp (a, "--full"      )  == 0)      v = 5;
      else if (strcmp (a, "--loud"      )  == 0)      v = 5;
      /*---(information)------------------*/
      else if (strcmp (a, "--scrps"     )  == 0)    { g.exec = 0; v = 2; }
      else if (strcmp (a, "--conds"     )  == 0)    { g.exec = 0; v = 3; }
      else if (strcmp (a, "--steps"     )  == 0)    { g.exec = 0; v = 4; }
      /*> else if (strcmp (a, "--stats"     )  == 0)      UNIT_stats ();              <*/
      /*---(help)-------------------------*/
      /*> else if (strcmp (a, "--help"      )  == 0)      UNIT_usage ();              <*/
      /*---(fomatting)--------------------*/
      else if (strcmp (a, "--console"   )  == 0)      g.eterm = '-';
      else if (strcmp (a, "--eterm"     )  == 0)      g.eterm = 'y';
      /*---(scope)------------------------*/
      else if (strcmp (a, "--all"       )  == 0)      { g.scrp = g.cond = 0; }
      else if (l == 2) {
          g.scrp = atoi(a);
      }
      else if (l == 6 && (a[2] == '.' || a[2] == '-'))    {
          sprintf (x_temp, "%%c%%c", a[0], a[1]);
          g.scrp = atoi (x_temp);
          sprintf (x_temp, "%%c%%c%%c", a[3], a[4], a[5]);
          g.cond = atoi (x_temp);
          v = 3;
      }
      else {
         printf("option not understood <<%%s>>\n", a);
         ++x_bad;
      }
      /*---(done)-------------------------*/
   }
   /*---(check results)------------------*/
   if (x_bad > 0) {
         printf("FATAL, exiting\n");
         exit (-1);
   }
   g.level = v;
   /*---(complete)-----------------------*/
   return 0;
}

