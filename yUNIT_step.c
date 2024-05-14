#include "yUNIT.h"
#include "yUNIT_priv.h"



static  int  s_resu    =  0;
static  int  s_code    =  0;
static  char s_seqn    [LEN_SHORT] = "";
static  char s_mask    [LEN_RECD]  = "";



/*====================------------------------------------====================*/
/*===----                        support functions                     ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char*
yunit_seqn              (int a_seqn)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_left      =    0;
   int         x_right     =    0;
   /*---(defense)------------------------*/
   if (a_seqn <   1)  a_seqn = 1;
   if (a_seqn > 675)  a_seqn = 675;
   /*---(calculate)----------------------*/
   --a_seqn;
   x_left  = a_seqn / 26;
   x_right = a_seqn % 26;
   /*---(make string)--------------------*/
   sprintf (s_seqn, "%c%c", x_left + 'a', x_right + 'a');
   /*---(complete)-----------------------*/
   return s_seqn;
}

char
yunit_colors            (char a_type, char *a_on, char *a_on2, char *a_off)
{
   /*---(defaults)-----------------------*/
   if (a_on  == NULL)        return -1;
   if (a_off == NULL)        return -2;
   strcpy (a_on , "");
   if (a_on2 != NULL)  strcpy (a_off, "");
   strcpy (a_off, "");
   if (myUNIT.mono)  return  0;
   strcpy (a_off , BACK_OFF);
   switch (a_type) {
   case TYPE_SCRP  : case TYPE_SECT  : case TYPE_COND  : case TYPE_GROUP :
      break;
   case TYPE_CCND  :
      strcpy (a_on , BACK_CYN);
      break;
   case TYPE_DOND  :
      strcpy (a_on , BACK_CYN);
      break;
   case TYPE_SHARE : case TYPE_ERAHS : case TYPE_SOND  :
      strcpy (a_on , BACK_MAG);
      break;
   case TYPE_GLOBAL: case TYPE_LABOLG: case TYPE_GOND  :
      strcpy (a_on , BACK_BLU);
      break;
   case TYPE_MODE  : case TYPE_LOCAL : case TYPE_CODE  : case TYPE_LOAD  : case TYPE_FILE : case TYPE_APPEND : case TYPE_SYSTEM :
      strcpy (a_on , BACK_CYN);
      break;
   case TYPE_TINU  :
      if      (UNIT_FAIL > 0)  strcpy (a_on , BACK_RED);
      else if (UNIT_BADD > 0)  strcpy (a_on , BACK_YEL);
      else                     strcpy (a_on , BACK_GRN);
      break;
   case TYPE_PRCS  :
      if      (SCRP_FAIL > 0)  strcpy (a_on , BACK_RED);
      else if (SCRP_BADD > 0)  strcpy (a_on , BACK_YEL);
      else                     strcpy (a_on , BACK_GRN);
      break;
   case TYPE_DNOC  :
      if      (COND_FAIL > 0)  strcpy (a_on , BACK_RED);
      else if (COND_BADD > 0)  strcpy (a_on , BACK_YEL);
      else                     strcpy (a_on , BACK_GRN);
      break;
   }
   return 0;
}

char
yunit_recd_colors       (char *a_test, char *a_note, char *a_on1, char *a_on2, char *a_off)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_resu      =  'p';
   /*---(defense)------------------------*/
   if (a_test == NULL)  return -1;
   if (a_note == NULL)  return -2;
   if (a_on1  == NULL)  return -3;
   if (a_on2  == NULL)  return -4;
   if (a_off  == NULL)  return -5;
   /*---(establish result)---------------*/
   x_resu = s_resu;
   if (s_resu == YUNIT_SUCC && myUNIT.is_forced_fail)   x_resu = YUNIT_FFAIL;
   if (s_resu == YUNIT_FAIL && myUNIT.is_forced_fail)   x_resu = YUNIT_FSUCC;
   /*---(establish result)---------------*/
   strcpy (a_off , BACK_OFF);
   switch (x_resu) {
   case YUNIT_SUCC  :
      strcpy (a_note, "PASS");
      ++COND_PASS;
      strcpy (a_on1 , BACK_GRN);
      strcpy (a_on2 , BACK_GRN);
      break;
   case YUNIT_FAIL  :
      strcpy (a_note, "FAIL");
      ++COND_FAIL;
      strcpy (a_on1 , BACK_RED);
      strcpy (a_on2 , BACK_RED);
      break;
   case YUNIT_FSUCC :
      strcpy (a_note, "!PASS");
      ++COND_PASS;
      strcpy (a_on1 , BACK_RED);
      strcpy (a_on2 , BACK_GRN);
      break;
   case YUNIT_FFAIL :
      ++COND_FAIL;
      strcpy (a_note, "!FAIL");
      strcpy (a_on1 , BACK_GRN);
      strcpy (a_on2 , BACK_RED);
      break;
   case YUNIT_VOID  :
      ++COND_VOID;
      strcpy (a_note, "----");
      strcpy (a_on1 , BACK_CYN);
      strcpy (a_on2 , BACK_CYN);
      break;
   default          :
      strcpy (a_note, "WARN");
      ++COND_BADD;
      strcpy (a_on1 , BACK_YEL);
      strcpy (a_on2 , BACK_YEL);
      break;
   }
   if (myUNIT.mono) {
      strcpy (a_on1 , "");
      strcpy (a_on2 , "");
      strcpy (a_off , "");
      return 0;
   }
   return 0;
}

