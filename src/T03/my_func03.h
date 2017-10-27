
#include "stdio.h"
#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"


int my_func03(
	hls::stream< ap_axiu< 8, 1, 1, 1> > &in_data,
	hls::stream< ap_axiu< 8, 1, 1, 1> > &out_data,
	unsigned short *in_h, unsigned short *in_w,
	unsigned short *out_h, unsigned short *out_w);

