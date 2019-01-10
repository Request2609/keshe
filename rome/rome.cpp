#include <iostream>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
 
//地图长度L，包括迷宫主体40，外侧的包围的墙体2，最外侧包围路径2（之后会解释）
 
#include<string.h>
#include<queue>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
#define WALL  0
#define ROUTE 1
 
//控制迷宫的复杂度，数值越大复杂度越低，最小值为0
static int Rank = 0;
#define Random(x) (rand() % x)
#define N 100
class room;
typedef struct node{
    int x, y;
    int a[2];
    struct node *next;
}_node;
class room{
private:
    int x,y;
public:    
    static int flag[N][N];
    static int map1[N][N];
    static int map2[N][N];
    room(){
        x=0;
        y=0;
    }
    ~room(){}
    void setX(int x){
        this->x=x;
    }
    int getX(){
        return x;
    }
    void setY(int y){
        this->y=y;
    }
    int getY(){
        return y;
    }
    void setmap1();
    void print();
    void create();
    static void printmap(int wide);
    void CreateMaze(int i,int j);
};
int room::flag[N][N]={{'\0'}};
int room::map1[N][N]={{0}};
int room::map2[N][N]={{0}};

void room::printmap(int wide){

    system("clear");
    for(int i=0;i<=wide+1;i++){
        for(int j=0;j<=wide+1;j++){
            if(i==1&&j==0){
                printf("   ");
                continue;
            }          
            if(i==wide&&j==wide+1){
                printf("   ");
                continue;
            }
            if(map2[i][j]==6)
                printf("\033[43:34m%s  \033[0m","#");
                
            else{
                printf("\033[44:32m%d  \033[0m",map2[i][j]);
            }
        }
        cout<<"\n"<<endl;
    }
    sleep(1);
}
void room::setmap1(){
    
    create();
}
void room::print(){
    
    int i,j;
    for(i=0;i<x+2;i++){
        for(j=0;j<y+2;j++){
            cout<<map1[i][j]<<"  ";
        }
        cout<<"\n"<<endl;
    }
}
//墙和路径的标识
 
//生成迷宫
 
void room::create() {
    int len;
    printf("\n\t\t请输入地图范围：");
    scanf("%d",&len);
    x = len ;
    y=  len;
	srand((unsigned)time(NULL));
	//最外围层设为路径的原因，为了防止挖路时挖出边界，同时为了保护迷宫主体外的一圈墙体被挖穿
    for (int i = 0; i <= len+1; i++){
		map1[i][0] = ROUTE;
		map1[0][i] = ROUTE;
		map1[i][len+1] = ROUTE;
		map1[len+1][i] = ROUTE;
	}
    for(int i=0;i<=len+1;i++){
        for(int j=0;j<=len+1;j++){
            cout<<map1[i][j]<<"  ";
        }
        cout<<"\n"<<endl;
    }
 
	//创造迷宫，（2，2）为起点
	CreateMaze(2, 2);
    
	//画迷宫的入口和出口
	map1[2][1] = ROUTE;
 
	//由于算法随机性，出口有一定概率不在（L-3,L-2）处，此时需要寻找出口
	for (int i = len - 3; i >= 0; i--) {
		if (map1[i][len - 3] == ROUTE) {
			map1[i][len - 2] = ROUTE;
			break;
		}
	}

    for(int i=0;i<=len+1;i++){
        for(int j=0;j<=len+1;j++){
            if(j==0||i==0||j==len+1||i==len+1){
                map2[i][j]=1;
                continue;
            }
            if(map1[i-1][j-1]==1)map1[i-1][j-1]=0;
            else map1[i-1][j-1]=1;
            map2[i][j]=map1[i-1][j-1];
            cout<<map1[i-1][j-1];
        }
        cout<<endl;
    }
    map2[len][len]=0;
    map2[len-1][len]=0;
    map2[len][len-1]=0;
	for (int i = 0; i <= len+1; i++) {
		for (int j = 0; j <= len+1; j++) {
			if (map2[i][j] == ROUTE) {
                cout<<map2[i][j]<<"  ";
			}
			else {
                cout<<map2[i][j]<<"  ";
			}
		}
		printf("\n\n");
	}
}
 
