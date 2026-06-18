#include <iostream>
using namespace std;
#define maxsize 100
#define QueueIncrement 10
typedef int QElemType;
typedef struct{
	QElemType *data;
	int rear;
	int front;
	int queuesize;
	int incrementsize;
}SqQueue;
void IncrementQueuesize(SqQueue &Q){
	QElemType *a=new QElemType[Q.queuesize+Q.incrementsize];
	for(int k=0;k<Q.queuesize;k++){
		a[k]=Q.data[(Q.front+k)%Q.queuesize];
	}
	delete[] Q.data;
	Q.data=a;
	Q.front=0;
	Q.rear=Q.queuesize-1;
	Q.queuesize+=Q.incrementsize;
}
void InitQueue(SqQueue &Q){
	Q.data=new QElemType[maxsize]; 
	Q.front=Q.rear=0; 
	Q.incrementsize=QueueIncrement;
	Q.queuesize=maxsize;
}
int isEmpty(SqQueue Q){
	if(Q.front==Q.rear) return 1;
	else return 0;
}
int isFull(SqQueue Q){
	if(Q.front==(Q.rear+1)%maxsize) return 1;
	else return 0;
}
int EnQueue(SqQueue &Q,int x){
	if(Q.front==(Q.rear+1)%maxsize) IncrementQueuesize(Q);
	Q.data[Q.rear]=x;
	Q.rear=(Q.rear+1)%maxsize;
	return 1;
}
int DeQueue(SqQueue &Q,int &x){
	if(Q.front==Q.rear) return 0;
	x=Q.data[Q.front];
	Q.front=(Q.front+1)%maxsize;
	return 1;
}
int GetLen(SqQueue Q,int length){
	length=((Q.rear+maxsize)-Q.front)%maxsize;
}
int GetHead(SqQueue Q,int &e){
	if(Q.front=Q.rear) return 0;
	e=Q.data[Q.front];
}

int main(){
	SqQueue Q; 
	int n;
	cout<<"please input the number of rows:";
	cin>>n;
	printyanghui(Q,n);
}
