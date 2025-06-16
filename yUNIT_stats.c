#include "yUNIT.h"
#include "yUNIT_priv.h"



static char  s_dittoing  = '-';


/*>                                                                                   <* 
 *> #define FULL_ID    0                                                              <* 
 *> #define FULL       g_counts [0]                                                   <* 
 *>                                                                                   <* 
 *> #define UNIT_ID    1                                                              <* 
 *> #define UNIT       g_counts [1]                                                   <* 
 *>                                                                                   <* 
 *> #define SCRP_ID    2                                                              <* 
 *> #define SCRP       g_counts [2]                                                   <* 
 *>                                                                                   <* 
 *> #define COND_ID    3                                                              <* 
 *> #define COND       g_counts [3]                                                   <* 
 *>                                                                                   <*/

char
yunit_stats_clear       (char a_type)
{
   /*---(clear)--------------------------*/
   switch (a_type) {
   case YUNIT_IS_FULL :
      yunit_reuse_clear (COND_ID);
      yunit_reuse_clear (SCRP_ID);
      yunit_reuse_clear (UNIT_ID);
      yunit_reuse_clear (FULL_ID);
      yunit_ditto_purge  ();
      yunit_stats_summary (0x1, "", '0', "", '-');
      break;
   case YUNIT_IS_UNIT :
      yunit_reuse_clear (COND_ID);
      yunit_reuse_clear (SCRP_ID);
      yunit_reuse_clear (UNIT_ID);
      yunit_ditto_purge  ();
      break;
   case YUNIT_IS_SCRP :
      yunit_reuse_clear (COND_ID);
      yunit_reuse_clear (SCRP_ID);
      yunit_ditto_purge  ();
      break;
   case YUNIT_IS_COND :
      yunit_reuse_clear (COND_ID);
      break;
   }
   s_dittoing = '-';
   /*---(complete)-----------------------*/
   return 0;
}

char
yUNIT_stats_purge       (char a_usage, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(call all clears)----------------*/
   yunit_stats_clear (YUNIT_IS_FULL);
   yunit_stats_summary (0x1, "", '0', "", '-');
   /*---(clear share areas)--------------*/
   for (i = 0; i < LEN_HUND; ++i)   yunit_reuse_clear (i);
   /*---(save-back)----------------------*/
   if (r_cunit != NULL)  *r_cunit = FULL.c_unit;
   if (r_cscrp != NULL)  *r_cscrp = UNIT.c_scrp;
   if (r_ccond != NULL)  *r_ccond = SCRP.c_midd;
   if (r_cstep != NULL)  *r_cstep = COND.c_step;
   /*---(complete)-----------------------*/
   return 0;
}

