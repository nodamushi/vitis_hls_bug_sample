// sample top module function
void Cosim(bool& a, bool& b)
{
#pragma HLS pipeline
  a = !b;
}

