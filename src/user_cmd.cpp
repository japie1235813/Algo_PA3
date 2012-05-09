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
#include <list>
#include <map>
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

Graph::Graph(int** tmp,int i){
    matrix = tmp;
    length = i;
    color = new int[length];
    pre = new int[length];
    disTime = new int[length];
    finTime = new int[length];
    for(int j=0;j<length;j++){
        color[j] = -1;
        pre[j] = -1;
        disTime[j] = -1;
        finTime[j] = -1;
    }
    cout << "In class Graph constructor" <<endl;
    for(int k = 0 ; k<length; k++){
        for(int j = 0 ; j<length ; j++)
            cout << matrix[k][j] << " ";
        cout <<endl;
    }    
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
    cout << "lalala" <<endl;
    for(int i = 0 ; i<vertexNum; i++){
        for(int j = 0 ; j<vertexNum ; j++)
            cout << matrix[i][j] << " ";
        cout <<endl;
    }

    graph = new Graph(matrix,vertexNum);

    return true;
}

WriteDfsCmd::WriteDfsCmd(const char * const name) : Cmd(name) {
    optMgr_.setShortDes("Perform depth first search starting from source node.  Then write to a dot file.");
    optMgr_.setDes("test");

    Opt *opt = new Opt(Opt::BOOL, "print usage", "");
    opt->addFlag("h");
    opt->addFlag("help");
    optMgr_.regOpt(opt);

    opt = new Opt(Opt::STR_REQ, "", "<sourcenode>");
    opt->addFlag("s");
    optMgr_.regOpt(opt);

    opt = new Opt(Opt::STR_REQ, "", "<dot_filename>");
    opt->addFlag("o");
    optMgr_.regOpt(opt);
}

WriteDfsCmd::~WriteDfsCmd() {}

bool WriteDfsCmd::exec(int argc, char **argv) {
    optMgr_.parse(argc, argv);

    if (optMgr_.getParsedOpt("h")) {
        optMgr_.usage();
        return true;
    }

    int sourcenode;
    ofstream outFile;
    string tmp;
    // try{
    if (optMgr_.getParsedOpt("s")) {
        cout << "sourcenode: " << optMgr_.getParsedValue("s") <<endl;
        tmp = optMgr_.getParsedValue("s");
        sourcenode = atoi(tmp.substr(1).c_str());
    }
    if (optMgr_.getParsedOpt("o")) {
        cout << optMgr_.getParsedValue("o") <<endl;
        outFile.open(optMgr_.getParsedValue("o"));
    }
    outFile << "graph gn" << graph->getlength() << "_dfs {" << endl;
    // }catch(string e){
    //     cout << "lack sth!: " << e << endl;
    //     return false;
    // }

    //========dfs 
    //(white,gray,black)==(-1,0,1)
    // for(int i=0;i<graph->getlength();i++){
    //     graph->setColor(i,0);
    //     graph->setPre(i,-1); //nil
    // }

    int time = 0;

    //didn't consider source....
    for(int j=0;j<graph->getlength();j++)
        if((graph->getMatrix(sourcenode,j)!=0)&&(graph->getColor(j) == -1))
            DFS_VISIT(sourcenode,time);


    for(int i=0;i<graph->getlength();i++){
        cout<<graph->getPre(i) << " " <<endl;
    }


    //========print out
    list<int> finTimeList;
    for(int j=0;j<graph->getlength();j++){
        finTimeList.push_back(graph->getFinTime(j));
        graph->finTimeMap[graph->getFinTime(j)] = j;
    }
    finTimeList.sort();
    list<int>::iterator it=finTimeList.begin();
    cout << *it <<" ";
    it++;
    for(;it!=finTimeList.end();it++){
        int suc = graph->finTimeMap[*it];
        int pre = graph->getPre(suc);
        cout << "(pre,suc): " << pre << " " << suc << endl;
        outFile << "v" << pre << " -- v" << suc ;
        //pre == -1 ??sourcenode....
        outFile << " [label = " << graph->getMatrix(pre,suc) << "];" << endl;
    }



    // print first
    // it = finTimeList.begin();
    // int suc = graph->finTimeMap[*it];
    // int pre = graph->getPre(suc);
    // outFile << "v" << pre << " -- v" << suc ;
    // outFile << " [label = " << graph->getMatrix(pre,suc) << "];" << endl;

    outFile << "}";
    outFile.close();
    return true;
}

void WriteDfsCmd::DFS_VISIT(int i,int time){
    cout << endl;
    cout << "i: " << i <<endl;
    time+=1;
    graph->setDisTime(i,time);
    graph->setColor(i,0); //color:gray

    list<int> vertexlist;
    for(int j=0;j<graph->getlength();j++){
        cout << "getM(i,j): " << graph->getMatrix(i,j) <<endl;
        cout << "getM(j,i): " << graph->getMatrix(j,i) <<endl;
        if(graph->getColor(j) == -1){ //color:white
            if(graph->getMatrix(i,j)!=0){
                vertexlist.push_back(graph->getMatrix(i,j));                    
                graph->sucMap[graph->getMatrix(i,j)] = j;
            }
            else if(graph->getMatrix(j,i)!=0){
                vertexlist.push_back(graph->getMatrix(j,i));             
                graph->sucMap[graph->getMatrix(j,i)] = j;
            }
            graph->setPre(j,i);
            cout << "graph->setPre(j,i): " << j <<" "<< i << endl;
        }
    }
    vertexlist.sort();
    for(list<int>::iterator it = vertexlist.begin();it!=vertexlist.end();it++)
        DFS_VISIT(graph->sucMap[*it],time);
    graph->setColor(i,1);
    time += 1;
    graph->setFinTime(i,time);
}