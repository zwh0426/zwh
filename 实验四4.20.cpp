#include<iostream>
#include"栈的基本操作.cpp"
using namespace std;
void knapsack(int w[],int T,int n,SqStack &S){
	InitStack(S);
	int k=0;
	do{
	while(T>0&&k<n){
		if(T-w[k]>=0){
			push(S,k);
			T-=w[k];
		}
		k++;
	}
	if(T==0){
		cout<<"找到一组解（物品的序号）：";
		for(int i=0;i<=S.top;i++){
			cout<<S.elem[i]+1<<" ";
		}
		cout<<endl;
	}
	if(!StackEmpty(S)){
	pop(S,k);
	T+=w[k];
	k++;
}
else{
	break;
}
}
	while(!StackEmpty(S)||k<n);
}//背包求解函数
void output(int n,int w[]){
	cout<<"请输入每个物品的体积"<<endl;
	for(int i=1;i<n+1;i++){
		cout<<"第"<<i<<"个物品的体积="<<"";
		cin>>w[i-1];
	}
}//输出函数 
int main(){
	SqStack S;
	InitStack(S);
	int w[100];
	int n;
	int T;
	cout<<"请输入物品个数n="<<"";
	cin>>n;
	cout<<endl;
	output(n,w);
	cout<<endl;
	cout<<"请输入背包体积T="<<"";
	cin>>T;
	cout<<endl;
	knapsack(w,T,n,S);
}
