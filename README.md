Design of **Dynamic** *PageRank algorithm* for link analysis.

All seven graphs (temporal) used in our experiments are stored in a plain
text file in `u, v, t` format, where `u` is the *source vertex*, `v` is the
*destination vertex*, and `t` is the *UNIX epoch time* in *seconds*. These
include: *CollegeMsg*, *email-Eu-core-temporal*, *sx-mathoverflow*,
*sx-askubuntu*, *sx-superuser*, *wiki-talk-temporal*, and *sx-stackoverflow*.
We obtained them from the [Stanford Large Network Dataset Collection].
If *initial ranks* are *not* provided, they are set to `1/N`. *Error check*
is done using *L1 norm* with *static PageRank* (without initial ranks). The
experiment is implemented in *C++*, and compiled using *GCC 9* with
*optimization level 3 (-O3)*. The system we use is a *Dell PowerEdge R740 Rack*
*server* with two *Intel Xeon Silver 4116 CPUs @ 2.10GHz*, *128GB DIMM DDR4*
*Synchronous Registered (Buffered) 2666 MHz (8x16GB) DRAM*, and running
*CentOS Linux release 7.9.2009 (Core)*. The *iterations* taken with each test
case is measured. `500` is the *maximum iterations* allowed. We print the
statistics of each test case to *standard output (stdout)*, and redirect to a
*log file*, which we then process with a *script* to generate a *CSV file*,
with each *row* representing the details of a *single test case*. This *CSV file*
is imported into *Google Sheets*, and necessary tables are set up with the
help of the *FILTER* function to create the *charts*.

<br>


### Comparing strategies to Update ranks

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

We conduct an experiment ([adjust-ranks]) with each *rank adjustment strategy*
on various *temporal graphs*, updating each graph with multiple batch sizes
(10¹, 5×10¹, 10², ...), until the entire graph is processed. For each batch
size, *static PageRank* is computed, along with *incremental PageRank* based on
each of the four rank adjustment strategies, *without skipping unaffected*
*vertices*. This is done in order to get an estimate of the *convergence rate* of
each *rank adjustment strategy*, *independent* of the *number of skipped*
*vertices* (which can *differ* based on the *dead end handling strategy* used).

We perform each rank adjustment strategy using a *common adjustment function*
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

From the results, We observe that all of the rank adjustment strategies with
incremental PageRank perform significantly better than static PageRank, with a
small performance difference among them. However, for *large batch sizes*,
*static PageRank* is able to beat *all* of the rank adjustment strategies. This
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

[adjust-ranks]: https://github.com/puzzlef/pagerank-dynamic/tree/adjust-ranks

<br>


### Comparison with Static approach

In this experiment ([compare-static]), we compare the performance between
finding *static* and *dynamic* PageRank of updated graph. Both approaches are
attempted on a number of temporal graphs, running each with multiple batch sizes
(`1`, `5`, `10`, `50`, ...). New edges are incrementally added to the graph
batch-by-batch until the entire graph is complete. **Dynamic PageRank** is
clearly **faster** than *static PageRank* for most cases. All outputs are saved
in [gist]. Some [charts] are also included below, generated from [sheets].

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

[compare-static]: https://github.com/puzzlef/pagerank-dynamic-tofu/tree/compare-static

<br>


### Other experiments

- [measure-tolerance](https://github.com/puzzlef/pagerank-dynamic-tofu/tree/measure-tolerance)

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [Stanford Large Network Dataset Collection]

<br>
<br>


[![](https://i.imgur.com/0TfMELc.jpg)](https://www.youtube.com/watch?v=tIybKX2NKeo)
[![ORG](https://img.shields.io/badge/org-puzzlef-green?logo=Org)](https://puzzlef.github.io)
[![DOI](https://zenodo.org/badge/367267258.svg)](https://zenodo.org/badge/latestdoi/367267258)
![](https://ga-beacon.deno.dev/G-KD28SG54JQ:hbAybl6nQFOtmVxW4if3xw/github.com/puzzlef/pagerank-dynamic)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://faculty.iiit.ac.in/~kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu/
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[pull]: https://github.com/puzzlef/pagerank
[CSR]: https://github.com/puzzlef/pagerank
[gist]: https://gist.github.com/wolfram77/d07a9ebe2e5517b7397cdffb26e8c7ce
[charts]: https://photos.app.goo.gl/dcQWY7z1HEdPAqre8
[sheets]: https://docs.google.com/spreadsheets/d/1b6fuE9dRbAbQanCl2rDXc-K2xpIUSg7Mw_dzVnFbkD8/edit?usp=sharing
