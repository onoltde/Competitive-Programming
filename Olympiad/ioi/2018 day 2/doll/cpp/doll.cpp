#include "doll.h"
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

void create_circuit(int m, std::vector<int> a) {
	a.pb(0);
	int n = a.size();
	vector<int> C(m + 1, 0), X, Y;
	const int inf = 1e9 + 10;

	while(n & (n - 1)) {
		n++;
	}

	auto get = [&](int k) -> vector<int> {
		vector<int> vec(k);
		iota(all(vec), 0);
		vector<int> pos;
		int l = 0;
		function<void(vector<int>&)> dfs = [&](vector<int> &vec) {
			if(vec.size() == 1) {
				pos.pb(vec[0]);
				return;
			}
			vector<int> L, R;
			for(int i = 0; i < vec.size(); i += 2) {
				L.pb(vec[i]);
				R.pb(vec[i + 1]);
			}
			dfs(L);
			dfs(R);
		};
		dfs(vec);
		return pos;
	};

	vector<int> pos = get(n), nwa(n, inf);
	vector<pair<int, int>> tmp;
	for(int i = n - a.size(); i < n; i++) {
		tmp.eb(pos[i], i);
	}
	sort(all(tmp));
	int l = 0;
	for(auto it : tmp) {
		nwa[it.ff] = a[l++];
	}
	swap(nwa, a);

	function<int(vector<int>&)> solve = [&](vector<int>& vec) {
		if(set<int>(all(vec)).size() == 1) return vec[0];
		vector<int> first, second;
		for(int i = 0; i < (int)vec.size(); i += 2) {
			first.pb(vec[i]);
			second.pb(vec[i + 1]);
		}
		int id1 = solve(first), id2 = solve(second);
		X.pb(id1);
		Y.pb(id2);
		return -(int)X.size();
	};
	C[0] = solve(a);
	for(int i = 1; i < C.size(); i++) {
		C[i] = C[0];
	}
	for(int i = 0; i < X.size(); i++) {
		if(X[i] == inf) X[i] = C[0];
		if(Y[i] == inf) Y[i] = C[0];
	}
	answer(C, X, Y);
}
