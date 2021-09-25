#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int MAX=1e6+9;

int fen[MAX];
void upd(int x,int val) 
{
	++x; 
	for (;x<MAX;x+=(x&-x)) fen[x]+=val;
}
int que(int x) 
{
	++x;
	int res=0; 
	for (;x;x-=(x&-x))
		res+=fen[x];
	return res;
}
int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0);
	upd(5,10);
	upd(7,9);
	cout<<que(8);
	return 0;
}
                            
