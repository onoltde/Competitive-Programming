#include "gap.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

// #define int long long

typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

long long findGap(int T, int N) {
	long long qn, qx;

	auto ask = [&](long long l, long long r) -> void {
		assert(l <= r);
		MinMax(l, r, &qn, &qx);
	};

	if(T == 1) {
		vector<long long> a(N);
		long long l = 0, r = (long long)1e18;
		for(int i = 0, j = N - 1; i <= j; i++, j--) {
			ask(l, r);
			a[i] = qn;
			a[j] = qx;
			l = qn + 1;
			r = qx - 1;
		}
		long long ans = 0;
		for(int i = 1; i < N; i++) {
			ans = max(ans, a[i] - a[i - 1]);
		}
		return ans;
	}

	long long sus1 = 0, sus2 = (long long)1e18;

	ask(sus1, sus2);

	long long mn = qn, mx = qx, ans = 0;
	long long d = (mx - mn + N - 1) / N;
	long long ls = mn, l = mn + 1;
	while(l <= mx) {
		long long r = l + d - 1;
		ask(l, r);
		if(qn != -1) {
			ans = max(ans, qn - ls);
			ls = qx;
		}
		l = r + 1;
	}
	return ans;
}
