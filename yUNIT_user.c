#include "yUNIT.h"
#include "yUNIT_priv.h"



char
yUNIT_user_del          (cchar *a_name)
{
   char        rce          =  -10;
   char        rc           =    0;
   char        t            [LEN_RECD ] = "";
   --rce;  if (a_name == NULL) return rce;
   snprintf (t, LEN_RECD, "userdel --remove %s >> /dev/null 2>&1", a_name);
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   return 0; 
}

char
yUNIT_user_add          (cchar *a_name, cchar *a_pass, cchar *a_shell)
{
   char        rce          =  -10;
   char        rc           =    0;
   char        t            [LEN_RECD  ] = "";
   char        s            [LEN_RECD  ] = "";
   --rce;  if (a_name == NULL) return rce;
   /*> --rce;  if (a_pass == NULL) return rce;                                        <*/
   yUNIT_user_del (a_name);
   snprintf (t, LEN_RECD, "useradd --gid nobody --create-home --no-user-group %s", a_name);
   if (a_shell != NULL && strlen (a_shell) > 0) {
      snprintf (s, LEN_RECD, "  --shell \"%s\"", a_shell);
      strcat   (t, s);
   }
   strcat   (t, "  >> /dev/null 2>&1");
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   if (a_pass != NULL) {
      snprintf (t, LEN_RECD, "printf \"%s\n%s\n\" | passwd %s >> /dev/null 2>&1", a_pass, a_pass, a_name);
      rc = system (t);
      --rce;  if (rc < 0)   return rce;
   }
   return 0; 
}


