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

void go() {
	int n;
	cin >> n;
	vector<int> cnt(30, 0);
	vector<vector<int>> g(30);
	vector<string> str(n + 1);
	bool kk = 0;
	for(int i = 1; i <= n; i++) {
		cin >> str[i];
		bool fl = 0;
		for(int j = 0; j < min(str[i].size(), str[i - 1].size()); j++) {
			if(str[i][j] != str[i - 1][j]) {
				cnt[str[i][j] - 'a']++;
				g[str[i - 1][j] - 'a'].pb(str[i][j] - 'a');
				fl = 1;
				break;
			}
		}
		if(!fl && str[i].size() < str[i - 1].size()) kk = 1;
	}
	queue<int> q;
	for(int i = 0; i < 26; i++) {
		if(cnt[i] == 0) q.push(i);
	}
	vector<int> ans;
	while(q.size()) {
		int x = q.front(); q.pop();
		ans.pb(x);
		for(int y : g[x]) {
			cnt[y]--;
			if(cnt[y] == 0) q.push(y);
		}
	}
	if(ans.size() != 26 || kk) {
		cout << "Impossible\n";
		return;
	}
	for(int x : ans) {
		cout << char(x + 'a');
	}
	cout << '\n';
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