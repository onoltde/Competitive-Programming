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

const int mxn = 5e4 + 10, inf = 1e9 + 10;
int a[mxn], mn[mxn], vis[mxn];
vector<int> cm[mxn], g[55];

void go() {
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		cm[a[i]].pb(i);
		mn[i] = inf;
	}
	for(int i = 1; i <= k; i++) {
		for(int j = 1; j <= k; j++) {
			char ch;
			cin >> ch;
			if(ch == '1') {
				g[i].pb(j);
			}
			else if(i == j && i != a[1]) {
				g[i].pb(j);
			}
		}
		sort(all(cm[i]));
	}
	mn[1] = 0;
	priority_queue<pair<int, int>> q;
	q.push({mn[1], 1});
	while(q.size()) {
		int x = q.top().ss; q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(int p : g[a[x]]) {
			int nx = upper_bound(all(cm[p]), x) - cm[p].begin();
			int pr = lower_bound(all(cm[p]), x) - cm[p].begin() - 1;
			if(nx < cm[p].size() && mn[cm[p][nx]] > mn[x] + abs(x - cm[p][nx])) {
				mn[cm[p][nx]] = mn[x] + abs(x - cm[p][nx]);
				q.push({-mn[cm[p][nx]], cm[p][nx]});
			}
			if(pr > -1 && mn[cm[p][pr]] > mn[x] + abs(x - cm[p][pr])) {
				mn[cm[p][pr]] = mn[x] + abs(x - cm[p][pr]);
				q.push({-mn[cm[p][pr]], cm[p][pr]});
			}
		}
	}
	if(mn[n] == inf) mn[n] = -1;
	cout << mn[n] << '\n';
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