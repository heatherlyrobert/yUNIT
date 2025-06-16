/*===[[ START HDOC ]]=========================================================*/
/*===[[ HEADER ]]==============================================================#

 *   focus         : (PS) programming support
 *   niche         : (st) software testing
 *   heritage      : daktyloi (the fingers, titan gods of metal working)
 *   purpose       : provide consistent automated unit testing framework
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : gnu/ansi-c  (right, just, best, standard, and everlasting)
 *   dependencies  : yVAR only (for var testing)
 *   size          : small       (less than 1,000 slocL)
 *
 *   author        : the_heatherlys
 *   created       : 2008-08 -- from previous c/c++ and bash versions
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 *
 */
/*===[[ SUMMARY ]]=============================================================#

 *   unit testing is a software verification and assurance method in which a
 *   programmer tests if individual units (functions) of source code are fit for
 *   use and remain so.  this form of testing is integral to build automation,
 *   refactoring, and regression testing.
 *
 */
/*===[[ PURPOSE ]]=============================================================#
 *
 *   yUNIT is a set of shared functions providing flexible, reliable, and
 *   automated unit testing services to make a painful, haphazard, tedious,
 *   neglected, and error prone process into a systematic, automated, rapid,
 *   responsive, and helpful one; and more likely to be used by a programmer
 *
 *   yUNIT focuses on providing three levels of testing -- (a), (b), and (c)...
 *      a) black box - which calls public functions and tests external effects
 *      b) dark box  - which uses public "accessors" to monitor key vars/states
 *      c) gray box  - allows individual calls to private functions
 *      d) light box - allows access to specific and private variables/states
 *      e) white box - allows internal access for structure and path testing
 *
 *   testing at level (a) is the only clean level for integration, but our unit
 *   testing needs to be more specific for us to quickly isolate issues.  using
 *   (d) and (e) jeopradize refactoring and reuse, so i refrain, and leave that
 *   work to the online debugger where it rightfully belongs
 *
 *   additionally, yUNIT must be able to adapt itself to all my contexts...
 *      - normal programs
 *      - shell scripts
 *      - daemons and background testing
 *      - kernel/system components
 *   we simply don't have time to learn additional tools for each context and
 *   therefore have to keep switching gears.
 *
 *   as always, there are many existing libraries and utilities have been built
 *   by better programmers which are likely superior in speed, size, capability,
 *   and reliability; BUT, i would not have learned nearly as much using them,
 *   so follow the adage..
 *
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 *
 *   the basic idea is to take all the great ideas from existing frameworks
 *   without taking all the unneeded complexity that comes from backwards
 *   compatiblilty and traditional views.  in this case, if i can get the same
 *   result with less fuss and mess, even better
 *
 *   ADVANTAGES, automated unit testing in general...
 *      - most important, allows testing to be done by the computer, in batch
 *      - allows programs to be tested very quickly
 *      - does not skip steps when under stress or time pressures
 *      - is precisely repeatable and therefore dependable
 *      - allows coders to test much more frequently (rather than saving it up)
 *      - causes a viewpoint that encourages defensive coding practices
 *      - drives increased interface stability
 *      - truly enables refactoring for disciplined changes
 *      - does not get tired of testing the same old thing
 *      - supports mini release philosophy by easing testing work
 *      - great basis for proper regression testing
 *
 *   DISADVANTAGES
 *      - one more thing to go wrong in an already complex world
 *      - requires more programming, and hence increases coding volume
 *      - can appear to be a silver bullet and reduce needed "hand testing"
 *      - can tick off programmers as a waste or beneath them
 *      - can be incomplete and cause late failures
 *      - can get too detailed and resist good changes to the code
 *
 */
