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

const int mxn = 51, inf = 1e18;
int a[mxn], dp[mxn][mxn][mxn][mxn];

int solve(int i, int j, int l, int r) {
	if(l > r) return -inf;
	if(i > j) return 0;
	if(i == j) return (a[i] >= l && a[i] <= r ? 1 : 0);
	int &ret = dp[i][j][l][r];
	if(ret != -1) return ret;
	mxx(ret, solve(i + 1, j - 1, l, r));
	if(a[j] >= l) mxx(ret, solve(i + 1, j - 1, a[j], r) + 1);
	if(a[i] <= r) mxx(ret, solve(i + 1, j - 1, l, a[i]) + 1);
	if(a[j] <= a[i] && a[j] >= l && a[i] <= r) mxx(ret, solve(i + 1, j - 1, a[j], a[i]) + 2);
	mxx(ret, solve(i + 1, j, l, r));
	mxx(ret, solve(i, j - 1, l, r));
	if(a[i] >= l) mxx(ret, solve(i + 1, j, a[i], r) + 1);
	if(a[j] <= r) mxx(ret, solve(i, j - 1, l, a[j]) + 1);
	if(a[i] >= l && a[i] <= a[j] && a[j] <= r) mxx(ret, solve(i + 1, j - 1, a[i], a[j]) + 2);
	return ret;
}

void go() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i; j <= n; j++) {
			for(int l = 1; l <= 50; l++) {
				for(int r = l; r <= 50; r++) {
					dp[i][j][l][r] = -1;
				}
			}
		}
	}
	cout << solve(1, n, 1, 50) << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("subrev.in", "r", stdin);
	freopen("subrev.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}