void room::CreateMaze( int x, int y) {
	map1[x][y] = ROUTE;
 
	//确保四个方向随机
	int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	for (int i = 0; i < 4; i++) {
		int r = rand() % 4;
		int temp = direction[0][0];
		direction[0][0] = direction[r][0];
		direction[r][0] = temp;
 
		temp = direction[0][1];
		direction[0][1] = direction[r][1];
		direction[r][1] = temp;
	}
 
	//向四个方向开挖
	for (int i = 0; i < 4; i++) {
		int dx = x;
		int dy = y;
 
		//控制挖的距离，由Rank来调整大小
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range>0) {
			dx += direction[i][0];
			dy += direction[i][1];
 
			//排除掉回头路
			if (map1[dx][dy] == ROUTE) {
				break;
			}
 
			//判断是否挖穿路径
			int count = 0;
			for (int j = dx - 1; j < dx + 2; j++) {
				for (int k = dy - 1; k < dy + 2; k++) {
					//abs(j - dx) + abs(k - dy) == 1 确保只判断九宫格的四个特定位置
					if (abs(j - dx) + abs(k - dy) == 1 && map1[j][k] == ROUTE) {
						count++;
					}
				}
			}
 
			if (count > 1) {
				break;
			}
 
			//确保不会挖穿时，前进
			--range;
			map1[dx][dy] = ROUTE;
		}
 
		//没有挖穿危险，以此为节点递归
		if (range <= 0) {
			CreateMaze(dx, dy);
		}
	}
}
void initroom(room &rr){
    
    rr.setmap1();
    room::map1[rr.getX()][rr.getY()]='0';
}
void getPrev(int &x,int& y,_node& t){
        
    t.a[0]=x;
    t.a[1]=y;
}

_node*getmap1(){
    _node *p ;
    p = (_node*)malloc(sizeof(_node));
    p->next = NULL;
    return p;
}

void copy(_node *t1,_node* t2){
    t1->a[0]=t2->a[0];
    t1->a[1]=t2->a[1];
    t1->x = t2->x;
    t1->y=t2->y;
}

void getway(_node* h,int wide){
    _node* tmp;
    tmp = h->next;
    while(tmp){
    //  printf("（%d，%d）",tmp->x,tmp->y);
      room::map2[tmp->x][tmp->y]=6;
      room::printmap(wide);
      tmp=tmp->next;
     // if(tmp!=NULL)
    }
    cout<<endl;
}

