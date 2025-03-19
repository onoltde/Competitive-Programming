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

const int N = 5010, mod = 998244353;
int n, dp[3][N][3], a[N];

vector<int> fac(1, 1), inv(1, 1);
int fpow(int a, int z) {
	int ret = 1;
	for(; z > 0; z >>= 1) {
		if(z & 1) ret = (ret * a) % mod;
		a = (a * a) % mod;
	}  
	return ret;
}

void build() {
	for(int i = 1; i < N; i++) {
		fac.pb(fac.back() * i % mod);
		inv.pb(fpow(fac.back(), mod - 2));
	}
}

int C(int n, int k) {
	if(n < 0 || k < 0 || k > n) return 1;
	return (((fac[n] * inv[k]) % mod) * inv[n - k]) % mod; 
}

void go() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	reverse(a + 1, a + n + 1);
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j <= n + 2; j++) {
			dp[i][j][0] = dp[i][j][1] = 0;
		}
	}
	int tp = 0;
	dp[0][0][0] = 1;
	for(int i = 1; i <= n; i++) {
		int nx = i;
		tp ^= 1;
		while(nx + 1 <= n && a[nx + 1] == a[i]) {
			nx++;
		}
		for(int j = 0; j <= n + 2; j++) {
			dp[tp][j][0] = dp[tp][j][1] = 0;
		}
		int cnt = nx - i + 1;
		for(int j = 0; j + cnt <= n; j++) {
			dp[tp][j][1] = (dp[tp][j][1] + dp[tp ^ 1][j + cnt][1] * C(j + cnt, cnt)) % mod;
			dp[tp][j][1] = (dp[tp][j][1] + dp[tp ^ 1][j + cnt][0] * C(j + cnt - 1, cnt - 1)) % mod;
		}
		for(int j = 1; j <= n; j++) {
			if(j + cnt <= n && j + cnt - 1 >= cnt)
				dp[tp][j][0] = (dp[tp][j][0] + dp[tp ^ 1][j + cnt][0] * C(j + cnt - 1, cnt)) % mod;
			if(j + cnt - 2 <= n && j + cnt - 2 >= 0) 
				dp[tp][j][0] = (dp[tp][j][0] + dp[tp ^ 1][j + cnt - 2][0] * (i - 1 == 0 || (j + cnt - 3 >= 0 && j >= 2) 
																			 ? C(j + cnt - 3, cnt - 1) : 0)) % mod;
		}
		i = nx;
	}
	cout << dp[tp][0][1] << '\n';
}

signed main() {
    fast;
    int t = 1;
    cin >> t;
    build();
    while(t--) {
        go();
    }
    return 0;
}