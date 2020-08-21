/*TCS Codevita 2020 
Question A Fill The Cube
*/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

// An Inplace function to 
// rotate a N x N matrix 
// by 90 degrees in 
// anti-clockwise direction 
void rotateMatrix(vector<vector<int>> & mat, int N) 
{ 
    // Consider all squares one by one 
    for (int x = 0; x < N / 2; x++) { 
        // Consider elements in group 
        // of 4 in current square 
        for (int y = x; y < N - x - 1; y++) { 
            // Store current cell in 
            // temp variable 
            int temp = mat[x][y]; 
  
            // Move values from right to top 
            mat[x][y] = mat[y][N - 1 - x]; 
  
            // Move values from bottom to right 
            mat[y][N - 1 - x] 
                = mat[N - 1 - x][N - 1 - y]; 
  
            // Move values from left to bottom 
            mat[N - 1 - x][N - 1 - y] 
                = mat[N - 1 - y][x]; 
  
            // Assign temp to left 
            mat[N - 1 - y][x] = temp; 
        } 
    } 
}

// Function to find the size of largest square sub-matrix of 1's
// present in the given binary matrix
int findLargestSquare(vector<vector<int>>  mat, int m, int n, int &max_size)
{
	// base condition
	if (m == 0 || n == 0) {

		if (max_size != 0) {
			max_size = max(max_size, mat[m][n]);
			return mat[m][n];
		}

		for (int i = 0; i <= m; i++) {
			if (mat[i][n] == 1) {
				max_size = 1;
				break;
			}
		}

		for (int j = 0; j <= n; j++) {
			if (mat[m][j] == 1) {
				max_size = 1;
				break;
			}
		}

		return max_size;
	}

	// find largest square matrix ending at mat[m][n-1]
	int left = findLargestSquare(mat, m, n - 1, max_size);

	// find largest square matrix ending at mat[m-1][n]
	int top = findLargestSquare(mat, m - 1, n, max_size);

	// find largest square matrix ending at mat[m-1][n-1]
	int top_left = findLargestSquare(mat, m - 1, n - 1, max_size);

	// largest square matrix ending at mat[m][n] will be 1 plus
	// minimum of largest square matrix ending at mat[m][n-1],
	// mat[m-1][n] and mat[m-1][n-1]

	int size = 0;
	if (mat[m][n] != 0) {
		size = 1 + min (min(top, left), top_left);
	}

	// update maximum size found so far
	max_size = max(max_size, size);

	// return the size of largest square matrix ending at mat[m][n]
	return size;
}
//melting matrix
vector<vector<int> > melt(vector<vector<int> > mat , int n){
	vector<vector<int> > meltmat = mat;
	for(int i=0;i<n;i++){
		int c;
		for(int j=n-1;j>0;){
				c=0;
			
				if(meltmat[j][i]==1 && meltmat[j-1][i]==0){
				meltmat[j][i] = 0;
				meltmat[j-1][i] = 1;
				c = 1;
				}
			if(c==1)
				j = n-1;
			else
				j--;
		}
	}
	return meltmat;
}

int main()
{
	int n;
	cin>>n;
	vector<vector<int>> mat(n , vector<int> (n));
	char a;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>a;
			if(a=='C'||a=='c'){
				mat[i][j]=0;
			}
			else
				mat[i][j] = 1;
		}
	}
	
	vector<vector<int> > ans;

	// size stores the size of largest square sub-matrix of 1's
	// and it is passed by reference
		
	int size = 0;

	findLargestSquare(melt(mat,n), n-1, n-1, size);
	int maxvalue = size;
	
	int b = n*n;
	
	for(int i=0;i<b-1;i++){
		
		//Rotate matrix
		rotateMatrix(mat,n);
		
		size = 0;
		
		findLargestSquare(melt(mat,n), n-1, n-1, size);
		
		if(maxvalue<size){
		maxvalue = size;
		ans = melt(mat,n);
		}
		
	}
	
	cout << maxvalue<<endl<<endl;
	cout<<"Resultant melted matrix"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(ans[i][j]==1)
				cout<<"-"<<" ";
			else
				cout<<"C"<<" ";
		}
		cout<<endl;
	}

	return 0;
}
