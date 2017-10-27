#include "ap_int.h"
#include "my_func02.h"

int main(int argc, char* argv[])
{
	

	ap_uint<8> in1;
	ap_uint<8> in2;
	ap_uint<9> res;


	if( argc == 2 ){
		in1 = (ap_uint<8>)atoi(argv[1]);
		in2 = (ap_uint<8>)atoi(argv[2]);
	}else{
		in1 = 10;
		in2 = 5;
	}


	my_func02( in1, in2, &res);

	printf("in1(%d) + in2(%d) = %d \n", (int)in1, (int)in2, (int)res);

	return 0;
}
