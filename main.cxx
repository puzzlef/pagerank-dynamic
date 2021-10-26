#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <utility>
#include "src/main.hxx"

using namespace std;



template <class G, class T>
void printRow(const G& x, const PagerankResult<T>& a, const PagerankResult<T>& b, const char *tec) {
  auto e = l1Norm(b.ranks, a.ranks);
  print(x); printf(" [%09.3f ms; %03d iters.] [%.4e err.] %s\n", b.time, b.iterations, e, tec);
}


void runPagerankBatch(const string& data, int repeat, int skip, int batch) {
  vector<float>  r0, r1;
  vector<float> *init = nullptr;

  DiGraph<> x;
  stringstream s(data);
  while (true) {
    // Skip some edges (to speed up execution)
    if (skip>0 && !readSnapTemporal(x, s, skip)) break;
    auto  k0 = vertices(x); size_t K0 = k0.size();
    auto  a0 = pagerankTeleport(x, init, {repeat});
    auto& r0 = a0.ranks;

    // Read edges for this batch.
    auto y = copy(x);
    if (!readSnapTemporal(y, s, batch)) break;
    auto k1 = vertices(y); size_t K1 = k1.size();
    r1.resize(y.span());

    // Find static pagerank of updated graph.
    auto a1 = pagerankTeleport(y, init, {repeat});
    printRow(y, a1, a1, "pagerankStatic");

    // Find incremental pagerank, using zero for new vertices.
    adjustRanks(r1, r0, k0, k1, 0.0f, 1.0f, 0.0f);
    auto a2 = pagerankTeleport(y, &r1, {repeat});
    printRow(y, a1, a2, "pagerankIncremental (zero-fill)");

    // Find incremental pagerank, using 1/N for new vertices.
    adjustRanks(r1, r0, k0, k1, 0.0f, 1.0f, 1.0f/K1);
    auto a3 = pagerankTeleport(y, &r1, {repeat});
    printRow(y, a1, a3, "pagerankIncremental (1/N-fill)");

    // Find incremental pagerank, scaling old vertices, and using zero for new vertices.
    adjustRanks(r1, r0, k0, k1, 0.0f, float(K0)/K1, 0.0f);
    auto a4 = pagerankTeleport(y, &r1, {repeat});
    printRow(y, a1, a4, "pagerankIncremental (scaled zero-fill)");

    // Find incremental pagerank, scaling old vertices, and using 1/N for new vertices.
    adjustRanks(r1, r0, k0, k1, 0.0f, float(K0)/K1, 1.0f/K1);
    auto a5 = pagerankTeleport(y, &r1, {repeat});
    printRow(y, a1, a5, "pagerankIncremental (scaled 1/N-fill)");

    // New graph is now old.
    x = move(y);
  }
}


void runPagerank(const string& data, int repeat) {
  int M = countLines(data), steps = 100;
  printf("Temporal edges: %d\n", M);
  for (int batch=10, i=0; batch<M; batch*=i&1? 2:5, i++) {
    int skip = max(M/steps - batch, 0);
    printf("\n# Batch size %.0e\n", (double) batch);
    runPagerankBatch(data, repeat, skip, batch);
  }
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int repeat = argc>2? stoi(argv[2]) : 5;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runPagerank(d, repeat);
  printf("\n");
  return 0;
}
