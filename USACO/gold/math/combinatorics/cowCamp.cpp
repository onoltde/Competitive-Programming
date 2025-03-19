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

const int mxn = 1010;
double pro[mxn][mxn], pre[mxn], sum[mxn];

double get(double val, double a, double b, int l) {
	return val * pow(a, l) + b * (pow(a, l) - 1) / (a - 1);
}

void go() {
	int n, k;
	cin >> n >> k;
	n--;
	pro[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		pro[i][0] = pro[i - 1][0] / 2;
		for(int j = 1; j <= i; j++) {
			pro[i][j] = pro[i - 1][j] / 2 + pro[i - 1][j - 1] / 2;
		}
	}
	pre[0] = pro[n][0];
	sum[0] = 0;
	for(int i = 1; i <= n; i++) {
		pre[i] = pre[i - 1] + pro[n][i];
		sum[i] = sum[i - 1] + pro[n][i] * i;
	}
	double ans = 0;
	for(int i = 0; i < k;) {
		int val = floor(ans);
		int l = 0, r = k - i;
		double a = pre[val], b = sum[n] - sum[val];
		while(r - l > 1) {
			int m = (r + l) / 2;
			if(floor(get(ans, a, b, m)) == val) l = m;
			else r = m;
		}
		i += r;
		ans = get(ans, a, b, r);
	}
	cout << fixed << setprecision(10) << ans + 1 << '\n';
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