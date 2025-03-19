#include "candies.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

// #define long long long long
 
typedef long long ll;
typedef vector<int> vi;
typedef set<long long> si;
typedef multiset<long long> msi;
typedef pair<long long, long long> pii;
typedef vector<pii> vpii;

const long long mxn = 2e5 + 10;
const long long inf = 1e18 + 10;
struct segTreeBeats {
	long long l, r, m;
	long long sum, max1, max2, min1, min2, maxc, minc, lz;
	segTreeBeats *le, *ri;

	void up() {
		assert(le != NULL);
		assert(ri != NULL);
		sum = le->sum + ri->sum;

		max1 = max(le->max1, ri->max1);
		min1 = min(le->min1, ri->min1);

		max2 = -inf;
		min2 = inf;

		if(le->max1 == ri->max1) {
			maxc = le->maxc + ri->maxc;
			max2 = max(le->max2, ri->max2);
		} else {
			if(le->max1 > ri->max1) {
				maxc = le->maxc;
				max2 = max(le->max2, ri->max1);
			} else {
				maxc = ri->maxc;
				max2 = max(le->max1, ri->max2);
			}
		}

		if(le->min1 == ri->min1) {
			minc = le->minc + ri->minc;
			min2 = min(le->min2, ri->min2);
		} else {
			if(le->min1 < ri->min1) {
				minc = le->minc;
				min2 = min(le->min2, ri->min1);
			} else {
				minc = ri->minc;
				min2 = min(le->min1, ri->min2);
			}
		}
	}

	segTreeBeats(long long _l, long long _r, vector<long long> &a) {
		l = _l; r = _r; m = (l + r) / 2;
		lz = 0;
		if(l == r) {
			sum = max1 = min1 = a[l];
			maxc = minc = 1;
			max2 = -inf; min2 = inf;
			le = ri = NULL;
			return;
		}
		le = new segTreeBeats(l, m, a);
		ri = new segTreeBeats(m + 1, r, a);
		up();
	}

	void proAdd(long long x) {
		sum += x * (r - l + 1);
		max1 += x; min1 += x;
		if(max2 != -inf) max2 += x;
		if(min2 != inf) min2 += x;
		lz += x;
	}

	void proMax(long long x) {
		if(x >= max1) return;
		sum -= maxc * max1;
		max1 = x;
		sum += maxc * max1;

		if(l == r) {
			min1 = x;
		} else {
			if(x <= min1) min1 = x;
			else if(x < min2) min2 = x;
		}
	}

	void proMin(long long x) {
		if(x <= min1) return;
		sum -= minc * min1;
		min1 = x;
		sum += minc * min1;

		if(l == r) {
			max1 = x;
		} else {
			if(x >= max1) max1 = x;
			else if(x > max2) max2 = x;
		}
	}

	void pro() {
		if(l == r) return;
		// if(le == NULL) le = new segTreeBeat(l, m);
		// if(ri == NULL) ri = new segTreeBeat(m + 1, r);

		le->proAdd(lz);
		ri->proAdd(lz);
		lz = 0;

		le->proMax(max1);
		ri->proMax(max1);

		le->proMin(min1);
		ri->proMin(min1);
	}

	void add(long long x, long long y, long long v) {
		if(l > y || r < x) return;
		if(l >= x && r <= y) {
			proAdd(v);
			return;
		} 
		pro();
		le->add(x, y, v);
		ri->add(x, y, v);
		up();
	}

