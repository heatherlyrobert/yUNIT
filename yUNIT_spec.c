#include "yUNIT.h"
#include "yUNIT_priv.h"



static uchar  s_file      [LEN_HUND] = "";



/*====================------------------------------------====================*/
/*===----                       specialty-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;}

char
yUNIT_mode              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_exec, char a_dittoing, char a_share)
{
   char        x_meth      [LEN_HUND]  = "";
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "MODE"  , a_meth);
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, YUNIT_VOID, 0);
   /*---(dispaly)------------------------*/
   if (a_meth != NULL)  strncpy (x_meth, a_meth, LEN_HUND);
   if (strcmp (x_meth, "FORCED_FAIL") == 0) {
      YUNIT_FORCED = 1;
      yunit_disp_single  (TYPE_MODE  , a_line, a_seqn, a_share, "ENABLE FORCED FAILURE (pass=fail, fail=pass)");
   } else {
      YUNIT_FORCED = 0;
      yunit_disp_single  (TYPE_MODE  , a_line, a_seqn, a_share, "normal (a pass is a pass ;)");
   }
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_mode_reset        (void)
{
   YUNIT_FORCED = 0;
   return 0;
}

char
yUNIT_code              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_code [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "CODE"  , a_desc);
   yunit_actual_accum (TYPE_STEP, YUNIT_VOID, 0);
   yunit_disp_double  (TYPE_CODE  , a_line, a_seqn, a_share, a_desc, "code"  , a_code);
   return 0;
}

char
yUNIT_local             (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_code [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "LOCAL" , a_desc);
   yunit_actual_accum (TYPE_STEP, YUNIT_VOID, 0);
   yunit_disp_double  (TYPE_LOCAL , a_line, a_seqn, a_share, a_desc, "local" , a_code);
   return 0;
}

