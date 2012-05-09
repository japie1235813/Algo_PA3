// **************************************************************************
// File       [ test_cmd.cpp ]
// Author     [ littleshamoo ]
// Synopsis   [ ]
// Date       [ 2012/04/10 created ]
// **************************************************************************

#include "user_cmd.h"
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace CommonNs;

Graph *graph;

TestCmd::TestCmd(const char * const name) : Cmd(name) {
    optMgr_.setShortDes("test");
    optMgr_.setDes("test");

    Opt *opt = new Opt(Opt::BOOL, "print usage", "");
    opt->addFlag("h");
    opt->addFlag("help");
    optMgr_.regOpt(opt);

    opt = new Opt(Opt::STR_REQ, "print the string of -s", "[string]");
    opt->addFlag("s");
    optMgr_.regOpt(opt);
}

TestCmd::~TestCmd() {}

bool TestCmd::exec(int argc, char **argv) {
    optMgr_.parse(argc, argv);

    if (optMgr_.getParsedOpt("h")) {
        optMgr_.usage();
        return true;
    }

    if (optMgr_.getParsedOpt("s")) {
        printf("%s\n", optMgr_.getParsedValue("s"));
        return true;
    }
    else
        printf("hello world !!\n");


    return true;
}


ReadCmd::ReadCmd(const char * const name) : Cmd(name) {    
    optMgr_.setShortDes("read the graph in dot format");
    optMgr_.setDes("Read the graph in dot format");

    Opt *opt = new Opt(Opt::BOOL, "print usage", "");
    opt->addFlag("h");
    opt->addFlag("help");
    optMgr_.regOpt(opt);

    opt = new Opt(Opt::STR_REQ, "Read the graph in dot format", "<dot_filename>");
    //opt->addFlag("");   //if not add wouldn't appear upon ??
    optMgr_.regOpt(opt);
}


ReadCmd::~ReadCmd() {}

bool ReadCmd::exec(int argc, char **argv) {
    optMgr_.parse(argc, argv);

    if (optMgr_.getParsedOpt("h")) {
        optMgr_.usage();
        return true;
    }

    char buf[256];

    string tmp = "";
    int vertexNum = -1;
    int pre = -1 ,suc = -1;
    ifstream inFile(argv[1],ios::in);
    inFile >> tmp >> tmp ;
    // cout << "tmp:" << tmp << endl;
    vertexNum = atoi(tmp.substr(2).c_str());
    // cout << "vertexNum: " << vertexNum <<endl;
    int** matrix = new int*[vertexNum];    
    for(int i=0;i<vertexNum;i++)
        matrix[i] = new int[vertexNum];

    inFile >> tmp;
    while(1){
        inFile >> tmp ;
        if(strcmp(tmp.c_str(),"}")==0) break;
        pre = atoi(tmp.substr(1).c_str());
        inFile >> tmp >> tmp;
        // cout << "tmp: " << tmp << endl;
        suc = atoi(tmp.substr(1).c_str());
        cout << "(pre,suc) : " << pre <<" " << suc <<endl;
        inFile.getline(buf,256);
        // cout << "buf: " << buf << endl;
        string str(buf);
        int pos = str.find_first_of("\"");
        int last = str.find_last_of("\"");
        // cout << "str.sub: " << str.substr(pos+1,last-pos-1) << endl;
        matrix[pre][suc] = atoi(str.substr(pos+1,last-pos-1).c_str());
    }
    // cout << "lalala" <<endl;
    // for(int i = 0 ; i<vertexNum; i++){
    //     for(int j = 0 ; j<vertexNum ; j++)
    //         cout << matrix[i][j] << " ";
    //     cout <<endl;
    // }

    graph = new Graph(matrix,vertexNum);

    return true;
}

