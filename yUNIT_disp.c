#include "yUNIT.h"
#include "yUNIT_priv.h"



char
yunit_disp_show         (int a_line, int a_seqn, char a_note [LEN_TERSE], char a_desc [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_line      [LEN_TERSE] = "";
   char        x_seqn      [LEN_TERSE] = "";
   char        x_desc      [LEN_HUND]  = "";
   /*---(quick-out)----------------------*/
   if (myUNIT.level <= YUNIT_COND)  return 0;
   /*---(format description)-------------*/
   yunit_final_prep  (TYPE_STEP, '-', a_line, a_seqn, a_desc, 85 - 15 - 7, YSTR_TEXT_LEF, 1, YUNIT_SDOTS, x_line, x_seqn, x_desc);
   /*---(create line)--------------------*/
   snprintf (s_print, LEN_RECD, "  %s) %-6.6s : %63.63s%07s", x_seqn, a_note, x_desc, x_line);
   /*---(output)-------------------------*/
   IF_STEP  yunit_printf  ("\n%s\n", s_print);
   /*---(score)--------------------------*/
   yunit_actual_accum (TYPE_DISP, 0, 0);
   /*---(complete)-----------------------*/
   return 1;
}

char
yunit_disp__top         (char a_type, int a_line, int a_seqn, char a_desc [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_line      [LEN_TERSE] = "";
   char        x_seqn      [LEN_TERSE] = "";
   char        x_desc      [LEN_HUND]  = "";
   /*---(locals)-----------+-----+-----+-*/
   char        x_on        [LEN_TERSE] = "";
   char        x_on2       [LEN_TERSE] = "";
   char        x_off       [LEN_TERSE] = "";
   char        x_note      [LEN_TERSE] = "";
   /*---(format description)-------------*/
   yunit_final_prep  (a_type, '-', a_line, a_seqn, a_desc, 85 - 15 - 7, YSTR_TEXT_LEF, 1, YUNIT_SDOTS, x_line, x_seqn, x_desc);
   /*---(colors)-------------------------*/
   yunit_final_color (YUNIT_MONO, a_type, x_on, x_on2, x_off, x_note, NULL);
   /*---(create line)--------------------*/
   snprintf (s_print, LEN_RECD, "  %s%s) %s%-6.6s%s : %63.63s%07s", x_on, x_seqn, x_on2, x_note, x_off, x_desc, x_line);
   /*---(output)-------------------------*/
   IF_STEP  yunit_printf  ("\n%s\n", s_print);
   /*---(complete)-----------------------*/
   return 1;
}

char
yunit_disp__mid         (char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   int         l           =    0;
   int         x_rc        =   -1;
   char        x_ch        =  '´';
   /*---(quick-out)----------------------*/
   IF_NOTFULL  return 0;
   /*---(calling)------------------------*/
   l  = strlen (a_meth);
   l += strlen (a_args);
   if (l <= 85 - 18) yunit_printf ("      method : %-s (%.50s)\n" , a_meth, a_args);
   else              yunit_printf ("      method : %-s (%.48s>>\n", a_meth, a_args);
   /*---(get result)---------------------*/
   yunit_actual_last (TYPE_STEP, NULL, &x_rc);
   /*---(testing)------------------------*/
   if      (x_rc >=  32 && x_rc <=  126)  x_ch = x_rc;
   else if (x_rc == '¢')                  x_ch = '?';
   else if (x_rc <= -32 && x_rc >= -126)  x_ch = -x_rc;
   else                                   x_ch = '-';
   yunit_printf ("      test   : %-10s (rc = %4d, test abbr = %c)%s\n", a_test, x_rc, x_ch, (x_rc == '¢') ? " BAD TEST" : "");
   /*---(complete)-----------------------*/
   return 1;
}

char
yunit_disp__bot         (char a_source, char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_modd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   int         l           =    0;
   int         i           =    0;
   int         x_bad       =    0;
   int         x_mis       =    0;
   int         x_tot       =    0;
   char        x_modd      [LEN_RECD]  = "";
   char        x_resu      = YUNIT_SUCC;
   char        x_show      =  '-';
   /*---(quick-out)----------------------*/
   if (myUNIT.level <= YUNIT_STEP)  return 0;
   /*---(get result)---------------------*/
   yunit_actual_last (TYPE_STEP, &x_resu, NULL);
   /*---(handle void)--------------------*/
   if (a_source == 'v') {
      yunit_printf ("      expect : VOID\n");
      yunit_printf ("      actual : VOID\n");
      return 2;
   }
   /*---(handle numbers)-----------------*/
   if (a_source == 'i' || a_source == 'r') {
      yunit_printf ("      expect : %s\n", a_expe);
      yunit_printf ("      actual : %s\n", a_actu);
   }
   /*---(handle rest)--------------------*/
   else {
      yunit_printf ("      expect : %3d%c%s%c\n", strlen (a_expe), YUNIT_BEG, a_expe, YUNIT_END);
      yunit_printf ("      actual : %3d%c%s%c\n", strlen (a_actu), YUNIT_BEG, a_actu, YUNIT_END);
   }
   /*---(set mode)-----------------------*/
   if      (strcmp  (a_test + 1, "_equal" ) == 0)  x_show = 'y';
   else if (strncmp (a_test, "u_round", 7) == 0)   x_show = 'y';
   else                                            x_show = '-';
   /*---(overrides)----------------------*/
   if (a_test [0] != a_source)  x_show = '-';
   if (x_resu != YUNIT_FAIL)    x_show = '-';
   /*---(handle modd)--------------------*/
   if (x_show == 'y' && myUNIT.level == YUNIT_MAXX) {
      /*---(get modd string)-------------*/
      if (a_modd != NULL)  strncpy (x_modd, a_modd, LEN_RECD);
      if      (strcmp  (a_test, "s_equal"   ) == 0) ;
      else if (strncmp (a_test, "u_round", 7) == 0) ;
      else   yVAR_yunit (a_actu, a_expe, x_modd);
      /*---(total)-----------------------*/
      l = strlen (x_modd);
      for (i = 0; i < l; ++i) {
         if (x_modd [i] != ' ') {
            if (strchr ("<>", x_modd [i]) != NULL)  ++x_mis;
            else                                    ++x_bad;
            if (YUNIT_PURE == '-' && x_modd [i] == 'x')   x_modd [i] = '°';
         } else if (YUNIT_PURE == '-')                    x_modd [i] = '·';
      }
      /*---(adjust)----------------------*/
      x_tot = x_mis + x_bad;
      if      (x_mis >  9)  x_mis  = '*';
      else if (x_mis >  0)  x_mis += '0';
      else                  x_mis  = '-';
      if      (x_bad >  9)  x_bad  = '*';
      else if (x_bad >  0)  x_bad += '0';
      else                  x_bad  = '-';
      /*---(show modd line)--------------*/
      if (x_tot > 0) {
         if      (a_test [0] == 'r') yunit_printf ("      ISSUE  : %s%s\n"    , YUNIT_ELIPSIS, x_modd + 3);
         else if (a_test [0] == 'i') yunit_printf ("      ISSUE  : %s%s\n"    , YUNIT_ELIPSIS, x_modd + 3);
         else                        yunit_printf ("      ISSUE (%c/%c) %c%s%c\n", x_bad, x_mis, YUNIT_BEG, x_modd, YUNIT_END);
      }
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   return 1;
}

char
yunit_disp_full         (char a_source, int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_expe [LEN_RECD], char a_test [LEN_TERSE], char a_actu [LEN_RECD], char a_modd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_desc      [LEN_LONG]  = "???";
   char        x_meth      [LEN_HUND]  = "???";
   char        x_args      [LEN_FULL]  = "???";
   char        x_expe      [LEN_RECD]  = "???";
   char        x_test      [LEN_TERSE] = "???";
   char        x_actu      [LEN_RECD]  = "???";
   char        x_modd      [LEN_RECD]  = "???";
   /*---(quick-out)----------------------*/
   if (myUNIT.level <= YUNIT_COND)   return 0;
   /*---(defense)------------------------*/
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_LONG);
   if (a_meth != NULL)  strncpy (x_meth, a_meth, LEN_HUND);
   if (a_args != NULL)  strncpy (x_args, a_args, LEN_FULL);
   if (a_expe != NULL)  strncpy (x_expe, a_expe, LEN_RECD);
   if (a_test != NULL)  strncpy (x_test, a_test, LEN_TERSE);
   if (a_actu != NULL)  strncpy (x_actu, a_actu, LEN_RECD);
   if (a_modd != NULL)  strncpy (x_modd, a_modd, LEN_RECD);
   /*---(create output)------------------*/
   yunit_disp__top (TYPE_STEP, a_line, a_seqn, x_desc);
   yunit_disp__mid (x_meth, x_args, x_test);
   yunit_disp__bot (a_source, x_test, x_expe, x_actu, x_modd);
   /*---(complete)-----------------------*/
   return 1;
}

char
yunit_disp_single       (char a_type, int a_line, int a_seqn, char a_desc [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_desc      [LEN_LONG]  = "???";
   /*---(quick-out)----------------------*/
   if (myUNIT.level <= YUNIT_COND)   return 0;
   /*---(defense)------------------------*/
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_LONG);
   /*---(create output)------------------*/
   yunit_disp__top (a_type, a_line, a_seqn, x_desc);
   /*---(complete)-----------------------*/
   return 1;
}

char
yunit_disp_double       (char a_type, int a_line, int a_seqn, char a_desc [LEN_LONG], char a_label [LEN_TERSE], char a_detail [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_desc      [LEN_LONG]  = "???";
   char        x_label     [LEN_TERSE] = "???";
   char        x_detail    [LEN_RECD]  = "???";
   int         l           =    0;
   char        x_second    [LEN_HUND]  = "???";
   /*---(quick-out)----------------------*/
   if (myUNIT.level <= YUNIT_COND)   return 0;
   /*---(defense)------------------------*/
   if (a_desc   != NULL)  strncpy (x_desc  , a_desc  , LEN_LONG);
   if (a_label  != NULL)  strncpy (x_label , a_label , LEN_TERSE);
   if (a_detail != NULL)  strncpy (x_detail, a_detail, LEN_RECD);
   /*---(create output)------------------*/
   yunit_disp__top (a_type, a_line, a_seqn, x_desc);
   /*---(second line)--------------------*/
   l = strlen (x_detail);
   if (l > 64)  { x_detail [66] = '\0'; x_detail [65] = '>'; x_detail [64] = '>'; }
   else         { x_detail [l]  = YUNIT_END; x_detail [l + 1] = '\0';             }
   sprintf (x_second , "      %-6.6s : %3d%c%s", x_label, l, YUNIT_BEG, x_detail);
   IF_FULL  yunit_printf  ("%s\n", x_second);
   /*---(complete)-----------------------*/
   return 1;
}



