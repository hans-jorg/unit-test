#ifndef UNITTEST_H
#define UNITTEST_H
/**
 *  @file   unittest.h
 *
 *  @brief  routines for unit test
 *
 *  @note   Test for strings uses strcmp. A include<string.h> is mandatory.
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


static unsigned TESTCOUNTER     = 0;
static unsigned TESTFAILS       = 0;
static unsigned TESTVERBOSEFLAG = 1;


static inline void  TESTSILENT(void) {

    TESTVERBOSEFLAG = 0;
}

static inline void  TESTVERBOSE(void) {

    TESTVERBOSEFLAG = 1;
}

static inline void  TESTINIT(void) {
    TESTCOUNTER = 0;
    TESTFAILS   = 0;
}

static inline void TESTINT(int exp, int obt) {

    TESTCOUNTER++;
    if( exp != obt ) {
        TESTFAILS++;
        fprintf(stderr,"Line %d File %s: Expected %d Got %d\n",
            __LINE__,
            __FILE__,
            exp,
            obt);
    }
}

static inline void TESTBOOL(int exp, int obt) {

    exp = !exp;     // TRUE != 0, but !TRUE = 0 and !FALSE = 1
    obt = !obt;
    TESTCOUNTER++;
    if( exp != obt ) {
        TESTFAILS++;
        fprintf(stderr,"Line %d File %s: Expected %d Got %d\n",
            __LINE__,
            __FILE__,
            !exp,
            !obt);
    }
}

static inline void TESTFLOAT(double exp, double obt) {

    TESTCOUNTER++;
    if( exp != obt ) {
        TESTFAILS++;
        fprintf(stderr,"Line %d File %s: Expected %g Got %g\n",
            __LINE__,
            __FILE__,
            exp,
            obt);
    }
}

static inline void TESTSTRING(char *exp, char *obt) {

    TESTCOUNTER++;
    if( strcmp(exp,obt) == 0 ) {
        TESTFAILS++;
        fprintf(stderr,"Line %d File %s: Expected %s Got %s\n",
            __LINE__,
            __FILE__,
            exp,
            obt);
    }
}

static inline void  TESTPOINTER(void *exp, void *obt) {

    TESTCOUNTER++;
    if( exp != obt ) {
        TESTFAILS++;
        fprintf(stderr,"Line %d File %s: Expected %p Got %p\n",
            __LINE__,
            __FILE__,
            exp,
            obt);
    }

}


static inline void TESTMESSAGE(char *s) {

    if( TESTVERBOSEFLAG )
        fprintf(stderr,"%s\n",s);
}

static inline void TESTSUMMARY(void) {

    fprintf(stderr,"%d tests %d fails\n",
        TESTCOUNTER,
        TESTFAILS);
}

#endif
