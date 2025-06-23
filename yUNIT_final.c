#include "yUNIT.h"
#include "yUNIT_priv.h"



static  char s_seqn    [LEN_SHORT] = "";



char*
yunit_final_step        (int a_seqn)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_left      =    0;
   int         x_right     =    0;
   /*---(too low)------------------------*/
   if      (a_seqn <=   0)   strcpy (s_seqn, "--");
   /*---(too low)------------------------*/
   else if (a_seqn >  676)   strcpy (s_seqn, "**");
   /*---(real)---------------------------*/
   else {
      --a_seqn;
      x_left  = a_seqn / 26;
      x_right = a_seqn % 26;
      sprintf (s_seqn, "%c%c", x_left + 'a', x_right + 'a');
   }
   /*---(complete)-----------------------*/
   return s_seqn;
}

char
yunit_final_prep        (char a_type, char a_share, int a_line, int a_seqn, char a_prefix [LEN_TERSE], char a_desc [LEN_LONG], char a_max, char a_align, char a_gap, char *a_fill, char r_line [LEN_TERSE], char r_seqn [LEN_TERSE], char r_desc [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   int         l           =    0;
   int         x_pre       =    0;
   int         x_suf       =    0;
   char        x_trunc     [LEN_LONG]  = "";
   char        x_select    [LEN_LONG]  = "";
   char        x_desc      [LEN_LONG]  = "????";
   char       *x_beg       = NULL;
   char       *x_end       = NULL;
   char        x_left      =    0;
   char        n           =    0;
   char        x_temp      [LEN_LONG]  = "";
   char        x_off       =    0;
   char        x_final     [LEN_LONG]  = "";
   /*---(defaults)-----------------------*/
   if (r_line != NULL)    strcpy (r_line, "");
   if (r_seqn != NULL)    strcpy (r_seqn, "");
   if (r_desc != NULL)    strcpy (r_desc, "");
   /*---(defense)------------------------*/
   if      (a_desc == NULL)      strcpy  (x_desc, "(null)");
   else if (a_desc [0] == '\0')  strcpy  (x_desc, "(empty)");
   else                          strlcpy (x_desc, a_desc, LEN_LONG);
   /*---(handle line)--------------------*/
   if (r_line != NULL) {
      if      (a_line <=     0)   strcpy (r_line, "[-----]");
      else if (a_line >  99999)   strcpy (r_line, "[*****]");
      else if (strchr ("-" YSTR_LOWER, a_share) != NULL)  {
         if (r_line != NULL)  sprintf (r_line, "[%05d]", a_line);
      } else {
         if (r_line != NULL)  sprintf (r_line, "º%05d»", a_line);
      }
   }
   /*---(handle sequence)----------------*/
   if (a_seqn <     0)   a_seqn = 0;
   switch (a_type) {
   case TYPE_SCRP   : case TYPE_SHARED : case TYPE_GLOBAL : case TYPE_CONFIG :
      if (r_seqn != NULL) {
         if      (a_seqn <=    0)   strcpy  (r_seqn, "[--]");
         else if (a_seqn >    99)   strcpy  (r_seqn, "[**]");
         else                       sprintf (r_seqn, "[%02d]", a_seqn);
      }
      break;
   case TYPE_COND   : case TYPE_CCND   : case TYPE_DOND   : case TYPE_SOND   : case TYPE_GOND   :
      if (r_seqn != NULL) {
         if      (a_seqn <=    0)   strcpy  (r_seqn, "[---]");
         else if (a_seqn >   999)   strcpy  (r_seqn, "[***]");
         else                       sprintf (r_seqn, "[%03d]", a_seqn);
      }
      break;
   case TYPE_STEP   : case TYPE_DISP   : case TYPE_LOCAL  : case TYPE_CODE   : case TYPE_LOAD   :
   case TYPE_MODE   : case TYPE_FILE   : case TYPE_APPEND : case TYPE_SYSTEM :
      if (r_seqn != NULL)  sprintf (r_seqn, yunit_final_step (a_seqn));
      break;
   }
   /*---(pull select)----------------------------*/
   /*> printf ("desc %2d, %s\n", strlen (x_desc), x_desc);                            <*/
   ystrutrim (x_desc, LEN_LONG);
   /*> printf ("desc %2d, %s\n", strlen (x_desc), x_desc);                            <*/
   x_beg = strchr (x_desc, 'å');
   /*> printf ("beg  %p\n", x_beg);                                                   <*/
   if (x_beg != NULL) {
      x_end = strchr (x_beg, 'æ');
      /*> printf ("end  %p\n", x_end);                                                <*/
      if (x_end != NULL) {
         strncpy (x_select, x_desc, x_end - x_beg + 1);
         ystrutrim (x_select, LEN_LONG);
         strncpy (x_desc, x_end + 1, LEN_LONG);
         ystrutrim (x_desc  , LEN_LONG);
      }
   }
   /*---(fix ellipsis)---------------------------*/
   n = 0;
   if      (strncmp (x_desc, "... ", 4) == 0)   n = 4;
   else if (strncmp (x_desc, "..." , 3) == 0)   n = 3;
   else                                         n = 0;
   /*---(handle special DOND)--------------------*/
   if (a_type == TYPE_DOND)  sprintf (x_trunc, "[[ %s ]]", x_desc + n);
   else                      sprintf (x_trunc, x_desc + n);
   /*---(concat description)---------------------*/
   if (strcmp (a_prefix, "") != 0) {
      if (strcmp (x_select, "") != 0) snprintf (x_temp, LEN_LONG, "%s %s %s", a_prefix, x_select, x_trunc);
      else                            snprintf (x_temp, LEN_LONG, "%s %s"   , a_prefix, x_trunc);
   } else {
      if (strcmp (x_select, "") != 0) snprintf (x_temp, LEN_LONG, "%s %s"   , x_select, x_trunc);
      else                            snprintf (x_temp, LEN_LONG, "%s"      , x_trunc);
   }
   /*---(overrun)------------------------*/
   l     = strlen (x_temp);
   if (a_align == YSTR_TEXT_CEN)    n = a_gap * 2;
   else                             n = a_gap;
   if (l + n > a_max)  { x_temp [a_max - n - 0] = '\0'; x_temp [a_max - n - 1] = '>'; x_temp [a_max - n - 2] = '>'; }
   l     = strlen (x_temp);
   /*---(sizing)-------------------------*/
   x_left  = a_max - l;
   if (x_left < 0)  x_left = 0;
   x_pre   = x_left / 2;
   if (x_pre < 0)  x_pre = 0;
   x_suf   = x_left - x_pre;
   if (x_suf < 0)  x_suf = 0;
   /*---(adjust)-------------------------*/
   x_pre  -= a_gap;
   if (x_pre  < 0)  x_pre  = 0;
   x_suf  -= a_gap;
   if (x_suf  < 0)  x_suf  = 0;
   x_left -= a_gap;
   if (x_left < 0)  x_left = 0;
   /*---(fill)---------------------------*/
   switch (a_align) {
   case YSTR_TEXT_RIG :
      sprintf (x_final, "%*.*s%*.*s%s", x_left, x_left, a_fill, a_gap, a_gap, YSTR_EMPTY, x_temp);
      break;
   case YSTR_TEXT_CEN :
      x_off   = strlen (x_temp) + x_pre + (a_gap * 2);
      sprintf (x_final, "%*.*s%*.*s%s%*.*s%*.*s", x_pre, x_pre, a_fill, a_gap, a_gap, YSTR_EMPTY, x_temp, a_gap, a_gap, YSTR_EMPTY, x_suf, x_suf, a_fill + x_off);
      break;
   case YSTR_TEXT_LEF :  default :
      x_off   = strlen (x_temp) + a_gap;
      sprintf (x_final, "%s%*.*s%*.*s", x_temp, a_gap, a_gap, YSTR_EMPTY, x_left, x_left, a_fill + x_off);
      break;
   }
   /*---(save-back)----------------------*/
   if (r_desc != NULL)  strlcpy (r_desc, x_final, LEN_LONG);
   /*---(complete)-----------------------*/
   return 0;
}

char
yunit_final_color       (char a_mono, char a_type, char r_on [LEN_LABEL], char r_on2 [LEN_LABEL], char r_off [LEN_LABEL], char r_note [LEN_TERSE], char r_test [LEN_DESC])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_on        [LEN_LABEL] = "";
   char        x_on2       [LEN_LABEL] = "";
   char        x_off       [LEN_LABEL] = "";
   char        x_note      [LEN_TERSE] = "";
   char        x_test      [LEN_DESC]  = "";
   char        x_resu      = YUNIT_VOID;
   /*---(defaults)-----------------------*/
   if (r_on   != NULL)   strcpy (r_on  , "");
   if (r_on2  != NULL)   strcpy (r_on2 , "");
   if (r_off  != NULL)   strcpy (r_off , "");
   if (r_note != NULL)   strcpy (r_note, "");
   if (r_test != NULL)   strcpy (r_test, "  one    two  ");
   /*---(headings)-----------------------*/
   switch (a_type) {
   case TYPE_SCRP  : case TYPE_SECT  : case TYPE_GROUP :
      return 0;
      break;
   case TYPE_DINU  : case TYPE_DRCS  : case TYPE_DNOD  : case TYPE_DISP  :
      return 0;
      break;
   }
   /*---(non-mono)-----------------------*/
   strcpy (x_off, BACK_OFF);
   /*---(scripts)------------------------*/
   switch (a_type) {
   case TYPE_COND  :
      strcpy (x_on , BACK_BRN);
      break;
   case TYPE_CCND  : case TYPE_DOND  :
      strcpy (x_on , BACK_PUR);
      break;
   }
   /*---(shared)-------------------------*/
   switch (a_type) {
   case TYPE_SHARED : case TYPE_DERAHS : case TYPE_SOND   :
      strcpy (x_on , BACK_CRI);
      break;
   case TYPE_GLOBAL : case TYPE_LABOLG : case TYPE_GOND   :
   case TYPE_CONFIG : case TYPE_GIFNOC :
      strcpy (x_on , BACK_BLU);
      break;
   }
   /*---(judgement)----------------------*/
   switch (a_type) {
   case TYPE_TINU  : case TYPE_PRCS  : case TYPE_DNOC  :
      yunit_actual_last (a_type, &x_resu, NULL);
      if      (x_resu == YUNIT_VOID)  strcpy (x_on , BACK_BRN);
      else if (x_resu == YUNIT_FAIL)  strcpy (x_on , BACK_RED);
      else if (x_resu == YUNIT_WARN)  strcpy (x_on , BACK_YEL);
      else                            strcpy (x_on , BACK_GRN);
      break;
   }
   /*---(special)------------------------*/
   switch (a_type) {
   case TYPE_LOCAL  : case TYPE_CODE   : case TYPE_LOAD   : case TYPE_MODE   :
      strcpy (x_on , BACK_BRN);
      strcpy (x_on2, BACK_GRN);
      switch (a_type) {
      case TYPE_LOCAL  : strcpy (x_note, "LOCAL" );  break;
      case TYPE_CODE   : strcpy (x_note, "CODE"  );  break;
      case TYPE_LOAD   : strcpy (x_note, "LOAD"  );  break;
      case TYPE_MODE   : strcpy (x_note, "MODE"  );  break;
      }
   }
   /*---(execution)----------------------*/
   switch (a_type) {
   case TYPE_SYSTEM : case TYPE_STEP   : case TYPE_FILE  : case TYPE_APPEND  :
      yunit_actual_last (a_type, &x_resu, NULL);
      switch (x_resu) {
      case YUNIT_SUCC  :  strcpy (x_note, "PASS" );  strcpy (x_on, BACK_GRN);  strcpy (x_on2, BACK_GRN);  break;
      case YUNIT_FAIL  :  strcpy (x_note, "FAIL" );  strcpy (x_on, BACK_RED);  strcpy (x_on2, BACK_RED);  break;
      case YUNIT_FSUCC :  strcpy (x_note, "!PASS");  strcpy (x_on, BACK_RED);  strcpy (x_on2, BACK_GRN);  break;
      case YUNIT_FFAIL :  strcpy (x_note, "!FAIL");  strcpy (x_on, BACK_GRN);  strcpy (x_on2, BACK_RED);  break;
      case YUNIT_VOID  :  strcpy (x_note, "----" );  strcpy (x_on, BACK_BRN);  strcpy (x_on2, BACK_BRN);  break;
      default          :  strcpy (x_note, "WARN" );  strcpy (x_on, BACK_YEL);  strcpy (x_on2, BACK_YEL);  break;
      }
      switch (a_type) {  /* override note */
      case TYPE_SYSTEM : /* strcpy (x_note, "SYSTEM"); */  strcpy (x_on, BACK_BRN);  break;
      case TYPE_FILE   : /* strcpy (x_note, "FILE"  ); */  strcpy (x_on, BACK_BRN);  break;
      case TYPE_APPEND : /* strcpy (x_note, "APPEND"); */  strcpy (x_on, BACK_BRN);  break;
      }
   }
   /*---(mono-override)------------------*/
   if (a_mono == 'y') {
      strcpy (x_on  , "");
      strcpy (x_on2 , "");
      strcpy (x_off , "");
   }
   /*---(for unit testing)---------------*/
   if (r_test != NULL) {
      if (strcmp (x_on2, "") == 0)  sprintf (r_test, "%s  one    two  %s"  , x_on, x_off);
      else                          sprintf (r_test, "%s  one  %s  two  %s", x_on, x_on2, x_off);
   }
   /*---(save-back)----------------------*/
   if (r_on   != NULL)   strcpy (r_on  , x_on);
   if (r_on2  != NULL)   strcpy (r_on2 , x_on2);
   if (r_off  != NULL)   strcpy (r_off , x_off);
   if (r_note != NULL)   strcpy (r_note, x_note);
   /*---(complete)-----------------------*/
   return 1;
}

