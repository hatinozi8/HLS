
#include "ap_int.h"


int my_func02(
	ap_uint<8> a,
	ap_uint<8> b,
	ap_uint<9> *x
)
{
#pragma HLS interface s_axilite port=a
#pragma HLS interface s_axilite port=b
#pragma HLS interface s_axilite port=x

#pragma HLS interface s_axilite port=return


	*x = a + b;

	return 1;
}