char
yunit_stats_summary     (FILE *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_LABEL], char a_major)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  '-';
   char        x_verb      [LEN_LABEL] = "";
   char        x_label     [LEN_HUND]  = "";
   char        x_ref       [LEN_SHORT] = "";
   char        x_stat      [LEN_TITLE] = "";
   char        x_prefix    [LEN_FULL]  = "";
   char        x_suffix    [LEN_FULL]  = "";
   char        x_header    [LEN_LABEL] = "";
   char       *x_title     = "=================================================================  ID   TOP======glob====shar====scrp   MID======cond====ditto=and=usage=======local-reuse-and-list============global-reuse-and-list===========skip   BOT======real====vars====void====skip===DITTO====real====void====skip  ";
   /*---(saves)--------------------------*/
   static char x_save      [LEN_LABEL] = "";
   static char x_stype     =  '-';
   static char x_smajor    =  '-';
   /*---(defense)------------------------*/
   --rce;  if (a_conv  == NULL)  return rce;
   --rce;  if (a_nscrp == NULL)  return rce;
   /*---(unit testing)-------------------*/
   if (a_type == '0') { strcpy (x_save, "");  x_stype = '-';  x_smajor = '-'; return 5; }
   if (a_type == '!') { fprintf (a_conv, "%-6.6s %c (%3d/%c)\n", x_save, x_stype, (uchar) x_smajor, (x_smajor > 32) ? x_smajor : '·'); return 2; }
   /*---(defense)------------------------*/
   if (a_type == 0 || strchr (YUNIT_IS_SUMMS, a_type) == NULL)   return 0;
   /*---(limits)-------------------------*/
   if (a_type == '-')                                              a_major = '-';
   if (a_type == YUNIT_IS_SCRP && (a_major < 0 || a_major > 100))  a_major = '?';
   /*---(current type)-------------------*/
   --rce;
   if        (strcmp (a_verb, "SCRP"  ) == 0)   x_type = YUNIT_IS_SCRP;
   else if   (strcmp (a_verb, "GLOBAL") == 0)   x_type = YUNIT_IS_GLOB;
   else if   (strcmp (a_verb, "CONFIG") == 0)   x_type = YUNIT_IS_CONF;
   else if   (strcmp (a_verb, "SHARED") == 0)   x_type = YUNIT_IS_SHAR;
   else if   (strcmp (a_verb, "SECT"  ) == 0)   x_type = YUNIT_IS_SECT;
   else if   (strcmp (a_verb, "UNIT"  ) == 0) { x_type = YUNIT_IS_UNIT; x_stype = YUNIT_IS_UNIT; }
   else if   (strcmp (a_verb, "FULL"  ) == 0) { x_type = YUNIT_IS_FULL; x_stype = YUNIT_IS_FULL; }
   else { fprintf (a_conv, "# BOOM===  %s \n", x_title); return rce; }
   /*---(master exception)---------------*/
   if (x_type == YUNIT_IS_UNIT && strcmp (a_nscrp, "master.unit") == 0)  { x_type = YUNIT_IS_MAST; x_stype = YUNIT_IS_MAST;  }
   /*---(data preparation)---------------*/
   switch (x_stype) {
   case YUNIT_IS_FULL  :  strcpy (x_verb, "LUFF        ");  strcpy (x_header, "#===========");  strcpy (x_label, "full program statistics -----------------------------------------");  strcpy  (x_ref, " -");                     sprintf (x_stat, "    %4d  %4d  %4d  %4d", FULL.c_topp, FULL.c_glob, FULL.c_shar, FULL.c_scrp);   break;
   case YUNIT_IS_MAST  :  strcpy (x_verb, "RETSAM      ");  strcpy (x_header, "#===========");  strcpy (x_label, "final master file statistics ------------------------------------");  strcpy  (x_ref, " -");                     sprintf (x_stat, "    %4d  %4d  %4d  %4d", UNIT.c_topp, UNIT.c_glob, UNIT.c_shar, UNIT.c_scrp);   break;
   case YUNIT_IS_UNIT  :  strcpy (x_verb, "TNIU        ");  strcpy (x_header, "#===========");  strcpy (x_label, "final unit test statistics --------------------------------------");  strcpy  (x_ref, " -");                     sprintf (x_stat, "    %4d  %4d  %4d  %4d", UNIT.c_topp, UNIT.c_glob, UNIT.c_shar, UNIT.c_scrp);   break;
   case YUNIT_IS_SCRP  :  strcpy (x_verb, "   PRCS     ");  strcpy (x_header, "   #========");  strcpy (x_label, "script statistics -----------------------------------------------");  sprintf (x_ref, "%2d", UNIT.c_scrp);       sprintf (x_stat, "       1     ·     ·     1");   break;
   case YUNIT_IS_GLOB  :  strcpy (x_verb, "   LABOLG   ");  strcpy (x_header, "   #========");  strcpy (x_label, "global shared code statistics -----------------------------------");  sprintf (x_ref, " %c", (uchar) x_smajor);  sprintf (x_stat, "       1     1     ·     ·");   break;
   case YUNIT_IS_CONF  :  strcpy (x_verb, "   GIFNOC   ");  strcpy (x_header, "   #========");  strcpy (x_label, "global shared code statistics -----------------------------------");  sprintf (x_ref, " %c", (uchar) x_smajor);  sprintf (x_stat, "       1     1     ·     ·");   break;
   case YUNIT_IS_SHAR  :  strcpy (x_verb, "   DERAHS   ");  strcpy (x_header, "   #========");  strcpy (x_label, "local shared code statistics ------------------------------------");  sprintf (x_ref, " %c", x_smajor);          sprintf (x_stat, "       1     ·     1     ·");   break;
   }
   /*---(header)-------------------------*/
   if (x_stype != '-')  {
      /*---(header)----------------------*/
      if (strchr (YUNIT_IS_FULLS YUNIT_IS_UNITS, x_type) != NULL)   fprintf (a_conv, "\n\n");
      fprintf (a_conv, "\n%-12.12s  %s \n", x_header, x_title);
      /*---(prefix)----------------------*/
      sprintf (x_prefix, "%-12.12s  %-65.65s  %-2.2s", x_verb, x_label, x_ref);
      /*---(suffix)----------------------*/
      switch (x_type) {
      case YUNIT_IS_FULL :
         fprintf (a_conv, "%s\n", yunit_full_show (x_prefix));
         break;
      case YUNIT_IS_UNIT : case YUNIT_IS_MAST :
         fprintf (a_conv, "%s\n", yunit_unit_show (x_prefix));
         break;
      default :
         fprintf (a_conv, "%s\n", yunit_scrp_show (x_prefix));
         break;
      }
      /*---(done)------------------------*/
   }
   /*---(save)---------------------------*/
   if      (strcmp (x_save, "") == 0)  rc = 3;
   else if (x_stype == '-')            rc = 0;
   else                                rc = 1;
   strcpy (x_save, a_verb);
   x_smajor = a_major;
   x_stype  = x_type;
   /*---(complete)-----------------------*/
   return rc;
}

