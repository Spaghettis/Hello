
/* < https://opensource.org/licenses/BSD-3-Clause > */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

#include "m_spaghettis.h"

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

// -- C++ spoken.

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

#include <memory>

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

using namespace std;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

class Jojo {

    public:
        Jojo()
        {
            post ("Jojo contructor...");
        }
    
        ~Jojo()
        {
            post ("Jojo destructor...");
        }
};

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

typedef struct _hello {

    public:
        _hello() : x_jojo (new Jojo())
        {
        }

    public:
        t_object          x_obj;            /* MUST be the first. */
        t_error           x_error;
        auto_ptr < Jojo > x_jojo;           /* You may use C++11 smart pointers instead. */

} t_hello;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

static t_class *hello_class;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static void hello_bang (t_hello *x)
{
    post ("C++ spoken!");   // --
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static void *hello_new (void)
{
    t_hello *x = NULL;

    if ((x = (t_hello *)pd_new (hello_class))) {
    //
    t_error err = (x->x_error = PD_ERROR_NONE);
    
    try {
        new (x) t_hello;                    /* Use placement new. */
    }
    
    catch (...) {
        err = (x->x_error = PD_ERROR);      /* Catch exceptions if any. */
    }
    
    if (!err) {
    
        /* Various allocations. */
        
    }
    
    if (err) {
        pd_free (cast_pd (x));
        x = NULL;
    }
    //
    }

    return x;
}

static void hello_free (t_hello *x)
{
    /* Various deallocations. */

    if (!x->x_error) { x->~t_hello(); }      /* Call the destructor only if object is fully constructed. */
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

PD_STUB void helloCPP_setup (t_symbol *s)
{
    t_class *c = NULL;
    
    c = class_new (gensym ("helloCPP"),
            (t_newmethod)hello_new,
            (t_method)hello_free,
            sizeof (t_hello),
            CLASS_BOX,
            A_NULL);
    
    class_addBang (c, (t_method)hello_bang);
    
    hello_class = c;
}

PD_STUB void helloCPP_destroy (void)
{
    class_free (hello_class);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
