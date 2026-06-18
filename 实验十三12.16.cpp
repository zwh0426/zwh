#include <stdio.h>
int main(){
	int a,b,c,d,e;
	int *term;
	int *p[5]={&a,&b,&c,&d,&e};
	scanf("%d%d%d%d%d",p[0],p[1],p[2],p[3],p[4]);
	for(int i=0;i<5;i++)
		for(int j=i+1;j<5;j++){
			if(*p[i]>*p[j]){
			term=p[i];
			p[i]=p[j];
			p[j]=term;//ц╟ещеепР 
		}
		}
	for(int i=0;i<5;i++)
		printf("%d ",*p[i]);
	printf("\n");
	printf("%d %d %d %d %d",a,b,c,d,e);
	
	return 0;
}

