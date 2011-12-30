#define _CRT_SECURE_NO_WARNINGS
#define QUORA_CC
#ifdef QUORA_CC
#include <stdio.h>
#include <string.h>
#include <time.h>
const char MAXROW = 10;
const char MAXCOL = 10;
char ROW,COL,ROOMS=0;
char matrix[10][10];
char visited[10][10];
//start point of duck
char starti,startj;
//end point of duck
char endi,endj;
clock_t begin,end,duration;
//simulate stack one
char stacki[100];char stackj[100];char top;
inline void push(char x,char y){*(stacki+top)=x;*(stackj+top)=y;top++;}
inline void peek(char* x,char* y){if(top){*x = *(stacki+top-1);*y = *(stackj+top-1);}}
inline void pop(){if(top){top--;}}
//simulate stack two
char stacki_[100];char stackj_[100];char top_;
inline void push_(char x,char y){*(stacki_+ top_)=x;*(stackj_+top_)=y;top_++;}
inline void peek_(char* x,char* y){if(top_){*x = *(stacki_+top_-1);*y = *(stackj_+top_-1);}}
inline void pop_(){if(top_){top_--;}}

//simulate trace-back stack three
char trace_stacki[100];char trace_stackj[100];char trace_top;
inline void trace_push(char x,char y){*(trace_stacki + trace_top)=x;*(trace_stackj + trace_top)=y;trace_top++;}
inline void trace_peek(char* x,char* y){
	if(trace_top){*x = *(trace_stacki+trace_top-1);*y = *(trace_stackj+trace_top-1);}
}
inline void trace_pop(){if(trace_top){trace_top--;}}

inline char isConnected(char remain){
	char x,y;top_=0;trace_top=0;
	push_(endi,endj);
	while(top_){
		peek_(&x,&y);pop_();
		if(*(*(visited+x)+y)==4) {(*(*(visited+x)+y))++;trace_push(x,y);remain--;}
		if(remain<=0) break;
		if(*(*(visited+x-1)+y)==4) push_(x-1,y);
		if(*(*(visited+x)+y+1)==4) push_(x,y+1);
		if(*(*(visited+x+1)+y)==4) push_(x+1,y);
		if(*(*(visited+x)+y-1)==4) push_(x,y-1);
	}
	while(trace_top){trace_peek(&x,&y);trace_pop();(*(*(visited+x)+y))--;}
	return remain;
}

//iterative solution
int DFS(){
	register int ret=0,passed=0;
	char x=starti,y=startj,flag=0;
	if(isConnected(ROOMS)) return 0;
	if(*(*(visited+x-1)+y)==4){ push(x-1,y);}
	if(*(*(visited+x)+y+1)==4){ push(x,y+1);}
	if(*(*(visited+x+1)+y)==4){ push(x+1,y);}
	if(*(*(visited+x)+y-1)==4){ push(x,y-1);}
	while(top){
		peek(&x,&y);flag=0;
		if(*(*(matrix+x)+y)==3){if(passed==ROOMS) ret++;pop();continue;}
		if(*(*(visited+x)+y)==5){ (*(*(visited+x)+y))--;passed--;pop();continue;}
		(*(*(visited+x)+y))++;passed++;
		if(isConnected(ROOMS-passed)){(*(*(visited+x)+y))--;passed--;pop();continue;}
		if(*(*(visited+x-1)+y)==4||(x-1==endi&&y==endj)){ push(x-1,y);flag++;}
		if(*(*(visited+x)+y+1)==4||(x==endi&&y+1==endj)){ push(x,y+1);flag++;}
		if(*(*(visited+x+1)+y)==4||(x+1==endi&&y==endj)){ push(x+1,y);flag++;}
		if(*(*(visited+x)+y-1)==4||(x==endi&&y-1==endj)){ push(x,y-1);flag++;}
		if(!flag){passed--;*(*(visited+x)+y) = 4;pop();}
	}
	return ret;
}

int main(){
	FILE* fp=fopen("input.txt","r");
	int i,j,temp;
	while(!feof(fp)){
		fscanf(fp,"%d %d",&COL,&ROW);
		//printf("%d %d\n",ROW,COL);
		memset(matrix,0,sizeof(matrix));
		for(i=0;i<MAXROW;i++) for(j=0;j<MAXCOL;j++) visited[i][j] = 6;//6 init value
		top = ROOMS = 0;
		for(i=0;i<ROW;i++) for(j=0;j<COL;j++){
			fscanf(fp,"%d",&temp);matrix[i][j] = temp;
			printf("%d ",temp);if(j==COL-1) printf("\n");
			if(temp==2) {starti=i,startj=j;visited[i][j]=2;}
			else if(temp==3) {endi=i,endj=j;visited[i][j]=3;}
			else if(temp==0){ ROOMS++;visited[i][j]=4;}
		}
		begin =clock();
		printf("%d\n",DFS());
		end = clock();
		duration = (clock_t)(end - begin) / CLOCKS_PER_SEC;
		printf("time elapsed : %d sec\n",duration);
		printf("\n");
	}
	fclose(fp);
	return 0;
}
#endif