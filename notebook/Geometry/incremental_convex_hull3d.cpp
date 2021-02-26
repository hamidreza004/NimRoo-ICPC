#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define pt2 pair<int,int> 
const int MAX=1500;
const ld eps=1e-9;

struct pt3
{
	ld x,y,z;
	pt3(ld x=0, ld y=0, ld z=0): x(x), y(y), z(z) {}
	pt3 operator - (const pt3 &t) const {return pt3(x-t.x,y-t.y,z-t.z);}
	pt3 cross (const pt3 &t) const {return pt3(y*t.z-t.y*z,z*t.x-t.z*x,x*t.y-t.x*y);}
	ld dot (const pt3 &t) const {return x*t.x+y*t.y+z*t.z;}
};

struct face 
{
	int a,b,c;
	pt3 q;
};

vector<face> hull3(const vector<pt3> &p)
{
	int n=p.size();
	assert(n>=3);
	vector<face> f;
	vector<vector<bool>> dead(n, vector<bool>(n, true));
	auto add_face = [&](int a, int b, int c) {
		f.push_back({a, b, c, (p[b] - p[a]).cross(p[c] - p[a])});
		dead[a][b] = dead[b][c] = dead[c][a] = false;
	};	
	add_face(0,1,2);
	add_face(0,2,1);
	for (int i=3;i<n;i++)
	{
		vector<face> f2;
		for (face &F : f)
		{
			if ((p[i]-p[F.a]).dot(F.q)>eps)
				dead[F.a][F.b]=dead[F.b][F.c]=dead[F.c][F.a]=true;
			else
				f2.push_back(F);
		}
		f.clear();
		for (face &F : f2)
		{
			if (dead[F.b][F.a]) add_face(F.b,F.a,i);
			if (dead[F.c][F.b]) add_face(F.c,F.b,i);
			if (dead[F.a][F.c]) add_face(F.a,F.c,i);
		}
		f.insert(f.end(),f2.begin(),f2.end());
	}
	return f;
}
ld dis(pt3 p)
{
	return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}

int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0);
	int t;
	cin>>t;
	for (int i=0;i<t;i++)
	{
		int n;
		cin>>n;
		vector<pt3> p;
		for (int i=0;i<n;i++)
		{
			ld x,y,z;
			cin>>x>>y>>z;
			pt3 a=pt3(x,y,z);
			p.push_back(a);
		}
		for (int i=3;i<n;i++) if (abs((p[1]-p[0]).cross(p[2]-p[0]).dot(p[i]))>eps) {swap(p[i],p[3]);break;}
		auto ans=hull3(p);
		ld area=0, vol=0;
		pt3 base=p[ans[0].a];
		for (auto t:ans) 
		{
			ld a=dis(p[t.a]-p[t.b]),b=dis(p[t.b]-p[t.c]),c=dis(p[t.c]-p[t.a]);
			ld s=(a+b+c)/2;
			ld tri=sqrt(s*(s-a)*(s-b)*(s-c));
			area+=tri;
			pt3 h=(p[t.b]-p[t.a]).cross(p[t.c]-p[t.a]);
			ld d=dis(h);
			h=pt3(h.x/d,h.y/d,h.z/d);
			ld height=abs(h.dot(base-p[t.a]));
			vol+=tri*height/3.0;
		}
		cout<<fixed<<setprecision(4)<<area<<" "<<vol<<'\n';
	}
	return 0;
}
