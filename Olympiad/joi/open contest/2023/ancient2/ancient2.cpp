#include "ancient2.h"
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

int ask(vector<int> a, vector<int> b) {
	return Query((int)a.size(), a, b);
}

string Solve(int n) {
	vector<int> a, b;
	int l = 0;
	string ans = "";
	auto getNext = [&]() -> char {
		int m = (int)a.size();
		a.pb(m + 2);
		b.pb(m + 1);
		for(int i = 0; i < 2; i++) {
			a.pb(m + i + 1);
			b.pb(m + i + 1);
		}
		int ret = ask(a, b);
		for(int i = 0; i < 3; i++) {
			a.pop_back();
			b.pop_back();
		}
		return (ret == m + 2 ? '0' : '1');
	};
	auto push = [&](char ch) -> void {
		int m = (int)a.size();
		if(ch == '0') {
			a.pb(m);
			b.pb(m + 1);
		} else {
			a.pb(m + 1);
			b.pb(m);
		}
	};
	while(l < n) {
		char nxt = getNext();
		ans.pb(nxt);
		l++;
		if(l == n) break;
		int ls = (int)a.size();
		bool found = 0;
		a.pb((int)a.size() + 1);
		b.pb((int)b.size() + 1);
		while(a.size() <= 500 && l < n) {
			char ch = getNext();
			ans.pb(ch);
			l++;
			if(ch != nxt) {
				found = 1;
				break;
			}
			a.pb((int)a.size() + 1);
			b.pb((int)b.size() + 1);
		}
		if(l == n) break;
		while(a.size() > ls) {
			a.pop_back();
			b.pop_back();
		}
		push(nxt);
		if(found) {
			continue;
		}
		int m = a.size();
		while(a.size() < 504) {
			a.pb((int)a.size());
			b.pb((int)b.size());
		}
		a.pb(504);
		b.pb(504);
		int len = ask(a, b) - m;
		int nxtl = n - len;
		while(ans.size() < nxtl - 1) {
			ans.pb(nxt);
		}
		ans.pb(nxt ^ '0' ^ '1');
		while(a.size() > m) {
			a.pop_back();
			b.pop_back();
		}
		l = nxtl;
	}
	return ans;
}
