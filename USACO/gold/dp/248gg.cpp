#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

typedef long long ll;
 
//#define int long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 250;
int dp[mxn][mxn];

signed main() {
	fast;
	freopen("248.in", "r", stdin);
	freopen("248.out", "w", stdout);
	int n;
	cin >> n;
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		dp[i][i] = x;
		mxx(ans, x);
	}
	for(int i = n; i >= 1; i--) {
		for(int j = i+1; j <= n; j++) {
			for(int k = i; k < j; k++) {
				int tmp = 0;
				if(dp[i][k] == dp[k+1][j]) {
					tmp = dp[i][k] + 1;
				}
				mxx(dp[i][j], tmp);
			}
			mxx(ans, dp[i][j]);
		}
	}
	cout << ans << '\n';
	return 0;
}