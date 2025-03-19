#include "tree.h"
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

vector<int> compute(int n, vector<int> F) {
	vector<int> ans, cnt(n);
	priority_queue<int> q;
	for(int i = 0; i < n; i++) {
		if(F[i] != -1) cnt[F[i]]++;
	}
	for(int i = 0; i < n; i++) {
		if(cnt[i] == 0) q.push(i);
	}
	while(q.size()) {
		int x = q.top();
		q.pop();
		if(F[x] == -1) break;
		ans.pb(x);
		cnt[F[x]]--;
		if(cnt[F[x]] == 0) q.push(F[x]);
	}
	return ans;
}