char
yUNIT_stats_full        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_major, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_usage == 0)        return rce;
   --rce;  if (a_nscrp == NULL)     return rce;
   --rce;  if (a_type  == 0)        return rce;
   --rce;  if (a_verb  == NULL)     return rce;
   --rce;  if (a_verb [0] == '\0')  return rce;
   --rce;  if (a_major == 0)        return rce;
   /*---(quick-out)----------------------*/
   --rce;  if (strchr (YUNIT_IS_FULLS, a_type) == NULL)  return rce;
   /*---(previous summary)---------------*/
   yunit_stats_summary (a_conv, a_nscrp, a_type, a_verb, a_major);
   /*---(clear)--------------------------*/
   yunit_stats_clear (YUNIT_IS_FULL);
   /*---(save-back)----------------------*/
   if (r_cunit != NULL)  *r_cunit = FULL.c_unit;
   if (r_cscrp != NULL)  *r_cscrp = UNIT.c_scrp;
   if (r_ccond != NULL)  *r_ccond = SCRP.c_midd;
   if (r_cstep != NULL)  *r_cstep = COND.c_step;
   /*---(done)---------------------------*/
   return 1;
}

char
yUNIT_stats_unit        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_major, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_usage == 0)        return rce;
   --rce;  if (a_nscrp == NULL)     return rce;
   --rce;  if (a_type  == 0)        return rce;
   --rce;  if (a_verb  == NULL)     return rce;
   --rce;  if (a_verb [0] == '\0')  return rce;
   --rce;  if (a_major == 0)        return rce;
   /*---(quick-out)----------------------*/
   --rce;  if (strchr (YUNIT_IS_UNITS, a_type) == NULL)  return rce;
   /*---(previous summary)---------------*/
   yunit_stats_summary (a_conv, a_nscrp, YUNIT_IS_SECT, "SECT", '-');
   yunit_stats_summary (a_conv, a_nscrp, a_type, a_verb, a_major);
   /*---(clear)--------------------------*/
   yunit_stats_clear (YUNIT_IS_UNIT);
   /*---(add to overall)-----------------*/
   ++(FULL.c_unit);
   /*---(save-back)----------------------*/
   if (r_cunit != NULL)  *r_cunit = FULL.c_unit;
   if (r_cscrp != NULL)  *r_cscrp = UNIT.c_scrp;
   if (r_ccond != NULL)  *r_ccond = SCRP.c_midd;
   if (r_cstep != NULL)  *r_cstep = COND.c_step;
   /*---(done)---------------------------*/
   return 1;
}

