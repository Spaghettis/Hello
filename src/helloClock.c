
/* < https://opensource.org/licenses/BSD-3-Clause > */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

#include "m_spaghettis.h"

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

/* Schedule a task in time. */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

typedef struct _hello {
    t_object    x_obj;
    t_outlet    *x_outlet;
    t_clock     *x_clock;
    } t_hello;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static t_class *hello_class;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

/* The task to perform (output a random number here). */

static void hello_task (t_hello *x)
{
    static int once = 0; static t_rand48 seed; if (!once) { PD_RAND48_INIT (seed); once = 1; }
    
    outlet_float (x->x_outlet, PD_RAND48_DOUBLE (seed));
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static void hello_bang (t_hello *x)
{
    /* Schedule the task. */
    
    clock_delay (x->x_clock, PD_SECONDS_TO_MILLISECONDS (1.0));
    
    /* Note that it is allowed to schedule the clock inside a DSP perform. */
    /* In fact, it IS the proper way for DSP to interact with control flow. */
    /* It's also the only way to manage communication from a custom thread. */
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static void *hello_new (void)
{
    t_hello *x  = (t_hello *)pd_new (hello_class);
    
    x->x_outlet = outlet_newFloat (cast_object (x));
    
    /* Register the clock with the task to attach. */
    
    x->x_clock = clock_new ((void *)x, (t_method)hello_task);
    
    return x;
}

static void hello_free (t_hello *x)
{
    clock_free (x->x_clock);    /* Unregister the clock. */
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

PD_STUB void helloClock_setup (t_symbol *s)
{
    t_class *c = NULL;
    
    c = class_new (gensym ("helloClock"),
            (t_newmethod)hello_new,
            (t_method)hello_free,
            sizeof (t_hello),
            CLASS_BOX,
            A_NULL);
    
    class_addBang (c, (t_method)hello_bang);

    hello_class = c;
}

PD_STUB void helloClock_destroy (void)
{
    class_free (hello_class);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
