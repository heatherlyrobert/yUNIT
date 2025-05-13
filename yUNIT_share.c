#include "yUNIT.h"
#include "yUNIT_priv.h"

static   char    s_share   = ' ';
static   char    zUNIT_desc    [LEN_HUND]  = "";


char    /*  PURPOSE :: display a shared condition message                     */
yUNIT_shar              (char a_share, char a_select, char *a_desc)
{
   char        x_desc      [LEN_HUND] = "???";
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   IF_STEP   yunit_printf  ("\n");
   yunit_header (TYPE_SHARED, 0, (uchar) a_share, NULL, x_desc, a_share, a_select);
   IF_STEP   yunit_printf  ("%s\n", s_print);
   s_share = a_share;
   strcpy (zUNIT_desc, x_desc);
   return 0;
}

char    /*  PURPOSE :: display a shared condition message                     */
yUNIT_rahs              (char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep)
{
   IF_STEP   yunit_printf  ("\n");
   yunit_footer (TYPE_DERAHS, a_share, a_select, a_econd, a_estep, a_acond, a_astep);
   IF_STEP   yunit_printf  ("%s\n", s_print);
   return 0;
}

char    /*  PURPOSE :: display a shared condition message                     */
yUNIT_glob              (char a_share, char a_select, char *a_desc)
{
   char        x_desc      [LEN_HUND] = "???";
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   IF_STEP   yunit_printf  ("\n");
   yunit_header (TYPE_GLOBAL, 0, (uchar) a_share, NULL, x_desc, a_share, a_select);
   IF_STEP   yunit_printf  ("%s\n", s_print);
   s_share = a_share;
   strcpy (zUNIT_desc, x_desc);
   return 0;
}

char    /*  PURPOSE :: display a shared condition message                     */
yUNIT_bolg              (char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep)
{
   IF_STEP   yunit_printf  ("\n");
   yunit_footer (TYPE_LABOLG, a_share, a_select, a_econd, a_estep, a_acond, a_astep);
   IF_STEP   yunit_printf  ("%s\n", s_print);
   return 0;
}

char    /*  PURPOSE :: display a shared condition message                     */
yUNIT_conf              (char a_share, char a_select, char *a_desc)
{
   char        x_desc      [LEN_HUND] = "???";
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   IF_STEP   yunit_printf  ("\n");
   yunit_header (TYPE_CONFIG, 0, (uchar) a_share, NULL, x_desc, a_share, a_select);
   IF_STEP   yunit_printf  ("%s\n", s_print);
   s_share = a_share;
   strcpy (zUNIT_desc, x_desc);
   return 0;
}

char    /*  PURPOSE :: display a shared condition message                     */
yUNIT_fnoc              (char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep)
{
   IF_STEP   yunit_printf  ("\n");
   yunit_footer (TYPE_GIFNOC, a_share, a_select, a_econd, a_estep, a_acond, a_astep);
   IF_STEP   yunit_printf  ("%s\n", s_print);
   return 0;
}
