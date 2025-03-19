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

#define ll long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 5100;

int is[mxn][mxn];
char str[mxn];
vector<pair<int, int>> q[mxn];
ll f[mxn];

signed main() {
	fast;
	cin >> str + 1;
	int n = strlen(str + 1);
	int T;
	cin >> T;
	vector<pair<int, ll>> ans;
	for(int i = 0; i < T; i++) {
		int x, y;
		cin >> x >> y;
		q[y].pb({x, i});
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i; j >= 1; j--) {
			if(str[i] == str[j] && (i == j || j + 1 == i || is[j + 1][i - 1])) {
				is[j][i] = 1;
				for(int k = j; k <= n; k += (k&-k)) {
					f[k]++;
				}
			}
		}
		ll sum = 0;
		for(int j = i; j >= 1; j -= (j&-j)) {
			sum += f[j];
		}
		for(auto it : q[i]) {
			int ind = it.second;
			int x = it.first;
			ll res = 0;
			for(int j = x - 1; j >= 1; j -= (j&-j)) {
				res += f[j];
			}
			ans.pb({ind, sum - res});
		}
	}
	sort(all(ans));
	for(auto it : ans) {
		cout << it.second << '\n';
	}
	return 0;
}