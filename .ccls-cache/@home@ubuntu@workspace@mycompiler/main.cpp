#include"parser.h"
#include<iostream>
using namespace std;
int main(int argc,char *argv[]) {
    if(argc!=2) {
        std::cout<<"input file"<<'\n';
        return 0;
    }
    std::cout<<argv[1]<<'\n';
    Parse parse(argv[1]);
    parse.init();
    parse.NextTOKEN();
    auto it=parse.getBlock();
    it=it->nex->nex;
    std::cout<<it->getval()<<'\n';
    return 0;
}