	void mnn(long long x, long long y, long long v) {
		if(l > y || r < x || max1 <= v) return;
		if(l >= x && r <= y && max2 < v) {
			proMax(v);
			return;
		}
		pro();
		le->mnn(x, y, v);
		ri->mnn(x, y, v);
		up();
	}
	void mxx(long long x, long long y, long long v) {
		if(l > y || r < x || min1 >= v) return;
		if(l >= x && r <= y && min2 > v) {
			proMin(v);
			return;
		}
		pro();
		le->mxx(x, y, v);
		ri->mxx(x, y, v);
		up();
	}
	long long getSum(long long x, long long y) {
		if(l > y || r < x) return 0LL;
		if(l >= x && r <= y) return sum;
		pro();
		return le->getSum(x, y) + ri->getSum(x, y);
	}
	long long getMax(long long x, long long y) {
		if(l > y || r < x) return -inf;
		if(l >= x && r <= y) return max1;
		pro();
		return max(le->getMax(x, y), ri->getMax(x, y));
	}
	long long getMin(long long x, long long y) {
		if(l > y || r < x) return inf;
		if(l >= x && r <= y) return min1;
		pro();
		return max(le->getMin(x, y), ri->getMin(x, y));
	}
	~segTreeBeats() {
		if(le != NULL) delete le;
		if(ri != NULL) delete ri;
	}
};

long long a[mxn];

struct seg {
	long long mx, mn, resmx, resmn, lz, zero, ismax;
} d[mxn * 4];

void up(long long i) {
	d[i].mx = max(d[i * 2 + 1].mx, d[i * 2].mx);
	d[i].resmx = max(d[i * 2 + 1].resmx, d[i * 2].resmx);
	d[i].mn = min(d[i * 2 + 1].mn, d[i * 2].mn);
	d[i].resmn = min(d[i * 2 + 1].resmn, d[i * 2].resmn);
}

void pro(long long i, long long l, long long r) {
	if(d[i].zero) {
		d[i].mx = d[i].mn = 0;
		d[i].resmx = a[r];
		d[i].resmn = a[l];
		// d[i].lz = 
		d[i].ismax = 0;

		if(l < r) {
			d[i * 2].zero = 1;
			d[i * 2 + 1].zero = 1;
			d[i * 2].ismax = d[i * 2].lz = 0;
			d[i * 2 + 1].ismax = d[i * 2 + 1].lz = 0;
		}
	}

	if(d[i].ismax) {
		d[i].mx = a[r]; 
		d[i].mn = a[l];
		d[i].resmx = d[i].resmn = 0;
		// d[i].lz = 
		d[i].zero = 0;

		if(l < r) {
			d[i * 2].ismax = 1;
			d[i * 2 + 1].ismax = 1;
			d[i * 2].zero = d[i * 2].lz = 0;
			d[i * 2 + 1].zero = d[i * 2 + 1].lz = 0;
		}
	}

	if(d[i].lz != 0) {
		d[i].mx += d[i].lz;
		d[i].mn += d[i].lz;
		d[i].resmx -= d[i].lz;
		d[i].resmn -= d[i].lz;

		if(l < r) {
			d[i * 2].lz += d[i].lz;
			d[i * 2 + 1].lz += d[i].lz;
		}
	}

	d[i].lz = d[i].zero = d[i].ismax = 0;
}

void build(long long l, long long r, long long i) {
	d[i].lz = d[i].zero = d[i].ismax = 0;
	if(l == r) {
		d[i].mx = d[i].mn = 0;
		d[i].resmx = d[i].resmn = a[l];
		return;
	}
	long long m = (l + r) / 2;
	build(l, m, i * 2);
	build(m + 1, r, i * 2 + 1);
	up(i);
}

void setZero(long long l, long long r, long long i, long long x, long long y) {
	pro(i, l, r);
	if(x > y) return;
	if(l > y || r < x) return;
	if(l >= x && r <= y) {
		d[i].zero = 1;
		pro(i, l, r);
		return;
	}
	long long m = (l + r) / 2;
	setZero(l, m, i * 2, x, y);
	setZero(m + 1, r, i * 2 + 1, x, y);
	up(i);
}

void setMax(long long l, long long r, long long i, long long x, long long y) {
	pro(i, l, r);
	if(x > y) return;
	if(l > y || r < x) return;
	if(l >= x && r <= y) {
		d[i].ismax = 1;
		pro(i, l, r);
		return;
	}
	long long m = (l + r) / 2;
	setMax(l, m, i * 2, x, y);
	setMax(m + 1, r, i * 2 + 1, x, y);
	up(i);
}

