#include "yUNIT.h"
#include "yUNIT_priv.h"

int         s_all       = 0;
int         s_good      = 0;

char
check_char              (int s, char *a_desc, char a_act, char a_exp)
{
   char        x_res       =  '-';
   ++s_all;
   if (a_act == a_exp) {
      x_res = 'Y';
      ++s_good;
   }
   printf ("%02d) %-40.40s  %c                    %c                    %c\n", s, a_desc, a_act, a_exp, x_res);
   return 0;
}

char
check_value             (int s, char *a_desc, int a_act, int a_exp)
{
   char        x_res       =  '-';
   ++s_all;
   if (a_act == a_exp) {
      x_res = 'Y';
      ++s_good;
   }
   printf ("%02d) %-40.40s  %-3d                  %-3d                  %c\n", s, a_desc, a_act, a_exp, x_res);
   return 0;
}

char
check_string            (int s, char *a_desc, char *a_act, char *a_exp)
{
   char        x_res       =  '-';
   ++s_all;
   if (strcmp (a_act, a_exp) == 0) {
      x_res = 'Y';
      ++s_good;
   }
   printf ("%02d) %-40.40s  exp %2d[%s]\n", s, a_desc, strlen (a_exp), a_exp);
   printf ("      %c                                       act %2d[%s]\n", x_res, strlen (a_act), a_act);
   return 0;
}

char
summ                    (void)
{
   if (s_all == s_good)  printf ("   SUCCESS   SUCCESS   SUCCESS   SUCCESS   SUCCESS   SUCCESS   SUCCESS\n");
   else                  printf ("   FAILED    FAILED    FAILED    FAILED    FAILED    FAILED    FAILED\n");
   return 0;
}

