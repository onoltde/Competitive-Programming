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

const int my = 19;
int n;
vector<int> a;

struct RMQ {
	vector<vector<pair<int, int>>> sp;
	vector<int> a;
	vector<int> mylg;

	void init() {
		a = ::a;
		sp.clear();
		for(int i = 0; i < n; i++) {
			sp.pb(vector<pair<int, int>>(my, make_pair(i, i)));
		}
		for(int j = 1; j < my; j++) {
			for(int i = 0; i + (1 << j) <= n; i++) {
				int p = i + (1 << (j - 1));
				sp[i][j] = sp[i][j - 1];
				if(a[sp[p][j - 1].ff] > a[sp[i][j].ff]) sp[i][j].ff = sp[p][j - 1].ff;
				if(a[sp[p][j - 1].ss] < a[sp[i][j].ss]) sp[i][j].ss = sp[p][j - 1].ss;
			}
		}
		mylg.resize(n + 1);
		for(int i = 2; i <= n; i++) {
			mylg[i] = mylg[i / 2] + 1;
		}
	}

	int getMx(int l, int r) {
		int p = mylg[r - l + 1];
		if(a[sp[l][p].ff] > a[sp[r - (1 << p) + 1][p].ff]) return sp[l][p].ff;
		else return sp[r - (1 << p) + 1][p].ff;
	}

	int getMn(int l, int r) {
		int p = mylg[r - l + 1];
		if(a[sp[l][p].ss] < a[sp[r - (1 << p) + 1][p].ss]) return sp[l][p].ss;
		else return sp[r - (1 << p) + 1][p].ss;
	}

} rmq;

struct SP {
	vector<vector<int>> sp;

	void init(bool fl) {
		sp.clear();
		for(int i = 0; i < n; i++) {
			sp.pb(vector<int>(my, n)); 
		}
		vector<int> mx, mn;
		for(int i = n - 1; i >= 0; i--) {
			while(mx.size() && a[mx.back()] < a[i]) mx.pop_back();
			while(mn.size() && a[mn.back()] > a[i]) mn.pop_back();
			mx.pb(i);
			mn.pb(i);
			if(i != n - 1 && a[i] > a[i + 1]) {
				int cl = n;
				if(mx.size() > 1) cl = mx[(int)mx.size() - 2];
				if(fl) {
					sp[i][0] = n - rmq.getMn(n - (cl - 1) - 1, n - i - 1) - 1;
				} else { 
					sp[i][0] = rmq.getMn(i, cl - 1);
				}
			} else if(i != n - 1 && a[i] < a[i + 1]) {
				int cl = n;
				if(mn.size() > 1) cl = mn[(int)mn.size() - 2];
				if(fl) {
					sp[i][0] = n - rmq.getMx(n - (cl - 1) - 1, n - i - 1) - 1;
				} else {
					sp[i][0] = rmq.getMx(i, cl - 1);
				}
			}
		}
		for(int j = 1; j < my; j++) {
			for(int i = 0; i < n; i++) {
				if(sp[i][j - 1] == n) sp[i][j] = n;
				else sp[i][j] = sp[sp[i][j - 1]][j - 1];
			}
		}
	}

	int get(int i, int k) {
		return sp[i][k];
	}

} spr, spl;

void init_permutation(int N, vector<int> A) {
	n = N;
	a = A;
	rmq.init();
	spr.init(0);
	reverse(all(a));
	spl.init(1);
	reverse(all(a));
}

int calc_f(int l, int r) {
	int mid = rmq.getMn(l, r);
	int ans1 = 0, ans2 = 0;
	r = n - r - 1;
	for(int i = my - 1; i >= 0; i--) {
		if(spr.get(l, i) <= mid) {
			ans1 += (1 << i);
			l = spr.get(l, i);
		}
		if(spl.get(r, i) <= n - mid - 1) {
			ans2 += (1 << i);
			r = spl.get(r, i);
		}
	}
	if(l != mid) ans1++;
	if(r != n - mid - 1) ans2++;
	return ans1 + ans2;
}