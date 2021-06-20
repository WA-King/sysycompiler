#include"parser.h"
#include"TAC.h"
#include"gen.h"
#include<iostream>
using namespace std;
int main(int argc,char *argv[]) {
    if(argc!=2) {
        std::cout<<"input file"<<'\n';
        return 0;
    }
    std::cout<<argv[1]<<'\n';
	string infile=argv[1];
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
	string outfile=infile.substr(0,infile.size()-3);
	outfile+=".asm";
	GEN generator;
	generator.code=tac.code;
	generator.gen(outfile);
    return 0;
}
