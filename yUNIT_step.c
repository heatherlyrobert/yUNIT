#include "yUNIT.h"
#include "yUNIT_priv.h"



static  int  s_resu    =  0;
static  int  s_code    =  0;
static  char s_seqn    [LEN_SHORT] = "";



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
   if (a_seqn <   0)  a_seqn = 0;
   if (a_seqn > 675)  a_seqn = 675;
   /*---(calculate)----------------------*/
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
   if (myUNIT.eterm != 'y')  return  0;
   strcpy (a_off , BACK_OFF);
   switch (a_type) {
   case TYPE_SCRP  : case TYPE_SECT  : case TYPE_COND  : case TYPE_GROUP :
      break;
   case TYPE_SHARE : case TYPE_ERAHS :
      strcpy (a_on , BACK_MAG);
      break;
   case TYPE_MODE  : case TYPE_CODE  : case TYPE_LOAD  : case TYPE_SYSTEM :
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
      strcpy (a_note, "OUCH");
      ++COND_FAIL;
      strcpy (a_on1 , BACK_RED);
      strcpy (a_on2 , BACK_GRN);
      break;
   case YUNIT_FFAIL :
      ++COND_PASS;
      strcpy (a_note, "FOR_F");
      strcpy (a_on1 , BACK_RED);
      strcpy (a_on2 , BACK_GRN);
      break;
   default          :
      strcpy (a_note, "WARN");
      ++COND_BADD;
      strcpy (a_on1 , BACK_YEL);
      strcpy (a_on2 , BACK_YEL);
      break;
   }
   /*> strncpy (a_note, "FAIL", 5);                                                   <* 
    *> if (s_resu == YUNIT_SUCC) {                                                    <* 
    *>    strncpy (a_note, "PASS", 5);                                                <* 
    *>    if (!myUNIT.is_forced_fail) {                                               <* 
    *>       ++COND_PASS;                                                             <* 
    *>       if (strcmp (a_test, "intg_FAIL") == 0) {                                 <* 
    *>          strcpy (a_on1 , "\e[41m");                                            <* 
    *>          strcpy (a_on2 , "\e[42m");                                            <* 
    *>          strcpy (a_off , "\e[0m");                                             <* 
    *>       } else {                                                                 <* 
    *>          strcpy (a_on1 , "\e[42m");                                            <* 
    *>          strcpy (a_on2 , a_on1  );                                             <* 
    *>          strcpy (a_off , "\e[0m");                                             <* 
    *>       }                                                                        <* 
    *>    } else {                                                                    <* 
    *>       ++COND_FAIL;                                                             <* 
    *>       strcpy (a_on1 , "\e[42m");                                               <* 
    *>       strcpy (a_on2 , "\e[41m");                                               <* 
    *>       strcpy (a_off , "\e[0m");                                                <* 
    *>       strcpy (a_note, "OUCH");                                                 <* 
    *>    }                                                                           <* 
    *> } else if (s_resu == YUNIT_FAIL) {                                             <* 
    *>    strncpy(a_note, "FAIL", 5);                                                 <* 
    *>    if (!myUNIT.is_forced_fail) {                                               <* 
    *>       ++COND_FAIL;                                                             <* 
    *>       strcpy (a_on1 , "\e[41m");                                               <* 
    *>       strcpy (a_on2 , a_on1  );                                                <* 
    *>       strcpy (a_off , "\e[0m");                                                <* 
    *>    } else {                                                                    <* 
    *>       ++COND_PASS;                                                             <* 
    *>       strcpy (a_on1 , "\e[41m");                                               <* 
    *>       strcpy (a_on2 , "\e[42m");                                               <* 
    *>       strcpy (a_off , "\e[0m");                                                <* 
    *>       strcpy (a_note, "FOR_F");                                                <* 
    *>    }                                                                           <* 
    *> } else {                                                                       <* 
    *>    strcpy (a_note, "WARN");                                                    <* 
    *>    ++COND_BADD;                                                                <* 
    *>    strcpy (a_on1 , "\e[43m");                                                  <* 
    *>    strcpy (a_on2 , a_on1  );                                                   <* 
    *>    strcpy (a_off , "\e[0m");                                                   <* 
    *> }                                                                              <*/
   if (myUNIT.eterm != 'y') {
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
   char        x_note      [LEN_TERSE] = "????";
   char        x_desc      [LEN_HUND]  = "???";
   char        t           [LEN_RECD]  = "";
   char       *x_cdot      = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ";
   char       *x_edot      = "·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ";
   char       *x_cdash     = " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --";
   char       *x_edash     = "··+··+··Ï··+··+··Ï··+··+··Ï··+··+··Ï··+··+··Ï··+··+··Ï··+··+··Ï··+··+··Ï··+··+··Ï··+··+··Ï··+··+··Ï";
   char       *x_dashes    = "---------------------------------------------------------------------------------------------------";
   char       *x_equal     = "===================================================================================================";
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
      snprintf (t      , LEN_HUND, "%s %s", x_desc, x_equal + l);
      snprintf (s_print, LEN_RECD, "SCRP [%02d] %68.68s[%05d]", a_seqn, t, a_line);
      break;
   case TYPE_SECT  :
      if (l < 65)  sprintf (t, "%*.*s[[ %s ]]%*.*s", x_pre - 3, x_pre - 3, x_dashes, x_desc, x_suf - 3, x_suf - 3, x_dashes);
      else         sprintf (t, "%65.65s", x_desc);
      sprintf (s_print, "SECT  ===----%s----===", t);
      strcpy  (s_sect, s_print);
      break;
   case TYPE_COND  :
      ++l;
      snprintf (t, LEN_HUND, "  COND [%03d] %s %s", a_seqn, x_desc, x_cdash + l);
      sprintf  (s_print, "%-78.78s[%05d]", t, a_line);
      break;
   case TYPE_GROUP :
      if (l < 65)  sprintf (t, "%*.*s   %s   %*.*s", x_pre - 3, x_pre - 3, x_dashes, x_desc, x_suf - 3, x_suf - 3, x_dashes);
      else         sprintf (t, "%65.65s", x_desc);
      sprintf (s_print, "  GROUP ===---%s---===", t);
      strcpy  (s_sect, s_print);
      break;
   case TYPE_SHARE :
      if (l < 65)  sprintf (t, "%*.*s   %s   %*.*s", x_pre - 3, x_pre - 3, x_dashes, x_desc, x_suf - 3, x_suf - 3, x_dashes);
      else         sprintf (t, "%65.65s", x_desc);
      sprintf (s_print, "  %sSHARE (%c) ===-%s-===%s", x_on, a_seqn, t, x_off);
      break;
   case TYPE_ERAHS :
      if (l < 65)  sprintf (t, "%*.*s   %s   %*.*s", x_pre - 3, x_pre - 3, x_dashes, x_desc, x_suf - 3, x_suf - 3, x_dashes);
      else         sprintf (t, "%65.65s", x_desc);
      sprintf (s_print, "  %sERAHS (%c) ===-%s-===%s", x_on, a_seqn, t, x_off);
      break;
   case TYPE_MODE  : case TYPE_CODE  : case TYPE_LOAD  : case TYPE_SYSTEM :
      ++l;
      snprintf (t      , LEN_HUND, "%s %s", x_desc, x_cdot + l);
      snprintf (s_print, LEN_RECD, "  %s%s) %-6.6s%s : %62.62s [%05d]", x_on, yunit_seqn (a_seqn), x_note, x_off, t, a_line);
      break;
   case TYPE_STEP  :
      ++l;
      strncpy (x_test, x_note, LEN_LABEL);
      yunit_recd_colors (x_test, x_note, x_on, x_on2, x_off);
      snprintf (t      , LEN_HUND, "%s %s", x_desc, x_cdot + l);
      snprintf (s_print, LEN_RECD, "  %s%s) %-6.6s%s : %62.62s [%05d]", x_on, yunit_seqn (a_seqn), x_note, x_off, t, a_line);
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
   case TYPE_TINU  :
      sprintf (s_print, "%sTINU   step=%-4d  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s",
            x_on, UNIT_TEST, UNIT_PASS, UNIT_FAIL, UNIT_BADD, UNIT_VOID, x_off);
      break;
   case TYPE_PRCS  :
      sprintf (s_print, "  %sPRCS   step=%-4d  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s",
            x_on, SCRP_TEST, SCRP_PASS, SCRP_FAIL, SCRP_BADD, SCRP_VOID, x_off);
      UNIT_TEST += SCRP_TEST;
      UNIT_PASS += SCRP_PASS;
      UNIT_FAIL += SCRP_FAIL;
      UNIT_BADD += SCRP_BADD;
      UNIT_VOID += SCRP_VOID;
      break;
   case TYPE_DNOC  :
      sprintf (s_print, "      %sDNOC   step=%-4d  [[ pass=%-4d  fail=%-4d  badd=%-4d  void=%-4d ]]%s",
            x_on, COND_TEST, COND_PASS, COND_FAIL, COND_BADD, COND_VOID, x_off);
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
yUNIT_void              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test)
{
   /*---(prepare)--------------------------------*/
   s_resu  = YUNIT_SUCC;
   s_code  = 0;
   /*---(record the key data)--------------------*/
   strncpy  (myUNIT.expe, "void", LEN_RECD);
   strncpy  (myUNIT.fixd, ""    , LEN_RECD);
   strncpy  (myUNIT.actu, "void", LEN_RECD);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_int               (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, long long a_expe, long long a_actu)
{
   /*---(prepare)--------------------------------*/
   s_resu  =  YUNIT_FAIL;
   s_code  = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "i_") != NULL) {
      s_code = yVAR_integer(a_test, a_expe, a_actu);
      if (s_code > 0) s_resu = YUNIT_SUCC;
   } else {
      s_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_i_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy  (myUNIT.fixd, ""    , LEN_RECD);
   snprintf (myUNIT.expe, LEN_RECD, "%lld", a_expe);
   snprintf (myUNIT.actu, LEN_RECD, "%lld", a_actu);
   /*> printf ("%20lld == [%s]¦", a_expe, myUNIT.expe);                              <*/
   /*> printf ("%20lld == [%s]¦", a_actu, myUNIT.actu);                              <*/
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_real              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, double a_expe, double a_actu)
{
   /*---(prepare)--------------------------------*/
   s_resu   =  YUNIT_FAIL;
   s_code   = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "r_") != NULL) {
      s_code = yVAR_real (a_test, a_expe, a_actu);
      if (s_code > 0) s_resu = YUNIT_SUCC;
   } else {
      s_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_r_rc = a_actu;
   /*---(record the key data)--------------------*/
   snprintf (myUNIT.expe, LEN_RECD, "%lf", a_expe);
   strncpy  (myUNIT.fixd, ""    , LEN_RECD);
   snprintf (myUNIT.actu, LEN_RECD, "%lf", a_actu);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_point             (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, void *a_expe, void *a_actu)
{
   /*---(prepare)--------------------------------*/
   s_resu   =  YUNIT_FAIL;
   s_code   = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "p_") != NULL) {
      s_code = yVAR_pointer (a_test, a_expe, a_actu);
      if (s_code > 0) s_resu = YUNIT_SUCC;
   } else {
      s_resu = YUNIT_WARN;
   }
   if (strcmp (a_test, "p_exists") == 0) a_expe = a_actu;
   /*---(save return)----------------------------*/
   yUNIT_p_rc = a_actu;
   /*---(record the key data)--------------------*/
   snprintf  (myUNIT.expe, LEN_RECD, "%p",  a_expe);
   if (strcmp(a_test, "p_exists") == 0) strncpy(myUNIT.expe, "---any---", LEN_HUND);
   strncpy   (myUNIT.fixd, ""    , LEN_RECD);
   snprintf  (myUNIT.actu, LEN_RECD, "%p",  a_actu);
   if (a_actu != NULL) myUNIT.is_leak_end = a_actu;
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_string            (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu)
{
   /*---(locals)---------------------------------*/
   char        x_fexp      [LEN_RECD]  = "???";
   char        x_fact      [LEN_RECD]  = "???";
   /*---(prepare)--------------------------------*/
   s_resu   =  YUNIT_FAIL;
   s_code   = -666;
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "s_") != NULL) {
      s_code = yVAR_string (a_test, a_expe, a_actu);
      if      (s_code >=  0) s_resu = YUNIT_SUCC;
      else if (s_code > -10) s_resu = YUNIT_WARN;
   } else {
      s_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   yVAR_results (NULL, NULL, NULL, x_fexp, x_fact);
   /*---(record the key data)--------------------*/
   strncpy (myUNIT.expe, x_fexp, LEN_RECD);
   strncpy (myUNIT.actu, x_fact, LEN_RECD);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_round             (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu)
{
   /*---(locals)---------------------------------*/
   char        x_fexp      [LEN_RECD]  = "???";
   char        x_fact      [LEN_RECD]  = "???";
   /*---(prepare)--------------------------------*/
   s_resu  =  YUNIT_FAIL;
   s_code  =  -666;               /* indicates unhandled test            */
   strncpy (myUNIT.fixd, "",     LEN_RECD);
   /*---(do the comparisons)---------------------*/
   if (strncmp (a_test, "u_round/", 8) == 0) {
      s_code = yVAR_round (a_test, a_expe, a_actu);
      if      (s_code >=    0) s_resu = YUNIT_SUCC;
      else if (s_code <= -600) s_resu = YUNIT_WARN;
      else                     s_resu = YUNIT_FAIL;
   } else {
      s_resu = YUNIT_WARN;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   yVAR_results (NULL, NULL, NULL, x_fexp, x_fact);
   /*---(record the key data)--------------------*/
   strncpy (myUNIT.expe, x_fexp, LEN_RECD);
   strncpy (myUNIT.actu, x_fact, LEN_RECD);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_ustr              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu)
{
   char    x_modd[LEN_RECD]  = "";
   char    x_actu[LEN_RECD]  = "";
   /*---(prepare)--------------------------------*/
   s_resu   =  YUNIT_FAIL;
   s_code   = -666;
   strncpy(x_modd, a_expe, 499);
   strncpy(x_actu, a_actu, 499);
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "u_") != NULL) {
      s_code = yVAR_round (a_test, x_modd, x_actu);
      if (s_code > 0) s_resu = YUNIT_SUCC;
   } else {
      s_resu = YUNIT_FAIL;
   }
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   /*---(record the key data)--------------------*/
   strncpy (myUNIT.expe, a_expe, LEN_RECD);
   strncpy (myUNIT.fixd, yVAR_modded (), LEN_RECD);
   strncpy (myUNIT.actu, x_actu, LEN_RECD);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_removed           (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu)
{  /*---(locals)-----------+-----------+-*/
   /*---(prepare)--------------------------------*/
   s_resu   =  YUNIT_FAIL;
   s_code   = -666;
   /*---(record the key data)--------------------*/
   strncpy     (myUNIT.expe, a_expe, LEN_RECD);
   strncpy     (myUNIT.fixd, ""    , LEN_RECD);
   strncpy     (myUNIT.actu, ""    , LEN_RECD);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_badd              (int a_line, int a_seqn, cchar *a_desc, cchar *a_test)
{
   s_resu   =  YUNIT_FAIL;
   ++COND_BADD;
   yUNIT__recd (a_line, a_seqn, a_desc, NULL  , NULL, a_test);
   /*> IF_STEP {                                                                       <* 
    *>    char  x_header[LEN_HUND] = "";                                               <* 
    *>    strncat(x_header, a_desc, 80);                                               <* 
    *>    strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);   <* 
    *>    strncat(x_header, "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .", 80);   <* 
    *>    fprintf(yUNIT_out, "\n  %s%s) BADD  %s :",                                   <* 
    *>          x_on, yunit_seqn (a_seqn), x_off);                                     <* 
    *>    fprintf(yUNIT_out, " %62.62s [%05d]\n", x_header, a_line);                   <* 
    *>    fprintf(yUNIT_out, "      test   : %s (not a recognized test)\n", a_test);   <* 
    *> }                                                                               <*/
   /*---(complete)---------------------*/
   return 0;
}

char
yUNIT_unknown           (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu)
{  /*---(locals)-----------+-----------+-*/
   /*---(prepare)--------------------------------*/
   s_resu   =  YUNIT_FAIL;
   s_code   = -666;
   /*---(record the key data)--------------------*/
   strncpy     (myUNIT.expe, a_expe, LEN_RECD);
   strncpy     (myUNIT.fixd, ""    , LEN_RECD);
   strncpy     (myUNIT.actu, ""    , LEN_RECD);
   yUNIT__recd (a_line, a_seqn, a_desc, a_meth, a_args, a_test);
   /*---(complete)---------------------*/
   return 0;
}


/*====================------------------------------------====================*/
/*===----                            display                           ----===*/
/*====================------------------------------------====================*/
static void      o___DISPLAY_________________o (void) {;}

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
   /*---(defense)--------------------------------*/
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   if (a_meth != NULL)  strncpy (x_meth, a_meth, LEN_HUND);
   if (a_args != NULL)  strncpy (x_args, a_args, LEN_HUND);
   if (a_test != NULL)  strncpy (x_test, a_test, LEN_HUND);
   /*---(capture key data)-----------------------*/
   ++COND_TEST;
   long int _gcpu = 0;
   /*---(print message)----------------*/
   IF_STEP {
      yunit_header (TYPE_STEP  , a_line, a_seqn, a_test, a_desc);
      fprintf (yUNIT_out, "%s\n", s_print);
   }
   IF_FULL   {
      if (strlen(x_args) <= 50) fprintf(yUNIT_out, "      method : %-s (%.50s)\n", x_meth, x_args);
      else                      fprintf(yUNIT_out, "      method : %-s (%.48s>>\n", x_meth, x_args);
      fprintf(yUNIT_out, "      test   : %-15s(@ %ld msecs with rc = %d) %s\n", x_test, _gcpu, s_code, (s_code <= -600) ? "----- BAD TEST -----" : "");
      if (strcmp(x_test, "void") != 0) {
         fprintf(yUNIT_out, "      expect : %-s>>\n", myUNIT.expe);
         fprintf(yUNIT_out, "      actual : %-s>>\n", myUNIT.actu);
      } else {
         fprintf(yUNIT_out, "      expect : void\n");
         fprintf(yUNIT_out, "      actual : void\n");
      }
      fprintf (yUNIT_out, "\n");
   }
   /*---(complete)-------------------------------*/
   return 0;
}

char
yunit__unit_result      (int a_resu, int a_code)
{
   s_resu = a_resu;
   s_code = a_code;
   return 0;
}



