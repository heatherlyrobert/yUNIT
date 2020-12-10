


/*===[[ 25 ONE_LINERS ]]======================================================*/
/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "st (software testing)"
#define     P_SUBJECT   "automated unit testing"
#define     P_PURPOSE   "provide consistent automated unit testing framework"

#define     P_NAMESAKE  "daktyloi-aeonius (forefinger)"
#define     P_HERITAGE  "idaeoan daktyls numbered five, the original metalsimths"
#define     P_IMAGERY   "rustic, titan spirit-men who protected the infant zeus"
#define     P_REASON    "daktyloi are the original metal smiths and forgers of tools"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "libyUNIT.so"
#define     P_FULLPATH  "/usr/local/lib64/libyUNIT.so"
#define     P_SUFFIX    "n/a"
#define     P_CONTENT   "n/a"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "yLOG,yURG,yVAR,ySTR"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2008-08"

#define     P_VERMAJOR  "2.--, upgraded c version (from bash)"
#define     P_VERMINOR  "2.1-, improve and expand"
#define     P_VERNUM    "2.1e"
#define     P_VERTXT    "break apart into separate source files for ease of maintenance"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"


/*
 * the five daktyloi
 * herakles      thumb
 * aeonius       forefinger
 * epimedes      middle finger
 * iasus         ring finger
 * acesidas      pinky
 */


/*===[[ START ]]==============================================================*/
#include <stdio.h>        /* printf(), snprintf()                             */
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>       /* malloc(), free()                                 */
#include <fcntl.h>              /* clibc standard file control              */

/*> #include <curses.h>       /+ getch, ungetch                                   +/   <*/

#include <yVAR.h>
#include <yURG.h>
#include "yUNIT.h"



/*===[[ CONSTANTS ]]==========================================================*/
#define  DISP_SUMM     if (o->is_noisy == 1)
#define  DISP_SCRP     if (o->is_noisy >= 2)
#define  DISP_COND     if (o->is_noisy >= 3)
#define  DISP_STEP     if (o->is_noisy >= 4 || o->its_resu > 0)
#define  DISP_FULL     if (o->is_noisy >= 5 || o->its_resu > 0)
#define  DISP_SECT     if (o->is_noisy == 4)

#define  YUNIT_SUCC    0
#define  YUNIT_FAIL    1
#define  YUNIT_WARN    2



#define  LEN_NORM     100
#define  LEN_ARGS     200
#define  LEN_HEAD     300
#define  LEN_LINE     500
#define  LEN_RECD    1000

extern    FILE     *yUNIT_stdin;
#define   STDIN          "yUNIT.stdin"
char      yUNIT_systext [1000];

extern FILE     *yUNIT_stdin;
extern FILE     *yUNIT_out;
extern char     s_sect      [LEN_LINE];

/*===[[ TEST STRUCTURE ]]=====================================================*/
typedef struct cUNIT tUNIT;
struct cUNIT {
   /*---(identification)-----------*/
   char        its_name    [LEN_NORM];
   /*---(working vars)-------------*/
   int         its_line;
   int         its_seqn;
   char        its_refn    [LEN_NORM];
   char        its_desc    [LEN_NORM];
   char        its_meth    [LEN_NORM];
   char        its_args    [LEN_ARGS];
   char        its_test    [LEN_NORM];
   char        its_expe    [LEN_LINE];
   char        its_fixd    [LEN_LINE];
   char        its_actu    [LEN_LINE];
   int         its_resu;
   int         its_code;
   char        its_comm    [LEN_NORM];
   /*---(counters)-----------------*/
   int         its_cond_test;
   int         its_cond_pass;
   int         its_cond_fail;
   int         its_cond_badd;
   int         its_cond_void;
   int         its_scrp_test;
   int         its_scrp_pass;
   int         its_scrp_fail;
   int         its_scrp_badd;
   int         its_scrp_void;
   int         its_unit_test;
   int         its_unit_pass;
   int         its_unit_fail;
   int         its_unit_badd;
   int         its_unit_void;
   /*---(flags)--------------------*/
   int         is_forced_fail;
   int         is_noisy;
   char        is_eterm;
   void       *is_leak_begin;
   void       *is_leak_end;
};
