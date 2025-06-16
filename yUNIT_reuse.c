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

#define     T_MASTER    'm'
#define     T_SHARES    'r'
#define     T_CONFIG    'c'



/*====================------------------------------------====================*/
/*===----                        script level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
yUNIT_reuse_type        (char a_abbr)
{
   if      (a_abbr == 0)                          return '-';
   else if (strchr (YSTR_UPPER, a_abbr) != NULL)  return T_MASTER;
   else if (strchr (YSTR_LOWER, a_abbr) != NULL)  return T_SHARES;
   else if (strchr (YSTR_GREEK, a_abbr) != NULL)  return T_CONFIG;
   return '-';
}

int
yUNIT_reuse_index       (char a_abbr)
{
   int         i           =    0;
   if (a_abbr == ' ')   return -1;
   if (a_abbr == '·')   return -1;
   if (a_abbr == '\0')  return -1;
   for (i = 0; i < LEN_HUND; ++i) {
      if (YUNIT_SHARES [i] == a_abbr)   return i;
   }
   /*---(trouble)------------------------*/
   return -1;
}

char
yunit_reuse_clear       (char n)
{
   /*---(identifier)---------------------*/
   g_counts [n].c_id     = YUNIT_SHARES [n];
   g_counts [n].c_type   = yUNIT_reuse_type (g_counts [n].c_id);
   g_counts [n].c_line   =   -1;
   strcpy (g_counts [n].c_desc, "·");
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
   char        n           =   -1;
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   if (n < 0) return n;
   yunit_reuse_clear (n);
   /*---(complete)-----------------------*/
   return 0;
}

