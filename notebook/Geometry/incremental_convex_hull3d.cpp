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


int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0);
	int n;
	while (cin>>n)
	{
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
		int res=ans.size();
		for (int i=0;i<ans.size();i++)
			for (int j=i+1;j<ans.size();j++)
			{
				auto f1=ans[i],f2=ans[j];
				int arr1[]={f1.a,f1.b,f1.c},arr2[]={f2.a,f2.b,f2.c};
				vector<int> eq;
				for (int i=0;i<3;i++)
					for (int j=0;j<3;j++)
						if (arr1[i]==arr2[j])
							eq.push_back(arr1[i]);
				if (eq.size()!=2) continue;
				int x=f1.a+f1.b+f1.c-eq[0]-eq[1];
				int y=f2.a+f2.b+f2.c-eq[0]-eq[1];
				if (abs((p[x]-p[eq[0]]).cross(p[eq[1]]-p[eq[0]]).dot(p[y]-p[eq[0]]))<eps) res--;
			}
		cout<<res<<'\n';
	}
	return 0;
}
