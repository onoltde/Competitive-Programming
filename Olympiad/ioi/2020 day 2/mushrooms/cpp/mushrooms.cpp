#include "mushrooms.h"
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

const int bl = 100;

int solveSmall(int n) {
	int ret = 0;
	for(int i = 1; i < n; i += 2) {
		vector<int> ask;
		ask.pb(i);
		ask.pb(0);
		if(i + 1 < n) ask.pb(i + 1);
		ret += use_machine(ask);
	}
	return n - ret;
}

int count_mushrooms(int n) {
	if(n / 2 <= 226) return solveSmall(n);
	vector<int> a{0}, b;
	int did = 0;

	auto check = [&]() -> void {
		if(b.size() > a.size()) {
			swap(a, b);
			did ^= 1;
		}
	};

	queue<int> m;
	for(int i = 5; i < n; i++) {
		m.push(i);
	}

	if(use_machine(vector<int>{0, 1})) b.pb(1);
	else a.pb(1); 
	if(use_machine(vector<int>{0, 2})) b.pb(2);
	else a.pb(2);
	check();

	int tmp = use_machine(vector<int>{a[0], 3, a[1], 4});
	if(tmp & 1) b.pb(4);
	else a.pb(4);
	if(tmp > 1) b.pb(3);
	else a.pb(3); 
	check();

	while(a.size() < bl) {
		vector<int> v;
		for(int i = 0; i < 3; i++) {
			v.pb(m.front()); m.pop();
		}
		int tmp = use_machine(vector<int>{a[0], v[0], a[1], v[1], a[2], v[2]});
		if(tmp == 2 || tmp == 3) {
			if(tmp == 2) a.pb(v[2]);
			else b.pb(v[2]);
			check();
			v.pop_back();

			if(b.size() >= 2) {
				for(int i = 0; i < 2; i++) {
					v.pb(m.front()); m.pop();
				}
				tmp = use_machine(vector<int>{b[0], v[0], b[1], a[0], v[1], a[1], v[2], a[2], v[3]}) - 1;
				if(tmp >= 4) {
					a.pb(v[0]);
					b.pb(v[1]);
					tmp -= 4;
				} else {
					a.pb(v[1]);
					b.pb(v[0]);
				}

				if(tmp & 1) b.pb(v[3]);
				else a.pb(v[3]);

				if(tmp > 1) b.pb(v[2]);
				else a.pb(v[2]);
			} else {
				if(use_machine(vector<int>{a[0], v[0]})) {
					b.pb(v[0]);
					a.pb(v[1]);
				} else {
					a.pb(v[0]);
					b.pb(v[1]);
				}
			}
		} else {
			if(tmp == 0) {
				a.insert(a.end(), all(v));
			} else if(tmp == 1) {
				a.pb(v[0]); a.pb(v[1]);
				b.pb(v[2]);
			} else if(tmp == 4) {
				a.pb(v[2]);
				b.pb(v[0]); b.pb(v[1]);
			} else {
				b.insert(b.end(), all(v));
			}
		}
		check();
	}
	vector<int> ask;
	int A = a.size(), B = b.size(), id = 0;
	while(m.size()) {
		int now = m.front(); m.pop();
		ask.pb(a[id]);
		ask.pb(now);
		id++;
		if(id == a.size()) {
			int tmp = use_machine(ask);
			A += id - (tmp + 1) / 2;
			B += (tmp + 1) / 2;
			if(tmp % 2 == 0) a.pb(ask.back());
			else b.pb(ask.back());
			id = 0;
			if(a.size() < b.size()) {
				swap(A, B);
				check();
			}
			ask.clear();
		}
	}
	if(ask.size()) {
		int tmp = use_machine(ask);
		A += id - (tmp + 1) / 2;
		B += (tmp + 1) / 2;
	}
	if(did) swap(A, B);	
	return A;
}