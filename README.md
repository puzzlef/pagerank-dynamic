Performance of static vs dynamic PageRank ([pull], [CSR], [scaled-fill]).

This experiment was for comparing the performance between:
1. Find static pagerank of updated graph.
2. Find dynamic pagerank, **scaling** old vertices, and using **1/N** for new vertices.

Both techniques were attempted on different temporal graphs, updating each
graph with multiple batch sizes. Batch sizes are always an order of 10. New
edges are incrementally added to the graph batch-by-batch until the entire
graph is complete. The speedup of dynamic pagerank tends to **~2x** of static
pagerank when batch size is **1000**. I was able to get [cool charts] for these
huge logs, showing the comparision.

All outputs (including shortened versions) are saved in [out/](out/) and
outputs for `email-Eu-core-temporal` and `wiki-talk-temporal` are listed here.
The input data used for this experiment is available at ["graphs"] (for small
ones), and the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/email-Eu-core-temporal.txt

# (SHORTENED)
# Using graph email-Eu-core-temporal.txt ...
# Temporal edges: 332335
# order: 986 size: 24929 {}
#
# # Batch size 1e+5
# [00000.564 ms; 024 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.528 ms; 022 iters.] [1.5042e-6 err.] pagerankDynamic
#
# # Batch size 1e+4
# [00000.504 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.404 ms; 022 iters.] [2.1353e-6 err.] pagerankDynamic
#
# # Batch size 1e+3
# [00000.490 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.329 ms; 018 iters.] [2.6096e-6 err.] pagerankDynamic
```

[![](https://i.imgur.com/r41PgWd.png)][cool charts]

<br>
<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/wiki-talk-temporal.txt

# (SHORTENED)
# Using graph wiki-talk-temporal.txt ...
# Temporal edges: 7833141
# order: 1140149 size: 3309592 {}
#
# # Batch size 1e+6
# [00408.373 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00435.189 ms; 060 iters.] [5.8216e-6 err.] pagerankDynamic
#
# # Batch size 1e+5
# [00360.306 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00319.501 ms; 051 iters.] [1.0180e-4 err.] pagerankDynamic
#
# # Batch size 1e+4
# [00338.425 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00220.896 ms; 038 iters.] [7.3697e-5 err.] pagerankDynamic
#
# # Batch size 1e+3
# [00347.279 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00139.173 ms; 024 iters.] [3.1690e-5 err.] pagerankDynamic
```

[![](https://i.imgur.com/sVzmhnz.png)][cool charts]

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/0TfMELc.jpg)](https://www.youtube.com/watch?v=npl0o3X7NTA)

[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[cool charts]: https://docs.google.com/spreadsheets/d/1avE7QFCxFSRJw2dr6A5QeX8rSQxSKr10CE8_IiHCBdk/edit?usp=sharing
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
