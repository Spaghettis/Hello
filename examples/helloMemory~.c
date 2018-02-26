
/* < https://opensource.org/licenses/BSD-3-Clause > */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

#include "m_spaghettis.h"

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

/* Memory cached (for efficiency). */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

#define HELLO_BLOCKSIZE     64      /* Default size for the application. */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

static t_class *hello_class;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

typedef struct _hello {
    t_object    x_obj;
    t_float     x_f;
    int         x_size;
    t_sample    *x_cache;
    t_outlet    *x_outlet;
    } t_hello;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static void hello_allocate (t_hello *x, int n)
{
    if (x->x_size != n) {
    //
    if (x->x_size)  { post ("Free / %d", x->x_size); }
    
    if (x->x_cache) { PD_MEMORY_FREE (x->x_cache); }                    /* Free previous. */
    
    post ("Allocate / %d", n);
    
    x->x_size  = n;
    x->x_cache = (t_sample *)PD_MEMORY_GET (sizeof (t_sample) * n);     /* Allocate new. */
    //
    }
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static t_int *hello_perform (t_int *w)
{
    t_hello  *x   = (t_hello *)(w[1]);
    t_sample *in  = (t_sample *)(w[2]);
    t_sample *out = (t_sample *)(w[3]);
    int n = (int)(w[4]);
    
    t_sample *copy = x->x_cache;    /* Fetch the vector. */
    
    while (n--) {
    //
    t_sample f = *in;
    
    *out  = f;
    *copy = f;                      /* Just make a copy of the signal here. */
    
    in++; out++; copy++;
    //
    }
    
    return (w + 5);
}

static void hello_dsp (t_hello *x, t_signal **sp)
{
    int size = signal_getVectorSize (sp[0]);
    
    hello_allocate (x, size);   /* Note that the vector size might be changed in reblocked patch. */
    
    /* Pass a pointer to the structure as (first) argument. */
    
    dsp_add (hello_perform, 4, x, signal_getVector (sp[0]), signal_getVector (sp[1]), size);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static void *hello_new (void)
{
    t_hello *x  = (t_hello *)pd_new (hello_class);
    
    x->x_outlet = outlet_newSignal (cast_object (x));

    hello_allocate (x, HELLO_BLOCKSIZE);        /* Allocate the memory. */
    
    return x;
}

static void hello_free (t_hello *x)
{
    post ("Free / %d", x->x_size);
    
    PD_MEMORY_FREE (x->x_cache);                /* Free the memory. */
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

PD_STUB void helloMemory_tilde_setup (void)
{
    t_class *c = NULL;
    
    c = class_new (gensym ("helloMemory~"),
            (t_newmethod)hello_new,
            (t_method)hello_free,
            sizeof (t_hello),
            CLASS_BOX,
            A_NULL);
    
    CLASS_SIGNAL (c, t_hello, x_f);
    
    class_addDSP (c, (t_method)hello_dsp);
    
    hello_class = c;
}

PD_STUB void helloMemory_tilde_destroy (void)
{
    class_free (hello_class);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
