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

const int mxn = 387420489;
int pw[10][10], a[10][10];
int vis[mxn];

int getNum() {
	int ret = 0;
	for(int i = 1; i <= 3; i++) {
		for(int j = 1; j <= 3; j++) {
			ret = ret + pw[i][j] * a[i][j];
		}
	}
	return ret;
}

vector<int> get(int x) {
	for(int i = 1; i <= 3; i++) {
		for(int j = 1; j <= 3; j++) {
			a[i][j] = x / pw[i][j] % 9;
		}
	}
	vector<int> ret;
	for(int i = 1; i <= 3; i++) {
		for(int j = 1; j <= 3; j++) {
			if(i + 1 <= 3) {
				swap(a[i][j], a[i + 1][j]);
				ret.pb(getNum());
				swap(a[i][j], a[i + 1][j]);
			}
			if(j + 1 <= 3) {
				swap(a[i][j], a[i][j + 1]);
				ret.pb(getNum());
				swap(a[i][j], a[i][j + 1]);
			}
		}
	}
	return ret;
}

void go() {
	int goal = 0;
	for(int i = 3; i >= 1; i--) {
		for(int j = 3; j >= 1; j--) {
			pw[i][j] = pow(9, (3 - i) * 3 + (3 - j));
		}
	}
	int cur = 0;
	int cnt = 0;
	for(int i = 1; i <= 3; i++) {
		for(int j = 1; j <= 3; j++) {
			int x;
			cin >> x;
			x--;
			cur += pw[i][j] * x;
			goal += pw[i][j] * (cnt++);
		}
	}
	vis[cur] = 1;
	queue<pair<int, int>> q;
	q.push({cur, 0});
	while(q.size()) {
		int x = q.front().ff;
		int p = q.front().ss;
		q.pop();
		if(x == goal) {
			cout << p << '\n';
			return;
		}
		vi v = get(x);
		for(int y : v) {
			if(vis[y]) continue;
			vis[y] = 1;
			q.push({y, p + 1});
		}
	}
}
 
signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	// struct timeval start, end;
    // mingw_gettimeofday(&start, NULL);
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
    // mingw_gettimeofday(&end, NULL);
    // double time_taken;
  
    // time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    // time_taken = (time_taken + (end.tv_usec - 
    //                           start.tv_usec)) * 1e-6;
  
    // cerr << "Time taken by program is : " << fixed
    //      << time_taken << setprecision(6);
    // cerr << " sec" << endl;
	return 0;
}