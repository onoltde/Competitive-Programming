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

// you may define some global variables, but it does not work if you try to transfer any information from function Alice to function Bob through these variables.
// you had better not use the same global variables in function Alice and in function Bob.

/*
p:              The original permutation owned by Alice. You can get its length by p.size(). 
				It is guaranteed that p.size()<=20 and each integers in [0, p.size()) appears exactly once in p.
return value:   The integer passed from Alice to Bob (64-bit unsigned).
*/
unsigned long long Alice(const std::vector<int> p){
	unsigned long long ret = 0;
	int n = p.size();
	vector<unsigned long long> fac(n + 1);
	fac[0] = 1;
	for(int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i;
		if(i < n) ret += fac[i];
	}
	vector<int> hho(n);
	for(int i = 0; i < n; i++) {
		int cnt = 0;
		for(int j = 0; j < p[i]; j++) {
			if(hho[j] == 0) cnt++;
		}
		hho[p[i]] = 1;
		ret += fac[n - i - 1] * cnt;
	}
	return ret + 1;
}

/*
x:         		The integer that Bob received from Alice.
return value:	The permutation that Bob restored based on the received information.
*/
std::vector<int> Bob(const unsigned long long _x) {
	unsigned long long x = _x;
	vector<unsigned long long> fac(21);
	fac[0] = 1;
	for(int i = 1; i <= 20; i++) {
		fac[i] = fac[i - 1] * i;
	}
	int n;
	for(int i = 1; i <= 20; i++) {
		if(fac[i] >= x) {
			n = i;
			break;
		}
		x -= fac[i];
	}
	vector<int> ret(n), hho(n);
	for(int i = 0; i < n; i++) {
		int cnt = 0;
		if(i == n - 1) {
			for(int j = 0; j < n; j++) {
				if(hho[j] == 0) ret[i] = j;
			}
			break;
		}
		for(int j = 0; j < n; j++) {
			if(hho[j]) continue;
			cnt++;
			if(fac[n - i - 1] * cnt >= x) {
				ret[i] = j;
				x -= fac[n - i - 1] * (cnt - 1);
				break;
			}
		}
		hho[ret[i]] = 1;
	}
	return ret;
}