char*
yunit_header            (char a_type, int a_line, int a_seqn, char *a_note, char *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   int         l           =    0;
   int         x_pre       =    0;
   int         x_suf       =    0;
   char        x_note      [LEN_TERSE] = "??";
   char        x_desc      [LEN_HUND]  = "??";
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
   yunit_colors (a_type, x_on, NULL, x_off);
   /*---(find merge point)---------------*/
   /*> strcat (x_desc, " ");                                                          <*/
   l       = strlen (x_desc);
   x_pre   = (65 - l) / 2;
   x_suf   = (65 - x_pre) - l;
   switch (a_type) {
   case TYPE_SCRP  :
      ++l;
      snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_EQUAL + l);
      snprintf (s_print, LEN_RECD, "SCRP [%02d] %61.61s[%4s]=[%05d]", a_seqn, t, x_note, a_line);
      break;
   case TYPE_SECT  :
      if (l < 65)  sprintf (t, "%*.*s %s %*.*s", x_pre - 3, x_pre - 3, YSTR_DASH, x_desc, x_suf - 3, x_suf - 3, YSTR_DASH);
      else         sprintf (t, "%65.65s", x_desc);
      sprintf (s_print, "SECT ===----%s----=== TCES", t);
      break;
   case TYPE_COND  :
      ++l;
      snprintf (t, LEN_HUND, "  COND [%03d] %s %s", a_seqn, x_desc, YSTR_COND + l);
      sprintf  (s_print, "%-78.78s[%05d]", t, a_line);
      break;
   case TYPE_CCND  :
      ++l;
      snprintf (t, LEN_HUND, "%s %s", x_desc, YSTR_COND + l);
      sprintf  (s_print, "  %sCCND [%03d] %s%s %-61.61s[%05d]", x_on, a_seqn, x_note, x_off, t, a_line);
      break;
   case TYPE_DOND  :
      ++l;
      snprintf (t, LEN_HUND, "%s %s", x_desc, YSTR_COND + l);
      sprintf  (s_print, "  %sDOND [%03d] %s %-61.61s[%05d]%s", x_on, a_seqn, x_note, t, a_line, x_off);
      break;
   case TYPE_SOND  :
      ++l;
      snprintf (t, LEN_HUND, "%s %s", x_desc, YSTR_COND + l);
      sprintf  (s_print, "  %sSOND [%03d]%s %-65.65s[%05d]", x_on, a_seqn, x_off, t, a_line);
      break;
   case TYPE_GOND  :
      ++l;
      snprintf (t, LEN_HUND, "%s %s", x_desc, YSTR_COND + l);
      sprintf  (s_print, "  %sGOND [%03d]%s %-65.65s[%05d]", x_on, a_seqn, x_off, t, a_line);
      break;
   case TYPE_GROUP :
      if (l < 65)  sprintf (t, "%*.*s   %s   %*.*s", x_pre - 3, x_pre - 3, YSTR_DASH, x_desc, x_suf - 3, x_suf - 3, YSTR_DASH);
      else         sprintf (t, "%65.65s", x_desc);
      sprintf (s_print, "  GROUP ===---%s---===", t);
      break;
   case TYPE_SHARE :
      if (l < 65)  sprintf (t, "%*.*s   %s   %*.*s", x_pre - 3, x_pre - 3, YSTR_DASH, x_desc, x_suf - 3, x_suf - 3, YSTR_DASH);
      else         sprintf (t, "%65.65s", x_desc);
      sprintf (s_print, "  %sSHARE (%c) ===-%s-===%s", x_on, a_seqn, t, x_off);
      break;
   case TYPE_ERAHS :
      if (l < 65)  sprintf (t, "%*.*s   %s   %*.*s", x_pre - 3, x_pre - 3, YSTR_DASH, x_desc, x_suf - 3, x_suf - 3, YSTR_DASH);
      else         sprintf (t, "%65.65s", x_desc);
      sprintf (s_print, "  %sERAHS (%c) ===-%s-===%s", x_on, a_seqn, t, x_off);
      break;
   case TYPE_GLOBAL :
      if (l < 63)  sprintf (t, "%*.*s   %s   %*.*s", x_pre - 4, x_pre - 4, YSTR_DASH, x_desc, x_suf - 4, x_suf - 4, YSTR_DASH);
      else         sprintf (t, "%63.63s", x_desc);
      sprintf (s_print, "  %sGLOBAL (%c) ===-%s--===%s", x_on, a_seqn, t, x_off);
      break;
   case TYPE_LABOLG :
      if (l < 63)  sprintf (t, "%*.*s   %s   %*.*s", x_pre - 4, x_pre - 4, YSTR_DASH, x_desc, x_suf - 4, x_suf - 4, YSTR_DASH);
      else         sprintf (t, "%63.63s", x_desc);
      sprintf (s_print, "  %sLABOLG (%c) ===-%s--===%s", x_on, a_seqn, t, x_off);
      break;
   case TYPE_LOCAL : case TYPE_CODE  : case TYPE_LOAD  : case TYPE_MODE  : case TYPE_FILE  : case TYPE_APPEND  :
      ++l;
      ++COND_VOID;
      snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_ESTEP + l);
      snprintf (s_print, LEN_RECD, "  %s%s) %s%-6.6s%s : %63.63s[%05d]", BACK_CYN, yunit_seqn (a_seqn), BACK_GRN, a_note, BACK_OFF, t, a_line);
      break;
   case TYPE_SYSTEM :
      ++l;
      yunit_recd_colors (x_test, x_note, x_on, x_on2, x_off);
      if (strcmp (x_note, "PASS")   == 0)  strcpy  (x_note, a_note);
      if (x_note [0] == '!')               sprintf (x_note, "!%s", a_note);
      if (strcmp (x_on  , BACK_GRN) == 0)  strcpy (x_on  , BACK_CYN);
      snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_ESTEP + l);
      snprintf (s_print, LEN_RECD, "  %s%s) %s%-6.6s%s : %63.63s[%05d]", x_on, yunit_seqn (a_seqn), x_on2, x_note, x_off, t, a_line);
      break;
   case TYPE_STEP  :
      ++l;
      yunit_recd_colors (x_test, x_note, x_on, x_on2, x_off);
      /*> if (myUNIT.level <= 4)  strncpy (x_note, a_note, LEN_LABEL);                <*/
      /*> ++l;                                                                        <*/
      if (myUNIT.pure)  snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_CSTEP + l);
      else              snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_ESTEP + l);
      if (myUNIT.is_forced_fail) {
         snprintf (s_print, LEN_RECD, "  %s%s) %s%-6.6s%s : %63.63s[%05d]", x_on, yunit_seqn (a_seqn), x_on2, x_note, x_off, t, a_line);
      } else {
         snprintf (s_print, LEN_RECD, "  %s%s) %-6.6s%s : %63.63s[%05d]", x_on, yunit_seqn (a_seqn), x_note, x_off, t, a_line);
      }
      break;
   case TYPE_DISP  :
      l -= 1;
      if (myUNIT.pure)  snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_CSTEP + l);
      else              snprintf (t      , LEN_HUND, "%s %s", x_desc, YSTR_ESTEP + l);
      snprintf (s_print, LEN_RECD, "     %s) %-6.6s: %61.61s[%05d]", yunit_seqn (a_seqn), x_note, t, a_line);
      break;
   }
   /*---(complete)-----------------------*/
   return s_print;
}

