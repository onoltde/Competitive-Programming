#include "messy.h"
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

vector<int> ans;
string str;
void build(int l, int r) {
	if(l == r) {
		return;
	}
	int m = (l + r) >> 1;
	for(int i = l; i <= m; i++) {
		str[i] = '1';
		add_element(str);
		str[i] = '0';
	}
	for(int i = l; i <= m; i++) {
		str[i] = '1';
	}
	build(m + 1, r);
	for(int i = l; i <= m; i++) {
		str[i] = '0';
	}
	for(int i = m + 1; i <= r; i++) {
		str[i] = '1';
	}
	build(l, m);
}

void find(int l, int r, vector<int> a) {
	if(l == r) {
		ans[l] = a[0];
		return;
	}
	int m = (l + r) >> 1;
	vector<int> L, R;
	for(int i = l; i <= r; i++) {
		int x = a[i - l];
		str[x] = '1';
		if(check_element(str)) L.pb(x);
		else R.pb(x);
		str[x] = '0';
	}
	for(int x : L) {
		str[x] = '1';
	}
	find(m + 1, r, R);
	for(int x : L) {
		str[x] = '0';
	}
	for(int x : R) {
		str[x] = '1';
	}
	find(l, m, L);
}

vector<int> restore_permutation(int n, int w, int r) {
	vector<int> a(n); iota(all(a), 0);
	ans.resize(n);
	str = string(n, '0');
	build(0, n - 1);
	compile_set();
	str = string(n, '0');
	find(0, n - 1, a);
	vector<int> ans_(n);
	for(int i = 0; i < n; i++) {
		ans_[ans[i]] = i;
	}
	swap(ans,  ans_);
	return ans;
}
