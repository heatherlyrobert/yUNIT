#include "yUNIT.h"
#include "yUNIT_priv.h"



static uchar  s_file      [LEN_HUND] = "";



/*====================------------------------------------====================*/
/*===----                        support functions                     ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char*
yunit_header            (char a_type, int a_line, int a_seqn, char *a_note, char a_desc [LEN_LONG], char a_share, char a_select)
{
   /*---(locals)-----------+-----+-----+-*/
   int         l           =    0;
   int         x_pre       =    0;
   int         x_suf       =    0;
   char        x_note      [LEN_TERSE] = "???";
   char        x_desc      [LEN_HUND]  = "???";
   char        t           [LEN_RECD]  = "";
   char        x_test      [LEN_LABEL] = "";
   char        x_on        [LEN_LABEL] = "";
   char        x_on2       [LEN_LABEL] = "";
   char        x_off       [LEN_LABEL] = "";
   /*---(defense)------------------------*/
   if (a_line <     0)  a_line = 0;
   if (a_line > 99999)  a_line = 99999;
   if (a_seqn <     0)  a_seqn = 0;
   if (a_seqn >   999)  a_seqn = 999;
   if (a_note != NULL)  strncpy (x_note, a_note, LEN_TERSE);
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   /*---(fix a little)---------------------------*/
   if      (strncmp (x_desc, "... ", 4) == 0)   strncpy (x_desc, a_desc + 4, LEN_HUND);
   else if (strncmp (x_desc, "..." , 3) == 0)   strncpy (x_desc, a_desc + 3, LEN_HUND);
   /*---(colors)-------------------------*/
   yunit_final_color (YUNIT_MONO, a_type, x_on, NULL, x_off, x_note, NULL);
   /*---(find merge point)---------------*/
   /*> strcat (x_desc, " ");                                                          <*/
   l       = strlen (x_desc);
   x_pre   = (65 - l) / 2;
   x_suf   = (65 - x_pre) - l;
   switch (a_type) {
   case TYPE_LOCAL : case TYPE_CODE  : case TYPE_LOAD  : case TYPE_MODE  : case TYPE_FILE  : case TYPE_APPEND  :
      ++l;
      snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_ESTEP + l);
      snprintf (s_print, LEN_RECD, "  %s%s) %s%-6.6s%s : %63.63s[%05d]", BACK_CYN, yunit_final_step (a_seqn), BACK_GRN, a_note, BACK_OFF, t, a_line);
      break;
   case TYPE_SYSTEM :
      ++l;
      if (strcmp (x_note, "PASS")   == 0)  strcpy  (x_note, a_note);
      if (x_note [0] == '!')               sprintf (x_note, "!%s", a_note);
      if (strcmp (x_on  , BACK_GRN) == 0)  strcpy (x_on  , BACK_CYN);
      snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_ESTEP + l);
      snprintf (s_print, LEN_RECD, "  %s%s) %s%-6.6s%s : %63.63s[%05d]", x_on, yunit_final_step (a_seqn), x_on2, x_note, x_off, t, a_line);
      break;
   case TYPE_STEP  :
      /*> ++l;                                                                                                                                       <* 
       *> /+> if (myUNIT.level <= 4)  strncpy (x_note, a_note, LEN_LABEL);                <+/                                                        <* 
       *> /+> ++l;                                                                        <+/                                                        <* 
       *> if (YUNIT_PURE == 'y')  snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_CSTEP + l);                                                     <* 
       *> else                    snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_ESTEP + l);                                                     <* 
       *> if (YUNIT_FORCED) {                                                                                                                        <* 
       *>    snprintf (s_print, LEN_RECD, "  %s%s) %s%-6.6s%s : %63.63s[%05d]", x_on, yunit_final_step (a_seqn), x_on2, x_note, x_off, t, a_line);   <* 
       *> } else {                                                                                                                                   <* 
       *>    snprintf (s_print, LEN_RECD, "  %s%s) %-6.6s%s : %63.63s[%05d]", x_on, yunit_final_step (a_seqn), x_note, x_off, t, a_line);            <* 
       *> }                                                                                                                                          <* 
       *> break;                                                                                                                                     <*/
   }
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                       specialty-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;}

char
yUNIT_mode              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_exec)
{
   char        x_meth      [LEN_HUND]  = "";
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, "MODE"  , a_meth);
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, YUNIT_VOID, 0);
   /*---(dispaly)------------------------*/
   if (a_meth != NULL)  strncpy (x_meth, a_meth, LEN_HUND);
   if (strcmp (x_meth, "FORCED_FAIL") == 0) {
      YUNIT_FORCED = 1;
      yunit_disp_single  (TYPE_MODE  , a_line, a_seqn, "ENABLE FORCED FAILURE (pass=fail, fail=pass)");
   } else {
      YUNIT_FORCED = 0;
      yunit_disp_single  (TYPE_MODE  , a_line, a_seqn, "normal (a pass is a pass ;)");
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
yUNIT_code              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_code [LEN_RECD], char a_exec)
{
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, "CODE"  , a_desc);
   yunit_actual_accum (TYPE_STEP, YUNIT_VOID, 0);
   yunit_disp_double  (TYPE_CODE  , a_line, a_seqn, a_desc, "code"  , a_code);
   return 0;
}

