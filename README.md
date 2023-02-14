Comparing strategies to **update ranks** for **incremental/dynamic PageRank** ([pull], [CSR]).

This experiment was for comparing the performance between:
1. Find **static** pagerank of updated graph.
2. Find **incremental** pagerank, using **zero-fill**.
3. Find **incremental** pagerank, using **1/N-fill**.
4. Find **incremental** pagerank, using **scaled zero-fill**.
5. Find **incremental** pagerank, using **scaled 1/N-fill**.

There are a number of **strategies to set up the initial rank vector** for the
PageRank algorithm on the *updated graph*, using the ranks from the *old graph*.
If a graph update does not end up adding any *new vertices*, then it is simply
a matter of running PageRank upon the *updated graph* with the previous ranks,
as the *initial ranks*. If however, some new vertices have been added, and/or
some old vertices have been removed, one of the following strategies may be
used to adjust the *initial ranks*: *zero-fill*, *1/N-fill*, *scaled zero-fill*,
or *scaled 1/N-fill*. The **zero-fill** strategy is the simplest, and consists
of simply filling the ranks of *new vertices* with `0` (i.e. `r₁ = 0` for new
vertices). The **1/N-fill** strategy is similar, ranks of *new vertices* are
filled with `1/N₁` (i.e. `r₁ = 1/N₁` for new vertices). The **scaled zero-fill**
strategy extends *zero-fill*, and additionally *scales* ranks of *old vertices*
with a factor of `N₀/N₁` (i.e. `r₁ = r₀ × N₀/N₁` for old vertices, and `r₁ = 0`
for new vertices). Finally, the **scaled 1/N-fill** strategy is a combination of
*scaling old vertices*, and *1/N-fill* (i.e. `r₁ = r₀ × N₀/N₁` for old vertices,
and `r₁ = 1/N₁` for new vertices). Here, `N₀` is the *total number of vertices*,
and `r₀` is the *rank of a given vertex* in the *old graph*. On the other hand,
`N₁` is the *total number of vertices*, and `r₁` is the *rank of a given vertex*
in the *updated graph*.

For *static PageRank* computation of a graph, the *initial ranks* of all vertices
are set to `1/N`, where `N` is the *total number of vertices* in the graph.
Therefore, the *sum* of all *initial ranks* equals `1`, as it should for a
*probability (rank) vector*. It is important to note however that this is *not*
an *essential condition*, rather, it likely helps with faster convergence.

With scaled rank adjustment strategies, unlike unscaled ones, PageRank computation
on *unaffected vertices* can be **skipped** , as long as the graph has no *affected*
*dead ends (including dead ends in the old graph)*. *Scaling* is *necessary*,
because even though the *importance* of *unaffected vertices* does not change,
the *final rank vector* is a *probabilistic vector* and *must sum to 1*. Here,
*affected vertices* are those which are either *changed vertices*, or are *reachable*
from changed vertices. *Changed vertices* are those which have an edge added or
removed between it and another (changed) vertex.

An experiment is conducted with each *rank adjustment strategy* on various
*temporal graphs*, updating each graph with multiple batch sizes (10¹, 5×10¹,
10², ...), until the entire graph is processed. For each batch size,
*static PageRank* is computed, along with *incremental PageRank* based on each
of the four rank adjustment strategies, *without skipping unaffected vertices*.
This is done in order to get an estimate of the *convergence rate* of
each *rank adjustment strategy*, *independent* of the *number of skipped*
*vertices* (which can *differ* based on the *dead end handling strategy* used).

Each rank adjustment strategy is performed using a *common adjustment function*
that *adds a value*, then *multiplies a value* to *old ranks*, and *sets a value*
for *new ranks*. After ranks are adjusted, they are set as *initial ranks* for
PageRank computation, which is then run on *all vertices* (no vertices are
skipped). The PageRank algorithm used is the *standard power-iteration (pull)*
based that optionally accepts *initial ranks*. The *rank* of a vertex in an
iteration is calculated as `c₀ + αΣrₑ/dₑ`, where `c₀` is the *common teleport*
*contribution*, `α` is the *damping factor (0.85)*, `rₑ` is the *previous rank*
of vertex with an incoming edge, `dₑ` is the *out-degree* of the incoming-edge
vertex, and `N` is the *total number of vertices* in the graph. The *common*
*teleport contribution* `c₀`, calculated as `(1-α)/N + αΣrₙ/N`, includes the
*contribution due to a teleport from any vertex* in the graph due to the damping
factor `(1-α)/N`, and *teleport from dangling vertices* (with *no outgoing*
*edges*) in the graph `αΣrₙ/N`. This is because a random surfer jumps to a random
page upon visiting a page with *no links*, in order to avoid the *rank-sink effect*.

