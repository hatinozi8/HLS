#include "my_func03.h"

int main(int argc, char* argv[])
{
	
	unsigned short i_h;
	unsigned short i_w;
	unsigned short o_h;
	unsigned short o_w;

	hls::stream< ap_axiu<8, 1, 1, 1> > in;
	hls::stream< ap_axiu<8, 1, 1, 1> > out;

	i_h = 40;
	i_w = 40;
	o_h = 20;
	o_w = 20;

	for(int h = 0; h < i_h ; h++){
		for(int w = 0; w < i_w ; w++){
			ap_axiu<8, 1, 1, 1> buf;
			buf.data = (ap_uint<8>)w;
			buf.user = (!w)&(!h);
			buf.last = (h == i_h-1)&&(w == i_w-1);
			buf.keep = 1;
			buf.strb = 1;
			buf.dest = 1;
			in.write(buf);
		}
	}



	my_func03( in, out,
			&i_h, &i_w,
			&o_h, &o_w
	);

	for(int h = 0; h < o_h ; h++){
		for(int w = 0; w < o_w ; w++){
			unsigned char data = (unsigned char)out.read().data;
			printf("(%d,%d) = %d\n", h, w, data);
		}
	}



	return 0;
}
