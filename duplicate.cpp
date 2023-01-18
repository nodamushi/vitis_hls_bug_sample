#include <ap_int.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

using no_crash_stream = hls::stream<ap_int<32>>;
using crash_stream = hls::stream<hls::axis<ap_int<32>, 1, 1, 1>>;

#ifndef NOCRASH
using stream = crash_stream;
#else
using stream = no_crash_stream;
#endif

void Duplicate(stream& a, stream& b)
{
#pragma HLS pipeline
#pragma HLS INTERFACE axis port=a name=s_axis_a
#pragma HLS INTERFACE axis port=b name=s_axis_a
//                                ~~~~~~~~~~~~~
// * Note: Line 18 was created by copying line 17.
//         However, I forgot to correct name.
  b.write(a.read());
}
