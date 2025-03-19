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

const int mod = 998244353;

int fpow(int a, int z) {
	int ret = 1;
	for(; z > 0; z >>= 1) {
		if(z & 1) ret = (ret * a) % mod;
		a = (a * a) % mod;
	}
	return ret;
}

void go() {
	int _;
	cin >> _;
	queue<pair<int, int>> q;
	int sum = 0, prod = 1;
	while(_--) {
		int tp;
		cin >> tp;
		if(tp == 0) {
			int a, b;
			cin >> a >> b;
			q.push({a, b});
			sum = (sum * a + b) % mod;
			prod = (prod * a) % mod;
		} else if(tp == 1) {
			if(q.size() == 0) continue;
			int a = q.front().ff, b = q.front().ss;
			q.pop();
			prod = (prod * fpow(a, mod - 2)) % mod;
			sum = ((sum - prod * b) % mod + mod) % mod;
		} else {
			int x;
			cin >> x;
			cout << (sum + prod * x) % mod << '\n';
		}
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