char
yunit_globals_unit      (void)
{
   int         n           =    0;
   printf ("yUNIT_base.................\n");
   printf ("\nyUNIT_level\n");
   s_all = s_good = 0;
   check_value  (++n, "change the level to yUNIT_MUTE"     , yUNIT_level (YUNIT_MUTE), 0);
   check_value  (++n, "change the level to yUNIT_SUMM"     , yUNIT_level (YUNIT_SUMM), 1);
   check_value  (++n, "change the level to yUNIT_SCRP"     , yUNIT_level (YUNIT_SCRP), 2);
   check_value  (++n, "change the level to yUNIT_COND"     , yUNIT_level (YUNIT_COND), 3);
   check_value  (++n, "change the level to yUNIT_STEP"     , yUNIT_level (YUNIT_STEP), 4);
   check_value  (++n, "change the level to yUNIT_FULL"     , yUNIT_level (YUNIT_FULL), 5);
   check_value  (++n, "change the level too low"           , yUNIT_level (-1        ), 5);
   check_value  (++n, "change the level too high"          , yUNIT_level (15        ), 5);
   summ ();
   printf ("\nyUNIT_eterm\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_char   (++n, "change the eterm to unknown"        , yUNIT_eterm (0            ), '-');
   check_char   (++n, "change the eterm to unknown"        , yUNIT_eterm ('w'          ), '-');
   check_char   (++n, "change the eterm to unknown"        , yUNIT_eterm (' '          ), '-');
   summ ();
   return 0;
}

char
yunit_base_unit         (void)
{
   int         n           =    0;
   printf ("yUNIT_base.................\n");
   printf ("\nyUNIT_unit\n");
   s_all = s_good = 0;
   check_value  (++n, "create a unit"                      , yUNIT_unit  ("unit_test", YUNIT_MUTE, YUNIT_CONSOLE), 0);
   check_string (++n, "... global name"                    , myUNIT.name             , "unit_test"                  );
   check_value  (++n, "... global level"                   , myUNIT.level            , YUNIT_MUTE                   );
   check_char   (++n, "... global eterm"                   , myUNIT.eterm            , YUNIT_CONSOLE                );
   check_value  (++n, "create a unit"                      , yUNIT_unit  ("uniter"   , YUNIT_SUMM, YUNIT_ETERM  ), 0);
   check_string (++n, "... global name"                    , myUNIT.name             , "uniter"                     );
   check_value  (++n, "... global level"                   , myUNIT.level            , YUNIT_SUMM                   );
   check_char   (++n, "... global eterm"                   , myUNIT.eterm            , YUNIT_ETERM                  );
   check_value  (++n, "create a unit"                      , yUNIT_unit  ("unity"    , YUNIT_STEP, YUNIT_ETERM  ), 0);
   check_string (++n, "... global name"                    , myUNIT.name             , "unity"                      );
   check_value  (++n, "... global level"                   , myUNIT.level            , YUNIT_STEP                   );
   check_char   (++n, "... global eterm"                   , myUNIT.eterm            , YUNIT_ETERM                  );
   summ ();
   return 0;
}

char
yunit_scrp_unit         (void)
{
   int         n           =    0;
   printf ("yUNIT_scrp.................\n");
   printf ("\nyUNIT_scrp\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "change the level to yUNIT_FULL"     , yUNIT_level (YUNIT_FULL   ),  5 );
   yunit_open   ("/tmp/yuint_unit.txt");
   check_value  (++n, "call SCRP verb handler"             , yUNIT_scrp  (   954,   0, "function"          , "first script"              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SCRP [00] first script =======================================================[00954]");
   yunit_close  ();
   return 0;
   check_value  (++n, "call SCRP verb handler"             , yUNIT_scrp  (   306,  10, "function"          , "second"                    ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SCRP [10] second =============================================================[00306]");
   check_value  (++n, "call with out of range values"      , yUNIT_scrp  (    -1,  -1, "function"          , NULL                        ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SCRP [00] ??? ================================================================[00000]");
   check_value  (++n, "call with out of range values"      , yUNIT_scrp  (100000, 100, "function"          , NULL                        ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SCRP [99] ??? ================================================================[99999]");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call SCRP verb handler"             , yUNIT_scrp  (   954,   0, "function"          , "first script"              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SCRP [00] first script =======================================================[00954]");
   summ ();
   printf ("\nyUNIT_sect\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call SECT verb handler"             , yUNIT_sect  ("a section"                       ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SECT  ===-----------------------------[[ a section ]]-----------------------------===");
   check_value  (++n, "call SECT with SCRP"                , yUNIT_sect  ("SCRP"                            ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SECT  ===-----------------------------[[ a section ]]-----------------------------===");
   check_value  (++n, "call SECT verb handler"             , yUNIT_sect  (NULL                              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SECT  ===--------------------------------[[ ??? ]]--------------------------------===");
   check_value  (++n, "call SECT with SCRP"                , yUNIT_sect  ("SCRP"                            ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SECT  ===--------------------------------[[ ??? ]]--------------------------------===");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call SECT verb handler"             , yUNIT_sect  ("a section"                       ), 0);
   check_string (++n, "... global print"                   , s_print                 , "SECT  ===-----------------------------[[ a section ]]-----------------------------===");
   summ ();
   printf ("\nyUNIT_prcs\n");
   s_all = s_good = 0;
   SCRP_TEST = 11;
   SCRP_TEST = 511;
   SCRP_PASS = 495;
   SCRP_FAIL =  23;
   SCRP_BADD =   6;
   SCRP_VOID =   0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call PCRS verb handler"             , yUNIT_prcs  ()                                  , 0);
   check_string (++n, "... global print"                   , s_print                 , "  PRCS   step=511   [[ pass=495   fail=23    badd=6     void=0    ]]");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call PCRS verb handler"             , yUNIT_prcs  ()                                  , 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_RED "PRCS   step=511   [[ pass=495   fail=23    badd=6     void=0    ]]" BACK_OFF);
   SCRP_FAIL =   0;
   check_value  (++n, "call PCRS verb handler"             , yUNIT_prcs  ()                                  , 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_YEL "PRCS   step=511   [[ pass=495   fail=0     badd=6     void=0    ]]" BACK_OFF);
   SCRP_BADD =   0;
   check_value  (++n, "call PCRS verb handler"             , yUNIT_prcs  ()                                  , 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_GRN "PRCS   step=511   [[ pass=495   fail=0     badd=0     void=0    ]]" BACK_OFF);
   summ ();
   return 0;
}

char
yunit_cond_unit         (void)
{
   int         n           =    0;
   printf ("yUNIT_cond.................\n");
   printf ("\nyUNIT_cond\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call COND verb handler"             , yUNIT_cond  (   954,  321, "check the initial values"                         ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  COND [321] check the initial values -- -- -- -- -- -- -- -- -- -- -- -- -- -[00954]");
   check_value  (++n, "call COND verb handler"             , yUNIT_cond  (    -1,   -1, NULL                                               ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  COND [000] ??? -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -[00000]");
   check_value  (++n, "call COND verb handler"             , yUNIT_cond  (100000, 1000, "excellent stuffs"                                 ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  COND [999] excellent stuffs - -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -[99999]");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call COND verb handler"             , yUNIT_cond  (   954,  321, "check the initial values"                         ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  COND [321] check the initial values -- -- -- -- -- -- -- -- -- -- -- -- -- -[00954]");
   summ ();
   printf ("\nyUNIT_group\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call GROUP verb handler"            , yUNIT_group ("nice group"                      ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  GROUP ===---------------------------   nice group   ----------------------------===");
   check_value  (++n, "call GROUP verb handler"            , yUNIT_group (NULL                              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  GROUP ===-------------------------------   ???   -------------------------------===");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call GROUP verb handler"            , yUNIT_group ("nice group"                      ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  GROUP ===---------------------------   nice group   ----------------------------===");
   summ ();
   printf ("\nyUNIT_dnoc\n");
   s_all = s_good = 0;
   COND_TEST = 11;
   COND_PASS =  5;
   COND_FAIL =  3;
   COND_BADD =  2;
   COND_VOID =  1;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   check_string (++n, "... global print"                   , s_print                 , "    DNOC   step=11    [[ pass=5     fail=3     badd=2     void=1    ]]");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   check_string (++n, "... global print"                   , s_print                 , "    " BACK_RED "DNOC   step=11    [[ pass=5     fail=3     badd=2     void=1    ]]" BACK_OFF);
   COND_FAIL =  0;
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   check_string (++n, "... global print"                   , s_print                 , "    " BACK_YEL "DNOC   step=11    [[ pass=5     fail=0     badd=2     void=1    ]]" BACK_OFF);
   COND_BADD =  0;
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   check_string (++n, "... global print"                   , s_print                 , "    " BACK_GRN "DNOC   step=11    [[ pass=5     fail=0     badd=0     void=1    ]]" BACK_OFF);
   summ ();
   return 0;
}

char
yunit_share_unit        (void)
{
   int         n           =    0;
   printf ("yUNIT_share................\n");
   printf ("\nyUNIT_share\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call SHARE verb handler"            , yUNIT_share ('a', "reusable conditions"             ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  SHARE (a) ===---------------------   reusable conditions   ---------------------===");
   check_value  (++n, "call ERAHS verb handler"            , yUNIT_erahs ('a'                               ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  ERAHS (a) ===---------------------   reusable conditions   ---------------------===");
   check_value  (++n, "call SHARE verb handler"            , yUNIT_share ('f', NULL                              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  SHARE (f) ===-----------------------------   ???   -----------------------------===");
   check_value  (++n, "call ERAHS verb handler"            , yUNIT_erahs ('f'                               ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  ERAHS (f) ===-----------------------------   ???   -----------------------------===");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call SHARE verb handler"            , yUNIT_share ('a', "reusable conditions"             ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_MAG "SHARE (a) ===---------------------   reusable conditions   ---------------------===" BACK_OFF);
   check_value  (++n, "call ERAHS verb handler"            , yUNIT_erahs ('a'                               ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_MAG "ERAHS (a) ===---------------------   reusable conditions   ---------------------===" BACK_OFF);
   summ ();
   return 0;
}

char
yunit_step_unit         (void)
{
   int         n           =    0;
   printf ("yUNIT_step.................\n");
   printf ("\nyunit_seqn\n");
   s_all = s_good = 0;
   check_string (++n, "generate sequence string"           , yunit_seqn ( -1)        , "aa" );
   check_string (++n, "generate sequence string"           , yunit_seqn (  0)        , "aa" );
   check_string (++n, "generate sequence string"           , yunit_seqn (  1)        , "ab" );
   check_string (++n, "generate sequence string"           , yunit_seqn ( 25)        , "az" );
   check_string (++n, "generate sequence string"           , yunit_seqn ( 26)        , "ba" );
   check_string (++n, "generate sequence string"           , yunit_seqn (300)        , "lo" );
   check_string (++n, "generate sequence string"           , yunit_seqn (675)        , "zz" );
   check_string (++n, "generate sequence string"           , yunit_seqn (676)        , "zz" );
   check_string (++n, "generate sequence string"           , yunit_seqn (900)        , "zz" );
   summ ();
   printf ("\nyUNIT_recd\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "change the level to yUNIT_FULL"     , yUNIT_level (YUNIT_FULL   ),  5 );
   yunit__unit_result (YUNIT_SUCC, 0);
   check_value  (++n, "call recd driver"                   , yUNIT__recd ( 954,  25, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  az) PASS   : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yunit__unit_result (YUNIT_FAIL, 0);
   check_value  (++n, "call recd driver"                   , yUNIT__recd ( 321, 300, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  lo) FAIL   : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   yunit__unit_result (YUNIT_WARN, 0);
   check_value  (++n, "call recd driver"                   , yUNIT__recd (1234, 657, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  zh) WARN   : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [01234]");
   yunit__unit_result (YUNIT_SUCC, 0);
   check_value  (++n, "call recd driver"                   , yUNIT__recd ( 954,  25, NULL             , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  az) PASS   : ???   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   yunit__unit_result (YUNIT_SUCC, 0);
   check_value  (++n, "call recd driver"                   , yUNIT__recd ( 954,  25, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_GRN "az) PASS  " BACK_OFF " : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yunit__unit_result (YUNIT_FAIL, 0);
   check_value  (++n, "call recd driver"                   , yUNIT__recd ( 321, 300, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_RED "lo) FAIL  " BACK_OFF " : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   yunit__unit_result (YUNIT_WARN, 0);
   check_value  (++n, "call recd driver"                   , yUNIT__recd (1234, 657, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_YEL "zh) WARN  " BACK_OFF " : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [01234]");
   summ ();
   return 0;
}

char
yunit_spec_unit         (void)
{
   int         n           =    0;
   printf ("yUNIT_spec.................\n");
   printf ("\nyUNIT_mode\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call MODE verb handler"             , yUNIT_mode  (   954,    0, "normal"                                           ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  aa) MODE   : normal (a pass is a pass ;)   .  .  .  .  .  .  .  .  .  .  .  [00954]");
   check_value  (++n, "call MODE verb handler"             , yUNIT_mode  (   321,  300, "FORCED_FAIL"                                      ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  lo) MODE   : ENABLE FORCED FAILURE (pass=fail, fail=pass) .  .  .  .  .  .  [00321]");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call MODE verb handler"             , yUNIT_mode  (   954,    0, "normal"                                           ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_CYN "aa) MODE  " BACK_OFF " : normal (a pass is a pass ;)   .  .  .  .  .  .  .  .  .  .  .  [00954]");
   check_value  (++n, "call MODE verb handler"             , yUNIT_mode  (   321,  300, "FORCED_FAIL"                                      ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_CYN "lo) MODE  " BACK_OFF " : ENABLE FORCED FAILURE (pass=fail, fail=pass) .  .  .  .  .  .  [00321]");
   summ ();
   printf ("\nyUNIT_code\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call CODE verb handler"             , yUNIT_code  (   954,    0, "working variable"   , "int  i = 32;"              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  aa) CODE   : working variable  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   check_string (++n, "... global suffix"                  , s_suffix                , "      code   : 12[int  i = 32;]");
   check_value  (++n, "call CODE verb handler"             , yUNIT_code  (   321,  300, NULL                 , "int  i = 32;"              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  lo) CODE   : ???   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   check_string (++n, "... global suffix"                  , s_suffix                , "      code   : 12[int  i = 32;]");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call CODE verb handler"             , yUNIT_code  (   954,    0, "working variable"   , "int  i = 32;"              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_CYN "aa) CODE  " BACK_OFF " : working variable  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   check_string (++n, "... global suffix"                  , s_suffix                , "      code   : 12[int  i = 32;]");
   summ ();
   printf ("\nyUNIT_load\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call LOAD verb handler"             , yUNIT_load  (   954,    0, "fresh data"         , "other"   , "qwerty"                    ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  aa) LOAD   : fresh data  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   check_string (++n, "... global suffix"                  , s_suffix                , "      other  :  6[qwerty]");
   check_value  (++n, "call LOAD verb handler"             , yUNIT_load  (   321,  300, NULL                 , "other"   , "qwerty"                    ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  lo) LOAD   : ???   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   check_string (++n, "... global suffix"                  , s_suffix                , "      other  :  6[qwerty]");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call LOAD verb handler"             , yUNIT_load  (   954,    0, "fresh data"         , "other"   , "qwerty"                    ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_CYN "aa) LOAD  " BACK_OFF " : fresh data  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   check_string (++n, "... global suffix"                  , s_suffix                , "      other  :  6[qwerty]");
   summ ();
   printf ("\nyUNIT_system\n");
   s_all = s_good = 0;
   check_char   (++n, "change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE), '-');
   check_value  (++n, "call SYSTEM verb handler"           , yUNIT_system(   954,    0, "quick command"      , "echo \"some good stuff\""              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  aa) SYSTEM : quick command  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   check_string (++n, "... global suffix"                  , s_suffix                , "      system : 22[echo \"some good stuff\"]" );
   check_value  (++n, "call SYSTEM verb handler"           , yUNIT_system(   321,  300, NULL                 , "other"                                 ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  lo) SYSTEM : ???   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   check_string (++n, "... global suffix"                  , s_suffix                , "      system :  5[other]");
   check_char   (++n, "change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  ), 'y');
   check_value  (++n, "call SYSTEM verb handler"           , yUNIT_system(   954,    0, "quick command"      , "echo \"some good stuff\""              ), 0);
   check_string (++n, "... global print"                   , s_print                 , "  " BACK_CYN "aa) SYSTEM" BACK_OFF " : quick command  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   check_string (++n, "... global suffix"                  , s_suffix                , "      system : 22[echo \"some good stuff\"]" );
   summ ();
   return 0;
}

char
main (void)
{
   yunit_globals_unit  ();
   yunit_base_unit     ();
   yunit_scrp_unit     ();
   /*> yunit_cond_unit  ();                                                           <* 
    *> yunit_share_unit ();                                                           <* 
    *> yunit_step_unit  ();                                                           <* 
    *> yunit_spec_unit  ();                                                           <*/
   return 0;
}

