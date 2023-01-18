# Vitis HLS Bug sample

Sample code for the Vitis HLS bug I suffered from.

## Environment

- Ubuntu 20.04
- Vitis HLS 2022.2
- CMake
- Make

## How to build

1. Init cmake

```sh
mkdir build
cd build
cmake .. \
  -DVITIS_HLS_ROOT=<Your Vitis HLS Install Directory>
```

Example of using Vitis 2022.2

`cmake .. -DVITIS_HLS_ROOT=/tools/Xilinx/Vitis_HLS/2022.2`

2. Run synthesis

```sh
make csynth_<xxxx>
```

- `<xxx>`
    - `duplicate` : [duplicate.cpp](./duplicate.cpp)
    - `duplicate2`: [duplicate.cpp](./duplicate.cpp) with NOCRASH macro

## duplicate.cpp

```cpp
#pragma HLS INTERFACE axis port=a name=s_axis_a
#pragma HLS INTERFACE axis port=b name=s_axis_a
//                                ~~~~~~~~~~~~~
```

I forgot to fix the `name` of the port `b`.

- `make csynth_duplicate` : Synthesis failed. However, the cause of the error is not specifically indicated.
- `make csynth_duplicate2`: Synthesis completes **WITHOUT** error and RTL is generated.

The difference between them is that the AXI Stream has a different data type.

The AXI Stream data type of `csynth_duplicate` is `hls::axis`, and the type of `csynth_duplicate2` is `ap_int`.


<details><summary>csynth_duplicate log</summary>

```log
****** Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
  **** SW Build 3670227 on Oct 13 2022
  **** IP Build 3669848 on Fri Oct 14 08:30:02 MDT 2022
    ** Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.

source /tools/Xilinx/Vitis_HLS/2022.2/scripts/vitis_hls/hls.tcl -notrace
INFO: [HLS 200-10] Running '/tools/Xilinx/Vitis_HLS/2022.2/bin/unwrapped/lnx64.o/vitis_hls'
INFO: [HLS 200-10] For user 'nodamushi' on host 'nodamushi-ubuntu' (Linux_x86_64 version 5.15.0-57-generic) on Wed Jan 18 23:22:27 JST 2023
INFO: [HLS 200-10] On os Ubuntu 20.04.5 LTS
INFO: [HLS 200-10] In directory '/home/nodamushi/hls_error/build'
Sourcing Tcl script '/home/nodamushi/hls_error/build/_deps/vivado_cmake_module-src/tcl/csynth.tcl'
INFO: [HLS 200-1510] Running: open_project duplicate_hls_prj
INFO: [HLS 200-10] Opening project '/home/nodamushi/hls_error/build/duplicate_hls_prj'.
INFO: [HLS 200-1510] Running: add_files -cflags -I/home/nodamushi/hls_error /home/nodamushi/hls_error/duplicate.cpp
INFO: [HLS 200-10] Adding design file '/home/nodamushi/hls_error/duplicate.cpp' to the project
INFO: [HLS 200-1510] Running: set_top Duplicate
INFO: [HLS 200-1510] Running: open_solution solution1 -flow_target vivado
INFO: [HLS 200-10] Opening solution '/home/nodamushi/hls_error/build/duplicate_hls_prj/solution1'.
INFO: [SYN 201-201] Setting up clock 'default' with a period of 10ns.
INFO: [HLS 200-1611] Setting target device to 'xc7z007s-clg400-1'
INFO: [HLS 200-1505] Using flow_target 'vivado'
Resolution: For help on HLS 200-1505 see www.xilinx.com/cgi-bin/docs/rdoc?v=2022.2;t=hls+guidance;d=200-1505.html
INFO: [HLS 200-1464] Running solution command: config_interface -m_axi_latency=0
INFO: [HLS 200-1510] Running: set_part xc7z007sclg400-1
INFO: [HLS 200-1510] Running: create_clock -period 10 -name default
INFO: [HLS 200-1510] Running: csynth_design
Running Dispatch Server on port: 43011
INFO: [HLS 200-111] Finished File checks and directory preparation: CPU user time: 0.01 seconodamushi. CPU system time: 0.01 seconodamushi. Elapsed time: 10.02 seconodamushi; current allocated memory: 206.730 MB.
INFO: [HLS 200-10] Analyzing design file '/home/nodamushi/hls_error/duplicate.cpp' ...
INFO: [HLS 200-111] Finished Source Code Analysis and Preprocessing: CPU user time: 3.21 seconodamushi. CPU system time: 0.46 seconodamushi. Elapsed time: 3.67 seconodamushi; current allocated memory: 206.766 MB.
INFO: [HLS 200-777] Using interface defaults for 'Vivado' flow target.
ERROR: [HLS 200-1715] Encountered problem during source synthesis
INFO: [HLS 200-111] Finished Command csynth_design CPU user time: 6.18 seconodamushi. CPU system time: 0.83 seconodamushi. Elapsed time: 7.17 seconodamushi; current allocated memory: 0.242 MB.
Pre-synthesis failed.
    while executing
"source /home/nodamushi/hls_error/build/_deps/vivado_cmake_module-src/tcl/csynth.tcl"
    ("uplevel" body line 1)
    invoked from within
"uplevel \#0 [list source $arg] "

INFO: [HLS 200-112] Total CPU user time: 7.34 seconodamushi. Total CPU system time: 1.02 seconodamushi. Total elapsed time: 18.39 seconodamushi; peak allocated memory: 206.973 MB.
INFO: [Common 17-206] Exiting vitis_hls at Wed Jan 18 23:22:44 2023...
make[3]: *** [CMakeFiles/csynth_duplicate.dir/build.make:58: duplicate_hls_prj/solution1/impl/ip/Anonymous_hls_duplicate_1_0.zip] Error 1
make[2]: *** [CMakeFiles/Makefile2:142: CMakeFiles/csynth_duplicate.dir/all] Error 2
make[1]: *** [CMakeFiles/Makefile2:149: CMakeFiles/csynth_duplicate.dir/rule] Error 2
make: *** [Makefile:144: csynth_duplicate] Error 2
```
</details>

<details><summary>csynth_duplicate2 Generated RTL Port</summary>

`build/duplicate2_hls_prj/solution1/syn/verilog/Duplicate.v`

```verilog
module Duplicate (
        ap_clk,
        ap_rst_n,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        s_axis_a_TVALID,
        s_axis_a_r_TREADY,
        s_axis_a_TDATA,
        s_axis_a_TREADY,
        s_axis_a_r_TDATA,
        s_axis_a_r_TVALID
);
```
</details>

## TODO

I have hit a problem where Vitis HLS fails if there is a structure with a `data` field.

However, I don't know how to reproduce the code.