All seven graphs (temporal) used in this experiment are stored in a plain
text file in `u, v, t` format, where `u` is the *source vertex*, `v` is the
*destination vertex*, and `t` is the *UNIX epoch time* in *seconds*. These
include: *CollegeMsg*, *email-Eu-core-temporal*, *sx-mathoverflow*,
*sx-askubuntu*, *sx-superuser*, *wiki-talk-temporal*, and *sx-stackoverflow*.
All of them are obtained from the *Stanford Large Network Dataset Collection*.
If *initial ranks* are *not* provided, they are set to `1/N`. *Error check*
is done using *L1 norm* with *static PageRank* (without initial ranks). The
experiment is implemented in *C++*, and compiled using *GCC 9* with
*optimization level 3 (-O3)*. The system used is a *Dell PowerEdge R740 Rack*
*server* with two *Intel Xeon Silver 4116 CPUs @ 2.10GHz*, *128GB DIMM DDR4*
*Synchronous Registered (Buffered) 2666 MHz (8x16GB) DRAM*, and running
*CentOS Linux release 7.9.2009 (Core)*. The *iterations* taken with each test
case is measured. `500` is the *maximum iterations* allowed. Statistics of
each test case is printed to *standard output (stdout)*, and redirected to a
*log file*, which is then processed with a *script* to generate a *CSV file*,
with each *row* representing the details of a *single test case*. This *CSV file*
is imported into *Google Sheets*, and necessary tables are set up with the
help of the *FILTER* function to create the *charts*.

It is observed that all of the rank adjustment strategies with incremental
PageRank perform significantly better than static PageRank, with a small
performance difference among them. However, for *large batch sizes*, *static*
*PageRank* is able to beat *all* of the rank adjustment strategies. This
is expected, since beyond a certain batch size, computing PageRank from
scratch is going to be *faster* than incremental/dynamic PageRank. On average, the
performance difference between the rank adjustment strategies *increases*
as the *batch size increases*. Both *1/N-fill*, and *scaled 1/N-fill* strategies
(having similar performance curve) require somewhat *fewer iterations* to
converge than *zero-fill*, and *scaled zero-fill* strategies (also with similar
performance curve). This is possibly because the `1/N` value for *new vertices*
is *closer* to their *actual rank value*, than `0`.

On average, *on all graphs*, both the **1/N-fill** , and **scaled 1/N-fill**
strategies seem to perform the **best**. Based on **GM-RATIO** comparison, the
*relative iterations* between *zero-fill*, *1/N-fill*, *scaled zero-fill*, and
*scaled 1/N-fill* is `1.00 : 0.96 : 1.00 : 0.96` for all batch sizes. Hence,
both *1/N-fill* and *scaled 1/N-fill* are *4% faster (1.04x)* than *zero-fill*
and *scaled zero-fill*. Here, *GM-RATIO* is obtained by taking the *geometric*
*mean (GM)* of iterations taken at different stages of the graph on all graphs,
with each specific batch size. Then, *GM* is taken for all batch sizes, and a
*ratio* is obtained *relative* to the *zero-fill* strategy. Based on **AM-RATIO**
comparison, the *relative iterations* between *zero-fill*, *1/N-fill*, *scaled*
*zero-fill*, and *scaled 1/N-fill* is `1.00 : 0.95 : 1.00 : 0.95` (all batch
sizes). Hence, both *1/N-fill* and *scaled 1/N-fill* are *5% faster (1.05x)*
than *zero-fill* and *scaled zero-fill*. *AM-RATIO* is obtained in a process
similar to that of *GM-RATIO*, except that *arithmetic mean (AM)* is used
instead of GM.

Among the four studied *rank adjustment strategies* for *incremental/dynamic PageRank*,
both **1/N-fill** and **scaled 1/N-fill** appear to be the **best**. However,
only with the *scaled 1/N-fill* strategy (also *scaled zero-fill*, but it is
*slower*), it is possible to **skip** PageRank computation on **unaffected**
**vertices** , as long as the graph has no *affected dead ends (including dead*
*ends in the old graph)*. The **scaled 1/N-fill** rank adjustment strategy,
which is commonly used for dynamic PageRank, is thus the way to go.

