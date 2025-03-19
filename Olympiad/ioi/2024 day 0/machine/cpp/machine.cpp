#include "machine.h"
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

vector<int> find_permutation(int n) {
	vector<int> cnt(8);
	for(int i = 0; i <= n + 2; i++) {
		for(int j = 0; j < 8; j++) {
			if(i & (1 << j)) cnt[j]++;
		}
	}
	vector<int> a(n + 3);
	iota(all(a), 0);
	for(int i = 0; i <= n + 2; i++) {
		for(int j = i + 1; j <= n + 2; j++) {
			for(int k = j + 1; k <= n + 2; k++) {
				int can = 1;
				for(int p = 0; p < 8; p++) {
					if(i & (1 << p)) cnt[p]--;
					if(j & (1 << p)) cnt[p]--;
					if(k & (1 << p)) cnt[p]--;
					if(cnt[p] * 2 == n) can = 0;
				}
				if(can) {
					a.erase(find(all(a), i));
					a.erase(find(all(a), j));
					a.erase(find(all(a), k));
					goto jump;
				}
				for(int p = 0; p < 8; p++) {
					if(i & (1 << p)) cnt[p]++;
					if(j & (1 << p)) cnt[p]++;
					if(k & (1 << p)) cnt[p]++;
					if(cnt[p] * 2 == n) can = 0;
				}
			}
		}
	}
jump:
	vector<int> b = use_machine(a);
	int x = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 8; j++) {
			if(b[i] & (1 << j)) cnt[j]--;
		}
	}
	for(int j = 0; j < 8; j++) {
		if(cnt[j] != 0) x ^= (1 << j);
	}
	vector<int> pos(n + 3, -1);
	for(int i = 0; i < n; i++) {
		pos[a[i]] = i;
	}
	vector<int> ret;
	for(int i = 0; i < n; i++) {
		ret.pb(pos[b[i] ^ x]);
	}
	return ret;
}