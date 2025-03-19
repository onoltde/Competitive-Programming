#include "rail.h"
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

void findLocation(int n, int first, int pos[], int tp[]) {
	pos[0] = first;
	tp[0] = 1;

	if(n == 1) return;

	vector<vector<int>> dis(n, vector<int>(n, -1));

	auto get = [&](int x, int y) -> int {
		if(x > y) swap(x, y);
		if(dis[x][y] != -1) return dis[x][y];
		return dis[x][y] = getDistance(x, y);
	};

	vector<int> id(n - 1);
	iota(all(id), 1);
	sort(all(id), [&](int x, int y) {
		return get(0, x) < get(0, y);
	});

	map<int, int> mp;

	int l = id[0], k = id[0];

	pos[l] = pos[0] + get(0, l);
	tp[l] = 2;

	id.erase(id.begin());

	mp[pos[0]] = tp[0];
	mp[pos[k]] = tp[k];

	for(int x : id) {
		if(get(0, k) + get(k, x) != get(0, x)) {
			int gg = pos[l] - (get(0, l) + get(l, x) - get(0, x)) / 2;
			if(mp[gg] == 2) {
				pos[x] = pos[l] - get(l, x);
				tp[x] = 1;
			} else {
				pos[x] = pos[0] + get(0, x);
				tp[x] = 2;
				l = x;
			}
			mp[pos[x]] = tp[x];
		}
	}
	id.resize(n - 1);
	iota(all(id), 1);
	id.erase(find(all(id), k));
	sort(all(id), [&](int x, int y) {
		return get(k, x) < get(k, y);
	});

	l = 0;

	for(int x : id) {
		if(get(0, k) + get(k, x) == get(0, x)) {
			int gg = pos[l] + (get(k, l) + get(l, x) - get(k, x)) / 2;
			if(mp[gg] == 1) {
				pos[x] = pos[l] + get(l, x);
				tp[x] = 2;
			} else {
				pos[x] = pos[k] - get(k, x);
				tp[x] = 1;
				l = x;
			}
			mp[pos[x]] = tp[x];
		}
	}
}
