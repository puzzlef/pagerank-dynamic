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
auto runPagerankCall(const char *name, const G& xt, const vector<T> *init, const vector<T> *ranks=nullptr) {
  int repeat = 5;
  auto a = pagerankSeq(xt, init, {repeat});
  auto e = absError(a.ranks, ranks? *ranks : a.ranks);
  print(xt); printf(" [%09.3f ms; %03d iters.] [%.4e err.] %s\n", a.time, a.iterations, e, name);
  return a;
}


void runPagerankBatch(const string& data, bool show, int batch) {
  vector<float>  ranksOld, ranksAdj;
  vector<float> *initStatic  = nullptr;
  vector<float> *initDynamic = &ranksAdj;

  DiGraph<> x;
  stringstream s(data);
  auto ksOld = vertices(x);
  while(readSnapTemporal(x, s, batch)) {
    auto ks = vertices(x);
    auto xt = transposeWithDegree(x);
    ranksAdj.resize(x.span());

    // Find static pagerank of updated graph.
    auto a1 = runPagerankCall("pagerankStatic", xt, initStatic);

    // Find dynamic pagerank, using zero-fill for new vertices.
    adjustRanks(ranksAdj, ranksOld, ksOld, ks, 0.0f, 1.0f, 0.0f);
    auto a2 = runPagerankCall("pagerankDynamic (zero-fill)", xt, initDynamic, &a1.ranks);

    // Find dynamic pagerank, using 1/N for new vertices.
    adjustRanks(ranksAdj, ranksOld, ksOld, ks, 0.0f, 1.0f, 1.0f/ks.size());
    auto a3 = runPagerankCall("pagerankDynamic (1/N-fill)", xt, initDynamic, &a1.ranks);

    // Find dynamic pagerank, scaling old vertices, and using 1/N for new vertices.
    adjustRanks(ranksAdj, ranksOld, ksOld, ks, 0.0f, float(ksOld.size())/ks.size(), 1.0f/ks.size());
    auto a4 = runPagerankCall("pagerankDynamic (scaled,1/N-fill)", xt, initDynamic, &a1.ranks);

    ksOld = move(ks);
    ranksOld = move(a2.ranks);
  }
}


void runPagerank(const string& data, bool show) {
  int M = countLines(data);
  printf("Temporal edges: %d\n\n", M);
  for (int batch=int(pow(10, int(log10(M)))); batch>=1000; batch/=10) {
    printf("# Batch size %.0e\n", (double) batch);
    runPagerankBatch(data, show, batch);
    printf("\n");
  }
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runPagerank(d, show);
  return 0;
}
