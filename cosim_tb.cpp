void Cosim(bool& a, bool& b);

#ifdef WORKAROUND_COSIMBUG
// define a wrapper function in the global scope.
void wrapper(bool& a, bool& b) { Cosim(a, b); }
#endif

struct xxx
{
  // call top module function in class
  static void test() {
    bool a = true, b;

#ifndef WORKAROUND_COSIMBUG
    Cosim(a, b);
#else
    wrapper(a, b); // Wrapper functions can be used to work around this bug.
#endif

  }
};

// pattern 2. This pattern is failed in the Vitis HLS 2021.2.
// Define a function without a line break after the declaration
// and call the top module function.
// This problem occurs, for example, when defining function declarations in macros.
int x;void test2() {
  bool a = true, b;

#ifndef WORKAROUND_COSIMBUG
  Cosim(a, b);
#else
  wrapper(a, b); // Wrapper functions can be used to work around this bug.
#endif

}

int main(int argc, char const *argv[])
{
  xxx::test();
  test2();
  return 0;
}
