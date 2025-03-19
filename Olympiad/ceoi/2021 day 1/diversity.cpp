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

const int mxn = 3e5 + 10, bl = 3333, inf = 1e18 + 10, MX = 300000;
int a[mxn], cnt[mxn], le[mxn], ri[mxn], tot[mxn], ans[mxn];

void add(int x) {
	int s = cnt[x];
	//-+
	// 2 1
	// 2 0
	// 1 0
	// 1 1
	if(tot[s] > 1 && tot[s + 1] == 0) {
		if(ri[s] != inf) le[ri[s]] = s + 1;
		ri[s + 1] = ri[s];
		le[s + 1] = s;
		ri[s] = s + 1;
	} else if(tot[s] == 1 && tot[s + 1] == 0) {
		ri[le[s]] = s + 1;
		if(ri[s] != inf) le[ri[s]] = s + 1;
		le[s + 1] = le[s];
		ri[s + 1] = ri[s];
		le[s] = 0;
		ri[s] = inf;
	} else if(tot[s] == 1 && tot[s + 1] >= 1) {
		ri[le[s]] = s + 1;
		le[s + 1] = le[s];
		le[s] = 0;
		ri[s] = inf;
	}
	tot[s]--;
	tot[s + 1]++;
	cnt[x]++;
}

void rem(int x) {
	int s = cnt[x];
	//+-
	// 1 2
	// 0 2
	// 0 1
	// 1 1
	if(tot[s] > 1 && tot[s - 1] == 0) {
		ri[le[s]] = s - 1;
		le[s - 1] = le[s];
		ri[s - 1] = s;
		le[s] = s - 1;
	} else if(tot[s] == 1 && tot[s - 1] == 0) {
		if(ri[s] != inf) le[ri[s]] = s - 1;
		ri[le[s]] = s - 1;
		le[s - 1] = le[s];
		ri[s - 1] = ri[s];
		le[s] = 0;
		ri[s] = inf;
	} else if(tot[s] == 1 && tot[s - 1] >= 1) {
		if(ri[s] != inf) le[ri[s]] = s - 1;
		ri[s - 1] = ri[s];
		le[s] = 0;
		ri[s] = inf;
	}
	tot[s]--;
	tot[s - 1]++;
	cnt[x]--;
}

int solve(int n) {
	// for(int i = 1; i <= m; i++) ret += (s - i * x) * (y + i * x);
	auto get = [&](int s, int x, int y, int m) -> int {
		if(m == 0) return 0;
		int ret = s * y * m;
		ret -= y * x * (m * (m + 1) / 2);
		ret -= m * (m + 1) * (2 * m + 1) / 6 * x * x; // sus
		ret += s * x * (m * (m + 1) / 2);
		return ret;
	};
	int lsum = 0, rsum = 0, ret = 0, tp = 0;
	for(int i = ri[0]; i < inf; i = ri[i]) {
		int m = tot[i];
		if(ri[i] == inf) m--;
		int m1 = m / 2, m2 = m / 2;
		if(m % 2 == 1) {
			if(tp) m1++;
			else m2++;
			tp ^= 1;
		}
		ret += get(n - lsum, i, lsum, m1);
		ret += get(n - rsum, i, rsum, m2);
		lsum += m1 * i;
		rsum += m2 * i;
	}
	return ret + n * (n + 1) / 2;
}

void go() {
	int n, Q;
	cin >> n >> Q;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	vector<pair<pair<int, int>, int>> q;
	for(int i = 1; i <= Q; i++) {
		int x, y; cin >> x >> y;
		q.eb(make_pair(x, y), i);
	}
	sort(all(q), [&](const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b) {
		if((a.ff.ff + bl - 1) / bl == (b.ff.ff + bl - 1) / bl) return a.ff.ss > b.ff.ss;
		return (a.ff.ff + bl - 1) / bl < (b.ff.ff + bl - 1) / bl;
	});

	tot[0] = inf;
	for(int i = 0; i <= MX; i++) {
		le[i] = 0;
		ri[i] = inf;
	}
	int l = 1, r = 1;
	add(a[1]);
	for(auto it : q) {
		int L = it.ff.ff, R = it.ff.ss, id = it.ss;
		while(r < R) add(a[++r]);
		while(l > L) add(a[--l]);
		while(r > R) rem(a[r--]);
		while(l < L) rem(a[l++]);
		assert(l == L && r == R);
		ans[id] = solve(R - L + 1);
	}
	for(int i = 1; i <= Q; i++) {
		cout << ans[i] << '\n';
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