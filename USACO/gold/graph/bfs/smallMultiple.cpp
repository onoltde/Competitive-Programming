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

const int mxn = 1e5 + 10, inf = 1e9 + 10;
int mn[mxn], vis[mxn];

void go() {
	int k;
	cin >> k;
	for(int i = 0; i <= k; i++) mn[i] = inf;
	priority_queue<pair<int, int>> q;
	q.push({-1, 1});
	mn[1] = 1;
	while(q.size()) {
		int x = q.top().ss; q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		int nxt = (x * 10) % k;
		if(mn[nxt] > mn[x]) {
			mn[nxt] = mn[x];
			q.push({-mn[nxt], nxt});
		}
		if(x % 10 < 9 && mn[x + 1] > mn[x] + 1) {
			mn[x + 1] = mn[x] + 1;
			q.push({-mn[x + 1], x + 1});
		}
	}
	cout << mn[0] << '\n';
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