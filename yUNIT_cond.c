#include "yUNIT.h"
#include "yUNIT_priv.h"



/*====================------------------------------------====================*/
/*===----                       condition-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___CONDITION_______________o (void) {;}

char
yUNIT_cond              (int a_line, int a_seqn, char a_share, cchar *a_desc)
{
   char        t           [LEN_TERSE] = "";
   /*---(reset summary counters)-------*/
   UNIT_COND++;
   SCRP_COND++;
   COND_TEST = COND_PASS = COND_FAIL = COND_BADD = COND_VOID = 0;
   /*---(print message)----------------*/
   if (a_share == '-') {
      yunit_header (TYPE_COND, a_line, a_seqn, NULL, a_desc);
   } else if (a_share >= ' ' && a_share <= ')') {
      sprintf (t, "(%c)", a_share - ' ' + '0');
      yunit_header (TYPE_CCND, a_line, a_seqn, t   , a_desc);
   } else if (strchr (YSTR_NUMBER, a_share) != NULL) {
      sprintf (t, "(%c)", a_share);
      yunit_header (TYPE_DOND, a_line, a_seqn, t   , a_desc);
   } else if (a_share == tolower (a_share)) {
      yunit_header (TYPE_SOND, a_line, a_seqn, NULL, a_desc);
   } else {
      yunit_header (TYPE_GOND, a_line, a_seqn, NULL, a_desc);
   }
   IF_COND   {
      yunit_printf  ("\n");
      yunit_printf  ("%s\n", s_print);
   }
   /*---(remove old stdin)-------------*/
   system ("/bin/rm -f yUNIT.stdin 2> /dev/null");
   yUNIT_stdin = NULL;
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_dnoc              (cchar a_exec)
{
   /*---(print message)----------------*/
   if (a_exec == 1) {
      yunit_footer (TYPE_DNOC);
      IF_STEP   yunit_printf  ("\n");
      IF_COND   yunit_printf  ("%s\n", s_print);
   }
   else              yunit_footer (TYPE_DNOD);
   /*---(close stdin and remove)-------*/
   if (yUNIT_stdin != NULL) fclose (yUNIT_stdin);
   system ("/bin/rm -f yUNIT.stdin 2> /dev/null");
   /*---(complete)---------------------*/
   return;
}

char
yUNIT_group             (char *a_desc)
{
   /*---(print title)------------------*/
   yunit_header (TYPE_GROUP, 0, 0, NULL, a_desc);
   IF_COND   yunit_printf ("\n");
   IF_COND   yunit_printf ("%s\n", s_print);
   return 0;
}

