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
int dp[mxn];
vector<int> g[mxn];

void dfs(int to, int fr, int k) {
	vector<int> v;
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs(x, to, k);
		v.pb(dp[x]);
		if(dp[x] == -1) {
			dp[to] = -1;
			return;
		}
	}
	sort(all(v));
	while(v.size() && v.back() == k - 1) {
		v.pop_back();
	}
	if(v.size() == 0) {
		dp[to] = 0;
	} else {
		int kk = -1;
		int l = 0, r = v.size() - 1;
		while(1) {
			if(l > r) break;
			if(l == r) {
				if(kk != -1) {
					dp[to] = -1;
					return;
				} else {
					kk = v[l];
					break;
				}
			}
			int sum = v[l] + v[r] + 2;
			if(sum == k) {
				l++;
				r--;
			} else if(kk != -1) {
				dp[to] = -1;
				return;
			} else if(sum < k) {
				kk = v[l];
				l++;
			} else {
				kk = v[r];
				r--;
			}
		}
		dp[to] = kk + 1;
	}
}

void go() {
	int n;
	cin >> n;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(g[i].size() == 1) cnt++;
	}
	if(cnt == n - 1) {
		while(1);
	}
	vector<int> ans(n + 10, 0), vis(n + 10);
	for(int i = 1; i < n; i++) {
		if((n - 1) % i) continue;
		if(vis[i]) continue;
		dfs(1, 0, i);
		if(dp[1] == 0) {
			ans[i] = 1;
		} else {
			for(int j = i; j < n; j += i) {
				vis[j] = 1;
			}
		}
	}
	for(int i = 1; i < n; i++) {
		cout << ans[i];
	}
	cout << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("deleg.in", "r", stdin);
	freopen("deleg.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}