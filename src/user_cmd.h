// **************************************************************************
// File       [ test_cmd.h ]
// Author     [ littleshamoo ]
// Synopsis   [ ]
// Date       [ 2012/04/10 created ]
// **************************************************************************

#ifndef _TEST_CMD_H_
#define _TEST_CMD_H_

#include "../lib/cmd.h"

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

    int* color;
    int* pre;
    int* disTime;
    int* finTime;
	int** matrix;
private:
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