char*
yunit_footer            (char a_type)
{
   char        x_on        [LEN_LABEL] = "";
   char        x_off       [LEN_LABEL] = "";
   yunit_colors (a_type, x_on, NULL, x_off);
   switch (a_type) {
   case TYPE_TINU  : case TYPE_DINU  :
      if (a_type == TYPE_TINU) {
         if (UNIT_TEST == 0)  strcpy (x_on, BACK_YEL);
         sprintf (s_print, "%sTINU  scrp=%-4d cond=%-5d test=%-5d [ pass=%-5d fail=%-5d badd=%-5d void=%-5d ]%s",
               x_on, UNIT_SCRP, UNIT_COND, UNIT_TEST, UNIT_PASS, UNIT_FAIL, UNIT_BADD, UNIT_VOID, x_off);
      } else {
         sprintf (s_print, "TINU  scrp=%-4d cond=%-5d test=%-5d [ ------------------------------------------- ]",
               UNIT_SCRP, UNIT_COND, UNIT_TEST);
      }
      break;
   case TYPE_PRCS  : case TYPE_DRCS  :
      if (a_type == TYPE_PRCS) {
         if (SCRP_TEST == 0)  strcpy (x_on, BACK_YEL);
         sprintf (s_print, "  %sPRCS -------- cond=%-5d test=%-5d [ pass=%-5d fail=%-5d badd=%-5d void=%-5d ]%s",
               x_on, SCRP_COND, SCRP_TEST, SCRP_PASS, SCRP_FAIL, SCRP_BADD, SCRP_VOID, x_off);
      } else {
         sprintf (s_print, "  PRCS -------- cond=%-5d test=%-5d [ ------------------------------------------- ]",
               SCRP_COND, SCRP_TEST);
      }
      UNIT_TEST += SCRP_TEST;
      UNIT_PASS += SCRP_PASS;
      UNIT_FAIL += SCRP_FAIL;
      UNIT_BADD += SCRP_BADD;
      UNIT_VOID += SCRP_VOID;
      break;
   case TYPE_DNOC  : case TYPE_DNOD  :
      if (a_type == TYPE_DNOC) {
         if (COND_TEST == 0)  strcpy (x_on, BACK_YEL);
         sprintf (s_print, "      %sDNOC --------------- test=%-5d [ pass=%-5d fail=%-5d badd=%-5d void=%-5d ]%s",
               x_on, COND_TEST, COND_PASS, COND_FAIL, COND_BADD, COND_VOID, x_off);
      }
      SCRP_TEST += COND_TEST;
      SCRP_PASS += COND_PASS;
      SCRP_FAIL += COND_FAIL;
      SCRP_BADD += COND_BADD;
      SCRP_VOID += COND_VOID;
      break;
   }
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                          step-level                          ----===*/
/*====================------------------------------------====================*/
static void      o___STEP____________________o (void) {;}

char
yUNIT_void              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char a_exec)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "void"  , a_desc);
   /*---(prepare)--------------------------------*/
   s_resu  = YUNIT_SUCC;
   s_code  = 'v';
   /*---(record the key data)--------------------*/
   strncpy  (myUNIT.expe, "void", LEN_RECD);
   strncpy  (myUNIT.actu, "void", LEN_RECD);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_char              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, uchar a_expe, uchar a_actu, char a_exec)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "char"  , a_desc);
   /*---(prepare)--------------------------------*/
   s_resu  =  YUNIT_FAIL;
   s_code  = -1;
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "c_") != NULL) {
      s_code = yVAR_char (a_test, a_expe, a_actu);
      if      (s_code >   0 ) s_resu = YUNIT_SUCC;
      else if (s_code == '¢') s_resu = YUNIT_WARN;
   } else {
      s_resu = YUNIT_WARN;
   }
   /*> printf ("%-12.12s  %4d  %4d  %4d  %4d\n", a_test, a_expe, a_actu, s_code, s_resu);   <*/
   /*---(save return)----------------------------*/
   yUNIT_i_rc = a_actu;
   /*---(record the key data)--------------------*/
   snprintf (myUNIT.expe, LEN_RECD, "%c", a_expe);
   snprintf (myUNIT.actu, LEN_RECD, "%c", a_actu);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_int               (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, llong a_expe, llong a_actu, char a_exec)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "int"   , a_desc);
   /*---(prepare)--------------------------------*/
   s_resu  =  YUNIT_FAIL;
   s_code  = -1;
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "i_") != NULL) {
      s_code = yVAR_integer (a_test, a_expe, a_actu);
      if      (s_code >   0 ) s_resu = YUNIT_SUCC;
      else if (s_code == '¢') s_resu = YUNIT_WARN;
   } else {
      s_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_i_rc = a_actu;
   /*---(record the key data)--------------------*/
   snprintf (myUNIT.expe, LEN_RECD, "%lld", a_expe);
   snprintf (myUNIT.actu, LEN_RECD, "%lld", a_actu);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_real              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, double a_expe, double a_actu, char a_exec)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "real"  , a_desc);
   /*---(prepare)--------------------------------*/
   s_resu  =  YUNIT_FAIL;
   s_code  = -1;
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "r_") != NULL) {
      s_code = yVAR_real (a_test, a_expe, a_actu);
      if      (s_code >   0 ) s_resu = YUNIT_SUCC;
      else if (s_code == '¢') s_resu = YUNIT_WARN;
   } else {
      s_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_r_rc = a_actu;
   /*---(record the key data)--------------------*/
   snprintf (myUNIT.expe, LEN_RECD, "%lf", a_expe);
   snprintf (myUNIT.actu, LEN_RECD, "%lf", a_actu);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_point             (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, void *a_expe, void *a_actu, char a_exec)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "point" , a_desc);
   /*---(prepare)--------------------------------*/
   s_resu  =  YUNIT_FAIL;
   s_code  = -1;
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "p_") != NULL) {
      s_code = yVAR_pointer (a_test, a_expe, a_actu);
      if      (s_code >   0 ) s_resu = YUNIT_SUCC;
      else if (s_code == '¢') s_resu = YUNIT_WARN;
   } else {
      s_resu = YUNIT_WARN;
   }
   if (strcmp (a_test, "p_exists") == 0) a_expe = a_actu;
   /*---(save return)----------------------------*/
   yUNIT_p_rc = a_actu;
   /*---(record the key data)--------------------*/
   snprintf  (myUNIT.expe, LEN_RECD, "%p",  a_expe);
   if (strcmp(a_test, "p_exists") == 0) strncpy(myUNIT.expe, "---any---", LEN_HUND);
   if (strcmp(a_test, "p_null"  ) == 0) strncpy(myUNIT.expe, "NULL"     , LEN_HUND);
   snprintf  (myUNIT.actu, LEN_RECD, "%p",  a_actu);
   if (a_actu != NULL) myUNIT.is_leak_end = a_actu;
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_string            (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu, char a_exec)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "str"   , a_desc);
   /*---(locals)---------------------------------*/
   char        x_fexp      [LEN_RECD]  = "???";
   char        x_fact      [LEN_RECD]  = "???";
   /*---(prepare)--------------------------------*/
   s_resu   =  YUNIT_FAIL;
   s_code   = -1;
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "s_") != NULL) {
      s_code = yVAR_string (a_test, a_expe, a_actu);
      if      (s_code >   0 ) s_resu = YUNIT_SUCC;
      else if (s_code == '¢') s_resu = YUNIT_WARN;
      else if (s_code >  -10) s_resu = YUNIT_WARN;
   } else {
      s_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   yVAR_results (NULL, NULL, s_mask, x_fexp, x_fact);
   /*---(record the key data)--------------------*/
   if (strcmp (a_test, "s_equal") == 0 || strncmp (a_test, "s_round", 7) == 0 ) {
      strncpy (myUNIT.expe, x_fexp, LEN_RECD);
      strncpy (myUNIT.actu, x_fact, LEN_RECD);
   } else {
      strncpy (myUNIT.expe, a_expe, LEN_RECD);
      strncpy (myUNIT.actu, a_actu, LEN_RECD);
   }
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_wrap              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu, char a_exec)
{
   char        x_test      [LEN_LABEL] = "";
   char        x_actu      [LEN_RECD]  = "";
   sprintf (x_test, "s_%s", a_test + 2);
   sprintf (x_actu, "å%sæ", a_actu);
   /*> ystrldchg (x_actu, '', '§', LEN_RECD);                                        <*/
   return yUNIT_string (a_line, a_seqn, a_desc, a_meth, a_args, x_test, a_expe, x_actu, a_exec);
}

