int gcd(int a,int b){
	
	return (b==0)?a:gcd(b,a%b);
}
void pollard(int n){
	
	int i=1;
	srand(time(0));
	int x=rand()%(n-1)+1;
	int y=x;
	int k=2;
	
	while(true){
		
		i++;
		x=(x*x-1)%n;
		int d=gcd(abs(y-x),n);
		if(d>1 && d<n){
			
			cout<<d<<endl;
			return;
		}
		
		if(i==k){
			
			y=x;
			k*=2;
		}
	}
}
