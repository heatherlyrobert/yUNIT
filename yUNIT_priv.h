/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YUNIT_priv_hguard
#define YUNIT_priv_hguard loaded



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
#define     P_VERMINOR  "2.3-, new level for unit testing in koios"
#define     P_VERNUM    "2.3i"
#define     P_VERTXT    "added remembering current dir to yUNIT_minscrp and yUNIT_minprcs"
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

/*> #include    <curses.h>       /+ getch, ungetch                                   +/   <*/
#include    <ncurses.h>       /* getch, ungetch                                   */

#include    <yVAR.h>
#include    <yCOLOR_solo.h>
#include    "yUNIT.h"


#define     TYPE_FULL        'Ô'
#define     TYPE_DUFF        '´'
#define     TYPE_LUFF        'Õ'

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
#define     TYPE_SHARED      '['
#define     TYPE_DERAHS      ']'
#define     TYPE_GLOBAL      '{'
#define     TYPE_LABOLG      '}'
#define     TYPE_CONFIG      '¸'
#define     TYPE_GIFNOC      '¹'

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
#define     IF_NOTFULL     if (myUNIT.level <= 4)



typedef struct tm        tTIME;



extern char        unit_answer [LEN_RECD];


extern    FILE     *yUNIT_stdin;
#define   STDIN          "yUNIT.stdin"
extern  char      yUNIT_systext [1000];

extern FILE     *yUNIT_stdin;
extern FILE     *yUNIT_out;

extern char  YUNIT_SHARES  [LEN_HUND];


extern char     s_prefix    [LEN_RECD];
extern char     s_print     [LEN_RECD];
extern char     s_suffix    [LEN_RECD];
extern char     s_sect      [LEN_RECD];

/*> #define      UNIT_SCRP      myUNIT.unit_scrp                                      <* 
 *> #define      UNIT_COND      myUNIT.unit_cond                                      <* 
 *> #define      UNIT_TEST      myUNIT.unit_test                                      <* 
 *> #define      UNIT_PASS      myUNIT.unit_pass                                      <* 
 *> #define      UNIT_FAIL      myUNIT.unit_fail                                      <* 
 *> #define      UNIT_BADD      myUNIT.unit_badd                                      <* 
 *> #define      UNIT_VOID      myUNIT.unit_void                                      <*/

/*> #define      SCRP_COND      myUNIT.scrp_cond                                      <* 
 *> #define      SCRP_TEST      myUNIT.scrp_test                                      <* 
 *> #define      SCRP_PASS      myUNIT.scrp_pass                                      <* 
 *> #define      SCRP_FAIL      myUNIT.scrp_fail                                      <* 
 *> #define      SCRP_BADD      myUNIT.scrp_badd                                      <* 
 *> #define      SCRP_VOID      myUNIT.scrp_void                                      <*/

/*> #define      COND_TEST      myUNIT.cond_test                                      <* 
 *> #define      COND_PASS      myUNIT.cond_pass                                      <* 
 *> #define      COND_FAIL      myUNIT.cond_fail                                      <* 
 *> #define      COND_BADD      myUNIT.cond_badd                                      <* 
 *> #define      COND_VOID      myUNIT.cond_void                                      <*/

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
   char        b_beg;                       /* open bracket                   */
   char        b_end;                       /* close bracked                  */
   char        b_elipsis   [LEN_TERSE];     /* elipsis                        */
   char        b_cond_dots [LEN_FULL];
   char        b_step_dots [LEN_FULL];
   char        b_num_dots  [LEN_FULL];
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
   char        modd        [LEN_RECD];
   /*---(flags)--------------------*/
   int         is_forced_fail;
   void       *is_leak_begin;
   void       *is_leak_end;
};
extern tUNIT   myUNIT;


#define          YUNIT_TERM      myUNIT.eterm
#define          YUNIT_PURE      myUNIT.pure
#define          YUNIT_MONO      myUNIT.mono
#define          YUNIT_FORCED    myUNIT.is_forced_fail

#define          YUNIT_BEG       myUNIT.b_beg
#define          YUNIT_END       myUNIT.b_end
#define          YUNIT_ELIPSIS   myUNIT.b_elipsis
#define          YUNIT_CDOTS     myUNIT.b_cond_dots
#define          YUNIT_SDOTS     myUNIT.b_step_dots
#define          YUNIT_NDOTS     myUNIT.b_num_dots


extern tyUNIT_COUNTS  g_counts [LEN_HUND];


#define FULL_ID    0
#define FULL       g_counts [0]

#define UNIT_ID    1
#define UNIT       g_counts [1]

#define SCRP_ID    2
#define SCRP       g_counts [2]