/*===[[ DECISION -- HOW TO TEST INDIVIDUAL PROGRAMS ]]=========================#

 *   PROBLEM (pr)
 *      programs are quite difficult to test and even harder to test repeatedly,
 *      in fact they are nearly impossible to regression test as humans get
 *      bored, tired, and inattentive when repeating a process which makes
 *      uncovering bugs, especially when under pressure, simply impossible
 *
 *   OBJECTIVES (o)
 *      - make testing as easy as possible so that it gets done
 *      - focus on the ability to regression test working software quickly
 *      - eleviate the need to wait for big changes in order to test
 *      - simple so that it does not require huge learning curve
 *      - able to be used to get a rapid answer to "does it work"
 *      - do not require special debugging code that can alter the program
 *      - enable a nightly build that includes regression testing
 *      - report all failures, not just the first and stop
 *
 *   ALTERNATIVES and CONSEQUENCES (ac)
 *
 *      1) test the latest changes by hand...
 *         - focus on what is current, rather than retesting everytime
 *         - does not see what broke that is not obvious
 *         - requires special setup everytime a test needs to happen
 *         - requires direct programmer involvement everytime
 *
 *      2) create manual testing scripts...
 *         - gives the programmer/tester something to follow
 *         - greater assurance that ad-hoc testing
 *         - still requires a great deal of human involvement
 *         - requires that a manual document must be updated
 *
 *      3) custom scripted testing...
 *         - can be run quicker and does not need as much handling
 *         - requires that the programmer create the testing logic
 *         - can lead to difficult to maintain and varied testing scripts
 *         - time consuming and difficult to automate consistently
 *
 *      4) packaged testing software (like nUNIT)...
 *         - already has testing in mind and does advanced functions
 *         - supports the basic testing languages pretty well (but complex)
 *         - but, takes away the ability to learn by creating
 *         - will only do what it will to (not changeable)
 *
 *      5) personal testing framework
 *         - takes longer to build and requires maintenance
 *         - allows me to learn even more advanced programming by building
 *         - will do anything i desire
 *         - will work with me to develop "testable" software methods
 *
 *      6) personal testing metaprogram/language
 *         - all the pros and cons of the personal testing framework, plus...
 *         - uses high level, consistent script rather than code
 *         - compiles into C code, not some funky other thing
 *         - will allow integration to VIM/refactoring though ascii script
 *
 *   JUDGEMENT
 *
 *      only the ignorant, cocky, or careless would pass up a technique that
 *      can save so many preventable mistakes.  As long as automated unit testing
 *      is used wisely to supplement other testing types, it is a godsend
 *
 *      while i could do nothing, our applications will become too critical to
 *      risk not regression testing and taking every possible chance to debug --
 *      the key is to prepare now for when you won't have time so you always
 *      create excellent changes
 *
 *      this is not a strategic element, or even exciting, so why code it
 *      more than once or take the chance on leaving things out of
 *      later versions
 *
 *      finally, without incremental unit testing you can not refactor with any
 *      confidence and therefore maintaining code becomes more of a hit-and-miss
 *      which is completely unacceptable
 *
 *   BOTTOM LINE : test like your life depends on it, because someday it will
 *
 */
/*===[[ DECISION -- USE DIRECT ACCESS OR ACCESSORS ]]==========================#

 *   PROBLEM (pr)
 *      no mattter what is done, a unit test typicall requires monitoring more
 *      than just return codes from functions -- things such as shared data
 *      structures, state information, global variables, etc.  how should the
 *      unit test gain access to this information while maximizing flexibility
 *      for refactoring and enhancement, for instance, changing data structure
 *      names and contents.
 *
 *   OBJECTIVES (o)
 *      - do not allow the unit test to access internal variables by name
 *      - do not require the unit test to be too tightly coupled to the code
 *
 *   ALTERNATIVES and CONSEQUENCES (ac)
 *
 *      1) use a traditional testing harness...
 *         - allows access to all data and variables
 *         - but, is code so you must name anything you touch
 *         - also requires direct access to all shared variables and state
 *         - this really slows down refactoring
 *
 *      2) custom "accessor" for unit testing...
 *         - use a custom accessor function to provide internal access
 *         - acts as a gatekeeper to maintain privacy and consistent interface
 *         - keeys the new code to one function rather than many accessors
 *         - deeper access than typical accessor functions
 *
 *   JUDGEMENT
 *
 *      since i am not burdened by backward compatibility or needs, i choose the
 *      accessor model so that i can quickly change the code, make a few changes
 *      to the accessor itself and no changes to the unit test code.  faster,
 *      cleaner, clearer
 *
 *
 */
/*===[[ DESIGN IDEALS ]]=======================================================#

 *   ALWAYS> endeavour to be direct, simple, brief, vigorous, and lucid ~ Fowler
 *
 *   SHARED DESIGN IDEALS (must, need, want, feel, like)...
 *      - (need) very loosely coupled to allow freedom to improve and change
 *      - (need) simple external interface to allow ease of use
 *      - (need) very defensive programming to give maximum maintainability
 *      - (need) bomb proof to reduce the failure probability to near-zero
 *      - (need) testable code to allow rapid debugging and refactoring
 *      - (want) easy to use to promote reuse
 *
 *   SPECIFIC DESIGN IDEALS (must, need, want, feel, like)
 *      - (need) few or no outside dependencies (allow broad applicability)
 *      - (need) keep dependencies down to yLOG and yVAR
 *      - (like) clean interface to allow summary to detailed reporting
 *      - (must) do not overlap external tools like less, vim, ...
 *      - (want) low configuration to keep it consistent
 *
 */
