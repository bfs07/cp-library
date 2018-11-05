#define N 4
bool isSafe(int mat[N][N],int row,int col) {
	for(int i = row - 1; i >= 0; i--)
		if(mat[i][col])	
			return false;
	for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--,j--)
		if(mat[i][j]) 
			return false;
	for(int i = row - 1, j = col + 1; i >= 0 && j < N; i--,j++)
		if(mat[i][j]) 
			return false;
	return true;
}
// inicialmente a matriz esta zerada
int queen(int mat[N][N], int row  = 0) {
	if(row >= N) {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				cout << mat[i][j] << ' ';
			}
			cout << endl;
		}		
		cout << endl << endl;
		return false;
	}
	for(int i = 0; i < N; i++) {
		if(isSafe(mat,row,i)) {
			mat[row][i] = 1;
			if(queen(mat,row+1))
				return true;
			mat[row][i] = 0;
		}
	}
	return false;
}
