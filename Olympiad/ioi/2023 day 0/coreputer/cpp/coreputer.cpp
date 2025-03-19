#include "coreputer.h"
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

vector<int> malfunctioning_cores(int n) {
	vector<int> state(n);
	auto ask = [&]() -> int {
		vector<int> tmp;
		for(int i = 0; i < n; i++) {
			if(state[i]) tmp.pb(i);
		}
		return run_diagnostic(tmp);
	};
	int l = -1, r = n - 1;
	int even = 0;
	while(r - l > 1) {
		int m = (l + r) / 2;
		for(int i = 0; i < n; i++) {
			state[i] = 0;
		}
		for(int i = 0; i <= m; i++) {
			state[i] = 1;
		}
		int gg = ask();
		if(gg == 1) r = m;
		else {
			l = m;
			if(gg == 0) even = 1;
		}
	}
	for(int i = 0; i < n; i++) {
		if(i <= l) state[i] = 1;
		else state[i] = 0;
	}
	vector<int> ret(n);
	ret[l + 1] = 1;
	if(even == 0 && l == n - 2) return ret;
	else if(even == 1 && l == n - 2) {
		for(int i = 0; i < n; i++) {
			state[i] = 0;
		}
		state[l + 1] = 1;
		for(int i = 0; i < n - 2; i++) {
			state[i] = 1;
			if(ask() == 1) {
				ret[i] = 1;
				return ret;
			}
			state[i] = 0;
		}
		ret[l] = 1;
		return ret;
	}
	for(int i = l + 2; i < n - 1; i++) {
		state[i] = 1;
		if(ask() == 1) ret[i] = 1;
		state[i] = 0;
	}
	state[l + 1] = 1;
	for(int i = 0; i <= l; i++) {
		state[i] = 0;
		int tmp = ask();
		if(tmp == 0 && even) ret[i] = 1;
		else if(tmp == -1) ret[i] = 1;
		state[i] = 1;
	}
	int sum = 0;
	for(int i = 0; i < n; i++) {
		sum += ret[i];
	}
	if(sum % 2 == 0 && even == 0) ret[n - 1] = 1;
	else if(sum % 2 == 1 && even == 1) ret[n - 1] = 1;
	return ret;
}