void add(long long l, long long r, long long i, long long x, long long y, long long val) {
	pro(i, l, r);
	if(x > y) return;
	if(l > y || r < x) return;
	if(l >= x && r <= y) {
		d[i].lz += val;
		long long m = (l + r) / 2;
		if(l != r) {
			pro(i * 2, l, m);
			pro(i * 2 + 1, m + 1, r);
		}
		pro(i, l, r);
		return;
	}
	long long m = (l + r) / 2;
	add(l, m, i * 2, x, y, val);
	add(m + 1, r, i * 2 + 1, x, y, val);
	up(i);
}

long long getLeftMax(long long l, long long r, long long i, long long val) {
	pro(i, l, r);
	if(d[i].mx < val) return -1;
	if(l == r) return l;
	long long m = (l + r) / 2;
	long long ret = getLeftMax(l, m, i * 2, val);
	if(ret == -1) ret = getLeftMax(m + 1, r, i * 2 + 1, val);
	return ret;
}

long long getLeftResmax(long long l, long long r, long long i, long long val) {
	pro(i, l, r);
	if(d[i].resmx < val) return -1;
	if(l == r) return l;
	long long m = (l + r) / 2;
	long long ret = getLeftResmax(l, m, i * 2, val);
	if(ret == -1) ret = getLeftResmax(m + 1, r, i * 2 + 1, val);
	return ret;
}

long long get(long long l, long long r, long long i, long long x) {
	pro(i, l, r);
	if(l == r) return d[i].mx;
	long long m = (l + r) / 2;
	if(x <= m) return get(l, m, i * 2, x);
	return get(m + 1, r, i * 2 + 1, x);
}

vi distribute_candies(vi c, vi l, vi r, vi v) {
	long long n = c.size(), q = l.size();
	vector<long long> ret(n);
	if(n * q <= 2000 * 2000) {
		for(long long i = 0; i < q; i++) {
			for(long long j = l[i]; j <= r[i]; j++) {
				ret[j] += v[i];
				ret[j] = min(1ll * c[j], max(0ll, ret[j]));
			}
		}
		return vi(all(ret));
	}
	if(*min_element(all(v)) >= 0) {
		for(long long i = 0; i < q; i++) {
			ret[l[i]] += v[i];
			if(r[i] + 1 < n) ret[r[i] + 1] -= v[i];
		}
		for(long long i = 1; i < n; i++) {
			ret[i] += ret[i - 1];
		}
		for(long long i = 0; i < n; i++) {
			ret[i] = min(1ll * c[i], max(0ll, ret[i]));
		}
		return vi(all(ret));
	}
	if(*max_element(all(c)) == *min_element(all(c))) {
		vector<long long> tmp(n, 0);
		segTreeBeats *st = new segTreeBeats(0, n - 1, tmp);
		for(long long i = 0; i < q; i++) {
			st->add(l[i], r[i], v[i]);
			st->mnn(l[i], r[i], c[0]);
			st->mxx(l[i], r[i], 0);
		}
		for(long long i = 0; i < n; i++) {
			ret[i] = st->getSum(i, i);
		}
		return vi(all(ret));
	}
	vector<int> id(n);
	iota(all(id), 0);
	sort(all(id), [&](int x, int y) {
		return c[x] < c[y];
	});
	for(long long i = 1; i <= n; i++) {
		a[i] = c[id[i - 1]];
	}
	build(1, n, 1);
	for(long long j = 0; j < q; j++) {
		if(v[j] == 0) continue;
		if(v[j] < 0) {
			long long p = getLeftMax(1, n, 1, -v[j]);
			if(p == -1) p = n + 1;
			setZero(1, n, 1, 1, p - 1);
			add(1, n, 1, p, n, v[j]);
		} else {
			long long p = getLeftResmax(1, n, 1, v[j]);
			if(p == -1) p = n + 1;
			setMax(1, n, 1, 1, p - 1);
			add(1, n, 1, p, n, v[j]);
		}
	}
	for(long long i = 0; i < n; i++) {
		ret[id[i]] = get(1, n, 1, i + 1);
	}
	return vi(all(ret));
}
