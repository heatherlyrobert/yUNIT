#include "yUNIT.h"
#include "yUNIT_priv.h"



/*====================------------------------------------====================*/
/*===----                          step-level                          ----===*/
/*====================------------------------------------====================*/
static void      o___STEP____________________o (void) {;}

char
yUNIT_void              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_exec, char a_dittoing, char a_share)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "void"  , a_desc);
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, YUNIT_SUCC, 0);
   /*---(record the key data)--------------------*/
   strlcpy  (myUNIT.expe, "VOID", LEN_RECD);
   strlcpy  (myUNIT.actu, "VOID", LEN_RECD);
   strlcpy  (myUNIT.modd, ""    , LEN_RECD);
   yunit_disp_full ('v', a_line, a_seqn, a_share, a_desc, a_meth, a_args, myUNIT.expe, a_test, myUNIT.actu, myUNIT.modd);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_num               (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL] , char a_test [LEN_TERSE], int a_expe, int a_actu, char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_resu      = YUNIT_FAIL;
   char        rc          = -1;
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "RC"    , a_desc);
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "z_") != NULL) {
      rc = yVAR_num  (a_test, a_expe, a_actu);
      if      (rc >   0 ) x_resu = YUNIT_SUCC;
      else if (rc == '¢') x_resu = YUNIT_WARN;
      else                x_resu = YUNIT_FAIL;
   } else {
      x_resu = YUNIT_WARN;
      rc     = '¢';
   }
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, rc);
   /*---(save return)----------------------------*/
   yUNIT_i_rc = a_actu;
   /*---(record the key data)--------------------*/
   snprintf (myUNIT.expe, LEN_RECD, "%d", a_expe);
   snprintf (myUNIT.actu, LEN_RECD, "%d", a_actu);
   strncpy  (myUNIT.modd, ""    , LEN_RECD);
   yunit_disp_full ('z', a_line, a_seqn, a_share, a_desc, a_meth, a_args, myUNIT.expe, a_test, myUNIT.actu, myUNIT.modd);
   /*---(complete)-------------------------------*/
   return 1;
}

char
yUNIT_char              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL] , char a_test [LEN_TERSE], uchar a_expe, uchar a_actu, char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_resu      = YUNIT_FAIL;
   char        rc          = -1;
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "CHAR"  , a_desc);
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "c_") != NULL) {
      rc = yVAR_char (a_test, a_expe, a_actu);
      if      (rc >   0 ) x_resu = YUNIT_SUCC;
      else if (rc == '¢') x_resu = YUNIT_WARN;
      else                x_resu = YUNIT_FAIL;
   } else {
      x_resu = YUNIT_WARN;
      rc     = '¢';
   }
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, rc);
   /*---(save return)----------------------------*/
   yUNIT_i_rc = a_actu;
   /*---(record the key data)--------------------*/
   snprintf (myUNIT.expe, LEN_RECD, "%c", a_expe);
   snprintf (myUNIT.actu, LEN_RECD, "%c", a_actu);
   strncpy  (myUNIT.modd, ""    , LEN_RECD);
   yunit_disp_full ('c', a_line, a_seqn, a_share, a_desc, a_meth, a_args, myUNIT.expe, a_test, myUNIT.actu, myUNIT.modd);
   /*---(complete)-------------------------------*/
   return 1;
}

char
yunit_int_sizing        (llong a_number, char *r_sign, char *r_sig, char *r_exp, char *r_digits)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_HUND]  = "";
   char        r           [LEN_HUND]  = "";
   char        x_sign      =  '+';
   char        x_exp       =    0;
   char        x_digits    =    0;
   char        x_sig       =    0;
   /*---(default)--------------------------------*/
   if (r_sign   != NULL)  *r_sign   = '+';
   if (r_sig    != NULL)  *r_sig    =   0;
   if (r_exp    != NULL)  *r_exp    =   0;
   if (r_digits != NULL)  *r_digits =   0;
   /*---(learing)--------------------------------*/
   if (a_number < 0) {
      x_sign = '-';
      a_number *= -1;
   }
   sprintf (t, "%5.3e", (double) a_number);
   x_exp  = t [8] - '0';
   /*> printf ("exp   %c  %3d\n", t [8], x_exp);                                      <*/
   x_exp += 10 * (t [7] - '0');
   /*> printf ("exp   %c  %3d\n", t [7], x_exp);                                      <*/
   /*---(integer sizing)-------------------------*/
   x_digits = x_exp + 1;
   /*---(significant)----------------------------*/
   sprintf (r, "%lld", a_number);
   x_sig    = x_digits;
   for (i = x_sig - 1; i >= 0; --i) {
      if (r [i] != '0')  break;
      --x_sig;
   }
   /*---(save-back)------------------------------*/
   if (r_sign   != NULL)  *r_sign   = x_sign;
   if (r_sig    != NULL)  *r_sig    = x_sig;
   if (r_exp    != NULL)  *r_exp    = x_exp;
   if (r_digits != NULL)  *r_digits = x_digits;
   /*---(complete)-------------------------------*/
   return 0;
}

