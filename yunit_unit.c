#include    "yUNIT.h"
#include    "yUNIT_priv.h"


#include    "yUNIT_solo.h"


char
yunit__unit_globals      (void)
{
   yUNIT_minscrp ("yUNIT_base");

   yUNIT_mincond ("yUNIT_level");
   yUNIT_minval ("change the level to yUNIT_MUTE"     , yUNIT_level (YUNIT_MUTE, '-'), 0);
   yUNIT_minval ("change the level to yUNIT_SUMM"     , yUNIT_level (YUNIT_SUMM, '-'), 1);
   yUNIT_minval ("change the level to yUNIT_SCRP"     , yUNIT_level (YUNIT_SCRP, '-'), 2);
   yUNIT_minval ("change the level to yUNIT_COND"     , yUNIT_level (YUNIT_COND, '-'), 3);
   yUNIT_minval ("change the level to yUNIT_STEP"     , yUNIT_level (YUNIT_STEP, '-'), 4);
   yUNIT_minval ("change the level to yUNIT_FULL"     , yUNIT_level (YUNIT_FULL, '-'), 5);
   yUNIT_minval ("change the level too low"           , yUNIT_level (-1        , '-'), 5);
   yUNIT_minval ("change the level too high"          , yUNIT_level (15        , '-'), 5);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_eterm");
   yUNIT_minchr ("change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE, '-'), '-');
   yUNIT_minchr ("change the eterm to yUNIT_ETERM"    , yUNIT_eterm (YUNIT_ETERM  , '-'), 'y');
   yUNIT_minchr ("change the eterm to unknown"        , yUNIT_eterm (0            , '-'), '-');
   yUNIT_minchr ("change the eterm to unknown"        , yUNIT_eterm ('w'          , '-'), '-');
   yUNIT_minchr ("change the eterm to unknown"        , yUNIT_eterm (' '          , '-'), '-');
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_base         (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_base");

   yUNIT_mincond ("configure a new unit test");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE), 0);
   yUNIT_minstr ("... global name"                    , myUNIT.name             , "/tmp/yunit_unit.urun"       );
   yUNIT_minval ("... global level"                   , myUNIT.level            , YUNIT_FULL                   );
   yUNIT_minchr ("... global eterm"                   , myUNIT.eterm            , YUNIT_CONSOLE                );
   yUNIT_minstr ("... check (0) header line"          , yUNIT_read (myUNIT.name, 0, &c), "yUNIT - heatherly unit testing framework ---------------------------------------(beg)");
   yUNIT_minstr ("... check (1) level line"           , yUNIT_read (myUNIT.name, 1, &c), "   assign output level to (5) YUNIT_FULL");
   yUNIT_minstr ("... check (2) eterm line"           , yUNIT_read (myUNIT.name, 2, &c), "   assign format/color to (-) CONSOLE");
   yUNIT_minstr ("... check (3) empty line"           , yUNIT_read (myUNIT.name, 3, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 4                            );
   yUNIT_minval ("close and remove"                   , yunit_close_and_remove ()  , 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("configure a new unit test");
   yUNIT_minval ("create a unit"                      , yUNIT_unit  ("/tmp/uniter"    , YUNIT_SUMM, YUNIT_ETERM  ), 0);
   yUNIT_minstr ("... global name"                    , myUNIT.name             , "/tmp/uniter.urun"           );
   yUNIT_minval ("... global level"                   , myUNIT.level            , YUNIT_SUMM                   );
   yUNIT_minchr ("... global eterm"                   , myUNIT.eterm            , YUNIT_ETERM                  );
   yUNIT_minstr ("... check (0) header line"          , yUNIT_read (myUNIT.name, 0, &c), "yUNIT - heatherly unit testing framework ---------------------------------------(beg)");
   yUNIT_minstr ("... check (1) empty line"           , yUNIT_read (myUNIT.name, 1, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 2                            );
   yUNIT_minval ("close and remove"                   , yunit_close_and_remove ()  , 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("configure a new unit test");
   yUNIT_minval ("create a unit"                      , yUNIT_unit  ("/tmp/unit.urun" , YUNIT_STEP, YUNIT_ETERM  ), 0);
   yUNIT_minstr ("... global name"                    , myUNIT.name             , "/tmp/unit.urun"             );
   yUNIT_minval ("... global level"                   , myUNIT.level            , YUNIT_STEP                   );
   yUNIT_minchr ("... global eterm"                   , myUNIT.eterm            , YUNIT_ETERM                  );
   yUNIT_minstr ("... check (0) header line"          , yUNIT_read (myUNIT.name, 0, &c), "yUNIT - heatherly unit testing framework ---------------------------------------(beg)");
   yUNIT_minstr ("... check (1) level line"           , yUNIT_read (myUNIT.name, 1, &c), "   assign output level to (4) YUNIT_STEP");
   yUNIT_minstr ("... check (2) eterm line"           , yUNIT_read (myUNIT.name, 2, &c), "   assign format/color to (y) ETERM");
   yUNIT_minstr ("... check (3) empty line"           , yUNIT_read (myUNIT.name, 3, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 4                            );
   yUNIT_minval ("close and remove"                   , yunit_close_and_remove ()  , 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("close out a unit test");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE), 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   UNIT_TEST = 511;
   UNIT_PASS = 495;
   UNIT_FAIL =  23;
   UNIT_BADD =   6;
   UNIT_VOID =   0;
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), -29);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) header line"          , yUNIT_read (myUNIT.name, 1, &c), "TINU   step=511   [[ pass=495   fail=23    badd=6     void=0    ]]");
   yUNIT_minstr ("... check (2) empty line"           , yUNIT_read (myUNIT.name, 2, &c), "");
   yUNIT_minstr ("... check (3) header line"          , yUNIT_read (myUNIT.name, 3, &c), "yUNIT - heatherly unit testing framework ---------------------------------------(end)");
   yUNIT_minval ("... check line count"               , c                       , 4                            );
   yUNIT_minval ("remove the reporting file"          , yunit_remove ()            , 0);

   yUNIT_mincond ("close out a unit test (failing)");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   UNIT_TEST = 511;
   UNIT_PASS = 495;
   UNIT_FAIL =  23;
   UNIT_BADD =   6;
   UNIT_VOID =   0;
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), -29);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) header line"          , yUNIT_read (myUNIT.name, 1, &c), BACK_RED "TINU   step=511   [[ pass=495   fail=23    badd=6     void=0    ]]" BACK_OFF);
   yUNIT_minstr ("... check (2) empty line"           , yUNIT_read (myUNIT.name, 2, &c), "");
   yUNIT_minstr ("... check (3) header line"          , yUNIT_read (myUNIT.name, 3, &c), "yUNIT - heatherly unit testing framework ---------------------------------------(end)");
   yUNIT_minval ("... check line count"               , c                       , 4                            );
   yUNIT_minval ("remove the reporting file"          , yunit_remove ()            , 0);

   yUNIT_mincond ("close out a unit test (warning)");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   UNIT_TEST = 511;
   UNIT_PASS = 495;
   UNIT_FAIL =   0;
   UNIT_BADD =   6;
   UNIT_VOID =   0;
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), -6);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) header line"          , yUNIT_read (myUNIT.name, 1, &c), BACK_YEL "TINU   step=511   [[ pass=495   fail=0     badd=6     void=0    ]]" BACK_OFF);
   yUNIT_minstr ("... check (2) empty line"           , yUNIT_read (myUNIT.name, 2, &c), "");
   yUNIT_minstr ("... check (3) header line"          , yUNIT_read (myUNIT.name, 3, &c), "yUNIT - heatherly unit testing framework ---------------------------------------(end)");
   yUNIT_minval ("... check line count"               , c                       , 4                            );
   yUNIT_minval ("remove the reporting file"          , yunit_remove ()            , 0);

   yUNIT_mincond ("close out a unit test (passing)");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   UNIT_TEST = 511;
   UNIT_PASS = 495;
   UNIT_FAIL =   0;
   UNIT_BADD =   0;
   UNIT_VOID =   0;
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) header line"          , yUNIT_read (myUNIT.name, 1, &c), BACK_GRN "TINU   step=511   [[ pass=495   fail=0     badd=0     void=0    ]]" BACK_OFF);
   yUNIT_minstr ("... check (2) empty line"           , yUNIT_read (myUNIT.name, 2, &c), "");
   yUNIT_minstr ("... check (3) header line"          , yUNIT_read (myUNIT.name, 3, &c), "yUNIT - heatherly unit testing framework ---------------------------------------(end)");
   yUNIT_minval ("... check line count"               , c                       , 4                            );
   yUNIT_minval ("remove the reporting file"          , yunit_remove ()            , 0);

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_scrp         (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_scrp");

   yUNIT_mincond ("basic script line");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SCRP verb handler"             , yUNIT_scrp  (   954,   0, "function"          , "first script"              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SCRP [00] first script =======================================================[00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) empty line"           , yUNIT_read (myUNIT.name, 1, &c), "");
   yUNIT_minstr ("... check (2) separator"            , yUNIT_read (myUNIT.name, 2, &c), "===[[ NEW SCRIPT ]]==================================================================");
   yUNIT_minstr ("... check (3) header line"          , yUNIT_read (myUNIT.name, 3, &c), "SCRP [00] first script =======================================================[00954]");
   yUNIT_minstr ("... check (4) focus line"           , yUNIT_read (myUNIT.name, 4, &c), "  focus : function");
   yUNIT_minval ("... check line count"               , c                       , 5);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("basic script line");
   yUNIT_minval ("create a unit on cond output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_COND, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SCRP verb handler"             , yUNIT_scrp  (   954,   0, "function"          , "first script"              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SCRP [00] first script =======================================================[00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) empty line"           , yUNIT_read (myUNIT.name, 1, &c), "");
   yUNIT_minstr ("... check (2) header line"          , yUNIT_read (myUNIT.name, 2, &c), "SCRP [00] first script =======================================================[00954]");
   yUNIT_minstr ("... check (3) focus line"           , yUNIT_read (myUNIT.name, 3, &c), "  focus : function");
   yUNIT_minval ("... check line count"               , c                       , 4);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("basic script line");
   yUNIT_minval ("create a unit on scrp output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_SCRP, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SCRP verb handler"             , yUNIT_scrp  (   954,   0, "function"          , "first script"              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SCRP [00] first script =======================================================[00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) header line"          , yUNIT_read (myUNIT.name, 1, &c), "SCRP [00] first script =======================================================[00954]");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("basic script line");
   yUNIT_minval ("create a unit on summ/mute output"  , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_SUMM, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SCRP verb handler"             , yUNIT_scrp  (   954,   0, "function"          , "first script"              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SCRP [00] first script =======================================================[00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 0);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("basic script line");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SCRP verb handler"             , yUNIT_scrp  (   954,   0, "function"          , "first script"              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SCRP [00] first script =======================================================[00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) empty line"           , yUNIT_read (myUNIT.name, 1, &c), "");
   yUNIT_minstr ("... check (2) separator"            , yUNIT_read (myUNIT.name, 2, &c), "===[[ NEW SCRIPT ]]==================================================================");
   yUNIT_minstr ("... check (3) header line"          , yUNIT_read (myUNIT.name, 3, &c), "SCRP [00] first script =======================================================[00954]");
   yUNIT_minstr ("... check (4) focus line"           , yUNIT_read (myUNIT.name, 4, &c), "  focus : function");
   yUNIT_minval ("... check line count"               , c                       , 5);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("basic script line");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SCRP verb handler"             , yUNIT_scrp  (   306,  10, "function"          , "second"                    ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SCRP [10] second =============================================================[00306]");
   yUNIT_minval ("call with out of range values"      , yUNIT_scrp  (    -1,  -1, "function"          , NULL                        ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SCRP [00] ??? ================================================================[00000]");
   yUNIT_minval ("call with out of range values"      , yUNIT_scrp  (100000, 100, "function"          , NULL                        ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SCRP [99] ??? ================================================================[99999]");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_sect         (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_sect");

   yUNIT_mincond ("yUNIT_sect");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SECT verb handler"             , yUNIT_sect  ("a section"                       ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                          a section                          ----=== TCES");
   yUNIT_minval ("call SECT with SCRP"                , yUNIT_sect  ("SCRP"                            ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                          a section                          ----=== TCES");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) empty line"           , yUNIT_read (myUNIT.name, 1, &c), "");
   yUNIT_minstr ("... check (2) top divider"          , yUNIT_read (myUNIT.name, 2, &c), "=========================------------------------------------========================");
   yUNIT_minstr ("... check (3) section"              , yUNIT_read (myUNIT.name, 3, &c), "SECT ===----                          a section                          ----=== TCES");
   yUNIT_minstr ("... check (4) bot divider"          , yUNIT_read (myUNIT.name, 4, &c), "=========================------------------------------------========================");
   yUNIT_minval ("... check line count"               , c                       , 5);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_sect");
   yUNIT_minval ("create a unit on cond output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_COND, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SECT verb handler"             , yUNIT_sect  ("system initialization"           ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                    system initialization                    ----=== TCES");
   yUNIT_minval ("call SECT with SCRP"                , yUNIT_sect  ("SCRP"                            ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                    system initialization                    ----=== TCES");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) empty line"           , yUNIT_read (myUNIT.name, 1, &c), "");
   yUNIT_minstr ("... check (2) top divider"          , yUNIT_read (myUNIT.name, 2, &c), "=========================------------------------------------========================");
   yUNIT_minstr ("... check (3) section"              , yUNIT_read (myUNIT.name, 3, &c), "SECT ===----                    system initialization                    ----=== TCES");
   yUNIT_minstr ("... check (4) bot divider"          , yUNIT_read (myUNIT.name, 4, &c), "=========================------------------------------------========================");
   yUNIT_minval ("... check line count"               , c                       , 5);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_sect");
   yUNIT_minval ("create a unit on scrp output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_SCRP, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SECT verb handler"             , yUNIT_sect  ("system initialization"           ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                    system initialization                    ----=== TCES");
   yUNIT_minval ("call SECT with SCRP"                , yUNIT_sect  ("SCRP"                            ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                    system initialization                    ----=== TCES");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (3) section"              , yUNIT_read (myUNIT.name, 1, &c), "SECT ===----                    system initialization                    ----=== TCES");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_sect");
   yUNIT_minval ("create a unit on mute output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_SUMM, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SECT verb handler"             , yUNIT_sect  ("system initialization"           ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                    system initialization                    ----=== TCES");
   yUNIT_minval ("call SECT with SCRP"                , yUNIT_sect  ("SCRP"                            ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                    system initialization                    ----=== TCES");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 0);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_sect");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SECT verb handler"             , yUNIT_sect  ("a section"                       ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                          a section                          ----=== TCES");
   yUNIT_minval ("call SECT with SCRP"                , yUNIT_sect  ("SCRP"                            ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                          a section                          ----=== TCES");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) empty line"           , yUNIT_read (myUNIT.name, 1, &c), "");
   yUNIT_minstr ("... check (2) top divider"          , yUNIT_read (myUNIT.name, 2, &c), "=========================------------------------------------========================");
   yUNIT_minstr ("... check (3) section"              , yUNIT_read (myUNIT.name, 3, &c), "SECT ===----                          a section                          ----=== TCES");
   yUNIT_minstr ("... check (4) bot divider"          , yUNIT_read (myUNIT.name, 4, &c), "=========================------------------------------------========================");
   yUNIT_minval ("... check line count"               , c                       , 5);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_sect defenses");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("call SECT verb handler"             , yUNIT_sect  (NULL                              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                             ???                             ----=== TCES");
   yUNIT_minval ("call SECT with SCRP"                , yUNIT_sect  ("SCRP"                            ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "SECT ===----                             ???                             ----=== TCES");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_prcs         (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_prcs");

   yUNIT_mincond ("yUNIT_prcs");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   SCRP_TEST =  11;
   SCRP_TEST = 511;
   SCRP_PASS = 495;
   SCRP_FAIL =  23;
   SCRP_BADD =   6;
   SCRP_VOID =   0;
   yUNIT_minval ("call PCRS verb handler"             , yUNIT_prcs  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  PRCS   step=511   [[ pass=495   fail=23    badd=6     void=0    ]]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  PRCS   step=511   [[ pass=495   fail=23    badd=6     void=0    ]]");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), -29);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_prcs");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call PCRS verb handler"             , yUNIT_prcs  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_RED "PRCS   step=511   [[ pass=495   fail=23    badd=6     void=0    ]]" BACK_OFF);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  " BACK_RED "PRCS   step=511   [[ pass=495   fail=23    badd=6     void=0    ]]" BACK_OFF);
   yUNIT_minval ("... check line count"               , c                       , 2);
   SCRP_FAIL =   0;
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call PCRS verb handler"             , yUNIT_prcs  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_YEL "PRCS   step=511   [[ pass=495   fail=0     badd=6     void=0    ]]" BACK_OFF);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  " BACK_YEL "PRCS   step=511   [[ pass=495   fail=0     badd=6     void=0    ]]" BACK_OFF);
   yUNIT_minval ("... check line count"               , c                       , 2);
   SCRP_BADD =   0;
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call PCRS verb handler"             , yUNIT_prcs  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_GRN "PRCS   step=511   [[ pass=495   fail=0     badd=0     void=0    ]]" BACK_OFF);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  " BACK_GRN "PRCS   step=511   [[ pass=495   fail=0     badd=0     void=0    ]]" BACK_OFF);
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), -999);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_cond         (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_cond");

   yUNIT_mincond ("yUNIT_cond");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call COND verb handler"             , yUNIT_cond  (   954,  321, "check the initial values"                         ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  COND [321] check the initial values -- -- -- -- -- -- -- -- -- -- -- -- -- -[00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  COND [321] check the initial values -- -- -- -- -- -- -- -- -- -- -- -- -- -[00954]");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_cond");
   yUNIT_minval ("create a unit on cond output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_COND, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call COND verb handler"             , yUNIT_cond  (   954,  321, "check the initial values"                         ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  COND [321] check the initial values -- -- -- -- -- -- -- -- -- -- -- -- -- -[00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  COND [321] check the initial values -- -- -- -- -- -- -- -- -- -- -- -- -- -[00954]");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_cond");
   yUNIT_minval ("create a unit on scrp output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_SCRP, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call COND verb handler"             , yUNIT_cond  (   954,  321, "check the initial values"                         ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  COND [321] check the initial values -- -- -- -- -- -- -- -- -- -- -- -- -- -[00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 0);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_cond");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call COND verb handler"             , yUNIT_cond  (   954,  321, "check the initial values"                         ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  COND [321] check the initial values -- -- -- -- -- -- -- -- -- -- -- -- -- -[00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  COND [321] check the initial values -- -- -- -- -- -- -- -- -- -- -- -- -- -[00954]");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_cond defenses");
   yUNIT_minval ("call COND verb handler"             , yUNIT_cond  (    -1,   -1, NULL                                               ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  COND [000] ??? -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -[00000]");
   yUNIT_minval ("call COND verb handler"             , yUNIT_cond  (100000, 1000, "excellent stuffs"                                 ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  COND [999] excellent stuffs - -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -[99999]");
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_group        (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_group");

   yUNIT_mincond ("yUNIT_group");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call GROUP verb handler"            , yUNIT_group ("nice group"                      ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  GROUP ===---------------------------   nice group   ----------------------------===");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  GROUP ===---------------------------   nice group   ----------------------------===");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_group");
   yUNIT_minval ("create a unit on cond output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_COND, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call GROUP verb handler"            , yUNIT_group ("nice group"                      ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  GROUP ===---------------------------   nice group   ----------------------------===");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  GROUP ===---------------------------   nice group   ----------------------------===");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_group");
   yUNIT_minval ("create a unit on scrp output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_SCRP, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call GROUP verb handler"            , yUNIT_group ("nice group"                      ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  GROUP ===---------------------------   nice group   ----------------------------===");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 0);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_group");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call GROUP verb handler"            , yUNIT_group ("nice group"                      ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  GROUP ===---------------------------   nice group   ----------------------------===");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  GROUP ===---------------------------   nice group   ----------------------------===");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_group defenses");
   yUNIT_minchr ("change the eterm to yUNIT_CONSOLE"  , yUNIT_eterm (YUNIT_CONSOLE, '-'), '-');
   yUNIT_minval ("call GROUP verb handler"            , yUNIT_group (NULL                              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  GROUP ===-------------------------------   ???   -------------------------------===");
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_dnoc         (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_group");

   yUNIT_mincond ("yUNIT_dnoc");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   COND_TEST = 11;
   COND_PASS =  5;
   COND_FAIL =  3;
   COND_BADD =  2;
   COND_VOID =  1;
   yUNIT_minval ("call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "      DNOC   step=11    [[ pass=5     fail=3     badd=2     void=1    ]]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "      DNOC   step=11    [[ pass=5     fail=3     badd=2     void=1    ]]");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_dnoc");
   yUNIT_minval ("create a unit on cond output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_COND, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   COND_TEST = 11;
   COND_PASS =  5;
   COND_FAIL =  3;
   COND_BADD =  2;
   COND_VOID =  1;
   yUNIT_minval ("call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "      DNOC   step=11    [[ pass=5     fail=3     badd=2     void=1    ]]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "      DNOC   step=11    [[ pass=5     fail=3     badd=2     void=1    ]]");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_dnoc");
   yUNIT_minval ("create a unit on scrp output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_SCRP, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   COND_TEST = 11;
   COND_PASS =  5;
   COND_FAIL =  3;
   COND_BADD =  2;
   COND_VOID =  1;
   yUNIT_minval ("call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "      DNOC   step=11    [[ pass=5     fail=3     badd=2     void=1    ]]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 0);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_dnoc");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   COND_TEST = 11;
   COND_PASS =  5;
   COND_FAIL =  3;
   COND_BADD =  2;
   COND_VOID =  1;
   yUNIT_minval ("call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "      " BACK_RED "DNOC   step=11    [[ pass=5     fail=3     badd=2     void=1    ]]" BACK_OFF);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "      " BACK_RED "DNOC   step=11    [[ pass=5     fail=3     badd=2     void=1    ]]" BACK_OFF);
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_dnoc");
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   COND_FAIL =  0;
   yUNIT_minval ("call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "      " BACK_YEL "DNOC   step=11    [[ pass=5     fail=0     badd=2     void=1    ]]" BACK_OFF);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "      " BACK_YEL "DNOC   step=11    [[ pass=5     fail=0     badd=2     void=1    ]]" BACK_OFF);
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_dnoc");
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   COND_BADD =  0;
   yUNIT_minval ("call DNOC verb handler"             , yUNIT_dnoc  ()                                  , 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "      " BACK_GRN "DNOC   step=11    [[ pass=5     fail=0     badd=0     void=1    ]]" BACK_OFF);
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "      " BACK_GRN "DNOC   step=11    [[ pass=5     fail=0     badd=0     void=1    ]]" BACK_OFF);
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_step         (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_step");

   yUNIT_mincond ("yunit_seqn");
   yUNIT_minstr ("generate sequence string"           , yunit_seqn ( -1)        , "aa" );
   yUNIT_minstr ("generate sequence string"           , yunit_seqn (  0)        , "aa" );
   yUNIT_minstr ("generate sequence string"           , yunit_seqn (  1)        , "ab" );
   yUNIT_minstr ("generate sequence string"           , yunit_seqn ( 25)        , "az" );
   yUNIT_minstr ("generate sequence string"           , yunit_seqn ( 26)        , "ba" );
   yUNIT_minstr ("generate sequence string"           , yunit_seqn (300)        , "lo" );
   yUNIT_minstr ("generate sequence string"           , yunit_seqn (675)        , "zz" );
   yUNIT_minstr ("generate sequence string"           , yunit_seqn (676)        , "zz" );
   yUNIT_minstr ("generate sequence string"           , yunit_seqn (900)        , "zz" );
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_recd");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yunit__unit_result (YUNIT_SUCC, 0);
   yUNIT_minval ("call recd driver"                   , yUNIT__recd ( 954,  25, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  az) PASS   : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  az) PASS   : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 2, &c), "      method : yUNIT_void (0, 15, \"test\")");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 3, &c), "      test   : i_equal    (rc =    0)");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 4, &c), "      expect : ");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 5, &c), "      actual : ");
   yUNIT_minval ("... check line count"               , c                       , 6);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_recd");
   yUNIT_minval ("create a unit on cond output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_COND, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yunit__unit_result (YUNIT_SUCC, 0);
   yUNIT_minval ("call recd driver"                   , yUNIT__recd ( 954,  25, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  az) PASS   : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 0);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_recd");
   yUNIT_minval ("create a unit on scrp output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_SCRP, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yunit__unit_result (YUNIT_SUCC, 0);
   yUNIT_minval ("call recd driver"                   , yUNIT__recd ( 954,  25, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  az) PASS   : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minval ("... check line count"               , c                       , 0);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_recd");
   yUNIT_minval ("create a unit on scrp output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_SCRP, YUNIT_CONSOLE)  , 0);
   yunit__unit_result (YUNIT_FAIL, 0);
   yUNIT_minval ("call recd driver"                   , yUNIT__recd ( 321, 300, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  lo) FAIL   : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   yunit__unit_result (YUNIT_WARN, 0);
   yUNIT_minval ("call recd driver"                   , yUNIT__recd (1234, 657, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  zh) WARN   : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [01234]");
   yunit__unit_result (YUNIT_SUCC, 0);
   yUNIT_minval ("call recd driver"                   , yUNIT__recd ( 954,  25, NULL             , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  az) PASS   : ???   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_recd");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yunit__unit_result (YUNIT_SUCC, 0);
   yUNIT_minval ("call recd driver"                   , yUNIT__recd ( 954,  25, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_GRN "az) PASS  " BACK_OFF " : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yunit__unit_result (YUNIT_FAIL, 0);
   yUNIT_minval ("call recd driver"                   , yUNIT__recd ( 321, 300, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_RED "lo) FAIL  " BACK_OFF " : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   yunit__unit_result (YUNIT_WARN, 0);
   yUNIT_minval ("call recd driver"                   , yUNIT__recd (1234, 657, "run function"   , "yUNIT_void"     , "0, 15, \"test\""                   , "i_equal"  ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_YEL "zh) WARN  " BACK_OFF " : run function   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [01234]");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_share        (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_share");

   yUNIT_mincond ("UNIT_share");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SHARE verb handler"            , yUNIT_share ('a', "reusable conditions"             ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  SHARE (a) ===---------------------   reusable conditions   ---------------------===");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  SHARE (a) ===---------------------   reusable conditions   ---------------------===");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call ERAHS verb handler"            , yUNIT_erahs ('a'                               ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  ERAHS (a) ===---------------------   reusable conditions   ---------------------===");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  ERAHS (a) ===---------------------   reusable conditions   ---------------------===");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("UNIT_share");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SHARE verb handler"            , yUNIT_share ('f', NULL                              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  SHARE (f) ===-----------------------------   ???   -----------------------------===");
   yUNIT_minval ("call ERAHS verb handler"            , yUNIT_erahs ('f'                               ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  ERAHS (f) ===-----------------------------   ???   -----------------------------===");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("UNIT_share");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("call SHARE verb handler"            , yUNIT_share ('a', "reusable conditions"             ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_MAG "SHARE (a) ===---------------------   reusable conditions   ---------------------===" BACK_OFF);
   yUNIT_minval ("call ERAHS verb handler"            , yUNIT_erahs ('a'                               ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_MAG "ERAHS (a) ===---------------------   reusable conditions   ---------------------===" BACK_OFF);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yunit__unit_spec         (void)
{
   int         c           =    0;

   yUNIT_minscrp ("yUNIT_spec");

   yUNIT_mincond ("yUNIT_mode");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call MODE verb handler"             , yUNIT_mode  (   954,    0, "normal"                                           ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  aa) MODE   : normal (a pass is a pass ;)   .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  aa) MODE   : normal (a pass is a pass ;)   .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("call MODE verb handler"             , yUNIT_mode  (   321,  300, "FORCED_FAIL"                                      ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  lo) MODE   : ENABLE FORCED FAILURE (pass=fail, fail=pass) .  .  .  .  .  .  [00321]");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_mode");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call MODE verb handler"             , yUNIT_mode  (   954,    0, "normal"                                           ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_CYN "aa) MODE  " BACK_OFF " : normal (a pass is a pass ;)   .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  " BACK_CYN "aa) MODE  " BACK_OFF " : normal (a pass is a pass ;)   .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minval ("... check line count"               , c                       , 2);
   yUNIT_minval ("call MODE verb handler"             , yUNIT_mode  (   321,  300, "FORCED_FAIL"                                      ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_CYN "lo) MODE  " BACK_OFF " : ENABLE FORCED FAILURE (pass=fail, fail=pass) .  .  .  .  .  .  [00321]");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_code");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call CODE verb handler"             , yUNIT_code  (   954,    0, "working variable"   , "int  i = 32;"              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  aa) CODE   : working variable  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... global suffix"                  , s_suffix                , "      code   : 12[int  i = 32;]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  aa) CODE   : working variable  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (2) suffix"               , yUNIT_read (myUNIT.name, 2, &c), "      code   : 12[int  i = 32;]");
   yUNIT_minval ("... check line count"               , c                       , 3);
   yUNIT_minval ("call CODE verb handler"             , yUNIT_code  (   321,  300, NULL                 , "int  i = 32;"              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  lo) CODE   : ???   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   yUNIT_minstr ("... global suffix"                  , s_suffix                , "      code   : 12[int  i = 32;]");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_mode");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call CODE verb handler"             , yUNIT_code  (   954,    0, "working variable"   , "int  i = 32;"              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_CYN "aa) CODE  " BACK_OFF " : working variable  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... global suffix"                  , s_suffix                , "      code   : 12[int  i = 32;]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  " BACK_CYN "aa) CODE  " BACK_OFF " : working variable  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (2) suffix"               , yUNIT_read (myUNIT.name, 2, &c), "      code   : 12[int  i = 32;]");
   yUNIT_minval ("... check line count"               , c                       , 3);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_load");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call LOAD verb handler"             , yUNIT_load  (   954,    0, "fresh data"         , "other"   , "qwerty"                    ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  aa) LOAD   : fresh data  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... global suffix"                  , s_suffix                , "      other  :  6[qwerty]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  aa) LOAD   : fresh data  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (2) suffix"               , yUNIT_read (myUNIT.name, 2, &c), "      other  :  6[qwerty]"              );
   yUNIT_minval ("... check line count"               , c                       , 3);
   yUNIT_minval ("call LOAD verb handler"             , yUNIT_load  (   321,  300, NULL                 , "other"   , "qwerty"                    ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  lo) LOAD   : ???   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   yUNIT_minstr ("... global suffix"                  , s_suffix                , "      other  :  6[qwerty]");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_load");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call LOAD verb handler"             , yUNIT_load  (   954,    0, "fresh data"         , "other"   , "qwerty"                    ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_CYN "aa) LOAD  " BACK_OFF " : fresh data  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... global suffix"                  , s_suffix                , "      other  :  6[qwerty]");
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  " BACK_CYN "aa) LOAD  " BACK_OFF " : fresh data  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (2) suffix"               , yUNIT_read (myUNIT.name, 2, &c), "      other  :  6[qwerty]");;
   yUNIT_minval ("... check line count"               , c                       , 3);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_system");
   yUNIT_minval ("create a unit on full output"       , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_CONSOLE)  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SYSTEM verb handler"           , yUNIT_system(   954,    0, "quick command"      , "echo \"some good stuff\""              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  aa) SYSTEM : quick command  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... global suffix"                  , s_suffix                , "      system : 22[echo \"some good stuff\"]" );
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  aa) SYSTEM : quick command  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (2) suffix"               , yUNIT_read (myUNIT.name, 2, &c), "      system : 22[echo \"some good stuff\"]" );
   yUNIT_minval ("... check line count"               , c                       , 3);
   yUNIT_minval ("call SYSTEM verb handler"           , yUNIT_system(   321,  300, NULL                 , "other"                                 ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  lo) SYSTEM : ???   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00321]");
   yUNIT_minstr ("... global suffix"                  , s_suffix                , "      system :  5[other]");
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("yUNIT_system");
   yUNIT_minval ("create a unit on full/eterm"        , yUNIT_unit  ("/tmp/yunit_unit", YUNIT_FULL, YUNIT_ETERM  )  , 0);
   yUNIT_minval ("cycle reporting file"               , yunit_cycle ()             , 0);
   yUNIT_minval ("call SYSTEM verb handler"           , yUNIT_system(   954,    0, "quick command"      , "echo \"some good stuff\""              ), 0);
   yUNIT_minstr ("... global print"                   , s_print                 , "  " BACK_CYN "aa) SYSTEM" BACK_OFF " : quick command  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... global suffix"                  , s_suffix                , "      system : 22[echo \"some good stuff\"]" );
   yUNIT_minstr ("... check (0) empty line"           , yUNIT_read (myUNIT.name, 0, &c), "");
   yUNIT_minstr ("... check (1) footer"               , yUNIT_read (myUNIT.name, 1, &c), "  " BACK_CYN "aa) SYSTEM" BACK_OFF " : quick command  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  [00954]");
   yUNIT_minstr ("... check (2) suffix"               , yUNIT_read (myUNIT.name, 2, &c), "      system : 22[echo \"some good stuff\"]" );
   yUNIT_minval ("... check line count"               , c                       , 3);
   yUNIT_minval ("close out a unit test"              , yUNIT_tinu  (), 0);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
main (void)
{
   /*---(unit test level)----------------*/
   yunit__unit_globals  ();
   yunit__unit_base     ();
   /*---(script level)-------------------*/
   yunit__unit_scrp     ();
   yunit__unit_sect     ();
   yunit__unit_prcs     ();
   /*---(condition level)----------------*/
   yunit__unit_cond     ();
   yunit__unit_group    ();
   yunit__unit_dnoc     ();
   /*---(step level)---------------------*/
   yunit__unit_step     ();
   yunit__unit_share    ();
   yunit__unit_spec     ();

   yUNIT_mintinu ();
   return 0;
}

