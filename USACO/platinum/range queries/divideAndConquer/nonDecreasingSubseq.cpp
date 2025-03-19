#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

#define int long long
 
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

typedef array<int, 21> arr;

const int mxn = 5e4 + 10, mod = 1e9 + 7, b = 200;
int a[mxn];
vector<arr> ans1[mxn * 4], ans2[mxn * 4];

void add(int &a, int b) {
	a = (a + b) % mod;
}

void build(int l, int r, int i = 1) {
	if(l == r) return;
	int m = (l + r) / 2;
	array<arr, 21> cnt;
	for(int j = 0; j <= 20; j++)
		for(int k = 0; k <= 20; k++)
			cnt[j][k] = 0;

	for(int j = m; j >= l; j--) {
		arr tmp;
		for(int k = 0; k <= 20; k++) {
			tmp[k] = 0;
		}
		tmp[a[j]] = 1;
		for(int k = a[j]; k <= 20; k++) {
			for(int kk = a[j]; kk <= k; kk++) {
				add(tmp[k], cnt[kk][k]);
			}
		}
		for(int k = 0; k <= 20; k++) {
			add(cnt[a[j]][k], tmp[k]);
		}
		ans1[i].pb(tmp);
	}
	for(int j = 1; j < ans1[i].size(); j++) {
		for(int k = 0; k <= 20; k++) {
			add(ans1[i][j][k], ans1[i][j - 1][k]);
		}
	}

	for(int j = 0; j <= 20; j++)
		for(int k = 0; k <= 20; k++)
			cnt[j][k] = 0;

	for(int j = m + 1; j <= r; j++) {
		arr tmp;
		for(int k = 0; k <= 20; k++) {
			tmp[k] = 0;
		}
		tmp[a[j]] = 1;
		for(int k = 0; k <= a[j]; k++) {
			for(int kk = k; kk <= a[j]; kk++) {
				add(tmp[k], cnt[kk][k]);
			}
		}
		for(int k = 0; k <= 20; k++) {
			add(cnt[a[j]][k], tmp[k]);
		}
		ans2[i].pb(tmp);
	}
	for(int j = 1; j < ans2[i].size(); j++) {
		for(int k = 0; k <= 20; k++) {
			add(ans2[i][j][k], ans2[i][j - 1][k]);
		}
	}
	build(l, m, i * 2);
	build(m + 1, r, i * 2 + 1);
}

int solve(int l, int r, int ll, int rr, int i = 1) {
	if(ll == rr) return 2;
	int m = (l + r) / 2;
	if(ll > m) return solve(m + 1, r, ll, rr, i * 2 + 1);
	if(rr <= m) return solve(l, m, ll, rr, i * 2);
	int idx1 = m - ll;
	int idx2 = rr - (m + 1);
	int ret = 1;
	for(int ii = 0; ii <= 20; ii++) {
		for(int jj = ii; jj <= 20; jj++) {
			add(ret, ans1[i][idx1][ii] * ans2[i][idx2][jj]);
		}
		add(ret, ans1[i][idx1][ii]);
		add(ret, ans2[i][idx2][ii]);
	}
	return ret;
}

void go() {
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	build(1, n);
	int q;
	cin >> q;
	for(int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		cout << solve(1, n, l, r) << '\n';
	}
}
 
signed main() {
	#ifndef ONO
	freopen("nondec.in", "r", stdin);
	freopen("nondec.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}