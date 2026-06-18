#include<stdio.h>
int main(){
	short int a,b,c,d;
	unsigned short e,f,g,i;
	printf("请输入四个短整型数\n");
	scanf("%hd%hd%hd%hd",&a,&b,&c,&d);
	e=(unsigned short)a;
	f=(unsigned short)b;
	g=(unsigned short)c;
	i=(unsigned short)d;
	printf("%hu,%hu,%hu,%hu\n",e,f,g,i);
	unsigned short max,min;
	int s;
	max=e;
	if(max<f)max=f;
	if(max<g)max=g;
	if(max<i)max=i;
	min=i;
	if(min>g)min=g;
	if(min>f)min=f;
	if(min>e)min=e;
	s=max-min;
	printf("最大无符号数为%hu，对应的输入值是%hd\n",max,(short)max);
	printf("最小无符号数为%hu,对应的输入值是%hd\n",min,(short)min);
	printf("它们的差值是%u",s) ;
	return 0;
	
	
} 
