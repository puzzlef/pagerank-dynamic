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
The input data used for this experiment is available at ["graphs"] (for small
ones), and the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/email-Eu-core-temporal.txt

# (SHORTENED)
# Using graph email-Eu-core-temporal.txt ...
# ...
```

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/wiki-talk-temporal.txt

# (SHORTENED)
# Using graph wiki-talk-temporal.txt ...
# ...
```

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/sNyLL3K.jpg)](https://www.youtube.com/watch?v=SoiKp2oSUl0)

[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
