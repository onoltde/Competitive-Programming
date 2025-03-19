#include "combo.h"
#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

string guess_sequence(int n) {
	string S = "ABXY";
	char st;
	string tmp = "AB";
	if(press(tmp)) {
		tmp = "A";
		if(press(tmp)) st = 'A';
		else st = 'B';
	} else {
		tmp = "X";
		if(press(tmp)) st = 'X';
		else st = 'Y';
	}
	S.erase(find(all(S), st));
	string ans = "";
	ans.pb(st);
	if(n == 1) return ans;
	for(int i = 2; i <= n - 1; i++) {
		string ask = "";
		ask += ans;
		ask.pb(S[0]);
		for(int j = 0; j < 3; j++) {
			ask += ans;
			ask.pb(S[1]);
			ask.pb(S[j]);
		}
		int l = press(ask);
		if(l == i - 1) ans.pb(S[2]);
		else if(l == i) ans.pb(S[0]);
		else ans.pb(S[1]);
	}
	char en = S[2];
	for(int i = 0; i < 2; i++) {
		string ask = ans;
		ask.pb(S[i]);
		if(press(ask) == n) {
			en = S[i];
			break;
		}
	}
	ans.pb(en);
	return ans;
}
