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

const int mxn = 1e5 + 10;
const ll inf = 1e18 + 10;
int n;
ll dp[mxn][3];
vector<pair<int, ll>> g[mxn];

ll travel_plan(int N, int M, int R[][2], int L[], int K, int P[]) {
	n = N;
	for(int i = 0; i < M; i++) {
		int x = R[i][0];
		int y = R[i][1];
		int t = L[i];
		g[x].pb({y, t});
		g[y].pb({x, t});
	}
	for(int i = 0; i < n; i++) {
		dp[i][0] = dp[i][1] = inf;
	}
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
	for(int i = 0; i < K; i++) {
		dp[P[i]][0] = dp[P[i]][1] = 0;
		q.push({0, P[i]});
	}
	while(q.size()) {
		ll cs = q.top().ff;
		int x = q.top().ss;
		q.pop();
		if(dp[x][1] != cs) continue;
		for(auto [y, t] : g[x]) {
			if(cs + t < dp[y][0]) {
				if(dp[y][0] != inf && dp[y][0] != dp[y][1]) {
					dp[y][1] = dp[y][0];
					q.push({dp[y][1], y});
				}
				dp[y][0] = cs + t;
			}
			else if(cs + t < dp[y][1]) {
				dp[y][1] = cs + t;
				q.push({dp[y][1], y});
			}
		}
	}
	// for(int i = 0; i < n; i++) {
	// 	cout << dp[i][0] << ' ' << dp[i][1] << '\n';
	// }
	assert(dp[0][1] != inf);
	return dp[0][1];
}

void go() {
	int N, M, K;
	cin >> N >> M >> K;
	int R[M][2], L[M], P[K]; 
	for(int i = 0; i < M; i++) {
		cin >> R[i][0] >> R[i][1] >> L[i];
	}
	for(int i = 0; i < K; i++) {
		cin >> P[i];
	}
	cout << travel_plan(N, M, R, L, K, P) + 1 << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("file.in", "r", stdin);
	freopen("file.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}