char
yUNIT_stats_scrp        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_major, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_usage == 0)        return rce;
   --rce;  if (a_nscrp == NULL)     return rce;
   --rce;  if (a_type  == 0)        return rce;
   --rce;  if (a_verb  == NULL)     return rce;
   --rce;  if (a_verb [0] == '\0')  return rce;
   --rce;  if (a_major == 0)        return rce;
   /*---(quick-out)----------------------*/
   --rce;  if (strchr (YUNIT_IS_TOPPS, a_type) == NULL)  return rce;
   /*> if (a_usage != YUNIT_BUILD)  return 0;                                         <*/
   /*---(previous summary)---------------*/
   if (a_type == YUNIT_IS_SCRP) a_major = UNIT.c_scrp;
   yunit_stats_summary (a_conv, a_nscrp, a_type, a_verb, a_major);
   /*---(fixes)--------------------------*/
   if (a_type == YUNIT_IS_SHAR && strchr (YSTR_LOWER, a_major) == NULL)  a_type = YUNIT_IS_GLOB;
   /*---(clear)--------------------------*/
   yunit_stats_clear (YUNIT_IS_SCRP);
   /*---(statistics)---------------------*/
   switch (a_type) {
   case YUNIT_IS_SCRP : /* script   */  ++(SCRP.c_scrp);  ++(UNIT.c_scrp);  ++(FULL.c_scrp);  SCRP.c_id = UNIT.c_scrp;  break;
   case YUNIT_IS_GLOB : /* g.share  */  ++(SCRP.c_glob);  ++(UNIT.c_glob);  ++(FULL.c_glob);  SCRP.c_id = a_major;      break;
   case YUNIT_IS_SHAR : /* l.share  */  ++(SCRP.c_shar);  ++(UNIT.c_shar);  ++(FULL.c_shar);  SCRP.c_id = a_major;      break;
   }
   /*---(add to overall)-----------------*/
   if (a_type != YUNIT_IS_SECT) {
      ++(SCRP.c_topp);  ++(UNIT.c_topp);  ++(FULL.c_topp);
   }
   /*---(save-back)----------------------*/
   if (r_cunit != NULL)  *r_cunit = FULL.c_unit;
   if (r_cscrp != NULL)  *r_cscrp = UNIT.c_scrp;
   if (r_ccond != NULL)  *r_ccond = SCRP.c_midd;
   if (r_cstep != NULL)  *r_cstep = COND.c_step;
   /*---(done)---------------------------*/
   return 1;
}

char /* zero globals or static variables */
yunit_ditto_stats       (char a_type, char a_ditto, char b_show [LEN_LABEL], char *r_dittoing)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =    0;
   /*---(default)------------------------*/
   if (strchr (YUNIT_IS_BOTTS, a_type) == NULL) {
      if (r_dittoing != NULL)  *r_dittoing = '-';
   }
   /*---(quick-out)----------------------*/
   if (strchr (YUNIT_IS_MIDDS, a_type) == NULL)   return 0;
   /*---(defense)------------------------*/
   if (a_ditto < '0')  return 0;
   if (a_ditto > '9')  return 0;
   n = a_ditto - '0';
   /*---(check COND)---------------------*/
   --rce;  if (a_type == YUNIT_IS_COND) {
      if  (b_show [n] != '·')   return rce;
      b_show [n] = '´';
      if (r_dittoing != NULL)  *r_dittoing = a_ditto;
      return 1;
   }
   /*---(check DITTO)--------------------*/
   --rce;  if (a_type == YUNIT_IS_DITT) {
      if      (b_show [n] == '´')                         b_show [n] = '1';
      else if (strchr ("12345678", b_show [n]) != NULL)   b_show [n] = b_show [n] + 1;
      else if (strchr ("9*", b_show [n]) != NULL)         b_show [n] = '*';
      else                                                return rce;
      return 2;
   }
   /*---(complete)-----------------------*/
   return 3;
}

char /* zero globals or static variables */
yunit_stats_reuse       (char a_type, char a_major, char b_full [LEN_HUND], char b_unit [LEN_HUND], char b_scrp [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_SHORT] = "";
   /*---(quick-out)----------------------*/
   if (strchr ("gr", a_type) == NULL)   return 0;
   /*---(defense)------------------------*/
   --rce;  if (a_major == 0)  return rce;
   --rce;  if (a_type == YUNIT_IS_REUS && strchr (YSTR_LOWER, a_major)            == NULL)  return rce;
   --rce;  if (a_type == YUNIT_IS_GREU && strchr (YSTR_UPPER YSTR_GREEK, a_major) == NULL)  return rce;
   /*---(add to lists)-------------------*/
   sprintf (t, "%c", a_major);
   if (b_full != NULL && strchr (b_full, a_major) == NULL)  strlcat (b_full, t, LEN_HUND);
   if (b_unit != NULL && strchr (b_unit, a_major) == NULL)  strlcat (b_unit, t, LEN_HUND);
   if (b_scrp != NULL)                                      strlcat (b_scrp, t, LEN_HUND);
   /*---(complete)-----------------------*/
   return 1;
}

