#include "yUNIT.h"
#include "yUNIT_priv.h"



/*====================------------------------------------====================*/
/*===----                       condition-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___CONDITION_______________o (void) {;}

char
yUNIT_cond              (int a_line, int a_seqn, char a_dittoing, char a_ditto, char a_share, char a_desc [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_type      = TYPE_COND;
   char        x_label     [LEN_TERSE] = "COND";
   char        x_line      [LEN_TERSE] = "";
   char        x_seqn      [LEN_TERSE] = "";
   char        x_desc      [LEN_LONG]  = "";
   char        x_note      [LEN_TERSE] = "";
   char        x_on        [LEN_TERSE] = "";
   char        x_off       [LEN_TERSE] = "";
   /*---(reset summary counters)---------*/
   yunit_actual_accum (TYPE_COND, 0, 0);
   /*---(identify type)------------------*/
   if      (strchr (YSTR_NUMBER, a_ditto) != NULL) {
      if (a_dittoing = 'y')                        { x_type = TYPE_DOND;  strcpy (x_label, "DOND");  sprintf (x_note, "(%c)", a_ditto);  }
      else                                         { x_type = TYPE_CCND;  strcpy (x_label, "CCND");  sprintf (x_note, "(%c)", a_ditto);  }
   }
   else if (strchr (YSTR_LOWER , a_share) != NULL) { x_type = TYPE_SOND;  strcpy (x_label, "SOND");  }
   else if (strchr (YSTR_UPPER , a_share) != NULL) { x_type = TYPE_GOND;  strcpy (x_label, "GOND");  }
   else if (strchr (YSTR_GREEK , a_share) != NULL) { x_type = TYPE_GOND;  strcpy (x_label, "GOND");  }
   else                                            { x_type = TYPE_COND;  strcpy (x_label, "COND");  }
   /*---(get colors)---------------------*/
   yunit_final_color (YUNIT_MONO, x_type, &x_on, NULL, &x_off, NULL, NULL);
   /*---(create message)-----------------*/
   switch (x_type) {
   case TYPE_COND :
      yunit_final_prep  (x_type, '-', a_line, a_seqn, a_desc, 85 - 13 - 7, YSTR_TEXT_LEF, 1, YSTR_COND, x_line, x_seqn, x_desc);
      sprintf (s_print, "  %-4.4s %-5.5s %s%-7.7s", x_label, x_seqn, x_desc, x_line);
      break;
   case TYPE_CCND : case TYPE_DOND :
      yunit_final_prep  (x_type, '-', a_line, a_seqn, a_desc, 61 - 16 - 7, YSTR_TEXT_LEF, 1, YSTR_COND, x_line, x_seqn, x_desc);
      sprintf (s_print, "  %s%-4.4s %-5.5s %s%s %s%-7.7s", x_on, x_label, x_seqn, x_note, x_off, x_desc, x_line);
      break;
   case TYPE_SOND : case TYPE_GOND :
      yunit_final_prep  (x_type, '-', a_line, a_seqn, a_desc, 85 - 13 - 7, YSTR_TEXT_LEF, 1, YSTR_COND, x_line, x_seqn, x_desc);
      sprintf (s_print, "  %s%-4.4s %-5.5s%s %s%-7.7s", x_on, x_label, x_seqn, x_note, x_off, x_desc, x_line);
      break;
   }
   /*---(print)--------------------------*/
   IF_COND   yunit_printf  ("\n%s\n", s_print);
   /*---(remove old stdin)---------------*/
   system ("/bin/rm -f yUNIT.stdin 2> /dev/null");
   yUNIT_stdin = NULL;
   /*---(complete)-----------------------*/
   return 0;
}

char
yUNIT_dnoc              (char a_exec)
{
   /*---(print message)----------------*/
   if (a_exec == 1)  yunit_final_footer (TYPE_DNOC);
   else              yunit_final_footer (TYPE_DNOD);
   IF_STEP   yunit_printf  ("\n");
   IF_COND   yunit_printf  ("%s\n", s_print);
   /*---(close stdin and remove)-------*/
   if (yUNIT_stdin != NULL) fclose (yUNIT_stdin);
   system ("/bin/rm -f yUNIT.stdin 2> /dev/null");
   /*---(complete)---------------------*/
   return;
}

char
yUNIT_group             (char a_desc [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_desc      [LEN_LONG]  = "";
   char        l           =    0;
   char        x_pre       =    0;
   char        x_suf       =    0;
   char        t           [LEN_FULL]  = "";
   /*---(print title)--------------------*/
   yunit_final_prep  (TYPE_GROUP, '-', 0, 0 , a_desc, 85 - 20, YSTR_TEXT_CEN, 3, YSTR_DASH, NULL, NULL, x_desc);
   IF_COND   yunit_printf ("\n");
   sprintf (s_print, "  GROUP ===---%s---===", x_desc);
   IF_COND   yunit_printf ("%s\n", s_print);
   /*---(complete)-----------------------*/
   return 0;
}

