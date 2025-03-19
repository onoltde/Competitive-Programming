#include "trip.h"

#include <cassert>
#include <cstdio>

#include <vector>

int main() {
  int S, Q;
  assert(2 == scanf("%d %d", &S, &Q));
  std::vector<int> V1(Q), V2(Q);
  for (int i = 0; i < Q; ++i) {
    assert(1 == scanf("%d", &V1[i]));
  }
  for (int i = 0; i < Q; ++i) {
    assert(1 == scanf("%d", &V2[i]));
  }
  printf("%d\n", solve(S, Q, V1, V2));
  return 0;
}