char
yUNIT_load              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_recd [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   int       x_flags = 0;         /* stdin file flags                         */
   int       i       = 0;
   int       x_ch    = 0;
   char        x_meth      [LEN_LABEL] = "???";
   char        x_recd      [LEN_RECD]  = "";
   char        x_disp      [LEN_RECD]  = "";
   int         l           =   0;
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "LOAD"  , a_desc);
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, YUNIT_VOID, 0);
   /*---(display)------------------------*/
   if (a_meth != NULL)   strncpy (x_meth, a_meth, LEN_RECD);
   if (a_recd != NULL)   strncpy (x_recd, a_recd, LEN_RECD);
   /*---(prepare data)-------------------*/
   strncpy (x_disp, x_recd, LEN_RECD);
   l = strlen (x_disp);
   for (i = 0; i < l; ++i)  if (x_disp [i] == '\n')  x_disp [i] = '�';
   yunit_disp_double  (TYPE_LOAD  , a_line, a_seqn, a_share, a_desc, x_meth  , x_disp);
   /*---(fix record)-------------------*/
   l = strlen (x_recd) - 1;
   if (x_recd [l] == '�') x_recd [l] = '\n';
   /*---(normal stdin)-----------------*/
   if (strcmp (x_meth, "stdin") == 0) {
      for (i = l; i >= 0; --i) {
         ungetc (x_recd [i], stdin);
      }
   }
   /*---(ncurses input)----------------*/
   else if (strcmp (x_meth, "ncurses") == 0) {
      while (x_ch = getch ()) {
         if (x_ch < 0)  break;
      }
      if (strlen (x_recd) > 0) {
         for (i = l; i >= 0; --i) {
            ungetch (x_recd [i]);
         }
      }
   }
   /*---(file input)-------------------*/
   else if (strcmp (x_meth, "file") == 0) {
      /*---(close it in case)----------*/
      if (yUNIT_stdin != NULL) fclose(yUNIT_stdin);
      /*---(write new data)------------*/
      yUNIT_stdin = fopen(STDIN, "a");
      IF_FULL  yUNIT_printf  ("%s\n", x_recd);
      fclose  (yUNIT_stdin);
      /*---(reopen for next steps)-----*/
      yUNIT_stdin = fopen(STDIN, "r");
   }
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_file              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_recd [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_resu      =    0;
   FILE       *x_file      = NULL;
   int         x_error     =    0;
   char        x_msg       [LEN_FULL]  = "";
   /*---(display only)-------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "FILE"  , a_desc);
   /*---(display only)-------------------*/
   strcpy (s_file, "");
   /*---(open/freshen file)--------------*/
   x_file = fopen (a_recd, "wt");
   if   (x_file != NULL)  {
      x_resu = YUNIT_SUCC; /* ++COND_PASS; */
      fprintf (x_file, "");
      fclose  (x_file);
      fflush  (x_file);
      strncpy (s_file, a_recd, LEN_HUND);
   }
   else  {
      x_resu = YUNIT_FAIL; /* ++COND_FAIL; */
      x_error = errno;
      sprintf (x_msg, "%d > %s", x_error, strerror (x_error));
   }
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, 0);
   /*---(display)------------------------*/
   yunit_disp_double  (TYPE_FILE  , a_line, a_seqn, a_share, a_desc, "file" , a_recd);
   if (x_file == NULL)  yUNIT_printf ("      ERROR  : %s\n", x_msg);
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_append            (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_recd [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_resu      =    0;
   FILE       *x_file      = NULL;
   int         x_error     =    0;
   int         l           =    0;
   int         i           =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        x_msg       [LEN_FULL]  = "";
   /*---(display only)-------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "FILE"  , a_desc);
   /*---(open/freshen file)--------------*/
   if (strcmp (s_file, "") == 0) {
      x_resu = YUNIT_FAIL; /* ++COND_FAIL; */
      strcpy (x_msg, "no file is currently specified");
   } else {
      x_file = fopen (s_file, "at");
      if (x_file != NULL) {
         x_resu = YUNIT_SUCC;
         strcpy (x_recd, a_recd);
         l = strlen (x_recd);
         for (i = 0; i < l; ++i)  {  if (x_recd [i] == '�')  x_recd [i] = ' ';  }
         fprintf (x_file, "%s\n", x_recd);
         fclose  (x_file);
         fflush  (x_file);
      } else {
         x_resu = YUNIT_FAIL; /* ++COND_FAIL; */
         x_error = errno;
         sprintf (x_msg, "%d > %s", x_error, strerror (x_error));
      }
   }
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, 0);
   /*---(display)------------------------*/
   yunit_disp_double  (TYPE_APPEND, a_line, a_seqn, a_share, a_desc, "append" , a_recd);
   if (x_file == NULL)  yUNIT_printf ("      ERROR  : %s\n", x_msg);
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_system            (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_disp [LEN_RECD], char a_cmd [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;
   int         x_rc        =    0;
   char        x_resu      =    0;
   char        x_msg       [LEN_FULL]  = "";
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "SYSTEM", a_desc);
   /*---(run system command)-----------*/
   if (a_cmd == NULL || a_cmd [0] == '\0') {
      rc     = -1;
      x_resu = YUNIT_WARN;
   } else {
      rc = system  (a_cmd);
      /*> if      (rc ==  127)  { x_resu = YUNIT_WARN; /+ ++COND_BADD; +/ }           <* 
       *> else if (rc >=  0  )  { x_resu = YUNIT_SUCC; /+ ++COND_PASS; +/ }           <* 
       *> else if (rc == -1  )  { x_resu = YUNIT_WARN; /+ ++COND_BADD; +/ }           <* 
       *> else if (rc == -127)  { x_resu = YUNIT_WARN; /+ ++COND_BADD; +/ }           <* 
       *> else if (rc <   0  )  { x_resu = YUNIT_FAIL; /+ ++COND_FAIL; +/ }           <*/
      x_rc = WEXITSTATUS (rc);
      if      (x_rc == 127) {
         x_resu = YUNIT_WARN;
         sprintf (x_msg, "%d > %s", x_rc, "shell command not found in linux");
      }
      else if (x_rc <    0)  {
         x_resu = YUNIT_FAIL;
         sprintf (x_msg, "%d > %s", x_rc, "shell command ended with errors");
      } else {
         x_resu = YUNIT_SUCC;
      }
   }
   /*> printf ("rc = %4d, x_rc = %d, x_resu = %d\n", rc, x_rc, x_resu);               <*/
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, rc);
   /*---(display)------------------------*/
   yunit_disp_double  (TYPE_SYSTEM, a_line, a_seqn, a_share, a_desc, "system" , a_disp);
   if (x_resu != YUNIT_SUCC)  yUNIT_printf ("      ERROR  : %s\n", x_msg);
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










