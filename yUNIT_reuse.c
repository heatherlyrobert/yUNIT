#include "yUNIT.h"
#include "yUNIT_priv.h"


/*                                main --------local------------- --------global------------ --------config---------- - */
char  YUNIT_SHARES  [LEN_HUND] = "0123 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ èéêëìíîïðñòóôõö÷øùúûüýþÿ !";
/*
 * 0 = full-level
 * 1 = unit-level
 * 2 = scrp-level
 * 3 = cond-level
 * ! = audit storage for checking
 * ? = for run-time loading/reporting
 */
tyUNIT_COUNTS  g_counts [LEN_HUND];

#define     T_MASTER    'g'
#define     T_SHARES    's'
#define     T_CONFIG    'c'



/*====================------------------------------------====================*/
/*===----                        script level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
yUNIT_reuse_type        (char a_abbr)
{
   char        x_type      =  '-';
   /*---(header)-------------------------*/
   if      (a_abbr == 0)                          x_type = '-';
   else if (strchr (YSTR_UPPER, a_abbr) != NULL)  x_type = T_MASTER;
   else if (strchr (YSTR_LOWER, a_abbr) != NULL)  x_type = T_SHARES;
   else if (strchr (YSTR_GREEK, a_abbr) != NULL)  x_type = T_CONFIG;
   /*---(complete)-----------------------*/
   return x_type;
}

char
yUNIT_reuse_major       (char a_abbr)
{
   char        x_major     =  '-';
   /*---(header)-------------------------*/
   if      (a_abbr == 0)                          x_major = '-';
   else if (strchr (YSTR_LOWER, a_abbr) != NULL)  x_major = a_abbr;
   else if (strchr (YSTR_UPPER, a_abbr) != NULL)  x_major = a_abbr;
   else if (strchr (YSTR_GREEK, a_abbr) != NULL)  x_major = (uchar) a_abbr - (uchar) 'è' + 'a';
   /*---(complete)-----------------------*/
   return x_major;
}

int
yUNIT_reuse_index       (char a_abbr)
{
   char        x_index     =   -1;
   int         i           =    0;
   /*---(header)-------------------------*/
   if      (a_abbr == ' ')   x_index = -1;
   else if (a_abbr == '·')   x_index = -1;
   else if (a_abbr == 0)     x_index = -1;
   else {
      for (i = 0; i < LEN_HUND; ++i) {
         if (YUNIT_SHARES [i] == a_abbr) {
            x_index = i;
            break;
         }
      }
   }
   /*---(complete)-----------------------*/
   return x_index;
}

char
yunit_reuse_clear       (char n)
{
   /*---(identifier)---------------------*/
   g_counts [n].c_id     = YUNIT_SHARES [n];
   g_counts [n].c_type   = yUNIT_reuse_type  (g_counts [n].c_id);
   g_counts [n].c_ftype  =  '-';
   g_counts [n].c_major  = yUNIT_reuse_major (g_counts [n].c_id);
   g_counts [n].c_line   =   -1;
   strcpy (g_counts [n].c_desc  , "·");
   strcpy (g_counts [n].c_which , "·");
   strcpy (g_counts [n].c_titles, "·");
   /*---(units)--------------------------*/
   g_counts [n].c_unit   =    0;
   /*---(top)----------------------------*/
   g_counts [n].c_topp   =    0;
   g_counts [n].c_scrp   =    0;
   g_counts [n].c_glob   =    0;
   g_counts [n].c_shar   =    0;
   /*---(middle)-------------------------*/
   g_counts [n].c_midd   =    0;
   g_counts [n].c_cond   =    0;
   g_counts [n].c_ditt   =    0;
   strcpy (g_counts [n].c_dittos, "··········");
   g_counts [n].c_lreu   =    0;
   strcpy (g_counts [n].c_lreuse, "");
   g_counts [n].c_greu   =    0;
   strcpy (g_counts [n].c_greuse, "");
   g_counts [n].c_skipc  =    0;
   /*---(step)---------------------------*/
   g_counts [n].c_step   =    0;
   g_counts [n].c_real   =    0;
   g_counts [n].c_vars   =    0;
   g_counts [n].c_void   =    0;
   g_counts [n].c_skips  =    0;
   /*---(ditto)--------------------------*/
   g_counts [n].c_dstep  =    0;
   g_counts [n].c_dreal  =    0;
   g_counts [n].c_dvoid  =    0;
   g_counts [n].c_dskip  =    0;
   /*---(usage)--------------------------*/
   g_counts [n].c_called =    0;
   /*---(done)---------------------------*/
   return 0;
}

char
yUNIT_reuse_clear       (char a_abbr)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   --rce;  if (n < 0)   return rce;
   yunit_reuse_clear (n);
   /*---(complete)-----------------------*/
   return 0;
}