char
yunit_int_show          (llong a_expe, llong a_actu, char r_expe [LEN_RECD], char r_actu [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x1, x2;
   char        s1, s2, sm;
   char        e1, e2, em;
   char        d1, d2, dm;
   char        x_pre;
   char        x_expe      [LEN_HUND]  = "";
   char        x_actu      [LEN_HUND]  = "";
   /*---(aquire details)-----------------*/
   yunit_int_sizing (a_expe, &x1, &s1, &e1, &d1);
   if (a_expe < 0)  a_expe *= -1;
   yunit_int_sizing (a_actu, &x2, &s2, &e2, &d2);
   if (a_actu < 0)  a_actu *= -1;
   /*---(get maximums)-------------------*/
   sm = s1;  if (s2 > sm) sm = s2;
   em = e1;  if (e2 > em) em = e2;
   dm = d1;  if (d2 > dm) dm = d2;
   /*---(create text)--------------------*/
   x_pre = dm - d1; if (x_pre < 0)  x_pre = 0;
   sprintf (x_expe, "%3d%c%c%*.*s%*.*lld%c", dm + 1, YUNIT_BEG, x1, x_pre, x_pre, YUNIT_NDOTS, d1, d1, a_expe, YUNIT_END);
   if (r_expe != NULL)  snprintf (r_expe, LEN_RECD, "%-24.24s  %c  %2dd  ···  ···  %2ds  %c%15.14e", x_expe, x1, d1, s1, x1, (double) a_expe);
   x_pre = dm - d2; if (x_pre < 0)  x_pre = 0;
   sprintf (x_actu, "%3d%c%c%*.*s%*.*lld%c", dm + 1, YUNIT_BEG, x2, x_pre, x_pre, YUNIT_NDOTS, d2, d2, a_actu, YUNIT_END);
   if (r_actu != NULL)  snprintf (r_actu, LEN_RECD, "%-24.24s  %c  %2dd  ···  ···  %2ds  %c%15.14e", x_actu, x2, d2, s2, x2, (double) a_actu);
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_int               (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], llong a_expe, llong a_actu, char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_resu      = YUNIT_FAIL;
   char        rc          = -1;
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "INT"   , a_desc);
   /*---(do the comparisons)---------------------*/
   if (strstr(a_test, "i_") != NULL) {
      rc = yVAR_integer (a_test, a_expe, a_actu);
      if      (rc >   0 ) x_resu = YUNIT_SUCC;
      else if (rc == '¢') x_resu = YUNIT_WARN;
      else                x_resu = YUNIT_FAIL;
   } else {
      x_resu = YUNIT_WARN;
      rc     = '¢';
   }
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, rc);
   /*---(save return)----------------------------*/
   yUNIT_i_rc = a_actu;
   /*---(record the key data)--------------------*/
   yunit_int_show (a_expe, a_actu, myUNIT.expe, myUNIT.actu);
   strncpy  (myUNIT.modd, ""    , LEN_RECD);
   yunit_disp_full ('i', a_line, a_seqn, a_share, a_desc, a_meth, a_args, myUNIT.expe, a_test, myUNIT.actu, myUNIT.modd);
   /*---(complete)-------------------------------*/
   return 1;
}