void Free(_node *h){
    
    _node* tmp,*p;
    p = h;
    tmp = p->next ;

    while(tmp){
        free(p) ; 
        p=tmp;
        tmp=tmp->next ;
    }
    free(p);
}
void widesearch(room rr){
    _node *h =getmap1();
    queue<_node>q;
    _node p ;
    p.x = 1;
    p.y =1;
    p.a[0]=-1;
    p.a[1]=-1;
    room::flag[1][1]=1;
    q.push(p);
    int flag= 0;
    while(1){
        if(q.empty()){
            break;
        }
        _node pp= q.front();
        _node*ss;
        ss = (_node*)malloc(sizeof(_node));
        copy(ss,&pp);
        ss->next = h->next ;
        h->next = ss;
        if(pp.x==rr.getX()&&pp.y==rr.getY()){
            flag = 1;
            break;
        }
        if(room::map2[pp.x-1][pp.y]==0&&!room::flag[pp.x-1][pp.y]){
            _node t;
            t.x = pp.x-1;
            t.y=pp.y;
            getPrev(pp.x,pp.y,t);
            room::flag[t.x][t.y]=1;
            q.push(t);
        }
        if(room::map2[pp.x][pp.y+1]==0&&!room::flag[pp.x][pp.y+1]){
            _node t;
            t.x = pp.x;
            t.y=pp.y+1;
            getPrev(pp.x,pp.y,t);
            q.push(t);
            room::flag[t.x][t.y]=1;
        }
        if(room::map2[pp.x+1][pp.y]==0&&!room::flag[pp.x+1][pp.y]){
            _node t;
            t.x = pp.x+1;
            t.y=pp.y;
            getPrev(pp.x,pp.y,t);
            q.push(t);
            room::flag[t.x][t.y]=1;
        }
        if(room::map2[pp.x][pp.y-1]==0&&!room::flag[pp.x][pp.y-1]){
            _node t;
            t.x = pp.x;
            t.y=pp.y-1;
            getPrev(pp.x,pp.y,t);
            q.push(t);
            room::flag[t.x][t.y]=1;
        }
        q.pop();
    }
    _node* way,*tmp,*tt;
    tmp = h->next;
    way =NULL ;
    
    way = (_node*)malloc(sizeof(_node));
    tt = (_node*)malloc(sizeof(_node));
    
    way->next = NULL;
    copy(tt,tmp);

    tt->next = way->next;
    way->next= tt;
    tmp = tmp->next;
    if(flag ==0){
        cout<<"no the way to end!"<<endl;
        Free(h);
        return ;
    }
    else
    {
    while(tmp!=NULL){   
        if(tmp->a[0]==-1&&tmp->a[1]==-1){
            _node *k;
            k = (_node*)malloc(sizeof(_node));
            copy(k,tmp);
            k->next =way->next;
            way->next = k;
            break;
        }
        if(tmp->x==way->next->a[0]&&tmp->y==way->next->a[1]){
            _node *k;
            k = (_node*)malloc(sizeof(_node));
            copy(k,tmp);
            k->next =way->next;
            way->next = k;
            }
           tmp=tmp->next;
        }
    }

    getway(way,rr.getX());
    Free(h);
    Free(way);
}

void getmap(room& rr){
    
    FILE *fp=NULL;
    string filename;
    int flag=0;
    cout<<"\n\t\tInput the filename:";
    cin>>filename;
    string s;
    if(!access(filename.data(),0))flag=1;
    else{
        cout<<"\n\t\tThe map not exist,are you continue to build a map?(y/n)"<<endl;
        cin>>s;
        if(s=="yes"||s=="y"||s=="Y"){
            fp =fopen(filename.data(),"w");
            if(fp==NULL){
                cout<<"file build error!"<<endl;
            }
            rr.create();
            fprintf(fp,"%d\n",rr.getX());
            for(int i=0;i<=rr.getX()+1;i++){
                for(int j=0;j<=rr.getX()+1;j++){
                    fprintf(fp,"%d ",room::map2[i][j]);
                }
                fprintf(fp,"%c",'\n');
            }
            cout<<"\n\t\tThe map has been build,do you want to go map?"<<endl;
            cin>>s;
            if(s=="yes"||s=="y"||s=="Y"){
                flag =1;
                fclose(fp);
            }
        }
        else{
            fclose(fp);
            exit(0);
        }
    }

    if(flag==1){
        int len;
        fp= fopen(filename.data(),"r");
        fscanf(fp,"%d\n",&len);
        rr.setX(len);
        rr.setY(len);
        for(int i=0;i<=len+1;i++){
            for(int j=0;j<=len+1;j++){
                if(fscanf(fp,"%d ",&room::map2[i][j])==EOF)break;
            }
        }
        fclose(fp);
    }
}
int main()
{
    int i;
    room rr;

    while(1){
            printf("\n\t\t[0].use your map and go?  [1].make map from computer");    
            cout<<"\n\n\t\tInput your choose:";
            cin>>i;
            switch(i){
               case 1:
                    initroom(rr);
                    widesearch(rr);
                    break;
                case 0:
                    getmap(rr);
                    widesearch(rr);
        }
    }
    return 0;
}

