#pragma once
#include <string>
#include <vector>
#include <istream>
#include <sstream>

using std::string;
using std::vector;
using std::istream;
using std::stringstream;
using std::getline;




// READ-SNAP-TEMPORAL
// ------------------

template <class G>
bool readSnapTemporalLine(G& a, const string& ln, bool sym=false) {
  int u, v, t;
  stringstream ls(ln);
  if (!(ls >> u >> v >> t)) return false;
  a.addEdge(u, v);
  if (sym) a.addEdge(v, u);
  return true;
}


template <class G>
void readSnapTemporal(G& a, istream& s, int N, bool sym=false) {
  for (int i=0; i<N; i++) {
    string ln; getline(s, ln);
    if (!readSnapTemporalLine(a, ln, sym)) break;
  }
}
