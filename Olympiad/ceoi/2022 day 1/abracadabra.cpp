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

const int mxn = 2e5 + 10, mxq = 1e6 + 10;
vector<pair<int, int>> qu[mxn];
int a[mxn], ans[mxq], nxt[mxn], did[mxn];

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node {
	int l, r, val, si, sum, mn, mx, lstlen, key;
	node *le, *ri;
	node(int _l, int _r, int _val) : l(_l), r(_r), val(_val), mn(_val), mx(_val), key(rand())
									, si(1), sum(_r - _l + 1), lstlen(_r - _l + 1), le(NULL), ri(NULL) {}
} *root;

int getSize(node *root) {
	if(!root) return 0;
	return root->si;
}

int getSum(node *root) {
	if(!root) return 0;
	return root->sum;
}

int getMax(node *root) {
	if(!root) return 0;
	return root->mx;
}

int getMin(node *root) {
	if(!root) return 0;
	return root->mn;
}

void merge(node *&root, node *le, node *ri) {
	if(!le || !ri) {
		root = (!le ? ri : le);
		return;
	}
	if(le->key < ri->key) {
		merge(le->ri, le->ri, ri);
		root = le;
	} else {
		merge(ri->le, le, ri->le);
		root = ri;
	}
	root->si = getSize(root->le) + getSize(root->ri) + 1;
	root->mx = max({root->mx, getMax(root->le), getMax(root->ri)});
	root->mn = min({root->mn, getMin(root->le), getMin(root->ri)});
	root->sum = getSum(root->le) + getSum(root->ri) + (root->r - root->l + 1);
	if(root->ri) root->lstlen = root->ri->lstlen;
	else root->lstlen = root->r - root->l + 1;
}

void split(node *root, node *&le, node *&ri, int pos) {
	if(!root) {
		le = ri = NULL;
		return;
	}
	if(getSize(root->le) < pos) {
		split(root->ri, root->ri, ri, pos - getSize(root->le) - 1);
		le = root;
	} else {
		split(root->le, le, root->le, pos);
		ri = root;
	}
	root->si = getSize(root->le) + getSize(root->ri) + 1;
	root->mx = max({root->mx, getMax(root->le), getMax(root->ri)});
	root->mn = min({root->mn, getMin(root->le), getMin(root->ri)});
	root->sum = getSum(root->le) + getSum(root->ri) + (root->r - root->l + 1);
	if(root->ri) root->lstlen = root->ri->lstlen;
	else root->lstlen = root->r - root->l + 1;
}

int find(node *root, int x) {
	if(!root) return 0;
	if(root->mn > x) return 0;
	if(root->mx < x) return getSize(root);
	if(root->val > x) return find(root->le, x);
	return find(root->ri, x) + 1;
}

int get(node *root, int id) {
	if(!root) return 0;
	if(getSum(root->le) >= id) return get(root->le, id);
	else if(getSum(root->le) + root->r - root->l + 1 >= id) return a[root->l + id - getSum(root->le) - 1];
	else return get(root->ri, id - getSum(root->le) - (root->r - root->l + 1));
}

signed main() {
	fast;
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		did[i] = -1;
	}

	for(int i = 1; i <= q; i++) {
		int t, id;
		cin >> t >> id;
		mnn(t, n);
		if(t == 0) {
			ans[i] = a[id];
		} else {
			qu[t].eb(id, i);
		}
	}

	stack<pair<int, int>> st;
	for(int i = 1; i <= n; i++) {
		nxt[i] = n + 1;
	}
	nxt[n + 1] = n + 1;
	for(int i = 1; i <= n; i++) {
		while(st.size() && st.top().ff < a[i]) {
			nxt[st.top().ss] = i;
			st.pop();
		}
		st.emplace(a[i], i);
	}

	for(int i = 1; i <= n; i = nxt[i]) {
		merge(root, root, new node(i, nxt[i] - 1, a[i]));
	}

	int len = n;

	for(int t = 1; t <= n; t++) {
		while(len - root->lstlen >= n / 2) {
			node *b;
			split(root, root, b, getSize(root) - 1);
			len -= b->lstlen;
			for(int i = b->l; i <= b->r; i++) {
				did[len + (i - b->l + 1)] = a[i];
			}
		}
		if(root->sum > n / 2) {
			node *b;
			split(root, root, b, getSize(root) - 1);
			len -= b->lstlen;
			int rr = b->l + n / 2 - len - 1;
			merge(root, root, new node(b->l, rr, b->val));
			for(int i = rr + 1; i <= b->r; i = nxt[i]) {
				int r = min(nxt[i] - 1, b->r);
				int pos = find(root, a[i]);
				node *c;
				split(root, root, c, pos);
				merge(root, root, new node(i, r, a[i]));
				merge(root, root, c);
			}
			len += b->lstlen;
		}
		sort(all(qu[t]));
		for(auto it : qu[t]) {
			int id = it.ff;
			int i = it.ss;
			if(id > len) ans[i] = did[id];
			else {
				ans[i] = get(root, id);
			}
		}
	}
	
	for(int i = 1; i <= q; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}