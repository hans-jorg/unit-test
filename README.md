Unit test routines for C
========================


# Motivation
It is yet another unit test for C. It is simple and the inline version does not, like many others, evaluate the arguments twice (one for test and another for printing). This is a problem when a function has side effects.

The macro version now evaluates parameters only once too. It uses the variables with block scope introduced by C99.


# Description

**Output goes to stderr!**

The implemented routines include:

* TESTINIT()
initializes counters.

* TESTMESSAGE(MSG)
print a message. Output can be suppressed by the use of TESTSILENT().

* TESTSILENT()
suppresses output of TESTMESSAGE.

* TESTVERBOSE()
enables output of TESTMESSAGE.

* TESTSUMMARY()
prints a summary including total number of tests and total number of fails.

* TESTINT(EXPECTED,OBTAINED)
evaluates both parameters and compare them. If not equal, prints an error message.

* TESTFLOAT(EXPECTED,OBTAINED)
evaluates both parameters and compare them. If not equal, prints an error message.

* TESTSTRING(EXPECTED,OBTAINED)
evaluates both parameters and compare them. If not equal, prints an error message.

* TESTPOINTER(EXPECTED,OBTAINED)
evaluates both parameters and compare them. If not equal, prints an error message.

* TESTBOOL(EXPECTED,OBTAINED)
evaluates both parameters and compare them. If not equal, prints an error message.

# Implementation

There are two version. One based on macros and other based on inline functions.
Both use global variables to count tests and fails.
Both use strcmp to compare strings. When using the macro version, a `#include <string.h>` must be inserted before use.

The macro version uses C99 variable definition inside blocks.


# Example

```C
    #include "unittest.h>


    int main() {


        TESTINIT();


        TESTINT(0,getvalue());
        ...



        TESTSUMMARY();

        return 0;
    }
```
