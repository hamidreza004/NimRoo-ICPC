#include<bits/stdc++.h>
using namespace std;
const int MAX=1e6+100;
struct node{
	int val,lazy;
}seg[MAX*4];
int n,q;
void merge(int id, int left, int right)
{
	seg[id].val=seg[left].val+seg[right].val;
}
void build(int s=0,int e=n,int id=0)
{
	seg[id].lazy=0;
	if (e-s==1)
	{
		seg[id].val=0;
		return ;
	}
	int mid=(s+e)>>1;
	build(s,mid,id*2+1),build(mid,e,id*2+2);
	merge(id,id*2+1,id*2+2);
}
void shift(int id)
{
	if (seg[id].lazy) 
	{
		seg[id*2+1].val+=seg[id].lazy;
		seg[id*2+2].val+=seg[id].lazy;
		seg[id].lazy=0;
	}
}
void update(int l,int r,int val, int s=0,int e=n,int id=0)
{
	if (e<=l || r<=s) return ;
	if (l<=s && e<=r)
	{
		seg[id].val+=val;
		seg[id].lazy+=val;
		return ;
	}	
	int mid=(s+e)>>1;
	shift(id);
	update(l,r,val,s,mid,id*2+1);
	update(l,r,val,mid,e,id*2+2);	
	merge(id,id*2+1,id*2+2);
}
int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	return 0;
}
