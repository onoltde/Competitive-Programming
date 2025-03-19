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

const int mxn = 1e7 + 10;
char str[mxn];

pair<int, int> merge(pair<int, int> a, pair<int, int> b, int tp) {
	pair<int, int> ret{0, 0};
	if(tp == 1) {
		ret.ff = a.ff + b.ff + 1;
		ret.ss = min(a.ss, b.ss);
	} else {
		ret.ff = min(a.ff, b.ff);
		ret.ss = a.ss + b.ss + 1;
	}
	return ret;
}

void go() {
	cin >> str + 1;
	int n = strlen(str + 1);
	int tot = 0;
	stack<tuple<pair<int, int>, pair<int, int>, int>> s;
	pair<int, int> ans{0, 0};

	function<void(pair<int, int>)> add = [&](pair<int, int> dp) {
		if(s.size() == 0) {
			ans = dp;
			return;
		}
		pair<int, int> a1, a2;
		int tp;
		tie(a1, a2, tp) = s.top();
		s.pop();
		if(a1.ff == -1) {
			s.push(make_tuple(dp, a2, tp));
		} else {
			add(merge(a1, dp, tp));
		}
	};

	for(int i = 1; i <= n; i++) {
		if(str[i] == 'm') {
			s.push(make_tuple(make_pair(-1, -1), make_pair(-1, -1), (str[i + 1] == 'a')));
		} else if(str[i] == '?') {
			tot++;
			add(make_pair(0, 0));
		}
	}
	cout << tot - ans.ff - ans.ss << '\n';
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