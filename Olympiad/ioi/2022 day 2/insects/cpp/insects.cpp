#include "insects.h"
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
set<int> all;

void add(int i) {
	if(all.count(i)) return;
	move_inside(i);
	all.in(i);
}

void rem(int i) {
	if(!all.count(i)) return;
	move_outside(i);
	all.erase(i);
}

int solve(vector<int> a, vector<int> b) {
	if(a.size() == 1) {
		rem(a[0]);
		return (int)a.size() + (int)b.size();
	}
	if(b.size() < a.size()) {
		for(int x : a) {
			rem(x);
		}
		return 1;
	}
	random_shuffle(all(a));
	vector<int> a1, a2, b1, b2;
	int sz = a.size();
	for(int i = 0; i < sz / 2; i++) {
		a1.pb(a[i]);
		add(a[i]);
	}
	for(int i = sz / 2; i < sz; i++) {
		a2.pb(a[i]);
		rem(a[i]);
	}
	for(int x : b) {
		add(x);
		if(press_button() > 1) b1.pb(x);
		else b2.pb(x);
		rem(x);
	}
	return min(solve(a1, b1), solve(a2, b2));
}

int min_cardinality(int n) {
	vector<int> a, b;
	for(int i = 0; i < n; i++) {
		a.pb(i);
		add(i);
		if(press_button() > 1) {
			a.pop_back();
			b.pb(i);
			rem(i);
		}
	}
	return solve(a, b);
}
