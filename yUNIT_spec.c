#include "yUNIT.h"
#include "yUNIT_priv.h"



/*====================------------------------------------====================*/
/*===----                       specialty-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;}

void               /*  rerturn = (none)                                       */
yUNIT_mode (       /*  PURPOSE = ENABLE FORCED FAILURES                       */
      void     *a_unit,           /*  unit test object                        */
      int       a_line,           /*  reference number to script file line    */
      int       a_seqn,           /*  sequence number                         */
      char     *a_desc)           /*  short description                       */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   int seq1 = (a_seqn / 26);
   int seq2 = (a_seqn % 26) + 1;
   if (seq1 == 0) {
      seq1  = seq2 - 1;
      seq2  = ' ' - 96;
   }
   char   x_on  [20] = "";
   char   x_off [20] = "";
   if (o->is_eterm == 'y') {
      strcpy(x_on , "\e[46m");
      strcpy(x_off, "\e[0m");
   }
   if (strcmp(a_desc, "FORCED_FAIL") == 0) {
      o->is_forced_fail = 1;
      DISP_STEP
         fprintf(yUNIT_out, "\n  %s%c%c) MODE  %s : ENABLE FORCED FAILURE (pass=fail, fail=pass) .  .  .  .  .  .  [%05i]\n",
               x_on, seq1 + 96, seq2 + 96, x_off, a_line);
   } else {
      o->is_forced_fail = 0;
      DISP_STEP
         fprintf(yUNIT_out, "\n  %s%c%c) MODE  %s : normal (a pass is a pass ;)   .  .  .  .  .  .  .  .  .  .  .  [%05i]\n",
               x_on, seq1 + 96, seq2 + 96, x_off, a_line);
   }
   /*---(complete)---------------------*/
   return;
}


void               /*  rerturn = (none)                                       */
yUNIT_code (       /*  PURPOSE = describe manual code lines                   */
      void     *a_unit,           /*  unit test object                        */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_code)           /* actual code line                         */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   /*---(prepare sequence)---------------*/
   int seq1 = (a_seqn / 26);
   int seq2 = (a_seqn % 26) + 1;
   if (seq1 == 0) {
      seq1  = seq2 - 1;
      seq2  = ' ' - 96;
   }
   /*---(prepare color)------------------*/
   char   x_on  [20] = "";
   char   x_off [20] = "";
   if (o->is_eterm == 'y') {
      strcpy (x_on , "\e[46m");
      strcpy (x_off, "\e[0m");
   }
   /*---(dispaly)------------------------*/
   DISP_STEP {
      char  x_header[LEN_HEAD] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      fprintf(yUNIT_out, "\n  %s%c%c) CODE  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      fprintf(yUNIT_out, " %62.62s [%05d]\n", x_header, a_line);
      fprintf(yUNIT_out, "      code   : %-70.70s\n", a_code);
   }
   /*---(complete)---------------------*/
   return;
}

