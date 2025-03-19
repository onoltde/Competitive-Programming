#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

#define int unsigned long long

#define ll long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 20;

int a[mxn][mxn];
int n;
int dp[1 << mxn][mxn];
int dd[mxn];
int ans[1 << mxn];

int solve() {
	for(int i = 0; i < n; i++) {
		dp[1 << i][i]++;
		for(int m = 1 << i; m < (1 << (i + 1)); m++) {
			for(int l = 0; l <= i; l++) {
				if(!(m & (1 << l))) {
					continue;
				}
				for(int k = 0; k < i; k++) {
					if(m & (1 << k)) {
						continue;
					}
					if(dd[l] & (1 << k))
						dp[m ^ (1 << k)][k] += dp[m][l];
				}
				if(dd[l] & (1 << i)) {
					ans[m] += dp[m][l];
				}
			}
			for(int k = i + 1; k < n; k++) {
				dp[(1 << k) ^ m][k] += ans[m];
			}
		}
	}
}

int find(string str) {
	int d1 = 0;
	int d2 = 0;
	for(int i = 0; i < n; i++) {
		if(str[i] == 'H') {
			d1 ^= (1 << i);
		}
		else {
			d2 ^= (1 << i);
		}
	}
	return ans[d1] * ans[d2];
	return 0;
}

signed main() {
	fast;
	// #ifndef ONO
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	// #endif
	cin >> n;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
		for(int j = 0; j < n; j++) {
			dd[i] ^= (1 << (a[i][j] - 1));
			if(a[i][j] == i + 1) {
				break;
			}
		}
	}

	solve();
	ans[0] = 1;
	int q;
	cin >> q;
	while(q--) {
		string str;
		cin >> str;
		cout << find(str) << '\n';
	}
	return 0;
}