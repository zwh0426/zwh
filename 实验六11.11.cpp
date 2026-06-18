#include<stdio.h>
int main(){
	int a;
	printf("请输入任意一个整数\n");
	scanf("%d",&a);
	int b,c=0;
	if(a>=0)
	b=a;
	if(a<0)
	b=-a;
	int d,f=b;
	while(b!=0){
	d=b%10;
	c=10*c+d;
	b=b/10;
	}
	if(c==f)
	printf("该整数是一个回文数\n");
	else
	printf("该整数不是一个回文数\n");
	return 0;
	
	
}
 
