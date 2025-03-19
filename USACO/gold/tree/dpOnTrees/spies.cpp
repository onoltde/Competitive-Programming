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
 
// typedef long long ll;
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

const int mxn = 1e6 + 2;
int par[mxn], cn[mxn];
vector<int> path;
bool vis[mxn], used[mxn];
int ans;

void go() {
	int n;
	cin >> n;
	int i, j, cnt, x, sz, id;
	for(i = 1; i <= n; i++) {
		cin >> par[i];
		cn[par[i]]++;
	}
	for(int i = 1; i <= n; i++) {
		if(cn[i] == 0) path.pb(i);
	}
	while(!path.empty()) {
		x = path.back();
		vis[x] = 1;
		path.pop_back();
		if(!used[x] && !used[par[x]]) {
			used[par[x]] = 1;
			ans++;
		}
		cn[par[x]]--;
		if(cn[par[x]] == 0) path.pb(par[x]);
	}
	for(i = 1; i <= n; i++) {
		if(vis[i] == 0) {
			x = i;
			path.clear();
			path.pb(x);
			while(par[path.back()] != x) {
				path.pb(par[path.back()]);
			}
			for(j = 0; j < path.size(); j++) {
				vis[path[j]] = 1;
			}
			id = 0;
			for(j = 0; j < path.size(); j++) {
				if(used[path[j]]) {
					id = j;
					break;
				}
			}
			cnt = 0;
			for(j = 0; j < path.size(); j++) {
				if(used[path[(j + id) % path.size()]]) {
					ans += cnt / 2;
					cnt = 0;
				} else {
					cnt++;
				}
			}
			ans += cnt / 2;
		}
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