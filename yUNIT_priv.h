


/*===[[ 27 ONE_LINERS ]]======================================================*/

/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "st (software testing)"
#define     P_SUBJECT   "automated unit testing"
#define     P_PURPOSE   "provide consistent automated unit testing framework"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "daktyloi-aeonius (forefinger)"
#define     P_PRONOUNCE "dahk·tee·loi ay·ohn·ee·uhs"
#define     P_HERITAGE  "idaeoan daktyls numbered five, the original metalsmiths"
#define     P_BRIEFLY   "the little metalsmiths"
#define     P_IMAGERY   "rustic, titan spirit-men who protected the infant zeus"
#define     P_REASON    "daktyloi are the original metal smiths and forgers of tools"
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_HOMEDIR   "/home/system/yUNIT.unit_testing_library"
#define     P_BASENAME  "libyUNIT.so"
#define     P_FULLPATH  "/usr/local/lib64/libyUNIT.so"
#define     P_SUFFIX    "urun"
#define     P_CONTENT   "unit test results"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "yLOG,yURG,yVAR,ySTR"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2008-08"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "2.--, upgraded c version (from bash)"
#define     P_VERMINOR  "2.2-, tighten and harden"
#define     P_VERNUM    "2.2k"
#define     P_VERTXT    "added yUNIT_version to aide debugging in other application"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

/*
 * the five daktyloi
 * herakles      thumb
 * aeonius       forefinger
 * epimedes      middle finger
 * iasus         ring finger
 * acesidas      pinky
 */


/*===[[ START ]]==============================================================*/
#include    <stdio.h>        /* printf(), snprintf()                             */
#include    <string.h>
#include    <stdlib.h>
#include    <time.h>
#include    <memory.h>       /* malloc(), free()                                 */
#include    <fcntl.h>              /* clibc standard file control              */
#include    <stdarg.h>              /* CLIBC   variable argument handling     */
#include    <errno.h>               /* CLIBC   standard library error codes   */
#include    <error.h>               /* CLIBC   standard library error codes   */

/*> #include <curses.h>       /+ getch, ungetch                                   +/   <*/

#include    <yVAR.h>
#include    <yURG.h>
#include    <ySTR_solo.h>
#include    <yURG_solo.h>
#include    "yUNIT.h"




#define     TYPE_UNIT        'U'
#define     TYPE_TINU        'u'
#define     TYPE_DINU        '1'

#define     TYPE_SCRP        'S'
#define     TYPE_SECT        'E'
#define     TYPE_PRCS        'P'
#define     TYPE_DRCS        '2'

#define     TYPE_COND        'C'
#define     TYPE_CCND        '>'
#define     TYPE_DOND        '<'
#define     TYPE_SOND        '&'
#define     TYPE_GOND        'g'
#define     TYPE_GROUP       'G'
#define     TYPE_DNOC        'D'
#define     TYPE_DNOD        '3'
#define     TYPE_SHARE       '['
#define     TYPE_ERAHS       ']'
#define     TYPE_GLOBAL      '{'
#define     TYPE_LABOLG      '}'

#define     TYPE_STEP        '+'
#define     TYPE_DISP        'd'
#define     TYPE_MODE        'm'
#define     TYPE_LOAD        'l'
#define     TYPE_CODE        'c'
#define     TYPE_LOCAL       'L'
#define     TYPE_SYSTEM      's'
#define     TYPE_FILE        'f'
#define     TYPE_APPEND      'a'


/*===[[ CONSTANTS ]]==========================================================*/
#define     IF_SUMM        if (myUNIT.level >= 1)
#define     IF_SCRP        if (myUNIT.level >= 2)
#define     IF_COND        if (myUNIT.level >= 3)
#define     IF_STEP        if (myUNIT.level >= 4)
#define     IF_FULL        if (myUNIT.level >= 5)


typedef struct tm        tTIME;



extern char        unit_answer [LEN_RECD];


extern    FILE     *yUNIT_stdin;
#define   STDIN          "yUNIT.stdin"
extern  char      yUNIT_systext [1000];

extern FILE     *yUNIT_stdin;
extern FILE     *yUNIT_out;



extern char     s_prefix    [LEN_RECD];
extern char     s_print     [LEN_RECD];
extern char     s_suffix    [LEN_RECD];
extern char     s_sect      [LEN_RECD];

#define      UNIT_SCRP      myUNIT.unit_scrp
#define      UNIT_COND      myUNIT.unit_cond
#define      UNIT_TEST      myUNIT.unit_test
#define      UNIT_PASS      myUNIT.unit_pass
#define      UNIT_FAIL      myUNIT.unit_fail
#define      UNIT_BADD      myUNIT.unit_badd
#define      UNIT_VOID      myUNIT.unit_void

#define      SCRP_COND      myUNIT.scrp_cond
#define      SCRP_TEST      myUNIT.scrp_test
#define      SCRP_PASS      myUNIT.scrp_pass
#define      SCRP_FAIL      myUNIT.scrp_fail
#define      SCRP_BADD      myUNIT.scrp_badd
#define      SCRP_VOID      myUNIT.scrp_void

#define      COND_TEST      myUNIT.cond_test
#define      COND_PASS      myUNIT.cond_pass
#define      COND_FAIL      myUNIT.cond_fail
#define      COND_BADD      myUNIT.cond_badd
#define      COND_VOID      myUNIT.cond_void

/*===[[ TEST STRUCTURE ]]=====================================================*/
typedef struct cUNIT tUNIT;
struct cUNIT {
   /*---(identification)-----------*/
   char        proj        [LEN_LABEL];
   char        unit        [LEN_TITLE];
   char        name        [LEN_HUND];
   char        level;
   char        eterm;
   char        mono;                        /* monochrome, 1 = no color       */
   char        pure;                        /* pure ascii, 1 = only 7bit      */
   int         nscrp;
   int         ncond;
   int         nstep;
   int         uscrp;
   int         ucond;
   int         ustep;
   /*---(working vars)-------------*/
   char        expe        [LEN_RECD];
   char        fixd        [LEN_RECD];
   char        actu        [LEN_RECD];
   /*---(counters)-----------------*/
   int         cond_test;
   int         cond_pass;
   int         cond_fail;
   int         cond_badd;
   int         cond_void;
   int         scrp_cond;
   int         scrp_test;
   int         scrp_pass;
   int         scrp_fail;
   int         scrp_badd;
   int         scrp_void;
   int         unit_scrp;
   int         unit_cond;
   int         unit_test;
   int         unit_pass;
   int         unit_fail;
   int         unit_badd;
   int         unit_void;
   /*---(flags)--------------------*/
   int         is_forced_fail;
   void       *is_leak_begin;
   void       *is_leak_end;
};
extern tUNIT   myUNIT;



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yunit_open              (cchar *a_name);
char        yunit_printf            (char *a_format, ...);
char        yunit_close             (void);
char        yunit_close_and_remove  (void);
char        yunit_cycle             (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char*       yunit_seqn              (int a_seqn);
char        yunit__recd_color       (char *a_test);
char        yunit_result            (int a_resu, int a_code);
char*       yunit_header            (char a_type, int a_line, int a_seqn, char *a_note, char *a_desc);

char        yunit_unage             (char a_age [LEN_SHORT], int *r_secs);
char        yunit_wave              (char a_act, FILE *f, char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_desc [LEN_LONG], char a_terse [LEN_LABEL], char a_wave, char a_stage, char a_nunit, char a_nscrp, short a_ncond, short a_nstep, char a_expe [LEN_SHORT], char a_result, short a_npass, short a_nfail, short a_nbadd, short a_nvoid, short a_actual);


