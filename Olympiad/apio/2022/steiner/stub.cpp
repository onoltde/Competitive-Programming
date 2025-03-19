#include "steiner.h"

#include <cassert>
#include <cstdio>

#include <vector>

int main() {
  int N, Q;
  assert(1 == scanf("%d", &N));
  std::vector<int> U(N - 1), V(N - 1), W(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    assert(3 == scanf("%d %d %d", &U[i], &V[i], &W[i]));
  }
  init(N, U, V, W);

  assert(1 == scanf("%d", &Q));
  for (int i = 0; i < Q; ++i) {
    int P;
    assert(1 == scanf("%d", &P));
    printf("%d\n", flip(P));
  }
  return 0;
}
