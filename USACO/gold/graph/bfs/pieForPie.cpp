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

template<typename T, typename U>
ostream & operator << (ostream &out, const pair<T, U> &c) {
	out << c.first << ' ' << c.second;
    return out;
}

template<typename T>
ostream & operator << (ostream &out, vector<T> &v) {
	const int sz = v.size();
	for (int i = 0; i < sz; i++) {
		if (i) out << ' ';
		out << v[i];
	}
    return out;
}

template<typename T>
istream & operator >> (istream &in, vector<T> &v) {
	for (T &x : v) in >> x;
    return in;
}


template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

const int mxn = 2e5 + 10;
int ans[mxn];

void go() {
	int n, d;
	cin >> n >> d;
	set<array<int, 3>> sa, sb;
	queue<pair<int, int>> q;
	for(int i = 0; i < n * 2; i++) {
		int x, y;
		cin >> x >> y;
		if(i >= n) swap(x, y);
		if(y == 0) {
			ans[i] = 1;
			q.push({x, i});
			continue;
		}
		if(i < n) sa.in({y, x, i});
		else sb.in({y, x, i});
	}
	while(q.size()) {
		int x = q.front().ff;
		int i = q.front().ss;
		q.pop();
		if(i < n) {
			while(sb.size()) {
				auto it = sb.lower_bound({x + 1, 0, 0});
				if(it == sb.begin()) break;
				it--;
				array<int, 3> val = *it;
				if(val[0] + d < x) break;
				ans[val[2]] = ans[i] + 1;
				q.push({val[1], val[2]});
				sb.erase(it);
			}
		}
		else {
			while(sa.size()) {
				auto it = sa.lower_bound({x + 1, 0, 0});
				if(it == sa.begin()) break;
				it--;
				array<int, 3> val = *it;
				if(val[0] + d < x) break;
				ans[val[2]] = ans[i] + 1;
				q.push({val[1], val[2]});
				sa.erase(it);
			}
		}
	}
	for(int i = 0; i < n; i++) {
		if(ans[i] == 0) ans[i]--;
		cout << ans[i] << '\n';
	}
}
 
signed main() {
	#ifndef ONO
	freopen("piepie.in", "r", stdin);
	freopen("piepie.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}