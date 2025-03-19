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

const int mxn = 2010, inf = 1e18;
int dp[mxn][mxn * 2];

struct P {
	int p, c, x;
	P() : p(0), c(0), x(0) {}
	P(int _p, int _c, int _x) : p(_p), c(_c), x(_x) {}
	void set(int _p, int _c, int _x) {
		p = _p, c = _c, x = _x;
	};
	bool operator < (const P &a) {
		return x < a.x;
	}
	bool operator > (const P &a) {
		return x > a.x;
	}
} a[mxn];

void go() {
	int n, A, B;
	cin >> n >> A >> B;
	for(int i = 1; i <= n; i++) {
		int p, c, x;
		cin >> p >> c >> x;
		a[i].set(p, c, x); 
	}
	sort(a + 1, a + n + 1);
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= A + B; j++) dp[i][j] = -inf;
	}
	dp[0][A + B] = 0;
	for(int i = 1; i <= n; i++) {
		int p = a[i].p, x = a[i].x, c = a[i].c;
		for(int j = 0; j <= A + B; j++) {
			mxx(dp[i][j], dp[i - 1][j]);
			if(j - x * c >= A) mxx(dp[i][j - x * c], dp[i - 1][j] + p);
			else if(j > A) {
				int cost = c - (j - A) / x;
				if(A - cost >= 0) mxx(dp[i][A - cost], dp[i][j] + p);
			} else if(j - c >= 0) mxx(dp[i][j - c], dp[i][j] + p);
		}
	}
	int ans = 0;
	for(int i = 0; i <= A + B; i++) {
		mxx(ans, dp[n][i]);
	}
	cout << ans << '\n';
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