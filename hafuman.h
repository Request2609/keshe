#pragma once
#include<string>
#include<memory>
#include<vector>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/stat.h>
#include<iterator>
#include<unistd.h>
using namespace std;
class hafuman;
typedef struct node{
    vector<char>s;
    string a;
}_node;
class times{
public:
    int tag;
    int r,l,p;
    int _time ;
    int index;
    static int more;
    static int filelongs;
    static int count;
    vector<char>code;
    times(){
        l =0 ;
        p =0 ;
        r =0 ;
        index=0 ;
        tag =0;
        _time = 0;
    }
    static void getNum(vector<times>&ss,vector<shared_ptr<hafuman>>&ls);
    static void decode(vector<times>&ss);
    static void getIndex(int &kl,int&kr,vector<times>&ss);
    static void makeCode(vector<times>&ss,int index);
    static void reserve(vector<char>&ss);
    static void zip(vector<times>&ss,vector<shared_ptr<hafuman>>&ls,char *filename);
    static string getcode(vector<times>&ss,vector<shared_ptr<hafuman>>&ls, string info);
    static string codes(vector<times>&ss,int index);
    static void unczip(vector<times>&ss,vector<shared_ptr<hafuman>>&ls);
    static int getBit(unsigned char ch,int &i,int &flag);
};
int times::count = 0;
int times::more =0;
int times::filelongs =0;
class hafuman:public times
{
public:
    static int counts;
    int index;
    string infos;
    int count;
    hafuman() {
        index = 0;
        infos ="";
    }
    ~hafuman() {}
    static void init(vector<shared_ptr<hafuman>>&ls,char*filename);
    static void recordInfo(vector<shared_ptr<hafuman>>&ls,string info);
    static void decode(vector<shared_ptr<hafuman>>&ls);
};
int hafuman::counts =0;
