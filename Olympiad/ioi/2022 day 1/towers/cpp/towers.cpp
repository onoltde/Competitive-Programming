#include "towers.h"
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

const int mxn = 1e5 + 10, inf = 2e9 + 10;
int h[mxn], n, lg[mxn], L[mxn], R[mxn], pre[mxn], pos;
pair<int, int> p[mxn][20];
bool sub1;

pair<int, int> get(int l, int r) {
	int k = lg[r - l + 1];
	return max(p[l][k], p[r - (1 << k) + 1][k]);
}

void build(int l, int r) {
	if(l > r) return;
	int pos = get(l, r).ss;
	L[pos] = l;
	R[pos] = r;
	if(l == r) return;
	pre[pos] = 1;
	build(l, pos - 1);
	build(pos + 1, r);
}

void init(int _n, vector<int> H) {
	n = _n;
	for(int i = 1; i <= n; i++) {
		h[i] = H[i - 1];
		p[i][0] = {h[i], i};
	}
	for(int j = 1; j < 20; j++) {
		for(int i = 1; i + (1 << j) - 1 <= n; i++) {
			p[i][j] = max(p[i][j - 1], p[i + (1 << (j - 1))][j - 1]);
		}
	}
	for(int i = 2; i <= n; i++) {
		lg[i] = lg[i / 2] + 1;
	}
	build(1, n);
	for(int i = 1; i <= n; i++) {
		pre[i] += pre[i - 1];
	}
	sub1 = 1;
	pos = get(1, n).ss;
	for(int i = 1; i <= n; i++) {
		if(L[i] < i && R[i] > i && (L[i] > 1 || R[i] < n)) sub1 = 0;
	}
}

int max_towers(int l, int r, int D) {
	l++;
	r++;
	if(l == r) return 1;
	if(sub1) {
		return 1 + (l < pos && r > pos && max(h[l], h[r]) <= h[pos] - D);
	}
	int ans = r - l + 1 - pre[r] + pre[l - 1];
	if(pre[l] - pre[l - 1] == 1 && R[l] == l) ans++;
	if(pre[r] - pre[r - 1] == 1 && L[r] == r) ans++;
	return ans;
}