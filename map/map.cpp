#include <iostream>
#include"map.h"
void menu(){
    cout<<"\n\t\t----------------------------------------------------------------\n";
    cout<<"\t\t\tWelcome To The XiYous'DuBai Map Navigation System \n";
    cout<<"\t\t----------------------------------------------------------------\n";
    cout<<"\n\t\t\t\t【1】.Add way\n ";
    cout<<"\n\t\t\t\t【2】.Delete way \n";
    cout<<"\n\t\t\t\t【3】.Modify way\n";
    cout<<"\n\t\t\t\t【4】.Find the shortest way between two addresses\n";
    cout<<"\n\t\t\t\t【5】.Inqury address infomation\n";
    cout<<"\n\t\t\t\t【6】.Print all address"<<endl;;
    cout<<"\n\t\t\t\t【0】.exit\n";
    cout<<"\n\t\t----------------------------------------------------------------\n";
}

void findway(vector<mapnode>&ls,vector<mapedge>&ss){
    
//    int want;
    string s,e;
    cout<<"\n\t\tInput the start address:";
    cin>>s;
   /* cout<<"\n\t\tInput the end address:";
    cout<<"\n\t\t----------------------------------------------------------------\n";
    cout<<"\n\t\t\t【1】.Find the shortest way\n";
    cout<<"\n\t\t\t【2】.Find the greenest way\n";
    cout<<"\n\t\t\t【3】.Find the viewbest way\n";
    cout<<"\n\t\t----------------------------------------------------------------\n";
    cout<<"\t\tInput your choice:";
    cin>>want;
    switch(want){
            case 1:
                mapnode::want=LENGTH;
                break;
            case 2:
                mapnode::want=VIEW;
                break;
            case 3:
                mapnode::want=GREEN;
                break;
            default:
                mapnode::want=LENGTH;
    }*/
    mapnode::search(s,ls,ss);
}

void initway(vector<mapnode>&s,vector<mapedge>&ss){
 
    FILE *fp1,*fp2;
    int size;
    fp1=fopen("addrinfo","r");
    fp2 =fopen("weightinfo","r");
    if(fp1==NULL||fp2==NULL){
        cout<<"open file error!"<<endl;
        exit(1);
    }
    char name[N];
    int id;
    while(1){
        if(fscanf(fp1,"%d %s %d ",&id,name,&size)==EOF)break;
            mapnode p;
            p.addrname =name;
            p.id = id;
            for(int i=0;i<size;i++){
                int index; 
                if(fscanf(fp1,"%d ",&index)==EOF){
                        return ;    
                }
                p.ss.push_back(index-1);
        }
        s.push_back(p);
    }
    while(1){
        mapedge q;
        if(fscanf(fp2,"%d %d %d %d %d\n",&q.x,&q.y,&q.view_weight,&q.length_weight,&q.green_weight)==EOF)
            break;
        ss.push_back(q);
    }
    fclose(fp2);
    fclose(fp1);
  //  mapnode::testprint(s,ss);
   // int k;
   // cin>>k;
}

