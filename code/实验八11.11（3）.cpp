#include<stdio.h>
int main(){
	int n;
	printf("请输入一个非0自然数n：");
	scanf("%d",&n);
	int lf=n*n*n;
	if(n<=0)
	return false;
	for(int i=1;;i+=2){
		int zjl=i;
		int sum=0;
		for(int j=0;j<n;j++){
			sum+=zjl;
			zjl+=2;
		}
		if(sum==lf){
			zjl=i;
			printf("%d*%d*%d=",n,n,n);
			for(int j=0;j<n;j++){
				printf("%d",zjl);
				if(j<n-1)
				printf("+");
				zjl+=2;
			}
			printf("\n");
			break; 
			
		}
	}
		
	
	
	
	
	return 0;
} 
