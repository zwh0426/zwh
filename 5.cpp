#include<stdio.h>

using namespace std;
int main(){
	char ch1,ch2,ch3;
	ch1=getchar();
	putchar('\n');
	ch2='z'-('z'-ch1+1)%26;
	ch3='a'+(ch1-'a'+1)%26;
	printf("%c,%c\n",ch2,ch3);
	
	
	
	return 0;
}
