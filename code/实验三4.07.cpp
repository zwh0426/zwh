#include<iostream>
#define list_init_size 100
#define listincrement 10
using namespace std;
typedef struct{
	int id;
	char name[20];
	int grade;
}student;//结构体定义 
typedef struct{
	student *elem;
	int length;
	int listsize;
	int incrementsize;
}sqlist;//顺序表定义 
int initlist(sqlist &L){
	L.elem=new student[list_init_size];
	if(!L.elem) return 0;
	L.length=0;
	L.listsize=list_init_size;
	L.incrementsize=listincrement;
	return 1;
}//初始化函数 
void increment(sqlist &L){
	student *a;
	a=new student [L.listsize+L.incrementsize];
	for(int i=0;i<L.length;i++) a[i]=L.elem[i];
	delete[] L.elem;
	L.elem=a;
	L.listsize+=L.incrementsize;
}//扩容函数 
int listinsert(sqlist &L,int i,student e){
	if(i<1||i>L.length+1) return 0;
	if(L.length>=L.listsize) increment(L);
	for(int j=L.length-1;j>i;j--) L.elem[j+1]=L.elem[j];
	L.elem[i-1]=e;  
	L.length++;
	return 1;
}//插入函数 
void input(int n,sqlist &L,student e){
	for(int i=1;i<n+1;i++){
		cout  <<  "请输入第"<<i<<"个同学的学号："  <<  "";
		cin>>e.id;
		cout  <<  "请输入第"<<i<<"个同学的名字："  <<  "";
		cin>>e.name;
		cout  <<  "请输入第"<<i<<"个同学的成绩："  <<  "";
		cin>>e.grade;
		listinsert(L,i,e);
		cout<<endl; 
	}
}//输出函数 
int getmax(sqlist L){
	int num=L.elem[0].grade;
	for(int i=1;i<L.length;i++){
		if(num<L.elem[i].grade) num=L.elem[i].grade;
	}
	return num;
} 
void sortdigit(sqlist &L,int n,int exp){
	n=L.length;
	student output[100];
	int count[10]={0};
	for(int i=0;i<n;i++){
		int digit=(L.elem[i].grade/exp)%10;
		count[digit]++;
	} 
	for(int i=1;i<10;i++){
		count[i]=count[i]+count[i-1];
	}
	for(int i=n-1;i>=0;i--){
		int digit=(L.elem[i].grade/exp)%10;
		output[count[digit]-1]=L.elem[i];
		count[digit]--;
	}
	for(int i=0;i<n;i++){
		L.elem[i]=output[i];
	}
}
void radixsort(sqlist &L,int n){
	n=L.length;
	int nummax=getmax(L);
	for(int exp=1;nummax/exp>0;exp=10*exp){
		sortdigit(L,n,exp);
	}
}//基数排序（从小到大）
void reservesqlist(sqlist &L){
	for(int i=0,j=L.length-1;i<j;i++,j--){
		student temp=L.elem[i];
		L.elem[i]=L.elem[j];
		L.elem[j]=temp;
	}
}//顺序表反转函数 
int main(){
	sqlist L;
	initlist(L);
	int n;
	cout  <<  "请输入学生人数:"  <<  ""  ;
	cin>>n;
	cout<<endl;
	student e;
	input(n,L,e);
	radixsort(L,n);
	reservesqlist(L); 
	cout<<"\n名次\t学号\t姓名\t成绩"<<"";
	cout<<endl;
	for(int i=0;i<L.length;i++){
		cout<<(i+1)   <<"\t" <<L.elem[i].id<<  "\t"<<     L.elem[i].name<<  "\t" << L.elem[i].grade;
		cout<<endl;
	} 
	return 0;
}

