#include <iostream>
#include<memory>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include"hafuman.h"
using namespace std;
void menu(){

    cout<<"请输入"<<endl;
}
int main(int argv,char* argc[])
{   
    char file[20];
    strcpy(file,"file.czip");
    if(argv!=2){
        cout<<"input the right"<<endl;
    }
    vector<times>ss;
    vector<shared_ptr<hafuman>>ls; 
    hafuman::init(ls,argc[1]);
    times::getNum(ss,ls);
    times::decode(ss);
    times::zip(ss,ls,argc[1]);
    times::unczip(ss,ls);
    return 0;
}

void hafuman::recordInfo(vector<shared_ptr<hafuman>>&ls,string info){

    int i =0;
    int flag =0;
    for(i =0 ;i<(int)ls.size();i++){
        if(ls[i]->infos==info){
            flag = 1;
            ls[i]->count++;
        }
    }
    if(flag ==0){
        shared_ptr<hafuman>p(new hafuman());
        p->infos = info ;
        p->count++;
        p->index =counts++;
        ls.push_back(p);
    }

}

void hafuman::init(vector<shared_ptr<hafuman>>&ls,char*filename){
    FILE *fp ;
    fp = fopen(filename,"r");
    if(fp==NULL){

        cout<<"open error!"<<endl;
        exit(1);
    }
    string info ;
    char ch ;
    int count =0;
    unsigned char hh ;
    string strs ;
    while((ch = fgetc(fp))!=EOF){
            hh = ch ;
            if(count==3){
                recordInfo(ls,info);
                info="";
                count=0;
            }
            if(hh>128){              
                info+=ch;
                count++;
            }
            else{
                info+=hh ;
                recordInfo(ls,info);
                info ="";
            }
    }
    fclose(fp); 
}

string times::codes(vector<times>&ss,int index){
    string str1="" ;
    for(int i =0 ;i<(int)ss[index].code.size();i++){
        str1+=ss[index].code[i];
    }

    return str1;
}

string times::getcode(vector<times>&ss,vector<shared_ptr<hafuman>>&ls, string info){
        string str1;
        int i =0;
        int flag=0;
        for(i=0;i<(int)ls.size();i++){
            if(ls[i]->infos==info){
                flag =1;
                str1=codes(ss,ls[i]->index);
                break;
            }
        }
        if(flag==0){
            cout<<"getcode error!"<<endl;
            exit(-1);
        }
        return str1;
}

void times::reserve(vector<char>&ss){

    
    int i =0 ;
    
    int ch ;
    vector<char>::reverse_iterator it;
    for(it=ss.rbegin();it!=ss.rend();it++){
        ch=*it;
        *it = ss[i];
        ss[i]=ch;
        i++;
        if(i==ss.size()/2){
            break;
        }
    }

}
void times::getNum(vector<times>&ss,vector<shared_ptr<hafuman>>&ls){
    
    int i =0 ;
    count =(int)ls.size();
    for(i =0 ;i<(int)ls.size();i++){
        times p ;
        p._time = ls[i]->count;
        //cout<<ls[i]->count<<endl;
        p.index = ls[i]->index;
        ss.push_back(p);
    }
    for(i=0;i<(int)ss.size();i++){
        int kl=-1,kr=-1 ;
        getIndex(kl,kr,ss);
        times pp ;
        if(kr==-1){
            break;
        }
        pp._time = ss[kl]._time+ss[kr]._time;
        pp.l = kl;
        pp.r = kr;
        ss[kl].p=(int)ss.size();
        ss[kr].p=(int)ss.size();
        pp.index = (int)ss.size();
        ss.push_back(pp);
    }
}


void times::getIndex(int &kl,int&kr,vector<times>&ss){
    
    int min ;
    int i =0,j;
    int flag =0;
    for(i=0;i<2;i++){
        min =35575 ;
        for(j=0;j<(int)ss.size();j++){
            if(flag==0&&min>ss[j]._time&&ss[j].tag==0){
                min = ss[j]._time;
                kl = j;
            }
            if(flag==1&&min>ss[j]._time&&ss[j].tag==0){
                min = ss[j]._time;
                kr = j;
            }
        }
        if(flag==0){
            ss[kl].tag = 1 ;
            flag =1 ;
        }
        if(kr!=-1){
             ss[kr].tag = 1;
             break;
        }
    }
    if(kr!=-1&&kl!=-1&&kl>kr){
        int tmp;
        tmp = kl ;
        kl =kr ;
        kr = tmp;
    }
}

void times::decode(vector<times>&ss){

   int i ;
   int len=count;
   for(i=0;i<len;i++) {
        
        makeCode(ss,i);
        reserve(ss[i].code);
    }
}