char
yUNIT_reuse_purge       (char a_type)
{
   /*---(locals)-------------------------*/
   int         i           =    0;
   /*---(set defaults)-------------------*/
   for (i = 0; i < LEN_HUND; ++i) {
      if      (a_type == '*')                  yunit_reuse_clear (i);
      else if (g_counts [i].c_type == a_type)  yunit_reuse_clear (i);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yUNIT_reuse_data        (char a_abbr, char *r_type, char r_tdesc [LEN_TERSE], int *r_line, char r_desc [LEN_LONG], short *r_conds, short *r_steps, char *r_called)
{
   char        rce         =  -10;
   int         n           =    0;
   if (r_type  != NULL)  *r_type   = '-';
   if (r_line  != NULL)  *r_line   =  -1;
   if (r_tdesc != NULL)  strcpy (r_tdesc, "");
   if (r_desc  != NULL)  strcpy (r_desc , "");
   if (r_conds != NULL)  *r_conds  =  -1;
   if (r_steps != NULL)  *r_steps  =  -1;
   n = yUNIT_reuse_index (a_abbr);
   --rce;  if (n < 0)  return rce;
   if (r_type  != NULL)  *r_type   = g_counts [n].c_type;
   if (r_tdesc != NULL) {
      switch (g_counts [n].c_type) {
      case T_MASTER : strlcpy (r_tdesc, "GLOBAL" , LEN_TERSE);  break;
      case T_SHARES : strlcpy (r_tdesc, "SHARED" , LEN_TERSE);  break;
      case T_CONFIG : strlcpy (r_tdesc, "CONFIG" , LEN_TERSE);  break;
      default       : strlcpy (r_tdesc, "special", LEN_TERSE);  break;
      }
   }
   if (r_line  != NULL)  *r_line   = g_counts [n].c_line;
   if (r_desc  != NULL)  strlcpy (r_desc, g_counts [n].c_desc, LEN_LONG);
   if (r_conds != NULL)  *r_conds  = g_counts [n].c_midd;
   if (r_steps != NULL)  *r_steps  = g_counts [n].c_step;
   return 1;
}

char
yUNIT_reuse_save        (char a_abbr)
{
   /*---(locals)-------------------------*/
   char        n           =   -1;
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   if (n < 0) return n;
   yunit_reuse_clear (n);
   /*---(identifier)---------------------*/
   g_counts [n].c_line   = g_counts [SCRP_ID].c_line;
   strcpy (g_counts [n].c_desc, g_counts [SCRP_ID].c_desc);
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
   /*---(done)---------------------------*/
   return 1;
}

char
yUNIT_reuse_add         (char a_abbr)
{
   /*---(locals)-------------------------*/
   char        n           =   -1;
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   if (n < 0) return n;
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
   /*---(done)---------------------------*/
   return 1;
}

char
yUNIT_reuse_set         (char a_abbr, int a_line, char a_desc [LEN_LONG])
{
   /*---(locals)-------------------------*/
   char        n           =   -1;
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   if (n < 0) return n;
   yunit_reuse_clear (n);
   /*---(update list)--------------------*/
   g_counts [n].c_line = a_line;
   if (a_desc != NULL)  strlcpy (g_counts [n].c_desc, a_desc, LEN_LONG);
   else                 strcpy  (g_counts [n].c_desc, "");
   /*---(complete)-----------------------*/
   return 1;
}

char
yUNIT_reuse_called      (char a_abbr)
{
   /*---(locals)-------------------------*/
   char        n           =   -1;
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   if (n < 0) return n;
   /*---(update list)--------------------*/
   ++(g_counts [n].c_called);
   /*---(complete)-----------------------*/
   return 1;
}

char*
yUNIT_reuse_show        (char a_abbr)
{
   /*---(locals)-------------------------*/
   char        n           =   -1;
   char        x_prefix    [LEN_FULL]  = "";
   /*---(get index)----------------------*/
   n = yUNIT_reuse_index (a_abbr);
   if (n < 0) return "((n/a))";
   sprintf (x_prefix, "%c  %4d  %-65.65s", g_counts [n].c_id, g_counts [n].c_line, g_counts [n].c_desc);
   return yunit_stats_show (x_prefix, n);
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
   /*---(defense)------------------------*/
   --rce;  if (a_recd == NULL)        return rce;
   --rce;  if (strlen (a_recd) == 0)  return rce;
   strlcpy (x_recd, a_recd, LEN_RECD);
   /*---(initial parse)------------------*/
   p = strtok_r (x_recd, q, &r);
   /*---(walk data)----------------------*/
   --rce;  for (i = 0; i <= 24; ++i) {
      /*---(check field)-----------------*/
      if (p == NULL)   return rce;
      strlcpy   (x_field, p, LEN_LONG);
      ystrutrim (x_field,    LEN_LONG);
      /*---(master)----------------------*/
      --rce;  if (a_type == 'g') {
         switch (i) {
         case  0 :  n = yUNIT_reuse_index (x_field [0]);
                    if (n < 0)  return rce;
                    break;
         case  1 :  g_counts [n].c_line   = atoi (x_field);
                    break;
         case  2 :  strlcpy (g_counts [n].c_desc  , x_field, LEN_LONG);
                    break;
         }
      } else if (a_type == 'r') {
         switch (i) {
         case  0 :  n = yUNIT_reuse_index ('!'); 
                    if (n < 0)  return rce;
                    if (g_counts [n].c_line < 0)  g_counts [n].c_line   = 0;
                    break;
         case  1 :  strlcpy (g_counts [n].c_desc  , x_field, LEN_LONG);
                    break;
         }
      } else if (a_type == 'u') {
         switch (i) {
         case  2 :  n = yUNIT_reuse_index (x_field [0]);
                    if (n < 0)  return rce;
                    if (g_counts [n].c_line < 0)  g_counts [n].c_line   = 0;
                    break;
         }
      } else {
         return rce;
         break;
      }
      /*---(script-level)----------------*/
      switch (i) {
      case  3 :  g_counts [n].c_topp   = atoi (x_field);  break;
      case  4 :  g_counts [n].c_glob   = atoi (x_field);  break;
      case  5 :  g_counts [n].c_shar   = atoi (x_field);  break;
      case  6 :  g_counts [n].c_scrp   = atoi (x_field);  break;
      }
      /*---(condition-level)-------------*/
      switch (i) {
      case  7 :  g_counts [n].c_midd   = atoi (x_field);  break;
      case  8 :  g_counts [n].c_cond   = atoi (x_field);  break;
      case  9 :  g_counts [n].c_ditt   = atoi (x_field);  break;
      case 10 :  strlcpy (g_counts [n].c_dittos, x_field, LEN_LABEL);  break;
      case 11 :  g_counts [n].c_lreu   = atoi (x_field);  break;
      case 12 :  strlcpy (g_counts [n].c_lreuse, x_field, LEN_HUND);   break;
      case 13 :  g_counts [n].c_greu   = atoi (x_field);  break;
      case 14 :  strlcpy (g_counts [n].c_greuse, x_field, LEN_HUND);   break;
      case 15 :  g_counts [n].c_skipc  = atoi (x_field);  break;
      }
      /*---(step-level)------------------*/
      switch (i) {
      case 16 :  g_counts [n].c_step   = atoi (x_field);  break;
      case 17 :  g_counts [n].c_real   = atoi (x_field);  break;
      case 18 :  g_counts [n].c_vars   = atoi (x_field);  break;
      case 19 :  g_counts [n].c_void   = atoi (x_field);  break;
      case 20 :  g_counts [n].c_skips  = atoi (x_field);  break;
      }
      /*---(ditto)-----------------------*/
      switch (i) {
      case 21 :  g_counts [n].c_dstep  = atoi (x_field);  break;
      case 22 :  g_counts [n].c_dreal  = atoi (x_field);  break;
      case 23 :  g_counts [n].c_dvoid  = atoi (x_field);  break;
      case 24 :  g_counts [n].c_dskip  = atoi (x_field);  break;
      }
      /*---(next)------------------------*/
      p = strtok_r (NULL, q, &r);
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
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
   int         x_line      =  '-';
   char        x_desc      [LEN_LONG]  = "";
   short       x_conds     =    0;
   short       x_steps     =    0;
   strcpy (s_print, "");
   rc = yUNIT_reuse_data (a_abbr, &x_type, x_tdesc, &x_line, x_desc, &x_conds, &x_steps, NULL);
   if (rc <= 0) {
      sprintf (s_print, "((n/a))");
      /*> sprintf (s_print, "- · ····  ´ · · · · ´ · · · · ´ · · · · ´ · · · · ´ · · · · ´  ···· ····  ·········  Ï");   <*/
   } else if (x_conds > 0) {
      ystruencode (x_desc);
      sprintf (s_print, "%c %c %4d  %-51.51s  %4d %4d  %-9.9s  Ï", a_abbr, x_type, x_line, x_desc, x_conds, x_steps, x_tdesc);
   } else if (x_line  > 0) {
      ystruencode (x_desc);
      sprintf (s_print, "%c %c %4d  %-51.51s  ···· ····  %-9.9s  Ï", a_abbr, x_type, x_line, x_desc, x_tdesc);
   } else {
      sprintf (s_print, "%c %c ····  ´ · · · · ´ · · · · ´ · · · · ´ · · · · ´ · · · · ´  ···· ····  %-9.9s  Ï", a_abbr, x_type, x_tdesc);
   }
   return s_print;
}

char
yUNIT_reuse_export     (void *a_file)
{
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        i           =    0;
   char        c           =    0;
   --rce;  if (a_file == NULL)  return rce;
   f = (FILE *) a_file;
   for (i = 0; i < LEN_HUND; ++i) {
      if (strchr ("mc", g_counts [i].c_type) == NULL)  continue;
      if (g_counts [i].c_line < 0)                     continue;
      yUNIT_reuse_show (g_counts [i].c_id);
      fprintf (f, "%s\n", s_print);
      ++c;
   }
   return c;
}

char
yUNIT_reuse_import      (void *a_file)
{
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        i           =    0;
   char        c           =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   --rce;  if (a_file == NULL)  return rce;
   f = (FILE *) a_file;
   for (i = 0; i < LEN_HUND; ++i) {
      /*---(read data)-------------------*/
      fgets   (x_recd, LEN_RECD, f);
      if (feof (f))  break;
      /*---(fix line)--------------------*/
      l = strlen (x_recd);
      if (x_recd [l - 1] == '\n')   x_recd [--l] = '\0';
      /*---(parse)-----------------------*/
      yUNIT_reuse_parse ('g', x_recd);
      ++c;
      /*---(done)------------------------*/
   }
   return c;
}


