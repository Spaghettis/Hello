
/* < https://opensource.org/licenses/BSD-3-Clause > */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

#include "m_spaghettis.h"

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

/* Click me. */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

typedef struct _hello {
    t_object    x_obj;              /* MUST be the first. */
    t_outlet    *x_outlet;
    } t_hello;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static t_class *hello_class;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

static void hello_click (t_hello *x, t_symbol *s, int argc, t_atom *argv)
{
    // int coordinateX = (int)atom_getFloatAtIndex (0, argc, argv);
    // int coordinateY = (int)atom_getFloatAtIndex (1, argc, argv);
    // int shift       = (int)atom_getFloatAtIndex (2, argc, argv);
    // int ctrl        = (int)atom_getFloatAtIndex (3, argc, argv);
    // int alt         = (int)atom_getFloatAtIndex (4, argc, argv);
    // int dblclick    = (int)atom_getFloatAtIndex (5, argc, argv);
    // int clicked     = (int)atom_getFloatAtIndex (6, argc, argv);
    
    char *t = atom_atomsToString (argc, argv);
    
    post ("Click: %s", t);
    
    PD_MEMORY_FREE (t);             /* Release the memory allocated for the string. */

    outlet_bang (x->x_outlet);
}

/* Called right after that the patch that contains the object is instantiated. */
/* Note that it can called later by user with a message. */

static void hello_loadbang (t_hello *x)
{
    post ("Click me!");
}

/* Called when the patch that contains the object will be closed. */
/* Note that it can called before by user with a message. */

static void hello_closebang (t_hello *x)
{
    post ("Goodbye!");
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static void *hello_new (void)
{
    t_hello *x = (t_hello *)pd_new (hello_class);
    
    x->x_outlet = outlet_newBang (cast_object (x));
    
    return x;
}

static void hello_free (t_hello *x)
{

}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

PD_STUB void helloClick_setup (t_symbol *s)
{
    t_class *c = NULL;
    
    c = class_new (gensym ("helloClick"),
            (t_newmethod)hello_new,
            (t_method)hello_free,
            sizeof (t_hello),
            CLASS_BOX | CLASS_NOINLET,
            A_NULL);
    
    class_addClick (c, (t_method)hello_click);              /* Called while clicking on the object. */
    class_addLoadbang (c, (t_method)hello_loadbang);        /* Called at load. */
    class_addClosebang (c, (t_method)hello_closebang);      /* Called at close. */

    hello_class = c;
}

PD_STUB void helloClick_destroy (void)
{
    class_free (hello_class);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
