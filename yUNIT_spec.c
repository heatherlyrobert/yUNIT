#include "yUNIT.h"
#include "yUNIT_priv.h"




/*====================------------------------------------====================*/
/*===----                       specialty-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;}

char
yUNIT_mode              (int a_line, int a_seqn, cchar *a_desc, char a_exec)
{
   char        x_desc      [LEN_HUND]  = "";
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "MODE"  , a_desc);
   /*---(dispaly)------------------------*/
   ++COND_TEST;
   yunit_result (0, YUNIT_VOID);
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   if (strcmp (x_desc, "FORCED_FAIL") == 0) {
      myUNIT.is_forced_fail = 1;
      yunit_header (TYPE_MODE, a_line, a_seqn, "MODE"  , "ENABLE FORCED FAILURE (pass=fail, fail=pass)");
   } else {
      myUNIT.is_forced_fail = 0;
      yunit_header (TYPE_MODE, a_line, a_seqn, "MODE"  , "normal (a pass is a pass ;)");
   }
   IF_STEP {
      yunit_printf  ("\n");
      yunit_printf  ("%s\n", s_print);
   }
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_mode_reset        (void)
{
   myUNIT.is_forced_fail = 0;
   return 0;
}


char
yUNIT_code              (int a_line, int a_seqn, cchar *a_desc, cchar *a_code, char a_exec)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "CODE"  , a_desc);
   /*---(dispaly)------------------------*/
   ++COND_TEST;
   yunit_result (0, YUNIT_VOID);
   yunit_header (TYPE_CODE, a_line, a_seqn, "CODE"  , a_desc);
   IF_STEP {
      yunit_printf  ("\n");
      yunit_printf  ("%s\n", s_print);
      sprintf (s_suffix , "      code   : %2d[%.65s]", strlen (a_code), a_code);
      IF_FULL  yunit_printf  ("%s\n", s_suffix);
   }
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_load              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_recd, char a_exec)
{
   int       x_flags = 0;         /* stdin file flags                         */
   int       i       = 0;
   int       x_ch    = 0;
   char        x_meth      [LEN_LABEL] = "???";
   char        x_data      [LEN_RECD]  = "";
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "LOAD"  , a_desc);
   /*---(display)------------------------*/
   ++COND_TEST;
   yunit_result (0, YUNIT_VOID);
   if (a_meth != NULL)   strncpy (x_meth, a_meth, LEN_RECD);
   if (a_recd != NULL)   strncpy (x_data, a_recd, LEN_RECD);
   yunit_header (TYPE_LOAD, a_line, a_seqn, "LOAD"  , a_desc);
   IF_STEP {
      yunit_printf  ("\n");
      yunit_printf  ("%s\n", s_print);
      sprintf (s_suffix , "      %-7.7s: %2d[%.65s]", a_meth, strlen (a_recd), a_recd);
      IF_FULL  yunit_printf  ("%s\n", s_suffix);
   }
   /*---(normal stdin)-----------------*/
   if (strcmp (x_meth, "stdin") == 0) {
      for (i = strlen (a_recd) - 1; i >= 0; --i) {
         ungetc (a_recd [i], stdin);
      }
   }
   /*---(ncurses input)----------------*/
   else if (strcmp (x_meth, "ncurses") == 0) {
      while (x_ch = getch ()) {
         if (x_ch < 0)  break;
      }
      if (strlen (a_recd) > 0) {
         for (i = strlen (a_recd) - 1; i >= 0; --i) {
            ungetch (a_recd [i]);
         }
      }
   }
   /*---(file input)-------------------*/
   else if (strcmp (x_meth, "file") == 0) {
      /*---(close it in case)----------*/
      if (yUNIT_stdin != NULL) fclose(yUNIT_stdin);
      /*---(write new data)------------*/
      yUNIT_stdin = fopen(STDIN, "a");
      IF_FULL  yunit_printf  ("%s\n", a_recd);
      fclose  (yUNIT_stdin);
      /*---(reopen for next steps)-----*/
      yUNIT_stdin = fopen(STDIN, "r");
   }
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_system            (int a_line, int a_seqn, cchar *a_desc, cchar *a_disp, cchar *a_cmd, char a_exec)
{
   char        rc          =    0;
   char        x_resu      =    0;
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "SYS"   , a_desc);
   /*---(run system command)-----------*/
   if (a_cmd == NULL) {
      rc     = -1;
      x_resu = YUNIT_WARN;
   } else {
      rc = system  (a_cmd);
      if      (rc >=  0  )  { x_resu = YUNIT_SUCC; /* ++COND_PASS; */ }
      else if (rc == -1  )  { x_resu = YUNIT_WARN; /* ++COND_BADD; */ }
      else if (rc == -127)  { x_resu = YUNIT_WARN; /* ++COND_BADD; */ }
      else if (rc <   0  )  { x_resu = YUNIT_FAIL; /* ++COND_FAIL; */ }
   }
   /*---(display)------------------------*/
   ++COND_TEST;
   yunit_result (rc, x_resu);
   yunit_header (TYPE_SYSTEM, a_line, a_seqn, "SYS", a_desc);
   IF_STEP {
      yunit_printf  ("\n");
      yunit_printf  ("%s\n", s_print);
      sprintf (s_suffix , "      system : %2d[%.65s]", strlen (a_disp), a_disp);
      IF_FULL  yunit_printf  ("%s\n", s_suffix);
   }
   /*---(complete)---------------------*/
   return 0;
}

static char        s_recd      [LEN_RECD]  = "";

char*
yUNIT_read              (cchar *a_name, int n, int *c)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        t           [LEN_RECD]  = "";
   int         i           =    0;
   int         x_len       =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)         return "err  : name is null";
   --rce;  if (strlen (a_name) <= 0)   return "err  : name is empty";
   if (c != NULL)  *c = 0;
   strncpy (s_recd, "", LEN_RECD);
   /*---(open file)----------------------*/
   if      (strcmp (a_name, "stdsig") == 0)  f = fopen ("/tmp/signal.log"      , "rt");
   else if (strcmp (a_name, "unit"  ) == 0)  f = fopen ("/tmp/signal_unit.log" , "rt");
   else if (strcmp (a_name, "local" ) == 0)  f = fopen ("/tmp/signal_local.log", "rt");
   else                                      f = fopen (a_name                 , "rt");
   --rce;  if (f == NULL)              return "err  : file can not open";
   /*---(read records)-------------------*/
   while (1) {
      fgets (t, LEN_RECD, f);
      if (i != 0 && feof (f))  break;
      if (n <  0)  strncpy (s_recd, t, LEN_RECD);
      if (i == n)  strncpy (s_recd, t, LEN_RECD);
      if (feof (f))            break;
      ++i;
   }
   if (i > 999)  i = 999;
   /*---(clean record)-------------------*/
   x_len = strlen (s_recd);
   if (x_len > 0 && s_recd [x_len - 1] == '\n')  s_recd [--x_len] = '\0';
   /*---(close file)---------------------*/
   fclose (f);
   /*---(save back)----------------------*/
   if (c != NULL)  *c = i;
   /*---(complete)-----------------------*/
   return s_recd;
}










