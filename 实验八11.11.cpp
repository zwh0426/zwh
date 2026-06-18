#include<stdio.h>
int main(){
	int n;
	printf("请输入一个非零自然数n：");
	scanf("%d",&n);
	if(n<0||n!=(int)n)
	return false;//判断n是否为自然数 
	int i,j,a=n*n*n,b;
	for(i=1;;i+=2){
		int sum=0 ;
		b=i;
		for(j=0;j<n;j++){
			sum+=b;
			b+=2;
}//n等于几，就有几个奇数相加，想明白这点就可以很好想到如何从奇数中寻找到合适的奇数。 
	
	if(sum==a){
		b=i;
		printf("%d^3=",n);
		for(int j=0;j<n;j++){
		printf("%d",b);
		if (j<n-1)
		printf("+");
		b+=2;
		
	}
	printf("\n");
	break;
	
}
	
}
	
	
	
	return 0;
}
