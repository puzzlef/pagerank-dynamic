Comparing strategies to **update ranks** for **dynamic PageRank** ([pull], [CSR]).

This experiment was for comparing the performance between:
1. Find **static** pagerank of updated graph.
2. Find **dynamic** pagerank, using **zero-fill**.
3. Find **dynamic** pagerank, using **1/N-fill**.
4. Find **dynamic** pagerank, using **scaled zero-fill**.
5. Find **dynamic** pagerank, using **scaled 1/N-fill**.

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
with a factor of `N₀/N₁` (i.e. `r₁ = r₀ × N₀/N₁` for old vertices, and `r₁ = 1/N₁`
for new vertices). Finally, the **scaled 1/N-fill** strategy is a combination
of *scaling old vertices*, and *1/N-fill* (i.e. `r₁ = r₀ × N₀/N₁` for old
vertices, and `r₁ = 1/N₁` for new vertices). Here, `N₁` is the *total number of*
*vertices*, and `r₀` is the *rank of a given vertex* in the *old graph*. On
the other hand, `N₁` is the *total number of vertices*, and `r₁` is the *rank*
*of a given vertex* in the *updated graph*.

For *static PageRank* computation of a graph, the *initial ranks* of all
vertices are set to `1/N`, where `N` is the *total number of vertices* in the
graph. Therefore, the *sum* of all *initial ranks* equals `1`, as it should
for a *probability (rank) vector*. It is important to note however that this
is *not* an *essential condition*, rather, it likely helps with faster
convergence.

With scaled rank adjustment strategies, unlike unscaled ones, PageRank
computation on *unaffected vertices* can be **skipped** , as long as the
graph has no *affected dead ends (including dead ends in the old graph)*.
*Scaling* is *necessary*, because even though the *importance* of
*unaffected vertices* does not change, the *final rank vector* is a
*probabilistic vector* and *must sum to* `1`. Here, *affected vertices* are
those which are either *changed vertices*, or are *reachable* from changed
vertices. *Changed vertices* are those which have an edge added or removed
between it and another (changed) vertex.

An experiment is conducted with each *rank adjustment strategy* on various
*temporal graphs*, updating each graph with multiple batch sizes (`10³`, `10⁴`,
...), until the entire graph is processed. For each batch size, *static*
*PageRank* is computed, along with *incremental PageRank* based on each of the
four rank adjustment strategies, *without skipping unaffected vertices*. This
is done in order to get an estimate of the *convergence rate* of each *rank*
*adjustment strategy*, *independent* of the *number of skipped vertices* (which
can *differ* based on the *dead end handling strategy* used).

Each rank adjustment strategy is performed using a *common adjustment function*
that *adds a value*, then *multiplies a value* to *old ranks*, and *sets a value*
for *new ranks*. After ranks are adjusted, they are set as *initial ranks* for
PageRank computation, which is then run on *all vertices* (no vertices are
skipped). The PageRank algorithm used is the *standard* *power-iteration (pull)*
based that optionally accepts *initial ranks*. The *rank* of a vertex in an
iteration is calculated as `c₀ + αΣrₙ/dₙ`, where `c₀` is the *common teleport*
*contribution*, `α` is the *damping factor (0.85)*, `rₙ` is the *previous rank*
of vertex with an incoming edge, `dₙ` is the *out-degree* of the incoming-edge
vertex, and `N` is the *total number of vertices* in the graph. The *common*
*teleport contribution* `c₀`, calculated as `(1-α)/N + αΣrₙ/N`, includes the
*contribution due to a teleport from any vertex* in the graph due to the damping
factor `(1-α)/N`, and *teleport from dangling vertices* (with *no outgoing edges*)
in the graph `αΣrₙ/N`. This is because a random surfer jumps to a random page
upon visiting a page with *no links*, in order to avoid the *rank-sink effect*.

All seven graphs (temporal) used in this experiment are stored in a plain text
file in `u, v, t` format, where `u` is the *source vertex*, `v` is the
*destination vertex*, and `t` is the *UNIX epoch time* in *seconds*. These
include: *CollegeMsg*, *email-Eu-core-temporal*, *sx-mathoverflow*, *sx-askubuntu*,
*sx-superuser*, *wiki-talk-temporal*, and *sx-stackoverflow*. All of them are
obtained from the *Stanford Large Network Dataset Collection*. If *initial ranks*
are *not* provided, they are set to `1/N`. *Error check* is done using *L1 norm*
with *static PageRank* (without initial ranks). The experiment is implemented in
*C++*, and compiled using *GCC 9* with *optimization level 3 (-O3)*. The system
used is a *Dell PowerEdge R740 Rack server* with two *Intel Xeon Silver 4116 CPUs*
*@ 2.10GHz*, *128GB DIMM DDR4 Synchronous Registered (Buffered) 2666 MHz (8x16GB)*
*DRAM*, and running *CentOS Linux release 7.9.2009 (Core)*. The *iterations* taken
with each test case is measured. *500* is the *maximum iterations* allowed.
Statistics of each test case is printed to *standard output (stdout)*, and redirected
to a *log file*, which is then processed with a *script* to generate a *CSV file*,
with each *row* representing the details of a *single test case*. This *CSV file*
is imported into *Google Sheets*, and necessary tables are set up with the help of
the *FILTER* function to create the *charts*.

