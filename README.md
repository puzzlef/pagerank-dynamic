Performance of **contribution-push** based vs **contribution-pull** based PageRank.

There are two ways (algorithmically) to think of the pagerank calculation.
1. Find pagerank by **pushing contribution** to *out-vertices*.
2. Find pagerank by **pulling contribution** from *in-vertices*.

This experiment was to try both of these approaches on a number of different
graphs, running each approach 5 times per graph to get a good time measure.
The **push** method is somewhat easier to implement, and is described in
[this lecture]. However, it requires multiple writes per source vertex.
On the other hand, the **pull** method requires 2 additional calculations
per-vertex, i.e., non-teleport contribution of each vertex, and, total
teleport contribution (to all vertices). However, it requires only 1 write
per destination vertex.

While it might seem that pull method would be a clear winner, the results
indicate that although **pull** is always **faster** than *push* approach,
the difference between the two depends on the nature of the graph. Note
that neither approach makes use of *SIMD instructions* which are available
on all modern hardware.

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
# [04851.921 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [00850.952 ms; 013 iters.] [4.2257e-4 err.] pagerankTeleport (dynamic-full)
# [00853.373 ms; 013 iters.] [4.2257e-4 err.] pagerankTeleport (dynamic-partial)
# [03696.537 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [00132.195 ms; 002 iters.] [1.5312e-6 err.] pagerankLoop (dynamic-full)
# [00184.983 ms; 003 iters.] [1.6357e-6 err.] pagerankLoop (dynamic-partial)
# [03857.906 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [00119.807 ms; 002 iters.] [1.5658e-6 err.] pagerankLoopAll (dynamic-full)
# [00170.017 ms; 003 iters.] [1.7373e-6 err.] pagerankLoopAll (dynamic-partial)
# [03439.101 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [03210.626 ms; 058 iters.] [1.5855e-2 err.] pagerankRemove (dynamic-full)
# [03262.219 ms; 059 iters.] [1.5855e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+1
# [04622.221 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [00905.163 ms; 015 iters.] [4.2427e-4 err.] pagerankTeleport (dynamic-full)
# [00906.015 ms; 015 iters.] [4.2427e-4 err.] pagerankTeleport (dynamic-partial)
# [03475.991 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [00266.267 ms; 004 iters.] [2.8962e-6 err.] pagerankLoop (dynamic-full)
# [00301.446 ms; 005 iters.] [2.7123e-6 err.] pagerankLoop (dynamic-partial)
# [03597.244 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [00237.085 ms; 004 iters.] [3.0453e-6 err.] pagerankLoopAll (dynamic-full)
# [00276.520 ms; 005 iters.] [2.9021e-6 err.] pagerankLoopAll (dynamic-partial)
# [03290.769 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [03038.005 ms; 058 iters.] [1.5855e-2 err.] pagerankRemove (dynamic-full)
# [03101.300 ms; 059 iters.] [1.5855e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+2
# [04585.060 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [00926.924 ms; 015 iters.] [4.2293e-4 err.] pagerankTeleport (dynamic-full)
# [00930.036 ms; 015 iters.] [4.2293e-4 err.] pagerankTeleport (dynamic-partial)
# [03451.951 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [00325.311 ms; 006 iters.] [3.5198e-6 err.] pagerankLoop (dynamic-full)
# [00364.794 ms; 007 iters.] [3.2179e-6 err.] pagerankLoop (dynamic-partial)
# [03568.740 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [00305.406 ms; 005 iters.] [3.7485e-6 err.] pagerankLoopAll (dynamic-full)
# [00339.491 ms; 006 iters.] [3.4649e-6 err.] pagerankLoopAll (dynamic-partial)
# [03264.674 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [03014.660 ms; 058 iters.] [1.5855e-2 err.] pagerankRemove (dynamic-full)
# [03068.464 ms; 059 iters.] [1.5855e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+2
# [04475.601 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [01025.701 ms; 017 iters.] [4.2555e-4 err.] pagerankTeleport (dynamic-full)
# [01026.733 ms; 017 iters.] [4.2555e-4 err.] pagerankTeleport (dynamic-partial)
# [03401.757 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [00517.111 ms; 010 iters.] [5.0824e-6 err.] pagerankLoop (dynamic-full)
# [00586.693 ms; 011 iters.] [4.3903e-6 err.] pagerankLoop (dynamic-partial)
# [03511.560 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [00507.089 ms; 010 iters.] [5.2972e-6 err.] pagerankLoopAll (dynamic-full)
# [00571.719 ms; 011 iters.] [4.5886e-6 err.] pagerankLoopAll (dynamic-partial)
# [03205.029 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02970.128 ms; 058 iters.] [1.5855e-2 err.] pagerankRemove (dynamic-full)
# [03019.891 ms; 059 iters.] [1.5855e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+3
# [04483.775 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [01142.090 ms; 018 iters.] [4.2759e-4 err.] pagerankTeleport (dynamic-full)
# [01145.313 ms; 018 iters.] [4.2759e-4 err.] pagerankTeleport (dynamic-partial)
# [03390.572 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [00665.872 ms; 013 iters.] [5.6965e-6 err.] pagerankLoop (dynamic-full)
# [00750.569 ms; 014 iters.] [4.8313e-6 err.] pagerankLoop (dynamic-partial)
# [03510.645 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [00651.872 ms; 012 iters.] [5.8364e-6 err.] pagerankLoopAll (dynamic-full)
# [00726.428 ms; 014 iters.] [5.0397e-6 err.] pagerankLoopAll (dynamic-partial)
# [03217.045 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02967.557 ms; 058 iters.] [1.5854e-2 err.] pagerankRemove (dynamic-full)
# [03015.005 ms; 059 iters.] [1.5854e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+3
# [04497.343 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [01556.970 ms; 024 iters.] [4.3287e-4 err.] pagerankTeleport (dynamic-full)
# [01557.819 ms; 024 iters.] [4.3287e-4 err.] pagerankTeleport (dynamic-partial)
# [03389.138 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [01169.442 ms; 021 iters.] [6.3166e-6 err.] pagerankLoop (dynamic-full)
# [01261.324 ms; 022 iters.] [5.3143e-6 err.] pagerankLoop (dynamic-partial)
# [03522.822 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [01130.907 ms; 020 iters.] [6.5629e-6 err.] pagerankLoopAll (dynamic-full)
# [01207.731 ms; 022 iters.] [5.5794e-6 err.] pagerankLoopAll (dynamic-partial)
# [03221.898 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02957.805 ms; 058 iters.] [1.5857e-2 err.] pagerankRemove (dynamic-full)
# [03016.430 ms; 059 iters.] [1.5857e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+4
# [04488.908 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [01769.905 ms; 027 iters.] [4.3164e-4 err.] pagerankTeleport (dynamic-full)
# [01767.358 ms; 027 iters.] [4.3164e-4 err.] pagerankTeleport (dynamic-partial)
# [03421.292 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [01397.260 ms; 024 iters.] [6.4854e-6 err.] pagerankLoop (dynamic-full)
# [01487.141 ms; 026 iters.] [5.4408e-6 err.] pagerankLoop (dynamic-partial)
# [03529.370 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [01370.308 ms; 024 iters.] [6.7158e-6 err.] pagerankLoopAll (dynamic-full)
# [01439.905 ms; 025 iters.] [5.6845e-6 err.] pagerankLoopAll (dynamic-partial)
# [03232.829 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02981.530 ms; 058 iters.] [1.5851e-2 err.] pagerankRemove (dynamic-full)
# [03026.178 ms; 059 iters.] [1.5851e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+4
# [04510.532 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [02331.230 ms; 034 iters.] [4.2591e-4 err.] pagerankTeleport (dynamic-full)
# [02342.306 ms; 034 iters.] [4.2591e-4 err.] pagerankTeleport (dynamic-partial)
# [03408.886 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [01935.739 ms; 032 iters.] [6.5757e-6 err.] pagerankLoop (dynamic-full)
# [02022.907 ms; 034 iters.] [5.4970e-6 err.] pagerankLoop (dynamic-partial)
# [03537.548 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [01894.896 ms; 032 iters.] [6.9042e-6 err.] pagerankLoopAll (dynamic-full)
# [01956.976 ms; 033 iters.] [5.8366e-6 err.] pagerankLoopAll (dynamic-partial)
# [03234.946 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02981.868 ms; 058 iters.] [1.5816e-2 err.] pagerankRemove (dynamic-full)
# [03037.288 ms; 059 iters.] [1.5816e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+5
# [04500.296 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [02596.185 ms; 038 iters.] [4.2523e-4 err.] pagerankTeleport (dynamic-full)
# [02604.035 ms; 038 iters.] [4.2523e-4 err.] pagerankTeleport (dynamic-partial)
# [03426.800 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [02157.199 ms; 036 iters.] [6.5941e-6 err.] pagerankLoop (dynamic-full)
# [02242.756 ms; 038 iters.] [5.5411e-6 err.] pagerankLoop (dynamic-partial)
# [03527.188 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [02115.772 ms; 035 iters.] [6.9358e-6 err.] pagerankLoopAll (dynamic-full)
# [02194.836 ms; 037 iters.] [5.8289e-6 err.] pagerankLoopAll (dynamic-partial)
# [03231.058 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [02978.933 ms; 058 iters.] [1.5762e-2 err.] pagerankRemove (dynamic-full)
# [03034.055 ms; 059 iters.] [1.5762e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+5
# [04526.756 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03217.553 ms; 046 iters.] [3.9182e-4 err.] pagerankTeleport (dynamic-full)
# [03221.831 ms; 046 iters.] [3.9182e-4 err.] pagerankTeleport (dynamic-partial)
# [03412.089 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [02696.333 ms; 044 iters.] [6.4926e-6 err.] pagerankLoop (dynamic-full)
# [02750.494 ms; 045 iters.] [5.5501e-6 err.] pagerankLoop (dynamic-partial)
# [03544.510 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [02641.881 ms; 043 iters.] [6.9493e-6 err.] pagerankLoopAll (dynamic-full)
# [02703.871 ms; 045 iters.] [5.9069e-6 err.] pagerankLoopAll (dynamic-partial)
# [03235.366 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [03000.420 ms; 058 iters.] [1.5293e-2 err.] pagerankRemove (dynamic-full)
# [03048.030 ms; 060 iters.] [1.5293e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+6
# [04989.396 ms; 056 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [03867.231 ms; 049 iters.] [3.4816e-4 err.] pagerankTeleport (dynamic-full)
# [03869.729 ms; 049 iters.] [3.4816e-4 err.] pagerankTeleport (dynamic-partial)
# [03850.290 ms; 044 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [03251.650 ms; 046 iters.] [6.4582e-6 err.] pagerankLoop (dynamic-full)
# [03352.257 ms; 048 iters.] [5.5068e-6 err.] pagerankLoop (dynamic-partial)
# [04017.433 ms; 044 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03224.120 ms; 046 iters.] [6.8601e-6 err.] pagerankLoopAll (dynamic-full)
# [03279.987 ms; 047 iters.] [5.8627e-6 err.] pagerankLoopAll (dynamic-partial)
# [03589.587 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [03356.372 ms; 059 iters.] [1.4546e-2 err.] pagerankRemove (dynamic-full)
# [03415.710 ms; 060 iters.] [1.4546e-2 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+6
# [04953.558 ms; 056 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [04507.158 ms; 056 iters.] [3.2059e-4 err.] pagerankTeleport (dynamic-full)
# [04484.068 ms; 056 iters.] [3.2059e-4 err.] pagerankTeleport (dynamic-partial)
# [03878.606 ms; 045 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [03757.160 ms; 051 iters.] [5.8825e-6 err.] pagerankLoop (dynamic-full)
# [03820.137 ms; 052 iters.] [5.2537e-6 err.] pagerankLoop (dynamic-partial)
# [04007.882 ms; 045 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [03680.963 ms; 050 iters.] [6.1178e-6 err.] pagerankLoopAll (dynamic-full)
# [03736.318 ms; 051 iters.] [5.3989e-6 err.] pagerankLoopAll (dynamic-partial)
# [03709.806 ms; 052 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [03491.077 ms; 060 iters.] [8.6993e-3 err.] pagerankRemove (dynamic-full)
# [03551.886 ms; 062 iters.] [8.6996e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 1e+7
# [05392.156 ms; 057 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [05020.084 ms; 057 iters.] [6.4179e-4 err.] pagerankTeleport (dynamic-full)
# [04982.307 ms; 057 iters.] [6.4179e-4 err.] pagerankTeleport (dynamic-partial)
# [04251.046 ms; 046 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [04091.434 ms; 050 iters.] [5.4004e-6 err.] pagerankLoop (dynamic-full)
# [04181.763 ms; 051 iters.] [4.9507e-6 err.] pagerankLoop (dynamic-partial)
# [04442.193 ms; 047 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [04027.664 ms; 049 iters.] [5.6146e-6 err.] pagerankLoopAll (dynamic-full)
# [04071.348 ms; 050 iters.] [4.9323e-6 err.] pagerankLoopAll (dynamic-partial)
# [04082.759 ms; 053 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [03903.030 ms; 061 iters.] [4.5333e-3 err.] pagerankRemove (dynamic-full)
# [03937.720 ms; 062 iters.] [4.5334e-3 err.] pagerankRemove (dynamic-partial)
#
# # Batch size 5e+7
# [06909.900 ms; 058 iters.] [0.0000e+0 err.] pagerankTeleport (static)
# [06383.602 ms; 059 iters.] [5.5646e-5 err.] pagerankTeleport (dynamic-full)
# [06407.914 ms; 059 iters.] [5.5646e-5 err.] pagerankTeleport (dynamic-partial)
# [06212.262 ms; 055 iters.] [0.0000e+0 err.] pagerankLoop (static)
# [05578.974 ms; 054 iters.] [2.8869e-6 err.] pagerankLoop (dynamic-full)
# [05558.839 ms; 055 iters.] [2.6885e-6 err.] pagerankLoop (dynamic-partial)
# [06526.776 ms; 055 iters.] [0.0000e+0 err.] pagerankLoopAll (static)
# [05576.140 ms; 054 iters.] [2.9767e-6 err.] pagerankLoopAll (dynamic-full)
# [05582.109 ms; 054 iters.] [2.9767e-6 err.] pagerankLoopAll (dynamic-partial)
# [06058.312 ms; 058 iters.] [0.0000e+0 err.] pagerankRemove (static)
# [05669.452 ms; 062 iters.] [2.4701e-3 err.] pagerankRemove (dynamic-full)
# [05770.752 ms; 063 iters.] [2.4698e-3 err.] pagerankRemove (dynamic-partial)
```

[![](https://i.imgur.com/rcvx67u.png)][sheetp]
[![](https://i.imgur.com/zM0FWhK.png)][sheetp]
[![](https://i.imgur.com/hdnvgFv.png)][sheetp]
[![](https://i.imgur.com/0PFzEdr.png)][sheetp]
[![](https://i.imgur.com/vHUGqZj.png)][sheetp]
[![](https://i.imgur.com/3KoFa4a.png)][sheetp]
[![](https://i.imgur.com/sugM3YE.png)][sheetp]
[![](https://i.imgur.com/sMeAFTI.png)][sheetp]

[![](https://i.imgur.com/frNocq5.png)][sheetp]
[![](https://i.imgur.com/panmjFp.png)][sheetp]
[![](https://i.imgur.com/vtGV8cy.png)][sheetp]
[![](https://i.imgur.com/SgP0oX5.png)][sheetp]
[![](https://i.imgur.com/cvOOgP1.png)][sheetp]
[![](https://i.imgur.com/1Kl8QjI.png)][sheetp]
[![](https://i.imgur.com/jn1XSoG.png)][sheetp]
[![](https://i.imgur.com/C0KCMVt.png)][sheetp]

[![](https://i.imgur.com/fIWv0LV.png)][sheetp]
[![](https://i.imgur.com/8UHPScN.png)][sheetp]
[![](https://i.imgur.com/WEOfhxQ.png)][sheetp]
[![](https://i.imgur.com/5HUxEvz.png)][sheetp]
[![](https://i.imgur.com/Gbm0HRo.png)][sheetp]
[![](https://i.imgur.com/Eg2SbDu.png)][sheetp]
[![](https://i.imgur.com/SLZqLbf.png)][sheetp]
[![](https://i.imgur.com/opGpoGp.png)][sheetp]

[![](https://i.imgur.com/nKYNcqI.png)][sheetp]
[![](https://i.imgur.com/uz6Vo8i.png)][sheetp]
[![](https://i.imgur.com/rEhwe0B.png)][sheetp]
[![](https://i.imgur.com/RCoGnHq.png)][sheetp]
[![](https://i.imgur.com/pVAQ12g.png)][sheetp]
[![](https://i.imgur.com/JpIYts8.png)][sheetp]
[![](https://i.imgur.com/MncjtSr.png)][sheetp]
[![](https://i.imgur.com/IkBs3j6.png)][sheetp]

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
[charts]: https://photos.app.goo.gl/mAGStz1Pg2DR4RsT8
[sheets]: https://docs.google.com/spreadsheets/d/1pz1ya2ftFWABJM-etPEV1GEf94Wnw1hJbZlh6WTickY/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vS8rn04zSsyDW29MphGmqUTGSEbzJzqw_S7J1fqRTMTPPSGPWiqxhUTQuDbba3XpXGgR9ugBX5vMlb2/pubhtml
