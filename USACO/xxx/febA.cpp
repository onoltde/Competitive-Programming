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

template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

const int mxn = 110;
int a[mxn], b[mxn], c[mxn];

void go() {
	int n, tc, tm;
	cin >> n >> tc >> tm;
	int suma = 0, sumb = 0;
	for(int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i];
	}
	int ans = 5000;
	for(int i = 0; i < tm; i++) {
		bool can = 1;
		int mx = 0;
		for(int j = 1; j <= n; j++) {
			int tot = max(0LL, a[j] * tc + (tm - i) * b[j] - c[j]);
			mxx(mx, (tot + a[j] - 1) / a[j]);
		}
		if(mx < tc) {
			mnn(ans, i + mx);
		}
	}
	cout << ans << '\n';
}
 
signed main() {
	fast;
	int t = 1;
	cin >> t;
	while(t--) {
		go();
	}
	return 0;
}