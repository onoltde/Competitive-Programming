// #include "toxic.h"
#include <string>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;


namespace {
	static void wrong_answer(){
		printf("%d\n",-1);
		exit(0);
	}
	static int tc, current_tc, N, batchsize = 300, qlimit = 600;
	static int q[105];
	static char answer[105][305];
	static char participant_type[105][305];
}

int query_sample(vector<int> species){
	if (species.size() > batchsize){
		wrong_answer();
	}
	q[current_tc]++;
	if (q[current_tc] > qlimit){
		wrong_answer();
	}
	bool has_toxic = false;
	int reg = 0, strong = 0;
	for (int i = 0; i < (int) species.size(); ++i){
		if (species[i] < 1 || species[i] > N){
			wrong_answer();
		}
		char tp = answer[current_tc][species[i]];
		if (tp == 'T'){
			has_toxic = true;
		}
		if (tp == 'R'){
			reg++;
		}
		if (tp == 'S'){
			strong++;
		}
	}
	if (has_toxic) return strong;
	else return reg + strong;
}

void answer_type(int x, char c){
	if (x < 1 || x > N) wrong_answer();
	if (c != 'T' && c != 'R' && c != 'S') wrong_answer(); 
	participant_type[current_tc][x] = c;
	if (participant_type[current_tc][x] != answer[current_tc][x]) wrong_answer();
}

// #include "toxic.h"
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

int main(){

	assert(2 == scanf("%d %d\n",&tc,&N));
	for (int t = 1; t <= tc; ++t){
		assert(1 == scanf("%s",answer[t]));
		for (int i = N; i >= 1; --i){
			answer[t][i] = answer[t][i-1];
		}
		answer[t][0] = 'X';
		for (int i = 1; i <= N; ++i){
			participant_type[t][i] = 'X';
		}
	}
	for (int t = 1; t <= tc; ++t){
		current_tc = t;
		q[current_tc] = 0;
		determine_type(N);
		for (int i = 1; i <= N; ++i){
			if (participant_type[current_tc][i] != answer[current_tc][i]) wrong_answer();
		}
	}
	


	for (int t = 1; t <= tc; ++t){
		printf("%d\n",q[t]);
	}
	return 0;
	
}