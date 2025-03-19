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

const int mxn = 31;
const string BASE = "KEY";
int dp[mxn][mxn][mxn][mxn * mxn];

void go() {
	string str;
	cin >> str;
	int k;
	cin >> k;
	dp[0][0][0][0] = 1;
	vector<vector<int>> pos(3);
	for(int i = 0; i < str.size(); i++) {
		for(int j = 0; j < 3; j++) {
			if(str[i] == BASE[j]) pos[j].pb(i);
		}
	}
	vector<int> id(3);
	int lim = str.size() * str.size() + 10;
	for(id[0] = 0; id[0] <= pos[0].size(); id[0]++) {
		for(id[1] = 0; id[1] <= pos[1].size(); id[1]++) {
			for(id[2] = 0; id[2] <= pos[2].size(); id[2]++) {
				for(int tot = 0; tot < lim; tot++) {
					for(int ch = 0; ch < 3; ch++) {
						if(id[ch] == pos[ch].size()) continue;
						int cur = 0;
						for(int res = 0; res < 3; res++) {
							if(ch == res) continue;
							for(int it = 0; it < id[res]; it++) {
								if(pos[res][it] > pos[ch][id[ch]]) cur++;
							}
						}
						if(cur + tot <= lim) {
							if(ch == 0) dp[id[0] + 1][id[1]][id[2]][cur + tot] += dp[id[0]][id[1]][id[2]][tot];
							if(ch == 1) dp[id[0]][id[1] + 1][id[2]][cur + tot] += dp[id[0]][id[1]][id[2]][tot];
							if(ch == 2) dp[id[0]][id[1]][id[2] + 1][cur + tot] += dp[id[0]][id[1]][id[2]][tot];
						}
					}
				}
			}
		}
	}
	int ans = 0;
	mnn(lim, k);
	for(int i = 0; i <= lim; i++) {
		ans += dp[pos[0].size()][pos[1].size()][pos[2].size()][i];
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