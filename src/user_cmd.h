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

class TestCmd : public CommonNs::Cmd {
public:
         TestCmd(const char * const name);
         ~TestCmd();

    bool exec(int argc, char **argv);
};

class Graph{
public:
    Graph(int** tmp,int i);
    int getlength(){return length;}
    int getColor(int i){return color[i];}
    int getPre(int i){return pre[i];}
    int getDisTime(int i){return disTime[i];}
    int getFinTime(int i){return finTime[i];}
    int getMatrix(int i,int j){return matrix[i][j];}

	void setColor(int i,int x){color[i]=x;}
    void setPre(int i,int x){pre[i]=x;}
    void setDisTime(int i,int x){disTime[i]=x;}
    void setFinTime(int i,int x){finTime[i]=x;}
    void setMatrix(int i,int j,int x){matrix[i][j]=x;}

    map<int,int> sucMap;
    map<int,int> finTimeMap;

private:
    int* color;
    int* pre;
    int* disTime;
    int* finTime;
	int** matrix;
    int length;
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
    void DFS_VISIT(int i,int time);
};

#endif

