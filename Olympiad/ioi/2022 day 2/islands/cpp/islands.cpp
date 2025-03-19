#include "islands.h"
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
 
const int mxn = 1e5 + 10;
vector<pair<int, int>> g[mxn];
bool tp, found;
vector<int> ans;
int vis[mxn], p[mxn];
 
void dfs(int to, int fr) {
	p[to] = fr;
	vis[to] = 1;
	vector<int> lol;
	for(auto it : g[to]) {
		int x = it.ff, id = it.ss;
		if(id == fr || vis[x]) continue;
		lol.pb(id);
	}
	if(lol.size() >= 2 && !tp) {
		vector<int> tmp = ans;
		tmp.pb(lol[0]);
		tmp.pb(lol[0] ^ 1);
		tmp.pb(lol[1]);
		tmp.pb(lol[1] ^ 1);
		tmp.pb(lol[0] ^ 1);
		tmp.pb(lol[0]);
		tmp.pb(lol[1] ^ 1);
		tmp.pb(lol[1]);
		tmp.in(tmp.end(), ans.rbegin(), ans.rend());
		swap(tmp, ans);
		found = 1;
		return;
	}
	if(found) return;
	for(auto it : g[to]) {
		int x = it.ff, id = it.ss;
		if(vis[x] == 2) continue;
		if(id / 2 == fr / 2) continue;
		ans.pb(id);
		if(vis[x] == 1) {
			found = 1;
			vector<int> cyc;
			while(ans.size() && ans.back() != p[x]) {
				cyc.pb(ans.back());
				ans.pop_back();
			}
			reverse(all(cyc));
			vector<int> tmp = ans;
			if(tp) {
				for(int x : cyc) tmp.pb(x);
				for(int x : cyc) tmp.pb(x ^ 1);
				reverse(all(cyc));
				for(int x : cyc) tmp.pb(x);
				for(int x : cyc) tmp.pb(x ^ 1);
			} else {
				for(int x : cyc) tmp.pb(x);
				reverse(all(cyc));
				for(int x : cyc) tmp.pb(x ^ 1);
				for(int x : cyc) tmp.pb(x);
				reverse(all(cyc));
				for(int x : cyc) tmp.pb(x ^ 1);
			}
			tmp.in(tmp.end(), ans.rbegin(), ans.rend());
			swap(tmp, ans);
		} else {
			dfs(x, id);
		}
 
		if(found) return;
		ans.pop_back();
	}
	vis[to] = 2;
}
 
variant<bool, vector<int>> find_journey(int n, int m, vector<int> U, vector<int> V) {
	if(n == 2) {
		vector<int> a0, a1;
		for(int i = 0; i < m; i++) {
			if(U[i] == 0) a0.pb(i);
			else a1.pb(i);
		}
		if(a0.size() >= 2 && a1.size() >= 1) return vector<int>{a0[0], a1[0], a0[1], a0[0], a1[0], a0[1]};
		else return false;
	}
	if(U[0] == U[1]) tp = 1;
	for(int i = 0; i < m; i++) {
		g[U[i]].eb(V[i], i);
	}
	dfs(0, -10000);
	if(found) return ans;
	return false;
}