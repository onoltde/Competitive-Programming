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

const int mxn = 1e5 + 10, inf = 1e9 + 10;
int x[mxn], y[mxn];
map<int, vector<int>> mx, my;
map<int, int> mnx, mny;

void go() {
	int n, xl, yl;
	cin >> n >> xl >> yl >> x[0] >> y[0];
	for(int i = 1; i <= n; i++)
		cin >> x[i] >> y[i];
	for(int i = 0; i <= n; i++) {
		mnx[x[i]] = inf;
		mny[y[i]] = inf;
		mx[x[i]].pb(y[i]);
		my[y[i]].pb(x[i]);
	}
	queue<pair<int, int>> q;
	q.push({xl, 1});
	q.push({yl, 0});
	mnx[xl] = 0;
	mny[yl] = 0;
	while(q.size()) {
		int pos = q.front().ff;
		int dir = q.front().ss;
		q.pop();
		if(dir == 1) {
			for(int ny : mx[pos]) {
				if(mny[ny] > mnx[pos] + 1) {
					mny[ny] = mnx[pos] + 1;
					q.push({ny, dir ^ 1});
				}
			}
		}
		else {
			for(int nx : my[pos]) {
				if(mnx[nx] > mny[pos] + 1) {
					mnx[nx] = mny[pos] + 1;
					q.push({nx, dir ^ 1});
				}
			}
		}
	}
	cout << min(mnx[x[0]], mny[y[0]]) << '\n';
}

signed main() {
	#ifndef ONO
	freopen("lasers.in", "r", stdin);
	freopen("lasers.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}