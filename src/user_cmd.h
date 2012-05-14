// **************************************************************************
// File       [ test_cmd.h ]
// Author     [ littleshamoo ]
// Synopsis   [ ]
// Date       [ 2012/04/10 created ]
// **************************************************************************

#ifndef _TEST_CMD_H_
#define _TEST_CMD_H_

#include <map>
#include <iostream>
#include "../lib/cmd.h"
using namespace std;
typedef pair<int*,int> Node;

class TestCmd : public CommonNs::Cmd {
public:
         TestCmd(const char * const name);
         ~TestCmd();

    bool exec(int argc, char **argv);
};

class Graph{
public:
    Graph(int** tmp,int i);
    void reset();

    int getlength(){return length;}
    int getColor(int i){return color[i];}
    int getPre(int i){return pre[i];}
    int getDisTime(int i){return disTime[i];}
    int getFinTime(int i){return finTime[i];}
    int getMatrix(int i,int j){return matrix[i][j];}
    int* getKey(int i){return &key[i];}

	void setColor(int i,int x){color[i]=x;}
    void setPre(int i,int x){pre[i]=x;}
    void setDisTime(int i,int x){disTime[i]=x;}
    void setFinTime(int i,int x){finTime[i]=x;}
    void setMatrix(int i,int j,int x){matrix[i][j]=x;}
    void setKey(int i,int x){key[i]=x;}

    map<int,int> sucMap;
    map<int,int> finTimeMap;
    map<Node,int> pqMap;

private:
    int* color;
    int* pre;
    int* disTime;
    int* finTime;
	int** matrix;
    int length;
    int* key;
};

class ReadCmd : public CommonNs::Cmd {
public:
         ReadCmd(const char * const name);
         ~ReadCmd();

    bool exec(int argc, char **argv);
};

class WriteDfsCmd : public CommonNs::Cmd {
public:
         WriteDfsCmd(const char * const name);
         ~WriteDfsCmd();

    bool exec(int argc, char **argv);
    void DFS_VISIT(int i,int& time);    
};

class WriteBfsCmd : public CommonNs::Cmd {
public:
         WriteBfsCmd(const char * const name);
         ~WriteBfsCmd();

    bool exec(int argc, char **argv);
    
};

class WriteMstCmd : public CommonNs::Cmd {
public:
         WriteMstCmd(const char * const name);
         ~WriteMstCmd();

    bool exec(int argc, char **argv);
    void HeapDecreaseKey(vector<Node>& v,int i,int key);
    
};

class IsSpanningTreeCmd : public CommonNs::Cmd {
public:
         IsSpanningTreeCmd(const char * const name);
         ~IsSpanningTreeCmd();

    bool exec(int argc, char **argv);    
};

#endif

