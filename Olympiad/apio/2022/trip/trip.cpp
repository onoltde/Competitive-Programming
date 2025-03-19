#include "trip.h"

#include <bits/stdc++.h>

int solve(int S, int Q, std::vector<int> V1, std::vector<int> V2) {
    for(int i = 1; i < Q; i++) {
        V1[i] += V1[i - 1];
        V2[i] += V2[i - 1];
    }
    for(int i = 0; i < Q; i++) {
        if(abs(V1[i] - V2[i]) > S) return 0;
    }
    return 1;
}
