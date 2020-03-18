int cross(pto a, pto b) { 
	return a.x * b.y - b.x * a.y;
}

int boundaryCount(pto a, pto b) {
	if(a.x == b.x) 
		return abs(a.y-b.y)-1;
	if(a.y == b.y)
		return abs(a.x-b.x)-1;
	return _gcd(abs(a.x-b.x), abs(a.y-b.y))-1;
}

int totalBoundaryPolygon(vector<pto> &arr, int n) {

	int boundPoint = n;
	for(int i = 0; i < n; i++) {
		boundPoint += boundaryCount(arr[i], arr[(i+1)%n]);
	}
	return boundPoint;
}

int polygonArea2(vector<pto> &arr, int n) {
	int area = 0;
	// N = quantidade de pontos no polígono e armazenados em p;
	// OBS: VALE PARA CONVEXO E NÃO CONVEXO
	for(int i = 0; i<n; i++){
	  area += cross(arr[i], arr[(i+1)%n]);
	}
	return abs(area);
}

int internalCount(vector<pto> &arr, int n) {

	int area_2 = polygonArea2(arr, n);
	int boundPoints = totalBoundaryPolygon(arr,n);
	return (area_2 - boundPoints + 2)/2;
}