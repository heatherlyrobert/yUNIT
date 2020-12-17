#include "yUNIT.h"
#include "yUNIT_priv.h"



/*====================------------------------------------====================*/
/*===----                       condition-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___CONDITION_______________o (void) {;}

char
yUNIT_cond              (int a_line, int a_seqn, cchar *a_desc)
{
   /*---(reset summary counters)-------*/
   COND_TEST = COND_PASS = COND_FAIL = COND_BADD = COND_VOID = 0;
   /*---(print message)----------------*/
   IF_COND   {
      fprintf (yUNIT_out, "\n");
      yunit_header (TYPE_COND, a_line, a_seqn, NULL, a_desc);
      fprintf (yUNIT_out, "%s\n", s_print);
   }
   fprintf (yUNIT_out, "\n");
   /*---(remove old stdin)-------------*/
   system ("/bin/rm -f yUNIT.stdin 2> /dev/null");
   yUNIT_stdin = NULL;
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_dnoc              (void)
{
   /*---(print message)----------------*/
   /*> IF_STEP   fprintf(yUNIT_out, "\n");                                            <*/
   IF_COND   {
      yunit_footer (TYPE_DNOC);
      fprintf (yUNIT_out, "%s\n", s_print);
   }
   IF_FULL   fprintf (yUNIT_out, "\n");
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
   IF_COND   fprintf(yUNIT_out, "\n");
   IF_COND   fprintf(yUNIT_out, "%s\n", s_print);
   return 0;
}

