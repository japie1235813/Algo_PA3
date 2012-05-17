// **************************************************************************
// File       [ test_cmd.cpp ]
// Author     [ littleshamoo ]
// Synopsis   [ ]
// Date       [ 2012/04/10 created ]
// **************************************************************************
#include "tm_usage.h"
#include "user_cmd.h"
#include "stdio.h"
#include <cassert>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
using namespace CommonNs;

Graph *graph;
extern TmUsage tmusg;

#define NIL     -1
#define WHITE   -1
#define GRAY    0
#define BLACK   1
#define INF     1e9

#define PARENT(x) (((x)+1)/2-1)

typedef pair<int*,int> Node;
typedef pair<int,int> Vertex;

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
    key = new int[length];

    // cout << "In class Graph constructor" <<endl;
    // for(int k = 0 ; k<length; k++){
    //     for(int j = 0 ; j<length ; j++)
    //         cout << matrix[k][j] << " ";
    //     cout <<endl;
    // }
}

void
Graph::reset(){
    for(int j=0;j<length;j++){
        color[j] = WHITE;
        pre[j] = NIL;
        disTime[j] = -1;
        finTime[j] = -1;
        key[j] = INF;
    }
}


//================ read

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
    // tmusg.periodStart();

    optMgr_.parse(argc, argv);

    if (optMgr_.getParsedOpt("h")) {
        optMgr_.usage();
        return true;
    }

    string tmp = "";
    int vertexNum = -1;
    int pre = -1 ,suc = -1;
    ifstream inFile(argv[1],ios::in);
    char buf[256];
    while(1){
        inFile.getline(buf,256);
        // cout << "tmp2:" << buf << endl;
        if(buf[0] != '/' && buf[1] != '/') break;
    }

    tmp = buf;
    vertexNum = atoi(tmp.substr(8).c_str());
    // cout << "vertexNum: " << vertexNum <<endl;
    int** matrix = new int*[vertexNum];
    for(int i=0;i<vertexNum;i++)
        matrix[i] = new int[vertexNum];

    for(int i=0;i<vertexNum;i++)
        for(int j=0;j<vertexNum;j++)
            matrix[i][j] = NIL;

    // inFile >> tmp;
    // cout << "tmp0: " << tmp << endl;
    while(1){
        inFile >> tmp ;
        // cout << "tmp1: " << tmp << endl;
        if(strcmp(tmp.c_str(),"}")==0) break;
        pre = atoi(tmp.substr(1).c_str());
        inFile >> tmp >> tmp;
        // cout << "tmp2: " << tmp << endl;
        suc = atoi(tmp.substr(1).c_str());
        // cout << "(pre,suc) : " << pre <<" " << suc <<endl;
        inFile.getline(buf,256);
        // cout << "buf: " << buf << endl;
        string str(buf);
        int pos = str.find_first_of("\"");
        int last = str.find_last_of("\"");
        // cout << "str.sub: " << str.substr(pos+1,last-pos-1) << endl;
        matrix[pre][suc] = atoi(str.substr(pos+1,last-pos-1).c_str());
        // cout << "matrix["<<pre<<"]["<<suc<<"] = "<<atoi(str.substr(pos+1,last-pos-1).c_str())<<endl;
    }
    // cout << "lalala" <<endl;
    // for(int i = 0 ; i<vertexNum; i++){
    //     for(int j = 0 ; j<vertexNum ; j++)
    //         cout << matrix[i][j] << " ";
    //     cout <<endl;
    // }

    graph = new Graph(matrix,vertexNum);

    inFile.close();

    // TmStat stat;
    // tmusg.getPeriodUsage(stat);
    // cout << argv[0] << " " << argv[1] << endl;
    // cout << stat.uTime / 1000.0 << "s" << endl; // print period user time

    return true;
}

