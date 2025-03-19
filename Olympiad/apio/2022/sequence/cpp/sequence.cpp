#include "sequence.h"

#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
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

template<typename T, typename U>
ostream & operator << (ostream &out, const pair<T, U> &c) {
	out << c.first << ' ' << c.second;
		return out;
}

template<typename T>
ostream & operator << (ostream &out, vector<T> &v) {
	const int sz = v.size();
	for (int i = 0; i < sz; i++) {
		if (i) out << ' ';
		out << v[i];
	}
		return out;
}

template<typename T>
istream & operator >> (istream &in, vector<T> &v) {
	for (T &x : v) in >> x;
		return in;
}


template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

const int mxn = 5e5 + 10;
int a[mxn], sum[mxn * 4];
pair<int, int> d[mxn * 4];

pair<int, int> operator+(const pair<int, int> a, const pair<int, int> b) {
	return make_pair(min(a.ff, b.ff), max(a.ss, b.ss));
}

pair<int, int> operator+(const pair<int, int> a, const int b) {
	return make_pair(a.ff + b, a.ss + b);
}

void build(int l, int r, int i) {
	if(l == r) {
		d[i] = make_pair(l, l);
		return;
	}
	int m = (l + r) >> 1;
	build(l, m, i * 2);
	build(m + 1, r, i * 2 + 1);
	d[i] = d[i * 2] + d[i * 2 + 1];
}

void update(int l, int r, int i, int x, int y, int val) {
	if(l >= x && r <= y) {
		sum[i] += val;
		d[i] = d[i] + val;
		return;
	}
	int m = (l + r) >> 1;
	if(x <= m) update(l, m, i * 2, x, y, val);
	if(y > m) update(m + 1, r, i * 2 + 1, x, y, val);
	d[i] = (d[i * 2] + d[i * 2 + 1]) + sum[i];
}

pair<int, int> get(int l, int r, int i, int x, int y) {
	if(l >= x && r <= y) return d[i];
	int m = (l + r) >> 1;
	if(y <= m) return get(l, m, i * 2, x, y) + sum[i];
	else if(x > m) return get(m + 1, r, i * 2 + 1, x, y) + sum[i];
	return (get(l, m, i * 2, x, y) + get(m + 1, r, i * 2 + 1, x, y)) + sum[i];
}

int sequence(int n, std::vector<int> A) {
	vector<vector<int>> g(n + 1, vector<int>());
	for(int i = 1; i <= n; i++) {
		a[i] = A[i - 1];
		g[a[i]].pb(i);
	}
	build(0, n, 1);
	int ans = 1;
	for(int i = 1; i <= n; i++) {
		for(int x : g[i]) {
			update(0, n, 1, x, n, -2);
		}
		for(int j = (int)g[i].size() - 1; j >= 0; j--) {
			update(0, n, 1, g[i][j], n, 2);
			while(j + ans < g[i].size()) {
				auto L = get(0, n, 1, 0, g[i][j] - 1);
				auto R = get(0, n, 1, g[i][j + ans], n);
				R.ff -= (ans + 1) * 2;
				if(!(min(L.ff, L.ss) > max(R.ff, R.ss) || max(L.ff, L.ss) < min(R.ff, R.ss))) {
					ans++;
				} else {
					break;
				}
			} 
		}
		for(int x : g[i]) {
			update(0, n, 1, x, n, -2);
		}
	}
	return ans;
}