char
yunit_real_sizing       (double a_number, char *r_sign, char *r_sig, char *r_exp, char *r_places, char *r_digits, char *r_fracts)
{
   int         i           =    0;
   char        t           [LEN_HUND]  = "";
   char        s           [LEN_HUND]  = "";
   char        r           [LEN_HUND]  = "";
   double      x_number    =  0.0;
   char        x_exp       =    0;
   char        x_digits    =    0;
   long        x_whole     =    0;
   char        x_fracts    =    0;
   double      x_part      =  0.0;
   char        x_sig       =    0;
   char        x_sign      =  '+';
   /*---(default)--------------------------------*/
   if (r_sign   != NULL)  *r_sign   = '+';
   if (r_sig    != NULL)  *r_sig    = 0;
   if (r_exp    != NULL)  *r_exp    = 0;
   if (r_places != NULL)  *r_places = 0;
   if (r_digits != NULL)  *r_digits = 0;
   if (r_fracts != NULL)  *r_fracts = 0;
   /*---(sign)-----------------------------------*/
   if (a_number < 0) {
      x_sign = '-';
      a_number *= -1.0;
   }
   /*---(learing)--------------------------------*/
   sprintf (t, "%5.3e", a_number);
   x_exp  = t [8] - '0';
   x_exp += 10 * (t [7] - '0');
   if (t [6] == '-')  x_exp *= -1;
   /*---(integer sizing)-------------------------*/
   x_number = a_number;
   if (x_exp >= 0) {
      sprintf (t, "%*.*lf", x_exp + 3, 2, x_number);
      for (i = 0; i < x_exp + 1; ++i) {  if (t [i] != ' ')  ++x_digits; }
      t [x_exp + 1] = '\0';
      x_whole = atol (t);
      /*> printf  ("whole  = %2då%sæ  %2d, %ld\n", strlen (t), t, x_digits, x_whole);   <*/
   } else {
      x_digits = 1;  /* minimum for display */
   }
   /*---(fraction sizing)------------------------*/
   x_number -= x_whole;
   if (x_exp > 15) {
      x_fracts = 1;
   } else if (x_whole = x_number) {
      x_fracts = 1;
   } else {
      x_fracts = 15 - x_exp;
      sprintf (t, "%*.*lf", x_fracts + 2, x_fracts, x_number);
      /*> printf  ("ready  = %2då%sæ  %2d\n", strlen (t), t, x_fracts);               <*/
      strlcpy (s, t, LEN_HUND);
      for (i = x_fracts + 1; i >= 2; --i) {
         /*> printf ("t [%d] = %c\n", i, t [i]);                                      <*/
         if (s [i] != '0')  break;
         --x_fracts; 
         s [i] = '\0';
      }
      x_part = atof (s);
      /*> printf  ("fracts = %2då%sæ  %2d, %lf\n", strlen (s), s, x_fracts, x_part);   <*/
      if (x_fracts == 0)  x_fracts = 1;
   }
   /*---(significan)-----------------------------*/
   sprintf (r, "%16.14e", a_number);
   x_sig = 15;
   for (i = x_sig; i >= 0; --i) {
      if (r [i] != '0')  break;
      --x_sig;
   }
   /*---(save-back)------------------------------*/
   if (r_sign   != NULL)  *r_sign   = x_sign;
   if (r_sig    != NULL)  *r_sig    = x_sig;
   if (r_exp    != NULL)  *r_exp    = x_exp;
   if (r_places != NULL)  *r_places = x_digits + 1 + x_fracts;
   if (r_digits != NULL)  *r_digits = x_digits;
   if (r_fracts != NULL)  *r_fracts = x_fracts;
   /*---(complete)-------------------------------*/
   return 0;
}

