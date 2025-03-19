#include "dungeons.h"

#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
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

template<typename T, typename U>
ostream & operator << (ostream &out, const pair<T, U> &c) {
	out << c.first << ' ' << c.second;
    return out;
}

template<typename T>
ostream & operator << (ostream &out, vector<T> &v) {
	const int sz = v.size();
	for (int i = 0; i < sz; i++) {
		if (i) out << ' ';
		out << v[i];
	}
    return out;
}

template<typename T>
istream & operator >> (istream &in, vector<T> &v) {
	for (T &x : v) in >> x;
    return in;
}

template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

const int mxn = 5e4 + 10;
int s[mxn], p[mxn], w[mxn], l[mxn], n;

void init(int n, std::vector<int> s, std::vector<int> p, std::vector<int> w, std::vector<int> l) {
	::n = n;
	for(int i = 1; i <= n; i++) {
		::s[i] = s[i - 1];
		::p[i] = p[i - 1];
		::w[i] = w[i - 1] + 1;
		::l[i] = l[i - 1] + 1;
	}
	return;
}

long long simulate(int x, int z) {
	x++;
	while(x != n + 1) {
		if(z >= s[x]) {
			z += s[x];
			x = w[x];
		} else {
			z += p[x];
			x = l[x];
		}
	}
	return z;

}

