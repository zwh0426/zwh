#include<stdio.h>
#include<stdlib.h>
int main(){
	int a,b,c,d,e,f,g;
	printf("请输入一个四位正整数\n");
	scanf("%d",&a);
	if(a<=999||a>=10000)
	{
	printf("输入错误\n");
	exit(-1);
	}
	b=a%10;
	c=(a%100)/10;
	d=(a%1000)/100;
	e=(a%10000)/1000;
	f=1000*b+100*c+10*d+e;
	printf("%d\n",f);
	for(int i=0;i<3;i++){
		if(b<c) {g=b,b=c,c=g;
		}
		if(c<d){g=c;c=d;d=g;
		}
		if(d<e){g=d;d=e;e=g;
		}
		
	}
	int max,min;
	max=1000*b+100*c+10*d+e;
	min=1000*e+100*d+10*c+b;
	printf("%d\n",max);
	printf("%d\n",min);
	
	
	
	
	
	
	return 0;
} 