void addway(vector<mapnode>&ls,vector<mapedge>&ss,person p){
        
    if(p.weight==USER){
        cout<<"permission dinied!"<<endl;
        return ;
    }
    string ch;
    while(1){
        mapedge q;
        mapnode p,s;
        cout<<"Input the two address:";
        cin>>p.addrname;
        cin>>s.addrname;
        p.id=mapnode::getindex(ls,p.addrname);
        s.id=mapnode::getindex(ls,s.addrname);
        if(p.id==-1||s.id==-1)return;
        cout<<"Input length weight:";
        cin>>q.length_weight;
        cout<<"Input view weight:";
        cin>>q.view_weight;
        cout<<"Input green_weight:";
        cin>>q.green_weight;
        q.x = p.id-1;
        q.y = s.id-1;
        q.length_weight = p.length_weight;
        q.view_weight=p.view_weight;
        q.green_weight=p.green_weight;
        int i=mapedge::addedge(q,ls,ss);
        if(i==0)cout<<"The way has exist!"<<endl;
        cout<<"Add edge !continue?(N/Y)"<<endl;
        cin>>ch;
        if(ch=="n"||ch=="N"){
            break;
        }
    }
}
int mapedge::addedge(mapedge q,vector<mapnode>&ls,vector<mapedge>&ss){
    int flag =0;
    for(int j =0 ;j<(int)ls[q.x].ss.size();j++){
        if(ls[q.x].ss[j]==q.y){
            flag=1;
        }
    }
    for(int j =0 ;j<(int)ls[q.y].ss.size();j++){
        if(ls[q.x].ss[j]==q.x){
            flag=1;
        }
    }
    if(flag ==1)return 0;
    ls[q.x].ss.push_back(q.y);
    ls[q.y].ss.push_back(q.y);
    mapedge p ;
    p.x = q .y;
    p.y = q.x;
    p.view_weight = q.view_weight;
    p.length_weight = q.length_weight;
    p.green_weight = q.length_weight;
    ss.push_back(q);
    ss.push_back(p);
    return 1;
}
void deleteway(vector<mapnode>&ss,vector<mapedge>&ls,person p){
    if(p.weight!=ADMIN){
        cout<<"Permission denied!"<<endl;
        return ;
    }
    while(1){
        mapnode q,s;
        mapedge ee ;
        cout<<"Input the two address name of the way:";
        cin>>q.addrname;
        cin>>s.addrname;
        q.id=ee.x = mapnode::getindex(ss,q.addrname);
        s.id=ee.y = mapnode::getindex(ss,s.addrname);
        if(ee.y==-1||ee.x==-1){
            cout<<"can't find place!"<<endl;
            return;
        }
        mapedge::deleteedge(q,ee,ss,ls);
        string ch;
        cout<<"Delete complete!continue?(N/Y)"<<endl;
        cin>>ch;
        if(ch=="N"||ch=="n"){
            break;
        }
    }
}

void mapedge::deleteedge(mapnode q,mapedge ee,vector<mapnode>&ss,vector<mapedge>&ls){
    
    vector<int>::iterator it ;

    for(it = ss[q.x].ss.begin();it!= ss[q.x].ss.end();it++){
        if(*it==q.y){
            ss[q.x].ss.erase(it);
        }
    }
    for(it = ss[q.y].ss.begin();it!= ss[q.y].ss.end();it++){
        if(*it==q.x){
            ss[q.y].ss.erase(it);
        }
    }
    vector<mapedge>::iterator iter;
    for(iter=ls.begin();iter!=ls.end();iter++){
        if(((*iter).x==ee.x&&(*iter).y==ee.y)||((*iter).y==ee.x&&(*iter).x==ee.y)){
            ls.erase(iter);
        }
    }
}

void modifyway(vector<mapnode>&ls,vector<mapedge>&ss,person p){
    
    if(p.weight!=ADMIN){
        cout<<"Permission denied!"<<endl;
        return;
    }
    while(1){
        mapedge q;
        mapnode p,s;
        cout<<"Input the two address:";
        cin>>p.addrname;
        cin>>s.addrname;
        p.id=mapnode::getindex(ls,p.addrname);
        s.id=mapnode::getindex(ls,s.addrname);
        if(p.id==-1||s.id==-1)return;
        cout<<"Input new length weight:";
        cin>>q.length_weight;
        cout<<"Input new view weight:";
        cin>>q.view_weight;
        cout<<"Input new green_weight:";
        cin>>q.green_weight;
        mapedge::modify(q,ss);
        string ch;
        cout<<"Modify finished!continue?(y/n)"<<endl;
        cin>>ch;
        if(ch=="n"||ch=="N"){
            break;
        }
    }
}

