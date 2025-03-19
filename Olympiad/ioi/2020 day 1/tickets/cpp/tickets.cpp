#include "tickets.h"
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

long long find_maximum(int k, vector<vector<int>> a) {
	int n = a.size();
	int m = a[0].size();
	vector<vector<int>> ans(n, vector<int>(m, -1));
	vector<vector<int>> neg(n), pos(n);

	long long ret = 0;
	priority_queue<pair<long long, pair<int, int>>> q;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < k; j++) {
			ret -= 1LL * a[i][j];
			neg[i].pb(j);
			q.push({1LL * (a[i][j] + a[i][m - k + j]), {i, m - k + j}});
		}
	}

	for(int t = 0; t < n * k / 2; t++) {
		auto val = q.top();
		q.pop();
		ret += val.ff;
		int i = val.ss.ff;
		int j = val.ss.ss;
		neg[i].pop_back();
		pos[i].pb(j);
	}

	for(int i = 0; i < n; i++) {
		reverse(all(pos[i]));
	}

	for(int t = 0; t < k; t++) {
		vector<int> v(n);
		iota(all(v), 0);
		sort(all(v), [&](int x, int y) {
			return pos[x].size() > pos[y].size();
		});
		for(int j = 0; j < n / 2; j++) {
			int i = v[j];
			ans[i][pos[i].back()] = t;
			pos[i].pop_back();
		}
		for(int j = n / 2; j < n; j++) {
			int i = v[j];
			ans[i][neg[i].back()] = t;
			neg[i].pop_back();
		}
	}

	allocate_tickets(ans);
	return ret;
}
