#include "aplusb.h"
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

vector<int> smallest_sums(int n, vector<int> a, vector<int> b) {
	priority_queue<tuple<int, int, int>> q;
	for(int i = 0; i < n; i++) {
		q.emplace(-a[i] - b[0], i, 0);
	}
	vector<int> ret;
	while(ret.size() < n) {
		int sum, i, j;
		tie(sum, i, j) = q.top(); q.pop();
		ret.pb(-sum);
		if(j + 1 < n) q.emplace(-a[i] - b[j + 1], i, j + 1);
	}
	return ret;
}
