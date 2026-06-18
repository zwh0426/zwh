#include<stdlib.h>
#include<iostream>
#define true 1
#define false 0
using namespace std;
typedef int elemtype;
typedef struct Lnode{
	elemtype data;
	struct Lnode *next;
}Lnode,*linklist;
void InitList(linklist *L){
	*L=new Lnode;
	(*L)->next=NULL;
}//1
void DestoryList(linklist *L){
	linklist p,q;
	p=(*L)->next;
	while(p!=NULL){
		q=p->next;
		delete p;
		p=q;
	}
	delete *L;
	*L=NULL; 
}//2
void ClearList(linklist *L){
	if(*L==NULL) return;
	linklist p,q;
	p=(*L)->next;
	while(p!=NULL){
		q=p->next;
		delete p;
		p=q;
	}
	(*L)->next=NULL; 
}//3
bool ListEmpty(linklist L){
	return L->next==NULL;
}//4
int ListLength(linklist L){
	linklist p;
	int length=0;
	p=L->next;
	while(p!=NULL){
		p=p->next;
		length++;
	}
	return length;
}//5
bool GetElem(linklist L,int i,elemtype *e){
	linklist p;
	int j=1;
	p=L->next;
	if(p==NULL||i<1) return false;
	while(p!=NULL&&j<i){
		p=p->next;
		j++;
	} 
	if(p==NULL) return false;
	*e=p->data;
	return true;
}//6
Lnode *LocateElem_L(linklist L,elemtype e){
	linklist p;
	p=L->next;
	if(p==NULL) return NULL;
	while(p!=NULL&&p->data!=e){
		p=p->next;
	}
	return p;
}//7
bool PriorElem(linklist L,elemtype cur_e,elemtype &pre_e){
	Lnode *p;
	p=L->next;
	if(L==NULL||L->next->data==cur_e) return false;
	while(p->next!=NULL){
		if(p->next->data==cur_e){
			pre_e=p->data;
			return true;
		}
		p=p->next;
	}
	return false;
}//8
bool NextList(linklist L,elemtype cur_e,elemtype &next_e){
	Lnode *p,*q;
	if(L==NULL) return false;
	p=L->next;
	q=p->next;
	while(p!=NULL&&q!=NULL){
		if(p->data==cur_e){
			next_e=q->data;
			return true;
		}
		else {
			p=q;
			q=q->next;
		}
	}
	return false;
}//9
bool ListInsert_L(linklist *L,int i,elemtype e){
	int length=ListLength(*L);
	if(i<1||i>length+1) return false;
	Lnode *p=*L;
	for(int j=1;j<i;j++){
		p=p->next;
	}
	Lnode *q=new Lnode;
	q->data=e;
	q->next=p->next;
	p->next=q;
	return true;
}//10
bool ListDelete(linklist *L,int i,elemtype &e){
	int length=ListLength(*L);
	if (i<1||i>length||*L==NULL) return false; 
	Lnode *p,*q;
	p=*L;
	q=p->next;
	if(q==NULL) return false;
	for(int j=1;j<i-1;j++){
		p=p->next;
		q=q->next;
	}
	p->next=q->next;
	e=q->data;
	delete q;
	return true;
}//11
void ListTraverse(linklist L){
	Lnode *p;
	p=L->next;
	while (p!=NULL){
		cout  <<  p->data  <<  "";
		p=p->next;
		}
}//12