void mapedge::modify(mapedge q,vector<mapedge>&ss){
 
    for(int i =0;i<(int)ss.size();i++){
        if((ss[i].x==q.x&&ss[i].y==q.y)||(ss[i].x==q.y||ss[i].y==q.x)){
            ss[i].view_weight = q.view_weight;
            ss[i].green_weight = q.green_weight;
            ss[i].length_weight = q.length_weight;
        }
    }
}
void inquiryway(vector<mapnode>&s){
    
    while(1){
        mapnode p ;
        int flag =0;
        cout<<"Input the address name you want to inquiry:";
        cin>>p.addrname;
        for(int i= 0; i<(int)s.size();i++){
            if(s[i].addrname==p.addrname){
                flag =1;
                cout<<"The place:"<<p.addrname<<"surround it address is:"<<endl;
                for(int j=0;j<(int)s[i].ss.size();j++){
                    cout<<s[s[i].ss[j]].addrname<<endl;
                }
            }
        }
        if(flag==0){    
            cout<<"The place is not exist!"<<endl;
        }
        string ch;
        cout<<"The inquiry has done,continue?(Y/N)";
        cin>>ch;
        if(ch=="N"||ch=="n"){
            break;
        }
    }
}

void print(){

    cout<<"\n====================================================================================\n";
    cout<<"\n\t\tThe address locate map";
    cout<<"\n====================================================================================\n";
	printf("-------------------------------------------------------------------------------------\n");
	usleep(200000);
	printf("|-----------------------------------------------------------------------------------|\n");
	usleep(200000);
    printf("|                                  ★西安邮电大学 ★                                |\n");
    usleep(200000);
    printf("|-----------------------------------------------------------------------------------|\n");
    usleep(200000);
    printf("|                                      |    |                                       |\n");
    usleep(200000);
    printf("|                                      |    |                                       |\n");
    usleep(200000);
    printf("|                                      |    |                                       |\n");
    usleep(200000);
	printf("|               北门                   |    |                                  ↑北 |\n");
	usleep(200000);
	printf("|                 |                    |    |                 东区操场              |\n");
	usleep(200000);
	printf("|                 |                    |    |                       |               |\n");
	usleep(200000);
	printf("|                 |------------行政楼  |    |     东区正门----------|---逸夫教学楼  |\n");
	usleep(200000);
	printf("|                 |                    |    |                       |               |\n");
	usleep(200000);
	printf("|        -------- |                    | 子 |                       |---安美公寓    |\n");
	usleep(200000);
	printf("|       |         |                    |    |                       |               |\n");
	usleep(200000);
	printf("|       基础      |                    |    |                       |---安悦公寓    |\n");
	usleep(200000);
	printf("|      教学楼     |                    |    |                       |               |\n");
	usleep(200000);
	printf("|       |         |----大学生          | 午 |                       |               |\n");
	usleep(200000);
	printf("|       |         |   活动中心         |    |                       |               |\n");
	usleep(200000);
	printf("|       |         |                    |    |       东升苑----------|               |\n");
	usleep(200000);
	printf("|       |         |                    |    |                       |               |\n");
	usleep(200000);
	printf("|       |      图书馆-----播云湖       |    |                       |               |\n");
	usleep(200000);
	printf("|     实验楼      |                    |    |                       |               |\n");
	usleep(200000);
	printf("|       |         |------------------------------------------------ |               |\n");
	usleep(200000);
	printf("|       |         |                    |天桥|                       |               |\n");
	usleep(200000);
	printf("| 小操场|         |------------------------------------------------ |               |\n");
	usleep(200000);
	printf("|       |         |            |       |    |                                       |\n");
	usleep(200000);
	printf("|       |         |            |大操场 |    |                                       |\n");
	usleep(200000);
	printf("|       |         |            |       |    |                                       |\n");
	usleep(200000);
	printf("|   美食          |------体育馆|       |    |                                       |\n");
	usleep(200000);
	printf("|   广场          |            |       | 大 |                                       |\n");
	usleep(200000);
	printf("|       |         |            |       |    |                                       |\n");
	usleep(200000);
	printf("|       |       旭日苑                 |    |                                       |\n");
	usleep(200000);
	printf("|       |         |                    |    |                                       |\n");
	usleep(200000);
    printf("|       |         |                    |    |                                       |\n");
    usleep(200000);
	printf("|       |-------大学生超市---------    |    |                                       |\n");
    cout<<"\n====================================================================================\n";
    getchar();
    // mapnode::initnode(s);
   // mapnode::mapprint((int)s.size(),s);
}
int  choose(person p){
    int chose ;
    vector<mapnode>s;
    vector<mapedge>ss;
    initway(s,ss);
    int  k;
    while(1){
        system("clear");
        menu();
        cout<<"\t\tInput the choice:";
        cin>>chose;
        while('\n'!=getchar());
        switch(chose){
            case 1:
                addway(s,ss,p);
               mapnode::testprint(s,ss);
               cout<<"--------------------"<<endl;
               cin>>k;
                break;
            case 2:
                deleteway(s,ss,p);
                break;
            case 3:
                modifyway(s,ss,p);
                break;
            case 4:
                findway(s,ss);
                break;
            case 5:
                inquiryway(s);
                break;
            case 6:
                print();
                break;
            default:
                return -1;
        }   
    }
    //mapnode::update(s,ss);
}

