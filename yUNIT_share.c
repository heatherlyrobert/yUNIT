#include "yUNIT.h"
#include "yUNIT_priv.h"



char
yunit_share__open       (char a_type, char a_label [LEN_TERSE], char a_share, char a_ftype, int a_line, char a_select, char a_desc [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_desc      [LEN_LONG]  = "";
   char        x_on        [LEN_LABEL] = "";
   char        x_off       [LEN_LABEL] = "";
   /*---(empty line)---------------------*/
   IF_STEP   yUNIT_printf  ("\n");
   /*---(save)---------------------------*/
   yUNIT_reuse_set   (a_share, a_ftype, a_line, a_desc);
   /*---(text)---------------------------*/
   yunit_final_prep  (a_type, a_share, 0, 0, "", a_desc, 85 - 22, YSTR_TEXT_CEN, 3, YSTR_DASH, NULL, NULL, x_desc);
   /*---(display)------------------------*/
   yunit_final_color (YUNIT_MONO, a_type, &x_on, NULL, &x_off, NULL, NULL);
   /*---(display)------------------------*/
   if (a_select == '-') sprintf (s_print, "  %s%-6.6s (%c) ==--%s---==%s", x_on, a_label, (uchar) a_share, x_desc, x_off);
   else                 sprintf (s_print, "  %s%-6.6s (%c/%c) ==-%s--==%s", x_on, a_label, (uchar) a_share, (uchar) a_select, x_desc, x_off);
   IF_STEP   yUNIT_printf  ("%s\n", s_print);
   /*---(complete)-----------------------*/
   return 0;
}

char yUNIT_shar              (char a_share, char a_ftype, int a_line, char a_select, char a_desc [LEN_LONG]) { return yunit_share__open (TYPE_SHARED, "SHARED", a_share, a_ftype, a_line, a_select, a_desc); }
char yUNIT_glob              (char a_share, char a_ftype, int a_line, char a_select, char a_desc [LEN_LONG]) { return yunit_share__open (TYPE_GLOBAL, "GLOBAL", a_share, a_ftype, a_line, a_select, a_desc); }
char yUNIT_conf              (char a_share, char a_ftype, int a_line, char a_select, char a_desc [LEN_LONG]) { return yunit_share__open (TYPE_CONFIG, "CONFIG", a_share, a_ftype, a_line, a_select, a_desc); }

char
yunit_share__close      (char a_type, char a_label [LEN_LABEL], char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_LONG]  = "";
   char        x_on        [LEN_LABEL] = "";
   char        x_off       [LEN_LABEL] = "";
   /*---(empty line)---------------------*/
   IF_STEP   yUNIT_printf  ("\n");
   /*---(display)------------------------*/
   yunit_final_color (YUNIT_MONO, a_type, &x_on, NULL, &x_off, NULL, NULL);
   if (a_select == '-')  sprintf (s_print, "  %s%-6.6s (%c)--[ cond=%-5d test=%-5d ]---------------------[ cond=%-5d test=%-5d ]%s", x_on, a_label, a_share, a_econd, a_estep, a_acond, a_astep, x_off);
   else                  sprintf (s_print, "  %s%-6.6s (%c)--[ cond=%-5d test=%-5d ]--------( %c >>>------[ cond=%-5d test=%-5d ]%s", x_on, a_label, a_share, a_econd, a_estep, a_select, a_acond, a_astep, x_off);
   IF_STEP   yUNIT_printf  ("%s\n", s_print);
   /*---(complete)-----------------------*/
   return 0;
}

char yUNIT_rahs              (char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep) { return yunit_share__close (TYPE_DERAHS, "DERAHS", a_share, a_select, a_econd, a_estep, a_acond, a_astep); }
char yUNIT_bolg              (char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep) { return yunit_share__close (TYPE_LABOLG, "LABOLG", a_share, a_select, a_econd, a_estep, a_acond, a_astep); }
char yUNIT_fnoc              (char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep) { return yunit_share__close (TYPE_GIFNOC, "GIFNOC", a_share, a_select, a_econd, a_estep, a_acond, a_astep); }


