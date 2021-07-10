Performance of static vs dynamic PageRank ([pull], [CSR], [scaled-fill]).

This experiment was for comparing the performance between:
1. Find static pagerank of updated graph.
2. Find dynamic pagerank, **scaling** old vertices, and using **1/N** for new vertices.

Both techniques were attempted on a number of temporal graphs, running each
with multiple batch sizes (`1`, `5`, `10`, `50`, ...). New edges are
incrementally added to the graph batch-by-batch until the entire graph is
complete. **Dynamic pagerank** is clearly **faster** than *static pagerank*
for most cases.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at the
[Stanford Large Network Dataset Collection]. This experiment was done with
guidance from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/sx-stackoverflow.txt

# (SHORTENED)
# Using graph sx-stackoverflow.txt ...
# Temporal edges: 63497051
# order: 2601977 size: 36233450 {}
#
# # Batch size 1e+0
# [04657.920 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00099.498 ms; 001 iters.] [9.6450e-7 err.] pagerankDynamic
#
# # Batch size 5e+0
# [04634.926 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00135.350 ms; 002 iters.] [1.4472e-6 err.] pagerankDynamic
#
# # Batch size 1e+1
# [04648.379 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00179.794 ms; 003 iters.] [1.9689e-6 err.] pagerankDynamic
#
# # Batch size 5e+1
# [04628.978 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [00341.603 ms; 006 iters.] [3.2815e-6 err.] pagerankDynamic
#
# # Batch size 1e+2
# [04609.713 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [00414.303 ms; 007 iters.] [4.0053e-6 err.] pagerankDynamic
#
# # Batch size 5e+2
# [04609.833 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [00685.551 ms; 011 iters.] [5.7854e-6 err.] pagerankDynamic
#
# # Batch size 1e+3
# [04628.448 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [00872.455 ms; 014 iters.] [7.5399e-6 err.] pagerankDynamic
#
# # Batch size 5e+3
# [04612.280 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [01532.175 ms; 022 iters.] [7.3422e-6 err.] pagerankDynamic
#
# # Batch size 1e+4
# [04636.627 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [01825.588 ms; 026 iters.] [7.2866e-6 err.] pagerankDynamic
#
# # Batch size 5e+4
# [04690.433 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [02556.521 ms; 034 iters.] [7.1117e-6 err.] pagerankDynamic
#
# # Batch size 1e+5
# [04637.379 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [02821.770 ms; 038 iters.] [1.1516e-5 err.] pagerankDynamic
#
# # Batch size 5e+5
# [04606.930 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [03491.683 ms; 046 iters.] [7.5847e-6 err.] pagerankDynamic
#
# # Batch size 1e+6
# [04590.247 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [03825.545 ms; 050 iters.] [7.3622e-6 err.] pagerankDynamic
#
# # Batch size 5e+6
# [04789.445 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [04697.050 ms; 056 iters.] [6.9308e-6 err.] pagerankDynamic
#
# # Batch size 1e+7
# [05223.199 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [05183.780 ms; 057 iters.] [6.0776e-6 err.] pagerankDynamic
#
# # Batch size 5e+7
# [06678.227 ms; 058 iters.] [0.0000e+0 err.] pagerankStatic
# [06742.952 ms; 059 iters.] [3.3479e-6 err.] pagerankDynamic
```

[![](https://i.imgur.com/4tWWPOT.gif)][sheets]
[![](https://i.imgur.com/VAHYT9C.gif)][sheets]
[![](https://i.imgur.com/opfSxQ9.gif)][sheets]
[![](https://i.imgur.com/gxzatLd.gif)][sheets]
[![](https://i.imgur.com/Gk1zBX3.gif)][sheets]
[![](https://i.imgur.com/4WLl0nt.gif)][sheets]
[![](https://i.imgur.com/QXdoot2.gif)][sheets]
[![](https://i.imgur.com/GYh1SV0.gif)][sheets]
[![](https://i.imgur.com/WFKWsuy.gif)][sheets]
[![](https://i.imgur.com/B2SDRKB.gif)][sheets]
[![](https://i.imgur.com/BdXE8ly.gif)][sheets]
[![](https://i.imgur.com/d1Qw1AF.gif)][sheets]
[![](https://i.imgur.com/3zo6nzy.gif)][sheets]
[![](https://i.imgur.com/v5y3qiY.gif)][sheets]

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/0TfMELc.jpg)](https://www.youtube.com/watch?v=npl0o3X7NTA)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[charts]: https://photos.app.goo.gl/dcQWY7z1HEdPAqre8
[sheets]: https://docs.google.com/spreadsheets/d/1b6fuE9dRbAbQanCl2rDXc-K2xpIUSg7Mw_dzVnFbkD8/edit?usp=sharing