char
yUNIT_stats_cond        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_desc [LEN_LONG], char a_dittoing, char a_ditto, char a_major, char a_share, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_SHORT] = "";
   /*---(defense)------------------------*/
   --rce;  if (a_usage == 0)        return rce;
   --rce;  if (a_nscrp == NULL)     return rce;
   --rce;  if (a_type  == 0)        return rce;
   --rce;  if (a_verb  == NULL)     return rce;
   --rce;  if (a_verb [0] == '\0')  return rce;
   --rce;  if (a_desc  == NULL)     return rce;
   --rce;  if (a_dittoing == 0)     return rce;
   --rce;  if (a_ditto == 0)        return rce;
   --rce;  if (a_major == 0)        return rce;
   --rce;  if (a_share == 0)        return rce;
   /*---(quick-out)----------------------*/
   --rce;  if (strchr (YUNIT_IS_MIDDS, a_type) == NULL)  return rce;
   /*---(fixes for shares)---------------*/
   if (a_type == YUNIT_IS_REUS && strchr (YSTR_LOWER, a_major) == NULL)  a_type = YUNIT_IS_GREU;
   /*---(fixes for build)----------------*/
   if (a_usage == YUNIT_BUILD) {
      if (a_type == YUNIT_IS_COND && a_dittoing == 'y')  a_type = YUNIT_IS_DITT;
   }
   /*---(clear)--------------------------*/
   yunit_stats_clear (YUNIT_IS_COND);
   /*---(statistics)---------------------*/
   switch (a_type) {
   case YUNIT_IS_COND : /* cond     */  ++(COND.c_cond);   ++(SCRP.c_cond);   ++(UNIT.c_cond);   ++(FULL.c_cond);   break;
   case YUNIT_IS_DITT : /* ditto    */  ++(COND.c_ditt);   ++(SCRP.c_ditt);   ++(UNIT.c_ditt);   ++(FULL.c_ditt);   break;
   case YUNIT_IS_REUS : /* l.reuse  */  ++(COND.c_lreu);   ++(SCRP.c_lreu);   ++(UNIT.c_lreu);   ++(FULL.c_lreu);   break;
   case YUNIT_IS_GREU : /* g.reuse  */  ++(COND.c_greu);   ++(SCRP.c_greu);   ++(UNIT.c_greu);   ++(FULL.c_greu);   break;
   }
   /*---(add to overall)-----------------*/
   ++(COND.c_midd);  ++(SCRP.c_midd);  ++(UNIT.c_midd);  ++(FULL.c_midd);
   /*---(skips)----------------*/
   if (strchr (a_desc, 'å') != NULL)  { ++(SCRP.c_skipc);  ++(UNIT.c_skipc);  ++(FULL.c_skipc); }
   /*---(reuses)---------------*/
   if (a_type == YUNIT_IS_REUS)   rc = yunit_stats_reuse (a_type, a_major, FULL.c_lreuse, UNIT.c_lreuse, SCRP.c_lreuse);
   if (a_type == YUNIT_IS_GREU)   rc = yunit_stats_reuse (a_type, a_major, FULL.c_greuse, UNIT.c_greuse, SCRP.c_greuse);
   /*> sprintf (t, "%c", a_major);                                                               <* 
    *> if (a_type == YUNIT_IS_REUS)  {                                                           <* 
    *>    if (strchr (FULL.c_lreuse, a_major) == NULL)  strlcat (FULL.c_lreuse, t, LEN_LABEL);   <* 
    *>    if (strchr (UNIT.c_lreuse, a_major) == NULL)  strlcat (UNIT.c_lreuse, t, LEN_LABEL);   <* 
    *>    if (strchr (SCRP.c_lreuse, a_major) == NULL)  strlcat (SCRP.c_lreuse, t, LEN_LABEL);   <* 
    *> }                                                                                         <* 
    *> if (a_type == YUNIT_IS_GREU)  {                                                           <* 
    *>    if (strchr (FULL.c_greuse, a_major) == NULL)  strlcat (FULL.c_greuse, t, LEN_LABEL);   <* 
    *>    if (strchr (UNIT.c_greuse, a_major) == NULL)  strlcat (UNIT.c_greuse, t, LEN_LABEL);   <* 
    *>    if (strchr (SCRP.c_greuse, a_major) == NULL)  strlcat (SCRP.c_greuse, t, LEN_LABEL);   <* 
    *> }                                                                                         <*/
   /*---(dittos)---------------*/
   rc = yunit_ditto_stats (a_type, a_ditto, SCRP.c_dittos, &s_dittoing);
   /*> if (a_type == YUNIT_IS_COND && (a_ditto >= '0' && a_ditto <= '9'))  SCRP.c_dittos [a_ditto - '0'] = '´';                                 <* 
    *> if (a_type == YUNIT_IS_DITT && (a_ditto >= '0' && a_ditto <= '9')) {                                                                     <* 
    *>    if      (strchr ("´·", SCRP.c_dittos [a_ditto - '0']) != NULL)   SCRP.c_dittos [a_ditto - '0'] = '1';                                 <* 
    *>    else if (strchr ("9*", SCRP.c_dittos [a_ditto - '0']) != NULL)   SCRP.c_dittos [a_ditto - '0'] = '*';                                 <* 
    *>    else                                                             SCRP.c_dittos [a_ditto - '0'] = SCRP.c_dittos [a_ditto - '0'] + 1;   <* 
    *> }                                                                                                                                        <*/
   rc = yunit_ditto_apply (a_usage, a_type, a_ditto);
   /*---(save-back)----------------------*/
   if (r_cunit != NULL)  *r_cunit = FULL.c_unit;
   if (r_cscrp != NULL)  *r_cscrp = UNIT.c_scrp;
   if (r_ccond != NULL)  *r_ccond = SCRP.c_midd;
   if (r_cstep != NULL)  *r_cstep = COND.c_step;
   /*---(done)---------------------------*/
   return 1;
}