char
yUNIT_round             (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu, char a_exec)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "round" , a_desc);
   /*---(locals)---------------------------------*/
   char        x_fexp      [LEN_RECD]  = "???";
   char        x_fact      [LEN_RECD]  = "???";
   /*---(prepare)--------------------------------*/
   s_resu  =  YUNIT_FAIL;
   s_code  =  -1;
   /*---(do the comparisons)---------------------*/
   if (strncmp (a_test, "u_round/", 8) == 0) {
      s_code = yVAR_round (a_test, a_expe, a_actu);
      if      (s_code >   0 ) s_resu = YUNIT_SUCC;
      else if (s_code == '¢') s_resu = YUNIT_WARN;
      else if (s_code >  -10) s_resu = YUNIT_WARN;
   } else {
      s_code = '¢';
      s_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   yVAR_results (NULL, NULL, NULL, x_fexp, x_fact);
   /*---(record the key data)--------------------*/
   if (s_code != '¢') {
      strncpy (myUNIT.expe, x_fexp, LEN_RECD);
      strncpy (myUNIT.actu, x_fact, LEN_RECD);
   } else {
      strncpy (myUNIT.expe, a_expe, LEN_RECD);
      strncpy (myUNIT.actu, a_actu, LEN_RECD);
   }
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_unknown           (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu, char a_exec)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yUNIT__disp (a_line, a_seqn, "????"  , a_desc);
   /*---(prepare)--------------------------------*/
   s_resu   =  YUNIT_WARN;
   s_code   = '¢';
   /*---(record the key data)--------------------*/
   strncpy     (myUNIT.expe, a_expe, LEN_RECD);
   strncpy     (myUNIT.actu, "NULL", LEN_RECD);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)---------------------*/
   return 0;
}


