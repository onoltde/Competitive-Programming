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

const int mod = 1e9 + 7, mxn = 2e5 + 10;
const string gen = "ACGT";
int dp[mxn][4][4][4];

void go() {
	string str;
	cin >> str;
	int n = str.size();
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(str[0] == '?' || str[0] == gen[j]) {
				dp[0][i][j][j] = 1;
			}
		}
	}
	for(int i = 1; i < n; i++) {
		for(int nw = 0; nw < 4; nw++) {
			if(str[i] == '?' || str[i] == gen[nw]) {
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int j = 0; j < 4; j++) {
							if(j != nw) dp[i][k][l][nw] = (dp[i][k][l][nw] + dp[i - 1][k][l][j]) % mod;
							if(k == j) dp[i][l][nw][nw] = (dp[i][l][nw][nw] += dp[i - 1][k][l][j]) % mod;
						}
					}
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			ans = (ans + dp[n - 1][i][j][i]) % mod;
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