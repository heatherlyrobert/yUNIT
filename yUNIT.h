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



/*===[[ VERSION ]]========================================*/
/* rapidly evolving version number to aid with visual change confirmation     */

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

#define     YUNIT_SUCC       0
#define     YUNIT_FAIL       1
#define     YUNIT_WARN       2
#define     YUNIT_FSUCC      3
#define     YUNIT_FFAIL      4
#define     YUNIT_VOID       5
#define     YUNIT_NORUN     -1


/*===[[ RETURN VALUE HOLDERS ]]===============================================*/
#define     UNITTEST     yes


/*===[[ RETURN VALUE HOLDERS ]]===============================================*/

extern void     *yUNIT_p_rc;
extern long      yUNIT_i_rc;
extern double    yUNIT_r_rc;
extern char     *yUNIT_s_rc;

typedef const char   cchar;
typedef const void   cvoid;


/*===[[ FUNCTION PROTOTYPES ]]================================================*/

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_unique            (int a_scrp, int a_cond, int a_step);
char        yUNIT_level             (cchar a_level, cchar a_quiet);
char        yUNIT_eterm             (cchar a_eterm, cchar a_quiet);
char        yUNIT_unit              (cchar *a_name, cchar a_level, cchar a_eterm, cchar a_exec);
char        yUNIT_tinu              (cchar a_exec);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_sect              (cchar *a_desc);
char        yUNIT_scrp              (int a_line, int a_seqn, cchar *a_stage, cchar *a_desc, cchar *a_dur, cchar *a_terse, cchar *a_focu);
char        yUNIT_prcs              (cchar a_exec);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_cond              (int a_line, int a_seqn, char a_share, cchar *a_desc);
char        yUNIT_group             (char *a_desc);
char        yUNIT_dnoc              (cchar a_exec);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_share             (char a_share, cchar *a_desc);
char        yUNIT_erahs             (char a_share);
char        yUNIT_global            (char a_share, cchar *a_desc);
char        yUNIT_labolg            (char a_share);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_mode_reset        (void);
char        yUNIT_mode              (int a_line, int a_seqn, cchar *a_desc, char a_exec);
char        yUNIT_local             (int a_line, int a_seqn, cchar *a_desc, cchar *a_code, char a_exec);
char        yUNIT_code              (int a_line, int a_seqn, cchar *a_desc, cchar *a_code, char a_exec);
char        yUNIT_load              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_recd, char a_exec);
char        yUNIT_file              (int a_line, int a_seqn, cchar *a_desc, cchar *a_recd, char a_exec);
char        yUNIT_append            (int a_line, int a_seqn, cchar *a_desc, cchar *a_recd, char a_exec);
char        yUNIT_system            (int a_line, int a_seqn, cchar *a_desc, cchar *a_disp, cchar *a_cmd, char a_exec);
char*       yUNIT_read              (cchar *a_name, int n, int *c);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yUNIT_void              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char a_exec);
char        yUNIT_int               (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, long long a_expe, long long a_actu, char a_exec);
char        yUNIT_real              (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, double a_expe, double a_actu, char a_exec);
char        yUNIT_point             (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, void *a_expe, void *a_actu, char a_exec);
char        yUNIT_string            (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu, char a_exec);
char        yUNIT_round             (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu, char a_exec);
char        yUNIT_unknown           (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test, char *a_expe, char *a_actu, char a_exec);
char        yUNIT__disp             (int a_line, int a_seqn, cchar *a_note, cchar *a_desc);
char        yUNIT__recd             (int a_line, int a_seqn, cchar *a_desc, cchar *a_meth, cchar *a_args, cchar *a_test);


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



#endif
/*===[[ END ]]================================================================*/
