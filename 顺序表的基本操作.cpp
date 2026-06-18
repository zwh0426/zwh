#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define list_init_size 100
#define listincrement 10
typedef int elemtype;
typedef struct{
	elemtype *elem;
	int length;
	int listsize;
	int incrementsize;
}sqlist;
void increment(sqlist &L){
	elemtype *a;
	a= new elemtype [L.listsize+L.incrementsize];
	for(int i=0;i<L.length;i++) a[i]=L.elem[i];
	delete[] L.elem;
	L.elem=a;
	L.listsize+=L.incrementsize;
}//increment函数 
int initlist_sq(sqlist &L){
	L.elem=new elemtype [list_init_size];
	if(!L.elem) return 0;
	L.length=0;
	L.listsize=list_init_size;
	L.incrementsize=listincrement;
	return 1; 
}//1
void destorylist(sqlist &L){
	delete[] L.elem;
	L.elem=NULL;
	L.length=0;
}//2
void clearlist(sqlist &L){
	L.length=0;
}//3
int listempty(sqlist L){
	if(L.length==0) return 1;
	else return 0;
}//4
int listlength(sqlist L){
	return L.length;
}//5
int getelem(sqlist L,int i,elemtype &e){
	if(i<1||i>L.length) {
		cout<<("“i”值不合法");
		return 0;
}
	e=L.elem[i-1];
	return 1;
}//6
int locateelem_sq(sqlist L,elemtype e){
	int i=0;
	for(i;i<L.length;i++){
		if(L.elem[i]==e) return(i+1);
	}
	return 0;	
}//7
int priorelem(sqlist L,elemtype cur_e,elemtype &pre_e){
	for(int i=1;i<L.length;i++){
		if(cur_e==L.elem[i]) {
	   		pre_e=L.elem[i-1];
			return 1;
	}
	}
	return 0;
}//8
int nextlist(sqlist L,elemtype cur_e,elemtype &next_e){
	for(int i=0;i<L.length-1;i++){
		if(cur_e==L.elem[i]){
			next_e=L.elem[i+1];
			return 1;
		}
		}
		return 0;
}//9
int listinsert_sq(sqlist &L,int i,elemtype e){
	if(i<1||i>L.length+1) return 0;
	if(L.length>=L.listsize) increment(L);
	for(int j=L.length;j>=i;j--) L.elem[j]=L.elem[j-1];
	L.elem[i-1]=e;
	L.length++;
	return 1;
}//10
int listdelete(sqlist &L,int i,elemtype &e){
	if(i<1||i>L.length) return 0;
	e=L.elem[i-1];
	for(int j=i;j<L.length;j++) L.elem[j-1]=L.elem[j];
	L.length--;
	return 1;
}//11
void listtraverse(sqlist L){
	for(int i=0;i<=L.length-1;i++) {
		cout << L.elem[i] << "";
}
	cout<<endl;
}//12


