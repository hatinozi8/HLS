

#include "stdio.h"
#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"


template< int MAX_HEIGHT, int MAX_WIDTH >
void pack_axiu( unsigned short height, unsigned short width,
	hls::stream< ap_uint<8> > &src,
	hls::stream< ap_axiu<8, 1, 1, 1> > &dst)
{
#pragma HLS interface ap_stable port=height
#pragma HLS interface ap_stable port=width

#pragma HLS dataflow
	H_LOOP:for( int h=0; h < height ; h++){
	#pragma HLS LOOP_TRIPCOUNT min=1 max=MAX_HEIGHT
	//#pragma HLS LOOP_FLATTEN off
		W_LOOP:for( int w=0; w < width ; w++){
	#pragma HLS LOOP_TRIPCOUNT min=1 max=MAX_WIDTH
	#pragma HLS PIPELINE II=1
			ap_axiu<8, 1, 1, 1> buf;
			buf.data = src.read();
			buf.user = (!h)&(!w);	// first data: 1 , other:0
			buf.last = ( h == height-1 && w == width-1 ); //last data: 1 , other:0
			buf.keep = 1;
			buf.strb = 1;
			buf.dest = 1;		
			dst.write( buf );
		}
	}

}


template< int MAX_HEIGHT, int MAX_WIDTH >
void unpack_axiu( unsigned short height, unsigned short width,
	hls::stream< ap_axiu<8, 1, 1, 1> > &src,
	hls::stream< ap_uint<8> > &dst)
{
#pragma HLS interface ap_stable port=height
#pragma HLS interface ap_stable port=width

#pragma HLS dataflow
	H_LOOP:for( int h=0; h < height ; h++){
	#pragma HLS LOOP_TRIPCOUNT min=1 max=MAX_HEIGHT
	//#pragma HLS LOOP_FLATTEN off
		W_LOOP:for( int w=0; w < width ; w++){
	#pragma HLS LOOP_TRIPCOUNT min=1 max=MAX_WIDTH
	#pragma HLS PIPELINE II=1
			ap_uint<8> buf;
			buf = src.read().data;
			
			dst.write( buf );
		}
	}

}

template< int MAX_HEIGHT, int MAX_WIDTH >
int my_dsp(
	unsigned short in_h, unsigned short in_w,
	unsigned short out_h, unsigned short out_w,
	hls::stream< ap_uint<8> > &data_i,
	hls::stream< ap_uint<8> > &data_o)
{
#pragma HLS interface ap_stable port=in_h
#pragma HLS interface ap_stable port=in_w
#pragma HLS interface ap_stable port=out_h
#pragma HLS interface ap_stable port=out_w

#pragma HLS dataflow

	H_LOOP:for( int h=0; h < in_h ; h++){
	#pragma HLS LOOP_TRIPCOUNT min=1 max=MAX_HEIGHT
	//#pragma HLS LOOP_FLATTEN off
		W_LOOP:for( int w=0; w < in_w ; w++){
	#pragma HLS LOOP_TRIPCOUNT min=1 max=MAX_WIDTH
	#pragma HLS PIPELINE II=1
			ap_uint<8> buf;
			buf = (data_i.read()) + 10;
			
			if( h < out_h && w < out_w ) data_o.write( buf );
		}
	}

}
	


int my_func03(
	hls::stream< ap_axiu< 8, 1, 1, 1> > &in_data,
	hls::stream< ap_axiu< 8, 1, 1, 1> > &out_data,
	unsigned short *in_h, unsigned short *in_w,
	unsigned short *out_h, unsigned short *out_w)
{

	
#pragma HLS interface s_axilite port=return
#pragma HLS interface s_axilite register port=in_h
#pragma HLS interface s_axilite register port=in_w
#pragma HLS interface s_axilite register port=out_h
#pragma HLS interface s_axilite register port=out_w

#pragma HLS interface axis port=in_data
#pragma HLS interface axis port=out_data

	hls::stream< ap_uint<8> > in_str;
#pragma HLS STREAM variable=in_str depth=1 dim=1
	hls::stream< ap_uint<8> > out_str;
#pragma HLS STREAM variable=out_str depth=2 dim=1


#pragma HLS dataflow

	unpack_axiu< 1080, 1920 >( *in_h, *in_w, in_data, in_str );

	my_dsp< 1080, 1920 >( *in_h, *in_w, *out_h, *out_w, in_str, out_str);

	pack_axiu< 1080, 1920 >( *out_h, *out_w, out_str, out_data );

	return 1;
}
