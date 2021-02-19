#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int MAX=1e6+9;
struct item {
	int key, prior;
	item * l, * r;
	item() { }
	item (int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};
typedef item * pitem;
void split (pitem t, int key, pitem & l, pitem & r) {
	if (!t)
		l = r = NULL;
	else if (key < t->key)
		split (t->l, key, l, t->l), r = t;
	else
		split (t->r, key, t->r, r), l = t;
}
void insert (pitem & t, pitem it) {
	if (!t)
		t = it;
	else if (it->prior > t->prior)
		split (t, it->key, it->l, it->r), t = it;
	else
		insert (it->key < t->key ? t->l : t->r, it);
}
void merge (pitem & t, pitem l, pitem r) {
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r), t = l;
	else
		merge (r->l, l, r->l), t = r;
}
void erase (pitem & t, int key) {
	if (t->key == key)
		merge (t, t->l, t->r);
	else
		erase (key < t->key ? t->l : t->r, key);
}
pitem unite (pitem l, pitem r) {
	if (!l || !r) return l ? l : r;
	if (l->prior < r->prior) swap (l, r);
	pitem lt, rt;
	split (r, l->key, lt, rt);
	l->l = unite (l->l, lt);
	l->r = unite (l->r, rt);
	return l;
}
pitem root = NULL;
int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0);
	item a = item(10,20);
	item b = item(10,20);
	insert(root, &a);
	insert(root, &b);
	return 0;
}
