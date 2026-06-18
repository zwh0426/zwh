#include<iostream>
#define stack_init_size 100
#define stackincrement 10
using namespace std;
typedef struct{
	int xpos;
	int ypos;
}PosType;
typedef struct DQNode{
	PosType seat;
	struct DQNode *next;
	struct DQNode *pre;
}DQNode,*DQueuePtr;
typedef struct{
	DQueuePtr rear;
	DQueuePtr front;
}DLinkQueue;
typedef struct{
	PosType *elem;
	int top;
	int stacksize;
	int incrementsize;
}SqStack;
void InitQueue(DLinkQueue &Q){
	Q.front=NULL;
	Q.rear=NULL;
}//InitQueue
void EnQueue(DLinkQueue &Q,PosType e){
	DQNode *p;
	p=new DQNode;
	p->seat.xpos=e.xpos;
	p->seat.ypos=e.ypos;
	p->next=NULL;
	p->pre=NULL;
	if(!Q.rear){
		Q.rear=p;
		Q.front=p;
	}
	else{
		Q.rear->next=p;
		p->pre=Q.rear;
		Q.rear=p;
	}
}//EnQueue
void GetHead(DLinkQueue Q,PosType &e){
	e.xpos=Q.front->seat.xpos;
	e.ypos=Q.front->seat.ypos;
}//GetHead
void DeQueue(DLinkQueue &Q){
	if(!Q.front) return;
	DQNode *p=Q.front;
	if(Q.front==Q.rear){
		Q.front=NULL;
		Q.rear=NULL;
	}
	else{
		Q.front=Q.front->next;
		Q.front->pre=NULL;
	}
	delete p;
}//DeQueue
bool QueueEmpty(DLinkQueue Q){
	return (Q.front==NULL);
}//QueueEmpty
void InitStack(SqStack &S){
	S.elem=new PosType [stack_init_size];
	S.top=-1;
	S.stacksize=stack_init_size;
	S.incrementsize=stackincrement;
}//InitStack
void increment(SqStack &S){
	PosType *a=new PosType[S.incrementsize+S.stacksize];
	for(int i=0;i<=S.top;i++){
		a[i]=S.elem[i];
	}
	delete[] S.elem;
	S.elem=a;
	S.stacksize+=S.incrementsize;
}//increment
int Push(SqStack &S,PosType e){
	if(S.elem==NULL) return 0;
	if(S.top==S.stacksize-1) increment(S);
	S.elem[++S.top]=e;
	return 1;
}//Push
bool Pop(SqStack &S,PosType &e){
	if(S.top==-1) return false;
	e=S.elem[S.top--];
	return true;
}
bool StackEmpty(SqStack S){
	return S.top==-1;
}
const int dirX[8]={-1,-1,0,1,1,1,0,-1};
const int dirY[8]={0,1,1,1,0,-1,-1,-1};
PosType NextPos(PosType cur,int v){
	PosType next;
	next.xpos=cur.xpos+dirX[v];
	next.ypos=cur.ypos+dirY[v];
	return next;
}//NextPos
bool Pass(int **maze,int m,int n,bool **visited,PosType pos){
	if(pos.xpos<0||pos.xpos>=m||pos.ypos<0||pos.ypos>=n)
		return false;
	return maze[pos.xpos][pos.ypos]==0&&!visited[pos.xpos][pos.ypos];
}//Pass
bool ShortestPath(int **maze,int m,int n,SqStack &S){
	if(maze[0][0]!=0) return false;
	bool **visited=new bool*[m];
	PosType **prev=new PosType*[m];
	for(int i=0;i<m;i++){
		visited[i]=new bool[n];
		prev[i]=new PosType[n];
		for(int j=0;j<n;j++){
			visited[i][j]=false;
			prev[i][j].xpos=-1;
			prev[i][j].ypos=-1;
		}
	}

	DLinkQueue Q;
	InitQueue(Q);

	visited[0][0]=true;
	PosType start={0,0};
	EnQueue(Q,start);

	bool found=false;
	PosType curpos,npos;

	while(!QueueEmpty(Q)&&!found){
		GetHead(Q,curpos);
		DeQueue(Q);

		for(int v=0;v<8&&!found;v++){
			npos=NextPos(curpos,v);
			if(Pass(maze,m,n,visited,npos)){
				visited[npos.xpos][npos.ypos]=true;
				prev[npos.xpos][npos.ypos]=curpos;
				EnQueue(Q,npos);

				if(npos.xpos==m-1&&npos.ypos==n-1){
					found=true;
				}
			}
		}
	}
	for(int i=0;i<m;i++) delete[] visited[i];
	delete[] visited;

	if(found){
		InitStack(S);
		PosType p={m-1,n-1};
		while(p.xpos!=0||p.ypos!=0){
			Push(S,p);
			p=prev[p.xpos][p.ypos];
		}
		Push(S,start);
}
	for(int i=0;i<m;i++) delete[] prev[i];
	delete[] prev;

	return found;
}//ShortestPath

void PrintMaze(int **maze,int m,int n){
	cout<<"Maze("<<m<<"x"<<n<<"):"<<endl;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<maze[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"(0=路,1=墙)"<<endl;
}

void PrintPath(SqStack &S){
	if(StackEmpty(S)){
		cout<<"没有路径!"<<endl;
		return;
	}
	cout<<"最短路径:"<<endl;
	PosType p;
	int step=0;
	while(!StackEmpty(S)){
		Pop(S,p);
		step++;
		cout<<"<"<<p.xpos<<","<<p.ypos<<">";
		if(!StackEmpty(S)) cout<<" -> ";
	}
}

int main(){
	int m,n;
	cout<<"请输入迷宫的行数与列数：";
	cin>>m>>n;
	int **maze=new int*[m];
	cout<<"请输入迷宫内容："<<endl;
	for(int i=0;i<m;i++){
		maze[i]=new int[n];
		for(int j=0;j<n;j++){
			cin>>maze[i][j];
		}
	}

	cout<<endl;
	PrintMaze(maze,m,n);
	SqStack S;
	if(ShortestPath(maze,m,n,S)){
		cout<<"找到最短路径！"<<endl;
		PrintPath(S);
	}
	else{
		cout<<"没有最短路径从<0,0>到<"<<m-1<<","<<n-1<<">!"<<endl;
	}
	for(int i=0;i<m;i++) delete[] maze[i];
	delete[] maze;

	return 0;
}
