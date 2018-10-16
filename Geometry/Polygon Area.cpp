
double polygonArea(vector<pto> &arr, int n) {
	int area = 0;
	// N = quantidade de pontos no polígono e armazenados em p;
	// OBS: VALE PARA CONVEXO E NÃO CONVEXO
	for(int i = 0; i<n; i++){
	  area += cross(arr[i], arr[(i+1)%n]);
	}
	return (double)abs(area/2.0);
}