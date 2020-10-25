#ifndef UNITTEST_H
#define UNITTEST_H
/**
 *  @file   unittest.h
 *
 *  @brief  routines for unit test
 *
 *
 *  @author Hans
 *  @date   21/04/2019
 */

#include <stdio.h>
#include <string.h>

#define TESTPREFIX unit

#define TESTCONCAT(X,Y) X ## Y

#define TESTCOUNTER     TESTCONCAT(TESTPREFIX,testCOUNTER)
#define TESTFAILS       TESTCONCAT(TESTPREFIX,testFAILS)
#define TESTVERBOSEFLAG TESTCONCAT(TESTPREFIX,testVERBOSE)

/*  Hack!
 *  Enables use of MACRO in the then clause of an if-then-else without
 *  semicolon problem
 */
///@{

/// Begin
#define _B do {
/// End
#define _E } while(0)
///@}

static unsigned TESTCOUNTER     = 0;
static unsigned TESTFAILS       = 0;
static unsigned TESTVERBOSEFLAG = 1;


#define  TESTSILENT() _B TESTVERBOSEFLAG = 0; _E

#define  TESTVERBOSE() _B TESTVERBOSEFLAG = 1; _E

#define  TESTINIT(void) _B TESTCOUNTER = 0; TESTFAILS   = 0; _E

#define TESTINT(EXP,OBT) \
_B                                                                      \
    int exp = (EXP);                                                    \
    int obt = (OBT);                                                    \
    TESTCOUNTER++;                                                      \
    if( exp != obt ) {                                                  \
        TESTFAILS++;                                                    \
        fprintf(stderr,"Line %d File %s: Expected %d Got %d\n",         \
            __LINE__,                                                   \
            __FILE__,                                                   \
            exp,                                                        \
            obt);                                                       \
     }                                                                  \
_E


#define TESTBOOL(EXP,OBT) \
_B                                                                      \
    /* TRUE != 0, but !TRUE = 0 and !FALSE = 1*/                        \
    int exp = !!(EXP);                                                  \
    int obt = !!(OBT);                                                  \
    TESTCOUNTER++;                                                      \
    if( exp != obt ) {                                                  \
        TESTFAILS++;                                                    \
        fprintf(stderr,"Line %d File %s: Expected %d Got %d\n",         \
            __LINE__,                                                   \
            __FILE__,                                                   \
            exp,                                                        \
            obt;                                                        \
    }                                                                   \
_E


#define TESTFLOAT(EXP,OBT) \
_B                                                                      \
    double exp = (EXP);                                                 \
    double obt = (OBT);                                                 \
    TESTCOUNTER++;                                                      \
    if( exp != obt) ) {                                                 \
        TESTFAILS++;                                                    \
        fprintf(stderr,"Line %d File %s: Expected %g Got %g\n",         \
            __LINE__,                                                   \
            __FILE__,                                                   \
            exp,                                                        \
            obt);                                                       \
    }                                                                   \
_E

#define TESTSTRING(EXP,OBT) \
_B                                                                      \
    char *exp = (EXP);                                                  \
    char *obt = (OBT);                                                  \
    TESTCOUNTER++;                                                      \
    if( strcmp(exp,obt) == 0 ) {                                        \
        TESTFAILS++;                                                    \
        fprintf(stderr,"Line %d File %s: Expected %s Got %s\n",         \
            __LINE__,                                                   \
            __FILE__,                                                   \
            exp,                                                        \
            obt);                                                       \
    }                                                                   \
_E

#define  TESTPOINTER(EXP,OBT)                                           \
_B                                                                      \
    void *exp = (EXP);                                                  \
    void *obt = (OBT);                                                  \
    TESTCOUNTER++;                                                      \
    if( exp != obt ) {                                                  \
        TESTFAILS++;                                                    \
        fprintf(stderr,"Line %d File %s: Expected %p Got %p\n",         \
            __LINE__,                                                   \
            __FILE__,                                                   \
            exp,                                                        \
            obt);                                                       \
    }                                                                   \
_E


#define TESTMESSAGE(S) \
_B                                                                      \
    if( TESTVERBOSEFLAG )                                               \
        fprintf(stderr,"%s\n",(S));                                     \
_E

#define TESTSUMMARY(void) \
_B                                                                      \
    fprintf(stderr,"%d tests %d fails\n",                               \
        TESTCOUNTER,                                                    \
        TESTFAILS);                                                     \
_E

#endif

