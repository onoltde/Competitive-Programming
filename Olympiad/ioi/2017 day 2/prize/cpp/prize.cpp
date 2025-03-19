#include "prize.h"
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

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int mxn = 2e5 + 10;
pair<int, int> did[mxn];
int mx, ans, n;

int get(int i) {
	if(did[i].ff != -1) return did[i].ff + did[i].ss;
	auto sus = ask(i);
	did[i].ff = sus[0]; did[i].ss = sus[1];
	return did[i].ff + did[i].ss;
}

int getl(int i) {
	if(i < 0 || i >= n) return 0;
	if(did[i].ff != -1) return did[i].ff;
	get(i);
	return did[i].ff;
}

int getr(int i) {
	if(i < 0 || i >= n) return 0;
	if(did[i].ss != -1) return did[i].ss;
	get(i);
	return did[i].ss;
}

void solve(int l, int r) {
	if(l > r) return;
	int m = (l + r) / 2;
	if(get(m) == 0) ans = m;
	if(l == r) return;
	int m1 = m, m2 = m;
	while(m1 >= l && get(m1) < mx) {
		if(get(m1) == 0) ans = m1;
		m1--;
	}
	while(m2 <= r && get(m2) < mx) {
		if(get(m2) == 0) ans = m2;
		m2++;
	}
 
	if(m1 >= l && did[m1].ff > getl(l - 1)) solve(l, m1 - 1);
	if(r >= m2 && did[m2].ss > getr(r + 1)) solve(m2 + 1, r);
}

int find_best(int _n) {
	n = _n;
	if(n == 1) return 0;
	for(int i = 0; i < n; i++) {
		did[i] = {-1, -1};
	}
	if(n <= 5000) {
		for(int i = 0; i < n; i++) {
			if(get(i) == 0) return i;
		}
		return -69;
	}
	ans = -1;
	srand(time(NULL));
	for(int i = 0; i < 100; i++) {
		int x = rand() % n;
		assert(x >= 0 && x <= n);
		if(get(x) == 0) return x;
		mx = max(mx, get(x));
	}
	solve(0, n - 1);
	assert(ans != -1);
	return ans;
}