char
yUNIT_local             (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_code [LEN_RECD], char a_exec)
{
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, "LOCAL" , a_desc);
   yunit_actual_accum (TYPE_STEP, YUNIT_VOID, 0);
   yunit_disp_double  (TYPE_LOCAL , a_line, a_seqn, a_desc, "local" , a_code);
   return 0;
}

char
yUNIT_load              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_recd [LEN_RECD], char a_exec)
{
   int       x_flags = 0;         /* stdin file flags                         */
   int       i       = 0;
   int       x_ch    = 0;
   char        x_meth      [LEN_LABEL] = "???";
   char        x_recd      [LEN_RECD]  = "";
   char        x_disp      [LEN_RECD]  = "";
   int         l           =   0;
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, "LOAD"  , a_desc);
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, YUNIT_VOID, 0);
   /*---(display)------------------------*/
   if (a_meth != NULL)   strncpy (x_meth, a_meth, LEN_RECD);
   if (a_recd != NULL)   strncpy (x_recd, a_recd, LEN_RECD);
   /*---(prepare data)-------------------*/
   strncpy (x_disp, x_recd, LEN_RECD);
   l = strlen (x_disp);
   for (i = 0; i < l; ++i)  if (x_disp [i] == '\n')  x_disp [i] = '¦';
   yunit_disp_double  (TYPE_LOAD  , a_line, a_seqn, a_desc, x_meth  , x_disp);
   /*---(fix record)-------------------*/
   l = strlen (x_recd) - 1;
   if (x_recd [l] == '¦') x_recd [l] = '\n';
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
      IF_FULL  yunit_printf  ("%s\n", x_recd);
      fclose  (yUNIT_stdin);
      /*---(reopen for next steps)-----*/
      yUNIT_stdin = fopen(STDIN, "r");
   }
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_file              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_recd [LEN_RECD], char a_exec)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_resu      =    0;
   FILE       *x_file      = NULL;
   int         x_error     =    0;
   char        x_msg       [LEN_FULL]  = "";
   /*---(display only)-------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, "FILE"  , a_desc);
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
   yunit_disp_double  (TYPE_FILE  , a_line, a_seqn, a_desc, "file" , a_recd);
   if (x_file == NULL)  yunit_printf ("      ERROR  : %s\n", x_msg);
   /*> yunit_header (TYPE_FILE, a_line, a_seqn, "FILE"  , a_desc, '-', '-');           <* 
    *> IF_STEP {                                                                       <* 
    *>    yunit_printf  ("\n");                                                        <* 
    *>    yunit_printf  ("%s\n", s_print);                                             <* 
    *>    sprintf (s_suffix , "      file   : %2då%.65sæ", strlen (a_recd), a_recd);   <* 
    *>    IF_FULL  yunit_printf  ("%s\n", s_suffix);                                   <* 
    *> }                                                                               <*/
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_append            (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_recd [LEN_RECD], char a_exec)
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
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, "FILE"  , a_desc);
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
         for (i = 0; i < l; ++i)  {  if (x_recd [i] == '²')  x_recd [i] = ' ';  }
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
   yunit_disp_double  (TYPE_APPEND, a_line, a_seqn, a_desc, "append" , a_recd);
   if (x_file == NULL)  yunit_printf ("      ERROR  : %s\n", x_msg);
   /*> yunit_header (TYPE_FILE, a_line, a_seqn, "APPEND", a_desc, '-', '-');           <* 
    *> IF_STEP {                                                                       <* 
    *>    yunit_printf  ("\n");                                                        <* 
    *>    yunit_printf  ("%s\n", s_print);                                             <* 
    *>    sprintf (s_suffix , "      recd   : %2då%.65sæ", strlen (a_recd), a_recd);   <* 
    *>    IF_FULL  yunit_printf  ("%s\n", s_suffix);                                   <* 
    *> }                                                                               <*/
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_system            (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_disp [LEN_RECD], char a_cmd [LEN_RECD], char a_exec)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;
   int         x_rc        =    0;
   char        x_resu      =    0;
   char        x_msg       [LEN_FULL]  = "";
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, "SYSTEM", a_desc);
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
   yunit_disp_double  (TYPE_SYSTEM, a_line, a_seqn, a_desc, "system" , a_disp);
   if (x_resu != YUNIT_SUCC)  yunit_printf ("      ERROR  : %s\n", x_msg);
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










