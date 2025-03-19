#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

#define int long long
 
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

const int mxn = 2e7 + 10;
int cnt[mxn];

void go() {
    int c, d, x;
    cin >> c >> d >> x;
    int ans = 0;
    for(int g = 1; g * g <= x; g++) {
        if(x % g) continue;
        int g1 = g, g2 = x / g;
        if((x + d * g1) % (c * g1) == 0) {
            int val = (x + d * g1) / (c * g1);
            ans += (1 << cnt[val]);
        }
        if((x + d * g2) % (c * g2) == 0 && g1 != g2) {
            int val = (x + d * g2) / (c * g2);
            ans += (1 << cnt[val]);
        }
    }
    cout << ans << '\n';
}

signed main() {
    fast;
    int t = 1;
    cin >> t;
    for(int i = 2; i <= 2e7; i++) {
        if(cnt[i]) continue;
        for(int j = i; j <= 2e7; j += i) {
            cnt[j]++;
        }
    }
    while(t--) {
        go();
    }
    return 0;
}