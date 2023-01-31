/**
	@file
	perlin
	giy - giy.hands@gmail.com
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "perlin_lib.h"

////////////////////////// object struct
typedef struct _perlin2D
{
	t_object					ob;			// the object itself (must be first)
    long m_in;
    void* m_proxy;
	void* m_outlet1;
	double m_x, m_y;
	double m_persistence;
	long m_octave, m_seed;
} t_perlin2D;

///////////////////////// function prototypes
//// standard set
void *perlin2D_new(t_symbol *s, long argc, t_atom *argv);
void perlin2D_free(t_perlin2D *x);
void perlin2D_assist(t_perlin2D *x, void *b, long m, long a, char *s);
void perlin2D_handle_int(t_perlin2D *x, long i);
void perlin2D_handle_float(t_perlin2D *x, double f);
void perlin2D_handle_list(t_perlin2D *x, t_symbol *s, long argc, t_atom *argv);

//////////////////////// global class pointer variable
void *perlin2D_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("perlin2D", (method)perlin2D_new, (method)perlin2D_free, (long)sizeof(t_perlin2D),
				  0L /* leave NULL!! */, A_GIMME, 0);

	/* you CAN'T call this from the patcher */
	class_addmethod(c, (method)perlin2D_assist,			"assist",		A_CANT, 0);
	class_addmethod(c, (method)perlin2D_handle_int,		"int",			A_LONG, 0);
	class_addmethod(c, (method)perlin2D_handle_float,	"float",		A_FLOAT, 0);
	class_addmethod(c, (method)perlin2D_handle_list,	"list",			A_GIMME, 0);

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	perlin2D_class = c;

	// post("I am the perlin2D object");
}

void perlin2D_assist(t_perlin2D *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void perlin2D_handle_int(t_perlin2D *x, long i) {

	double rslt;
	switch(proxy_getinlet((t_object*)x)) {
		case 2:
			// object_post((t_object*)x, "float received in inlet 0");
			x->m_octave = i;
			break;

		case 3:
			// object_post((t_object*)x, "float received in inlet 1");
			x->m_seed = i;
			break;

		default:
			break;
	}
}

void perlin2D_handle_float(t_perlin2D *x, double f) {

	double rslt;
	switch(proxy_getinlet((t_object*)x)) {
		case 1:
			x->m_persistence = f;
			break;

		default:
			break;
	}
}

void perlin2D_handle_list(t_perlin2D *x, t_symbol *s, long argc, t_atom *argv) {
	long i;
    t_atom *ap;
	double val1, val2, rslt;
 
    // post("message selector is %s",s->s_name);
    // post("there are %ld arguments",argc);

	if (argc == 1) {
		val1 = atom_getfloat(argv);
		rslt = pnoise1d(val1, x->m_persistence, x->m_octave, x->m_seed);
	} else if (argc == 2) {
		val1 = atom_getfloat(argv + 0);
		val2 = atom_getfloat(argv + 1);
		rslt = pnoise2d(val1, val2, x->m_persistence, x->m_octave, x->m_seed);
	}
	outlet_float(x->m_outlet1, rslt);
}

void perlin2D_free(t_perlin2D *x)
{
	;
}

void *perlin2D_new(t_symbol *s, long argc, t_atom *argv)
{
	t_perlin2D *x = NULL;
	long i;

	if ((x = (t_perlin2D *)object_alloc(perlin2D_class))) {
		// object_post((t_object *)x, "a new %s object was instantiated: %p", s->s_name, x);
		// object_post((t_object *)x, "it has %ld arguments", argc);

		// inlets
		x->m_proxy = proxy_new((t_object*)x, 3, &x->m_in);
		x->m_proxy = proxy_new((t_object*)x, 2, &x->m_in);
		x->m_proxy = proxy_new((t_object*)x, 1, &x->m_in);

		// outlets
		x->m_outlet1 = outlet_new((t_object*)x, NULL);

		// init values
		x->m_persistence = 0.7;
		x->m_octave = 5;
		x->m_seed = 12124;

		for (i = 0; i < argc; i++) {
			if ((argv + i)->a_type == A_LONG) {
				long v = atom_getlong(argv+i);
				// object_post((t_object *)x, "arg %ld: long (%ld)", i, v);
				if (i == 1){
					x->m_octave = v;
					object_post((t_object *)x, "octave is set : %ld", x->m_octave);
				} else if (i == 2) {
					x->m_seed = v;
					object_post((t_object *)x, "seed is set : %ld", x->m_seed);
				} 
			} else if ((argv + i)->a_type == A_FLOAT) {
				double v = atom_getfloat(argv+i);
				// object_post((t_object *)x, "arg %ld: float (%f)", i, v);
				if (i == 0){
					x->m_persistence = v;
					object_post((t_object *)x, "persistence is set : %f", x->m_persistence);
				}
			} else if ((argv + i)->a_type == A_SYM) {
				object_post((t_object *)x, "arg %ld: symbol (%s)", i, atom_getsym(argv+i)->s_name);
			} else {
				object_error((t_object *)x, "forbidden argument");
			}
		}
	}
	return (x);
}
