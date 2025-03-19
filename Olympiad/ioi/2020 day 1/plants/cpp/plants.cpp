#include "plants.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

// #define int long long
 
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

vector<int> a;
set<int> s;
int n, k;

bool check(int i) {
	
}

void init(int _k, vector<int> r) {
}

int compare_plants(int x, int y) {
	if(a[x] > a[y]) return 1;
	else return -1;
	return 0;
}
