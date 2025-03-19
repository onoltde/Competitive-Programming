#include "prison.h"

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

vector<vector<int>> devise_strategy(int n) {
	vector<vector<int>> rep(n + 1, vector<int>(8));
	for(int i = 0; i <= n; i++) {
		int x = i;
		for(int j = 0; j < 8; j++) {
			rep[i][j] = x % 3;
			x /= 3;
		}
	}
	vector<vector<int>> ret{vector<int>{0}};
	for(int i = 1; i <= n; i++) {
		ret[0].pb(rep[i][7] + 1);
	}
	int bit = 7, now = 1;
	vector<int> pl{-1, -2};
	// 0 = A, 1 = B
	while(bit > 0) {
		vector<int> idx{ret.size() + 3, ret.size() + 4, ret.size() + 5};
		for(int j = 0; j < 3; j++) {
			vector<int> tmp{now};
			for(int i = 1; i <= n; i++) {
				if(rep[i][bit] < j) tmp.pb(pl[now]);
				else if(rep[i][bit] > j) tmp.pb(pl[now ^ 1]);
				else {
					if(bit == 1) {
						if(rep[i][bit - 1] == 0) tmp.pb(pl[now]);
						else if(rep[i][bit - 1] == 2) tmp.pb(pl[now ^ 1]);
						else tmp.pb(idx[0]);
					} else {
						tmp.pb(idx[rep[i][bit - 1]]);
					}
				}
			}
			ret.pb(tmp);
		}
		bit--;
		now ^= 1;
	}
	vector<int> tmp(n + 1);
	tmp[0] = now;
	for(int i = 1; i <= n; i++) {
		if(rep[i][0] == 0) tmp[i] = pl[now];
		else if(rep[i][0] == 2) tmp[i] = pl[now ^ 1];
	}
	ret.pb(tmp);
	return ret;
}
