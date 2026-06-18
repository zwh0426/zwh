#include<iostream>
using namespace std;
void diagscan(int i,int j,int &jpos,int &maxlen,int n,int m,int **mat){
	int eq=0,len=0;
	int sj;
	while(i<n&&j<m){
		if(mat[i][j]==1){
			len++;
			if(!eq){
				sj=j;
				eq=1;
			}
		}
		else if(eq){
			if(len>maxlen){
				maxlen=len;
				jpos=sj;
			}
			eq=0;
			len=0;
		}
		i++;
		j++;
	}
	if(eq&&len>maxlen){
		maxlen=len;
		jpos=sj;
	} 
}
void diagmaxl(int **mat,int &maxlen,int &jpos,int m,int n){
	maxlen=0;jpos=-1;
	int istart=0;
	for(int k=-(m-1);k<=n-1;k++){
		int i=istart;
		int j=i-k;
		diagscan(i,j,jpos,maxlen,n,m,mat);
		if(k>=0) istart++;
	}
}
void SubString(char *&sub,char *str,int s,int len){
	char *p;
	int k;
	sub=new char[len+1];
	p=str+s-1;
	k=len;
	while(k){
		*sub++=*p++;
		k--;
	}
	*sub='\0';
	sub=sub-len;
}
int maxsamesubstring(char *string1,char *string2,char *&sub,int **mat,int n,int m,int &maxlen,int &jpos){
	char *p1,*p2;
	p1=string1;
	p2=string2;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(string1[j]==string2[i]) mat[i][j]=1;
			else mat[i][j]=0;
		}
	}
	diagmaxl(mat,maxlen,jpos,m,n);
	if(maxlen==0) *sub='\0';
	else SubString(sub,string1,jpos+1,maxlen);
	return maxlen;
}
int StrLength(char *str){
	if(str==NULL) return 0;
	int len=0;
	while(str[len]!='\0'){
		len++;
	}
	return len;
}
int main(){
	int m,n,maxlen=0,jpos=0,s,len,i,j;
	char *string1,*string2,*sub;
	string1=new char[100];
	string2=new char[100];
	sub=new char[100];
	cout<<"请输入字符串1：";
	cin>>string1;
	cout<<"请输入字符串2：";
	cin>>string2;
	m=StrLength(string1);
	n=StrLength(string2);
	int **mat=new int*[n];
	for(int i=0;i<n;i++){
		mat[i]=new int[m]();
	}
	maxsamesubstring(string1,string2,sub,mat,n,m,maxlen,jpos);
	cout<<"最长公共子串长度="<<maxlen<<endl;
	cout<<sub;
	return 0;
}
