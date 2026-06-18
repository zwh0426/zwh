#include<iostream>
#include<stdio.h>
#include"不带头结点的单链表的基本操作.cpp"
using namespace std;
void deepcopy_L(linklist &L1,linklist L2) {
	L1=NULL;
	Lnode *p=L2;
	Lnode *tail=NULL;
	while(p!=NULL){
		Lnode *s=new Lnode;
		s->data=p->data;
		s->next=NULL;
		if(L1==NULL){
			L1=s;
			tail=s;
		}
		else{
			tail->next=s;
			tail=s;
		}
		p=p->next;
	}
}//拷贝 
void unionset(linklist *L1,linklist L2){
	int lenL2=ListLength(L2);
	for(int i=1;i<=lenL2;i++){
		elemtype e;
		GetElem(L2,i,&e);
		if(LocateElem_L(*L1,e)==0){
			ListInsert_L(L1,ListLength(*L1)+1,e);
		}
	}
}//并集 
void intersectionset(linklist *L1,linklist L2){
	int lenL1=ListLength(*L1);
	int i=1;
	while(i<=lenL1){
		elemtype e;
		GetElem(*L1,i,&e);
		if(LocateElem_L(L2,e)!=0){
			i++; 
		}
		else {
				ListDelete(L1,i,e);
			lenL1--;
		}
	}
}//交集 
void differenceset(linklist *L1,linklist L2){
	int lenL1=ListLength(*L1);
	int i=1;
	while(i<=lenL1){
		elemtype e;
		GetElem(*L1,i,&e);
		if(LocateElem_L(L2,e)!=0){
			ListDelete(L1,i,e);
			lenL1--;
		}
		else i++;
	}
}//差集 
int main(){
	linklist L1,L2,L3,L4,L5,L6;
	InitList(&L1);
	InitList(&L2);
	InitList(&L3);
	InitList(&L4);
	InitList(&L5);
	InitList(&L6);
	int length1,length2;
	//初始化 
	cout<<"*************input*************"<<endl;
	cout<<"num=";
	cin>>length1;
	cout<<"elem=";
	for(int i=1;i<length1+1;i++){
		elemtype e;
		cin>>e;
		ListInsert_L(&L1,i,e);
	}
	cout<<endl;
	cout<<"*************input*************"<<endl;
	cout<<"num=";
	cin>>length2;  
	cout<<"elem=";
	for(int i=1;i<length2+1;i++){
		elemtype e;
		cin>>e;
		ListInsert_L(&L2,i,e);
	}
	cout<<endl;
	//输入L1L2的值 
	
	
	cout<<"A=<";
	ListTraverse(L1);
	cout<<">"<<endl;
	cout<<"B=<";
	ListTraverse(L2);
	cout<<">"<<endl;
	//输出AB中的元素
	
	deepcopy_L(L3,L1);
	deepcopy_L(L4,L1);
	deepcopy_L(L5,L1);
	deepcopy_L(L6,L2);
	//将链表中的数据进行拷贝，防止数据混乱。 
	
	unionset(&L3,L2);
	intersectionset(&L4,L2);
	differenceset(&L5,L2);
	differenceset(&L6,L1);

	cout<<"A union B=<";
	ListTraverse(L3); 
	cout<<">"<<endl;
	
	cout<<"A intersection B=<";
	ListTraverse(L4);
	cout<<">"<<endl;
	
	cout<<"A - B=<";
	ListTraverse(L5);
	cout<<">"<<endl;
	
	cout<<"B - A=<";
	ListTraverse(L6);
	cout<<">"<<endl;	 
	//输出数据
	
	
	return 0;
} 

