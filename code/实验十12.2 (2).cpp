#include<stdio.h>
#include<string.h>
int main(){
	int a[10],b[10],c[20];
	printf("请输入数组a:"); 
	for(int i=0;i<10;i++)
		scanf("%d",&a[i]);
	printf("请输入数组b:");
	for(int j=0;j<10;j++)
		scanf("%d",&b[j]);//读入数据 

		
	for(int i=1;i<10;i++){
		int flagi=0;
		for(int j=0;j<9;j++)
			if(a[j]<a[j+1]){
				int zjl1=a[j];
				a[j]=a[j+1];
				a[j+1]=zjl1;
				flagi=1;
			}
			if(flagi==0)
			break;
		
}
	printf("数组a用冒泡法排序后降序排序为：");
	for(int j=0;j<10;j++)
	printf("%d ",a[j]); 
	printf("\n");//冒泡排序 
	
	for(int i=0;i<9;i++){
		int k=i;
		for(int j=i+1;j<10;j++)int r=0,p=0,q=0;
	while(p<10&&q<10)
		if(a[p]>=a[q])
			c[r++]=a[p++];
		else
			c[r++]=b[q++];//将a，b中较大的先排，较小的后排 
	while(p<10)
		c[r++]=a[p++];
	while(q<10)
		c[r++]=b[q++];//将a，b中剩余的最小元素进行补充 
			if(b[k]<b[j])
			k=j;
			if(k!=i){
				int zjl2=b[i];
				b[i]=b[k];
				b[k]=zjl2;
				
			}
}
		printf("数组b用选择排序法后降序为：");
		for(int i=0;i<10;i++)
		printf("%d ",b[i]);
		printf("\n");//选择排序
		
	
	printf("将这两个数组合并成一个降序数组c为：");
	for(int i=0;i<20;i++)
		printf("%d ",c[i]);
	
	
	
	
	
	return 0;
} 
