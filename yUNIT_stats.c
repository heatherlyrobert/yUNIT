#include "yUNIT.h"
#include "yUNIT_priv.h"


/*---(script-level)-------------------*/
static int  s_utopp   = 0;
static int  s_uscrp   = 0;
static int  s_uglob   = 0;
static int  s_ushar   = 0;

/*---(condition-level)----------------*/
static int  s_umidd   = 0;
static int  s_ucond   = 0;
static int  s_uditt   = 0;
static int  s_ulreu   = 0;
static int  s_ugreu   = 0;
static char s_ulreuse [LEN_HUND]  = "";
static char s_ugreuse [LEN_HUND]  = "";

static int  s_nmidd   = 0;
static int  s_ncond   = 0;
static int  s_nditt   = 0;
static int  s_nlreu   = 0;
static int  s_ngreu   = 0;
static char s_nlreuse [LEN_HUND]  = "";
static char s_ngreuse [LEN_HUND]  = "";
static char s_ndittos [LEN_LABEL] = "··········";

static int  s_ccond   = 0;

/*---(step-level)---------------------*/
static int  s_ustep   = 0;
static int  s_ureal   = 0;
static int  s_uvars   = 0;
static int  s_uvoid   = 0;

static int  s_nstep   = 0;
static int  s_nreal   = 0;
static int  s_nvars   = 0;
static int  s_nvoid   = 0;

static int  s_cstep   = 0;

/*---(skip/select)--------------------*/
static int  s_uscond  = 0;
static int  s_usstep  = 0;

static int  s_nscond  = 0;
static int  s_nsstep  = 0;

/*---(done)---------------------------*/