/*===[[ TERMINOLOGY ]]=========================================================#

 *   pass          : scripts that can be run in the same environment, sequence
 *   script        : logical group of related, sequential conditions
 *   condition     : specific situation/option to be tested
 *   step          : an individual action to verify a condition
 *
 */
/*===[[ BEST PRACTICES ]]======================================================#

 *   GOOD...
 *      - focus energy on external interfaces to code, user, kernel, files, ...
 *      - keep the interfaces predictable while allowing internal change
 *      - keep tests running rapidly so they will encourage frequent use
 *      - encourage refactoring by staying out of the details
 *      - use error types and lists to encourage defensive programming
 *      - add to the promotion and build cycle to act as a QA point
 *      - incementally build tests and don't allow them to stop momentum
 *      - enable forced failures to really hit programs from all sides
 *
 *   BAD...
 *      - do not test structure as that should migrate over time
 *      - do not just test design compliance which is not value add (but easy)
 *      - do not get into the internals which focuses on "how" to "outcome"
 *
 */
/*===[[ PSEUDO-CODE ]]=========================================================#

 *   GENERAL FLOW
 *      - read the next test
 *      - log a test as planned
 *      - clear the test variables
 *      - run the correct function
 *      - compare actual and expected results properly
 *      - log the test outcome
 *      - produce detailed results
 *
 */
/*===[[ END HDOC ]]===========================================================*/


/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YUNIT_hguard
#define YUNIT_hguard loaded

#include <ySTR_solo.h>


#define     YUNIT_CONVERT   'C'
#define     YUNIT_BUILD     'B'
#define     YUNIT_RUNTIME   'R'

#define     YUNIT_ETERM     'y'
#define     YUNIT_CONSOLE   '-'

#define     YUNIT_LIST       0
#define     YUNIT_RUN        1

#define     YUNIT_ALL        0

#define     YUNIT_MUTE       0
#define     YUNIT_SUMM       1
#define     YUNIT_SCRP       2
#define     YUNIT_COND       3
#define     YUNIT_STEP       4
#define     YUNIT_FULL       5
#define     YUNIT_MAXX       6

#define     YUNIT_SUCC       0
#define     YUNIT_FAIL       1
#define     YUNIT_WARN       2
#define     YUNIT_FSUCC      3
#define     YUNIT_FFAIL      4
#define     YUNIT_VOID       5
#define     YUNIT_NORUN     -1



#define     YUNIT_IS_FULL   'F'
#define     YUNIT_IS_FULLS  "F"
#define     YUNIT_IS_SUMMS  "FUMPGCS-"

#define     YUNIT_IS_UNIT   'U'
#define     YUNIT_IS_MAST   'M'
#define     YUNIT_IS_UNITS  "UM"

#define     YUNIT_IS_SCRP   'P'
#define     YUNIT_IS_GLOB   'G'
#define     YUNIT_IS_CONF   'C'
#define     YUNIT_IS_SHAR   'S'
#define     YUNIT_IS_SECT   '-'
#define     YUNIT_IS_TOPPS  "PGCS-"

#define     YUNIT_IS_COND   'c'
#define     YUNIT_IS_DITT   'd'
#define     YUNIT_IS_REUS   'r'
#define     YUNIT_IS_GREU   'g'
#define     YUNIT_IS_MIDDS  "cdrg"

#define     YUNIT_IS_EXEC   'x'
#define     YUNIT_IS_VARS   'a'
#define     YUNIT_IS_VOID   'v'
#define     YUNIT_IS_DEXE   'X'
#define     YUNIT_IS_DVOI   'V'
#define     YUNIT_IS_BOTTS  "xavXV"

/*===[[ RETURN VALUE HOLDERS ]]===============================================*/
#define     UNITTEST     yes


/*===[[ RETURN VALUE HOLDERS ]]===============================================*/

extern void     *yUNIT_p_rc;
extern long      yUNIT_i_rc;
extern double    yUNIT_r_rc;
extern char     *yUNIT_s_rc;

typedef unsigned char   uchar;
typedef const char      cchar;
typedef const void      cvoid;
typedef long long       llong;


