const int maxN = 105;
typedef vector <int> vec;

bitset<maxN> matrix[maxN];
bitset<maxN> ans;

vec solve(int n, int m) {
	vec ptr;
	ptr.resize(n);

	int i = 0, j = 0;
	while(i < n and j < m) {
		int ind = -1;
		for(int row = i; row < n; row++)
			if(matrix[row][j])
				ind = row;
		if(ind == -1) {
			j++;
			continue ;
		}

		bitset<maxN> b;
		b = matrix[i];
		matrix[i] = matrix[ind];
		matrix[ind] = b;

		bool f = ans[i];
		ans[i] = ans[ind];
		ans[ind] = f;

		for(int row = i + 1; row < n; row++) {
			if(matrix[row][j]) {
				matrix[row] ^= matrix[i];
				ans[row] = ans[row] ^ ans[i];
			}
		}

		ptr[i] = j;
		i ++;
		j ++;
		

	}
	
	vec sol;

	if(i != n) {
		for (int row=i; row<n; row++)
			if(ans[row])
				return sol; //without answer;
	}
	sol.resize(m);

	for (int j=0; j<m; j++)
		sol[j] = 0;

	for (int row=i-1; row>=0; row--){
		int j = ptr[row];
		sol[j] = ans[row];
		for (int c=row-1; c>=0; c--)
			if(matrix[c][j]) ans[c] = ans[c] ^ sol[j];
	}
	return sol;
}

