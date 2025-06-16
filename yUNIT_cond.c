#include "yUNIT.h"
#include "yUNIT_priv.h"



/*====================------------------------------------====================*/
/*===----                       condition-level                        ----===*/
/*====================------------------------------------====================*/
static void      o___CONDITION_______________o (void) {;}

char
yunit_cond_type         (char a_dittoing, char a_ditto, char a_dtarget, char a_share, char r_label [LEN_TERSE], char r_note [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_type      = TYPE_COND;
   char        x_label     [LEN_TERSE] = "COND";
   char        x_ditto     [LEN_TERSE] = "";
   char        x_share     [LEN_TERSE] = "";
   char        x_note      [LEN_TERSE] = "";
   /*---(default)------------------------*/
   if (r_label != NULL)  strcpy (r_label, "");
   if (r_note  != NULL)  strcpy (r_note , "");
   /*---(identify type)------------------*/
   if      (strchr (YSTR_LOWER , a_share) != NULL)                   { x_type = TYPE_SOND;  strcpy (x_label, "SOND"); sprintf (x_share, "[%c>", a_share);   }
   else if (strchr (YSTR_UPPER , a_share) != NULL)                   { x_type = TYPE_GOND;  strcpy (x_label, "GOND"); sprintf (x_share, "[%c>", a_share);   }
   else if (strchr (YSTR_GREEK , a_share) != NULL)                   { x_type = TYPE_GOND;  strcpy (x_label, "GOND"); sprintf (x_share, "[%c>", a_share);   }
   else                                                              { x_type = TYPE_COND;  strcpy (x_label, "COND"); }
   /*---(handle ditto)-------------------*/
   if (a_dittoing == 'y' && strchr (YSTR_NUMBER, a_dtarget) != NULL) { sprintf (x_ditto, "(%c)", a_dtarget); }
   else if (strchr (YSTR_NUMBER, a_ditto) != NULL)                   { sprintf (x_ditto, "(%c)", a_ditto);   }
   /*---(update type)--------------------*/
   if      (strchr (YSTR_NUMBER, a_dtarget) != NULL) {
      switch (x_type) {
      case  TYPE_COND :  x_type = TYPE_DOND;  strcpy (x_label, "DOND");  break;
      case  TYPE_SOND :                       strcpy (x_label, "SDON");  break;
      case  TYPE_GOND :                       strcpy (x_label, "GDON");  break;
      }
   }
   else if (strchr (YSTR_NUMBER, a_ditto)   != NULL) {
      switch (x_type) {
      case  TYPE_COND :  x_type = TYPE_CCND;  strcpy (x_label, "CCND");  break;
      case  TYPE_SOND :                       strcpy (x_label, "SCND");  break;
      case  TYPE_GOND :                       strcpy (x_label, "GCND");  break;
      }
   }
   /*---(combine)------------------------*/
   strlcpy (x_note, x_share, LEN_TERSE);
   if (strcmp (x_ditto, "") != 0) {
      if (strcmp (x_share, "") != 0)   strlcat (x_note, " ", LEN_TERSE);
      strlcat (x_note, x_ditto, LEN_TERSE);
   }
   /*> if (a_dittoing == 'y' && strchr (YSTR_NUMBER, a_dtarget) != NULL) { x_type = TYPE_DOND;  strcpy (x_label, "DOND"); sprintf (x_note, "(%c)", a_dtarget); }   <* 
    *> else if (strchr (YSTR_NUMBER, a_ditto) != NULL)                   { x_type = TYPE_CCND;  strcpy (x_label, "CCND"); sprintf (x_note, "(%c)", a_ditto);   }   <*/
   /*> if   (strchr (YSTR_NUMBER, a_dtarget) != NULL)      sprintf (x_note, "(%c)", a_dtarget);   <* 
    *> if   (strchr (YSTR_NUMBER, a_ditto  ) != NULL)      sprintf (x_note, "(%c)", a_ditto);     <*/
   /*---(save-back)----------------------*/
   if (r_label != NULL)  strlcpy (r_label, x_label, LEN_TERSE);
   if (r_note  != NULL)  strlcpy (r_note , x_note , LEN_TERSE);
   /*---(complete)-----------------------*/
   return x_type;
}

char
yUNIT_cond              (int a_line, int a_seqn, char a_dittoing, char a_ditto, char a_dtarget, char a_share, char a_desc [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_type      = TYPE_COND;
   char        x_label     [LEN_TERSE] = "COND";
   char        x_note      [LEN_TERSE] = "";
   char        x_line      [LEN_TERSE] = "";
   char        x_seqn      [LEN_TERSE] = "";
   char        x_desc      [LEN_LONG]  = "(null)";
   char        x_final     [LEN_LONG]  = "";
   char        x_on        [LEN_LABEL] = "";
   char        x_off       [LEN_LABEL] = "";
   char        t           [LEN_LONG]  = "";
   /*---(default)------------------------*/
   if (a_desc  != NULL)   strlcpy (x_desc, a_desc, LEN_LONG);
   /*---(reset summary counters)---------*/
   yunit_actual_accum (TYPE_COND, 0, 0);
   /*---(identify type)------------------*/
   x_type = yunit_cond_type (a_dittoing, a_ditto, a_dtarget, a_share, x_label, x_note);
   /*---(get colors)---------------------*/
   yunit_final_color (YUNIT_MONO, x_type, &x_on, NULL, &x_off, NULL, NULL);
   /*---(create message)-----------------*/
   switch (x_type) {
   case TYPE_COND :
      strlcpy (t, x_desc, LEN_LONG);
      break;
   case TYPE_CCND : case TYPE_DOND :
      if (x_type == TYPE_DOND)  sprintf (t, "%s [ %s ]", x_note, x_desc);
      else                      sprintf (t, "%s %s"    , x_note, x_desc);
      break;
   case TYPE_SOND : case TYPE_GOND :
      if (strcmp (x_note, "") == 0)  strlcpy (t, x_desc, LEN_LONG);
      else                           sprintf (t, "%s %s", x_note, x_desc);
      break;
   }
   yunit_final_prep  (x_type, a_share, a_line, a_seqn, t, 85 - 13 - 7, YSTR_TEXT_LEF, 1, YSTR_COND, x_line, x_seqn, x_final);
   sprintf (s_print, "  %s%-4.4s %-5.5s %s%-7.7s%s", x_on, x_label, x_seqn, x_final, x_line, x_off);
   /*---(print)--------------------------*/
   IF_COND   yUNIT_printf  ("\n%s\n", s_print);
   /*---(remove old stdin)---------------*/
   system ("/bin/rm -f yUNIT.stdin 2> /dev/null");
   yUNIT_stdin = NULL;
   /*---(complete)-----------------------*/
   return 0;
}

char
yUNIT_dnoc              (char a_exec)
{
   /*---(create message)---------------*/
   if (a_exec == 1)  yunit_final_footer (TYPE_DNOC);
   else              yunit_final_footer (TYPE_DNOD);
   /*---(output message)---------------*/
   IF_STEP {
      if (a_exec == 1) yUNIT_printf  ("\n%s\n", s_print);
      else             yUNIT_printf  ("%s\n"  , s_print);
   }
   else if (a_exec == 1 && myUNIT.level == YUNIT_COND)  yUNIT_printf  ("%s\n", s_print);
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
   IF_COND   yUNIT_printf ("\n");
   sprintf (s_print, "  GROUP ===---%s---===", x_desc);
   IF_COND   yUNIT_printf ("%s\n", s_print);
   /*---(complete)-----------------------*/
   return 0;
}

