#pragma once
#include <stdio.h> 
#include <termios.h>  
#include<stdarg.h>
#include<string.h>
#include <unistd.h> 
#include<string.h>
#include <errno.h>
#include <iostream>
#include<vector>
#include<memory>
#include<string>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<stdio.h>
#include"md5.h"
#define LENGTH 6 
#define VIEW 60
#define GREEN 600
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)  //函数set_disp_mode用于控制是否开启输入回显功能  //如果option为0，则关闭回显，为1则打开回显  
#define ADMIN 0
#define USER 1
#define N 100
using namespace std;
class person{
private:
    string name;
    string password;
public:
    int weight;
    int tag ;
    person(){
        tag =0;
        name="";
        password="";
    }
    ~person(){}
    void regist();
    person  login();
    void setname(string name);
    void set_disp_mode(int fd,int option);
    void getpasswd(char*passwd,int size);
    string getpass();
    string getname();
    void setpass(string pass);
};
class mapnode;
class mapedge{

public:
    static int view[N][N];
    static int leng[N][N];
    static int green[N][N];
    int x ,y;
    int view_weight,length_weight,green_weight;
    mapedge(){
        view_weight = 0;
        length_weight = 0;
        green_weight = 0;
    }
    ~mapedge(){}
    static void saveedge(FILE *fp,const vector<mapedge>ss);
    static void initedge(vector<mapedge>&ss,int len);
    static void testprint(int len);
    static int addedge(mapedge q,vector<mapnode>&ls,vector<mapedge>&ss);
    static void deleteedge(mapnode q,mapedge ee,vector<mapnode>&ss,vector<mapedge>&ls);
    static void modify(mapedge p,vector<mapedge>&ss);
};  
class mapnode:public mapedge{

public:
    static int want;
    static int previous[N];
    /*static int previous_view[N];
    static int previous_green[N];*/
    static int map1[N][N];
    static int dist[N];
    static int dist_view[N];
    static int dist_green[N];
    static int tag[N];
 /*   static int tag_view[N];
    static int tag_green[N];*/
    string addrname ;
    int id;
    string info;
    vector<int>ss;
    mapnode(){
        info="";
        addrname = "";
    }
    ~mapnode(){
    }
    static void initinfo(const char * addfile);
    static int getindex(vector<mapnode>&ss,string str1);
    static void savenode(FILE *fp,const vector<mapnode>s);
    static void search(string s,vector<mapnode>&ls,vector<mapedge>&ss);
    static void initnode(vector<mapnode>ls);
    static void testprint(vector<mapnode>&s,vector<mapedge>&ss);
    static void superway(vector<mapnode>ls);
    static void printway(vector<mapnode>ls,string s);
    //static void mapprint(int len,vector<mapnode>&s);
    static void update(vector<mapnode>&ss,vector<mapedge>&ls);
};
/*
int mapnode::tag_view[N]={0};
int mapnode::tag_green[N]={0};*/
int mapnode::dist_view[N]={0};
int mapnode::dist_green[N]={0};
/*int mapnode::previous_view[N]={0};
int mapnode::previous_green[N]={0};*/
int mapedge::green[N][N]={{0}};
int mapedge::view[N][N]={{0}};
int mapedge::leng[N][N]={{0}};
int mapnode::tag[N]={0};
int mapnode::dist[N]={0};
int mapnode::map1[N][N]={{0}};
int mapnode::previous[N] = {0};
int mapnode::want =6;
void person::set_disp_mode(int fd,int option) {
    int err; struct termios term; 
    if(tcgetattr(fd,&term)==-1){ 
        perror("Cannot get the attribution of the terminal"); 
        return ; 
    } 
    if(option) term.c_lflag|=ECHOFLAGS;
    else term.c_lflag &=~ECHOFLAGS; 
    err=tcsetattr(fd,TCSAFLUSH,&term); 
    if(err==-1 && err==EINTR){
        perror("Cannot set the attribution of the terminal");
        return ; 
    } 
    return ;
} //函数getpasswd用于获得用户输入的密码，并将其存储在指定的字符数组中 
void person::getpasswd(char* passwd, int size) {
    int c; 
    int n = 0;
    do{ c=getchar();
        if (c != '\n'|c!='\r'){ 
            passwd[n++] = c; 
        } 
    }while(c != '\n' && c !='\r' && n < (size - 1));
    passwd[n] = '\0'; 
    return;
} 
string person::getpass(){
    char password[N];
    bzero(password,sizeof(password));
    char* p; 
    set_disp_mode(STDIN_FILENO,0); 
    getpasswd(password, sizeof(password)); 
    p=password; 
    while(*p!='\n') 
         p++; 
    *p='\0'; 
    set_disp_mode(STDIN_FILENO,1);
    string a;
    a=  password;
    return a;
}

