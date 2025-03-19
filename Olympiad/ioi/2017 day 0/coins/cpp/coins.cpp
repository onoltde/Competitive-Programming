#include "coins.h"
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

vector<int> coin_flips(vector<int> b, int c) {
	for(int i = 0; i < 64; i++) {
		c ^= i * b[i];
	}
	return vector<int>{c};
}

int find_coin(vector<int> b) {
	int ans = 0;
	for(int i = 0; i < 64; i++) {
		ans ^= i * b[i];
	}
	return ans;
}
