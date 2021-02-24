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

	for (int i=1; i<(int)upper_hull.size() - 1; i++)
		lower_hull.pb(upper_hull[i]);
	return lower_hull;

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

		vector <point> convex_hull = graham_scan(points);

		point st = convex_hull[0];
		int ind = 0;

		/*for (int i=1; i<(int)convex_hull.size(); i++)
			if(convex_hull[i].S > st.S)
				ind = i, st = convex_hull[i];
			else if (convex_hull[i].S == st.S and convex_hull[i].F < st.F)
				ind = i, st = convex_hull[i];
		*/
		int sz = convex_hull.size();
		//cout << sz << '\n';
		for (int i=0; i<sz; i++)
			cout << convex_hull[(i + ind)%sz].F << ' ' << convex_hull[(i + ind)%sz].S << ' ';
		cout << '\n';
	}

}