All outputs are saved in [gist] and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at the
[Stanford Large Network Dataset Collection]. This experiment was done with
guidance from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
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
# [04939.784 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [03615.313 ms; 041 iters.] [4.3594e-4 err.] pagerankIncremental (zero-fill)
# [03622.748 ms; 041 iters.] [4.3594e-4 err.] pagerankIncremental (1/N-fill)
# [03634.465 ms; 041 iters.] [4.3594e-4 err.] pagerankIncremental (scaled zero-fill)
# [03629.793 ms; 041 iters.] [4.3594e-4 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 5e+1
# [05160.998 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [03766.426 ms; 041 iters.] [4.3596e-4 err.] pagerankIncremental (zero-fill)
# [03782.768 ms; 041 iters.] [4.3594e-4 err.] pagerankIncremental (1/N-fill)
# [03769.523 ms; 041 iters.] [4.3596e-4 err.] pagerankIncremental (scaled zero-fill)
# [03786.383 ms; 041 iters.] [4.3594e-4 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 1e+2
# [05136.888 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [03767.514 ms; 041 iters.] [4.3596e-4 err.] pagerankIncremental (zero-fill)
# [03772.496 ms; 041 iters.] [4.3595e-4 err.] pagerankIncremental (1/N-fill)
# [03769.711 ms; 041 iters.] [4.3596e-4 err.] pagerankIncremental (scaled zero-fill)
# [03777.805 ms; 041 iters.] [4.3596e-4 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 5e+2
# [05120.352 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [03748.187 ms; 041 iters.] [4.3600e-4 err.] pagerankIncremental (zero-fill)
# [03767.701 ms; 041 iters.] [4.3600e-4 err.] pagerankIncremental (1/N-fill)
# [03762.846 ms; 041 iters.] [4.3600e-4 err.] pagerankIncremental (scaled zero-fill)
# [03764.992 ms; 041 iters.] [4.3600e-4 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 1e+3
# [05146.768 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [03765.965 ms; 041 iters.] [4.3607e-4 err.] pagerankIncremental (zero-fill)
# [03774.291 ms; 041 iters.] [4.3604e-4 err.] pagerankIncremental (1/N-fill)
# [03779.047 ms; 042 iters.] [4.3606e-4 err.] pagerankIncremental (scaled zero-fill)
# [03774.637 ms; 041 iters.] [4.3603e-4 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 5e+3
# [05090.658 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [03766.083 ms; 042 iters.] [4.3612e-4 err.] pagerankIncremental (zero-fill)
# [03786.325 ms; 042 iters.] [4.3612e-4 err.] pagerankIncremental (1/N-fill)
# [03787.047 ms; 042 iters.] [4.3613e-4 err.] pagerankIncremental (scaled zero-fill)
# [03793.852 ms; 042 iters.] [4.3611e-4 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 1e+4
# [05155.605 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [03834.611 ms; 043 iters.] [4.3615e-4 err.] pagerankIncremental (zero-fill)
# [03823.441 ms; 043 iters.] [4.3609e-4 err.] pagerankIncremental (1/N-fill)
# [03820.311 ms; 043 iters.] [4.3618e-4 err.] pagerankIncremental (scaled zero-fill)
# [03836.097 ms; 043 iters.] [4.3610e-4 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 5e+4
# [05390.391 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [04059.541 ms; 044 iters.] [4.3631e-4 err.] pagerankIncremental (zero-fill)
# [04055.194 ms; 044 iters.] [4.3610e-4 err.] pagerankIncremental (1/N-fill)
# [04082.488 ms; 044 iters.] [4.3632e-4 err.] pagerankIncremental (scaled zero-fill)
# [04086.058 ms; 044 iters.] [4.3611e-4 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 1e+5
# [05211.426 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [04012.745 ms; 045 iters.] [4.3642e-4 err.] pagerankIncremental (zero-fill)
# [04013.988 ms; 045 iters.] [4.3621e-4 err.] pagerankIncremental (1/N-fill)
# [03985.501 ms; 045 iters.] [4.3649e-4 err.] pagerankIncremental (scaled zero-fill)
# [03977.713 ms; 045 iters.] [4.3621e-4 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 5e+5
# [05750.091 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [04760.236 ms; 050 iters.] [4.3668e-4 err.] pagerankIncremental (zero-fill)
# [04721.523 ms; 049 iters.] [7.4446e-6 err.] pagerankIncremental (1/N-fill)
# [04709.357 ms; 050 iters.] [4.3679e-4 err.] pagerankIncremental (scaled zero-fill)
# [04674.002 ms; 049 iters.] [7.5238e-6 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 1e+6
# [05786.956 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [04975.434 ms; 052 iters.] [8.0893e-6 err.] pagerankIncremental (zero-fill)
# [04908.633 ms; 051 iters.] [7.8276e-6 err.] pagerankIncremental (1/N-fill)
# [04934.850 ms; 052 iters.] [8.0739e-6 err.] pagerankIncremental (scaled zero-fill)
# [04895.568 ms; 051 iters.] [7.7943e-6 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 5e+6
# [06634.203 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [06363.779 ms; 059 iters.] [7.3656e-6 err.] pagerankIncremental (zero-fill)
# [05934.904 ms; 056 iters.] [7.1436e-6 err.] pagerankIncremental (1/N-fill)
# [06161.640 ms; 059 iters.] [7.3794e-6 err.] pagerankIncremental (scaled zero-fill)
# [05859.559 ms; 056 iters.] [7.0833e-6 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 1e+7
# [07038.214 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [06738.821 ms; 062 iters.] [6.3339e-6 err.] pagerankIncremental (zero-fill)
# [06499.542 ms; 057 iters.] [6.1972e-6 err.] pagerankIncremental (1/N-fill)
# [07009.660 ms; 062 iters.] [6.3312e-6 err.] pagerankIncremental (scaled zero-fill)
# [06591.503 ms; 057 iters.] [6.0978e-6 err.] pagerankIncremental (scaled 1/N-fill)
#
# # Batch size 5e+7
# [08794.845 ms; 058 iters.] [0.0000e+0 err.] pagerankStatic
# [10055.872 ms; 068 iters.] [5.8015e-6 err.] pagerankIncremental (zero-fill)
# [08454.233 ms; 059 iters.] [3.6083e-6 err.] pagerankIncremental (1/N-fill)
# [09482.630 ms; 068 iters.] [5.8012e-6 err.] pagerankIncremental (scaled zero-fill)
# [08932.575 ms; 059 iters.] [3.5756e-6 err.] pagerankIncremental (scaled 1/N-fill)
```

[![](https://i.imgur.com/2By6cGN.gif)][sheetp]
[![](https://i.imgur.com/1BT8w4v.gif)][sheetp]

[![](https://i.imgur.com/CBqjWKE.gif)][sheetp]
[![](https://i.imgur.com/57mx2Jb.gif)][sheetp]

[![](https://i.imgur.com/nqox5b5.gif)][sheetp]
[![](https://i.imgur.com/KM6X4W4.gif)][sheetp]

[![](https://i.imgur.com/6MVyhyn.gif)][sheetp]
[![](https://i.imgur.com/wiL56Ng.gif)][sheetp]

[![](https://i.imgur.com/w2BQGK6.gif)][sheetp]
[![](https://i.imgur.com/7i9Y5ks.gif)][sheetp]

[![](https://i.imgur.com/M4RTnro.gif)][sheetp]
[![](https://i.imgur.com/wBzMpnv.gif)][sheetp]

[![](https://i.imgur.com/OGeMEhH.gif)][sheetp]
[![](https://i.imgur.com/8xP9PrJ.gif)][sheetp]

[![](https://i.imgur.com/5Uax3lK.png)][sheetp]
[![](https://i.imgur.com/b9sjkvD.png)][sheetp]
[![](https://i.imgur.com/mDfuwQw.png)][sheetp]
[![](https://i.imgur.com/DLxadcA.png)][sheetp]

[![](https://i.imgur.com/b2mqXR2.png)][sheetp]
[![](https://i.imgur.com/WAtYv2H.png)][sheetp]
[![](https://i.imgur.com/yhQFuXv.png)][sheetp]
[![](https://i.imgur.com/pW8H4Bx.png)][sheetp]

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/xYJUQbm.jpg)](https://www.youtube.com/watch?v=tIybKX2NKeo)
[![ORG](https://img.shields.io/badge/org-puzzlef-green?logo=Org)](https://puzzlef.github.io)
[![DOI](https://zenodo.org/badge/367267258.svg)](https://zenodo.org/badge/latestdoi/367267258)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[gist]: https://gist.github.com/wolfram77/57d8f58a7becbc0685cfeb9f533d721c
[charts]: https://photos.app.goo.gl/7vjL6WDN5hY8wWjM9
[sheets]: https://docs.google.com/spreadsheets/d/1MAdwqlAEhYf5EXF3B6ahVvztS*vQt0nT*MBK2xOYl2w/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vSAvNX3h6-oDrvrNG2*fTLFVk32mnzAI2PSXt2WN34zKSjNRxPyQwY84hc2zPzL9mNGnFDYn3cSCkZd/pubhtml
