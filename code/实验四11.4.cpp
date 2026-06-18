#include<stdio.h>
#include<stdlib.h>
int main(){
	int a,b,c,d,e,f;
	printf("请输入一个五位正整数：\n");
	scanf("%d",&a);
	if(a<=9999||a>=100000)
	{printf("input error\n");
	exit(-1);
	}
	b=a%10;
	c=(a%100)/10;
	d=(a%1000)/100;
	e=(a%10000)/1000;
	f=(a%100000)/10000;
	if(b==f&&c==e)
	printf("这是一个五位回文数\n");
	else
	printf("这不是一个五位回文数\n");
	return 0;
} 
