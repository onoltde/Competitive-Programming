#include "shoes.h"
#include<bits/stdc++.h>
using namespace std;

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

const int mxn = 2e5 + 10;
int a[mxn], fn[mxn], n;
queue<int> q[mxn][3];

void add(int i, int val) {
	for(; i; i -= (i & -i)) {
		fn[i] += val;
	}
}

int get(int i) {
	int ret = 0;
	for(; i <= n; i += (i & -i)) {
		ret += fn[i];
	}
	return ret;
}

long long count_swaps(vector<int> s) {
	n = (int)s.size();
	for(int i = 1; i <= n; i++) {
		a[i] = s[i - 1];
	}
	long long ret = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i] > 0) {
			if(q[a[i]][0].size()) {
				int lst = q[a[i]][0].front();
				q[a[i]][0].pop();
				ret += 1LL * (i - lst - 1) - 1LL * (get(i) - get(lst));
				add(i, -1);
				add(lst, 1);
			} else {
				q[a[i]][1].push(i);
			}
		} else {
			a[i] = -a[i];
			if(q[a[i]][1].size()) {
				int lst = q[a[i]][1].front();
				q[a[i]][1].pop();
				ret += (i - lst) - (get(i) - get(lst));
				add(i, -1);
				add(lst, 1);
			} else {
				q[a[i]][0].push(i);
			}
		}
	}
	return ret;
}