//================dfs

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
    tmusg.periodStart();
    graph->reset();
    optMgr_.parse(argc, argv);

    if (argc < 5) {
        fprintf(stderr, "**ERROR SysSetCmd::exec(): ");
        fprintf(stderr, "variable and value needed\n");
        return false;
    }

    if (optMgr_.getParsedOpt("h")) {
        optMgr_.usage();
        return true;
    }

    int sourcenode;
    ofstream outFile;
    string tmp;

    if (optMgr_.getParsedOpt("s")) {
        tmp = optMgr_.getParsedValue("s");
        sourcenode = atoi(tmp.substr(1).c_str());
    }
    if (optMgr_.getParsedOpt("o")) {
        outFile.open(optMgr_.getParsedValue("o"));
    }


    outFile << "graph gn" << graph->getlength() << "_dfs {" << endl;

    //==============================
    //dfs
    int time = 0;
    DFS_VISIT(sourcenode,time);
    time++;
    for(int j=0;j<graph->getlength();j++)
        if((graph->getMatrix(sourcenode,j)!=NIL || graph->getMatrix(j,sourcenode)!=NIL)&&(graph->getColor(j) == -1)){
            DFS_VISIT(j,time);
            cout <<"return!! 0.0" << endl;
        }


    for(int i=0;i<graph->getlength();i++){
        cout<<graph->getPre(i) << " " <<endl;
    }


    //==============================
    //print out

    list<int> finTimeList;
    for(int j=0;j<graph->getlength();j++){
        // cout << j << " FinTime: " << graph->getFinTime(j) <<endl;
        finTimeList.push_back(graph->getFinTime(j));
        graph->finTimeMap[graph->getFinTime(j)] = j;
    }
    finTimeList.sort();
    int weight = 0;

    list<int>::iterator it=finTimeList.end();
    it--;
    for(;;it--){
        int suc = graph->finTimeMap[*it];
        int pre = graph->getPre(suc);
        if(pre!=-1){
            // cout << "(pre,suc): " << pre << " " << suc << endl;
            outFile << "v" << pre << " -- v" << suc ;
            if(graph->getMatrix(pre,suc)!=NIL){
                outFile << " [label = \"" << graph->getMatrix(pre,suc) << "\"];" << endl;
                weight += graph->getMatrix(pre,suc);
            }
            else{
                outFile << " [label = \"" << graph->getMatrix(suc,pre) << "\"];" << endl;
                weight += graph->getMatrix(suc,pre);
            }
        }
        if(it==finTimeList.begin()) break;
    }

    outFile << "}"<<endl;

    outFile << "// vertices = " << graph->getlength() << endl;
    outFile << "// edges = " << graph->getlength()-1 << endl;
    outFile << "// total_weight = "<< weight << endl;

    TmStat stat;
    tmusg.getPeriodUsage(stat);
    // cout << argv[0] << " " << argv[1] << " " << argv[2] << endl;
    outFile << "// runtime = " << stat.uTime / 1000.0 << "sec" << endl; // print period user time
    // tmusg.getTotalUsage(stat);
    // cout << stat.vmSize / 1024.0 << "MB" << endl; // print current memory
    outFile << "// memory = " << stat.vmPeak / 1024.0 << "MB" << endl; // print peak memory
    cout << endl;

    outFile.close();
    return true;
}

void WriteDfsCmd::DFS_VISIT(int i,int& time){
    cout << endl;
    cout << "i: " << i <<endl;
    time+=1;
    graph->setDisTime(i,time);
    graph->setColor(i,0); //color:gray
    list<int> vertexlist;
    for(int j=0;j<graph->getlength();j++){
        if( graph->getColor(j) == WHITE){ //color:white
            if(graph->getMatrix(i,j)!=NIL){
                vertexlist.push_back(j);
                graph->sucMap[j] = graph->getMatrix(i,j);
                graph->setPre(j,i);
            }
            else if(graph->getMatrix(j,i)!=NIL){
                vertexlist.push_back(j);
                graph->sucMap[j] = graph->getMatrix(j,i);
                graph->setPre(j,i);
            }
        }
    }
    vertexlist.sort();
    // cout << "! vertexlist.sort(): " <<endl;
    // for(list<int>::iterator it = vertexlist.begin();it!=vertexlist.end();it++)
    //     cout << *it << " ";

    cout << endl;
    for(list<int>::iterator it = vertexlist.begin();it!=vertexlist.end();it++){
        // cout << i << ": go to: " << *it << endl;
        DFS_VISIT(*it,time);
    }

    graph->setColor(i,BLACK);
    time += 1;
    // if(!vertexlist.empty() ){
    if(graph->getFinTime(i)==-1){
        // cout << "graph->setFinTime("<<i<<","<<time<<")"<<endl;
        graph->setFinTime(i,time);
    }
}

