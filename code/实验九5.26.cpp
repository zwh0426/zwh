#include<iostream>
#include"栈的基本操作1.cpp"
using namespace std;
typedef char **HuffmanCode;
typedef struct{
	int weight;
	int parent;
	char data;
	int lchild,rchild;
}HTNode;
typedef struct{
	HTNode *HTree;
	int root;
}HuffmanTree;
void Select(HuffmanTree HT,int n,int &s1,int &s2)
{
    int min1=-1,min2=-1;
    for(int i=0;i<n;i++)
    {
        if(HT.HTree[i].parent!=-1) continue;
        int w=HT.HTree[i].weight;
        if(min1==-1||w<HT.HTree[min1].weight)
        {
            min2=min1;
            min1=i;
        }
        else if(min2==-1||w<HT.HTree[min2].weight)
        {
            min2=i;
        }
    }
    s1=min1;s2=min2;
}//选择权值最小的两个结点，用s1，s2返回其下标 
void CreateHuffmanTree(HuffmanTree &HT,int *w,int n,char *ch){
	if(n<=1) {
 		HT.HTree = new HTNode[1];
        if(n == 1){
            HT.HTree[0].weight = w[0];
            HT.HTree[0].data = ch[0];
            HT.HTree[0].parent = HT.HTree[0].lchild = HT.HTree[0].rchild = -1;
            HT.root = 0;
		}else {
            HT.HTree[0].weight=0;
            HT.HTree[0].data='\0';
            HT.HTree[0].parent=HT.HTree[0].lchild=HT.HTree[0].rchild=-1;
            HT.root=-1;
        }
        return;
}
	int m=2*n-1;
	HT.HTree=new HTNode[m];
    for(int i=0;i<m;i++){
        HT.HTree[i].weight=0;
        HT.HTree[i].data='\0';
        HT.HTree[i].parent=HT.HTree[i].lchild=HT.HTree[i].rchild=-1;
    }
    for(int i=0;i<n;i++){
        HT.HTree[i].weight=w[i];
        HT.HTree[i].data=ch[i];
    }
    for(int i=n;i<m;i++){
        int s1,s2;
        Select(HT,i,s1,s2);
        HT.HTree[s1].parent=i;
        HT.HTree[s2].parent=i;
        HT.HTree[i].lchild=s1;
        HT.HTree[i].rchild=s2;
        HT.HTree[i].weight=HT.HTree[s1].weight+HT.HTree[s2].weight;
    }
    HT.root=m-1;
}
void Coding(HuffmanTree T,int i,SqStack &S,HuffmanCode &HC,int n){
	if((T.HTree[i].lchild==-1)&&(T.HTree[i].rchild==-1)&&i<n){
		HC[i]=new char[StackLength(S)+1];
		HC[i][StackLength(S)]='\0';
		for(int k=0;k<StackLength(S);k++){
			HC[i][k]=S.elem[k];
		}
	}
	else{
		SElemtype e;
		push(S,'0');
		Coding(T,T.HTree[i].lchild,S,HC,n);
		pop(S,e);
		push(S,'1');
		Coding(T,T.HTree[i].rchild,S,HC,n);
		pop(S,e); 
	}
}
void HuffmanCoding(HuffmanTree HT,HuffmanCode &HC,int n){
	SqStack S;
	HC=new char *[n];
	InitStack(S);
	Coding(HT,HT.root,S,HC,n);
	DestroyStack(S);
}
void print(int n,int *w,char *ch){
	for(int i=1;i<=n;i++){
		cout<<"第"<<i<<"个编码：";
		cin>>ch[i-1];
		cout<<"其权值为：";
		cin>>w[i-1];
	}
}
void result(char *ch,HuffmanCode &HC,int n){
	for(int i=0;i<n;i++){
		cout<<ch[i]<<"："<<HC[i]<<endl;
	}
}
int main (){
	int n;
	cout<<"请输入编码的个数：";
	cin>>n;
	if(n<=0){
        cout<<"个数必须大于0！"<<endl;
        return 1;
    }
	cout<<"请输入各编码的名称及权值：";
	cout<<endl;
	cout<<endl;
	int *w=new int[n];
	char *ch=new char[n];
	print(n,w,ch);
	HuffmanTree HT;
	CreateHuffmanTree(HT,w,n,ch);
	HuffmanCode HC;
	HuffmanCoding(HT,HC,n);
	result(ch,HC,n);
	for(int i=0;i<n;i++) delete[] HC[i];
	delete[] HC;
	delete[] HT.HTree;
	delete[] w;
	delete[] ch;
}