char
yUNIT_stats_step        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_desc [LEN_LONG], char a_dittoing, char a_ditto, char a_major, char a_share, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_skip      =  '-';
   /*---(defense)------------------------*/
   --rce;  if (a_usage == 0)        return rce;
   --rce;  if (a_nscrp == NULL)     return rce;
   --rce;  if (a_type  == 0)        return rce;
   --rce;  if (a_verb  == NULL)     return rce;
   --rce;  if (a_verb [0] == '\0')  return rce;
   --rce;  if (a_desc  == NULL)     return rce;
   --rce;  if (a_dittoing == 0)     return rce;
   --rce;  if (a_ditto == 0)        return rce;
   --rce;  if (a_major == 0)        return rce;
   --rce;  if (a_share == 0)        return rce;
   /*---(quick-out)----------------------*/
   --rce;  if (strchr (YUNIT_IS_BOTTS, a_type) == NULL)  return rce;
   /*---(fixes for build)----------------*/
   if (a_usage == YUNIT_BUILD && a_dittoing != '-') {
      if (a_type == YUNIT_IS_EXEC)  a_type = YUNIT_IS_DEXE;
      if (a_type == YUNIT_IS_VOID)  a_type = YUNIT_IS_DVOI;
   }
   /*---(statistics)---------------------*/
   switch (a_type) {
   case YUNIT_IS_EXEC : /* exec     */  ++(COND.c_real);   ++(SCRP.c_real);   ++(UNIT.c_real);   ++(FULL.c_real);     break;
   case YUNIT_IS_VARS : /* vars     */  ++(COND.c_vars);   ++(SCRP.c_vars);   ++(UNIT.c_vars);   ++(FULL.c_vars);     break;
   case YUNIT_IS_VOID : /* void     */  ++(COND.c_void);   ++(SCRP.c_void);   ++(UNIT.c_void);   ++(FULL.c_void);     break;
   case YUNIT_IS_DEXE : /* ditto ex */  ++(COND.c_dreal);  ++(SCRP.c_dreal);  ++(UNIT.c_dreal);  ++(FULL.c_dreal);    break;
   case YUNIT_IS_DVOI : /* ditto vo */  ++(COND.c_dvoid);  ++(SCRP.c_dvoid);  ++(UNIT.c_dvoid);  ++(FULL.c_dvoid);    break;
   }
   /*---(add to overall)-----------------*/
   ++(COND.c_step);  ++(SCRP.c_step);  ++(UNIT.c_step);  ++(FULL.c_step);
   /*---(skips)----------------*/
   if (strchr (a_desc, 'å') != NULL)  { ++(COND.c_skips);  ++(SCRP.c_skips);  ++(UNIT.c_skips);  ++(FULL.c_skips);  x_skip = 'y';  }
   /*---(setting dittos)-------*/
   rc = yunit_ditto_step  (a_usage, a_type, s_dittoing, x_skip);
   /*> if (a_usage == YUNIT_CONVERT && s_dittoing != '-') {                                                                                             <* 
    *>    n = a_ditto - '0';                                                                                                                            <* 
    *>    switch (a_type) {                                                                                                                             <* 
    *>    case YUNIT_IS_EXEC : /+ exec     +/  ++(s_dittos [n].c_real);  ++(s_dittos [n].c_step);  if (x_skip == 'y')  ++s_dittos [n].c_skip;  break;   <* 
    *>    case YUNIT_IS_VOID : /+ void     +/  ++(s_dittos [n].c_void);  ++(s_dittos [n].c_step);  if (x_skip == 'y')  ++s_dittos [n].c_skip;  break;   <* 
    *>    }                                                                                                                                             <* 
    *> }                                                                                                                                                <*/
   /*---(save-back)----------------------*/
   if (r_cunit != NULL)  *r_cunit = FULL.c_unit;
   if (r_cscrp != NULL)  *r_cscrp = UNIT.c_scrp;
   if (r_ccond != NULL)  *r_ccond = SCRP.c_midd;
   if (r_cstep != NULL)  *r_cstep = COND.c_step;
   /*---(done)---------------------------*/
   return 1;
}

