
#include "ap_int.h"


void my_func01(
	ap_uint<8> *a,
	ap_uint<8> *b,
	ap_uint<9> *x
)
{
	*x = *a + *b;
}