char
yunit_real_show         (double a_expe, double a_actu, char r_expe [LEN_RECD], char r_actu [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x1, x2;
   char        s1, s2, sm;
   char        e1, e2, em;
   char        p1, p2, pm;
   char        d1, d2, dm;
   char        f1, f2, fm;
   char        x_pre, x_suf;
   char        x_expe      [LEN_HUND]  = "";
   char        x_actu      [LEN_HUND]  = "";
   char        x_max       =    0;
   int         l           =    0;
   /*---(aquire details)-----------------*/
   yunit_real_sizing (a_expe, &x1, &s1, &e1, &p1, &d1, &f1);
   yunit_real_sizing (a_actu, &x2, &s2, &e2, &p2, &d2, &f2);
   /*---(get maximums)-------------------*/
   sm = s1;  if (s2 > sm)  sm = s2;
   em = e1;  if (e2 > em)  em = e2;
   pm = p1;  if (p2 > pm)  pm = p2;
   dm = d1;  if (d2 > dm)  dm = d2;
   fm = f1;  if (f2 > fm)  fm = f2;
   x_max = dm + fm + 2;
   /*---(create text)--------------------*/
   x_pre = dm - d1; if (x_pre < 0)  x_pre = 0;
   x_suf = fm - f1; if (x_suf < 0)  x_suf = 0;
   sprintf (x_expe, "%3d%c%c%*.*s%*.*lf%*.*s%c", x_max, YUNIT_BEG, x1, x_pre, x_pre, YUNIT_NDOTS, p1, f1, a_expe, x_suf, x_suf, YUNIT_NDOTS, YUNIT_END);
   l = strlen (x_expe);
   if (r_expe != NULL) {
      if      (l <= 24)  snprintf (r_expe, LEN_RECD, "%-24.24s  %c  %2dd  %2df  %2dp  %2ds  %c%15.14e", x_expe, x1, d1, f1, p1, s1, x1, a_expe);
      else               snprintf (r_expe, LEN_RECD, "%-47.47s  %c%15.14e", x_expe, x1, a_expe);
   }
   x_pre = dm - d2; if (x_pre < 0)  x_pre = 0;
   x_suf = fm - f2; if (x_suf < 0)  x_suf = 0;
   sprintf (x_actu, "%3d%c%c%*.*s%*.*lf%*.*s%c", x_max, YUNIT_BEG, x2, x_pre, x_pre, YUNIT_NDOTS, p2, f2, a_actu, x_suf, x_suf, YUNIT_NDOTS, YUNIT_END);
   if (r_actu != NULL) {
      if      (l <= 24)  snprintf (r_actu, LEN_RECD, "%-24.24s  %c  %2dd  %2df  %2dp  %2ds  %c%15.14e", x_actu, x2, d2, f2, p2, s2, x2, a_actu);
      else               snprintf (r_actu, LEN_RECD, "%-47.47s  %c%15.14e", x_actu, x2, a_actu);
   }
   /*---(complete)-------------------------------*/
   return 0;
}

char
yUNIT_real              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], double a_expe, double a_actu, char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_resu      = YUNIT_FAIL;
   char        rc          =   -1;
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "REAL"  , a_desc);
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "r_") != NULL) {
      rc = yVAR_real (a_test, a_expe, a_actu);
      if      (rc >   0 ) x_resu = YUNIT_SUCC;
      else if (rc == '¢') x_resu = YUNIT_WARN;
      else                x_resu = YUNIT_FAIL;
   } else {
      x_resu = YUNIT_WARN;
      rc     = '¢';
   }
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, rc);
   /*---(save return)----------------------------*/
   yUNIT_r_rc = a_actu;
   /*---(record the key data)--------------------*/
   yunit_real_show (a_expe, a_actu, myUNIT.expe, myUNIT.actu);
   strncpy  (myUNIT.modd, ""    , LEN_RECD);
   yunit_disp_full ('r', a_line, a_seqn, a_share, a_desc, a_meth, a_args, myUNIT.expe, a_test, myUNIT.actu, myUNIT.modd);
   /*---(complete)-------------------------------*/
   return 1;
}

char
yUNIT_point             (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], void *a_expe, void *a_actu, char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_resu      = YUNIT_FAIL;
   char        rc          = -1;
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "POINT" , a_desc);
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "p_") != NULL) {
      rc = yVAR_pointer (a_test, a_expe, a_actu);
      if      (rc >   0 ) x_resu = YUNIT_SUCC;
      else if (rc == '¢') x_resu = YUNIT_WARN;
      else                x_resu = YUNIT_FAIL;
   } else {
      x_resu = YUNIT_WARN;
      rc     = '¢';
   }
   if (strcmp (a_test, "p_exists") == 0) a_expe = a_actu;
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, rc);
   /*---(save return)----------------------------*/
   yUNIT_p_rc = a_actu;
   /*---(record the key data)--------------------*/
   snprintf  (myUNIT.expe, LEN_RECD, "%p",  a_expe);
   if (strcmp(a_test, "p_exists") == 0) strncpy(myUNIT.expe, "---any---", LEN_HUND);
   if (strcmp(a_test, "p_null"  ) == 0) strncpy(myUNIT.expe, "NULL"     , LEN_HUND);
   snprintf  (myUNIT.actu, LEN_RECD, "%p",  a_actu);
   if (a_actu != NULL) myUNIT.is_leak_end = a_actu;
   strncpy  (myUNIT.modd, ""    , LEN_RECD);
   yunit_disp_full ('p', a_line, a_seqn, a_share, a_desc, a_meth, a_args, myUNIT.expe, a_test, myUNIT.actu, myUNIT.modd);
   /*---(complete)-------------------------------*/
   return 1;
}