char*
yunit_final_footer      (char a_type)
{
   char        x_on        [LEN_LABEL] = "";
   char        x_off       [LEN_LABEL] = "";
   char        x_foot      [LEN_HUND]  = "";
   char        x_unused    =   '-';
   yunit_final_color (YUNIT_MONO, a_type, x_on, NULL, x_off, NULL, NULL);
   switch (a_type) {
   case TYPE_TINU  : case TYPE_DINU  :
      strlcpy (x_foot, yunit_actual_footer (a_type, &x_unused), LEN_HUND);
      /*> if (a_type == TYPE_TINU && x_unused == 'y')  strcpy (x_on, BACK_YEL);       <*/
      sprintf (s_print, "%s%s%s", x_on, x_foot, x_off);
      break;
   case TYPE_PRCS  : case TYPE_DRCS  :
      strlcpy (x_foot, yunit_actual_footer (a_type, &x_unused), LEN_HUND);
      /*> if (a_type == TYPE_PRCS && x_unused == 'y')  strcpy (x_on, BACK_YEL);       <*/
      sprintf (s_print, "  %s%s%s", x_on, x_foot, x_off);
      break;
   case TYPE_DNOC  : case TYPE_DNOD  :
      strlcpy (x_foot, yunit_actual_footer (a_type, &x_unused), LEN_HUND);
      /*> if (a_type == TYPE_DNOC && x_unused == 'y')  strcpy (x_on, BACK_YEL);       <*/
      sprintf (s_print, "     %s%s%s", x_on, x_foot, x_off);
      break;
   }
   /*---(complete)-----------------------*/
   return s_print;
}


