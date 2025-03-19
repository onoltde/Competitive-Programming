#include "choreography.h"
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

int n;
vector<int> p, pos;
int sum0, sum1;
int tp;
int add0[2], add1[2];

void init(int N, vector<int> P) {
	n = N;
	p = P;
	pos.resize(N);
	for(int i = 0; i < N; i++) {
		pos[p[i]] = i;
	}
	return;
} 

int is(int x) {
	if(x % 2 == 0) return 0;
	else return 1;
}

void move_right(int K) {
	if(tp == 0) sum1 += K;
	else sum0 += K;
	sum0 %= n;
	sum1 %= n;
}

void move_left(int K) {
	if(tp == 0) sum1 -= K;
	else sum0 -= K;
	sum0 %= n;
	sum1 %= n;
}

void swap_places() {
	if(tp == 1) {
		for(int i = 0; i < 2; i++) {
			if(is(sum0 + i + add0[i]) == 0) add0[i]++;
			else add0[i]--;
		}
	} else {
		for(int i = 0; i < 2; i++) {
			if(is(sum1 + i + add1[i]) == 0) add1[i]++;
			else add1[i]--;
		}
	}
	for(int i = 0; i < 2; i++) {
		add0[i] = (add0[i] + n) % n;
		add1[i] = (add1[i] + n) % n;
	}
}

void move_around() {
	tp ^= 1;
}

int get_position(int D) {
	int ret = 0, x = -1;
	if(tp == 0) {
		for(int i = 0; i < 2; i++) {
			int gg = (D - sum0 - add0[i]) % n;
			gg = (gg + n) % n;
			if(gg % 2 == i) x = gg;
		}
		assert(x != -1);
		ret = pos[x] + sum1 + add1[pos[x] & 1];
	} else {
		for(int i = 0; i < 2; i++) {
			int gg = (D - sum1 - add1[i]) % n;
			gg = (gg + n) % n;
			if(gg % 2 == i) x = gg;
		}
		ret = p[x] + sum0 + add0[p[x] & 1];
	}
	ret = (ret + n) % n;
	return ret;
}
