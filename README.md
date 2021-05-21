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
# # Batch size 1e+0
# [00000.498 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.032 ms; 002 iters.] [6.4766e-7 err.] pagerankDynamic
#
# # Batch size 5e+0
# [00000.510 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.065 ms; 003 iters.] [1.0864e-6 err.] pagerankDynamic
#
# # Batch size 1e+1
# [00000.501 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.098 ms; 005 iters.] [1.5461e-6 err.] pagerankDynamic
#
# # Batch size 5e+1
# [00000.503 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.218 ms; 011 iters.] [2.4047e-6 err.] pagerankDynamic
#
# # Batch size 1e+2
# [00000.502 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.251 ms; 014 iters.] [2.4436e-6 err.] pagerankDynamic
#
# # Batch size 5e+2
# [00000.499 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.308 ms; 016 iters.] [2.5226e-6 err.] pagerankDynamic
#
# # Batch size 1e+3
# [00000.501 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.336 ms; 018 iters.] [2.4926e-6 err.] pagerankDynamic
#
# # Batch size 5e+3
# [00000.509 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.391 ms; 020 iters.] [2.3684e-6 err.] pagerankDynamic
#
# # Batch size 1e+4
# [00000.518 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.415 ms; 022 iters.] [2.1345e-6 err.] pagerankDynamic
#
# # Batch size 5e+4
# [00000.530 ms; 024 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.481 ms; 022 iters.] [1.6988e-6 err.] pagerankDynamic
#
# # Batch size 1e+5
# [00000.577 ms; 024 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.541 ms; 022 iters.] [1.5049e-6 err.] pagerankDynamic
```

[![](https://i.imgur.com/TmvAX7l.png)][cool charts]
[![](https://i.imgur.com/5vUMTH3.png)][cool charts]

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
# # Batch size 1e+0
# [00340.903 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00009.966 ms; 002 iters.] [1.1367e-6 err.] pagerankDynamic
#
# # Batch size 5e+0
# [00341.358 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00018.500 ms; 004 iters.] [2.8356e-6 err.] pagerankDynamic
#
# # Batch size 1e+1
# [00340.824 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00024.168 ms; 005 iters.] [5.3977e-6 err.] pagerankDynamic
#
# # Batch size 5e+1
# [00341.422 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00046.705 ms; 010 iters.] [9.2519e-6 err.] pagerankDynamic
#
# # Batch size 1e+2
# [00342.834 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00060.702 ms; 012 iters.] [9.8899e-6 err.] pagerankDynamic
#
# # Batch size 5e+2
# [00338.967 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00109.049 ms; 020 iters.] [2.7572e-5 err.] pagerankDynamic
#
# # Batch size 1e+3
# [00338.164 ms; 055 iters.] [0.0000e+0 err.] pagerankStatic
# [00131.742 ms; 024 iters.] [9.9510e-6 err.] pagerankDynamic
#
# # Batch size 5e+3
# [00343.487 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00193.201 ms; 034 iters.] [6.7188e-5 err.] pagerankDynamic
#
# # Batch size 1e+4
# [00341.069 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00220.372 ms; 038 iters.] [3.3175e-4 err.] pagerankDynamic
#
# # Batch size 5e+4
# [00344.286 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00278.292 ms; 047 iters.] [8.0925e-5 err.] pagerankDynamic
#
# # Batch size 1e+5
# [00345.874 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00307.791 ms; 051 iters.] [1.0181e-4 err.] pagerankDynamic
#
# # Batch size 5e+5
# [00372.870 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00381.515 ms; 058 iters.] [7.1419e-6 err.] pagerankDynamic
#
# # Batch size 1e+6
# [00404.854 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00431.128 ms; 060 iters.] [5.8216e-6 err.] pagerankDynamic
#
# # Batch size 5e+6
# [00663.725 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# [00691.425 ms; 059 iters.] [2.5494e-6 err.] pagerankDynamic
```

[![](https://i.imgur.com/D49BRLA.png)][cool charts]
[![](https://i.imgur.com/IESSIQ9.png)][cool charts]

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
[cool charts]: https://docs.google.com/spreadsheets/d/1b6fuE9dRbAbQanCl2rDXc-K2xpIUSg7Mw_dzVnFbkD8/edit?usp=sharing
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
