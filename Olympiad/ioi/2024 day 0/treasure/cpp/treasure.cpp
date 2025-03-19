#include "treasure.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

//#define int long long

typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
const int MX = 5e8;

vector<int> encode(vector<pair<int, int>> P) {
	int n = (int)P.size();
	vector<pair<int, int>> a, b;
	for(int i = 0; i < n; i++) {
		a.eb(P[i].ff, i);
		b.eb(P[i].ss, i);
	}
	sort(all(a));
	sort(all(b));
	vector<int> pos(n);
	for(int i = 0; i < n; i++) {
		pos[b[i].ss] = i;
	}
	vector<int> ret;
	int sum = 0;
	for(int i = 0; i < n; i++) {
		sum += pos[a[i].ss];
		ret.pb(sum * 2 + 1);
	}
	for(int i = 0; i < n; i++) {
		ret.pb(P[i].ff * 2);
		ret.pb((P[i].ss + MX) * 2);
	}
	return ret;
}

vector<pair<int, int>> decode(vector<int> S) {
	vector<int> a, b, s;
	int n = S.size() / 3;
	for(int i = 0; i < n * 3; i++) {
		if(S[i] % 2 == 1) s.pb(S[i] / 2);
		else {
			int tmp = S[i] / 2;
			if(tmp == MX) continue;
			if(tmp < MX) {
				a.pb(tmp);
			} else {
				b.pb(tmp - MX);
			}
		}
	}
	while(a.size() < n) a.pb(MX);
	while(b.size() < n) b.pb(0);
	sort(all(a));
	sort(all(b));
	sort(all(s));
	vector<pair<int, int>> ret;
	int ls = 0;
	for(int i = 0; i < n; i++) {
		ret.eb(a[i], b[s[i] - ls]);
		ls = s[i];
	}
	return ret;
}