/*===[[ FUNCTION PROTOTYPES ]]================================================*/
char*       yUNIT_version           (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_unique            (int a_nscrp, int a_ncond, int a_nstep, int a_uscrp, int a_ucond, int a_ustep);
char        yUNIT_level             (char a_level, char a_quiet);
char        yUNIT_eterm             (char a_eterm, char a_quiet);
char        yUNIT_unit              (char a_name [LEN_TITLE], char a_level, char a_eterm, char a_exec);
char        yUNIT_tinu              (char a_exec);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_scrp              (int a_line, int a_seqn, char a_stage [LEN_SHORT], char a_desc [LEN_LONG], char a_dur [LEN_SHORT], char a_terse [LEN_LABEL], char a_focu [LEN_HUND]);
char        yUNIT_prcs              (char a_exec);
char        yUNIT_sect              (char a_desc [LEN_LONG]);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_cond              (int a_line, int a_seqn, char a_dittoing, char a_ditto, char a_dtarget, char a_share, char a_desc [LEN_LONG]);
char        yUNIT_dnoc              (char a_exec);
char        yUNIT_group             (char a_desc [LEN_LONG]);



/*===[[ yUNIT_share.c ]]======================================================*/
/*········· ´······················ ´·········································*/
/*---(local share)----------*/
char        yUNIT_shar              (char a_share, char a_select, char a_desc [LEN_LONG]);
char        yUNIT_rahs              (char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep);
/*---(global share)---------*/
char        yUNIT_glob              (char a_share, char a_select, char a_desc [LEN_LONG]);
char        yUNIT_bolg              (char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep);
/*---(config share)---------*/
char        yUNIT_conf              (char a_share, char a_select, char a_desc [LEN_LONG]);
char        yUNIT_fnoc              (char a_share, char a_select, int a_econd, int a_estep, int a_acond, int a_astep);
/*---(done)-----------------*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_mode_reset        (void);
char        yUNIT_mode              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_exec, char a_dittoing, char a_share);
char        yUNIT_local             (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_code [LEN_RECD], char a_exec, char a_dittoing, char a_share);
char        yUNIT_code              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_code [LEN_RECD], char a_exec, char a_dittoing, char a_share);
char        yUNIT_load              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_recd [LEN_RECD], char a_exec, char a_dittoing, char a_share);
char        yUNIT_file              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_recd [LEN_RECD], char a_exec, char a_dittoing, char a_share);
char        yUNIT_append            (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_recd [LEN_RECD], char a_exec, char a_dittoing, char a_share);
char        yUNIT_system            (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_disp [LEN_RECD], char a_cmd [LEN_RECD], char a_exec, char a_dittoing, char a_share);
char*       yUNIT_read              (cchar *a_name, int n, int *c);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_void              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_exec, char a_dittoing, char a_share);
char        yUNIT_char              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], uchar a_expe, uchar a_actu, char a_exec, char a_dittoing, char a_share);
char        yUNIT_int               (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], llong a_expe, llong a_actu, char a_exec, char a_dittoing, char a_share);
char        yUNIT_real              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], double a_expe, double a_actu, char a_exec, char a_dittoing, char a_share);
char        yUNIT_point             (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], void *a_expe, void *a_actu, char a_exec, char a_dittoing, char a_share);
char        yUNIT_string            (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_exec, char a_dittoing, char a_share);
char        yUNIT_wrap              (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_exec, char a_dittoing, char a_share);
char        yUNIT_round             (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_exec, char a_dittoing, char a_share);
char        yUNIT_unknown           (int a_line, int a_seqn, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_exec, char a_dittoing, char a_share);


/*345678901 12345678901 12345678901 12345678901 12345678901 12345678901 123456*/
char        yUNIT_user_del          (cchar *a_name);
char        yUNIT_user_add          (cchar *a_name, cchar *a_pass, cchar *a_shell);


/*345678901 12345678901 12345678901 12345678901 12345678901 12345678901 123456*/
char        yUNIT_usage             (void);
char        yUNIT_args              (int a_argc, char *a_argv[]);
char        yUNIT_reset_rc          (void);
char        yUNIT_run_scrp          (char a_scrp);


/*345678901 12345678901 12345678901 12345678901 12345678901 12345678901 123456*/
char*       yUNIT_teststring        (char n);
float       yUNIT_testreal          (float n);
int         yUNIT_testint           (int n);
char        yUNIT_testchar          (char n);
int*        yUNIT_testptr           (void);


/*345678901 12345678901 12345678901 12345678901 12345678901 12345678901 123456*/
char        yUNIT_wave_beg          (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_desc [LEN_LONG], char a_terse [LEN_LABEL], char a_wave, char a_stage, char a_rate, char a_expe [LEN_SHORT]);
char        yUNIT_wave_end          (void *f);
char        yUNIT_wave_act          (void *f, char a_nunit, char a_nscrp, short a_ncond, short a_nstep, char a_result, short a_npass, short a_nfail, short a_nbadd, short a_nvoid, short a_actual);

char        yUNIT_stats_purge       (char a_usage, int *r_cunit, int *r_nscrp, int *r_ncond, int *r_nstep);

char        yUNIT_stats_full        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_major, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep);
char        yUNIT_stats_unit        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_major, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep);
char        yUNIT_stats_scrp        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_major, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep);
char        yUNIT_stats_cond        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_desc [LEN_LONG], char a_dittoing, char a_dtarget, char a_major, char a_share, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep);
char        yUNIT_stats_step        (char a_usage, void *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_TERSE], char a_desc [LEN_LONG], char a_dittoing, char a_dtarget, char a_major, char a_share, int *r_cunit, int *r_cscrp, int *r_ccond, int *r_cstep);