char
yUNIT_reuse_purge       (char a_ftype)
{
   /*---(locals)-------------------------*/
   int         i           =    0;
   /*---(set defaults)-------------------*/
   if (a_ftype == 0 || strchr ("*hwd", a_ftype) == NULL)  return -1;
   for (i = 0; i < LEN_HUND; ++i) {
      if      (a_ftype == '*')                   yunit_reuse_clear (i);
      else if (g_counts [i].c_ftype == a_ftype)  yunit_reuse_clear (i);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yUNIT_reuse_ftype       (char a_nscrp [LEN_TITLE], char r_header [LEN_TITLE])
{
   char        x_ftype     =  '-';
   char        x_header    [LEN_TITLE] = "";
   if (r_header != NULL)  strcpy  (r_header, "");
   if      (a_nscrp == NULL)                         { x_ftype = '°'; }
   else if (strcmp (a_nscrp, "unit_head.unit") == 0) { x_ftype = 'h'; }
   else if (strcmp (a_nscrp, "unit_wide.unit") == 0) { x_ftype = 'w'; strcpy (x_header, "unit_wide.h"); }
   else if (strcmp (a_nscrp, "unit_data.unit") == 0) { x_ftype = 'd'; strcpy (x_header, "unit_data.h"); }
   else                                              { x_ftype = '-'; }
   if (r_header != NULL)  strlcpy (r_header, x_header, LEN_TITLE);
   return x_ftype;
}

char
yUNIT_reuse_data        (char a_abbr, char *r_type, char r_tdesc [LEN_TERSE], char *r_major, char r_label [LEN_TERSE], char *r_ftype, int *r_line, char r_desc [LEN_LONG], char r_which [LEN_LABEL], char r_titles [LEN_PATH], short *r_conds, short *r_steps, char *r_called)
{
   char        rce         =  -10;
   int         n           =    0;
   char        x_tdesc     [LEN_TERSE] = "";
   char        x_label     [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_type   != NULL)  *r_type   = '-';
   if (r_tdesc  != NULL)  strcpy (r_tdesc , "");
   if (r_major  != NULL)  *r_major  = '-';
   if (r_label  != NULL)  strcpy (r_label , "");
   if (r_ftype  != NULL)  *r_ftype  = '-';
   if (r_line   != NULL)  *r_line   =  -1;
   if (r_desc   != NULL)  strcpy (r_desc  , "");
   if (r_which  != NULL)  strcpy (r_which , "");
   if (r_titles != NULL)  strcpy (r_titles, "");
   if (r_conds  != NULL)  *r_conds  =  -1;
   if (r_steps  != NULL)  *r_steps  =  -1;
   if (r_called != NULL)  *r_called =  -1;
   /*---(get reuse)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   --rce;  if (n < 0) {
      DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(get labels)---------------------*/
   switch (g_counts [n].c_type) {
   case T_SHARES :
      strlcpy (x_tdesc, "SHARED" , LEN_TERSE);
      strlcpy (x_label, "shared" , LEN_TERSE);
      break;
   case T_MASTER :
      strlcpy (x_tdesc, "GLOBAL" , LEN_TERSE);
      strlcpy (x_label, "global" , LEN_TERSE);
      break;
   case T_CONFIG :
      strlcpy (x_tdesc, "CONFIG" , LEN_TERSE);
      strlcpy (x_label, "config" , LEN_TERSE);
      break;
   default       :
      strlcpy (x_tdesc, "special", LEN_TERSE);
      break;
   }
   /*---(save-back)----------------------*/
   if (r_type   != NULL)  *r_type   = g_counts [n].c_type;
   if (r_tdesc  != NULL)  strlcpy (r_tdesc, x_tdesc, LEN_TERSE);
   if (r_major  != NULL)  *r_major  = g_counts [n].c_major;
   if (r_label  != NULL)  strlcpy (r_label, x_label, LEN_TERSE);
   if (r_ftype  != NULL)  *r_ftype  = g_counts [n].c_ftype;
   if (r_line   != NULL)  *r_line   = g_counts [n].c_line;
   if (r_desc   != NULL)  strlcpy (r_desc  , g_counts [n].c_desc  , LEN_LONG);
   if (r_which  != NULL)  strlcpy (r_which , g_counts [n].c_which , LEN_LABEL);
   if (r_titles != NULL)  strlcpy (r_titles, g_counts [n].c_titles, LEN_PATH);
   if (r_conds  != NULL)  *r_conds  = g_counts [n].c_midd;
   if (r_steps  != NULL)  *r_steps  = g_counts [n].c_step;
   if (r_called != NULL)  *r_steps  = g_counts [n].c_called;
   /*---(not set)------------------------*/
   if (g_counts [n].c_line <= 0) {
      DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return 1;
}

int
yUNIT_reuse_get         (char a_abbr, char r_desc [LEN_LONG], short *r_conds, short *r_steps)
{
   int         x_line      =   -1;
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   yUNIT_reuse_data (a_abbr, NULL, NULL, NULL, NULL, NULL, &x_line, r_desc, NULL, NULL, r_conds, r_steps, NULL);
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return x_line;
}

int
yUNIT_reuse_line        (char a_abbr)
{
   int         x_line      =   -1;
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   yUNIT_reuse_data (a_abbr, NULL, NULL, NULL, NULL, NULL, &x_line, NULL, NULL, NULL, NULL, NULL, NULL);
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return x_line;
}

int
yUNIT_reuse_desc        (char a_abbr, char r_tdesc [LEN_TERSE], char r_desc [LEN_LONG])
{
   int         x_line      =   -1;
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   yUNIT_reuse_data (a_abbr, NULL, r_tdesc, NULL, NULL, NULL, &x_line, r_desc, NULL, NULL, NULL, NULL, NULL);
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return x_line;
}

char*
yUNIT_reuse_title       (char a_abbr, char a_select)
{
   char        rc          =    0;
   char        x_desc      [LEN_LONG]  = "";
   char        x_which     [LEN_LABEL] = "";
   char        x_titles    [LEN_PATH]  = "";
   char        x_key       [LEN_SHORT] = "";
   char        x_sub       [LEN_LABEL] = "";
   char       *p           = NULL;
   int         l           =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   rc = yUNIT_reuse_data (a_abbr, NULL, NULL, NULL, NULL, NULL, NULL, x_desc, x_which, x_titles, NULL, NULL, NULL);
   if (rc <  0)  return "(n/a)";
   if (rc == 0)  return "(unset)";
   /*---(null)---------------------------*/
   if (a_select == 0) {
      sprintf (s_print, "%s (NULL)", x_desc);
      return s_print;
   }
   /*---(full)---------------------------*/
   if (a_select == '*') {
      sprintf (s_print, "%s (EVERY)", x_desc);
      return s_print;
   }
   /*---(check which)--------------------*/
   if (strchr (x_which, a_select) == NULL) {
      sprintf (s_print, "%s (N/A)", x_desc);
      return s_print;
   }
   /*---(check which)--------------------*/
   sprintf (x_key, "%c=", a_select);
   p = strstr (x_titles, x_key);
   if (p == NULL) {
      sprintf (s_print, "%s (TBD)", x_desc);
      return s_print;
   }
   /*---(add subtitle)-------------------*/
   snprintf (x_sub, 16, "%s", p);
   p = strchr (x_sub, ',');
   if (p != NULL)  p [0] = '\0';
   p = strchr (x_sub, '·');
   if (p != NULL)  p [0] = '\0';
   sprintf (s_print, "%s (%s)", x_desc, x_sub);
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return s_print;
}

char         /*-> at end shared, save stats ----------------------------------*/
yUNIT_reuse_save        (char a_abbr)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   --rce;  if (n < 0) {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(units)--------------------------*/
   g_counts [n].c_unit   = g_counts [SCRP_ID].c_unit;
   /*---(top)----------------------------*/
   g_counts [n].c_topp   = g_counts [SCRP_ID].c_topp;
   g_counts [n].c_scrp   = g_counts [SCRP_ID].c_scrp;
   g_counts [n].c_glob   = g_counts [SCRP_ID].c_glob;
   g_counts [n].c_shar   = g_counts [SCRP_ID].c_shar;
   /*---(middle)-------------------------*/
   g_counts [n].c_midd   = g_counts [SCRP_ID].c_midd;
   g_counts [n].c_cond   = g_counts [SCRP_ID].c_cond;
   g_counts [n].c_ditt   = g_counts [SCRP_ID].c_ditt;
   strcpy (g_counts [n].c_dittos, g_counts [SCRP_ID].c_dittos);
   g_counts [n].c_lreu   = g_counts [SCRP_ID].c_lreu;
   strcpy (g_counts [n].c_lreuse, g_counts [SCRP_ID].c_lreuse);
   g_counts [n].c_greu   = g_counts [SCRP_ID].c_greu;
   strcpy (g_counts [n].c_greuse, g_counts [SCRP_ID].c_greuse);
   g_counts [n].c_skipc  = g_counts [SCRP_ID].c_skipc;
   /*---(step)---------------------------*/
   g_counts [n].c_step   = g_counts [SCRP_ID].c_step;
   g_counts [n].c_real   = g_counts [SCRP_ID].c_real;
   g_counts [n].c_vars   = g_counts [SCRP_ID].c_vars;
   g_counts [n].c_void   = g_counts [SCRP_ID].c_void;
   g_counts [n].c_skips  = g_counts [SCRP_ID].c_skips;
   /*---(ditto)--------------------------*/
   g_counts [n].c_dstep  = g_counts [SCRP_ID].c_dstep;
   g_counts [n].c_dreal  = g_counts [SCRP_ID].c_dreal;
   g_counts [n].c_dvoid  = g_counts [SCRP_ID].c_dvoid;
   g_counts [n].c_dskip  = g_counts [SCRP_ID].c_dskip;
   /*---(usage)--------------------------*/
   g_counts [n].c_called = g_counts [SCRP_ID].c_called;
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   /*---(done)---------------------------*/
   return 1;
}

char
yUNIT_reuse_add         (char a_abbr)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   if (n < 0) {
      DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(top)----------------------------*/
   g_counts [SCRP_ID].c_topp  += g_counts [n].c_topp;
   g_counts [SCRP_ID].c_scrp  += g_counts [n].c_scrp;
   g_counts [SCRP_ID].c_glob  += g_counts [n].c_glob;
   g_counts [SCRP_ID].c_shar  += g_counts [n].c_shar;
   /*---(middle)-------------------------*/
   g_counts [SCRP_ID].c_midd  += g_counts [n].c_midd;
   g_counts [SCRP_ID].c_cond  += g_counts [n].c_cond;
   g_counts [SCRP_ID].c_ditt  += g_counts [n].c_ditt;
   g_counts [SCRP_ID].c_lreu  += g_counts [n].c_lreu;
   if (strcmp (g_counts [n].c_lreuse, "·") != 0)  strcat (g_counts [SCRP_ID].c_lreuse, g_counts [n].c_lreuse);
   g_counts [SCRP_ID].c_greu  += g_counts [n].c_greu;
   if (strcmp (g_counts [n].c_greuse, "·") != 0)  strcat (g_counts [SCRP_ID].c_greuse, g_counts [n].c_greuse);
   g_counts [SCRP_ID].c_skipc += g_counts [n].c_skipc;
   /*---(step)---------------------------*/
   g_counts [SCRP_ID].c_step  += g_counts [n].c_step;
   g_counts [SCRP_ID].c_real  += g_counts [n].c_real;
   g_counts [SCRP_ID].c_vars  += g_counts [n].c_vars;
   g_counts [SCRP_ID].c_void  += g_counts [n].c_void;
   g_counts [SCRP_ID].c_skips += g_counts [n].c_skips;
   /*---(ditto)--------------------------*/
   g_counts [SCRP_ID].c_dstep += g_counts [n].c_dstep;
   g_counts [SCRP_ID].c_dreal += g_counts [n].c_dreal;
   g_counts [SCRP_ID].c_dvoid += g_counts [n].c_dvoid;
   g_counts [SCRP_ID].c_dskip += g_counts [n].c_dskip;
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   /*---(done)---------------------------*/
   return 1;
}

char
yUNIT_reuse_reserve     (char a_abbr, char a_ftype, int a_line)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_MUNIT  ylog_uenter   (__FUNCTION__);
   /*---(get index)----------------------*/
   DEBUG_MUNIT  ylog_uchar    ("a_abbr"    , a_abbr);
   n = yUNIT_reuse_index (a_abbr);
   DEBUG_MUNIT  ylog_uvalue   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   yunit_reuse_clear (n);
   /*---(defense)------------------------*/
   DEBUG_MUNIT  ylog_uchar    ("a_ftype"   , a_ftype);
   --rce;  if (a_ftype == 0 || strchr ("hwd-", a_ftype) == NULL) {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MUNIT  ylog_uvalue   ("a_line"    , a_line);
   --rce;  if (a_line  <= 0 || a_line  >  99999) {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update list)--------------------*/
   g_counts [n].c_ftype = a_ftype;;
   g_counts [n].c_line  = a_line;
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return 1;
}

char
yUNIT_reuse_populate    (char a_abbr, char a_ftype, int a_line, char a_desc [LEN_LONG], char a_which [LEN_LABEL], char a_titles [LEN_PATH])
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_MUNIT  ylog_uenter   (__FUNCTION__);
   /*---(get index)----------------------*/
   DEBUG_MUNIT  ylog_uchar    ("a_abbr"    , a_abbr);
   n = yUNIT_reuse_index (a_abbr);
   DEBUG_MUNIT  ylog_uvalue   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   yunit_reuse_clear (n);
   /*---(defense)------------------------*/
   DEBUG_MUNIT  ylog_uchar    ("a_ftype"   , a_ftype);
   --rce;  if (a_ftype == 0 || strchr ("hwd-", a_ftype) == NULL) {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MUNIT  ylog_uvalue   ("a_line"    , a_line);
   --rce;  if (a_line  <= 0 || a_line  >  99999) {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> printf ("a_abbr %c, a_line %d, n %d, %s\n", a_abbr, a_line, n, a_desc);        <*/
   /*---(update list)--------------------*/
   g_counts [n].c_ftype = a_ftype;;
   g_counts [n].c_line  = a_line;
   if (a_desc   != NULL)  strlcpy (g_counts [n].c_desc  , a_desc  , LEN_LONG);
   if (a_which  != NULL)  strlcpy (g_counts [n].c_which , a_which , LEN_LABEL);
   if (a_titles != NULL)  strlcpy (g_counts [n].c_titles, a_titles, LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                        code/conv use                         ----===*/
/*====================------------------------------------====================*/
static void  o___IN_USE__________o () { return; }

char
yUNIT_reuse_called      (char a_abbr)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   --rce;  if (n < 0)   return rce;
   /*---(update list)--------------------*/
   ++(g_counts [n].c_called);
   /*---(complete)-----------------------*/
   return 1;
}

char
yUNIT_parse_update      (char a_abbr, int a_conds, int a_steps)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   int         n           =  -10;
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   /*---(lookup)-------------------------*/
   n = yUNIT_reuse_index (a_abbr);
   --rce;  if (n < 0)  {
      DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (g_counts [n].c_line < 0) {
      DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(update list)--------------------*/
   g_counts [n].c_cond = a_conds;
   g_counts [n].c_step = a_steps;
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return 1;
}

char
yUNIT_parse_addback     (char a_abbr, int *b_conds, int *b_steps)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   int         n           =  -10;
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   /*---(lookup)-------------------------*/
   n = yUNIT_reuse_index (a_abbr);
   --rce;  if (n < 0)  {
      DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (g_counts [n].c_line  <  0) {
      DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (g_counts [n].c_cond  <= 0) {
      DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(update list)--------------------*/
   if (b_conds != NULL)  *b_conds += g_counts [n].c_cond;
   if (b_steps != NULL)  *b_steps += g_counts [n].c_step;
   /*---(after)--------------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   /*---(complete)-----------------------*/
   return 1;
}


char*
yUNIT_reuse_show        (char a_abbr)
{
   /*---(locals)-------------------------*/
   char        n           =   -1;
   char        x_prefix    [LEN_FULL]  = "";
   char        x_suffix    [LEN_PATH]  = "";
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   if (n < 0)  return "((n/a))";
   sprintf (x_prefix, "%c  %c  %c  %5d  %-65.65s", g_counts [n].c_id, g_counts [n].c_type, g_counts [n].c_ftype, g_counts [n].c_line, g_counts [n].c_desc);
   sprintf (x_suffix, " %-14.14s  %s ", g_counts [n].c_which, g_counts [n].c_titles);
   /*---(complete)-----------------------*/
   return yunit_stats_show (x_prefix, n, x_suffix);
}

char
yUNIT__reuse_parse_more (char n, char *p, char *q, char *r)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        x_field     [LEN_LONG]  = "";
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   /*---(walk remaining data)------------*/
   --rce;  for (i = 0; i <= 23; ++i) {
      /*---(check field)-----------------*/
      if (p == NULL)  {
         DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
         return rce;
      }
      strlcpy   (x_field, p, LEN_LONG);
      ystrutrim (x_field,    LEN_LONG);
      /*---(script-level)----------------*/
      switch (i) {
      case  0 :  g_counts [n].c_topp   = atoi (x_field);  break;
      case  1 :  g_counts [n].c_glob   = atoi (x_field);  break;
      case  2 :  g_counts [n].c_shar   = atoi (x_field);  break;
      case  3 :  g_counts [n].c_scrp   = atoi (x_field);  break;
      }
      /*---(condition-level)-------------*/
      switch (i) {
      case  4 :  g_counts [n].c_midd   = atoi (x_field);  break;
      case  5 :  g_counts [n].c_cond   = atoi (x_field);  break;
      case  6 :  g_counts [n].c_ditt   = atoi (x_field);  break;
      case  7 :  strlcpy (g_counts [n].c_dittos, x_field, LEN_LABEL);  break;
      case  8 :  g_counts [n].c_lreu   = atoi (x_field);  break;
      case  9 :  strlcpy (g_counts [n].c_lreuse, x_field, LEN_HUND);   break;
      case 10 :  g_counts [n].c_greu   = atoi (x_field);  break;
      case 11 :  strlcpy (g_counts [n].c_greuse, x_field, LEN_HUND);   break;
      case 12 :  g_counts [n].c_skipc  = atoi (x_field);  break;
      }
      /*---(step-level)------------------*/
      switch (i) {
      case 13 :  g_counts [n].c_step   = atoi (x_field);  break;
      case 14 :  g_counts [n].c_real   = atoi (x_field);  break;
      case 15 :  g_counts [n].c_vars   = atoi (x_field);  break;
      case 16 :  g_counts [n].c_void   = atoi (x_field);  break;
      case 17 :  g_counts [n].c_skips  = atoi (x_field);  break;
      }
      /*---(ditto)-----------------------*/
      switch (i) {
      case 18 :  g_counts [n].c_dstep  = atoi (x_field);  break;
      case 19 :  g_counts [n].c_dreal  = atoi (x_field);  break;
      case 20 :  g_counts [n].c_dvoid  = atoi (x_field);  break;
      case 21 :  g_counts [n].c_dskip  = atoi (x_field);  break;
      }
      /*---(which)-----------------------*/
      switch (i) {
      case 22 :  strlcpy (g_counts [n].c_which , x_field, LEN_LABEL);  break;
      case 23 :  strlcpy (g_counts [n].c_titles, x_field, LEN_PATH );  break;
      }
      /*---(next)------------------------*/
      p = strtok_r (NULL, q, &r);
   }
   /*---(after)--------------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   /*---(complete)-----------------------*/
   return 1;
}

char
yUNIT_reuse_parse       (char a_type, char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_recd      [LEN_RECD]  = "";
   char        n           =   -1;
   int         i           =    0;
   char       *p           = NULL;
   char       *q           = "§";
   char       *r           = NULL;
   int         j           =    0;
   char        x_field     [LEN_LONG]  = "";
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   /*---(existing)-----------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(defense)------------------------*/
   DEBUG_MUNIT   ylog_upoint  ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL || a_recd [0] == '\0') {
      DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MUNIT   ylog_uinfo   ("a_recd"    , a_recd);
   strlcpy (x_recd, a_recd, LEN_RECD);
   /*---(initial parse)------------------*/
   p = strtok_r (x_recd, q, &r);
   /*---(walk data)----------------------*/
   --rce;  for (i = 0; i <= 5; ++i) {
      /*---(check field)-----------------*/
      DEBUG_MUNIT   ylog_upoint  ("p"         , p);
      if (p == NULL) {
         DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
         return rce;
      }
      strlcpy   (x_field, p, LEN_LONG);
      ystrutrim (x_field,    LEN_LONG);
      DEBUG_MUNIT   ylog_uinfo   ("x_field"   , x_field);
      /*---(master)----------------------*/
      DEBUG_MUNIT   ylog_uchar   ("a_type"    , a_type);
      --rce;  if (a_type == 'g') {
         switch (i) {
         case  0 :  n = yUNIT_reuse_index (x_field [0]);
                    DEBUG_MUNIT   ylog_uvalue  ("n"         , n);
                    if (n < 0) {
                       DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
                       return rce;
                    }
                    break;
         case  1 :  break;
         case  2 :  if (x_field [0] != '\0' && strchr ("hwd-", x_field [0]) != NULL) {
                       g_counts [n].c_ftype  = x_field [0];
                    } else {
                       g_counts [n].c_ftype  = '-';
                    }
                    DEBUG_MUNIT   ylog_uchar   ("c_ftype"   , g_counts [n].c_ftype);
                    break;
         case  3 :  g_counts [n].c_line   = atoi (x_field);
                    DEBUG_MUNIT   ylog_uvalue  ("c_line"    , g_counts [n].c_line);
                    break;
         case  4 :  strlcpy (g_counts [n].c_desc  , x_field, LEN_LONG);
                    DEBUG_MUNIT   ylog_uinfo   ("c_desc"    , g_counts [n].c_desc);
                    break;
         case  5 :  yUNIT__reuse_parse_more (n, p, q, r);
                    break;
         }
      } else if (a_type == 'r') {
         switch (i) {
         case  0 :  n = yUNIT_reuse_index ('!'); 
                    DEBUG_MUNIT   ylog_uvalue  ("n"         , n);
                    if (n < 0) {
                       DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
                       return rce;
                    }
                    if (g_counts [n].c_line < 0)  g_counts [n].c_line   = 0;
                    DEBUG_MUNIT   ylog_uvalue  ("c_line"    , g_counts [n].c_line);
                    break;
         case  1 :  strlcpy (g_counts [n].c_desc  , x_field, LEN_LONG);
                    DEBUG_MUNIT   ylog_uinfo   ("c_desc"    , g_counts [n].c_desc);
                    break;
         case  2 :  break;
         case  3 :  yUNIT__reuse_parse_more (n, p, q, r);
                    i = 5;
                    break;
         }
      } else if (a_type == 'u') {
         switch (i) {
         case  0 :  break;
         case  1 :  break;
         case  2 :  n = yUNIT_reuse_index (x_field [0]);
                    DEBUG_MUNIT   ylog_uvalue  ("n"         , n);
                    if (n < 0) {
                       DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
                       return rce;
                    }
                    if (g_counts [n].c_line < 0)  g_counts [n].c_line   = 0;
                    DEBUG_MUNIT   ylog_uvalue  ("c_line"    , g_counts [n].c_line);
                    break;
         case  3 :  yUNIT__reuse_parse_more (n, p, q, r);
                    i = 5;
                    break;
         }
      } else {
         DEBUG_MUNIT   ylog_unote   ("unknown type");
         DEBUG_MUNIT   ylog_uexitr  (__FUNCTION__, rce);
         return rce;
         break;
      }
      /*---(next)------------------------*/
      p = strtok_r (NULL, q, &r);
      /*---(done)------------------------*/
   }
   /*---(existing)-----------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(complete)-----------------------*/
   DEBUG_MUNIT   ylog_uexit   (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                        debugging support                     ----===*/
/*====================------------------------------------====================*/
static void  o___DEBUGGING_______o () { return; }

char*
yUNIT_reuse_actuals     (void)
{
   /*---(locals)-------------------------*/
   int         i           =    0;
   int         x_off       =    0;
   int         c           =    0;
   /*---(dittos)-------------------------*/
   strcpy (s_print, "·   á···   SH á·····á·····á·····á·····á·   GL á·····á·····á·····á·····á·   CO á·····á·····á·····á·····   á   Ï");
   /*---(global)-------------------------*/
   x_off = 9;
   for (i = 0; i < LEN_HUND; ++i) {
      if (g_counts [i].c_type == T_MASTER) {
         if      (g_counts [i].c_called >= 20)   s_print [i + x_off] = '°';
         else if (g_counts [i].c_called >= 10)   s_print [i + x_off] = '*';
         else if (g_counts [i].c_called >   0)   s_print [i + x_off] = '0' + g_counts [i].c_called;
         else if (g_counts [i].c_line   >=  0)   s_print [i + x_off] = '¬';
         if      (g_counts [i].c_called >=  0)   ++c;
      }
   }
   /*---(shared)-------------------------*/
   x_off += 5;
   for (i = 0; i < LEN_HUND; ++i) {
      if (g_counts [i].c_type == T_SHARES) {
         if      (g_counts [i].c_called >= 20)   s_print [i + x_off] = '°';
         else if (g_counts [i].c_called >= 10)   s_print [i + x_off] = '*';
         else if (g_counts [i].c_called >   0)   s_print [i + x_off] = '0' + g_counts [i].c_called;
         else if (g_counts [i].c_line   >=  0)   s_print [i + x_off] = '¬';
         if      (g_counts [i].c_called >=  0)   ++c;
      }
   }
   /*---(config)-------------------------*/
   x_off += 5;
   for (i = 0; i < LEN_HUND - 2; ++i) {
      if (g_counts [i].c_type == T_CONFIG) {
         if      (g_counts [i].c_called >= 20)   s_print [i + x_off] = '°';
         else if (g_counts [i].c_called >= 10)   s_print [i + x_off] = '*';
         else if (g_counts [i].c_called >   0)   s_print [i + x_off] = '0' + g_counts [i].c_called;
         else if (g_counts [i].c_line   >=  0)   s_print [i + x_off] = '¬';
         if      (g_counts [i].c_called >=  0)   ++c;
      }
   }
   /*---(use marker)---------------------*/
   if      (c ==  0)  s_print [0] = '¬';
   else if (c <= 10)  s_print [0] = '+';
   else if (c <= 20)  s_print [0] = '*';
   else               s_print [0] = '°';
   /*---(complete)-----------------------*/
   return s_print;
}

char*
yUNIT_reuse_used        (void)
{
   /*---(locals)-------------------------*/
   int         i           =    0;
   int         x_off       =    0;
   int         c           =    0;
   /*---(dittos)-------------------------*/
   strcpy (s_print, "·   á···   SH á·····á·····á·····á·····á·   GL á·····á·····á·····á·····á·   CO á·····á·····á·····á·····   á   Ï");
   /*---(base)---------------------------*/
   x_off =  4;
   for (i = 0; i < 4; ++i) {
      if (g_counts [i].c_line >= 0)  {  s_print [i + x_off] = g_counts [i].c_id;  ++c;  }
   }
   /*---(global)-------------------------*/
   x_off += 5;
   for (i = 0; i < LEN_HUND; ++i) {
      if (g_counts [i].c_type == T_SHARES) {
         if (g_counts [i].c_line >= 0)  {    s_print [i + x_off] = g_counts [i].c_id;  ++c;  }
      }
   }
   /*---(shared)-------------------------*/
   x_off += 5;
   for (i = 0; i < LEN_HUND; ++i) {
      if (g_counts [i].c_type == T_MASTER) {
         if (g_counts [i].c_line >= 0)  {    s_print [i + x_off] = g_counts [i].c_id;  ++c;  }
      }
   }
   /*---(config)-------------------------*/
   x_off += 5;
   for (i = 0; i < LEN_HUND - 2; ++i) {
      if (g_counts [i].c_type == T_CONFIG) {
         if (g_counts [i].c_line >= 0)  {    s_print [i + x_off] = g_counts [i].c_id;  ++c;  }
      }
   }
   /*---(audit)--------------------------*/
   x_off += 2;
   i = yUNIT_reuse_index ('!');
   if (g_counts [i].c_line >= 0)  {    s_print [i + x_off] = g_counts [i].c_id;  ++c;  }
   /*---(use marker)---------------------*/
   if      (c ==  0)  s_print [0] = '¬';
   else if (c <= 10)  s_print [0] = '+';
   else if (c <= 20)  s_print [0] = '*';
   else               s_print [0] = '°';
   /*---(complete)-----------------------*/
   return s_print;
}

char*
yUNIT_reuse_detail    (char a_abbr)
{
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  '-';
   char        x_tdesc     [LEN_TERSE] = "";
   char        x_major     =  '-';
   char        x_ftype     =  '-';
   int         x_line      =  '-';
   char        x_desc      [LEN_LONG]  = "";
   short       x_conds     =    0;
   short       x_steps     =    0;
   char        x_which     [LEN_LABEL] = "";
   strcpy (s_print, "");
   rc = yUNIT_reuse_data (a_abbr, &x_type, x_tdesc, &x_major, NULL, &x_ftype, &x_line, x_desc, x_which, NULL, &x_conds, &x_steps, NULL);
   if (rc <  0) {
      sprintf (s_print, "((n/a))");
   } else if (x_conds > 0) {
      ystruencode (x_desc);
      sprintf (s_print, "%c %c %c %4d  %-51.51s  %4d %4d  %-9.9s %c  %-14.14s  Ï", a_abbr, x_type, x_ftype, x_line, x_desc, x_conds, x_steps, x_tdesc, x_major, x_which);
   } else if (x_line  > 0) {
      ystruencode (x_desc);
      sprintf (s_print, "%c %c %c %4d  %-51.51s  ···· ····  %-9.9s %c  %-14.14s  Ï", a_abbr, x_type, x_ftype, x_line, x_desc, x_tdesc, x_major, x_which);
   } else {
      sprintf (s_print, "%c %c - ····  ´ · · · · ´ · · · · ´ · · · · ´ · · · · ´ · · · · ´  ···· ····  %-9.9s %c  å············æ  Ï", a_abbr, x_type, x_tdesc, x_major);
   }
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                     export/import                            ----===*/
/*====================------------------------------------====================*/
static void  o___EXIM____________o () { return; }

char
yUNIT_reuse_export     (char a_name [LEN_PATH])
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        i           =    0;
   char        c           =    0;
   char       *x_big       = "            #===line   DESC==============================================================   TOP======glob====shar====scrp   MID======cond====ditto=and=usage=======local-reuse-and-list============global-reuse-and-list===========skip   BOT========real=====vars=====void=====skip====DITTO=====real=====void=====skip      WHICH=========    TITLES============>>\n";
   char       *x_sml       = "            #··· ···   ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ··· ·\n";
   /*---(header)-------------------------*/
   DEBUG_MUNIT ylog_uenter   (__FUNCTION__);
   DEBUG_MUNIT ylog_uchar    ("zUNIT_debug", zUNIT_debug);
   /*---(existing)-----------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(defense)------------------------*/
   DEBUG_MUNIT ylog_upoint   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_MUNIT ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MUNIT ylog_uinfo    ("a_name"    , a_name);
   /*---(open file)----------------------*/
   rc = yenv_uopen_detail (__FILE__, __FUNCTION__, __LINE__, a_name, 'w', &f);
   DEBUG_MUNIT ylog_uvalue   ("uopen"     , rc);
   DEBUG_MUNIT ylog_upoint   ("f"         , f);
   --rce;  if (rc < 0 || f == NULL) {
      DEBUG_MUNIT ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(header)-------------------------*/
   fprintf (f, "#!/usr/local/bin/koios\n");
   fprintf (f, "#   shared global reuse inventory\n\n");
   /*---(walk shares)--------------------*/
   for (i = 0; i < LEN_HUND; ++i) {
      DEBUG_MUNIT ylog_ucomplex ("entry"     , "%c %c %c %5d", g_counts [i].c_id, g_counts [i].c_type, g_counts [i].c_ftype, g_counts [i].c_line);
      if (strchr ("gc", g_counts [i].c_type) == NULL) {
         DEBUG_MUNIT ylog_unote    ("not global or config");
         continue;
      }
      if (g_counts [i].c_line < 0) {
         DEBUG_MUNIT ylog_unote    ("line is not set");
         continue;
      }
      if (c % 25 == 0) fprintf (f, "%s", x_big);
      else if (c %  5 == 0 && c > 0) fprintf (f, "%s", x_sml);
      DEBUG_MUNIT ylog_unote    ("found a good one");
      yUNIT_reuse_show (g_counts [i].c_id);
      DEBUG_MUNIT ylog_uinfo    ("s_print"   , s_print);
      fprintf (f, "%s\n", s_print);
      ++c;
   }
   DEBUG_MUNIT ylog_uvalue   ("c"         , c);
   /*---(footer)-------------------------*/
   if (c % 25 >= 4) fprintf (f, "%s", x_big);
   if (c > 0)   fprintf (f, "\n# found %d entries\n", c);
   else         fprintf (f, "\n# zero entries found\n");
   fprintf (f, "\n# end-of-file.  done, finito, completare, whimper [Ï´···\n");
   /*---(close file)---------------------*/
   rc = yenv_uclose_detail (__FILE__, __FUNCTION__, __LINE__, a_name, &f);
   DEBUG_MUNIT ylog_uvalue   ("uclose"    , rc);
   DEBUG_MUNIT ylog_upoint   ("f"         , f);
   --rce;  if (rc < 0 || f != NULL) {
      DEBUG_MUNIT ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(after)--------------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(complete)-----------------------*/
   DEBUG_MUNIT ylog_uexit    (__FUNCTION__);
   return c;
}

char
yUNIT_reuse_header      (char a_ftype, char a_header [LEN_TITLE])
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        i           =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_MUNIT ylog_uenter   (__FUNCTION__);
   /*---(existing)-----------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(defense)------------------------*/
   DEBUG_MUNIT ylog_uchar    ("a_ftype"   , a_ftype);
   --rce;  if (a_ftype == 0 || strchr ("wd", a_ftype) == NULL) {
      DEBUG_MUNIT ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MUNIT ylog_upoint   ("a_header"  , a_header);
   --rce;  if (a_header == NULL || a_header [0] == '\0') {
      DEBUG_MUNIT ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MUNIT ylog_uinfo    ("a_header"  , a_header);
   /*---(open file)----------------------*/
   rc = yenv_uopen_detail (__FILE__, __FUNCTION__, __LINE__, a_header, 'w', &f);
   DEBUG_MUNIT ylog_uvalue   ("uopen"     , rc);
   DEBUG_MUNIT ylog_upoint   ("f"         , f);
   --rce;  if (rc < 0 || f == NULL) {
      DEBUG_MUNIT ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk shares)--------------------*/
   for (i = 0; i < LEN_HUND; ++i) {
      DEBUG_MUNIT ylog_ucomplex ("entry"     , "%c %c %c %4d", g_counts [i].c_id, g_counts [i].c_type, g_counts [i].c_ftype, g_counts [i].c_line);
      /*---(filter)----------------------*/
      if (g_counts [i].c_ftype != a_ftype) {
         DEBUG_MUNIT ylog_unote    ("line is not for current file");
         continue;
      }
      if (strchr ("gc", g_counts [i].c_type) == NULL) {
         DEBUG_MUNIT ylog_unote    ("not global or config");
         continue;
      }
      if (g_counts [i].c_line < 0) {
         DEBUG_MUNIT ylog_unote    ("line is not set");
         continue;
      }
      /*---(write line)------------------*/
      if (c == 0) fprintf (f, "/*········· ´······················ ´·········································*/\n");
      switch (g_counts [i].c_type) {
      case 'g'  :
         fprintf (f, "int         yUNIT_global_%c          (char a_select);\n", g_counts [i].c_major);
         break;
      case 'c'  :
         fprintf (f, "int         yUNIT_config_%c          (char a_select);\n", g_counts [i].c_major);
         break;
      }
      ++c;
      /*---(done)------------------------*/
   }
   DEBUG_MUNIT ylog_uvalue   ("c"         , c);
   if (c >  0) fprintf (f, "/*········· ´······················ ´·········································*/\n");
   /*---(close file)---------------------*/
   rc = yenv_uclose_detail (__FILE__, __FUNCTION__, __LINE__, a_header, &f);
   DEBUG_MUNIT ylog_uvalue   ("uclose"    , rc);
   DEBUG_MUNIT ylog_upoint   ("f"         , f);
   --rce;  if (rc < 0 || f != NULL) {
      DEBUG_MUNIT ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return c;
}

char
yUNIT_reuse_list        (void)
{
   int         i           =    0;
   char        c           =    0;
   /*> printf ("yUNIT_reuse_list\n");                                                 <*/
   /*---(header)-------------------------*/
   DEBUG_MUNIT   ylog_uenter  (__FUNCTION__);
   for (i = 0; i < LEN_HUND; ++i) {
      if (g_counts [i].c_line < 0)  continue;
      yUNIT_reuse_show (g_counts [i].c_id);
      printf ("%2d %s\n", c, s_print);
      ++c;
   }
   /*---(after)--------------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return c;
}

char
yUNIT_reuse_import     (char a_name [LEN_PATH])
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        i           =    0;
   char        c           =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_MUNIT  ylog_uenter   (__FUNCTION__);
   /*---(existing)-----------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(defense)------------------------*/
   DEBUG_MUNIT  ylog_upoint   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MUNIT  ylog_uinfo    ("a_name"    , a_name);
   /*---(open file)----------------------*/
   rc = yenv_uopen_detail (__FILE__, __FUNCTION__, __LINE__, a_name, 'r', &f);
   DEBUG_MUNIT  ylog_uvalue   ("uopen"     , rc);
   DEBUG_MUNIT  ylog_upoint   ("f"         , f);
   --rce;  if (rc < 0 || f == NULL) {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(parse shares)-------------------*/
   for (i = 0; i < LEN_HUND; ++i) {
      /*---(read data)-------------------*/
      fgets   (x_recd, LEN_RECD, f);
      if (feof (f)) {
         DEBUG_MUNIT  ylog_unote    ("found end-of-file");
         break;
      }
      /*---(fix line)--------------------*/
      l = strlen (x_recd);
      if (x_recd [l - 1] == '\n')   x_recd [--l] = '\0';
      DEBUG_MUNIT  ylog_ucomplex ("x_recd"    , "%3då%sæ", l, x_recd);
      /*---(filter)----------------------*/
      if (x_recd [0] == '\0')  continue;
      if (x_recd [0] == ' ')   continue;
      if (x_recd [0] == '#')   continue;
      /*---(parse)-----------------------*/
      rc = yUNIT_reuse_parse ('g', x_recd);
      DEBUG_MUNIT  ylog_uvalue   ("parse"     , rc);
      ++c;
      /*---(done)------------------------*/
   }
   /*---(close file)---------------------*/
   rc = yenv_uclose_detail (__FILE__, __FUNCTION__, __LINE__, a_name, &f);
   DEBUG_MUNIT  ylog_uvalue   ("uclose"    , rc);
   DEBUG_MUNIT  ylog_upoint   ("f"         , f);
   --rce;  if (rc < 0 || f != NULL) {
      DEBUG_MUNIT  ylog_uexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(after)--------------------------*/
   DEBUG_MUNIT ylog_uinfo    ("used"      , yUNIT_reuse_used ());
   /*---(complete)-----------------------*/
   DEBUG_MUNIT  ylog_uexit    (__FUNCTION__);
   return c;
}