It is observed that *1/N-fill* and *scaled zero-fill* strategies tend to require
more iterations for convergence for all graphs, with the *1/N-fill* strategy
usually performing the worst. For *small temporal graphs*, such as *CollegeMsg*
and *email-Eu-core-temporal*, the two strategies are *almost always slower* than
*static PageRank*. This is possibly because the sum of ranks with both the
strategies *does not sum up to 1*. For *larger graphs* this is usually not the
case for *smaller batch sizes*. However, for *large batch sizes*, *static PageRank*
is able to beat *all* of the rank adjustment strategies. This is expected, since
beyond a certain batch size, computing PageRank from scratch is going to be
*faster* than dynamic PageRank.

On average, *on all graphs*, the **scaled 1/N-fill** strategy seems to perform
the **best**. Based on **GM-RATIO** comparison, the *relative iterations*
between *zero-fill*, *1/N-fill*, *scaled zero-fill*, and *scaled 1/N-fill* is
**1.00 : 1.07 : 1.10 : 0.93** for all batch sizes. Hence, *1/N-fill* is
*3% faster (1.03x)* than *scaled zero-fill*, *zero-fill* is *7% faster (1.07x)*
than *1/N-fill*, and *scaled 1/N-fill* is *7% faster (1.08x)* than *zero-fill*.
Here, *GM-RATIO* is obtained by taking the *geometric mean (GM)* of iterations
taken at different stages of the graph, on each graph, with each batch size.
Then, *GM* is taken for each batch size, across all graphs. Finally, *GM* is
taken for all batch sizes, and a *ratio* is obtained *relative* to the *zero-fill*
strategy. Based on **AM-RATIO** comparison , the *relative iterations* between
*zero-fill*, *1/N-fill*, *scaled zero-fill*, and *scaled 1/N-fill* is
**1.00 : 1.03 : 1.07 : 0.92** (all batch sizes). Hence, *1/N-fill* is
*4% faster (1.04x)* than *scaled zero-fill*, *zero-fill* is *3% faster (1.03x)*
than *1/N-fill*, and *scaled 1/N-fill* is *8% faster (1.09x)* than *zero-fill*.
*AM-RATIO* is obtained in a process similar to that of *GM-RATIO*, except that
*arithmetic mean (AM)* is used instead of GM.

All outputs are saved in [out](out/) and a small part of the output is listed
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
# Using graph wiki-talk-temporal.txt ...
# Temporal edges: 7833141
# order: 1140149 size: 3309592 {}
#
# # Batch size 1e+6
# [00395.797 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00453.499 ms; 066 iters.] [7.1507e-6 err.] pagerankDynamic (zero-fill)
# [00468.554 ms; 066 iters.] [7.2686e-6 err.] pagerankDynamic (1/N-fill)
# [00468.014 ms; 068 iters.] [1.0144e-3 err.] pagerankDynamic (scaled,zero-fill)
# [00420.007 ms; 060 iters.] [5.8216e-6 err.] pagerankDynamic (scaled,1/N-fill)
#
# # Batch size 1e+5
# [00335.793 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00313.070 ms; 054 iters.] [4.7299e-4 err.] pagerankDynamic (zero-fill)
# [00333.001 ms; 057 iters.] [8.3215e-6 err.] pagerankDynamic (1/N-fill)
# [00319.527 ms; 056 iters.] [6.2674e-4 err.] pagerankDynamic (scaled,zero-fill)
# [00299.217 ms; 051 iters.] [1.0181e-4 err.] pagerankDynamic (scaled,1/N-fill)
#
# # Batch size 1e+4
# [00327.667 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00223.278 ms; 040 iters.] [1.6293e-4 err.] pagerankDynamic (zero-fill)
# [00237.262 ms; 043 iters.] [8.4152e-6 err.] pagerankDynamic (1/N-fill)
# [00232.948 ms; 042 iters.] [3.1093e-4 err.] pagerankDynamic (scaled,zero-fill)
# [00214.799 ms; 038 iters.] [7.3679e-5 err.] pagerankDynamic (scaled,1/N-fill)
#
# # Batch size 1e+3
# [00337.526 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00139.943 ms; 026 iters.] [4.0339e-5 err.] pagerankDynamic (zero-fill)
# [00145.916 ms; 028 iters.] [1.1269e-5 err.] pagerankDynamic (1/N-fill)
# [00151.074 ms; 027 iters.] [6.3871e-5 err.] pagerankDynamic (scaled,zero-fill)
# [00135.772 ms; 024 iters.] [2.9000e-5 err.] pagerankDynamic (scaled,1/N-fill)
#
# ...
```

[![](https://i.imgur.com/xxdjWrl.png)][sheetp]
[![](https://i.imgur.com/vbfc9dq.png)][sheetp]
[![](https://i.imgur.com/UvhUly1.png)][sheetp]
[![](https://i.imgur.com/0baQPMn.png)][sheetp]

[![](https://i.imgur.com/TCoW86O.png)][sheetp]
[![](https://i.imgur.com/tpcvd1F.png)][sheetp]
[![](https://i.imgur.com/t84Mmbq.png)][sheetp]
[![](https://i.imgur.com/vzcbS53.png)][sheetp]

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/sNyLL3K.jpg)](https://www.youtube.com/watch?v=SoiKp2oSUl0)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/7vjL6WDN5hY8wWjM9
[sheets]: https://docs.google.com/spreadsheets/d/1ABVf_qu8h8_7OE2X1WbVo9vI95kSPtRr5LB2_7OAMSo/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vTwEBQV2eB895vLkDkXLsXzdtPbDz62ppJKn6B9-FEJBAB2-1wymqyzTVCFGtSZOUO6FCrA7ihPm5Lw/pubhtml
