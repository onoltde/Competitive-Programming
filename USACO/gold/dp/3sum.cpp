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

#define ll long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 5100;
const int mxm = 2e6 + 10;

int a[mxn], p[mxn];
vector<pair<int, int>> q[mxn];
ll f[mxn];
int pp[mxm];
int pre[mxn][mxn];

signed main() {
	fast;
	#ifndef ONO
	freopen("threesum.in", "r", stdin);
	freopen("threesum.out", "w", stdout);
	#endif
	int n, T;
	cin >> n >> T;
	map<int, vector<int>> g;
	set<int> s;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		s.in(a[i]);
	}
	vector<int> lol;
	for(int x : s) {
		lol.pb(x);
	}
	for(int i = 1; i <= n; i++) {
		p[i] = lower_bound(all(lol), a[i]) - lol.begin() + 1;
		pre[i][p[i]] = 1;
		pp[a[i] + (int)1e6] = p[i];
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			pre[i][j] += pre[i - 1][j];
		}
	}
	for(int i = 0; i < T; i++) {
		int x, y;
		cin >> x >> y;
		q[y].eb(x, i);
	}
	vector<pair<int, ll>> ans;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < i; j++) {
			int gg = -a[i] - a[j];
			if(abs(gg) > (int)1e6) {
				continue;
			}
			if(pp[gg + (int)1e6] == 0) {
				continue;
			}
			int num = pre[i - 1][pp[gg + (int)1e6]] - pre[j][pp[gg + (int)1e6]];
			for(int k = j; k <= n; k += (k&-k)) {
				f[k] += num;
			}
		}
		ll sum = 0;
		for(int j = i; j >= 1; j -= (j&-j)) {
			sum += f[j];
		}
		for(auto it : q[i]) {
			int x = it.first;
			int ind = it.second;
			ll res = 0;
			for(int j = x - 1; j >= 1; j -= (j&-j)) {
				res += f[j];
			}
			ans.eb(ind, sum - res);
		}
	}
	sort(all(ans));
	for(auto it : ans) {
		cout << it.second << '\n';
	}
	return 0;
}