/*====================------------------------------------====================*/
/*===----                            display                           ----===*/
/*====================------------------------------------====================*/
static void      o___DISPLAY_________________o (void) {;}

char
yUNIT__disp             (int a_line, int a_seqn, cchar *a_note, cchar *a_desc)
{
   char        x_desc      [LEN_HUND]  = "???";
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   /*---(fix a little)---------------------------*/
   if      (strncmp (x_desc, "... ", 4) == 0)   strncpy (x_desc, a_desc + 4, LEN_HUND);
   else if (strncmp (x_desc, "..." , 3) == 0)   strncpy (x_desc, a_desc + 3, LEN_HUND);
   yunit_header (TYPE_DISP  , a_line, a_seqn, a_note, x_desc);
   IF_STEP  yunit_printf  ("%s\n", s_print);
   ++COND_TEST;
   return 0;
}

char
yUNIT__recd             (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test)
{
   char        t           [LEN_HUND] = "";
   char        x_desc      [LEN_HUND]  = "???";
   char        x_meth      [LEN_HUND]  = "???";
   char        x_args      [LEN_HUND]  = "???";
   char        x_test      [LEN_HUND]  = "???";
   char        x_fexp      [LEN_RECD]  = "???";
   char        x_fact      [LEN_RECD]  = "???";
   char        x_ch        =  '´';
   int         l           =    0;
   /*---(defense)--------------------------------*/
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   if (a_meth != NULL)  strncpy (x_meth, a_meth, LEN_HUND);
   if (a_args != NULL)  strncpy (x_args, a_args, LEN_HUND);
   if (a_test != NULL)  strncpy (x_test, a_test, LEN_HUND);
   /*---(capture key data)-----------------------*/
   ++COND_TEST;
   /*---(print message)----------------*/
   yunit_header (TYPE_STEP  , a_line, a_seqn, x_test, x_desc);
   IF_STEP {
      yunit_printf  ("\n");
      yunit_printf  ("%s\n", s_print);
   }
   IF_FULL   {
      if (strlen(x_args) <= 50) yunit_printf ("      method : %-s (%.50s)\n", x_meth, x_args);
      else                      yunit_printf ("      method : %-s (%.48s>>\n", x_meth, x_args);
      if      (s_code >=  32 && s_code <=  126)  x_ch = s_code;
      else if (s_code == '¢')                    x_ch = '?';
      else if (s_code <= -32 && s_code >= -126)  x_ch = -s_code;
      else                                       x_ch = '-';
      yunit_printf ("      test   : %-10s (rc = %4d, test abbr = %c)%s\n", x_test, s_code, x_ch, (s_code == '¢') ? " BAD TEST" : "");
      if (strcmp(x_test, "void") != 0) {
         if (strcmp (x_test, "s_equal") == 0)  l = strlen (s_mask);
         else                                  l = strlen (myUNIT.expe);
         yunit_printf ("      expect : %2då%sæ\n", l, myUNIT.expe);
         if (strcmp (x_test, "s_equal") == 0)  l = strlen (s_mask);
         else                                  l = strlen (myUNIT.actu);
         yunit_printf ("      actual : %2då%sæ\n", l, myUNIT.actu);
      } else {
         yunit_printf ("      expect : void\n");
         yunit_printf ("      actual : void\n");
      }
   }
   /*---(complete)-------------------------------*/
   return 0;
}

char
yunit_result            (int a_resu, int a_code)
{
   s_resu = a_resu;
   s_code = a_code;
   return 0;
}



