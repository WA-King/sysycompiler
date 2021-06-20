#include"parser.h"
#include"TAC.h"
#include"gen.h"
#include<iostream>
using namespace std;
int main(int argc,char *argv[]) {
    if(argc!=2) {
        std::cerr<<"input file"<<'\n';
        return 0;
    }
    std::cerr<<argv[1]<<'\n';
	string infile=argv[1];
	string filename=infile.substr(0,infile.size()-3);
	freopen((filename+".mid").c_str(),"w",stdout);
	if(infile.substr(infile.size()-3,3)!=".sy") {
		printerror("Please input .sy file");
	}
    Parse parse(infile);
    parse.init();
    parse.NextTOKEN();
    auto it=parse.getCompUnit();
    TAC tac;
    tac.ASTtoTAC(it);
	tac.print();
	GEN generator;
	generator.code=tac.code;
	generator.gen(filename+".asm");
    return 0;
}
