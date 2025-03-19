#include "fish.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

// #define int long long
 
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

template<typename T>
void mxx(T &a, T b) {
	if(a < b) a = b;
}

long long max_weights(int n, int m, vector<int> X, vector<int> Y, vector<int> W) {
	vector<vector<pair<int, long long>>> pos(n);
	for(int i = 0; i < m; i++) {
		pos[X[i]].eb(Y[i], W[i]);
	}
	vector<vector<pair<long long, long long>>> dp(n);
	for(int i = 0; i < n; i++) {
		sort(all(pos[i]));
		dp[i].resize(pos[i].size(), make_pair(0, 0));
	}
	long long ans = 0;
	for(int i = 1; i < n; i++) {
		int sz = (int)pos[i].size();

		int r = (int)pos[i - 1].size() - 1;
		for(int j = sz - 1; j >= 0; j--) {
			dp[i][j].ss = ans + pos[i][j].ss;
			if(j + 1 < sz) mxx(dp[i][j].ss, dp[i][j + 1].ss + pos[i][j].ss);
			while(r >= 0 && pos[i - 1][r].ff > pos[i][j].ff) {
				mxx(dp[i][j].ss, max(dp[i - 1][r].ff, dp[i - 1][r].ss) + pos[i][j].ss);
				r--;
			}
		}

		for(int j = 0; j < (int)pos[i - 1].size(); j++) {
			mxx(ans, dp[i - 1][j].ss);
		}

		int l = 0;
		for(int j = 0; j < sz; j++) {
			if(j) dp[i][j].ff = dp[i][j - 1].ff;
			while(l < pos[i - 1].size() && pos[i - 1][l].ff < pos[i][j].ff) {
				dp[i][j].ff += pos[i - 1][l].ss;
				mxx(dp[i][j].ff, dp[i - 1][l].ff + pos[i - 1][l].ss);
				l++;
			}
		}

		for(int j = 0; j < sz; j++) {
			mxx(dp[i][j].ff, ans);
		}

		long long sum = 0;
		for(int j = (int)pos[i - 1].size() - 1; j >= 0; j--) {
			sum += pos[i - 1][j].ss;
			mxx(ans, dp[i - 1][j].ff + sum);
		}
	}
	for(int j = 0; j < pos.back().size(); j++) {
		mxx(ans, dp.back()[j].ss);
	}
	return ans;
}