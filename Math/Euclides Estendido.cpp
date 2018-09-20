int gcd,x,y;

//Ax + By = gcd(A,B)

void extendedEuclidian(int a,int b){
	
	if(b==0){
		gcd=a;
		x=1;
		y=0;
	} else{
		extendedEuclidian(b, a%b);
		
		int temp = x;
		x=y;
		y = temp - (a/b)*y;
	}
}
