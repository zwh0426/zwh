#include<iostream>
#define maxsize 100
typedef char TElemType;
using namespace std;
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void CreateBiTree(BiTree &T,char *ch,int &i){
	char temp=ch[i++];
	if(temp=='#') T=NULL;
	else{
		T=new BiTNode;
		T->data=temp;
		CreateBiTree(T->lchild,ch,i);
		CreateBiTree(T->rchild,ch,i);
	}
}//先序建立 
void InOrder(BiTree T){
	if(T){
		InOrder(T->lchild);
		cout<<T->data;
		InOrder(T->rchild);
	}
}//中序 
void PostOrder(BiTree T){
	if(!T) return;
	PostOrder(T->lchild);
	PostOrder(T->rchild);
	cout<<T->data;
}//后序 
void LevelOrder(BiTree T){
	BiTree q[maxsize];
	int front,rear;
	front=0;
	rear=0;
	q[rear++]=T;
	if(!T) return;
	while(front!=rear){
		BiTree p=q[front++];
		cout<<p->data;
		if(p->lchild) q[rear++]=p->lchild;
		if(p->rchild) q[rear++]=p->rchild;
	}
}
int main(){
	char *ch=new char[maxsize];
	cout<<"请输入字符:";
	cin>>ch;
	BiTree T;
	int i=0;
	CreateBiTree(T,ch,i);//先序建立二叉树 
	cout<<"中序：";
	InOrder(T);
	cout<<endl;//中序输出
	cout<<"后序：";
	PostOrder(T);
	cout<<endl;//后序输出
	cout<<"层次：";
	LevelOrder(T);//层次输出 
	delete[] ch;
}
