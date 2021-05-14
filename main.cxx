#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




void runPagerankBatch(const string& data, bool show, int batch) {
  int repeat = 5;
  vector<float>  ranksOld, ranks;
  vector<float> *initStatic  = nullptr;
  vector<float> *initDynamic = &ranks;

  DiGraph<> x;
  stringstream s(data);
  auto ksOld = vertices(x);
  while(readSnapTemporal(x, s, batch)) {
    auto ks = vertices(x);
    auto xt = transposeWithDegree(x);
    ranks.resize(x.span());
    adjustRanks(ranks, ks, ranksOld, ksOld, 0.0f, 1.0f, 0.0f);

    // Find pagerank of updated graph without using initial ranks (static).
    auto a1 = pagerankSeq(xt, initStatic, {repeat});
    auto e1 = absError(a1.ranks, a1.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankStatic\n", a1.time, a1.iterations, e1);
    if (show) println(a1.ranks);

    // Find pagerank of updated graph using initial ranks (dynamic).
    auto a2 = pagerankSeq(xt, initDynamic, {repeat});
    auto e2 = absError(a2.ranks, a1.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankDynamic\n", a2.time, a2.iterations, e2);
    if (show) println(a2.ranks);

    copy(ranksOld, a2.ranks);
  }
}


void runPagerank(const string& data, bool show) {
  int M = countLines(data);
  for (int batch=100; batch<M; batch*=10)
    runPagerankBatch(data, show, batch);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runPagerank(d, show);
  printf("\n");
  return 0;
}
