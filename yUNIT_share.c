#include "yUNIT.h"
#include "yUNIT_priv.h"

static   char    s_share   = ' ';
static   char    s_desc    [LEN_HUND]  = "";


char    /*  PURPOSE :: display a shared condition message                     */
yUNIT_share             (char a_share, cchar *a_desc)
{
   char        x_desc      [LEN_HUND] = "???";
   if (a_desc != NULL)  strncpy (x_desc, a_desc, LEN_HUND);
   IF_COND   yunit_printf  ("\n");
   yunit_header (TYPE_SHARE, 0, a_share, NULL, x_desc);
   IF_COND   yunit_printf  ("%s\n", s_print);
   s_share = a_share;
   strcpy (s_desc, x_desc);
   return 0;
}

char    /*  PURPOSE :: display a shared condition message                     */
yUNIT_erahs             (char a_share)
{
   IF_COND   yunit_printf  ("\n");
   yunit_header (TYPE_ERAHS, 0, s_share, NULL, s_desc);
   IF_COND   yunit_printf  ("%s\n", s_print);
   return 0;
}
