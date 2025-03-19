#include "meetings.h"
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

const int mxn = 1e5 + 10, maxVal = 2;
const long long inf = 1e18;
int h[mxn];

struct node {
	long long dp[maxVal + 1][maxVal + 1];
	pair<long long, int> l[maxVal + 1], r[maxVal + 1];
	node() {
		for(int i = 1; i <= maxVal; i++) {
			for(int j = 1; j <= maxVal; j++) {
				dp[i][j] = -1;
			}
			l[i] = r[i] = {-1, -1};
		}
	}
} d[mxn * 4];

void mnn(long long& a, long long b) {
	if(a == -1 || a > b) a = b;
}

node operator+(const node& a, const node& b) {
	node ret;
	for(int i = 1; i <= maxVal; i++) {
		for(int j = 1; j <= maxVal; j++) {
			if(~a.dp[i][j]) {
				mnn(ret.dp[i][b.l[j].ss], a.dp[i][j] + b.l[j].ff);
			}
			if(~b.dp[i][j]) {
				mnn(ret.dp[a.r[i].ss][j], b.dp[i][j] + a.r[i].ff);
			}
		}
		ret.l[i] = {a.l[i].ff + b.l[a.l[i].ss].ff, b.l[a.l[i].ss].ss};
		ret.r[i] = {b.r[i].ff + a.r[b.r[i].ss].ff, a.r[b.r[i].ss].ss};
	}
	return ret;
}

void build(int l, int r, int i) {
	if(l == r) {
		d[i].dp[h[l]][h[l]] = h[l];
		for(int j = 1; j <= maxVal; j++) {
			d[i].l[j] = d[i].r[j] = {max(j, h[l]), max(j, h[l])};
		}
		return;
	}
	int m = (l + r) / 2;
	build(l, m, i * 2);
	build(m + 1, r, i * 2 + 1);
	d[i] = d[i * 2] + d[i * 2 + 1];
}

node query(int l, int r, int i, int x, int y) {
	if(l >= x && r <= y) return d[i];
	int m = (l + r) / 2;
	if(y <= m) return query(l, m, i * 2 , x, y);
	if(x > m) return query(m + 1, r, i * 2 + 1, x, y);
	return query(l, m, i * 2, x, y) + query(m + 1, r, i * 2 + 1, x, y); 
}

vector<long long> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
	int Q = L.size(), n = H.size();
	vector<long long> ret(Q);

	for(int i = 1; i <= n; i++) {
		h[i] = H[i - 1];
	}
	build(1, n, 1);
	for(int i = 0; i < Q; i++) {
		int l = L[i] + 1, r = R[i] + 1;
		node qu = query(1, n, 1, l, r);
		ret[i] = inf;
		for(int j = 1; j <= maxVal; j++) {
			for(int k = 1; k <= maxVal; k++) {
				if(~qu.dp[j][k]) ret[i] = min(ret[i], qu.dp[j][k]);
			}
		}
	}
	return ret;
}
