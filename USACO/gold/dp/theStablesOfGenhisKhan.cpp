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

const int mxn = 310, inf = 1e18;
int k[mxn], dp[mxn][mxn], cnt[mxn][mxn];

int solve(int l, int r) {
	if(l > r) return 0;
	if(dp[l][r] != inf) return dp[l][r];
	if(l == r) {
		dp[l][r] = cnt[l][r];
		return dp[l][r];
	}
	for(int i = l; i <= r; i++) {
		mnn(dp[l][r], solve(l, i - 1) + cnt[l][i - 1] + solve(i + 1, r) + cnt[i + 1][r] + 1);
	}
	return dp[l][r];
}

void go() {
	int n, m;
	cin >> m >> n;
	for(int i = 1; i <= n; i++) {
		cin >> k[i];
		for(int j = 1; j <= n; j++) {
			dp[i][j] = inf;
		}
	}
	sort(k + 1, k + n + 1);
	k[0] = 0;
	k[n + 1] = m + 1;
	for(int i = 1; i <= n + 1; i++) {
		for(int j = 0; j <= n; j++) {
			cnt[i][j] = k[j + 1] - k[i - 1] - 1;
		}
	}
	cout << solve(1, n) << '\n';
}

signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}