char
yunit_stats_clear       (char a_type)
{
   /*---(clear)--------------------------*/
   switch (a_type) {
   case '*' :
      s_utopp = s_uscrp = s_uglob = s_ushar = 0;
      s_umidd = s_ucond = s_uditt = s_ulreu = s_ugreu = 0;
      s_ustep = s_ureal = s_uvars = s_uvoid = 0;
      strcpy (s_ulreuse, "");
      strcpy (s_ugreuse, "");
      s_uscond = s_usstep = 0;
      break;
   case 'S' :
      s_nmidd = s_ncond = s_nditt = s_nlreu = s_ngreu = 0;
      s_nstep = s_nreal = s_nvars = s_nvoid = 0;
      s_ccond = s_cstep = 0;
      strcpy (s_nlreuse, "");
      strcpy (s_ngreuse, "");
      strcpy (s_ndittos , "··········");
      s_nscond = s_nsstep = 0;
      break;
   case 'c' :
      s_cstep = 0;
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yUNIT_stats_purge       (int *r_cscrp, int *r_ccond, int *r_cstep)
{
   /*---(call all clears)----------------*/
   yunit_stats_clear ('*');
   yunit_stats_clear ('S');
   yunit_stats_clear ('c');
   /*---(save-back)----------------------*/
   if (r_cscrp != NULL)  *r_cscrp = s_uscrp;
   if (r_ccond != NULL)  *r_ccond = s_ccond;
   if (r_cstep != NULL)  *r_cstep = s_cstep;
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
   char       *x_title     = "=================================================================  ID   TOP===all====glob====shar====scrp   MID===all====cond====ditto=and=usage==========local=reuse=====================global=reuse=================skip   BOT===all====real====vars====void====skip    ================= ";
   /*---(saves)--------------------------*/
   static char x_save      [LEN_LABEL] = "";
   static char x_stype     =  '-';
   static char x_smajor    =  '-';
   /*---(defense)------------------------*/
   --rce;  if (a_conv  == NULL)  return rce;
   --rce;  if (a_nscrp == NULL)  return rce;
   /*---(unit testing)-------------------*/
   if (a_type == '!') { fprintf (a_conv, "%-6.6s %c (%3d/%c)\n", x_save, x_stype, (uchar) x_smajor, (x_smajor > 32) ? x_smajor : '·'); return 2; }
   /*---(defense)------------------------*/
   if (a_type == 0 || strchr ("UPS-", a_type) == NULL)   return 0;
   /*> --rce;  if (a_conv == NULL)                                 { fprintf (a_conv, "# BOOM===  %s \n", x_title); return rce; }   <*/
   /*> --rce;  if (a_verb == NULL)                                 { fprintf (a_conv, "# BOOM===  %s \n", x_title); return rce; }   <*/
   /*---(limits)-------------------------*/
   if (a_type == '-')                                          a_major = '-';
   if (a_type == 'P' && (a_major < 0 || a_major > 100))        a_major = '?';
   /*> if (a_type == 'S' && strchr (YSTR_UPPER, a_major) == NULL)  a_major = '?';     <*/
   /*---(current type)-------------------*/
   --rce;
   if        (strcmp (a_verb, "SCRP"  ) == 0)   x_type = 'P';
   else if   (strcmp (a_verb, "GLOBAL") == 0)   x_type = 'G';
   else if   (strcmp (a_verb, "CONFIG") == 0)   x_type = 'C';
   else if   (strcmp (a_verb, "SHARED") == 0)   x_type = 'S';
   else if   (strcmp (a_verb, "SECT"  ) == 0)   x_type = '-';
   else if   (strcmp (a_verb, "UNIT"  ) == 0) { x_type = 'U'; x_stype = 'U'; }
   else { fprintf (a_conv, "# BOOM===  %s \n", x_title); return rce; }
   /*---(master exception)---------------*/
   if (x_type == 'U' && strcmp (a_nscrp, "master.unit") == 0)  { x_type = 'M'; x_stype = 'M';  }
   /*---(data preparation)---------------*/
   switch (x_stype) {
   case 'M'  :  strcpy (x_verb, "RETSAM      ");  strcpy (x_header, "#===========");  strcpy (x_label, "final master file statistics ------------------------------------");  strcpy  (x_ref, " -");                     sprintf (x_stat, "    %4d  %4d  %4d  %4d", s_utopp, s_uglob, s_ushar, s_uscrp);   break;
   case 'U'  :  strcpy (x_verb, "TNIU        ");  strcpy (x_header, "#===========");  strcpy (x_label, "final unit test statistics --------------------------------------");  strcpy  (x_ref, " -");                     sprintf (x_stat, "    %4d  %4d  %4d  %4d", s_utopp, s_uglob, s_ushar, s_uscrp);   break;
   case 'P'  :  strcpy (x_verb, "   PRCS     ");  strcpy (x_header, "   #========");  strcpy (x_label, "script statistics -----------------------------------------------");  sprintf (x_ref, "%2d", (uchar) x_smajor);  sprintf (x_stat, "       1     ·     ·     1");                                   break;
   case 'G'  :  strcpy (x_verb, "   LABOLG   ");  strcpy (x_header, "   #========");  strcpy (x_label, "global shared code statistics -----------------------------------");  sprintf (x_ref, " %c", (uchar) x_smajor);  sprintf (x_stat, "       1     1     ·     ·");                                   break;
   case 'C'  :  strcpy (x_verb, "   GIFNOC   ");  strcpy (x_header, "   #========");  strcpy (x_label, "global shared code statistics -----------------------------------");  sprintf (x_ref, " %c", (uchar) x_smajor);  sprintf (x_stat, "       1     1     ·     ·");                                   break;
   case 'S'  :  strcpy (x_verb, "   DERAHS   ");  strcpy (x_header, "   #========");  strcpy (x_label, "local shared code statistics ------------------------------------");  sprintf (x_ref, " %c", x_smajor);          sprintf (x_stat, "       1     ·     1     ·");                                   break;
   }
   /*---(header)-------------------------*/
   if (x_stype != '-')  {
      /*---(header)----------------------*/
      fprintf (a_conv, "\n%-12.12s  %s \n", x_header, x_title);
      /*---(prefix)----------------------*/
      /*> sprintf (x_prefix, "%-12.12s  %-65.65s  %-2.2s  %-29.29s", x_verb, x_label, x_ref, x_stat);   <*/
      sprintf (x_prefix, "%-12.12s  %-65.65s  %-2.2s", x_verb, x_label, x_ref);
      /*---(suffix)----------------------*/
      if (strchr ("UM", x_type) != NULL)  {
         fprintf (a_conv, "%s\n", yunit_stats_all    (x_prefix));
         /*> if (strcmp (s_ulreuse, "") == 0) strcpy (s_ulreuse, "·");                                                                                                    <* 
          *> if (strcmp (s_ugreuse, "") == 0) strcpy (s_ugreuse, "·");                                                                                                    <* 
          *> fprintf (a_conv, "%s      %4d  %4d  %4d  %-10.10s  %4d  %-20.20s  %4d  %-20.20s  %4d      %4d  %4d  %4d  %4d  %4d  -----------------  \n",   <* 
          *>       x_prefix,                                                                                                                                              <* 
          *>       s_umidd, s_ucond, s_uditt, "----------", s_ulreu, s_ulreuse, s_ugreu, s_ugreuse, s_uscond,                                                             <* 
          *>       s_ustep, s_ureal, s_uvars, s_uvoid, s_usstep);                                                                                                         <*/
      }
      else {
         fprintf (a_conv, "%s\n", yunit_stats__curr  (x_prefix, x_stat));
         /*> if (strcmp (s_nlreuse, "") == 0)  strcpy (s_nlreuse, "·");                                                                                                   <* 
          *> if (strcmp (s_ngreuse, "") == 0)  strcpy (s_ngreuse, "·");                                                                                                   <* 
          *> fprintf (a_conv, "%s      %4d  %4d  %4d  %-10.10s  %4d  %-20.20s  %4d  %-20.20s  %4d      %4d  %4d  %4d  %4d  %4d  -----------------  \n",   <* 
          *>       x_prefix,                                                                                                                                              <* 
          *>       s_nmidd, s_ncond, s_nditt, s_ndittos, s_nlreu, s_nlreuse, s_ngreu, s_ngreuse, s_nscond,                                                                <* 
          *>       s_nstep, s_nreal, s_nvars, s_nvoid, s_nsstep);                                                                                                         <*/
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
yUNIT_stats_accum       (void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_LABEL], char a_desc [LEN_LONG], char a_ditto, char a_major, int *r_cscrp, int *r_ccond, int *r_cstep)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_SHORT] = "";
   /*---(defense)------------------------*/
   --rce;  if (a_nscrp    == NULL)  return --rce;
   --rce;  if (a_type     == 0   )  return --rce;
   --rce;  if (a_verb     == NULL)  return --rce;
   --rce;  if (a_verb [0] == '\0')  return --rce;
   --rce;  if (a_desc     == NULL)  return --rce;
   /*---(start with summaries)-----------*/
   if (a_type == 'P')  a_major = s_uscrp + 1;
   yunit_stats_summary (a_conv, a_nscrp, a_type, a_verb, a_major);
   /*---(script-level)-------------------*/
   switch (a_type) {
   case 'P' : /* script   */  ++(s_uscrp);  ++(s_utopp);  break;
   case 'G' : /* g.share  */  ++(s_uglob);  ++(s_utopp);  break;
   case 'S' : /* l.share  */  ++(s_ushar);  ++(s_utopp);  break;
   }
   if (strchr ("PGS" , a_type) != NULL) {
      yunit_stats_clear ('S');
   }
   /*---(condition-level)----------------*/
   if (a_type == 'r' && strchr (YSTR_LOWER, a_major) == NULL)  a_type = 'g';
   switch (a_type) {
   case 'c' : /* cond     */  ++(s_ncond);  ++(s_nmidd);  ++(s_ucond);  ++(s_umidd);  ++(s_ccond);    break;
   case 'd' : /* ditto    */  ++(s_nditt);  ++(s_nmidd);  ++(s_uditt);  ++(s_umidd);  ++(s_ccond);    break;
   case 'r' : /* l.reuse  */  ++(s_nlreu);  ++(s_nmidd);  ++(s_ulreu);  ++(s_umidd);  ++(s_ccond);    break;
   case 'g' : /* g.reuse  */  ++(s_ngreu);  ++(s_nmidd);  ++(s_ugreu);  ++(s_umidd);  ++(s_ccond);    break;
   }
   /*---(clearing)-------------*/
   if (strchr ("cdrg", a_type) != NULL) {
      if (strchr (a_desc, 'å') != NULL)  { ++(s_nscond);  ++(s_uscond); }
      yunit_stats_clear ('c');
   }
   /*---(reuses)---------------*/
   sprintf (t, "%c", a_major);
   if (a_type == 'r')  {
      if (strchr (s_ulreuse, a_major) == NULL)  strlcat (s_ulreuse, t, LEN_LABEL);
      if (strchr (s_nlreuse, a_major) == NULL)  strlcat (s_nlreuse, t, LEN_LABEL);
               }
   if (a_type == 'g')  {
      if (strchr (s_ugreuse, a_major) == NULL)  strlcat (s_ugreuse, t, LEN_LABEL);
      if (strchr (s_ngreuse, a_major) == NULL)  strlcat (s_ngreuse, t, LEN_LABEL);
   }
   /*---(dittos)---------------*/
   if (a_type == 'c' && (a_ditto >= '0' && a_ditto <= '9'))  s_ndittos [a_ditto - '0'] = '´';
   if (a_type == 'd' && (a_ditto >= '0' && a_ditto <= '9')) {
      if      (strchr ("´·", s_ndittos [a_ditto - '0']) != NULL)   s_ndittos [a_ditto - '0'] = '1';
      else if (strchr ("9*", s_ndittos [a_ditto - '0']) != NULL)   s_ndittos [a_ditto - '0'] = '*';
      else                                                         s_ndittos [a_ditto - '0'] = s_ndittos [a_ditto - '0'] + 1;
   }
   /*---(step-level)---------------------*/
   switch (a_type) {
   case 'x' : /* exec     */  ++(s_nreal);  ++(s_nstep);  ++(s_ureal);  ++(s_ustep);  ++(s_cstep);    break;
   case 'a' : /* vars     */  ++(s_nvars);  ++(s_nstep);  ++(s_uvars);  ++(s_ustep);  ++(s_cstep);    break;
   case 'v' : /* void's   */  ++(s_nvoid);  ++(s_nstep);  ++(s_uvoid);  ++(s_ustep);  ++(s_cstep);    break;
   }
   if (strchr ("xav" , a_type) != NULL) {
      if (strchr (a_desc, 'å') != NULL)  { ++(s_nsstep);  ++(s_usstep); }
   }
   /*---(save-back)----------------------*/
   if (r_cscrp != NULL)  *r_cscrp = s_uscrp;
   if (r_ccond != NULL)  *r_ccond = s_ccond;
   if (r_cstep != NULL)  *r_cstep = s_cstep;
   /*---(complete)-----------------------*/
   return 0;
}

char*
yunit_stats_all         (char a_prefix [LEN_FULL])
{
   char x_ulreuse [LEN_HUND]  = "";
   char x_ugreuse [LEN_HUND]  = "";
   if (strcmp (s_ulreuse, "") == 0) strcpy (x_ulreuse, "·"); else strcpy (x_ulreuse, s_ulreuse);
   if (strcmp (s_ugreuse, "") == 0) strcpy (x_ugreuse, "·"); else strcpy (x_ugreuse, s_ugreuse);
   sprintf (s_print, "%s      %4d  %4d  %4d  %4d      %4d  %4d  %4d  %-10.10s  %4d  %-20.20s  %4d  %-20.20s  %4d      %4d  %4d  %4d  %4d  %4d  -----------------  ",
         a_prefix,
         s_utopp, s_uglob, s_ushar, s_uscrp,
         s_umidd, s_ucond, s_uditt, "----------", s_ulreu, x_ulreuse, s_ugreu, x_ugreuse, s_uscond,
         s_ustep, s_ureal, s_uvars, s_uvoid, s_usstep);
   return s_print;
}

char*
yunit_stats__curr       (char a_prefix [LEN_FULL], char a_summ [LEN_DESC])
{
   char x_nlreuse [LEN_HUND]  = "";
   char x_ngreuse [LEN_HUND]  = "";
   if (strcmp (s_nlreuse, "") == 0) strcpy (x_nlreuse, "·"); else strcpy (x_nlreuse, s_nlreuse);
   if (strcmp (s_ngreuse, "") == 0) strcpy (x_ngreuse, "·"); else strcpy (x_ngreuse, s_ngreuse);
   sprintf (s_print, "%s  %s      %4d  %4d  %4d  %-10.10s  %4d  %-20.20s  %4d  %-20.20s  %4d      %4d  %4d  %4d  %4d  %4d  -----------------  ",
         a_prefix, a_summ,
         s_nmidd, s_ncond, s_nditt, s_ndittos, s_nlreu, x_nlreuse, s_ngreu, x_ngreuse, s_nscond,
         s_nstep, s_nreal, s_nvars, s_nvoid, s_nsstep);
   return s_print;
}

char* yunit_stats_curr        (char a_prefix [LEN_FULL])  { return yunit_stats__curr (a_prefix, "       -     -     -     -"); }



