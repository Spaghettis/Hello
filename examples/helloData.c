
/* < https://opensource.org/licenses/BSD-3-Clause > */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

#include "m_spaghettis.h"

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

/* Save data with patch. */

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

typedef struct _hello {
    t_object    x_obj;          /* MUST be the first. */
    t_buffer    *x_buffer;
    t_outlet    *x_outlet;
    } t_hello;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static t_class *hello_class;

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static void hello_bang (t_hello *x)
{
    outlet_list (x->x_outlet, buffer_getSize (x->x_buffer), buffer_getAtoms (x->x_buffer));
}

static void hello_list (t_hello *x, t_symbol *s, int argc, t_atom *argv)
{
    buffer_clear (x->x_buffer); buffer_append (x->x_buffer, argc, argv);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

/* Function called when patch is saved. */

static t_error hello_data (t_gobj *z, t_buffer *b)
{
    t_hello *x = (t_hello *)z;

    if (buffer_getSize (x->x_buffer)) {
    //
    buffer_appendSymbol (b, gensym ("list"));
    buffer_appendBuffer (b, x->x_buffer);
    
    /* The message composed will be sent to the object just after instantiation at load. */
    /* For instance "list 1 2 3 4 5" in that case. */
    /* Note that interaction with other objects MUST be avoided. */
    /* Indeed at that point the patch might be not fully constructed. */
    
    return PD_ERROR_NONE;
    //
    }
    
    return PD_ERROR;    /* Return an error if you don't need serialization anymore. */
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

static void *hello_new (void)
{
    t_hello *x = (t_hello *)pd_new (hello_class);
    
    x->x_buffer = buffer_new();
    x->x_outlet = outlet_newList (cast_object (x));
    
    return x;
}

static void hello_free (t_hello *x)
{
    buffer_free (x->x_buffer);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// MARK: -

PD_STUB void helloData_setup (t_symbol *s)
{
    t_class *c = NULL;
    
    c = class_new (gensym ("helloData"),
            (t_newmethod)hello_new,
            (t_method)hello_free,
            sizeof (t_hello),
            CLASS_BOX,
            A_NULL);
    
    class_addBang (c, (t_method)hello_bang);
    class_addList (c, (t_method)hello_list);

    class_setDataFunction (c, hello_data);                  /* Register the data function. */
    
    hello_class = c;
}

PD_STUB void helloData_destroy (void)
{
    class_free (hello_class);
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
