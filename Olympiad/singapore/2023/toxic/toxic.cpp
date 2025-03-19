#include "toxic.h"
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
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
void determine_type(int n) {
	vector<int> type(n + 1, 2), sorr, dnow;
	int toxic = 0, samp;
	for(int i = 1; i <= n; i++) {
		dnow.pb(i);
	}
	random_shuffle(all(dnow));
 
	while(dnow.size()) {
		random_shuffle(all(dnow));
		vector<int> ask;
		int sz = min((int)dnow.size(), 8);
		for(int i = 0; i < sz; i++) {
			for(int j = 0; j < (1 << i); j++) {
				ask.pb(dnow[i]);
			}
		}
		int ans = query_sample(ask);
		if(ans == ask.size()) {
			for(int i = 0; i < sz; i++) {
				sorr.pb(dnow[0]);
				dnow.erase(dnow.begin());
			}
			continue;
		}
		vector<int> torr;
		for(int i = 0; i < sz; i++) {
			if(ans & (1 << i)) type[dnow[0]] = 0;
			else torr.pb(dnow[0]);
			dnow.erase(dnow.begin());
		}
		// random_shuffle(all(torr));
		int l = 0, r = torr.size() + 1;
		while(r - l > 1) {
			int m = (l + r) / 2;
			ask.clear();
			for(int i = l; i < m; i++) {
				ask.pb(torr[i]);
			}
			int szdn = min((int)sorr.size(), 8);
			for(int i = 0; i < szdn; i++) {
				for(int j = 0; j < (1 << i); j++) {
					ask.pb(sorr[i]);
				}
			}
			ans = query_sample(ask);
			if(ans == ask.size()) {
				l = m;
			} else {
				r = m;
				for(int i = 0; i < szdn; i++) {
					if(ans & (1 << i)) type[sorr[0]] = 0;
					sorr.erase(sorr.begin());
				}
			}
		}
		type[torr[l]] = 1;
		samp = torr[l];
		for(int i = l + 1; i < torr.size(); i++) {
			dnow.pb(torr[i]);
		}
		toxic++;
		if(toxic == 30) {
			for(int x : dnow) {
				sorr.pb(x);
			}
			dnow.clear();
		}
	}
 
	while(sorr.size()) {
		vector<int> ask;
		int sz = min((int)sorr.size(), 8);
		for(int i = 0; i < sz; i++) {
			for(int j = 0; j < (1 << i); j++) {
				ask.pb(sorr[i]);
			}
		}
		ask.pb(samp);
		int ans = query_sample(ask);
		for(int i = 0; i < sz; i++) {
			if(ans & (1 << i)) type[sorr[0]] = 0;
			sorr.erase(sorr.begin());
		}
	}
 
	string str = "STR";
	for(int i = 1; i <= n; i++) {
		answer_type(i, str[type[i]]);
	}
}