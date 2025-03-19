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

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

template<typename T>
T gcd(T a,T b){
	T aa=__builtin_ctz(a);
	T bb=__builtin_ctz(b);
	T k=min(aa,bb);
	b>>=bb;
	while(a){
		a>>=aa;
		T c=b-a;
		aa=__builtin_ctz(c);
		b=min(a,b);
		a=abs(c);
	}
	return b<<k;
}

template<typename T>
T lcm(T a,T b){
	return a*b/gcd(a,b);
}

const int mxn=1e6+10,mod=998244353;

int fpow(int a,int z){
	a%=mod;
	int ret=1;
	for(; z; z>>=1){
		if(z&1) ret=(ret*a)%mod;
		a=(a*a)%mod;
	}
	return ret;
}

vector<int> fac(1,1),inv(1,1);

void init(){

	for(int i=1; i<=mxn; i++){
		// fac.pb((fac.back()*i)%mod);
		// inv.pb(fpow(fac.back(),mod-2));
		inv.pb(fpow(i,mod-2));
	}
}

int C(int n,int k){
	// return ((fac[n]*inv[k])%mod*inv[n-k])%mod;
	return ((fac[n])%mod*inv[n-k])%mod;
}


void go() {
	int n;
	cin >> n;
	int tot = 0;
	vector<int> k(n);
	vector<vector<int>> a;
	// map<int, int> mp;
	vector<int> mp(mxn + 10, 0);
	for(int i = 0; i < n; i++) {
		cin >> k[i];
		tot += k[i];
		a.pb(vector<int>(k[i], 0));
		for(int j = 0; j < k[i]; j++) {
			cin >> a[i][j];
			mp[a[i][j]]++;
		}
	}
	int ans = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < k[i]; j++) {
			ans = (ans + inv[n] * inv[k[i]] % mod * inv[n] % mod * mp[a[i][j]] % mod) % mod;
		}
	}
	cout << ans << '\n';
}

signed main() {
	fast;
	init();
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
}