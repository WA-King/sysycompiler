#include"parser.h"
#include"TAC.h"
#include"gen.h"
#include<iostream>
using namespace std;
int main(int argc,char *argv[]) {
    freopen("mid.out","w",stdout);
    if(argc!=2) {
        std::cout<<"input file"<<'\n';
        return 0;
    }
    std::cout<<argv[1]<<'\n';
    Parse parse(argv[1]);
    parse.init();
    parse.NextTOKEN();
    auto it=parse.getCompUnit();
    TAC tac;
    tac.ASTtoTAC(it);
	tac.print();
	GEN generator;
	generator.code=tac.code;
	generator.gen("a.asm");
    return 0;
}
