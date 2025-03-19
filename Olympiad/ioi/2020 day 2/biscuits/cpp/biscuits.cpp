#include "biscuits.h"
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

long long count_tastiness(long long x, vector<long long> a) {
	const long long inf = 1e18;
	const int mxn = 62;
	while(a.size() < mxn) {
		a.pb(0);
	}
	map<long long, long long> mp[mxn];
	for(int i = 1; i < mxn; i++) {
		a[i] *= (1ll << i);
		a[i] += a[i - 1];
	}
	for(int i = 0; i < mxn; i++) {
		a[i] /= x;
	}

	function<long long(long long, int)> solve = [&](long long n, int bit) -> long long {
		if(bit == -1) return 1;
		n = min({n, (1ll << (bit + 1)) - 1, a[bit]});
		if(mp[bit].count(n)) return mp[bit][n];
		long long &ret = mp[bit][n];
		if((1ll << bit) <= n) ret += solve(n - (1ll << bit), bit - 1);
		ret += solve(n, bit - 1);
		return ret;
	};

	return solve(a.back(), (int)a.size() - 1);
}

