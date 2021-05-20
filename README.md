Comparing strategies to update ranks for dynamic PageRank ([pull], [CSR]).

This experiment was for comparing the performance between:
1. Find static pagerank of updated graph.
2. Find dynamic pagerank, using **zero-fill** for new vertices.
3. Find dynamic pagerank, using **1/N** for new vertices.
4. Find dynamic pagerank, **scaling** old vertices, and using **1/N** for new vertices.

Each technique was attempted on different temporal graphs, updating each graph
with multiple batch sizes. Batch sizes are always an order of 10. For each
batch size, static as well as the 3 dynamic rank adjust methods are tested.
Each rank adjust method (for dynamic pagerank) can have a different number
of iterations to convergence. The **4th approach**, which does **scaling**
and uses **1/N** for new vertices seems to perform best. It is also seen
that as batch size increases, the convergence iterations (time) of dynamic
pagerank increases. In some cases it even becomes slower than static pagerank.

All outputs (including shortened versions) are saved in [out/](out/) and
outputs for `email-Eu-core-temporal` and `wiki-talk-temporal` are listed here.
The input data used for this experiment is available at the
[Stanford Large Network Dataset Collection].

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
# [00000.578 ms; 024 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.756 ms; 035 iters.] [3.2327e-6 err.] pagerankDynamic (zero-fill)
# [00001.202 ms; 048 iters.] [3.8549e-6 err.] pagerankDynamic (1/N-fill)
# [00000.534 ms; 022 iters.] [1.5243e-6 err.] pagerankDynamic (scaled,1/N-fill)
#
# # Batch size 1e+4
# [00000.501 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.412 ms; 023 iters.] [2.5338e-6 err.] pagerankDynamic (zero-fill)
# [00000.869 ms; 045 iters.] [5.0035e-6 err.] pagerankDynamic (1/N-fill)
# [00000.442 ms; 022 iters.] [2.1339e-6 err.] pagerankDynamic (scaled,1/N-fill)
#
# # Batch size 1e+3
# [00000.487 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.327 ms; 018 iters.] [2.7722e-6 err.] pagerankDynamic (zero-fill)
# [00000.499 ms; 027 iters.] [3.8160e-6 err.] pagerankDynamic (1/N-fill)
# [00000.325 ms; 018 iters.] [2.6078e-6 err.] pagerankDynamic (scaled,1/N-fill)
```

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
# [00394.073 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00453.070 ms; 066 iters.] [7.1507e-6 err.] pagerankDynamic (zero-fill)
# [00468.710 ms; 066 iters.] [7.2686e-6 err.] pagerankDynamic (1/N-fill)
# [00422.879 ms; 060 iters.] [5.8216e-6 err.] pagerankDynamic (scaled,1/N-fill)
#
# # Batch size 1e+5
# [00335.164 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00310.921 ms; 054 iters.] [4.7300e-4 err.] pagerankDynamic (zero-fill)
# [00331.087 ms; 057 iters.] [8.3190e-6 err.] pagerankDynamic (1/N-fill)
# [00296.468 ms; 051 iters.] [1.0178e-4 err.] pagerankDynamic (scaled,1/N-fill)
#
# # Batch size 1e+4
# [00326.888 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00220.635 ms; 040 iters.] [1.6347e-4 err.] pagerankDynamic (zero-fill)
# [00235.016 ms; 043 iters.] [8.4288e-6 err.] pagerankDynamic (1/N-fill)
# [00212.356 ms; 038 iters.] [7.3709e-5 err.] pagerankDynamic (scaled,1/N-fill)
#
# # Batch size 1e+3
# [00341.327 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# [00140.240 ms; 026 iters.] [4.5626e-5 err.] pagerankDynamic (zero-fill)
# [00145.631 ms; 027 iters.] [1.5023e-5 err.] pagerankDynamic (1/N-fill)
# [00136.688 ms; 024 iters.] [3.5643e-5 err.] pagerankDynamic (scaled,1/N-fill)
```

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/sNyLL3K.jpg)](https://www.youtube.com/watch?v=SoiKp2oSUl0)

[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