char*
yunit_stats_show        (char a_prefix [LEN_FULL], char n)
{
   char x_part    [LEN_FULL]  = "";
   char x_ulreuse [LEN_HUND]  = "·";
   char x_ugreuse [LEN_HUND]  = "·";
   if (strcmp (g_counts [n].c_lreuse, "") == 0) strcpy (x_ulreuse, "·"); else strlcpy (x_ulreuse, g_counts [n].c_lreuse, LEN_HUND);
   if (strcmp (g_counts [n].c_greuse, "") == 0) strcpy (x_ugreuse, "·"); else strlcpy (x_ugreuse, g_counts [n].c_greuse, LEN_HUND);
   strcpy (s_print, "");
   sprintf (x_part , "%s  %4d  %4d  %4d  %4d  ",
         a_prefix, g_counts [n].c_topp , g_counts [n].c_glob , g_counts [n].c_shar , g_counts [n].c_scrp);
   strlcat (s_print, x_part, LEN_RECD);
   sprintf (x_part , "%4d  %4d  %4d  %-10.10s  ",
         g_counts [n].c_midd , g_counts [n].c_cond , g_counts [n].c_ditt , g_counts [n].c_dittos);
   strlcat (s_print, x_part, LEN_RECD);
   sprintf (x_part , "%4d  %-20.20s  %4d  %-20.20s  %4d  ",
         g_counts [n].c_lreu , x_ulreuse, g_counts [n].c_greu , x_ugreuse, g_counts [n].c_skipc);
   strlcat (s_print, x_part, LEN_RECD);
   sprintf (x_part , "%4d  %4d  %4d  %4d  %4d  ",
         g_counts [n].c_step , g_counts [n].c_real , g_counts [n].c_vars , g_counts [n].c_void  , g_counts [n].c_skips);
   strlcat (s_print, x_part, LEN_RECD);
   sprintf (x_part , "%4d  %4d  %4d  %4d   ",
         g_counts [n].c_dstep, g_counts [n].c_dreal, g_counts [n].c_dvoid, g_counts [n].c_dskip);
   strlcat (s_print, x_part, LEN_RECD);
   return s_print;
}

char*   yunit_full_show (char a_prefix [LEN_FULL]) { return yunit_stats_show (a_prefix, FULL_ID); }
char*   yunit_unit_show (char a_prefix [LEN_FULL]) { return yunit_stats_show (a_prefix, UNIT_ID); }
char*   yunit_scrp_show (char a_prefix [LEN_FULL]) { return yunit_stats_show (a_prefix, SCRP_ID); }
char*   yunit_cond_show (char a_prefix [LEN_FULL]) { return yunit_stats_show (a_prefix, COND_ID); }


char
yUNIT_force_prog        (int a_scrp, int a_cond, int a_step)
{
   FULL.c_scrp = UNIT.c_scrp = a_scrp;
   FULL.c_midd = UNIT.c_midd = SCRP.c_midd = a_cond;
   FULL.c_step = UNIT.c_step = SCRP.c_step = COND.c_step = a_step;
   return 0;
}

char
yunit_stats_of_scrp     (int *r_conds, int *r_steps)
{
   if (r_conds != NULL)   *r_conds = SCRP.c_midd;
   if (r_steps != NULL)   *r_steps = SCRP.c_step;
   return 0;
}

