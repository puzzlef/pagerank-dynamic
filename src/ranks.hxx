#pragma once
#include "_main.hxx"




// ADJUST-RANKS
// ------------

template <class T, class J>
void adjustRanks(vector<T>& a, J&& ks, const vector<T>& r, J&& rks, T radd, T rmul, T rset) {
  auto ksNew = setDifference(ks, rks);
  fill(a, T());
  for (int k : rks)
    a[k] = (r[k]+radd)*rmul;
  for (int k : ksNew)
    a[k] = rset;
}