char
yUNIT_string            (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_resu      = YUNIT_FAIL;
   char        rc          = -1;
   char        x_fexp      [LEN_RECD]  = "???";
   char        x_fact      [LEN_RECD]  = "???";
   char        x_modd      [LEN_RECD]  = "???";
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "STRING", a_desc);
   /*---(do the comparisons)---------------------*/
   if (strstr (a_test, "s_") != NULL) {
      rc = yVAR_string (a_test, a_expe, a_actu);
      if      (rc >   0 ) x_resu = YUNIT_SUCC;
      else if (rc == '¢') x_resu = YUNIT_WARN;
      else if (rc >  -10) { x_resu = YUNIT_WARN;  rc = '¢'; }
      else                x_resu = YUNIT_FAIL;
   } else {
      x_resu = YUNIT_WARN;
      rc     = '¢';
   }
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, rc);
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   yVAR_results (NULL, NULL, x_modd, x_fexp, x_fact);
   /*---(record the key data)--------------------*/
   /*> if (strcmp (a_test, "s_equal") == 0 || strncmp (a_test, "s_round", 7) == 0 ) {   <* 
    *>    strncpy (myUNIT.expe, x_fexp, LEN_RECD);                                      <* 
    *>    strncpy (myUNIT.actu, x_fact, LEN_RECD);                                      <* 
    *>    strncpy (myUNIT.modd, x_modd, LEN_RECD);                                      <* 
    *> } else {                                                                         <*/
   strncpy (myUNIT.expe, a_expe, LEN_RECD);
   strncpy (myUNIT.actu, a_actu, LEN_RECD);
   strncpy (myUNIT.modd, x_modd, LEN_RECD);
   /*> }                                                                              <*/
   yunit_disp_full ('s', a_line, a_seqn, a_share, a_desc, a_meth, a_args, myUNIT.expe, a_test, myUNIT.actu, myUNIT.modd);
   /*---(complete)-------------------------------*/
   return 1;
}

char
yUNIT_wrap              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   char        x_test      [LEN_LABEL] = "";
   char        x_actu      [LEN_RECD]  = "";
   sprintf (x_test, "s_%s", a_test + 2);
   sprintf (x_actu, "%c%s%c", YUNIT_BEG, a_actu, YUNIT_END);
   return yUNIT_string (a_line, a_seqn, a_desc, a_meth, a_args, x_test, a_expe, x_actu, a_exec, a_dittoing, a_share);
}

char
yUNIT_round             (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_resu      = YUNIT_FAIL;
   char        rc          = -1;
   char        x_fexp      [LEN_RECD]  = "???";
   char        x_fact      [LEN_RECD]  = "???";
   char        x_modd      [LEN_RECD]  = "???";
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "ROUND" , a_desc);
   /*---(do the comparisons)---------------------*/
   if (strncmp (a_test, "u_round/", 8) == 0) {
      rc = yVAR_round (a_test, a_expe, a_actu);
      if      (rc >   0 ) x_resu = YUNIT_SUCC;
      else if (rc == '¢') x_resu = YUNIT_WARN;
      else if (rc >  -10) x_resu = YUNIT_WARN;
      else                x_resu = YUNIT_FAIL;
   } else {
      rc = '¢';
      x_resu = YUNIT_WARN;
      rc     = '¢';
   }
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, x_resu, rc);
   /*---(save return)----------------------------*/
   yUNIT_s_rc = a_actu;
   yVAR_results (NULL, NULL, x_modd, x_fexp, x_fact);
   /*---(record the key data)--------------------*/
   /*> if (rc != '¢') {                                                               <* 
    *>    strncpy (myUNIT.expe, x_fexp, LEN_RECD);                                    <* 
    *>    strncpy (myUNIT.actu, x_fact, LEN_RECD);                                    <* 
    *>    strncpy (myUNIT.modd, x_modd, LEN_RECD);                                    <* 
    *> } else {                                                                       <*/
   strncpy (myUNIT.expe, a_expe, LEN_RECD);
   strncpy (myUNIT.actu, a_actu, LEN_RECD);
   strncpy (myUNIT.modd, x_modd, LEN_RECD);
   /*> }                                                                              <*/
   yunit_disp_full ('u', a_line, a_seqn, a_share, a_desc, a_meth, a_args, myUNIT.expe, a_test, myUNIT.actu, myUNIT.modd);
   /*---(complete)-------------------------------*/
   return 1;
}

char
yUNIT_unknown           (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_exec, char a_dittoing, char a_share)
{
   /*---(display only)---------------------------*/
   if (a_exec == 0)   return yunit_disp_show (a_line, a_seqn, a_share, "????"  , a_desc);
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_STEP, YUNIT_WARN, '¢');
   /*---(record the key data)--------------------*/
   strncpy  (myUNIT.expe, a_expe , LEN_RECD);
   strncpy  (myUNIT.actu, "(n/a)", LEN_RECD);
   strncpy  (myUNIT.modd, ""     , LEN_RECD);
   yunit_disp_full ('?', a_line, a_seqn, a_share, a_desc, a_meth, a_args, myUNIT.expe, a_test, myUNIT.actu, myUNIT.modd);
   /*---(complete)---------------------*/
   return 1;
}


