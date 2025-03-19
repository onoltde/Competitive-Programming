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

const int mxn = 2010;
int vis1[mxn][mxn], vis2[mxn][mxn];
vector<int> g1[mxn], g2[mxn];

void go() {
	int n1, n2, m1, m2;
	cin >> n1 >> n2 >> m1 >> m2;
	for(int i = 1; i <= m1; i++) {
		int x, y;
		cin >> x >> y;
		g1[x].pb(y);
	}	
	for(int i = 1; i <= m2; i++) {
		int x, y;
		cin >> x >> y;
		g2[x].pb(y);
	}
	queue<int> q;
	q.push(1);
	vis1[0][1] = 1;
	for(int i = 1; i <= 2000; i++) {
		queue<int> tmp;
		while(q.size()) {
			int x = q.front(); q.pop();
			for(int y : g1[x]) {
				if(!vis1[i][y]) {
					vis1[i][y] = 1;
					tmp.push(y);
				}
			}
		}
		swap(tmp, q);
	}

	while(q.size()) q.pop();
	q.push(1);
	vis2[0][1] = 1;
	for(int i = 1; i <= 2000; i++) {
		queue<int> tmp;
		while(q.size()) {
			int x = q.front(); q.pop();
			for(int y : g2[x]) {
				if(!vis2[i][y]) {
					vis2[i][y] = 1;
					tmp.push(y);
				}
			}
		}
		swap(tmp, q);
	}
	int qu;
	cin >> qu;
	while(qu--) {
		int p;
		cin >> p;
		int ans = 0;
		for(int i = 0; i <= p; i++) {
			ans |= (vis1[i][n1] & vis2[p - i][n2]);
		}
		cout << (ans ? "Yes\n" : "No\n");
	}
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