void mapnode::update(vector<mapnode>&ss,vector<mapedge>&ls){
    FILE *fp1,*fp2; 
    fp1 = fopen("addrinfo","w");
    fp2 = fopen("weightinfo","w");
    if(fp1==NULL||fp2==NULL){
        cout<<"update info error!"<<endl;
        return ;
    }
    
    for(int i=0;i<(int)ss.size();i++){
        fprintf(fp1,"%d %s %d ",ss[i].id,ss[i].addrname.data(),(int)ss[i].ss.size());
        for(int j=0;j<(int)ss[i].ss.size();j++){
            fprintf(fp1,"%d ",ss[i].ss[j]);
        }
        fprintf(fp1,"%c",'\n');
    }
    for(int j =0 ;j<(int)ls.size();j++){
        fprintf(fp2,"%d %d %d %d %d\n",ls[j].x,ls[j].y,ls[j].view_weight,ls[j].length_weight,ls[j].green_weight);
    }
    fclose(fp1);
    fclose(fp2);
}

int  newUser(){
    int choose ;
    cout<<"\n\t\t----------------------------------------------------------------"<<endl;
    cout<<"\t\t 1.Regist                     2.Log in                   0.Exit"<<endl;
    cout<<"\t\t----------------------------------------------------------------\n"<<endl;
    cout<<"\t\tInput your choice:";
    cin>>choose;
    return choose;
}

void process(person p){

    int ch;
    while(true){
        system("clear");
       menu();
        ch =choose(p);
        if(ch==-1)break;
    }
}
int main()
{
    
    person p ;
    int choose ;
    int k =0;
    //const char *addinfo ="addrinfo";
    /*if(access(addinfo,0)){
        mapnode::initinfo(addinfo);
    }*/
    while((choose =newUser())){
        switch(choose){
            case 1:
                p.regist();
                break;
            case 2:
                if(p.login().tag!=0){
                    system("clear");
                    process(p);
                }
                break;
            default:
                if(k==3)exit(-1);
                k++;
                cout<<"wrong choice!"<<endl;
                break;
        }      
    }
    return 0;
}
/*
void mapnode::initinfo(const char*addfile){
    
    FILE *fp = fopen(addfile,"w");
    FILE*fp1 = fopen("weightinfo","w");
    if(fp1==NULL){
        cout<<"can't build file"<<endl;
        exit(-1);
    }
    if(fp==NULL){
        cout<<"can't build file "<<endl;
        exit(-1);
    }
    vector<mapnode>s;
    vector<mapedge>ss;
    while(1){
        mapnode p;
        cin>>p.addrname;
        p.id = 0;
        s.push_back(p);
    }
    string add_s,add_e;
    int index1,index2;
    while(1){
        mapedge q ;
        cin>>add_s;
        if(add_s=="-1")break;
        cin>>add_e;
        if(add_e=="-1")break;
        cin>>q.view_weight;
        cin>>q.length_weight;
        cin>>q.green_weight;
        index1 = getindex(s,add_s);
        index2 = getindex(s,add_e);
        if(index1==-1||index2==-1)return;
        q.x = index1;
        q.y = index2;
        s[index1].ss.push_back(index2);
        s[index2].ss.push_back(index1);
        ss.push_back(q);
    }
    savenode(fp,s) ;
    saveedge(fp1,ss);
    cout<<"complete !"<<endl;
}
*/
void mapnode::savenode(FILE*fp,const vector<mapnode>s){
        int i ,j;
        for(i=0;i<(int)s.size();i++){
            fprintf(fp,"%d %s %d ",s[i].id,s[i].addrname.data(),(int)s[i].ss.size());
            for(j=0;j<(int)s[i].ss.size();j++){
                fprintf(fp,"%d ",s[i].ss[j]);
            }

            fprintf(fp,"%c",'\n');
        }
        fclose(fp);
}
void mapedge::testprint(int n){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<leng[i][j]<<"  ";
        }
        cout<<endl;
    }
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cout<<view[i][j]<<"  ";
        }
        cout<<endl;
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cout<<green[i][j]<<"  ";
        }
        cout<<endl;
    }
    int k;
    cin>>k;
}
//void mapnode::mapprint(){
   
    /*
    cout<<"\n\t\t=================================================================";
    cout<<"\n\t\t\t\tThe address locate map";
    cout<<"\n\t\t=================================================================\n";
    for(int i=0;i<len;i++){
        cout<<s[i].addrname<<":";
        for(int j=0;j<len;j++){
            if(map1[i][j]!=35535){
                cout<<s[map1[i][j]].addrname<<"    ";
            }
         //   cout<<map1[i][j]<<"  ";
        }
        cout<<endl;
    }
    int k;
    cin>>k;*/
