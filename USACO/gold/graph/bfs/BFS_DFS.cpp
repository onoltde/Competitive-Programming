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

const int mxn = 5010;
int a[mxn], b[mxn];

void go() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	for(int i = 1; i <= n; i++)
		cin >> b[i];
	if(n > 1 && b[2] != a[2]) {
		cout << -1 << '\n';
		return;
	}
	vector<pair<int, int>> ans;
	for(int i = 2; i <= n; i++)
		ans.eb(1, a[i]);
	for(int i = 3; i <= n; i++)
		ans.eb(b[i - 1], b[i]);
	cout << ans.size() << '\n';
	for(auto [x, y] : ans)
		cout << x << ' ' << y << '\n';
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