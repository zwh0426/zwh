#include<stdio.h>
int main(){
	int a;
	printf("please input a number,\n");
	scanf("%d",&a);
	printf("0x%08x\n",(unsigned)a);
	unsigned int i, b,c,d,e;
	i=a;//将a转化成无符号整形 
	b=i>>24;//保留最高八位 且移至最低八位 
	c=i<<24;//保留最低八位且移至最高八位 
	d=(i&0x00ff0000)>>8;//提取次高八位且移至次低八位 
	e=(i&0x0000ff00)<<8;//提取次低八位且移至次高八位 
	unsigned int result=b+c+d+e;//得出结果
	printf("0x%08x\n",(unsigned)result);//以无符号十六进制32位整数输出 
	return 0;



} 
