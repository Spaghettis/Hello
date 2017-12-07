
/* Copyright (c) 2017 Nicolas Danet. */

/* < https://opensource.org/licenses/BSD-3-Clause > */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

#include "m_spaghettis.h"

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

/* Hello world! */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

typedef struct _hello {
    t_object x_obj;                             /* MUST be the first. */
    } t_hello;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static t_class *hello_class;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

static void hello_bang (t_hello *x)
{
    post ("Hello world!");
}

static void *hello_new (void)
{
    return pd_new (hello_class);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

PD_STUB void hello_setup (t_symbol *s)          /* MUST be the name of the file with _setup appended. */
{
    t_class *c = NULL;
    
    /* MUST contains (at least) a class with the file name. */
    
    c = class_new (gensym ("hello"),
            (t_newmethod)hello_new,
            NULL,
            sizeof (t_hello),
            CLASS_BOX,
            A_NULL);
    
    class_addBang (c, (t_method)hello_bang); 
    
    hello_class = c;
}

PD_STUB void hello_destroy (void)               /* MUST be the name of the file with _destroy appended. */
{
    class_free (hello_class);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
