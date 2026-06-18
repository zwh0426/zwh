#include <stdio.h>
#include<math.h>
void judge(int a,int *p_e);
int flag1=1;
int main(){
	int m,n,t,f=0,e=0;
	printf("please input m and n:");
	scanf("%d%d",&m,&n);
	if(m>n){
		t=m;
		n=m;
		n=t;
	}//保证m<n 
	printf("%d与%d之间的素数有：\n",m,n);
	for(int i=m;i<n;i++){
		flag1=1;
		judge(i,&e);
		if(flag1==1){
		printf("%-5d",i);
		f++;
	if(f%9==0){
	printf("\n");
	f=0;
}
}
}
	printf("\n");
	printf("总计%d个",e);	
	
	
	
	return 0;
} 
void judge(int a,int *p_e){
	if (a<2){
	flag1=0;
	return;
	}
	for(int j=2;j<=sqrt(a);j++){
		if(a%j==0){
			flag1=0;
			break;
		}
		
	}
	if(flag1==1){
		(*p_e)++;
	}
	

}

	
	
	
	
 