char        yUNIT_force_prog        (int a_scrp, int a_cond, int a_step);

char        yUNIT_printf            (char *a_format, ...);



typedef struct cyUNIT_COUNTS tyUNIT_COUNTS;
static struct cyUNIT_COUNTS {
   /*---(identifier)---------------------*/
   char        c_id;                        /* script, global, config, or shared identifier/sequence */
   char        c_type;                      /* specific type --  global, config, or shared           */
   int         c_line;                      /* location in file                                      */
   char        c_desc    [LEN_LONG];        /* description of purpose                                */
   /*---(unit)---------------------------*/
   int         c_unit;                      /* all units                                             */
   /*---(top)----------------------------*/
   int         c_topp;                      /* all count                                             */
   int         c_scrp;                      /* script count                                          */
   int         c_glob;                      /* global count                                          */
   int         c_shar;                      /* shared count                                          */
   /*---(middle)-------------------------*/
   int         c_midd;                      /* condition, ditto, reuse count                         */
   int         c_cond;                      /* condition count                                       */
   int         c_ditt;                      /* ditto count                                           */
   char        c_dittos    [LEN_LABEL];     /* dittos usage list                                     */
   int         c_lreu;                      /* local (shared) reuse count                            */
   char        c_lreuse    [LEN_HUND];      /* local reuse usage list                                */
   int         c_greu;                      /* global (global/config) reuse count                    */
   char        c_greuse    [LEN_HUND];      /* global reuse usage list                               */
   int         c_skipc;                     /* skipped conditions                                    */
   /*---(step)---------------------------*/
   int         c_step;                      /* all step count                                        */
   int         c_real;                      /* steps returning non-void                              */
   int         c_vars;                      /* local and global variables                            */
   int         c_void;                      /* steps returning void                                  */
   int         c_skips;                     /* skipped steps                                         */
   /*---(ditto)--------------------------*/
   int         c_dstep;                     /* dittoed all steps                                     */
   int         c_dreal;                     /* dittoed non-void steps                                */
   int         c_dvoid;                     /* dittoed void steps                                    */
   int         c_dskip;                     /* dittoed skipped steps                                 */
   /*---(usage)--------------------------*/
   char        c_called;                    /* number of times reused/called                         */
   /*---(done)---------------------------*/
};



/*===[[ yUNIT_reuse.c ]]======================================================*/
/*········· ´······················ ´·········································*/
char      yUNIT_reuse_type        (char a_abbr);
int       yUNIT_reuse_index       (char a_abbr);
char      yUNIT_reuse_clear       (char a_abbr);
char      yUNIT_reuse_purge       (char a_type);
char      yUNIT_reuse_data        (char a_abbr, char *r_type, char r_tdesc [LEN_TERSE], int *r_line, char r_desc [LEN_LONG], short *r_conds, short *r_steps, char *r_called);
char      yUNIT_reuse_set         (char a_abbr, int a_line, char a_desc [LEN_LONG]);
char      yUNIT_reuse_called      (char a_abbr);
char      yUNIT_reuse_save        (char a_abbr);
char      yUNIT_reuse_add         (char a_abbr);
char*     yUNIT_reuse_show        (char a_abbr);
char      yUNIT_reuse_parse       (char a_type, char a_recd [LEN_RECD]);
/*---(debugging)------------*/
char*     yUNIT_reuse_actuals     (void);
char*     yUNIT_reuse_used        (void);
char*     yUNIT_reuse_detail      (char a_abbr);
/*---(exim)-----------------*/
char      yUNIT_reuse_export      (void *a_file);
char      yUNIT_reuse_import      (void *a_file);
/*---(done)-----------------*/



#endif

/*===[[ END ]]================================================================*/
