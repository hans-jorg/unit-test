#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "unittest.h"

/**
 *  Default element is int
 */
#ifndef CBUFFER_ELEMENTTYPE
#define CBUFFER_ELEMENTTYPE int
#endif

/**
 *  Default is the use of pointers
 */
#if !defined(CBUFFER_USEINTEGERS) && !defined(CBUFFER_USEPOINTERS)
#define CBUFFER_USEPOINTERS
#endif

typedef struct cbuffer_s {
    CBUFFER_ELEMENTTYPE    *area;

#if defined(CBUFFER_USEINTEGERS)
    int                     front;
    int                     rear;
#elif defined(CBUFFER_USEPOINTERS)
    CBUFFER_ELEMENTTYPE    *front;
    CBUFFER_ELEMENTTYPE    *rear;
#endif
    int                     size;
    int                     capacity;
} *cbuffer;

static inline int cbuffer_capacity(cbuffer f) {
    return f->capacity;
}

static inline int cbuffer_size(cbuffer f) {
    return f->size;
}

static inline int cbuffer_empty(cbuffer f) {
    return f->size == 0;
}

static inline int cbuffer_full(cbuffer f) {
    return f->size == f->capacity;
}

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

/**
 *  @brief  Macro to adjust limits
 */
///@{
#if defined(CBUFFER_USEPOINTERS)
#define ADJUST_LIMITS(X,F) _B if( F->X >= F->area+F->capacity ) F->X = F->area; _E
#elif defined(CBUFFER_USEINDEXES)
#define ADJUST_LIMITS(X,F) _B if( F->X >= F->capacity ) F->X = 0; _E
#endif
///@}

/**
 *  @brief  creates a circular buffer of size n
 */
cbuffer
cbuffer_create(int n) {
cbuffer p;
CBUFFER_ELEMENTTYPE *q;

    p = malloc(sizeof(struct cbuffer_s));
    if( !p ) return NULL;
    q = malloc(n*sizeof(CBUFFER_ELEMENTTYPE));
    if( !q ) {
        free(p);
        return NULL;
    }
    p->area = q;
#ifdef CBUFFER_USEPOINTERS
    p->front = p->rear = q;
#elif defined(CBUFFER_USEINTEGERS)
    p->front = p->rear = 0;
#endif
    p->size = 0;
    p->capacity = n;
    return p;
}

/**
 *  @brief  destroys a circular buffer
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 */
void
cbuffer_destroy(cbuffer f) {
    assert(f);
    free(f->area);
    f->area = NULL;
    free(f);
}

/**
 *  @brief  inserts an element in a circular
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 *  @param  x: element to store in circular buffer
 */
int
cbuffer_insert(cbuffer f, CBUFFER_ELEMENTTYPE x) {

    assert(f);
    assert(f->area);

#ifdef CBUFFER_USEPOINTERS
    *(f->rear++) = x;
#elif defined(CBUFFER_USEINTEGERS)
    f->area[f->rear++] = x;
#endif
    ADJUST_LIMITS(rear,f);
    if( cbuffer_full(f) ) {
        f->front++;
        ADJUST_LIMITS(front,f);
/*
#ifdef CBUFFER_USEPOINTERS
        if( f->front >= f->area+f->capacity )
            f->front = f->area;
#elif defined(CBUFFER_USEINTEGERS)
        if( f->front >= f->capacity )
            f->front = 0;
#endif
*/
    } else {
        f->size++;
    }
    return 0;
}

/**
 *  @brief  removes an element from a circular buffer
 *
 *  @param  f: pointer to cbuffer_s structure created by cbuffer_create
 *  @param px: pointer to an area where the element will be stored
 *
 *  @return    -1 if buffer empty, 0 otherwise
 */
int
cbuffer_remove(cbuffer f, CBUFFER_ELEMENTTYPE *px) {

    assert(f);
    assert(f->area);

    if( cbuffer_empty(f) )
        return -1;

    f->size--;
#ifdef CBUFFER_USEPOINTERS
    *px = *(f->front++);
#elif defined(CBUFFER_USEINTEGERS)
    *px = f->area[f->front++];
#endif
    ADJUST_LIMITS(front,f);
    return 0;
}


/**
 *  @brief  test script
 */

///@{
int
main (int argc, char *argv[]) {
cbuffer f;
int i,e;
int rc;

    TESTINIT();

    TESTMESSAGE("Criando um buffer circular para 4 elementos");
    f = cbuffer_create(4);
    TESTINT(0,cbuffer_size(f));
    TESTINT(4,cbuffer_capacity(f));
    TESTINT(1,cbuffer_empty(f));
    TESTINT(0,cbuffer_full(f));

    TESTMESSAGE("Inserindo 10 elementos. Somente os ultimos 4 devem sobrar");
    for(i=0;i<10;i++) {
        rc = cbuffer_insert(f,i);
        TESTINT(0,rc);
    }

    TESTINT(4,cbuffer_size(f));
    TESTINT(4,cbuffer_capacity(f));
    TESTINT(0,cbuffer_empty(f));
    TESTINT(1,cbuffer_full(f));

    TESTMESSAGE("Removendo dois elementos");
    rc = cbuffer_remove(f,&i);
    TESTINT(0,rc);
    TESTINT(6,i);
    rc = cbuffer_remove(f,&i);
    TESTINT(0,rc);
    TESTINT(7,i);

    TESTMESSAGE("Buffer com dois elementos");
    TESTINT(2,cbuffer_size(f));
    TESTINT(4,cbuffer_capacity(f));
    TESTINT(0,cbuffer_empty(f));
    TESTINT(0,cbuffer_full(f));

    TESTMESSAGE("Inserindo mais 10");
    for(i=10;i<20;i++) {
        rc = cbuffer_insert(f,i);
        TESTINT(0,rc);
    }

    TESTMESSAGE("Buffer cheio");
    TESTINT(4,cbuffer_size(f));
    TESTINT(4,cbuffer_capacity(f));
    TESTINT(0,cbuffer_empty(f));
    TESTINT(1,cbuffer_full(f));

    TESTMESSAGE("Removendo tudo");
    e = 16;
    while( !cbuffer_empty(f) ) {
        rc = cbuffer_remove(f,&i);
        TESTINT(0,rc);
        TESTINT(i,e);
        e++;
    }

    TESTMESSAGE("Buffer vazio");
    TESTINT(0,cbuffer_size(f));
    TESTINT(4,cbuffer_capacity(f));
    TESTINT(1,cbuffer_empty(f));
    TESTINT(0,cbuffer_full(f));

    cbuffer_destroy(f);
    TESTSUMMARY();

    return 0;
}

