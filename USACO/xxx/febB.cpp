#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define mp make_pair
 
#define int long long
 
typedef long long ll;
 
template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int inf = 1e9 + 10;
const int mxn = 2e5 + 10;

vector<array<int, 3>> g[mxn];
int mn[mxn], a[mxn], id[mxn];

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++) {
		int s, ts, e, te;
		cin >> s >> ts >> e >> te;
		g[s].pb({ts, te, e});
	}
	for(int i = 1; i <= n; i++) {
		sort(all(g[i]));
		id[i] = g[i].size();
		cin >> a[i];
	}
	priority_queue<pair<int, int>> q;
	q.push({-a[1], 1});
	for(int i = 2; i <= n; i++) {
		mn[i] = inf;
	}
	while(q.size()) {
		int now = q.top().ss;
		int cs = q.top().ff; q.pop();
		if(mn[now] < cs) continue;
		int ls = id[now];
		while(id[now] > 0 && g[now][id[now] - 1][0] >= cs + a[now]) id[now]--;
		for(int i = id[now]; i < ls; i++) {
			int u = g[now][i][2];
			int te = g[now][i][1];
			if(mn[u] > te) {
				mn[u] = te;
				q.push({te, u});
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		if(mn[i] == inf) cout << -1;
		else cout << mn[i];
		cout << '\n';
	}
}

signed main() {
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}