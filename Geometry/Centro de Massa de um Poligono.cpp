double area = 0;
pto c;

c.x = c.y = 0;
for(int i = 0; i < n ; i++) {
	double aux = (arr[i].x * arr[i+1].y) - (arr[i].y * arr[i+1].x); // shoelace
	area += aux;
	c.x += aux*(arr[i].x + arr[i+1].x);
	c.y += aux*(arr[i].y + arr[i+1].y);
}

c.x /= (3.0*area);
c.y /= (3.0*area);

cout  << c.x <<  ' ' << c.y << endl;
