#include "cave.h"
#include <stdio.h>
#include <stdlib.h>

void exploreCave(int N) {
	int S[N + 1], D[N + 1], LOL[N + 1];
	int A[N + 1];
	for(int i = 0; i < N; i++) {
		A[i] = LOL[i] = 0;
	}
	for(int i = 0; i < N; i++) {
		int l = 0, r = N - 1;
		int c = tryCombination(A);
		if(c == -1) c = N;
		while(l < r) {
			int m = (l + r) / 2;

			for(int j = l; j <= m; j++) {
				if(LOL[j]) continue;
				A[j] ^= 1;
			}

			int pp = tryCombination(A);
			if(pp == -1) pp = N;

			for(int j = l; j <= m; j++) {
				if(LOL[j]) continue;
				A[j] ^= 1;
			}

			if((pp == i && c > i) || (pp > i && c == i)) r = m;
			else l = m + 1;
		}
		D[l] = i;
		if(c == i) {
			A[l] ^= 1;
		}
		S[l] = A[l];
		LOL[l] = 1;
	}
	answer(S, D);
}
