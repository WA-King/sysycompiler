#ifndef _GEN_H__
#define _GEN_H__
#include"TAC.h"
#include<map>
#include<fstream>
class info {
public:
	bool instack;
	int pstack;
	int reg;
	info();
};
class GEN{
public:
	std::vector<std::string> rname={"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};
	std::vector<address> code;
	std::map<Var,int> endp;
	std::map<Var,info> biao;
	std::ofstream outfile;
	std::vector<Var> st,reg;
	std::vector<bool> usedreg;
	std::vector<std::string> data,text;
	GEN();
	void init();
	void pre();
	void delreg(Var,int);
	void delallreg(int);
	void getendp(int);
	int getreg(int);
	int isinreg(Var);
	int readVar(Var,int,bool);
	void writeVar(std::string,int,Var);
	int allpstack(int);
	int gendata(int);
	int gentext(int);
	void gen(std::string file);
};
std::string oprr(OP_TYPE,std::string,std::string,std::string);
std::string opri(OP_TYPE,std::string,std::string,int);
std::string oplsw(std::string,std::string,std::string,int);
#endif