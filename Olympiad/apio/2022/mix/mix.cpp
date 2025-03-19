#include"mix.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

const int MX = 10;
int id[11][11], id1[11], ecid[11];

vector<vector<bool>> propose(int X, int K, int M) {
	vector<vector<bool>> A(M, vector<bool>(X));
	int now = 0;
	for(int i = 0; i < MX; i++) {
		for(int j = i + 1; j < MX; j++) {
			id[i][j] = id[j][i] = now;
			for(int k = 0; k < K; k++) {
				if(((k >> i) & 1) == 0 && ((k >> j) & 1) == 0) A[now][k] = 1;
			}
			now++;
		}
	}
	for(int i = 0; i < MX; i++) {
		id1[i] = now;
		for(int k = 0; k < K; k++) {
			if((k >> i) & 1) A[now][k] = 1;
		}
		now++;
	}
	int lol = (1 << MX) - 1;
	for(int i = 0; i < MX; i++) {
		if(lol - (1 << i) <= 1000) {
			ecid[i] = now;
			A[now][lol - (1 << i)] = 1;
			now++;
		}
	}
	return A;
}

vector<int> detect(int x, int k, int m, const vector<vector<bool>> &a, const vector<bool> &R) {
	vector<int> ret;
	int ans1 = 0, ans2 = 0;
	vector<bool> is(MX, 0);
	bool did = 0;
	for(int i = 0; i < MX; i++) {
		if(!R[id1[i]]) is[i] = 1;
		did |= is[i];
	}
	auto solve1 = [&]() -> void {
		vector<int> v;
		for(int i = 0; i < MX; i++) {
			if(is[i]) continue;
			v.pb(i);
			for(int j = 0; j < MX; j++) {
				if(!is[j] || i == j) continue;
				if(!R[id[i][j]]) {
					v.pop_back();
					ans1 ^= (1 << i);
					ans2 ^= (1 << i);
					break;
				}
			}
		}
		if(v.size()) {
			ans2 ^= (1 << v[0]);
			for(int i = 1; i < v.size(); i++) {
				if(R[id[v[0]][v[i]]]) ans2 ^= (1 << v[i]);
				else ans1 ^= (1 << v[i]);
			}
		}
	};
	auto find = [&]() -> vector<int> {
		vector<int> tmp;
		int val = (1 << MX);
		for(int i = 0; i < MX; i++) {
			if(ecid[i] != 0) {
				if(R[ecid[i]]) tmp.pb(val ^ (1 << i));
			}
		}
		return tmp;
	};
	auto solve3 = [&]() -> void {
		auto tmp = find();
		ans1 = tmp[0];
		ans2 = tmp.back();
	};
	auto solve2 = [&]() -> void {
		int pos = -1;
		for(int i = 0; i < MX; i++) {
			for(int j = i + 1; j < MX; j++) {
				if(!R[id[i][j]]) {
					pos = i;
					break;
				}
			}
			if(pos != -1) break;
		}
		if(pos == -1) {
			solve3();
			return;
		}
		vector<int> v;
		for(int i = 0; i < MX; i++) {
			if(i == pos) continue;
			if(!R[id[i][pos]]) {
				ans1 ^= (1 << i);
				v.pb(i);
			}
		}
		bool found = 0;
		set<int> ss;
		for(int i = 0; i < v.size(); i++) {
			for(int j = i + 1; j < v.size(); j++) {
				if(R[id[v[i]][v[j]]]) {
					found = 1;
					ss.in(v[i]);
					ss.in(v[j]);
				}
			}
		}
		if(found) {
			ans2 = (1 << MX) - 1;
			for(int x : ss) {
				ans2 ^= (1 << x);
			}
		} else {
			ans2 = find()[0];
		}
	};

	if(did) {
		solve1();
	} else {
		solve2();
	}

	ret.pb(ans1);
	if(ans1 != ans2) ret.pb(ans2);
	return ret;
}