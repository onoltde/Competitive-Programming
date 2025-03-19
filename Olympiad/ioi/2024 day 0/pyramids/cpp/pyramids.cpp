#include "pyramids.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

//#define int long long

typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
vector<ll> a, b;

void init(std::vector<int> A, std::vector<int> B) {
	int n = A.size();
	a.resize(n + 1);
	b.resize(n + 1);
	for(int i = 0; i < n; i++) {
		a[i + 1] = a[i] + A[i];
		b[i + 1] = b[i] + B[i];
	}
}

bool can_transform(int L, int R, int X, int Y) {
	return a[R + 1] - a[L] == b[Y + 1] - b[X];
}
