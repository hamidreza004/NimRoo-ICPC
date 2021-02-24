#include <bits/stdc++.h>

#define F first
#define S second
#define pii pair <int, int>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pii point;

const int LEFT_TURN=1, RIGHT_TURN=-1, COLLINEAR=0;


//r is in LEFT_TURN of pq;
int orientation(point p, point q, point r)
{
	ll val = 1LL * (q.S - p.S) * (r.F - q.F) - 1LL * (q.F - p.F) * (r.S - q.S);
	if (val == 0) return 0;  // Collinear
	return (val > 0)? -1: 1; // CW: -1 or CCW: 1
}

ll dist(point A, point B) {
	return 1LL * (A.F - B.F) * (A.F - B.F) + 1LL * (A.S - B.S) * (A.S - B.S);
}

vector <point> graham_scan(vector<point> points) {
	sort(points.begin(), points.end());
	vector <point> lower_hull;
	vector <point> upper_hull;

	int n = (int)points.size();
	if(n <= 1) return points;

	for (int i=0; i<n; i++)
	{
		while((int)lower_hull.size() >= 2 and orientation(lower_hull[lower_hull.size() - 2], lower_hull.back(), points[i]) != LEFT_TURN) // != LEFT_TURN for non_collinear
			lower_hull.pop_back();
		lower_hull.pb(points[i]);
	}

	for (int i=n-1; i>=0; i--)
	{
		while((int)upper_hull.size() >= 2 and orientation(upper_hull[upper_hull.size() - 2], upper_hull.back(), points[i]) != LEFT_TURN) // != LEFT_TURN for non_collinear
			upper_hull.pop_back();
		upper_hull.pb(points[i]);	
	}

	for (int i=1; i<(int)upper_hull.size(); i++)
		lower_hull.pb(upper_hull[i]);
	return lower_hull;

}


//return indexes {i, j} (hull number i, j-th point)
pii get_start_point(vector <vector <point> >& hulls) {
	int h = (int)hulls.size();
	pii ind;
	ind = {0, 0};
	point st = hulls[0][0];

	for (int i=0; i<h; i++) {
		int j = 0;
		for (auto p : hulls[i]) {
			if(p.S < st.S)
				st = p, ind = {i, j};
			else if(p.S == st.S and p.F < st.F)
				st = p, ind = {i, j};
			j++;
		}
	}
	return ind;
}

//return index of the point in hull which line p to point covver all points
int tangent(vector <point> v, point p) {

	int l=0;
	int r = v.size();
	if(r == 1) return 0;
	int l_before = orientation(p, v[0], v[v.size()-1]);
	int l_after = orientation(p, v[0], v[(l + 1) % v.size()]);
	while (l < r){
		int c = ((l + r)>>1);
		int c_before = orientation(p, v[c], v[(c + v.size() - 1) % v.size()]);
		int c_after = orientation(p, v[c], v[(c + 1) % v.size()]);
		int c_side = orientation(p, v[l], v[c]);
		if (c_before != RIGHT_TURN and c_after != RIGHT_TURN)
			return c;
		else if ((c_side == LEFT_TURN) and (l_after == RIGHT_TURN or l_before == l_after) or (c_side == RIGHT_TURN and c_before == RIGHT_TURN))
			r = c;
		else
			l = c + 1 ;
		l_before = -c_after; 
		l_after = orientation(p, v[l], v[(l + 1) % v.size()]);

	}
	if(l == v.size()) l--;

	return l;
}

//return indexes {i, j} (hull number i, j-th point)
pii get_next_point(vector <vector <point> >& hulls, pii o) {
	point p = hulls[o.F][o.S];
	pii next = {o.F, (o.S + 1) % hulls[o.F].size()};


	int h = hulls.size();

	for (int i=0; i<h; i++)
	{
		if(i == o.F) continue ;
		int s = tangent(hulls[i], p);
		point r = hulls[i][s];
		point q = hulls[next.F][next.S];
		if(orientation(p, q, r) == RIGHT_TURN or (orientation(p, q, r) == COLLINEAR and dist(p, r) < dist(p, q)))
			next = {i, s};
	}

	return next;

}

vector <point> chan(vector <point>& points) {
	int n = (int)points.size();
	int t = 0;
	while(true) {
		ll m = (1LL << (1LL << t));
		vector <vector <point> > hulls;
		for(ll i=0; i<n; i+=m) {
			vector <point> chunk;
			for (int j=i; j<min((ll)n, i+m); j++)
				chunk.pb(points[j]);
			hulls.pb(graham_scan(chunk));
		}

		vector <pii> hull;
		hull.pb(get_start_point(hulls));

		for (int i=0; i<m; i++) {
			pii p = get_next_point(hulls, hull.back());
			if(hulls[p.F][p.S] == hulls[hull[0].F][hull[0].S])
			{
				vector <point> convex_hull;
				for (int j=0; j<(int)hull.size(); j++) {
					if(convex_hull.size() == 0 or hulls[hull[j].F][hull[j].S] != convex_hull.back())
						convex_hull.pb(hulls[hull[j].F][hull[j].S]);
				}
				return convex_hull;
			}
			hull.pb(p);
		}
		++t;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		vector <point> points;
		for (int i=0; i<n; i++) {
			int x, y; cin >> x >> y;
			points.pb(pii(x, y));
		}

		while(n){

			vector <point> convex_hull = chan(points);

			point st = convex_hull[0];
			int ind = 0;

			for (int i=1; i<convex_hull.size(); i++)
				if(convex_hull[i].S > st.S)
					st = convex_hull[i], ind = i;

			int sz = convex_hull.size();
			for (int i=0; i<sz; i++)
				cout << convex_hull[(i + ind)%sz].F << ' ' << convex_hull[(i + ind)%sz].S << ' ';

			sort(points.begin(), points.end());
			sort(convex_hull.begin(), convex_hull.end());

			vector <point> rem;
			int ptr = 0;
			for (int i=0; i<n; i++)
			{
				if(ptr == convex_hull.size() or points[i] < convex_hull[ptr]) 
					rem.pb(points[i]);
				else if(points[i] == convex_hull[ptr])
					ptr ++;
			}
			n = rem.size();
			points = rem;
		}
		cout << '\n';
	}
}
