#include<iostream>
#define maxsize 100
using namespace std;
typedef char TElemType;
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
}
bool CompleteBiTree(BiTree T){
	if(!T) return false;
	BiTree q[maxsize];
	int rear=0,front=0;//层次遍历用队列实现 
	q[rear++]=T;
	bool has_NULL=false;
	while(front!=rear){
		BiTree p=q[front++];//队头结点出队列 
		if(!p) {
			has_NULL=true;
			continue;
		}
		if(has_NULL) return false;
		q[rear++]=p->lchild;
		q[rear++]=p->rchild;
	}
}
int main(){
	char *ch=new char[maxsize];
	cout<<"请输入字符：";
	cin>>ch;
	int i=0;
	BiTree T;
	CreateBiTree(T,ch,i);
	if(CompleteBiTree(T)) cout<<"是完全二叉树。";
	else cout<<"不是完全二叉树。";
}