void mapedge::saveedge(FILE *fp,const vector<mapedge>s){
    int i ;
    for(i=0;i<(int)s.size();i++){
          fprintf(fp,"%d %d %d %d %d\n",s[i].x,s[i].y,s[i].view_weight,s[i].length_weight,s[i].green_weight);    
    }
    fclose(fp);
}

int mapnode::getindex(vector<mapnode>&ss,string str1){
    
    int i ;
    for(i=0;i<(int)ss.size();i++){
    //    cout<<ss[i].addrname<<endl;
        if(str1 == ss[i].addrname)
        return i+1;
    }
    cout<<"input info error!"<<endl;
    return -1 ;
}
void person::regist(){
    
    FILE *fp =fopen("usersinfo","a+");
    if(fp==NULL){
        cout<<"open file error!"<<endl;
        exit(-1);
    }
    int i =0;
    while(1){
        cout<<"\n\t\tInput username:";
        cin>>name;
        while('\n'!=getchar());
        cout<<endl;
        cout<<"\n\t\tInput password:";
        password = getpass();
        while(password.size()<6) {
            if(i==3)exit(-1);
            i++;
            cout<<"\n\t\tThe Password is two short,input again!"<<endl;
            cout<<"\n\t\tpasseord:"<<"";
            password = getpass();
        } 
        if(password.size()>6)break;
    }
    password=md5(password);
    weight = USER;
    fprintf(fp,"%s %s %d\n",name.data(),password.data(),weight);
    fclose(fp);   
}

person  person::login(){
    
    person q;
    cout<<"\n\t\tInput user name:";
    cin>>q.name;
    while('\n'!=getchar());
    cout<<"\n\t\tInput user password:";
    q.password=getpass();
    q.password  = md5(q.password);
    cout<<q.password<<endl;
    char n[N],p[N];
    FILE *fp ;
    fp = fopen("usersinfo","r");
    if(fp==NULL){
        cout<<"\n\t\topen file error!"<<endl;
        exit(-1);
    }
    while(fscanf(fp,"%s %s %d\n",n,p,&q.weight)!=EOF){
          if(!strcmp(p,q.password.data())&&!strcmp(n,q.name.data())){
            q.tag = 1;               
            break;
          }
    }
    return q;
}
void mapnode::testprint(vector<mapnode>&s,vector<mapedge>&ss){
    for(int i=0;i<(int)s.size();i++){
        cout<<s[i].id<<"-----"<<s[i].addrname<<"===";
        for(int j=0;j<(int)s[i].ss.size();j++){
            cout<<s[i].ss[j]<<"  ";
        }
        cout<<endl;
    }
    for(int j=0;j<(int)ss.size();j++){
        cout<<ss[j].x<<"++"<<ss[j].y<<"    "<<ss[j].view_weight<<"    "<<ss[j].green_weight<<"    "<<ss[j].length_weight<<endl;
    }
}

