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
 
#define int long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 1010;

int dp[3][mxn][mxn];

signed main() {
	fast;
	// freopen("cowrun.in", "r", stdin);
	// freopen("cowrun.out", "w", stdout);
	int n;
	cin >> n;
	vector<int> a, b;
	a.pb(0);
	b.pb(0);
	for(int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if(x < 0) {
			a.pb(-x);
		}
		else {
			b.pb(x);
		}
	}
	for(int i = 0; i < mxn; i++) {
		for(int j = 0; j < mxn; j++) {
			dp[0][i][j] = dp[1][i][j] = (int)1e18;
		}
	}
	sort(all(a));
	sort(all(b));
	dp[0][0][0] = dp[1][0][0] = 0;
	int n1 = (int)a.size() - 1;
	int n2 = (int)b.size() - 1;
	for(int i = 0; i <= n1; i++) {
		for(int j = 0; j <= n2; j++) {
			int cs = n - (i + j - 1);
			if(i) {
				dp[0][i][j] = min(dp[0][i-1][j] + cs * (a[i] - a[i-1]), 
								  dp[1][i-1][j] + cs * (a[i] + b[j]));
			}
			if(j) {
				dp[1][i][j] = min(dp[1][i][j-1] + cs * (b[j] - b[j-1]), 
								  dp[0][i][j-1] + cs * (a[i] + b[j]));
			}
		}
	}
	cout << min(dp[0][n1][n2], dp[1][n1][n2]) << '\n';
}