void times::zip(vector<times>&ss,vector<shared_ptr<hafuman>>&ls,char *filename){
        
    FILE*fz,*fp ;
    fz = fopen("file.czip","wb+");
    if(fz==NULL){
        cout<<"can.t write"<<endl;
        return ;
    }
    fp = fopen(filename,"r");
    if(fp==NULL){
        cout<<"can.t write"<<endl;
        return ;
    }
    char ch1,ch2='\0';
    char arr[8];
    unsigned char cc;
    int cs=0;
    int i=0;
    string  code;
    string info = "";
    int len =0;
    while(1){
        if((ch2=getc(fp))==EOF){
            if(len!=8){
                more=len;
                ch1 = (arr[0]-48)*128+(arr[1]-48)*64+(arr[2]-48)*32+(arr[3]-48)*16+(arr[4]-48)*8+(arr[5]-48)*4+(arr[6]-48)*2+(arr[7]-48)*1;
                fputc(ch1,fz);
                break;
            }else{
                filelongs++;
                ch1 = (arr[0]-48)*128+(arr[1]-48)*64+(arr[2]-48)*32+(arr[3]-48)*16+(arr[4]-48)*8+(arr[5]-48)*4+(arr[6]-48)*2+(arr[7]-48)*1;
                fputc(ch1,fz);
                break;
            }
        }
        cc = ch2;
        if(cs==3){
            code=getcode(ss,ls,info);
            for(i=0;i<(int)code.length();i++){
                if(len<8){
                    arr[len]=code[i];
                    len++;
                }
                else{
                    filelongs++;
                    ch1 = (arr[0]-48)*128+(arr[1]-48)*64+(arr[2]-48)*32+(arr[3]-48)*16+(arr[4]-48)*8+(arr[5]-48)*4+(arr[6]-48)*2+(arr[7]-48)*1;
                    fputc(ch1,fz);
                    ch1 = '\0';
                    len=0;
                    bzero(arr,sizeof(arr));
                    arr[len]=code[i];
                    len++;
                }
            }
                info="";
                cs = 0;
        }
        if(cc>128){
            info+=ch2;
            cs++;
        }
        else{
            info+=ch2;
            code=getcode(ss,ls,info);
            
            for(i=0;i<(int)code.length();i++){
                if(len<8){
                    arr[len]=code[i];
                    len++;
                }
                else{
                    filelongs++;
                    ch1 = (arr[0]-48)*128+(arr[1]-48)*64+(arr[2]-48)*32+(arr[3]-48)*16+(arr[4]-48)*8+(arr[5]-48)*4+(arr[6]-48)*2+(arr[7]-48)*1;
                    fputc(ch1,fz);
                    ch1 = '\0';
                    len=0;
                    bzero(arr,sizeof(arr));
                    arr[len]=code[i];
                    len++;
                }
            }
            info="";
        }
    }
    fclose(fp);
    fclose(fz);
}
void times::makeCode(vector<times>&ss,int indexs){
    int pp = ss[indexs].p;
    int qq;
    int index1 = indexs;
    while(pp!=0){
        if(indexs == ss[pp].l){
            char ch;
            ch ='0';
            ss[index1].code.push_back(ch);
        }
        if(indexs == ss[pp].r){
            char ch ='1';
            ss[index1].code.push_back(ch);
        }   
        qq = indexs;
        indexs = ss[indexs].p;
        pp = ss[indexs].p;
    }
}

int times::getBit(unsigned char ch,int &i,int &flag){
    unsigned char ch1[8]={128,64,32,16,8,4,2,1};
    if(ch&ch1[i]){
        i++;
        if(i==8)flag=1;
        return 1;
    }
    else{
        i++;
        if(i==8)flag=1;
        return 0;
    }
}

void times::unczip(vector<times>&ss,vector<shared_ptr<hafuman>>&ls){
    static unsigned char cc;
    static int j =0;
    int flag =0;
    int tag=0;
    int len= filelongs*8+more;
    char fp1[20]="file.czip";
    char fp2[20]="file.unczip";
    FILE *fpB,*fpC; 
    fpB =fopen(fp1,"rb");
    fpC =fopen(fp2,"w") ;
    int a = (int)ss.size()-1;
    cc= fgetc(fpB);
    for(int i =1;i<filelongs+1;i++){
       if(tag==-1)break;
       if(j==8){
        tag=0;
         j=0;
         cc= fgetc(fpB);
       }
       else{
           i--;
       }
       while(ss[a].r!=0){
           flag =getBit(cc,j,tag);
            if(flag==1){
                len--;
                a =ss[a].r; 
            }
            else{
                len--;
                a = ss[a].l;
            }
            if(tag==1){
                break;
            }
            if(len==1){
                tag=-1;
            }
       }
       if(tag==1||tag==-1)continue;
        const char* str1 =(ls[ss[a].index]->infos).data(); 
        a = (int)ss.size()-1;
        fputs(str1,fpC);
    }
    fclose(fpB);
    fclose(fpC);
}

