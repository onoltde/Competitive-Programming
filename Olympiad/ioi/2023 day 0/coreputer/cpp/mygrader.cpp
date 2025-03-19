#include "coreputer.h"
#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
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

vector<int> my;
int tot, cnt, mx;

int run_diagnostic(std::vector<int> T) {
	int cnt0 = 0, cnt1 = 0;
	cnt++;
	for(auto x : T) {
		cnt0 += my[x];
	}
	cnt1 = tot - cnt0;
	if(cnt0 > cnt1) return 1;
	else if(cnt0 == cnt1) return 0;
	else return -1;
}

void go() {
	int n = 16;
	for(int bit = 1; bit < (1 << n); bit++) {
		my.clear();
		tot = 0;
		cnt = 0;
		for(int i = 0; i < n; i++) {
			if((bit >> i) & 1) my.pb(1);
			else my.pb(0);
			tot += my[i];
		}
		vector<int> res = malfunctioning_cores(n);
		mxx(mx, cnt);
		if(cnt == 19) {
			cout << my << '\n';
		}
		if(res != my) {
			cout << res << '\n' << my << '\n' << '\n';
		}
	}
	cout << " maax:" << mx << '\n';
}

signed main() {
	//#ifndef ONO
	//freopen("file.in", "r", stdin);
	//freopen("file.out", "w", stdout);
	//#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}