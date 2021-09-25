#include<bits/stdc++.h>
using namespace std;

typedef long double ld; 
typedef complex<ld> pt; 
typedef vector<pt> poly;
#define x real()
#define y imag()
typedef pair<pt, pt> line;
// +, -, * scalar well defined
const ld EPS = 1e-12;
const ld PI = acos(-1);
const int ON = 0, LEFT = 1, RIGHT = -1, BACK = -2, FRONT = 2, IN = 3, OUT = -3; 

inline bool Lss(ld a, ld b){ return a - b < -EPS; }
inline bool Grt(ld a, ld b){ return a - b > +EPS; } 
inline bool Leq(ld a, ld b){ return a - b < +EPS; }
inline bool Geq(ld a, ld b){ return a - b > -EPS; }
inline bool Equ(ld a, ld b){ return abs(a-b) < EPS; }

bool byX(const pt &a, const pt &b) 
{
    if (Equ(a.x, b.x)) return Lss(a.y, b.y);
    return Lss(a.x, b.x);
}

ld dot(pt a, pt b){return (conj(a) * b).x;}
ld cross(pt a, pt b){return (conj(a) * b).y;}
int relpos(pt a, pt b, pt c) //c to a-b
{
    b = b-a, c= c-a;
    if (Grt(cross(b,c), 0)) return LEFT;
    if (Lss(cross(b,c), 0)) return RIGHT;
    if (Lss(dot(b,c), 0)) return BACK;
    if (Lss(dot(b,c), abs(b))) return FRONT;
    return ON;
}

//START:
vector<pair<pt, pt>> get_antipodals(poly &p)
{
	int n = p.size();
	sort(p.begin(), p.end(), byX);
	vector <pt> U, L;
	for (int i = 0; i < n; i++){
		while (U.size() > 1 && relpos(U[U.size()-2], U[U.size()-1], p[i]) != LEFT)
			U.pop_back();
		while (L.size() > 1 && relpos(L[L.size()-2], L[L.size()-1], p[i]) != RIGHT)
			L.pop_back();
		U.push_back(p[i]);
		L.push_back(p[i]);
	}
	vector <pair<pt, pt>> res;
	int i = 0, j = L.size()-1;
	while (i+1 < (int)U.size() || j > 0){
		res.push_back({U[i], L[j]});
		if (i+1 == (int)U.size())
			j--;
		else if (j == 0)
			i++;
		else if (cross(L[j]-L[j-1], U[i+1]-U[i]) >= 0) i++;
		else
			j--;
	}
	return res;
}
//END.

int main()
{
    ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
    return 0;
}