void
yUNIT_load (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_meth,           /* input method (stdin, ncurses, STDIN)     */
      char     *a_recd)           /* record to load                           */
{
   /*> printf ("recd :%s:\n", a_recd);                                                <*/
   int       x_flags = 0;         /* stdin file flags                         */
   int       i       = 0;
   int       x_ch    = 0;
   tUNIT    *o       = (tUNIT *) a_unit;
   int seq1 = (a_seqn / 26);
   int seq2 = (a_seqn % 26) + 1;
   if (seq1 == 0) {
      seq1  = seq2 - 1;
      seq2  = ' ' - 96;
   }
   /*---(prepare color)------------------*/
   char   x_on  [20] = "";
   char   x_off [20] = "";
   if (o->is_eterm == 'y') {
      strcpy (x_on , "\e[46m");
      strcpy (x_off, "\e[0m");
   }
   /*---(display)------------------------*/
   DISP_STEP {
      char  x_header[LEN_HEAD] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      fprintf(yUNIT_out, "\n  %s%c%c) CODE  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      fprintf(yUNIT_out, " %62.62s [%05d]\n", x_header, a_line);
      fprintf(yUNIT_out, "      load   : (%-10.10s) %-.55s\n", a_meth, a_recd);
   }
   /*---(normal stdin)-----------------*/
   if (strcmp (a_meth, "stdin") == 0) {
      /*---(clear existing)------------*/
      /*> x_flags     = fcntl  (stdin, F_GETFL, 0);                                   <* 
       *> fcntl (stdin, F_SETFL, x_flags | O_NONBLOCK);                               <* 
       *> printf ("clearing stdin...\n");                                             <* 
       *> while (getc (stdin) != -1);   /+ clear existing  +/                         <* 
       *> fcntl  (stdin, F_SETFL, x_flags);                                           <*/
      /*---(load new)------------------*/
      /*> printf ("loading stdin...\n");                                              <*/
      for (i = strlen (a_recd) - 1; i >= 0; --i) {
         ungetc (a_recd [i], stdin);
      }
   }
   /*---(ncurses input)----------------*/
   else if (strcmp (a_meth, "ncurses") == 0) {
      while (x_ch = getch ()) {
         /*> fprintf (yUNIT_out, "pulled %3d\n", x_ch);                                           <*/
         if (x_ch < 0)  break;
         /* clear existing  */
      }
      /*> fprintf (yUNIT_out, "placing <<%s>>\n", a_recd);                                        <*/
      if (strlen (a_recd) > 0) {
         for (i = strlen (a_recd) - 1; i >= 0; --i) {
            /*> fprintf (yUNIT_out, "ungetch %3d = %c\n", a_recd[i], a_recd[i]);                  <*/
            ungetch (a_recd [i]);
         }
      }
   }
   /*---(file input)-------------------*/
   else {
      /*---(close it in case)----------*/
      /*> fprintf (yUNIT_out, "yUNIT_load 1.0 : %p\n", yUNIT_stdin);                              <*/
      if (yUNIT_stdin != NULL) fclose(yUNIT_stdin);
      /*> fprintf (yUNIT_out, "yUNIT_load 2.0 : %p\n", yUNIT_stdin);                              <*/
      /*---(write new data)------------*/
      yUNIT_stdin = fopen(STDIN, "a");
      /*> fprintf (yUNIT_out, "yUNIT_load 3.0 : %p\n", yUNIT_stdin);                              <*/
      /*> fprintf (yUNIT_out, "yUNIT_load 3.5 : %s\n", a_recd);                                   <*/
      fprintf (yUNIT_stdin, "%s\n", a_recd);
      fclose  (yUNIT_stdin);
      /*> fprintf (yUNIT_out, "yUNIT_load 4.0 : %p\n", yUNIT_stdin);                              <*/
      /*---(reopen for next steps)-----*/
      yUNIT_stdin = fopen(STDIN, "r");
      /*> fprintf (yUNIT_out, "yUNIT_load 5.0 : %p\n", yUNIT_stdin);                              <*/
   }
   /*> fprintf (yUNIT_out, "done with load\n");                                                   <*/
   /*---(complete)---------------------*/
   return;
}

void
yUNIT_sys    (
      void     *a_unit,           /* unit test object                         */
      int       a_line,           /* reference number to script file line     */
      int       a_seqn,           /* sequence number                          */
      char     *a_desc,           /* short description                        */
      char     *a_cmd )           /* record to execute                        */
{
   tUNIT    *o       = (tUNIT *) a_unit;
   int seq1 = (a_seqn / 26);
   int seq2 = (a_seqn % 26) + 1;
   if (seq1 == 0) {
      seq1  = seq2 - 1;
      seq2  = ' ' - 96;
   }
   /*---(prepare color)------------------*/
   char   x_on  [20] = "";
   char   x_off [20] = "";
   if (o->is_eterm == 'y') {
      strcpy (x_on , "\e[46m");
      strcpy (x_off, "\e[0m");
   }
   /*---(display)------------------------*/
   /*> fprintf (yUNIT_out, "yUNIT_load 0.0 : %p\n", yUNIT_stdin);                                 <*/
   DISP_STEP {
      char  x_header[LEN_HEAD] = "";
      strncat(x_header, a_desc, 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);
      fprintf(yUNIT_out, "\n  %s%c%c) CODE  %s :",
            x_on, seq1 + 96, seq2 + 96, x_off);
      fprintf(yUNIT_out, " %62.62s [%05d]\n", x_header, a_line);
      fprintf(yUNIT_out, "      sys    : %-.65s\n", a_cmd);
   }
   /*---(run system command)-----------*/
   char     x_sys [LEN_RECD];
   sprintf (x_sys, "%s > /tmp/yUNIT_sys_verb.tmp", a_cmd);
   /*> fprintf (yUNIT_out, "SYS COMMAND : %s\n", x_sys);                                          <*/
   system (x_sys);
   /*---(open file)--------------------*/
   FILE  *f;
   f = fopen ("/tmp/yUNIT_sys_verb.tmp", "r");
   if (f == NULL) return -1;
   /*---(read one line)----------------*/
   char        x_text      [LEN_RECD] = "";
   int         x_len       = 0;
   fgets (x_text, LEN_RECD, f);
   x_len = strlen (x_text);
   x_text [--x_len] = '\0';
   strcpy (yUNIT_systext, x_text);
   /*---(close)------------------------*/
   fclose (f);
   /*---(complete)---------------------*/
   return;
}