void mapnode::initnode(vector<mapnode>ls){
    
    int i=0,j=0;
    for(i=0;i<(int)ls.size();i++){
        for(j=0;j<(int)ls.size();j++){
            mapnode::map1[i][j]=35535;
        }
    }
    for(i=0;i<(int)ls.size();i++){
        for(j=0;j<(int)ls[i].ss.size();j++){
            if(i==map1[ls[i].ss[j]][i])continue;
            map1[i][ls[i].ss[j]]=ls[i].ss[j];
            map1[ls[i].ss[j]][i]=i;
        }
    }
}

void mapedge::initedge(vector<mapedge>&ss,int len){
    
    for(int i=0;i<=len;i++){
        for(int j=0;j<=len;j++){
            view[i][j]=35535;
            leng[i][j]=35535;
            green[i][j]=35535;
        }
    }
    for(int i=0;i<(int)ss.size();i++){
            view[ss[i].x][ss[i].y]=ss[i].view_weight;
            view[ss[i].y][ss[i].x]=ss[i].view_weight;
            leng[ss[i].x][ss[i].y]=ss[i].length_weight;
            leng[ss[i].y][ss[i].x]=ss[i].length_weight;
            green[ss[i].y][ss[i].x]=ss[i].green_weight;
            green[ss[i].x][ss[i].y]=ss[i].green_weight;
    }
  /*  mapedge::testprint(len);
    while('\n'!=getchar());
    int k;
    cin>>k;.*/
}
void  mapnode::search(string s,vector<mapnode>&ls,vector<mapedge>&ss){
    
    initnode(ls);
    initedge(ss,(int)ls.size());
    int index_s=getindex(ls,s);
    if(index_s==-1)return ;
    tag[index_s]=1;/*
    tag_green[index_s]=-1;
    tag_view[index_s]=-1;*/
    previous[index_s]=-1;/*
    previous_view[index_s]=-1;
    previous_green[index_s]=-1;*/

    for(int i=1;i<=(int)ls.size();i++){
        dist[i]=leng[index_s][i];/*
        dist_view[i]=view[index_s][i];
        dist_green[i]=green[index_s][i];*/
        if(dist[i]!=35535){
            previous[i]=index_s;
        }/*
        if(dist_view[i]!=35535){
            previous_view[i]=index_s;
        }
        if(dist_green[i]!=35535){
            previous_green[i]=index_s;
        }*/
    }
    dist[index_s]=0;
    int index;
    for(int j=2;j<=(int)ls.size();j++){
        int mins = 35535;
        index = index_s;
        for(int i=1;i<=(int)ls.size();i++){
            if(!tag[i]&&mins>dist[i]){
                mins = dist[i];
                index= i;
            }
        }
        
        tag[index]=1;
        int in;
        for(int i=1;i<=(int)ls.size();i++){
            if(!tag[i]&&leng[index][i]<35535){
                in = dist[index]+leng[index][i];
                if(in<dist[i]){
                    previous[i]=index; 
                    dist[i]=in;
                    }
                }
            }    
    }/*
    for(int i=1;i<=(int)ls.size();i++){
        cout<<previous[i]<<endl;
    }
    */
    printway(ls, s);
}

void mapnode::printway(vector<mapnode>ls,string s){
    
    cout<<"\n\t\tInput the end way:";
    string e;
    cin>>e;/*
    while('\n'!=getchar());
    for(int i=1;i<(int)ls.size();i++){
        cout<<previous[i]<<endl;
    }*/
    int index = getindex(ls,e);
    if(index==-1)return ;
    int k=previous[index];
    int ss=0;
    int a[N];
    while(k!=-1){
        a[ss]=k;
        ss++;
        k=previous[k];
    }
    cout<<"From"<<"   " <<s<<"->"<<e<<" the shortest way has  "<<dist[index]<<"m:\n"<<"";
    for(--ss;ss>=0;ss--){
        cout<<ls[a[ss]-1].addrname<<"";
        cout<<"->";
    }
    cout<<e<<endl;
    cout<<"Input any key to return....."<<endl;
    getchar();
}
