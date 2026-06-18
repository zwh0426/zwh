#include<iostream>
#define stack_init_size 100
#define stackincrement 10
#define TRUE 1
#define FALSE 0
typedef char SElemtype;
using namespace std;
typedef struct{
	SElemtype *elem;
	int top;
	int stacksize;
	int incrementsize;
}SqStack;
void InitStack(SqStack &S){
	S.elem=new SElemtype [stack_init_size];
	S.top=-1;
	S.stacksize=stack_init_size;
	S.incrementsize=stackincrement;
}
void increment(SqStack &S){
	char *a=new SElemtype[S.incrementsize+S.stacksize];
	for(int i=0;i<S.top+1;i++){
		a[i]=S.elem[i];
	}
	delete[] S.elem;
	S.elem=a;
	S.stacksize+=S.incrementsize;
}
int DestroyStack(SqStack &S){
	if(S.elem==NULL) return 0;
	delete[] S.elem;
	S.elem=NULL;
	S.top=-1;
	return 1;
}
int ClearStack(SqStack &S){
	if(S.elem==NULL) return 0;
	S.top=-1;
	return 1;
}
int StackEmpty(SqStack S){
	if(S.elem==NULL) return 0;
	if(S.top==-1) return TRUE;
	if(S.top!=-1) return FALSE;
}
int StackLength(SqStack S){
	if(S.elem==NULL) return 0;
	return (S.top+1);
}
int GetStack(SqStack S,SElemtype &e){
	if(S.elem==NULL||S.top==-1) return 0;
	e=S.elem[S.top];
	return 1;
}
int push(SqStack &S,SElemtype e){
	if(S.elem==NULL) return 0;
	if(S.top==S.stacksize-1) increment(S);
	S.elem[++S.top]=e;
	return 1;
}
int pop(SqStack &S,SElemtype &e){
	if(S.elem==NULL||S.top==-1) return 0;
	e=S.elem[S.top];
	S.top--;
	return 1;
}
void StackTraverse(SqStack S){
	for(int i=0;i<S.top+1;i++){
		cout<<S.elem[i]<<endl;
	}
}
void StackCopyArray(SqStack S,char *ch,int n){
	for(int i=0;i<n;i++){
		ch[i]=(char)S.elem[i];
	}
}
