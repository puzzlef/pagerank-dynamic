Performance comparison of using **error measurement strategies** with
dynamic PageRank ([pull], [CSR]).

There are two ways of *error measurement* with *dynamic PageRank* calculation.
1. Measure error *for all vertices* (**full**), and stop once it falls below tolerance value.
2. Measure error *only for affected vertices* (**partial**), and stop once it falls below *scaled* tolerance value.

`TODO`

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -std=c++17 -O3 main.cxx
$ ./a.out ~/data/email-Eu-core-temporal.txt
$ ./a.out ~/data/CollegeMsg.txt
$ ...

# (SHORTENED)
# ...
#
# Using graph sx-stackoverflow.txt ...
# Temporal edges: 63497051
# order: 2601977 size: 36233450 {}
#
# # Batch size 1e+1
# [05530.117 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03885.523 ms; 043 iters.] [1.0784e-2 err.] pagerankTeleport (dynamic-full)
# [03879.973 ms; 043 iters.] [1.0784e-2 err.] pagerankTeleport (dynamic-partial)
# [04945.522 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [02841.727 ms; 032 iters.] [1.0635e-2 err.] pagerankLoop (dynamic-full)
# [02854.771 ms; 034 iters.] [1.0634e-2 err.] pagerankLoop (dynamic-partial)
# [04732.724 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03132.172 ms; 036 iters.] [1.0813e-2 err.] pagerankLoopAll (dynamic-full)
# [03190.126 ms; 038 iters.] [1.0812e-2 err.] pagerankLoopAll (dynamic-partial)
# [03709.146 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02697.447 ms; 040 iters.] [3.6837e-2 err.] pagerankRemove (dynamic-full)
# [02731.531 ms; 042 iters.] [3.6837e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+1
# [05404.213 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03904.148 ms; 043 iters.] [8.5991e-4 err.] pagerankTeleport (dynamic-full)
# [03884.698 ms; 043 iters.] [8.5991e-4 err.] pagerankTeleport (dynamic-partial)
# [04848.698 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [02894.188 ms; 033 iters.] [6.3630e-4 err.] pagerankLoop (dynamic-full)
# [02965.799 ms; 035 iters.] [6.3499e-4 err.] pagerankLoop (dynamic-partial)
# [04616.032 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03241.114 ms; 037 iters.] [7.8648e-4 err.] pagerankLoopAll (dynamic-full)
# [03268.989 ms; 038 iters.] [7.8512e-4 err.] pagerankLoopAll (dynamic-partial)
# [03642.386 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02712.481 ms; 040 iters.] [1.4858e-3 err.] pagerankRemove (dynamic-full)
# [02814.504 ms; 043 iters.] [1.4858e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+2
# [05398.281 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03886.014 ms; 043 iters.] [8.5820e-4 err.] pagerankTeleport (dynamic-full)
# [03862.920 ms; 043 iters.] [8.5820e-4 err.] pagerankTeleport (dynamic-partial)
# [04761.810 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [02857.284 ms; 033 iters.] [6.3595e-4 err.] pagerankLoop (dynamic-full)
# [02927.210 ms; 035 iters.] [6.3465e-4 err.] pagerankLoop (dynamic-partial)
# [04563.852 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03208.563 ms; 037 iters.] [7.8661e-4 err.] pagerankLoopAll (dynamic-full)
# [03280.487 ms; 039 iters.] [7.8524e-4 err.] pagerankLoopAll (dynamic-partial)
# [03649.768 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02724.629 ms; 041 iters.] [1.4858e-3 err.] pagerankRemove (dynamic-full)
# [02720.289 ms; 043 iters.] [1.4858e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+2
# [05472.637 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03911.807 ms; 043 iters.] [8.5792e-4 err.] pagerankTeleport (dynamic-full)
# [03906.738 ms; 043 iters.] [8.5792e-4 err.] pagerankTeleport (dynamic-partial)
# [04761.451 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [02813.523 ms; 033 iters.] [6.3410e-4 err.] pagerankLoop (dynamic-full)
# [02961.176 ms; 035 iters.] [6.3281e-4 err.] pagerankLoop (dynamic-partial)
# [04635.045 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03185.616 ms; 037 iters.] [7.8522e-4 err.] pagerankLoopAll (dynamic-full)
# [03273.207 ms; 039 iters.] [7.8387e-4 err.] pagerankLoopAll (dynamic-partial)
# [03634.719 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02666.254 ms; 041 iters.] [1.4865e-3 err.] pagerankRemove (dynamic-full)
# [02711.250 ms; 044 iters.] [1.4864e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+3
# [05410.048 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03867.531 ms; 044 iters.] [8.5552e-4 err.] pagerankTeleport (dynamic-full)
# [03865.457 ms; 044 iters.] [8.5552e-4 err.] pagerankTeleport (dynamic-partial)
# [04751.256 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [02850.915 ms; 033 iters.] [6.3282e-4 err.] pagerankLoop (dynamic-full)
# [02945.889 ms; 035 iters.] [6.3153e-4 err.] pagerankLoop (dynamic-partial)
# [04503.616 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03263.122 ms; 037 iters.] [7.8425e-4 err.] pagerankLoopAll (dynamic-full)
# [03278.221 ms; 039 iters.] [7.8294e-4 err.] pagerankLoopAll (dynamic-partial)
# [03648.349 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02727.434 ms; 041 iters.] [1.4872e-3 err.] pagerankRemove (dynamic-full)
# [02789.369 ms; 044 iters.] [1.4871e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+3
# [05529.451 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03928.555 ms; 044 iters.] [8.6132e-4 err.] pagerankTeleport (dynamic-full)
# [03973.335 ms; 044 iters.] [8.6132e-4 err.] pagerankTeleport (dynamic-partial)
# [04786.888 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [02838.815 ms; 034 iters.] [6.2588e-4 err.] pagerankLoop (dynamic-full)
# [02988.667 ms; 036 iters.] [6.2470e-4 err.] pagerankLoop (dynamic-partial)
# [04658.512 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03312.873 ms; 038 iters.] [7.7974e-4 err.] pagerankLoopAll (dynamic-full)
# [03225.711 ms; 040 iters.] [7.7848e-4 err.] pagerankLoopAll (dynamic-partial)
# [03655.904 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02722.193 ms; 042 iters.] [1.4945e-3 err.] pagerankRemove (dynamic-full)
# [02725.165 ms; 045 iters.] [1.4944e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+4
# [05355.425 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03850.469 ms; 044 iters.] [8.6273e-4 err.] pagerankTeleport (dynamic-full)
# [03850.058 ms; 044 iters.] [8.6273e-4 err.] pagerankTeleport (dynamic-partial)
# [04734.508 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [02889.423 ms; 035 iters.] [6.2011e-4 err.] pagerankLoop (dynamic-full)
# [03024.678 ms; 037 iters.] [6.1897e-4 err.] pagerankLoop (dynamic-partial)
# [04560.633 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03266.595 ms; 038 iters.] [7.7665e-4 err.] pagerankLoopAll (dynamic-full)
# [03240.672 ms; 040 iters.] [7.7548e-4 err.] pagerankLoopAll (dynamic-partial)
# [03619.322 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02708.890 ms; 043 iters.] [1.5040e-3 err.] pagerankRemove (dynamic-full)
# [02772.865 ms; 045 iters.] [1.5040e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+4
# [05435.680 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03952.017 ms; 045 iters.] [8.5426e-4 err.] pagerankTeleport (dynamic-full)
# [03941.191 ms; 045 iters.] [8.5426e-4 err.] pagerankTeleport (dynamic-partial)
# [04859.709 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [03103.775 ms; 037 iters.] [5.9698e-4 err.] pagerankLoop (dynamic-full)
# [03222.962 ms; 039 iters.] [5.9604e-4 err.] pagerankLoop (dynamic-partial)
# [04720.057 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03303.619 ms; 040 iters.] [7.6608e-4 err.] pagerankLoopAll (dynamic-full)
# [03364.793 ms; 042 iters.] [7.6503e-4 err.] pagerankLoopAll (dynamic-partial)
# [03684.576 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02708.787 ms; 045 iters.] [1.6220e-3 err.] pagerankRemove (dynamic-full)
# [02785.400 ms; 047 iters.] [1.6218e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+5
# [05446.271 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03947.911 ms; 046 iters.] [8.5883e-4 err.] pagerankTeleport (dynamic-full)
# [03959.313 ms; 046 iters.] [8.5883e-4 err.] pagerankTeleport (dynamic-partial)
# [04659.606 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [03146.380 ms; 039 iters.] [5.8047e-4 err.] pagerankLoop (dynamic-full)
# [03264.366 ms; 041 iters.] [5.7965e-4 err.] pagerankLoop (dynamic-partial)
# [04625.957 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03356.807 ms; 041 iters.] [7.6095e-4 err.] pagerankLoopAll (dynamic-full)
# [03413.821 ms; 043 iters.] [7.6002e-4 err.] pagerankLoopAll (dynamic-partial)
# [03660.425 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02863.631 ms; 046 iters.] [1.7630e-3 err.] pagerankRemove (dynamic-full)
# [02982.411 ms; 048 iters.] [1.7629e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+5
# [05235.717 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03998.946 ms; 049 iters.] [3.9015e-4 err.] pagerankTeleport (dynamic-full)
# [03974.706 ms; 049 iters.] [3.9015e-4 err.] pagerankTeleport (dynamic-partial)
# [04513.054 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [03357.693 ms; 045 iters.] [5.1104e-4 err.] pagerankLoop (dynamic-full)
# [03413.932 ms; 046 iters.] [5.1056e-4 err.] pagerankLoop (dynamic-partial)
# [04363.629 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03269.979 ms; 044 iters.] [7.4686e-4 err.] pagerankLoopAll (dynamic-full)
# [03328.293 ms; 046 iters.] [7.4625e-4 err.] pagerankLoopAll (dynamic-partial)
# [03521.911 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02871.785 ms; 050 iters.] [2.9415e-3 err.] pagerankRemove (dynamic-full)
# [02907.066 ms; 052 iters.] [2.9413e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+6
# [05207.828 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [04163.442 ms; 051 iters.] [3.4792e-4 err.] pagerankTeleport (dynamic-full)
# [04159.791 ms; 051 iters.] [3.4792e-4 err.] pagerankTeleport (dynamic-partial)
# [04642.410 ms; 051 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [03731.395 ms; 047 iters.] [5.1622e-4 err.] pagerankLoop (dynamic-full)
# [03817.179 ms; 048 iters.] [5.1587e-4 err.] pagerankLoop (dynamic-partial)
# [04398.673 ms; 051 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03590.860 ms; 046 iters.] [7.8028e-4 err.] pagerankLoopAll (dynamic-full)
# [03603.509 ms; 048 iters.] [7.7980e-4 err.] pagerankLoopAll (dynamic-partial)
# [03566.511 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02988.230 ms; 052 iters.] [4.0616e-3 err.] pagerankRemove (dynamic-full)
# [03012.101 ms; 054 iters.] [4.0613e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+6
# [05208.010 ms; 056 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [04694.504 ms; 056 iters.] [3.2031e-4 err.] pagerankTeleport (dynamic-full)
# [04727.816 ms; 056 iters.] [3.2031e-4 err.] pagerankTeleport (dynamic-partial)
# [05067.397 ms; 052 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [04705.365 ms; 052 iters.] [4.5803e-4 err.] pagerankLoop (dynamic-full)
# [04591.157 ms; 053 iters.] [4.5785e-4 err.] pagerankLoop (dynamic-partial)
# [04424.067 ms; 052 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [04322.087 ms; 051 iters.] [8.9832e-4 err.] pagerankLoopAll (dynamic-full)
# [04197.665 ms; 052 iters.] [8.9811e-4 err.] pagerankLoopAll (dynamic-partial)
# [03694.155 ms; 054 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [03652.800 ms; 056 iters.] [9.8153e-3 err.] pagerankRemove (dynamic-full)
# [03630.079 ms; 057 iters.] [9.8148e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+7
# [06053.154 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [05558.233 ms; 057 iters.] [6.4174e-4 err.] pagerankTeleport (dynamic-full)
# [05545.498 ms; 057 iters.] [6.4174e-4 err.] pagerankTeleport (dynamic-partial)
# [05636.728 ms; 053 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [04994.432 ms; 053 iters.] [4.1711e-4 err.] pagerankLoop (dynamic-full)
# [05035.627 ms; 054 iters.] [4.1689e-4 err.] pagerankLoop (dynamic-partial)
# [05204.659 ms; 053 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [05031.842 ms; 052 iters.] [8.7106e-4 err.] pagerankLoopAll (dynamic-full)
# [05008.802 ms; 053 iters.] [8.7091e-4 err.] pagerankLoopAll (dynamic-partial)
# [04305.305 ms; 055 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [04068.965 ms; 056 iters.] [1.0733e-2 err.] pagerankRemove (dynamic-full)
# [04401.484 ms; 057 iters.] [1.0733e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+7
# [07711.316 ms; 058 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [07436.135 ms; 059 iters.] [5.4804e-5 err.] pagerankTeleport (dynamic-full)
# [08238.648 ms; 059 iters.] [5.4804e-5 err.] pagerankTeleport (dynamic-partial)
# [07670.212 ms; 055 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [06798.180 ms; 056 iters.] [2.4537e-4 err.] pagerankLoop (dynamic-full)
# [07059.362 ms; 056 iters.] [2.4535e-4 err.] pagerankLoop (dynamic-partial)
# [07363.364 ms; 055 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [07249.228 ms; 055 iters.] [1.2089e-4 err.] pagerankLoopAll (dynamic-full)
# [06544.768 ms; 055 iters.] [1.2085e-4 err.] pagerankLoopAll (dynamic-partial)
# [06484.971 ms; 058 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [06954.867 ms; 059 iters.] [5.0810e-3 err.] pagerankRemove (dynamic-full)
# [06397.615 ms; 059 iters.] [5.0810e-3 err.] pagerankRemove (dynamic-partial)
```

[![](https://i.imgur.com/iXWSwSj.gif)][sheetp]
[![](https://i.imgur.com/XnPpQ7N.gif)][sheetp]
[![](https://i.imgur.com/AXw3bfH.gif)][sheetp]
[![](https://i.imgur.com/Me2uD1J.gif)][sheetp]
[![](https://i.imgur.com/4kJMw90.gif)][sheetp]
[![](https://i.imgur.com/kS3lO2N.gif)][sheetp]
[![](https://i.imgur.com/TlY2tk4.gif)][sheetp]
[![](https://i.imgur.com/mFjxYdb.gif)][sheetp]

[![](https://i.imgur.com/7xbsTnI.gif)][sheetp]
[![](https://i.imgur.com/M3N2ugc.gif)][sheetp]
[![](https://i.imgur.com/g6yRV5I.gif)][sheetp]
[![](https://i.imgur.com/LIRshab.gif)][sheetp]
[![](https://i.imgur.com/04c1rGI.gif)][sheetp]
[![](https://i.imgur.com/OCt5j3L.gif)][sheetp]
[![](https://i.imgur.com/IhZKLr6.gif)][sheetp]
[![](https://i.imgur.com/9SVIo4t.gif)][sheetp]

[![](https://i.imgur.com/1ujIEKW.gif)][sheetp]
[![](https://i.imgur.com/MkPEQ9T.gif)][sheetp]
[![](https://i.imgur.com/Xkbjpnc.gif)][sheetp]
[![](https://i.imgur.com/sV2FIQF.gif)][sheetp]
[![](https://i.imgur.com/3UflZ3F.gif)][sheetp]
[![](https://i.imgur.com/5tVVN4n.gif)][sheetp]
[![](https://i.imgur.com/nWyUoSC.gif)][sheetp]
[![](https://i.imgur.com/SfIpzCs.gif)][sheetp]

[![](https://i.imgur.com/Sr2lga8.gif)][sheetp]
[![](https://i.imgur.com/cYu2AYH.gif)][sheetp]
[![](https://i.imgur.com/qZaJ6n8.gif)][sheetp]
[![](https://i.imgur.com/dRIcft5.gif)][sheetp]
[![](https://i.imgur.com/uTQoyTX.gif)][sheetp]
[![](https://i.imgur.com/EAz11wD.gif)][sheetp]
[![](https://i.imgur.com/KPE8TZk.gif)][sheetp]
[![](https://i.imgur.com/2Vmx4WH.gif)][sheetp]

[![](https://i.imgur.com/Kh0iURR.gif)][sheetp]
[![](https://i.imgur.com/1YL1D1i.gif)][sheetp]
[![](https://i.imgur.com/9jSmdEN.gif)][sheetp]
[![](https://i.imgur.com/rtvwtHL.gif)][sheetp]
[![](https://i.imgur.com/Lozs712.gif)][sheetp]
[![](https://i.imgur.com/SbQw9uT.gif)][sheetp]
[![](https://i.imgur.com/ORDyKDP.gif)][sheetp]
[![](https://i.imgur.com/P0hPCuX.gif)][sheetp]

[![](https://i.imgur.com/X8PCXMh.gif)][sheetp]
[![](https://i.imgur.com/0V5Cgzf.gif)][sheetp]
[![](https://i.imgur.com/107gh8Y.gif)][sheetp]
[![](https://i.imgur.com/i4BP7zH.gif)][sheetp]
[![](https://i.imgur.com/Pqr2yOn.gif)][sheetp]
[![](https://i.imgur.com/t1WTA5s.gif)][sheetp]
[![](https://i.imgur.com/ks8lRxK.gif)][sheetp]
[![](https://i.imgur.com/WsbLJFP.gif)][sheetp]

[![](https://i.imgur.com/dMSHrON.gif)][sheetp]
[![](https://i.imgur.com/w6B5vHq.gif)][sheetp]
[![](https://i.imgur.com/cbC7ujr.gif)][sheetp]
[![](https://i.imgur.com/zdVtza9.gif)][sheetp]
[![](https://i.imgur.com/fhdME1W.gif)][sheetp]
[![](https://i.imgur.com/BYFHBY4.gif)][sheetp]
[![](https://i.imgur.com/5zbhHqQ.gif)][sheetp]
[![](https://i.imgur.com/RQnuEC4.gif)][sheetp]


[![](https://i.imgur.com/qefllB8.png)][sheetp]
[![](https://i.imgur.com/4WzFlIQ.png)][sheetp]
[![](https://i.imgur.com/21PYkJt.png)][sheetp]
[![](https://i.imgur.com/lVjSN7g.png)][sheetp]
[![](https://i.imgur.com/JlSGjbA.png)][sheetp]
[![](https://i.imgur.com/Xqa7JrJ.png)][sheetp]
[![](https://i.imgur.com/EuaXnt2.png)][sheetp]
[![](https://i.imgur.com/JEbnNTZ.png)][sheetp]

[![](https://i.imgur.com/9GR88NW.png)][sheetp]
[![](https://i.imgur.com/z3GGJaM.png)][sheetp]
[![](https://i.imgur.com/s0FjaiE.png)][sheetp]
[![](https://i.imgur.com/e2Qbnny.png)][sheetp]
[![](https://i.imgur.com/AIbMeOn.png)][sheetp]
[![](https://i.imgur.com/s7vr9Ss.png)][sheetp]
[![](https://i.imgur.com/97sokl3.png)][sheetp]
[![](https://i.imgur.com/qLMWpaw.png)][sheetp]

[![](https://i.imgur.com/h1vtKm2.png)][sheetp]
[![](https://i.imgur.com/bUFxmle.png)][sheetp]
[![](https://i.imgur.com/DIIh1pm.png)][sheetp]
[![](https://i.imgur.com/9LLyUWc.png)][sheetp]
[![](https://i.imgur.com/KzBCgzd.png)][sheetp]
[![](https://i.imgur.com/xQHxkZ6.png)][sheetp]
[![](https://i.imgur.com/C1YX0zM.png)][sheetp]
[![](https://i.imgur.com/uvG7mHr.png)][sheetp]

[![](https://i.imgur.com/vowm1k6.png)][sheetp]
[![](https://i.imgur.com/MkIpRZd.png)][sheetp]
[![](https://i.imgur.com/Y2Eccqb.png)][sheetp]
[![](https://i.imgur.com/CeuTtMG.png)][sheetp]
[![](https://i.imgur.com/GPL5CNv.png)][sheetp]
[![](https://i.imgur.com/KMEWDV9.png)][sheetp]
[![](https://i.imgur.com/oPFJBn4.png)][sheetp]
[![](https://i.imgur.com/v9ARKBq.png)][sheetp]

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/89cRRdY.jpg)](https://www.youtube.com/watch?v=iMdq5_5eib0)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/mAGStz1Pg2DR4RsT8
[sheets]: https://docs.google.com/spreadsheets/d/1pz1ya2ftFWABJM-etPEV1GEf94Wnw1hJbZlh6WTickY/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vS8rn04zSsyDW29MphGmqUTGSEbzJzqw_S7J1fqRTMTPPSGPWiqxhUTQuDbba3XpXGgR9ugBX5vMlb2/pubhtml