//================

WriteBfsCmd::WriteBfsCmd(const char * const name) : Cmd(name) {
    optMgr_.setShortDes("Perform breadth first search starting from source node.  Then write to a dot file.");
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

WriteBfsCmd::~WriteBfsCmd() {}

bool WriteBfsCmd::exec(int argc, char **argv) {
    tmusg.periodStart();
    graph->reset();
    optMgr_.parse(argc, argv);

    if (argc < 5) {
        fprintf(stderr, "**ERROR SysSetCmd::exec(): ");
        fprintf(stderr, "variable and value needed\n");
        return false;
    }

    if (optMgr_.getParsedOpt("h")) {
        optMgr_.usage();
        return true;
    }

    int sourcenode;
    ofstream outFile;
    string tmp;

    if (optMgr_.getParsedOpt("s")) {
        tmp = optMgr_.getParsedValue("s");
        sourcenode = atoi(tmp.substr(1).c_str());
    }
    if (optMgr_.getParsedOpt("o")) {
        outFile.open(optMgr_.getParsedValue("o"));
    }

    outFile << "graph gn" << graph->getlength() << "_bfs {" << endl;


    //=======BFS
    for(int j=0;j<graph->getlength();j++){
        graph->setDisTime(j,INF);
    }
    graph->setColor(sourcenode,0);
    graph->setDisTime(sourcenode,0);

    list<int> queueList;
    queueList.push_back(sourcenode);
    int popNode;
    int time = 0;

    while(!queueList.empty()){
        popNode = queueList.front();
        queueList.pop_front();
        for(int j = 0 ; j < graph->getlength(); j++){
            if( graph->getColor(j) == -1){ //color:white
                if((graph->getMatrix(popNode,j)!=NIL)||(graph->getMatrix(j,popNode)!=NIL)){
                    graph->setColor(j,0);
                    graph->setDisTime(j,++time);
                    // cout << " graph->setPre("<<j<<","<<popNode<<")"<<endl;
                    graph->setPre(j,popNode);
                    queueList.push_back(j);
                }
            }
        }
        graph->setColor(popNode,1);
    }

    //=============================
    //print out
    // cout << "checkout Pre: " <<endl;
    // for(int j=0;j<graph->getlength();j++)
    //     cout << j << ": " << graph->getPre(j) << "  ";


    list<int> disTimeList;
    for(int j=0;j<graph->getlength();j++){
        // cout << j << " DisTime: " << graph->getDisTime(j) <<endl;
        disTimeList.push_back(graph->getDisTime(j));
        graph->finTimeMap[graph->getDisTime(j)] = j;
    }
    disTimeList.sort();

    int weight = 0;
    list<int>::iterator it=disTimeList.begin();
    // it--;
    for(;it!=disTimeList.end();it++){
        int suc = graph->finTimeMap[*it];
        int pre = graph->getPre(suc);
        // cout << "(pre,suc): " << pre << " " << suc << endl;
        if(pre!=-1){
            outFile << "v" << pre << " -- v" << suc ;
            if(graph->getMatrix(pre,suc)!=NIL){
                outFile << " [label = \"" << graph->getMatrix(pre,suc) << "\"];" << endl;
                weight += graph->getMatrix(pre,suc) ;
            }
            else{
                outFile << " [label = \"" << graph->getMatrix(suc,pre) << "\"];" << endl;
                weight += graph->getMatrix(suc,pre) ;
            }
        }
    }

    outFile << "}"<<endl;

    outFile << "// vertices = " << graph->getlength() << endl;
    outFile << "// edges = " << graph->getlength()-1 << endl;
    outFile << "// total_weight = "<< weight << endl;

    TmStat stat;
    tmusg.getPeriodUsage(stat);
    outFile << "// runtime = " << stat.uTime / 1000.0 << "sec" << endl; // print period user time
    // tmusg.getTotalUsage(stat);
    // cout << stat.vmSize / 1024.0 << "MB" << endl; // print current memory
    outFile << "// memory = " << stat.vmPeak / 1024.0 << "MB" << endl; // print peak memory
    // cout << endl;

    outFile.close();

    return true;
}



//================ MST


WriteMstCmd::WriteMstCmd(const char * const name) : Cmd(name) {
    optMgr_.setShortDes("Perform breadth first search starting from source node.  Then write to a dot file.");
    optMgr_.setDes("test");

    Opt *opt = new Opt(Opt::BOOL, "print usage", "");
    opt->addFlag("h");
    opt->addFlag("help");
    optMgr_.regOpt(opt);

    opt = new Opt(Opt::STR_REQ, "", "<rootnode>");
    opt->addFlag("r");
    optMgr_.regOpt(opt);

    opt = new Opt(Opt::STR_REQ, "", "<dot_filename>");
    opt->addFlag("o");
    optMgr_.regOpt(opt);

    opt = new Opt(Opt::STR_REQ, "", "prim");
    opt->addFlag("a");
    optMgr_.regOpt(opt);
}

WriteMstCmd::~WriteMstCmd() {}


class comparison
{
  bool reverse;
public:
  comparison(){}
  bool operator() (const Node& lhs, const Node&rhs) const
  {
    return *(lhs.first)>*(rhs.first);
  }
};

void checkPqMapConsistency(const vector<Node>& pq){
    for(int i=0; i<pq.size(); ++i){
        // cout << "i" << i << endl;
        assert(graph->pqMap[pq[i]] == i);
    }
}

bool WriteMstCmd::exec(int argc, char **argv) {
    tmusg.periodStart();
    optMgr_.parse(argc, argv);
    graph->reset();

    if (argc < 7) {
        fprintf(stderr, "**ERROR SysSetCmd::exec(): ");
        fprintf(stderr, "variable and value needed\n");
        return false;
    }

    if (optMgr_.getParsedOpt("h")) {
        optMgr_.usage();
        return true;
    }

    int sourcenode;
    ofstream outFile;
    string tmp;

    if (optMgr_.getParsedOpt("r")) {
        tmp = optMgr_.getParsedValue("r");
        sourcenode = atoi(tmp.substr(1).c_str());
    }
    if (optMgr_.getParsedOpt("o")) {
        outFile.open(optMgr_.getParsedValue("o"));
    }

    outFile << "graph gn" << graph->getlength() << "_mst_p {" << endl;


    //========MST
    vector<Node> pq;

    //set each node key
    // cout << "graph->getlength(): " << graph->getlength() << endl;
    for(int i=0;i<graph->getlength();i++)
        graph->setKey(i,INF);
    graph->setKey(sourcenode,0);


    //put each vertex into queue
    for(int i=0;i<graph->getlength();i++){
        Node n(graph->getKey(i),i);
        pq.push_back(n);
    }
    // cout << "pq.size():" << pq.size() <<endl;
    make_heap(pq.begin(),pq.end(),comparison());

    for(int i=0;i<graph->getlength();i++){
        graph->pqMap[pq[i]] = i;
    }
    Node popNode;

    //for(vector<Node>::iterator it=pq.begin();it!=pq.end();it++)
    //    cout << *((*it).first) <<" , "<< (*it).second << " | " ;
    //cout << endl;

    int c = 0;
/*
MST-PRIM(G,w,r)
for each u 屬於 G,V
  u.key = INF
  u.pi    = NIL
r.key = 0
Q = G.V
while Q 不等於空集合
  u = EXTRACT-MIN(Q)
        for each v 屬於 G.Adj[u]
            if v 屬於 Q and w(u,v) < v.key
                v.pi = u
                v.key = w(u,v)
*/
    while(1){
        c++;
        popNode = pq.front();

        // cout <<endl <<endl;
        // cout << "popNode: (" << *popNode.first << "," << popNode.second << ") " <<endl;
        // bool success = false;

        for(int j=0;j<graph->getlength();j++){
            int val = max(graph->getMatrix(j,popNode.second),graph->getMatrix(popNode.second,j));
            if( val != NIL){ //j belong to popNode's adj
                //cout << j << ": val: "<<val << " Key: " << *graph->getKey(j) << endl;
                Node n(graph->getKey(j),j)  ;
                //cout << "graph->pqMap.find(n)->second: " << graph->pqMap.find(n)->second << endl;
                int nPos = graph->pqMap.find(n)->second; // node n's position in pq
                if( ( nPos != NIL ) && (val < *graph->getKey(j))){  //v in queue
                // if(val < *graph->getKey(j)){
                    //j in queue and w(j,v) < j.key
                    graph->setPre(j,popNode.second);
                    // graph->setSuc(popNode.second,j);
                    //cout << "graph->setPre("<<popNode.second<<","<<j<<")"<<endl;
                    graph->setKey(j,val);
                    //cout << "graph->setKey("<<j<<","<<val<<")"<<endl;
                    //then increase key <- remeber to modify Map
                    checkPqMapConsistency(pq);
                    HeapDecreaseKey(pq,nPos,val);
                    checkPqMapConsistency(pq);
                }
            }
        }

        if(pq.empty()) break;

        //dequeue
        graph->pqMap[popNode] = NIL; //make popNode black
        
        // cout << "before pop_heap: " << endl;
        // for(vector<Node>::iterator it=pq.begin();it!=pq.end();it++)
        //     cout << *((*it).first) <<" , "<< (*it).second << " | " ;
        // cout << endl;

        pop_heap (pq.begin(),pq.end(),comparison()); 
        
        // cout << "before pop_back: " << endl;
        // for(vector<Node>::iterator it=pq.begin();it!=pq.end();it++)
        //     cout << *((*it).first) <<" , "<< (*it).second << " | " ;
        // cout << endl;

        pq.pop_back();
        
        // cout << "pq.size()" << pq.size() << endl;
        
        for(int i=0; i<pq.size(); ++i){
            graph->pqMap[pq[i]] = i;
        }
        // for(vector<Node>::iterator it=pq.begin();it!=pq.end();it++)
        //     cout << *((*it).first) <<" , "<< (*it).second << " | " ;
        // cout << endl;

    }

    //for(int j=0;j<graph->getlength();j++)
    //    cout << j <<" Pre: " << graph->getPre(j) << endl;


    //=======print out

    int weight = 0;
    for(int i = 0 ;i < graph->getlength() ;i++){
        int pre = graph->getPre(i);
        // cout << "(pre,suc): " << pre << " " << i << endl;
        if(pre!=-1){
            outFile << "v" << pre << " -- v" << i ;
            // cout << "before: " << weight << endl;
            if(graph->getMatrix(pre,i)!=NIL){
                outFile << " [label = \"" << graph->getMatrix(pre,i) << "\"];" << endl;
                weight += graph->getMatrix(pre,i);
            }
            else{
                outFile << " [label = \"" << graph->getMatrix(i,pre) << "\"];" << endl;
                weight += graph->getMatrix(i,pre);
            }
            // cout << "after: " << weight << endl;
        }
    }

    outFile << "}"<<endl;

    outFile << "// vertices = " << graph->getlength() << endl;
    outFile << "// edges = " << graph->getlength()-1 << endl;
    outFile << "// total_weight = "<< weight << endl;

    TmStat stat;
    tmusg.getPeriodUsage(stat);
    // cout << argv[0] << " " << argv[1] << " " << argv[2] << endl;
    outFile << "// runtime = " << stat.uTime / 1000.0 << "sec" << endl; // print period user time
    // tmusg.getTotalUsage(stat);
    // cout << stat.vmSize / 1024.0 << "MB" << endl; // print current memory
    outFile << "// memory = " << stat.vmPeak / 1024.0 << "MB" << endl; // print peak memory
    // cout << endl;

    outFile.close();

    return true;
}

void WriteMstCmd::HeapDecreaseKey(vector<Node>& v,int i,int key){
    // cout << "HeapDecreaseKey("<< i << "," << key << ")" <<endl;
    if(key > *(v[i].first)){
        // cout << "not decrease!"<<endl;
        return;
    }
    // cout << "*(v[<<i].first) = key;" << *(v[i].first) << " = " << key <<endl;
    // *(v[i].first) = key;

    while( i>2 && ( *(v[PARENT(i)].first) > *(v[i].first) ) ){
        // cout << "exchange v[i] w/ v[PARENT(i)]: " <<endl;
        // cout << "*(v[i].first): " << *(v[i].first) << " <-> " << *(v[PARENT(i)].first) << endl;
        // cout << "*(v[i].second): " << v[i].second << " <-> " << v[PARENT(i)].second << endl;
        assert(graph->pqMap[v[i]] != NIL);
        graph->pqMap[v[i]] = PARENT(i);
        assert(graph->pqMap[v[PARENT(i)]] != NIL);
        graph->pqMap[v[PARENT(i)]] = i;
        Node tmp = v[i];
        v[i] = v[PARENT(i)];
        v[PARENT(i)] = tmp;
        i = PARENT(i);
    }
    // for(vector<Node>::iterator it=v.begin();it!=v.end();it++)
    //     cout << *((*it).first) <<" , "<< (*it).second << " | " ;
    // cout << endl;
}


//================is_spanning_tree

IsSpanningTreeCmd::IsSpanningTreeCmd(const char * const name) : Cmd(name) {
    optMgr_.setShortDes("Perform depth first search starting from source node.  Then write to a dot file.");
    optMgr_.setDes("test");

    Opt *opt = new Opt(Opt::BOOL, "print usage", "");
    opt->addFlag("h");
    opt->addFlag("help");
    optMgr_.regOpt(opt);

    opt = new Opt(Opt::STR_REQ, "", "<dot_filename>");
    opt->addFlag("i");
    optMgr_.regOpt(opt);
}

IsSpanningTreeCmd::~IsSpanningTreeCmd() {}

bool IsSpanningTreeCmd::exec(int argc, char **argv) {
    optMgr_.parse(argc, argv);

    if (argc < 3) {
        fprintf(stderr, "**ERROR SysSetCmd::exec(): ");
        fprintf(stderr, "variable and value needed\n");
        return false;
    }

    if (optMgr_.getParsedOpt("h")) {
        optMgr_.usage();
        return true;
    }

    string tmp;

    ifstream inFile(argv[2],ios::in);
    char buf[256];
    while(1){
        inFile.getline(buf,256);
        // cout << "tmp2:" << buf << endl;
        if(buf[0] != '/' && buf[1] != '/') break;
    }


    map<int,map<int,int> > spanMap;
    int edge= 0;

    while(1){
        inFile >> tmp ;
        if(strcmp(tmp.c_str(),"}")==0) break;

        int pre = atoi(tmp.substr(1).c_str());

        inFile >> tmp >> tmp;
        // cout << "tmp: " << tmp << endl;
        int suc = atoi(tmp.substr(1).c_str());
        // cout << "(pre,suc) : " << pre <<" " << suc <<endl;

        inFile.getline(buf,256);
        // cout << "buf: " << buf << endl;
        string str(buf);
        int pos = str.find_first_of("\"");
        int last = str.find_last_of("\"");
        // cout << "str.sub: " << str.substr(pos+1,last-pos-1) << endl;
        int weight = atoi(str.substr(pos+1,last-pos-1).c_str());

        spanMap[pre][suc] = weight;
        spanMap[suc][pre] = weight;

        edge++;
    }

    //check edge number
    if(edge!=spanMap.size()-1){
        cout <<"No" <<endl;
        return 0;
    }


    //check connectivity
    int count = 0;
    int* visted = new int[spanMap.size()];
    cout << "spanMap.size(): " << spanMap.size()<<endl;
    for(int i = 0 ; i < spanMap.size() ; i++ )
        visted[i] = 0;

    dfs(0,spanMap,visted,count);

    if(count != spanMap.size()){
        cout << "No" << endl << endl;
    }else
        cout << "Yes" << endl << endl;

    cout << "=====================" << endl << endl;

}

void
IsSpanningTreeCmd::dfs(int v,map<int,map<int,int> > spanMap,int* visted,int& count){
    map<int,int>::iterator it;
    visted[v] = 1;

    for(it = spanMap[v].begin();it!=spanMap[v].end();it++){
        if(visted[(*it).first] != 1)
            dfs( (*it).first ,spanMap,visted,count);
    }

    count++;
    // cout << v << " count: " << count << endl;
}

