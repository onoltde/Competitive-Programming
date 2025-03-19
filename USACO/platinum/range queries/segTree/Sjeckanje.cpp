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

const int mxn = 2e5 + 10;
int a[mxn], b[mxn];

struct node {
	int dp[2][2];
	int left, right;
	node() {
		dp[0][0] = dp[1][1] = dp[0][1] = dp[1][0] = 0;
		left = right = 0;
	}
	void set(int val) {
		dp[1][1] = val;
		right = left = val;
		dp[0][0] = dp[1][0] = dp[0][1] = 0;
	}
} d[mxn * 4];

node merge(node tl, node tr) {
	node ret;
	ret.left = tl.left;
	ret.right = tr.right;
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			for(int k = 0; k < 2; k++) {
				for(int p = 0; p < 2; p++) {
					if(j && k) {
						if((tl.right > 0) & (tr.left > 0)) {
							mxx(ret.dp[i][p], tl.dp[i][j] + tr.dp[k][p]);
						}
					}
					else {
						mxx(ret.dp[i][p], tl.dp[i][j] + tr.dp[k][p]);
					}
				}
			}
		}
	}
	return ret;
}

void build(int l, int r, int i) {
	if(l == r) {
		d[i].set(a[l]);
		return;
	}
	int m = (l + r) / 2;
	build(l, m, i * 2);
	build(m + 1, r, i * 2 + 1);
	d[i] = merge(d[i * 2], d[i * 2 + 1]);
}

// void update(int l, int r, int i, int x, int y) {

// }

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i < n; i++) {
		b[i] = a[i + 1] - a[i];
	}
	build(1, n - 1, 1);
	while(m--) {
		int l, r, x;
		
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