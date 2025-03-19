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

const int mxn = 1e6 + 10, inf = 1e18;
int a[mxn], e[mxn];
bool can[mxn];
vector<int> cnt[mxn], M[mxn];

struct pqpii : priority_queue<pair<int, int>> {
	auto begin() const {
		return c.begin();
	}
	auto end() const {
		return c.end();
	}
};

vector<int> get(int x) {
	vector<int> ret;
	for(int i = 2; i * i <= x; i++) {
		if(x % i) continue;
		ret.pb(i);
		while(x % i == 0) {
			x /= i;
		}
	}
	if(x > 1) ret.pb(x);
	return ret;
}

void go() {
	int k, n;
	cin >> n >> k;
	int g = 0;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		g = __gcd(g, a[i]);
	}
	for(int i = 1; i <= n; i++) {
		cin >> e[i];
	}
	vector<int> P = get(g);
	int N = P.size();
	unordered_map<int, pqpii> mp;
	for(int i = 1; i <= n; i++) {
		cnt[i].resize(N, 0);
		M[i].resize(N, 1);
		int x = a[i];
		for(int j = 0; j < N; j++) {
			while(x % P[j] == 0) {
				cnt[i][j]++;
				M[i][j] *= P[j];
				x /= P[j];
			}
		}
		a[i] = a[i] / x;
		mp[a[i]].push({e[i], i});
		can[i] = 1;
		if(mp[a[i]].size() > N) {
			can[mp[a[i]].top().ss] = 0;
			mp[a[i]].pop();
		}
	}
	mp.clear();
	vector<vector<int>> b(n + 10);
	for(int i = 1; i <= n; i++) {
		if(!can[i]) continue;
		for(int j = 0; j < (1 << N); j++) {
			int mul = 1;
			for(int k = 0; k < N; k++) {
				if((j >> k) & 1) mul *= M[i][k];
			}
			if(mul <= k) {
				mp[j].push({e[i], i});
				if(mp[j].size() > N) {
					mp[j].pop();		
				}
			}
		}
		can[i] = 0;
	}
	for(int i = 0; i < (1 << N); i++) {
		for(auto &it : mp[i]) {
			b[it.ss].pb(i);
			can[it.ss] = 1;
		}
	}
	vector<vector<int>> dp(N + 1, vector<int>((1 << N), inf));
	dp[0][0] = 0;
	for(int i = 1; i <= n; i++) {
		if(!can[i]) continue;
		for(int j = N - 1; j >= 0; j--) {
			for(int mask : b[i]) {
				mnn(dp[j + 1][mask], dp[j][0] + e[i]);
				int bit = ((1 << N) - 1) ^ mask;
				for(int sub = bit; sub; sub = (sub - 1) & bit) {
					mnn(dp[j + 1][sub | mask], dp[j][sub] + e[i]);
				}
			}
		}
	}
	int ans = inf;
	for(int i = 0; i <= N; i++) {
		if(dp[i][(1 << N) - 1] == inf) continue;
		mnn(ans, dp[i][(1 << N) - 1] * i);
	}
	if(ans == inf) ans = -1;
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