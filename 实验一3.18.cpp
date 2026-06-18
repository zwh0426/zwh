#include<iostream>
#include<stdio.h>
#include"顺序表的基本操作.cpp"
using namespace std;
void deepcopy_sq(sqlist &L1, const sqlist &L2) {
    L1.elem=new elemtype[L2.listsize];
    for (int i=0; i<L2.length;i++) L1.elem[i]=L2.elem[i];
    L1.length=L2.length;
    L1.listsize=L2.listsize;
    L1.incrementsize=L2.incrementsize;
}//拷贝 
void unionset(sqlist &L1,sqlist L2){
	int lenL2=listlength(L2);
	for(int i=1;i<=lenL2;i++){
		elemtype e;
		getelem(L2,i,e);
		if(locateelem_sq(L1,e)==0){
			listinsert_sq(L1,listlength(L1)+1,e);
		}
	}
}//并集 
void intersectionset(sqlist &L1,sqlist L2){
	int lenL1=listlength(L1);
	int i=1;
	while(i<=lenL1){
		elemtype e;
		getelem(L1,i,e);
		if(locateelem_sq(L2,e)!=0){
			i++; 
		}
		else {
				listdelete(L1,i,e);
			lenL1--;
		}
	}
}//交集 
void differenceset(sqlist &L1,sqlist L2){
	int lenL1=listlength(L1);
	int i=1;
	while(i<=lenL1){
		elemtype e;
		getelem(L1,i,e);
		if(locateelem_sq(L2,e)!=0){
			listdelete(L1,i,e);
			lenL1--;
		}
		else i++;
	}
}//差集 
int main(){
	sqlist L1,L2,L3,L4,L5,L6;
	initlist_sq(L1);
	initlist_sq(L2);
	initlist_sq(L3);
	initlist_sq(L4);
	initlist_sq(L5);
	initlist_sq(L6);
	//初始化 
	cout<<"*************input*************"<<endl;
	cout<<"num=";
	cin>>L1.length;
	cout<<"elem=";
	for(int i=0;i<L1.length;i++){
		cin>>L1.elem[i];
	}
	cout<<endl;
	cout<<"*************input*************"<<endl;
	cout<<"num=";
	cin>>L2.length;  
	cout<<"elem=";
	for(int i=0;i<L2.length;i++){
		cin>>L2.elem[i];
	}
	cout<<endl;
	//输入L1L2的值 
	
	
	cout<<"A=<";
	for(int i=0;i<L1.length;i++)
		cout<<L1.elem[i];
	cout<<">"<<endl;
	 	cout<<"B=<";
	for(int i=0;i<L2.length;i++)
		cout<<L2.elem[i];
	cout<<">"<<endl;
	//输出AB中的元素
	
	deepcopy_sq(L3,L1);
	deepcopy_sq(L4,L1);
	deepcopy_sq(L5,L1);
	deepcopy_sq(L6,L2);
	//将顺序表中的数据进行拷贝，防止数据混乱。 
	
	unionset(L3,L2);
	intersectionset(L4,L2);
	differenceset(L5,L2);
	differenceset(L6,L1);

	cout<<"A union B=<";
	for(int i=0;i<L3.length;i++)
		cout<<L3.elem[i];
	cout<<">"<<endl;
	
	cout<<"A intersection B=<";
	for(int i=0;i<L4.length;i++)
		cout<<L4.elem[i];
	cout<<">"<<endl;
	
	cout<<"A - B=<";
	for(int i=0;i<L5.length;i++)
		cout<<L5.elem[i];
	cout<<">"<<endl;
	
	cout<<"B - A=<";
	for(int i=0;i<L6.length;i++)
		cout<<L6.elem[i];
	cout<<">"<<endl;	 
	//输出数据
	
	 
	return 0;
} 
 
