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

#define ll long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mod = 1e9 + 7;
const int mxn = 510;

int fpow(int a, int z){
	a %= mod;
	z %= (mod - 1);
	int ret = 1;
	for(; z; z >>= 1){
		if(z & 1) ret = (ret * a) % mod;
		a = (a * a) % mod;
	}
	return ret;
}

vector<int> fac(1,1),inv(1,1);

void init(){

	for(int i=1; i<=mxn; i++){
		fac.pb((fac.back() * i) % mod);
		inv.pb(fpow(fac.back(), mod - 2));
	}
}

int C(int n,int k){
	return ((fac[n] * inv[k]) % mod * inv[n - k]) % mod;
}

int dp[mxn][mxn]; 
char str[mxn];
int n;

int solve(int l, int r) {
	if(dp[l][r] != -1) {
		return dp[l][r];
	}
	if(l > r) {
		return 1;
	}
	if((r - l) % 2 == 0) {
		return 0;
	}
	int res = 0;
	for(int i = l + 1; i <= r; i++) {
		if(str[l] == str[i]) {
			int tot1 = (i - l - 1) / 2 + 1;
			int tot2 = (r - i) / 2;
			res = (solve(l + 1, i - 1) * solve(i + 1, r) % mod * C(tot1 + tot2, tot1) % mod + res) % mod;
		}
	}
	return dp[l][r] = res;
}

signed main() {
	fast;	
	// #ifndef ONO
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	// #endif
	cin >> str + 1;
	n = strlen(str + 1);
	init();
	for(int i = 0; i < mxn; i++) {
		for(int j = 0; j < mxn; j++) {
			dp[i][j] = -1;
		}
	}
	cout << solve(1, n) << '\n';
	return 0;
}