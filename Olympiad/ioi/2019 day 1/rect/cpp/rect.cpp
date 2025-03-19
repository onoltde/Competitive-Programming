#include "rect.h"
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

void mnn(int &a, int b) {
	if(a > b) a = b;
}

void mxx(int &a, int b) {
	if(a < b) a = b;
}

const int mxn = 2510;
int a[mxn][mxn];
vector<pair<int, int>> h[mxn][mxn], v[mxn][mxn];

void addHor(int i, int l, int r) {
	h[i][l].eb(r - l + 1, 1);
}

void addVer(int j, int l, int r) {
	v[l][j].eb(r - l + 1, 1);
}

long long count_rectangles(vector<vector<int>> A) {
	int n = A.size(), m = A[0].size();
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			a[i][j] = A[i - 1][j - 1];
		}
	}
	for(int i = 1; i <= n; i++) {
		vector<int> v;
		for(int j = 1; j <= m; j++) {
			while(v.size() && a[i][v.back()] < a[i][j]) v.pop_back();
			if(v.size() && a[i][v.back()] > a[i][j] && v.back() + 1 <= j - 1) {
				addHor(i, v.back() + 1, j - 1);
			}
			v.pb(j);
		}

		v.clear();
		for(int j = m; j >= 1; j--) {
			while(v.size() && a[i][v.back()] < a[i][j]) v.pop_back();
			if(v.size() && a[i][v.back()] >= a[i][j] && v.back() - 1 >= j + 1) {
				addHor(i, j + 1, v.back() - 1);
			}
			v.pb(j);
		}
	}

	for(int j = 1; j <= m; j++) {
		vector<int> v;
		for(int i = 1; i <= n; i++) {
			while(v.size() && a[v.back()][j] < a[i][j]) v.pop_back();
			if(v.size() && a[v.back()][j] > a[i][j] && v.back() + 1 <= i - 1) {
				addVer(j, v.back() + 1, i - 1);
			}
			v.pb(i);
		}

		v.clear();
		for(int i = n; i >= 1; i--) {
			while(v.size() && a[v.back()][j] < a[i][j]) v.pop_back();
			if(v.size() && a[v.back()][j] >= a[i][j] && v.back() - 1 >= i + 1) {
				addVer(j, i + 1, v.back() - 1);
			}
			v.pb(i);
		}
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			sort(all(h[i][j]));
			sort(all(v[i][j]));
		}
	}

	for(int i = n; i >= 1; i--) {
		for(int j = 1; j <= m; j++) {
			int p = 0;
			for(int k = 0; k < h[i][j].size(); k++) {
				while(p < h[i + 1][j].size() && h[i + 1][j][p].ff < h[i][j][k].ff) p++;
				if(p < h[i + 1][j].size() && h[i + 1][j][p].ff == h[i][j][k].ff) h[i][j][k].ss = h[i + 1][j][p].ss + 1;
			}
		}
	}

	for(int i = 1; i <= n; i++) {
		for(int j = m; j >= 1; j--) {
			int p = 0;
			for(int k = 0; k < v[i][j].size(); k++) {
				while(p < v[i][j + 1].size() && v[i][j + 1][p].ff < v[i][j][k].ff) p++;
				if(p < v[i][j + 1].size() && v[i][j + 1][p].ff == v[i][j][k].ff) v[i][j][k].ss = v[i][j + 1][p].ss + 1;
			}
		}
	}

	long long ans = 0;

	for(int i = 2; i < n; i++) {
		for(int j = 2; j < m; j++) {
			for(auto i1 : h[i][j]) {
				for(auto i2 : v[i][j]) {
					if(i1.ff <= i2.ss && i1.ss >= i2.ff) ans++;
				}
			}
		}
	}
	return ans;
}