#define COND_ID    3
#define COND       g_counts [3]



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yunit_open              (char a_name [LEN_TITLE]);
char        yunit_close             (void);
char        yunit_close_and_remove  (void);
char        yunit_cycle             (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/

char        yunit_unage             (char a_age [LEN_SHORT], int *r_secs);
char        yunit_wave              (char a_act, FILE *f, char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_desc [LEN_LONG], char a_terse [LEN_LABEL], char a_wave, char a_stage, char a_rate, char a_nunit, char a_nscrp, short a_ncond, short a_nstep, char a_expe [LEN_SHORT], char a_result, short a_npass, short a_nfail, short a_nbadd, short a_nvoid, short a_actual);





/*===[[ yUNIT_stats.c ]]======================================================*/
/*········· ´······················ ´·········································*/
/*---(support)-----------------------*/
char        yunit_stats_clear       (char a_type);
/*---(accum)-------------------------*/
char        yunit_stats_summary     (FILE *a_conv, char a_nscrp [LEN_TITLE], char a_type, char a_verb [LEN_LABEL], char a_major);
/*---(outcome)-----------------------*/
char*       yunit_stats_show        (char a_prefix [LEN_FULL], char n);
char*       yunit_full_show         (char a_prefix [LEN_FULL]);
char*       yunit_unit_show         (char a_prefix [LEN_FULL]);
char*       yunit_scrp_show         (char a_prefix [LEN_FULL]);
char*       yunit_cond_show         (char a_prefix [LEN_FULL]);
char        yunit_stats_reuse       (char a_type, char a_major, char b_full [LEN_HUND], char b_unit [LEN_HUND], char b_scrp [LEN_HUND]);
char        yunit_stats_of_scrp     (int *r_conds, int *r_steps);

/*> char*       yunit_stats_all         (char a_prefix [LEN_FULL]);                   <*/
/*> char*       yunit_stats__curr       (char a_prefix [LEN_FULL], char a_summ [LEN_DESC]);   <*/
/*> char*       yunit_stats_curr        (char a_prefix [LEN_FULL]);                   <*/



/*===[[ yUNIT_ditto.c ]]======================================================*/
/*········· ´······················ ´·········································*/
char        yunit_ditto_purge       (void);
char        yunit_ditto_stats       (char a_type, char a_ditto, char b_show [LEN_LABEL], char *r_dittoing);
char        yunit_ditto_step        (char a_usage, char a_type, char a_dittoing, char a_skip);
char        yunit_ditto_apply       (char a_usage, char a_type, char a_dtarget);
char*       yunit_ditto_show        (char n);
/*---(done)--------------------------*/



/*===[[ yUNIT_final.c ]]======================================================*/
/*········· ´······················ ´·········································*/
char*       yunit_final_step        (int a_seqn);
char        yunit_final_prep        (char a_type, char a_share, int a_line, int a_seqn, char a_prefix [LEN_TERSE], char a_desc [LEN_LONG], char a_max, char a_align, char a_gap, char *a_fill, char r_line [LEN_TERSE], char r_seqn [LEN_TERSE], char r_desc [LEN_LONG]);
char        yunit_final_color       (char a_mono, char a_type, char r_on [LEN_LABEL], char r_on2 [LEN_LABEL], char r_off [LEN_LABEL], char r_note [LEN_TERSE], char r_test [LEN_DESC]);
char*       yunit_final_footer      (char a_type);
/*---(done)--------------------------*/



/*===[[ yUNIT_actual.c ]]=====================================================*/
/*········· ´······················ ´·········································*/
/*---(stats)-------------------------*/
char        yunit_actual_clear      (char a_type);
char        yunit_actual_init       (void);
char        yunit_actual_accum      (char a_type, char a_resu, int a_rc);
char        yunit_actual_last       (char a_type, char *r_resu, int *r_rc);
/*---(report)------------------------*/
char*       yunit_actual_footer     (char a_type, char *r_unused);
char        yunit_actual_pcrs       (void *f, long a_dur);
int         yunit_actual_wrap       (char a_level);
/*---(unit-test)---------------------*/
char        yunit_force_prog        (int a_unit, int a_scrp, int a_cond, int a_test, int a_pass, int a_fail, int a_badd, int a_void);
char        yunit_force_unit        (int a_scrp, int a_cond, int a_test, int a_pass, int a_fail, int a_badd, int a_void);
char        yunit_force_scrp        (int a_cond, int a_test, int a_pass, int a_fail, int a_badd, int a_void);
char        yunit_force_cond        (int a_test, int a_pass, int a_fail, int a_badd, int a_void);
char        yunit_force_resu        (char a_resu, int a_rc);
char        yunit_actual_wave       (int *r_test, int *r_pass, int *r_fail, int *r_void, int *r_badd);
/*---(done)--------------------------*/

char        yunit_disp_show         (int a_line, int a_seqn, char a_share, char a_note [LEN_TERSE], char a_desc [LEN_LONG]);
char        yunit_disp__top         (char a_type, int a_line, int a_seqn, char a_desc [LEN_LONG], char a_share);
char        yunit_disp__mid         (char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_test [LEN_TERSE]);
char        yunit_disp__bot         (char a_source, char a_test [LEN_TERSE], char a_expe [LEN_RECD], char a_actu [LEN_RECD], char a_modd [LEN_RECD]);
char        yunit_disp_full         (char a_source, int a_line, int a_seqn, char a_share, char a_desc [LEN_LONG], char a_meth [LEN_HUND], char a_args [LEN_FULL], char a_expe [LEN_RECD], char a_test [LEN_TERSE], char a_actu [LEN_RECD], char a_modd [LEN_RECD]);
char        yunit_disp_single       (char a_type, int a_line, int a_seqn, char a_share, char a_desc [LEN_LONG]);
char        yunit_disp_double       (char a_type, int a_line, int a_seqn, char a_share, char a_desc [LEN_LONG], char a_label [LEN_TERSE], char a_detail [LEN_RECD]);


char        yunit_int_sizing        (llong a_number, char *r_sign, char *r_sig, char *r_exp, char *r_digits);
char        yunit_int_show          (llong a_expe, llong a_actu, char r_expe [LEN_RECD], char r_actu [LEN_RECD]);
char        yunit_real_sizing       (double a_number, char *r_sign, char *r_sig, char *r_exp, char *r_places, char *r_digits, char *r_fracts);
char        yunit_real_show         (double a_expe, double a_actu, char r_expe [LEN_HUND], char r_actu [LEN_HUND]);

char        yunit_cond_type         (char a_dittoing, char a_ditto, char a_dtarget, char a_share, char r_label [LEN_TERSE], char r_note [LEN_TERSE]);


char        yunit_reuse_clear       (char n);



#endif
