#include<stdio.h>
int main(){
	int a;
	short b,c;
	printf("请输入一个整数：\n");
	scanf("%d",&a);
	b=(a>>16)&0xffff;
	c=a&0xffff;
	printf("该数的低16位是0x%04x,所表示的有符号数是%d,它是%s\n",(unsigned short)c,c,(c%2==0)?"偶数":"奇数");
	printf("该数的高16位是0x%04x,所表示的有符号数是%d,它是%s\n",(unsigned short)b,b,(b%2==0)?"偶数":"奇数");
	return 0; 
	
	//感悟：要分清有符号与无符号的区别，不要因为有无符号的问题导致错误，如上述若不将b，c转化成无符号整数，就会导致出现错误。
	//且左移右移要注意补零还是补符号位，若补符号位可以考虑以短整型来定义变量。 
	
	
	
	
} 
